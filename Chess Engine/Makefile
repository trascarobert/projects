CC = g++
CFLAGS = -g -Wall
SOURCES = main


build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(SOURCES) $(SOURCES).cpp

clean:
	rm -f $(SOURCES)

run: build
	./$(SOURCES)


xboard:
	xboard -fcp "make run" -debug