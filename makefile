CC = gcc
AR = ar
CFLAGS = -Wall -g
OBJS = main.o func.o
LIBS = graph.h
MAIN = main.c
FUNC = func.c
OUT = graph

main.o: $(MAIN) $(LIBS)
	$(CC) $(CFLAGS) -c $(MAIN)

func.o: $(FUNC) $(LIBS)
	$(CC) $(CFLAGS) -c $(FUNC)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

clean:
	rm -f $(OBJS) $(OUT)

.PHONY: clean all
