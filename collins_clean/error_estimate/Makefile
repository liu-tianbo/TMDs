# this allows for multy platform usage:
OS := $(shell uname)
#on Linux it gives Linux
ifeq ($(OS),Linux)
CPP = g++
FF = gfortran
else # Mac, update with your compilers
CPP = g++-mp-4.8
FF = gfortran-mp-4.8
#CPP = g++
#FF = gfortran
endif


# Options for LINUX and MAC
ifeq ($(OS),Linux)
# Peng:
#OPT = -c -O3 -m64 -Wall -I./
#Alexei:
OPT = -c -O3 -Wall -I./
#OPT = -c -O3 -Wall -fopenmp -I./   \
#	-I/usr/local/lib/ 
else # Mac	
OPT = -c -O3 -arch x86_64 -m64 -Wall -fopenmp -I./  
endif

#My library
MYLIB =  -L./  -lFORTRANLIB
#In order for gfortran to work I need to include this
FLIBS =   -lgfortran

# Exe file is done here
fit_sets.exe: fit_sets.o
	$(CPP)  -o fit_sets.exe fit_sets.o $(OBJECTS_UNIVERSAL) $(MYLIB) $(FLIBS)  

#Object file is done here	
fit_sets.o:	fit_sets.cpp 
	$(CPP) $(OPT)   -o $@ fit_sets.cpp
	@echo "..................done FIT SETS."
	
# Here we will create a library out of all object files I do not
# want to change.
OBJALL = ./fortran/corset.o ./fortran/corgen.o ./fortran/rnorml.o ./fortran/ranmar.o

#Type make all in order to make all objects and exe
all:
	cd ./fortran && make clean
	cd ./fortran && make
	rm libFORTRANLIB.a ; ar rvs libFORTRANLIB.a $(OBJALL) ;
	make fit_sets.exe;

#Type make all_lib in order to create the library
all_lib:
	cd ./fortran && make clean
	cd ./fortran && make
	rm libFORTRANLIB.a ; ar rvs libFORTRANLIB.a $(OBJALL) ;

#Type make clean in order to clean up the directory
clean:
	rm libFORTRANLIB.a;
	rm *.o;
	rm *.exe
