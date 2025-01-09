LIBS=-lpng -ljpeg
all:
	gcc main.c rendered/dialogue.c rendered/main.c -O2 -pedantic -Wall $(LIBS) -o tfiles 

