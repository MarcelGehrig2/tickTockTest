#!/bin/bash
my_scriptname="$(basename $0)"

echo "[SCRIPT] $my_scriptname"


cd ../buildX86/
make -j2
cd -
