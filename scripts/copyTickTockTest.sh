#!/bin/bash


target_name="es105"
project_build_file="/home/mgehrig2/projects/tickTockTest/buildMPC/ticktocktest"
target_folder="/root/"



echo "copy project to " "$target_name"
scp $project_build_file root@$target_name:$target_folder
