all: dijkstra debug-dijkstra

dijkstra: main.c graph.c queue.c dijkstra.c
	gcc -o $@ $^ -O3

debug-dijkstra: main.c graph.c queue.c dijkstra.c
	gcc -o $@ $^ -g
