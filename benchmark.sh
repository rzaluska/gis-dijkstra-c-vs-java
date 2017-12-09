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
for v in 10 100 1000 10000 100000 1000000; do
    max_edges=$(($v*$v/2))
    inc=$(($max_edges/6)) #6 steps increment of number of edeges
    for e in $(seq 10 $inc $max_edges); do
        for i in $(seq 100); do
            python graph-generator/graph-generator.py -v $v -e $e | ./c/dijkstra >> results_c.txt
            python graph-generator/graph-generator.py -v $v -e $e | java -cp ./java Dijkstra >> results_java.txt
        done
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

