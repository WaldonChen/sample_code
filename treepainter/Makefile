CC := g++
CFLAGS := -O3

LIB_BTREEPAINTER := libbtreepainter.so

all: main.cpp $(LIB_BTREEPAINTER)
	$(CC) $(CFLAGS) main.cpp -lbtreepainter -L./ -o main

single: main.cpp bpainttree.cpp canvas.cpp
	$(CC) $(CFLAGS) main.cpp bpainttree.cpp canvas.cpp -o main

$(LIB_BTREEPAINTER): bpainttree.cpp canvas.cpp
	$(CC) $(CFLAGS) -shared bpainttree.cpp canvas.cpp -o $(LIB_BTREEPAINTER)

clean:
	-rm *.o $(LIB_BTREEPAINTER) main
