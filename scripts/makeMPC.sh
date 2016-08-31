#!/bin/bash
my_scriptname="$(basename $0)"

echo "[SCRIPT] $my_scriptname"

cd ../buildMPC/
make -j2
cd -
