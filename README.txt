#################################
## Colllins Prediction Study
##, -- by Alexei Prokudin, Kalyan Allada, Nobuo Sato, and Zhihong Ye
#################################

------------------------------------------------------------------
1. "./collins/":
  Generate psudo-data of transversity distribution and tensor charge based on the projection results of SoLID-3he, SoLID-proton and CLAS12-proton

  (1) The projection data are stored in ./data/
      The collins parameter set based on Alexei's fit is stored in ./error_estimate
      
  (2) How to run the code: 
    1), Compile collins.cxx, by typing "make"
    2), Run the code to generate a set of unpolarized cross sections for an experimental setting, by typing:
            ./collins.exe -SOLID -NEUTRON -PI+ -UNPOL 0
       (other options:    -CLAS  -PROTON  -PI- )
        It will generate a file like, solid_unpolarised_3he_pip.dat. You only run once for each setting
    3), Run the code to generate replica events based on the order of parameters in the parameter file:
           ./collins.exe -SOLID -NEUTRON -PI+ -DATA N, where N=0,1,2 ...
      (other options:    -CLAS  -PROTON  -PI- )

  (3), Use the scripts to submit massive jobs to the batch-farm:
      1), The script "gofarm_all" can submit an individual job with "jsub" or "swif" method
      2), The script "LongRun_ALL" helps you to submit many jobs

------------------------------------------------------------------
2, "./get_psudo/":
   Get the best-fit psudo-data. For each setting, the N=0 replica is the best-fit data which uses the central values of the fitting paramters.
   We assume it is very close to the experimental results which should be allowed to have some statistical fluctuation. 

   "Get_Psudo.C" will take the best-fit replica and smear the results with a random number to simualte the statistical fluctuation. The results
   is saved for the futher analysis.

------------------------------------------------------------------
3, "./get_weight": 
   Read all replica and compute the weight of each replica:
   The code "Get_Weight.C" reads in three files for each replica and computes the weights. The results are saved into root-files and a text-file.

   If we have to scale-up the experimetal statistcal errors (projected), this code will ask for a scale factor and saves the new results in different files

------------------------------------------------------------------
4, "./make_plot/": 
   Analysis the results and make some plots. 
  (1) "Get_Data.C": Read in the results of each setting for different scale factors.  Use the weight to compute new tensor-charges and new errors, 
      as well as the transveristy values and errors in each x-bin. Save the final results in two text files.
   
      "Get_AllData.C": Read in results of all settings for one experiment and then do the same things 
 
  (2) "Tensor.C": Do a fit of the improved ratio (Err_New/Err_Old) as a function of scale factors. Extrapolate the ratio at scale=1 which gives the "actual" improvement.

  (3) "Trans.C": Do the same things but on each x-bin of the transveristy distribution.

  (4) "tensor_solid.C": Plot the tensor-chages.

  (5) To-Do: Get the transversity plot.
