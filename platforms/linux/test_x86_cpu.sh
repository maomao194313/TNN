#!/bin/bash
DEBUG=0
CLEAN=""

WORK_DIR=`pwd`
BUILD_DIR=build
MODEL_DIR=$WORK_DIR/models
DUMP_DIR=$WORK_DIR/dump_data
#INPUT_FILE_NAME=hdr_test.jpg
INPUT_FILE_NAME=rpn_in_0_n1_c3_h320_w320.txt

function usage() {
    echo "-c\tClean up build folders."
}
function die() {
    echo $1
    exit 1
}

function clean_build() {
    echo $1 | grep "$BUILD_DIR\b" > /dev/null
    if [[ "$?" != "0" ]]; then
        die "Warnning: $1 seems not to be a BUILD folder."
    fi
    rm -rf $1
    mkdir $1
}

function build_x86() {
    if [ "-c" == "$CLEAN" ]; then
        clean_build $BUILD_DIR
    fi
    mkdir -p build
    cd $BUILD_DIR
    cmake ../../.. \
          -DCMAKE_BUILD_TYPE=Release \
          -DDEBUG=$DEBUG \
          -DTNN_TEST_ENABLE:BOOL="ON"  \
          -DTNN_CPU_ENABLE:BOOL="ON"  \
          -DTNN_BUILD_SHARED:BOOL="ON"  \
          -DTNN_OPENMP_ENABLE:BOOL="ON"
    make -j4
}

function run_x86() {
    build_x86
    mkdir -p $DUMP_DIR
    ./test/TNNTest -mp=$MODEL_DIR/test.tnnproto -ip=$MODEL_DIR/$INPUT_FILE_NAME -dt="NAIVE" -op=dump_data.txt -wc=0 -ic=1
}

while [ "$1" != "" ]; do
    case $1 in
        -c)
            shift
            CLEAN="-c"
            ;;
        *)
            usage
            exit 1
    esac
done

run_x86
