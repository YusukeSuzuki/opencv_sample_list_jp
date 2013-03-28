target = datamatrix.bin
objects = main.o

CXXFLAGS = -std=c++0x -Wall -Werror -g `pkg-config --cflags opencv`
LDFLAGS= -lstdc++ `pkg-config --libs opencv`

all: $(target)

$(target): $(objects)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

clean:
	-rm $(target)
	-rm $(objects)


