CC = clang
CFLAGS = -c -Wall -Wextra -O0
AFLAGS = -c -S -Wall -Wextra -fno-verbose-asm
LFLAGS = -Wall -Wextra

all: readmymind readmymindextension
clean:
	rm -f readmymind readmymind.o readmymindextension

readmymind: readmymind.o
	${CC} ${LFLAGS} readmymind.o -o readmymind

readmymind.o: readmymind.c
	${CC} ${CFLAGS} readmymind.c -o readmymind.o

readmymindextension: readmymindextension.o
	${CC} ${LFLAGS} readmymindextension.o -o readmymindextension

readmymindextension.o: readmymindextension.c
	${CC} ${CFLAGS} readmymindextension.c -o readmymindextension.o

