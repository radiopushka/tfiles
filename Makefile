LIBS=-lpng -ljpeg
all:
	$(CC) main.c rendered/dialogue.c vector/main.c rendered/main.c -O2 -pedantic -Wall $(LIBS) -o tfiles 


