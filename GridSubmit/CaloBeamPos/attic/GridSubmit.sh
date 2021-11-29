#Setup all the stuff we need here
source /gm2/app/users/sgrant/scripts/setup_fnal_security
source /grid/fermiapp/products/common/etc/setups.sh
setup jobsub_client
setup fife_utils

# Check that samweb and root are installed
command -v samweb >/dev/null 2>&1 || { echo >&2 "samweb not found. You want:"; echo "source /grid/fermiapp/products/common/etc/setups.sh"; echo "setup fife_utils"; return; }

# Get list of files in SAM dataset
echo "Getting SAM file list."
dataset=$1
samweb -e gm2 list-definition-files $dataset > tmp.txt
echo "Sorting SAM file list."
sort -t_ -k4 tmp.txt > SAMFileList.txt
rm -f tmp.txt

# Check for jobs that haven't been processed already
currJobRun=-1
currRunPath=""
rm -f FileList.txt && touch FileList.txt

echo "Reading SAM list"

while read file; do # in `cat SAMFileList.txt`; do 

	# Get run and sub-run
  run=${file##*_}
  run=${run%%.*}
  subrun=${file##*${run}.}
  subrun=${subrun%%.*}

  # Make output directory
  pnfsOutDir=/pnfs/GM2/scratch/users/${USER}/BrAna/CaloBeamPos/${dataset}/${run}

  if [ ! -d $pnfsOutDir ]; then
    mkdir -p $pnfsOutDir
    chmod -R g+w $pnfsOutDir
  fi

  echo "Output files will appear in $pnfsOutDir"

  # If we're in a new run (or the first run), submit the old lot and clear FileList
  if [ $run -ne $currJobRun ]; then

  	# Check if filelist exists with size greater than zero 
    if [ -s FileList.txt ]; then
      bash -c ". submitFiles.sh"
      rm -f FileList.txt && touch FileList.txt
      # If testing, add return statment here
      return
    fi

    fullFilePath=`samweb -e gm2 locate-file $file`
    currRunPath=/pnfs${fullFilePath##*/pnfs}
    currRunPath=${currRunPath%%(*}
    currJobRun=$run

  fi

  echo $fullFilePath
  echo $currRunPath

  echo ${currRunPath}/${file} >> FileList.txt

done < SAMFileList.txt

# Catch final submission (as we've left loop)
if [ -s FileList.txt ]; then
 echo "done"
 bash -c ". submitFiles.sh"
 rm -f FileList.txt
fi
