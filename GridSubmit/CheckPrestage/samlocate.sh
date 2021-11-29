#!/bin/bash
# Liang Li
# Require bash version >= 4.0 (associative array)

program="samlocate"


usage()
{
  cat << EOF

  Locate, touch and check prestage status for any given input (file, file list or dataset).

  Usage: $program <[options]> file|filelist|dir|sam-dataset
  Options:
          -a   --alt            Alternative method when Webdev method is unavailable (warning: ~100 times slower!)
          -b   --bulk           Number of files to query simultaneously via WebDev method (default: 200)
          -e   --ext            Filename extension (default: root) 
          -l   --locate         Check if files/datasets are located (default action)
          -p   --prestage       Check if files/datasets are (pre-)staged
          -r   --role           Run as Analysis or Production Role (default: Analysis)
          -t   --touch          Touch files/datasets
          -v   --verbose        Verbose printout (e.g. print file location)
               --vv             VERY verbose printout
          -h   --help           Display this help and exit

EOF
[[ ! -z $1 ]] && echo -e "\n\t$1\n"
exit 2
}

error()
{
  printf "\n$1\n\n"
  exit 1
}

which getopt >/dev/null 2>&1
[ $? -ne 0 ] && error "Install GNU 'getopt' first!"
which samweb 2>&1 >/dev/null
[ $? -ne 0 ] && error "Where is samweb? Did you run setup?"
which curl 2>&1 >/dev/null
[ $? -ne 0 ] && error "Where is curl? Did you run setup?"
which id >/dev/null 2>&1
if [ $? -eq 0 ]; then
      if [[ -z $UID ]]; then
            UID=$(id -u $USER)
      else
            [[ $UID != $(id -u $USER) ]] && error "UID mismatch: id -u $USER gives `id -u $USER` but \$UID gives $UID !"
      fi
else
      [[ -z $UID ]] && error "Empty UID! please check user ID!"
fi


[[ -z $EXPERIMENT ]] && [[ -z ${SAM_EXPERIMENT} ]] && error "SAM_EXPERIMENT or EXPERIMENT environment variable needs to be set first!"

export WEB_URI="https://fndca1.fnal.gov:2880/pnfs/fnal.gov/usr"
#old server name now alias to fndca4b, more general name fndca1
#export WEB_URI="https://fndca4a.fnal.gov:2880/pnfs/fnal.gov/usr"
XROOT_URI="xroot://fndca1.fnal.gov:1094/pnfs/fnal.gov/usr"

#taken from https://cdcvs.fnal.gov/redmine/projects/novaart/repository/entry/trunk/NovaGridUtils/bin/cache_state.py and modified
export CCMD="curl  -L --capath /etc/grid-security/certificates \
             --cert   /tmp/x509up_u$UID \
             --cacert /tmp/x509up_u$UID \
             --key    /tmp/x509up_u$UID \
             -s -X PROPFIND -H Depth:0 \
             --data '<?xml version=\"1.0\" encoding=\"utf-8\"?>
              <D:propfind xmlns:D=\"DAV:\">
                  <D:prop xmlns:R=\"http://www.dcache.org/2013/webdav\"
                          xmlns:S=\"http://srm.lbl.gov/StorageResourceManager\">
                      <S:FileLocality/>
                  </D:prop>
              </D:propfind>'"
 
#echo "$@"
OPTIONS=$(getopt -o ab:e:hlpr:tv --long alt:,bulk:,ext:,help,locate,prestage,role:,touch,verbose,vv -n $program -- "$@")
#echo "$OPTIONS"

[ $? -ne 0 ] && usage

eval set -- "$OPTIONS"

export do_alt=0                 # alternative method (check .locality)
export ext="root"               # work on root files by default
export verbose=0                # show full inquiry result
export role=${ROLE:-Analysis}   # VOMS role
export do_touch=0               # touch file
export do_locate=1              # locate file (default action)
export check_prestage=0         # check stage status
np=15                           # number of parallel processes
bulk=200                        # number of files to query at the same time
action=""                       # action name

input=()
inputdir=()
inputlist=()
inputfile=()
inputdef=()

#echo "$@"

while [ $# -gt 0 ]; do
    #echo $1
    case "$1" in
         -a|--alt)      do_alt=1;;
         -b|--bulk)     bulk=$2; shift;;
         -e|--ext)      ext=$2; shift;;
         -h|--help)     usage;;
         -l|--locate)   do_locate=1;;
         -p|--prestage) check_prestage=1; do_locate=0;;
         -r|--role)     role=$2; shift;;
         -t|--touch)    do_touch=1; do_locate=0;;
         -v|--verbose)  verbose=1;;
         --vv)          verbose=2;;
         --)            ;;
         *)             input+=($1);;
    esac
    shift
done
         

[ ${#input[@]} -eq 0 ] && usage

[ ${do_touch} -eq 0 -a ${do_locate} -eq 0 -a ${check_prestage} -eq 0 ] && usage

klist -s || kinit 2>/dev/null 
if ! kx509 >/dev/null 2>&1; then
     kx509
     echo -e "\n***Unable to get a valid Kerbose certificate, check screen printout for detailed information."  
     echo -e "***Try to fix it via tuning environment setup and/or security settings, or use a different machine."
     echo -e "***As the last resort, use -a or --alt to activate the alternative method (Warning: 50-100 times slower).\n" 
     sleep 3 && exit 1
fi

if [ ${do_touch} -eq 1 -a ${check_prestage} -eq 1 ]; then
     action="touching and checking prestage status for"
elif [ ${do_touch} -eq 1 ]; then
     action="touching"
elif [ ${check_prestage} -eq 1 ]; then
     action="checking prestage status for"
     if [[ ${do_alt} -eq 0 ]] && [[ $(voms-proxy-info -all |grep -A100 'VO fermilab' |grep timeleft |awk -F: '{print $2+$3+$4}') -eq 0 ]]; then
          if [[ $USER != "gm2pro" ]] && [[ $role != "Production" ]]; then
                voms-proxy-destroy > /dev/null 2>&1
                klist -s || kinit 
                if kx509; then
                   if voms-proxy-init -rfc -noregen -voms=fermilab:/fermilab/gm2/Role=Analysis; then
                      if [ $(voms-proxy-info -all |grep -A100 'VO fermilab' |grep timeleft |awk -F: '{print $2+$3+$4}') -eq 0 ]; then
                           voms-proxy-info -all
                           echo -e "\n***Unable to generate a valid voms proxy, check screen printout for detailed information."
                           echo -e "***Try to fix it via tuning environment setup and/or security settings, or use a different machine."
                           echo -e "***As the last resort, use -a or --alt to activate the alternative method (Warning: 50-100 times slower).\n"  
                           sleep 3 && exit 1
                      fi
                   else
                      echo -e "\n***Unable to generate a valid voms proxy, check screen printout for detailed information."
                      echo -e "***Try to fix it via tuning environment setup and/or security settings, or use a different machine."
                      echo -e "***As the last resort, use -a or --alt to activate the alternative method (Warning: 50-100 times slower).\n"
                      sleep 3 && exit 1 
                   fi
                else
                      echo -e "\n***Unable to get a valid Kerbose certificate, check screen printout for detailed information."  
                      echo -e "***Try to fix it via tuning environment setup and/or security settings, or use a different machine."
                      echo -e "***As the last resort, use -a or --alt to activate the alternative method (Warning: 50-100 times slower).\n" 
                      sleep 3 && exit 1
                fi
          else
                export X509_USER_PROXY=/opt/gm2pro/gm2pro.Production.proxy
                if [[ $(voms-proxy-info -all |grep -A100 'VO fermilab' |grep timeleft |awk -F: '{print $2+$3+$4}') -eq 0 ]]; then
                     voms-proxy-info -all
                     echo -e "\n***Unable to generate a valid voms proxy, check screen printout for detailed information."
                     echo -e "***Try to fix it via tuning environment setup and/or security settings, or use a different machine."
                     echo -e "***As the last resort, use -a or --alt to activate the alternative method (Warning: 50-100 times slower).\n"  
                     sleep 3 && exit 1
                fi
          fi
     fi
else
     action="processing"
fi

function sam_locate_file()
{
        local tag=$1; shift
        local file=""
        local location=""
        local locations=""
        for file in "$@"; do
            [[ $file =~ ^[0-9]+$ ]] && continue
            if locations=$(samweb locate-file $file 2>/dev/null); then
               #echo "locations=$locations" >&2
               if [[ -z $locations ]]; then
                     echo -e "\nEmpty location for '$file'!\n" >&2
                     return
               fi
               for location in $locations; do
                   [[ -z $location ]] && continue
                   location=$(echo $location | sed -e "s/^\([^:]\+\):\(.*\)(\(.*\)/\2/g" -e "s/^\([^:]\+\):\(.*\)/\2/g")
                   if [[ $tag -ge 1 ]]; then
                         if [ -e "$location/$file" ]; then
                              ((countl++))
                              if [[ $tag -eq 1 ]]; then
                                    echo "$location/$file" `du -h "$location/$file" | cut -f1`
                              else
                                    echo "$location/$file" `du -h "$location/$file" | cut -f1` `cat "$location/.(get)($file)(locality)"`
                              fi
                         else
                              echo "Cannot find $location/$file !" >&2
                         fi
                   else
                         if [ -e "$location/$file" ]; then       
                              echo "$location/$file"
                         else
                              echo "Cannot find $location/$file !" >&2
                         fi
                   fi
               done
            else              
               echo -e "\nCannot locate file '$file'!\n" >&2
            fi
        done
}

export -f sam_locate_file


count=0
countt=0
countp=0
countl=0
countll=0

for x in "${input[@]}"; do
##      echo "x=$x"
        if [ -d "$x" ]; then
           [ ! -r "$x" ] && error "Cannot access directory: '$x'!\n"
           inputdir+=("$x")
        elif [ -f "$x" ]; then
           [ ! -r "$x" ] && error "Cannot access file: '$x'!"
           if [[ "$x" == *.$ext ]]; then
                 inputfile+=("$x")
                 ((count++))
           else
                 inputlist+=("$x")
           fi
        elif y=$(samweb locate-file "$x" 2>/dev/null); then
             if [[ ! -z "$y" ]]; then
                   inputfile+=($(sam_locate_file 0 $x))
                   ((count++))
             else
                   error "Empty location for file '$x'!"
             fi
        else
           if ! samweb describe-definition $x 1>/dev/null; then
              error "Not a file (list), directory or dataset defintion: '$x'!"
           fi
           inputdef+=($x)
        fi
done


dirfile=()
listfile=()
deffile=()
deffiles=()
inputfiles=()
mfiles=()

function check_files()
{
        local files=("$@")
        local size=${#files[@]}
        local location=""
        local file=""
        local LOC=()
        local OUT=()
        local CMD=""

        if [ ${do_locate} -eq 1 ]; then
             countl=$((countl+${#files[@]}))
             [ $verbose -ge 2 ] && echo -e "\n" && printf "%s\n" "${files[@]}"
        fi

        if [ ${do_touch} -eq 1 ]; then
             [ $verbose -ge 2 ] && echo "touch ${files[@]}"
             if touch "${files[@]}" >/dev/null 2>&1; then
                ((countt+=size))
             else
                echo -e "\nError touching files: ${files[@]}, check permission!\n"
             fi
        fi
        
        if [ ${check_prestage} -eq 1 ]; then
             for file in "${files[@]}"; do
                 #dirname
                 location=${file%/*}
                 #basename
                 file=${file##*/}
                 if [ ${do_alt} -eq 1 ]; then
                      location="$location/.(get)($file)(locality)"
                 else
                      location="${location/\/pnfs/${WEB_URI}}/$file"
                 fi
                 LOC+=("$location")
             done
             if [ ${do_alt} -eq 1 ]; then
                  CMD="cat ${LOC[@]}"
             else
                  CMD="$CCMD ${LOC[@]}"
             fi

             [ $verbose -ge 2 ] && echo "$CMD"
             
             if [ ${do_alt} -eq 1 ]; then
                  OUT=$($CMD 2>&1)
             else
                  OUT=$(eval $CMD 2>&1)
             fi
             [ $verbose -ge 2 ] && echo "$OUT"
             local count=$(echo "$OUT" | grep -c ONLINE)
             ((countp+=count))
        fi

}

export -f check_files

function progressbar()
{
#print  "\e[H";              # Put the cursor on the first line
#print  "\e[J";              # Clear from cursor to end of screen
#print  "\e[H\e[J";          # Clear entire screen (just a combination of the above)
#print  "\e[K";              # Clear to end of current  line (as stated previously)
#print  "\e[m";              # Turn off character attributes (eg. colors)
#printf "\e[%dm", $N;        # Set color to $N (for values of 30-37, or 100-107)
#printf "\e[%d;%dH", $R, $C; # Put cursor at row $R, column $C (good for "drawing")

	local total=${1:-1}
        local current=${2:-0}
        local out=${3:-1}
        local head=${4:-Progess}
        local width=${4:-60}
        local symbol=${5:-=}
        
        local percent=$((current*100/total))
        local size=$((current*width/total))
        local remaining=$((total-current))
        local bar
        printf -v bar "%*s" "$size" ""
        bar=${bar// /$symbol}

        if [ $out -eq 1 ]; then
             printf "\r\e[K%s [%-*s] %3d%%: %d/%d done and %d to go..." "$head" $width "$bar" $percent $current $total $remaining
             #[ $verbose -ge 2 ] && echo -e "\n"
        elif [ $out -eq 2 ]; then
             printf "\r\e[K%s [%-*s] %3d%%: %d/%d done and %d to go..." "$head" $width "$bar" $percent $current $total $remaining >&2
             #[ $verbose -ge 2 ] && echo -e "\n" >&2
        elif [ $out -eq 3 ]; then
             printf "\r\e[K%s [%-*s] %3d%%: %d/%d done and %d to go..." "$head" $width "$bar" $percent $current $total $remaining >&3
             #[ $verbose -ge 2 ] && echo -e "\n" >&3
        fi

}
export -f progressbar

loclist=""
stagedlist=""
unstagedlist=""

if [ $verbose -ge 1 ] && ( [ ${#inputlist[@]} -ge 1 ]  || [ ${#inputdef[@]} -ge 1 ] ); then
     mkdir -p /tmp/$USER || error "Unable to create temporary directory at '/tmp/$USER'!"
     if [ ${#inputlist[@]} -ge 1 ]; then
          loclist=/tmp/$USER/$program.located.${inputlist[0]}
          stagedlist=/tmp/$USER/$program.staged.${inputlist[0]}
          unstagedlist=/tmp/$USER/$program.unstaged.${inputlist[0]}
     elif [ ${#inputdef[@]} -ge 1 ]; then
          loclist=/tmp/$USER/$program.located.${inputdef[0]}
          stagedlist=/tmp/$USER/$program.staged.${inputdef[0]}
          unstagedlist=/tmp/$USER/$program.unstaged.${inputdef[0]}
     fi

     if ! truncate -s 1k $loclist > /dev/null 2>&1; then
          error "Cannot create file '$loclist', check /tmp space!"
     fi
     rm -f $loclist $stagedlist $unstagedlist
fi	


echo
date
echo

if [ ${#inputfile[@]} -ge 1 ]; then
     echo -e "Locating ${#inputfile[@]} $ext file(s): ${inputfile[@]} ...\n"
fi

if [ ${#inputdir[@]} -ge 1 ]; then
     echo -e "Locating $ext files from directories: ${inputdir[@]} ...\n"
     readarray -t dirfile < <(find "${inputdir[@]}" -name "*.$ext")
     [ $verbose -ge 2 ] && [ ${#dirfile[@]} -ge 1 ] && printf "%s\n" "${dirfile[@]}" && echo
fi

count=$((count+${#dirfile[@]}))
i=0
x=0

#echo "count=$count"

if [ ${#inputlist[@]} -ge 1 ]; then
     x=$(cat "${inputlist[@]}" | grep -c "\.$ext")
     echo -e "Locating $x $ext files from list(s): ${inputlist[@]} ...\n"
     while read -r line ; do 
           if [[ "$line" == http* ]]; then
                 line=${line/${WEB_URI}/\/pnfs}
           elif [[ "$line" == xroot* ]]; then
                 line=${line/${XROOT_URI}/\/pnfs}
           fi
           if [ -r "$line" ]; then
                ((count++))
                listfile+=("$line")
                if [[ $verbose -eq 1 ]]; then
                      echo "$line" `du -h "$line" | cut -f1` | tee -a $loclist
                elif [[ $verbose -ge 2 ]]; then
                      echo "$line" `du -h "$line" | cut -f1` `cat "$(dirname "$line")/.(get)($(basename "$line"))(locality)"` | tee -a $loclist
                fi
           elif line=$(sam_locate_file $verbose "$line"); then
                ((count++))
                if [[ ! -z "$line" ]]; then
                      listfile+=("$line")
                      if [[ $verbose -ge 1 ]]; then 
                            echo "$line" | tee -a $loclist
                      fi
                else
                      echo -e "\nEmpty location for file '$line'!\n"
                fi 
           else
                echo -e "\nCannot access file '$line'!\n"
           fi
           ((i++))
           [[ $verbose -eq 0 ]] && progressbar $x $i
     done < <(cat "${inputlist[@]}" | grep "\.$ext") 
     [ $x -gt 0 ] && echo
     [ $verbose -ge 2 ] && [ ${#listfile[@]} -ge 1 ] && printf "%s\n" "${listfile[@]}" && echo
fi


if [ ${#inputdef[@]} -ge 1 ]; then
     echo -e "Locating files from dataset(s): ${inputdef[@]} ...\n"
fi

for def in "${inputdef[@]}"; do
     x=$(samweb count-definition-files $def)
     [[ $x == 0 ]] && echo "Empty definition: $def" && continue
     if [ ${do_locate} -eq 1 -a ${check_prestage} -eq 0 ] && [ $verbose -ge 1 ]; then
           ((count+=x))
           sam_locate_file $verbose $(samweb list-definition-files $def) | tee -a $loclist
     else 
           readarray -t deffile < <(samweb list-definition-files $def | nl -bt | \
                             xargs -P $np -n $bulk bash -c 'progressbar '$x' $(($1-1)) 2; sam_locate_file 0 "$@"' anything)
           progressbar $x $x && echo
           [ $verbose -ge 1 ] && [ ${#deffile[@]} -ge 1 ] && echo -e "\n" && printf "%s\n" "${deffile[@]}" && echo
           deffiles+=("${deffile[@]}")
           count=$((count+${#deffiles[@]}))
     fi
done


echo -e "\n"
date
echo

inputfiles=("${inputfile[@]}" "${dirfile[@]}" "${listfile[@]}" "${deffiles[@]}")
#sanity check
[ $count -ne ${#inputfiles[@]} ] && [ ! -e $loclist ] && error "Array sizes mismatch, check inputfiles list: $count != ${#inputfiles[@]} !"


#uniq array
[ ${#inputfiles[@]} -gt 0 ] && readarray -t mfiles < <(printf '%s\n' "${inputfiles[@]}" | awk '!a[$0]++')


if [[ ! -z $loclist ]] && [[ -s $loclist ]]; then

     countll=$(wc -l $loclist | cut -d ' ' -f1)
     if [ $verbose -ge 2 ]; then
          mfiles=()
          grep ' ONLINE' $loclist | cut -d ' ' -f1 > $stagedlist     
          [ -s $stagedlist ] && countp=$(wc -l $stagedlist | cut -d ' ' -f1)
          [[ $countp -lt $countll ]] && grep -v ' ONLINE' $loclist | cut -d ' ' -f1 > $unstagedlist
     fi

else
     if [ $count -gt ${#mfiles[@]} ]; then
          echo -e "Removed $(( count-${#mfiles[@]} )) duplicated files from the list.\n"
          count=${#mfiles[@]}
     elif [ $count -lt ${#mfiles[@]} ]; then
            error "Array size error, check mfiles list: $count < ${#mfiles[@]} !"
     fi

     if [ ${#mfiles[@]} -ge 1 ]; then
          echo -e "Processing ${#mfiles[@]} files in total...\n"
          [ $verbose -ge 1 ] && printf "%s\n" "${mfiles[@]}" && echo
     else
            echo -e "Zero files found, check inputs!\n"
     fi

fi

#echo "countl=$countl, $countll"

sub=()
left=()
m=0

[ $verbose -ge 1 ] && echo -e "----------------------------------------------------------------------\n"

while [ ${#mfiles[@]} -gt 0 ]; do
        m=${#mfiles[@]}
# Slice files array into sub and left
        if [ $m -le $bulk ]; then
             sub=("${mfiles[@]}")
             left=()
        else
             (( m=m-bulk ))
             sub=("${mfiles[@]:0:bulk}")
             left=("${mfiles[@]:bulk:m}")
        fi

        check_files "${sub[@]}"
        progressbar $count $((count-${#left[@]}))

        mfiles=("${left[@]}")
done

#echo "countl=$countl, $countll"

echo -en "\n\nFinished $action $count files,"

if [ $count -gt 0 ]; then

   if [ ${do_touch} -eq 1 -a ${check_prestage} -eq 1 ]; then

        echo -e " $countt (~$((100*countt/count))%) are touched, $countp (~$((100*countp/count))%) are staged.\n" 

   elif [ ${do_touch} -eq 1 ]; then
     echo -e " $countt (~$((100*countt/count))%) are touched.\n" 

   elif [ ${check_prestage} -eq 1 ]; then
     echo -en " $countp (~$((100*countp/count))%) are staged." 
     if [[ ! -z $loclist ]] && [ -s $loclist -a $verbose -ge 1 ]; then
          countl=$countll
          echo -e " $countl (~$((100*countl/count))%) are located.\n\nLocated file list: $loclist\n"
          [[ $verbose -ge 2 ]] && [[ $countp -gt 0 ]] && echo -e "Staged file list: $stagedlist\n"
          [[ $verbose -ge 2 ]] && [[ $countp -lt $count ]] && echo -e "Unstaged file list: $unstagedlist\n"
     else
          echo   
     fi 
   else
     if [[ ! -z $loclist ]] && [ -s $loclist -a $verbose -ge 1 ]; then
          countl=$countll
          echo -en " $countl (~$((100*countl/count))%) are located."
          if [ $verbose -ge 2 ]; then
               echo -e " $countp (~$((100*countp/count))%) are staged.\n\nLocated file list: $loclist\n"
               [[ $countp -gt 0 ]] && echo -e "Staged file list: $stagedlist\n"
               [[ $countp -lt $count ]] && echo -e "Unstaged file list: $unstagedlist\n"
          else
               echo -e "\n\nLocated file list: $loclist\n"
          fi
     else
          echo -en " $countl (~$((100*countl/count))%) are located."
     fi 
   fi
else
     echo -e " empty list?\n"
fi

date
echo
