# Add current directory to LD_LIBRARY_PATH for so file we copied
export LD_LIBRARY_PATH=`pwd`:$LD_LIBRARY_PATH

# Some nodes have newer kernels
case 3.10.0-1160.15.2.el7.x86_64 in
  3.*) export UPS_OVERRIDE="-H Linux64bit+2.6-2.12";;
  4.*) export UPS_OVERRIDE="-H Linux64bit+2.6-2.12";;
esac

# Run jobs
while read file; do 

  echo "Processing $file"

  subRun=${file##*_}
  subRun=${subRun%.*}
  subRun=${subRun#*.}

  # Update input file names in fcl file
  echo "" >> RunCaloBeamPositionPlots_Run23.fcl
  echo "source.fileNames: [ \"$file\" ]" >> RunCaloBeamPositionPlots_Run23.fcl

  gm2 -c RunCaloBeamPositionPlots_Run23.fcl -T caloBeamPositionPlots_26708.${subRun}.root

  # Only copy back if job completed successfully (output from last command was 0)
  if [ $? -eq 0 ]; then
    if [ -f caloBeamPositionPlots_26708.${subRun}.root ]; then
      ifdh mv caloBeamPositionPlots_26708.${subRun}.root /pnfs/GM2/scratch/users/sgrant/BrAna/CaloBeamPos_NewCuts/gm2pro_daq_offline_dqc_run2F/26708/caloBeamPositionPlots_26708.${subRun}.root
    else 
      echo "caloBeamPositionPlots_26708.${subRun}.root does not exist.  ls reads:"
      ls
    fi
  fi
done < xrootdFileList000.txt
