start: regions.o main.o
	clang -o regions regions.o main.o

regions.o: regions.c
	clang -c regions.c -o regions.o

main.o: test.c
	clang -c test.c -o main.o

clean:
	rm -rf regions.o
	rm -rf main.o
  
