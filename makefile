.PHONY: dirs clean

SRC = src/rectangle.h src/triangle.h src/ellipse.h src/two_dimensional_coordinate.h src/sort.h src/terminal.h src/compound_shape.h

TEST = test/ut_rectangle.h test/ut_triangle.h test/ut_ellipse.h test/ut_sort.h test/ut_terminal.h test/ut_compound_shape.h test/ut_iterator.h \
		test/ut_visitor.h

all : dirs ut_main #geo

ut_main: test/ut_main.cpp $(SRC) $(TEST) shape_obj
	g++ -std=c++11 -Wfatal-errors -Wall -g test/ut_main.cpp obj/shape.o -o bin/ut_main -lgtest -lpthread

shape_obj: src/shape.cpp
	g++ -std=c++11 -Wfatal-errors -Wall -c -g src/shape.cpp -o obj/shape.o

# geo: src/main.cpp $(SRC)
# 	g++ -std=c++11 -Wfatal-errors -Wall -g src/main.cpp src/shape.cpp -o bin/geo

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*
