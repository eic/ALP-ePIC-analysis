#!/bin/bash
if [ "$#" -ne 2 ]; then
    echo "Usage: bash run_analysis.sh <input_file> <output_file>"
    exit 1
fi

################################################################################
# TO BE removed
oldpath="$(pwd)"
newpath="$(cd ""$(dirname "${BASH_SOURCE[0]}")"/.." && pwd)"
cd $newpath
make clean
make
cd $oldpath

read -n 1 -s -r -p "Press any key to continue..."
echo # Add a newline after the key is pressed
################################################################################

infile=$1
outfile=$2

BASE_DIR="$(cd ""$(dirname "${BASH_SOURCE[0]}")"/.." && pwd)"
LIB_DIR="${BASE_DIR}/lib"
MACRO_DIR="${BASE_DIR}/macros"
INC_DIR="${BASE_DIR}/MyAnalysis"

export LD_LIBRARY_PATH="${LIB_DIR}:${LD_LIBRARY_PATH}"
export ROOT_INCLUDE_PATH="${INC_DIR}:${ROOT_INCLUDE_PATH}"

root -l -b -q -e 'gSystem->Load("libMyAnalysis.so");' "${MACRO_DIR}/analysis.C(\"${infile}\", \"${outfile}\")"
