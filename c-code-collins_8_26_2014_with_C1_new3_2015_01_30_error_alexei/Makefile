OS := $(shell uname)
#on Linux it gives Linux
ifeq ($(OS),Linux)
CPP = g++
FF = gfortran
else # Mac
CPP = g++-mp-4.8
FF = gfortran-mp-4.8
endif

# Root is the same for both systems... MathMore is needed!
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs) -lMinuit -lMathMore
ROOTGLIBS := $(shell root-config --glibs)

LDFLAGS = -O
CFLAGS += $(ROOTCFLAGS)

ifeq ($(OS),Linux)
HOPPET_DIR = /work/halla/solid/yez/TMDs/hoppet-1.1.5/
GSL_DIR = /work/halla/solid/yez/TMDs/gsl-1.16/
else # Mac
HOPPET_DIR = /Users/alexei/Dropbox/cpp/hoppet-1.1.5/
GSL_DIR = /Users/alexei/ScienceSoftware/gsl-1.16/
endif

ifeq ($(OS),Linux)
#Hoppet does evolution of transversity, unpolarised and helicity 
HOPPETLIB =  -L$(HOPPET_DIR)src  -lhoppet_v1 
#gsl
GSL_LIB = -L$(GSL_DIR)/lib/ -lgsl  -lgslcblas
else # Mac
#Hoppet does evolution of transversity, unpolarised and helicity 
HOPPETLIB =  -L$(HOPPET_DIR)src  -lhoppet_v1 
#gsl1_9 IS GSL NEEDED FOR FITTING?
GSL_LIB = -L$(GSL_DIR)/.libs -lgsl  -L$(GSL_DIR)/cblas/.libs  -lgslcblas
endif


#in order for gfortran to work I need to include this
FLIBS =   -lgfortran


#USAGE OF OPENMP:
CFLAGS += -pthread

# I use OPENMP!!! -fopenmp 
ifeq ($(OS),Linux)
OPT = -c -O3 -Wall -fopenmp -I./  \
	-I/usr/local/lib/ -I$(HOPPET_DIR)src -I$(HOPPET_DIR)include
	
#OPT = -c -O3 -Wall -fopenmp -I./ -I$(LHAPDFINCLUDE) -I$(LHAPDFINCLUDE)/LHAPDF \
#	-I/usr/local/include/ -I/usr/local/lib/ 
else # Mac
# Try with a new HOPPET:	
OPT = -c -O3 -arch x86_64 -m64 -Wall -fopenmp -I./  -I$(GSL_DIR) \
	-I$(HOPPET_DIR)src
endif

all: collins.exe
collins.exe: collins.o CT10Pdf.o fDSS.o DSSV-2008.o
	$(CPP) -fopenmp $(CFLAGS) -o collins.exe collins.o CT10Pdf.o fDSS.o DSSV-2008.o $(ROOTLIBS) $(HOPPETLIB) $(GSL_LIB) $(FLIBS)



collins.o: collins.cxx
	$(CPP) $(OPT) $(CFLAGS) -c collins.cxx

fDSS.o: fDSS.f
	$(FF) -c fDSS.f -lgfortran

DSSV-2008.o: DSSV-2008.f
	$(FF) -c DSSV-2008.f -lgfortran


CT10Pdf.o: CT10Pdf.f
	$(FF) -c CT10Pdf.f

clean:
	rm *.o;





