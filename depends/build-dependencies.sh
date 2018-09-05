#!/bin/bash


build_dep() {
    pushd $1
    ./build.sh
    popd
}

build_dep libbitcoin