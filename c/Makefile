all: dijkstra debug-dijkstra

FLAGS=-Wall -Wextra -Wshadow

dijkstra: main.c graph.c queue.c dijkstra.c timer.c
	gcc ${FLAGS} -O2 -o $@ $^

debug-dijkstra: main.c graph.c queue.c dijkstra.c timer.c
	gcc -DDEBUG ${FLAGS} -o $@ $^ -g
