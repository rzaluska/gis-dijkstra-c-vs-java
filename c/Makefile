all: dijkstra debug-dijkstra

FLAGS=-Wall -Wextra -Wshadow

dijkstra: main.c graph.c queue.c dijkstra.c timer.c
	gcc ${FLAGS} -o $@ $^ -O3

debug-dijkstra: main.c graph.c queue.c dijkstra.c timer.c
	gcc ${FLAGS} -o $@ $^ -g
