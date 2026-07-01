#!/bin/bash
if [[ "$#" -ne 2 && "$#" -ne 3 ]]; then
    echo "Usage: bash run_analysis.sh <input_file> <output_file>"
    echo "Usage: bash run_analysis.sh <input_file> <output_file> <tree_file>"
    exit 1
fi

maketree=0
if [ "$#" -eq 3 ]; then
    maketree=1
fi

infile=$1
outfile=$2
if [ $maketree -eq 1 ]; then
    treefile=$3
fi

#BASE_DIR="$(cd ""$(dirname "${BASH_SOURCE[0]}")"/.." && pwd)"
BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

LIB_DIR="${BASE_DIR}/lib"
MACRO_DIR="${BASE_DIR}/macros"
INC_DIR="${BASE_DIR}/MyAnalysis"

export LD_LIBRARY_PATH="${LIB_DIR}:${LD_LIBRARY_PATH}"
export ROOT_INCLUDE_PATH="${INC_DIR}:${ROOT_INCLUDE_PATH}"

if [ $maketree -ne 1 ]; then
    root -l -b -q -e 'gSystem->Load("libMyAnalysis.so");' "${MACRO_DIR}/analysis.C(\"${infile}\", \"${outfile}\")"
else
    root -l -b -q -e 'gSystem->Load("libMyAnalysis.so");' "${MACRO_DIR}/analysis.C(\"${infile}\", \"${outfile}\", \"${treefile}\")"
fi
