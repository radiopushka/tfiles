LIBS=-lpng -ljpeg
ARCH=-march=native
EXTRA=
all:
	$(CC) main.c rendered/dialogue.c vector/main.c rendered/main.c $(ARCH) $(EXTRA) -O2 -pedantic -Wall $(LIBS) -o tfiles 


