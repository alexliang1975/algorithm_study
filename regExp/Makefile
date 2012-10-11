CC=g++
CFLAGS=-I/usr/local/include -L/usr/local/lib -lgtest -lpthread

EXEC=regExp

DEPS = $(wildcard *.h)
SRC = $(notdir $(wildcard *.cpp ))
OBJS=$(patsubst %.cpp,%.o,$(SRC))

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(EXEC)
