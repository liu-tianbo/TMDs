How to run this code:
 1) Make sure you install GSL and HOPPET or link to my work directory /work/halla/solid/yez/TMDs. 
    I included the pre-compile one but they may not run in your computer. You may want to download the packages and compile them locally.
    I am using gsl-1.16 and hoppet-1.1.5, but I think newer versions should work.
 
 2) The package requires FORTRAN compiler. I am using GFORTRAN
 
 3) Run the code as following:
 
     ./GetCollins.exe -SOLID   -PROTON   -PI+  Comment1  Comment2  Segments SegmentID  par1 par2 par3 .... par13
   or                 -CLAS12  -NEUTRON  -PI- 

   where Comment1/2 just two comments reserved for you to distinguish each parameter sets,
         Segments mean how many segments (N) you want to divide the projected data into,
         SegmentID mean which segment from the total segments you want to use for this calculation (0, ..., N-1) 

 4) After finishing the run, it will return the ChiSQ value and also the results will be saved into a data file. The LAST number in the LAST line is the total ChiSQ of all bins.

  --- Zhihong Ye, 06/26/2016
