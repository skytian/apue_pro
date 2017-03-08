all: algo_sort.o 
	gcc -o  sort algo_sort.o sort_main.c
	rm *.o -f

algo_sort.o: algo_sort.h
	gcc -c  algo_sort.c
