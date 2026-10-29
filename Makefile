.PHONY: all clean

var := $(patsubst %.c, %.o, $(wildcard *.c))
lib = -lm
all: converter.exe

converter.exe: $(var) $(lib)
	gcc -o $@ $^

clean:
	rm -f *.exe *.o
