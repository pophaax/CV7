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

SOURCES_WIND = Windsensor.cpp
HEADERS_WIND = Windsensor.h
FILE_WIND = Windsensor.o

SOURCES_MOCK = MockWindsensor.cpp
HEADERS_MOCK = MockWindsensor.h
FILE_MOCK = MockWindsensor.o

SOURCES_CV7 = CV7.cpp
HEADERS_CV7 = CV7.h
FILE_CV7 = CV7.o

SOURCES_UTIL = UtilityLibrary.cpp
HEADERS_UTIL = UtilityLibrary.h
FILE_UTIL = UtilityLibrary.o

FILE_LOGGER = ../logger/Logger.o

SOURCES = $(SOURCES_WIND) $(SOURCES_CV7) $(SOURCES_MOCK) $(SOURCES_UTIL) 
HEADERS = $(HEADERS_WIND) $(HEADERS_CV7) $(HEADERS_MOCK) $(HEADERS_UTIL) 
FILES = $(FILE_WIND) $(FILE_CV7) $(FILE_MOCK) $(FILE_UTIL)

all : $(FILES) 

$(FILE_CV7) : $(SOURCES_CV7) $(HEADERS_CV7)
	$(CC) $(SOURCES_CV7) $(FLAGS) $(LIBS) -c -o $(FILE_CV7)

$(FILE_UTIL) : $(SOURCES_UTIL) $(HEADERS_UTIL)
	$(CC) $(SOURCES_UTIL) $(FLAGS) $(LIBS) -c -o $(FILE_UTIL)

$(FILE_WIND) : $(SOURCES_WIND) $(HEADERS_WIND)
	$(CC) $(SOURCES_WIND) $(FLAGS) $(LIBS) -c -o $(FILE_WIND)

$(FILE_MOCK) : $(SOURCES_MOCK) $(HEADERS_MOCK)
	$(CC) $(SOURCES_MOCK) $(FLAGS) $(LIBS) -c -o $(FILE_MOCK)
			
example : $(SOURCES) $(HEADERS) $(FILES) example.cpp
	$(CC) $(SOURCES) example.cpp $(FLAGS) $(LIBS) $(FILE_LOGGER) -o example
	
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

