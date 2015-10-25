OS := $(shell uname)
#on Linux it gives Linux
ifeq ($(OS),Linux)
FC = gfortran
else
# Change your fortran compiler here
FC = gfortran-mp-4.8
#FC = gfortran
endif

FFLAGS = -g

OBJECTS = corset.o corgen.o rnorml.o ranmar.o

toy.run: toy.o $(OBJECTS)
	$(FC) $(FFLAGS) -o $@ $+

clean:
	rm *.o; rm toy.run
