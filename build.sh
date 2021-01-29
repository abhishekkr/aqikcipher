#!/usr/bin/env bash

set -ex

PROJECT_DIR=$(dirname $0)
BUILD_DIR="${PROJECT_DIR}/out"
BINARY_NAME="aqikcipher"

buildBinaries(){
  [[ ! -d "${BUILD_DIR}" ]] && mkdir "${BUILD_DIR}"

  gcc -o "${BUILD_DIR}/${BINARY_NAME}" ./aQikCipher.c
}

##### main
buildBinaries
