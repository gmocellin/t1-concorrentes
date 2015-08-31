all: matriz.o main.o
	@g++ matriz.o main.o -g -O3 -o t1-concorrentes

matriz.o:
	@g++ -c -g -O3 matriz.cpp

main.o:
	@g++ -c -g -O3 main.cpp

run:
	@./t1-concorrentes

zip:
	@zip -r t1-concorrentes.zip Makefile *.cpp *.h

clean:
	@rm *.o
