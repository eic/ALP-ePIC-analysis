#!/bin/bash
if [ "$#" -ne 3 ]; then
    echo "Usage: bash run_analysis.sh <input_file> <output_file> <tree_output_file>"
    exit 1
fi

infile=$1
outfile=$2
treefile=$3 #AW 20260605i
#signal_type=$4

BASE_DIR="$(cd ""$(dirname "${BASH_SOURCE[0]}")"/.." && pwd)"
LIB_DIR="${BASE_DIR}/lib"
MACRO_DIR="${BASE_DIR}/macros"
INC_DIR="${BASE_DIR}/MyAnalysis"

export LD_LIBRARY_PATH="${LIB_DIR}:${LD_LIBRARY_PATH}"
export ROOT_INCLUDE_PATH="${INC_DIR}:${ROOT_INCLUDE_PATH}"

root -l -b -q -e 'gSystem->Load("libMyAnalysis.so");' "${MACRO_DIR}/analysis.C(\"${infile}\", \"${outfile}\", \"${treefile}\")" #AW 20260605
