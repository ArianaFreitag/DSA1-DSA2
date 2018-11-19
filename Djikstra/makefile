djikstra.exe: djikstra.o graph.o heap.o hash.o
	g++ -o djikstra.exe djikstra.o graph.o heap.o hash.o

djikstra.o: djikstra.cpp
	g++ -c djikstra.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
