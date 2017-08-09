OBJECT=./BigInt/BigInt.o
main:$(OBJECT) main.o handlehttp.o socketop.o
	g++ -o main main.o handlehttp.o socketop.o $(OBJECT) -g -lpthread

main.o:main.cpp handlehttp.h socketop.h
	g++ -o main.o -c main.cpp -g
handlehttp.o:handlehttp.h handlehttp.cpp calc.h mystring.h
	g++ -o handlehttp.o -c handlehttp.cpp -g
socketop.o: socketop.cpp socketop.h
	g++ -o socketop.o -c socketop.cpp -g 

clean:
	rm *.o
