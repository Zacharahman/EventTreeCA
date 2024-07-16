# Define paths
CLAPACK_ROOTPATH = ./CLAPACK
CLAPACK_F2CDIR  = $(CLAPACK_ROOTPATH)/F2CLIBS
INCLUDE = -I./local_sphinx/include/ -I$(CLAPACK_ROOTPATH)/SRC -I$(CLAPACK_ROOTPATH)
LIBDIR  = -L./local_sphinx/lib

# Compiler and flags
COMPILERFLAGS = -Wall -O3
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lfftw3 $(CLAPACK_ROOTPATH)/lapack_LINUX.a $(CLAPACK_ROOTPATH)/blas_LINUX.a $(CLAPACK_F2CDIR)/libF77.a $(CLAPACK_F2CDIR)/libI77.a -lm

# Targets and dependencies
ptree_test: ptree_test.o al_datahandling.o d_llists.o inputhandling.o matrices.o ptreehandling.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $^ $(LIBRARIES)

ptree_test.o: ptree_test.c al_datahandling.h d_llists.h inputhandling.h matrices.h ptreehandling.h
	$(CC) $(CFLAGS) -c ptree_test.c

al_datahandling.o: al_datahandling.c al_datahandling.h
	$(CC) $(CFLAGS) -c al_datahandling.c

d_llists.o: d_llists.c d_llists.h
	$(CC) $(CFLAGS) -c d_llists.c

inputhandling.o: inputhandling.c inputhandling.h
	$(CC) $(CFLAGS) -c inputhandling.c

matrices.o: matrices.c matrices.h
	$(CC) $(CFLAGS) -c matrices.c

ptreehandling.o: ptreehandling.c ptreehandling.h
	$(CC) $(CFLAGS) -c ptreehandling.c

# Clean up object files and executable
clean:
	rm -f *.o ptree_test

