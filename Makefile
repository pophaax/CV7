#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    windsensor
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror -std=c++14 -DBOOST_LOG_DYN_LINK
LIBS = -lpthread -lwiringPi -lrt -lboost_system -lboost_log -lboost_thread

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
	$(CC) $(SOURCES) testCV7.cpp $(FLAGS) $(LIBS) -o test 

metatest : $(SOURCES) $(HEADERS) ../catch.hpp testCV7.cpp
	$(CC) $(SOURCES) testCV7.cpp -fprofile-arcs -ftest-coverage $(FLAGS) $(LIBS) -o metatest 

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
	gcov -r CV7.cpp >> metatestlog.txt
	
	rm -f *.gcov
	make clean
	sed -i '1s/^/Codelines below not tested by test*.cpp\n/' metatestlog.txt

