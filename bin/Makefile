all: matriz.o jacobi.o main.o
	@g++ matriz.o jacobi.o main.o -g -O3 -o t1-concorrentes -lpthread

matriz.o:
	@g++ -c -g -O3 matriz.cpp

main.o:
	@g++ -c -g -O3 main.cpp

jacobi.o:	
	@g++ -c -g -O3 jacobi.cpp -lpthread

normal:
	@./t1-concorrentes normal

thread:
	@./t1-concorrentes thread

tests:
	@./tests.sh

zip:
	@zip -r t1-concorrentes.zip Makefile *.cpp *.h

clean:
	@rm *.o t1-concorrentes
