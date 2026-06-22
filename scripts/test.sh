#!/bin/bash
script="/gpfs/mnt/gpfs02/eic/awheeler/large_jobs/ALP_analysis/ALP-ePIC-main/analysis/scripts/run_analysis.sh"
infile=$1
outfile=$2
treefile=$3
#signal_type=$4
remake=$4


if [[ "$#" -lt 3 || "$#" -gt 4 ]]; then
    echo "Usage: bash test.sh <input_file> <output_file> <tree_output_file> <signal_type>" #AW 20260605
    echo "Usage: bash test.sh <input_file> <output_file> <tree_output_file> <recompile_library> <signal_type>"
fi

if [ "$#" -eq 3 ]; then
    remake=1
fi

if [ "$remake" -eq 1 ]; then
    oldpath="$(pwd)"
    newpath="$(cd ""$(dirname "${BASH_SOURCE[0]}")"/.." && pwd)"
    cd $newpath
    make clean
    make
    cd $oldpath
fi

read -n 1 -s -r -p "Press any key to continue..."

$script $infile $outfile $treefile
