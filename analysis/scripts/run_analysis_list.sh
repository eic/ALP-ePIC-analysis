#!/bin/bash
if [ "$#" -ne 3 ]; then
    echo "Usage: bash run_analysis.sh <input_file_index> <input_file_list> <output_file>"
    exit 1
fi

infile=$(tail -n +$1 $2 | head -n 1)
outfile=$3

BASE_DIR="$(cd ""$(dirname "${BASH_SOURCE[0]}")"/.." && pwd)"
LIB_DIR="${BASE_DIR}/lib"
MACRO_DIR="${BASE_DIR}/macros"
INC_DIR="${BASE_DIR}/MyAnalysis"

export LD_LIBRARY_PATH="${LIB_DIR}:${LD_LIBRARY_PATH}"
export ROOT_INCLUDE_PATH="${INC_DIR}:${ROOT_INCLUDE_PATH}"

root -l -b -q -e 'gSystem->Load("libMyAnalysis.so");' "${MACRO_DIR}/analysis.C(\"${infile}\", \"${outfile}\")"
