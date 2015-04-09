#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    windsensor
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror -std=c++14
LIBS = -lpthread -lwiringPi -lrt

SOURCES_CV7 = CV7.cpp
HEADERS_CV7 = CV7.h
FILE_CV7 = CV7.o

SOURCES_UTIL = UtilityLibrary.cpp
HEADERS_UTIL = UtilityLibrary.h
FILE_UTIL = UtilityLibrary.o

SOURCES = $(SOURCES_CV7) $(SOURCES_UTIL)
HEADERS = $(HEADERS_CV7) $(HEADERS_UTIL)
FILES = $(FILE_CV7) $(FILE_UTIL)

all : $(FILE_CV7) $(FILE_UTIL)

$(FILE_CV7) : $(SOURCES_CV7) $(HEADERS_CV7)
	$(CC) $(SOURCES_CV7) $(FLAGS) $(LIBS) -c -o $(FILE_CV7)
	
$(FILE_UTIL) : $(SOURCES_UTIL) $(HEADERS_UTIL)
	$(CC) $(SOURCES_UTIL) $(FLAGS) $(LIBS) -c -o $(FILE_UTIL)

example : $(SOURCES) $(HEADERS) example.cpp
	$(CC) $(SOURCES) example.cpp $(FLAGS) $(LIBS) -o example
	
test : $(SOURCES) $(HEADERS) ../catch.hpp testCV7.cpp
	$(CC) $(SOURCES) testCV7.cpp $(LIBS) -o test 

metatest : $(SOURCES) $(HEADERS) ../catch.hpp testCV7.cpp
	$(CC) $(SOURCES) testCV7.cpp -fprofile-arcs -ftest-coverage $(LIBS) -o metatest 

clean :
	rm -f $(FILES)
	rm -f example
	rm -f test
	rm -f metatest
	rm -f *.gcda
	rm -f *.gcno

metalog :
	make metatest
	./metatest
	gcov -r CV7.cpp
	grep -wE "(#####)" CV7.cpp.gcov > metatestlog.txt
	rm -f *.gcov
	make clean
	sed -i '1s/^/Codelines below not tested by test*.cpp\n/' metatestlog.txt

