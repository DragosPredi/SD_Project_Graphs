build: 
	gcc problema1.c graph.c list.c queue.c -g -Wall -o movies
	gcc problema2.c graph.c list.c queue.c -g -Wall -o labirint

run:
	./a.out

clean: 
	rm movies
