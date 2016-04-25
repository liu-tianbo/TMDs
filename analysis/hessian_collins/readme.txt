The data structure of these files are:

For each line:
  #1 --> Name of the parameter that has an offset, 
         where "FIT" means the one with the best fit values of all paramters
         "BLNY" means that there is a offset for the "BNLY" parameter
  #2 --> from 1 to 20, means 20 different offset values of the particular parmeter

  #3 --> ChiSQ, the total ChiSQ value of all data bins in one experimental setting (e.g, solid: he3(e,e'pi+)X), 
         compared with the best fit values (w/ random offsets) 
  #4 ~ # 16 --> The exact values of all 13 parameters that correspond to this ChiSQ

In general, it looks like:
#par  #id  #chisq  #BNLY  #Nu  #Nd  #au  #ad  #bu  #bd  #Nu_t  #Nd_t  #au_t  #ad_t  #bu_t  #bd_t 
