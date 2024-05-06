# Copyright (C) Paul Tröster - All Rights Reserved

.SUFFIXES:
.PHONY: clean compile checkstyle test
.PRECIOUS: %.o

CXX = clang++

all: clean compile checkstyle test

compile: SnakeMain SnakeTest

checkstyle:
	clang-format-14 --dry-run -Werror *.cpp

test:
	./SnakeTest

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o
	rm -f a.out

%.o: %.cpp $(HEADERS)
	$(CXX) -c $< -o $@

SnakeMain: SnakeMain.o Snake.o
	$(CXX) -o $@ $^ -lncurses

SnakeTest: SnakeTest.o Snake.o
	$(CXX) -o $@ $^ -lncurses -lgtest -lgtest_main
