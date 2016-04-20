#!/usr/bin/env python
import sys,os
import numpy as np
from numpy.random import uniform
##################################################################

par={}
par['BLNY']= {'val': 2.36166e-02,'err':7.17002e-04}
par['Nu_c']= {'val': 2.61971e-01,'err':2.46543e-02}
par['Nd_c']= {'val':-1.95220e-01,'err':7.15875e-03}
par['au_c']= {'val': 1.69586e+00,'err':7.59358e-03}
par['ad_c']= {'val': 3.20601e-01,'err':4.01160e-02}
par['bu_c']= {'val': 1.46831e-06,'err':5.38257e-01}  
par['bd_c']= {'val': 3.61390e-03,'err':7.93746e-01}  
par['Nu_T']= {'val': 8.54376e-01,'err':8.65518e-02}
par['Nd_T']= {'val':-9.99999e-01,'err':1.25156e-01}
par['au_T']= {'val': 6.88367e-01,'err':4.33534e-02}
par['ad_T']= {'val': 1.79434e+00,'err':3.17379e-01}
par['bu_T']= {'val': 4.81953e-02,'err':3.88934e-02}
par['bd_T']= {'val': 6.99676e+00,'err':2.64818e+00}

order=[]
order.append('BLNY') 
order.append('Nu_c')
order.append('Nd_c')
order.append('au_c')
order.append('ad_c')
order.append('bu_c')
order.append('bd_c')
order.append('Nu_T')
order.append('Nd_T')
order.append('au_T')
order.append('ad_T')
order.append('bu_T')
order.append('bd_T')


def gen_pars(pname,scale,sign):
  if pname!=None:
    L='%7s'%pname
  else:
    L='%7s'%'----'

  for o in order:
    if pname!=o:
      L+='%15.5e'%par[o]['val']
    else:
      L+='%15.5e'%(par[pname]['val']+sign*scale*par[pname]['err'])
  return L


H='%7s'%''
for o in order:
  H+='%15s'%o
print H


print gen_pars(None,0,1)

for o in order:
  for i in range(10):
    print gen_pars(o,1/(2.0**i),1)
    print gen_pars(o,1/(2.0**i),-1)
      









  

 


 




















