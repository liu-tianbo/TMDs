#!/usr/bin/env python
import sys,os
import numpy as np
from numpy.random import uniform
##################################################################

par={}
scale=1.0/5.0
par['BLNY']= {'val': 2.36166e-02,'err':7.17002e-04*scale}
par['Nu_c']= {'val': 2.61971e-01,'err':2.46543e-02*scale}
par['Nd_c']= {'val':-1.95220e-01,'err':7.15875e-03*scale}
par['au_c']= {'val': 1.69586e+00,'err':7.59358e-03*scale}
par['ad_c']= {'val': 3.20601e-01,'err':4.01160e-02*scale}
par['bu_c']= {'val': 1.46831e-06,'err':5.38257e-01*scale}  #
par['bd_c']= {'val': 3.61390e-03,'err':7.93746e-01*scale}  #
par['Nu_T']= {'val': 8.54376e-01,'err':8.65518e-02*scale}
par['Nd_T']= {'val':-9.99999e-01,'err':1.25156e-01*scale}
par['au_T']= {'val': 6.88367e-01,'err':4.33534e-02*scale}
par['ad_T']= {'val': 1.79434e+00,'err':3.17379e-01*scale}
par['bu_T']= {'val': 4.81953e-02,'err':3.88934e-02*scale}
par['bd_T']= {'val': 6.99676e+00,'err':2.64818e+00*scale}


fname='params-flat-s5.dat'
size=100000
sample=np.zeros((13,size))
sample[0]  = uniform(par['BLNY']['val']-par['BLNY']['err'],par['BLNY']['val']+par['BLNY']['err'],size)   
sample[1]  = uniform(par['Nu_c']['val']-par['Nu_c']['err'],par['Nu_c']['val']+par['Nu_c']['err'],size)
sample[2]  = uniform(par['Nd_c']['val']-par['Nd_c']['err'],par['Nd_c']['val']+par['Nd_c']['err'],size)
sample[3]  = uniform(par['au_c']['val']-par['au_c']['err'],par['au_c']['val']+par['au_c']['err'],size)
sample[4]  = uniform(par['ad_c']['val']-par['ad_c']['err'],par['ad_c']['val']+par['ad_c']['err'],size)
sample[5]  = uniform(par['bu_c']['val'],par['bu_c']['val'],size)
sample[6]  = uniform(par['bd_c']['val'],par['bd_c']['val'],size)
sample[7]  = uniform(par['Nu_T']['val']-par['Nu_T']['err'],par['Nu_T']['val']+par['Nu_T']['err'],size)
sample[8]  = uniform(par['Nd_T']['val']-par['Nd_T']['err'],par['Nd_T']['val']+par['Nd_T']['err'],size)
sample[9]  = uniform(par['au_T']['val']-par['au_T']['err'],par['au_T']['val']+par['au_T']['err'],size)
sample[10] = uniform(par['ad_T']['val']-par['ad_T']['err'],par['ad_T']['val']+par['ad_T']['err'],size)
sample[11] = uniform(par['bu_T']['val']-par['bu_T']['err'],par['bu_T']['val']+par['bu_T']['err'],size)
sample[12] = uniform(par['bd_T']['val']-par['bd_T']['err'],par['bd_T']['val']+par['bd_T']['err'],size)
sample=np.transpose(sample)
np.savetxt('data/%s'%fname,sample,delimiter=' ',fmt='%0.10e')







