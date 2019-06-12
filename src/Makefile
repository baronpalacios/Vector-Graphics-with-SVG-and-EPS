CC = gcc

all:		figures.o free.o test_figures.o svg.o eps.o fractals.o \
			test_fractals.o tree.o test_tree.o sxmlc.o sxmlsearch.o
		${CC} -o main main.c figures.o free.o test_figures.o svg.o eps.o \
		tree.o test_tree.o fractals.o test_fractals.o sxmlc.o sxmlsearch.o -l m
		mv main ..

figure.o:	figures.c 
		${CC} -c figures.c -l m

free.o:		free.c
		${CC} -c free.c

svg.o:		svg.c figures.o
		${CC} -c svg.c
           
eps.o:		eps.c figures.o
		${CC} -c eps.c
           
fractals.o:	fractals.c figures.o   
		${CC} -c fractals.c -l m
            
tree.o:		tree.c figures.o
		${CC} -c tree.c -l m

test_figures.o:	test_figures.c
		${CC} -c test_figures.c

test_tree.o:	test_tree.c
		${CC} -c test_tree.c

test_fractals.o:	test_fractals.c
		${CC} -c test_fractals.c

sxmlsearch.o:	sxmlsearch.c
		${CC} -c sxmlsearch.c

sxmlc.o:	sxmlc.h
		${CC} -c sxmlc.c


clean:
		rm -f *.o

