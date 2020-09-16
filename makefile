.PHONY: dirs clean

all : dirs ut_main

ut_main: 

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
