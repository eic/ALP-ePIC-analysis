#!/bin/bash
script="/gpfs/mnt/gpfs02/eic/namjae/madgraph/analysis/scripts/run_analysis.sh"
infile=$1
outfile=$2
remake=$3


if [[ "$#" -lt 2 || "$#" -gt 3 ]]; then
    echo "Usage: bash test.sh <input_file> <output_file>"
    echo "Usage: bash test.sh <input_file> <output_file> <recompile_library>"
fi

if [ "$#" -eq 2 ]; then
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

$script $infile $outfile
