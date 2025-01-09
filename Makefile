LIBS=-lpng -ljpeg
all:
	gcc main.c rendered/dialogue.c rendered/main.c -O2 -Wall $(LIBS) -o tfiles 

