tagrun: extractor.o
	g++ bin/extractor.o -o run -std=c++2a
 
extractor.o: src/extractor.cpp #src/extractor.h
	g++ -c src/extractor.cpp -o bin/extractor.o


# driver.o: src/driver.cpp
# 	g++ -c src/driver.cpp -o bin/driver.o
   
test: 
	./run temp.pgm -t 1 2 3 4 -s 50 60 -w none test.txt

clean:
	@rm -f bin/*.o
# @rm run
# @rm data/extractor.txt	