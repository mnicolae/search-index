# Makefile for programs to index and search an index.

FLAGS= -Wall -g
SRC =  freq_list.c
OBJ =  freq_list.o

# make with no arguments will make sure that indexfile and query
# are up to date and build them if they are not. "make all" will
# also build both programs if they are not up to date.

all : indexfile query

# "make indexfile" will build the indexfile program if it is not
# already up to date.
indexfile : indexfile.o ${OBJ}
	gcc ${FLAGS} -o $@ indexfile.o ${OBJ}

query : query.o ${OBJ}
	gcc ${FLAGS} -o $@ query.o ${OBJ}

# Separately compile each C file
%.o : %.c freq_list.h
	gcc ${FLAGS} -c $<

# Update all dependencies.
depend : 
	makedepend ${SRC}

clean :
	-rm *.o indexfile query
