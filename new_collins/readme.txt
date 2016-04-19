I have test this code on JLab Cento-OS Linux. Each run takes 10mins to 20mins depending on how many data bins. 

How to run this code:
 1) Make sure you install GSL and HOPPET. I included the pre-compile one but they may not run in your computer. You may want to download the packages and compile them locally.
    I am using gsl-1.16 and hoppet-1.1.5, but I think newer versions should work.
 2) The package requires FORTRAN compiler. I am using GFORTRAN
 3) Run the code as following:

     ./GetCollins.exe -SOLID   -PROTON   -PI+ par1 par2 par3 .... par13
   or                 -CLAS12  -NEUTRON  -PI- 
 4) It will return the ChiSQ value and also the results will be saved into a data file. The LAST number in the LAST line is the total ChiSQ of all bins.

  --- Zhihong Ye, 04/19/2016
