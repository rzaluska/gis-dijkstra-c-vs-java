#!/bin/bash

# compile c
cd c
make -B
cd ..

# compile java
cd java
javac *.java
cd ..

echo '"v","e","s","t"' >> results_c.txt
echo '"v","e","s","t"' >> results_java.txt

# benchmarks for random graphs
for v in 10 100 1000 10000; do
    max_edges=$(($v*($v - 1)/2))
    inc=$(($max_edges/6)) #6 steps increment of number of edeges
    for e in $(seq $inc $inc $(($max_edges+1))); do
        graph_file=$(mktemp)
        python graph-generator/graph-generator.py -v $v -e $e > $graph_file
        for i in $(seq 100); do
            cat $graph_file | ./c/dijkstra >> results_c.txt
            cat $graph_file | java -cp ./java Dijkstra >> results_java.txt
        done
        rm $graph_file
    done
done

exit
# skip below

# benchmarks for HackerRank graphs

for f in test-cases/*.in.txt
do
    for i in $(seq 100); do
        echo "cat $f | ./c/dijkstra >> results_c.txt"
        cat $f | ./c/dijkstra >> results_c.txt
        echo "cat $f | java -cp ./java Dijkstra >> results_java.txt"
        cat $f | java -cp ./java Dijkstra >> results_java.txt
    done
done

