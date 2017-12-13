all: dijkstra debug-dijkstra prof-dijkstra

FLAGS=-Wall -Wextra -Wshadow

prof-dijkstra: main.c graph.c queue.c dijkstra.c timer.c
	gcc ${FLAGS} -no-pie -g -pg -o $@ $^

dijkstra: main.c graph.c queue.c dijkstra.c timer.c
	gcc ${FLAGS} -O3 -o $@ $^

debug-dijkstra: main.c graph.c queue.c dijkstra.c timer.c
	gcc -DDEBUG ${FLAGS} -o $@ $^ -g
