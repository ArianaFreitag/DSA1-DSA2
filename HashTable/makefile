spell.exe: spellCheck.o hash.o
	g++ -o spell.exe spellCheck.o hash.o

spellcheck.o: spellCheck.cpp hash.h
	g++ -c spellcheck.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o spellDebug.exe spellCheck.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
