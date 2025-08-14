LIBS=-lpng -ljpeg
ARCH=-march=native
EXTRA=-Wstrict-prototypes
#for openBSD
#INCLUDE="-I/usr/local/include"
#LDCONFIG="-L/usr/local/lib"
all:
	$(CC) main.c rendered/dialogue.c vector/main.c rendered/config_file/config.c rendered/main.c $(ARCH) $(EXTRA) -O2 -pedantic -Wall $(LIBS) -o tfiles 
	 

clean:
	rm ./tfiles

install:
	cp ./tfiles /usr/bin

