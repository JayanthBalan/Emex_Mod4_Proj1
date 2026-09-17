#!/bin/bash

make clean
make

if [ $# -eq 2 ]
then
    echo "Running program for all possible options with inputs"
    ./apc $1 + $2
    ./apc $1 - $2
    ./apc $1 "*" $2
    ./apc $1 / $2
else
    echo "Running program for all possible options with default values: \$1 = 3031239, \$2 = 31"
    ./apc 3031239 + 31
    ./apc 3031239 - 31
    ./apc 3031239 x 31
    ./apc 3031239 / 31
fi
