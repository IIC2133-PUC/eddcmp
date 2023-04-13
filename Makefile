# Compiler
CC=gcc

# Compiler flags
CFLAGS=-Wunused -Wall -O3

PROGRAM=eddcmp
SRCDIR=src/${PROGRAM}
TARGETDIR=bin
CFILES=$(wildcard ${SRCDIR}/*.c)
all:
	@mkdir -p ${TARGETDIR}
	${CC} ${CFLAGS} ${CFILES} -o ${TARGETDIR}/${PROGRAM}
	@echo "Done!"

clean:
	@rm -rf ${TARGETDIR}
	@echo "Cleaned!"

install: all
	@cp ${TARGETDIR}/${PROGRAM} /usr/local/bin/${PROGRAM}
	@echo "Installed!"




