#!/bin/bash

lab=$1

if [ "$lab" == 1 ]
then
    cd lab1/ && ./script.sh "${@:2}"
elif [ "$lab" == 2 ]
then
    cd lab2/ && make run
fi
