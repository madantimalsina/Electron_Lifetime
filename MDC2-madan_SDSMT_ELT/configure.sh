#!/bin/bash

source /cvmfs/lz.opensciencegrid.org/LzBuild/release-latest/LzBuild/setup.sh 

mkdir -p bin

rm -rf rqlib/*
root -b -q configure.C\(\"$1\"\)
sed -i '/#include <vector>/a using namespace std;' rqlib/*h
