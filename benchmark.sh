#!/bin/bash

# compile c
cd c
make -B
cd ..

# compile java
cd java
javac *.java
cd ..

echo '"v","e","s","t"' > results_c.txt
echo '"v","e","s","t"' > results_java.txt

for graph_file in graphs/*.txt; do
    for i in $(seq 50); do
        cat $graph_file | ./c/dijkstra >> results_c.txt
        cat $graph_file | java -Xmx8G -cp ./java Dijkstra >> results_java.txt
    done
done
