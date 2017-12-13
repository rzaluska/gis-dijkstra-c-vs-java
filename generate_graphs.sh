#!/bin/bash

for v in 100 500 1000 5000 10000; do
    max_edges=$(($v*($v - 1)/2))
    threefour=$((($max_edges*3)/4))
    half=$(($max_edges/2))
    four=$(($max_edges/4))
    tenth=$(($max_edges/10))
    for e in $tenth $four $half $threefour $max_edges; do
        graph_file=$v-$e.txt
        python graph-generator/graph-generator.py -v $v -e $e > graphs/$graph_file
    done
done
