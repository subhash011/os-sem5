#!/bin/bash

lab=$1

if [ "$lab" == 1 ]
then
    cd lab1/ && ./script.sh "${@:2}"
fi