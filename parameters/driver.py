#!/usr/bin/env python
import sys,os
import matplotlib
import numpy as np
import matplotlib.pyplot as py
import pandas as pd
from scipy.stats import norm
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)  
tex = lambda x: r'$\mathrm{'+x+'}$'
from scipy.stats import kde

class SAMPLER(object):

  def __init__(self):

    self.load_cov_matrix()
    self.load_mean_values()
    self.prepare_plot()

  def load_cov_matrix(self):

    F=open('data/correlation_matrix.dat')
    L=F.readlines()
    F.close()
    L=[l.strip() for l in L]
    L=[l for l in L if l!='']
    rho=np.array([[float(x) for x in l.split()] for l in L])
    err=[]
    err.append(7.17002e-04) 
    err.append(2.46543e-02)
    err.append(7.15875e-03)
    err.append(7.59358e-03)
    err.append(4.01160e-02)
    err.append(5.38257e-01)
    err.append(7.93746e-01)
    err.append(8.65518e-02)
    err.append(1.25156e-01)
    err.append(4.33534e-02)
    err.append(3.17379e-01)
    err.append(3.88934e-02)
    err.append(2.64818e+00)
    err=np.array(err)

    self.cov=np.einsum('ij,i,j->ij',rho,err,err)

  def load_mean_values(self):

    par={}
    par['BLNY']       = {'range':None,'idx': 0,'val': 2.36166e-02,'pmin':None,'pmax':None}
    par['Nu']         = {'range':None,'idx': 1,'val': 2.61971e-01,'pmin':None,'pmax':None}
    par['Nd']         = {'range':None,'idx': 2,'val':-1.95220e-01,'pmin':None,'pmax':None}
    par['au']         = {'range':None,'idx': 3,'val': 1.69586e+00,'pmin':None,'pmax':None}
    par['ad']         = {'range':None,'idx': 4,'val': 3.20601e-01,'pmin':None,'pmax':None}
    par['bu']         = {'range':None,'idx': 5,'val': 1.46831e-06,'pmin':None,'pmax':None}
    par['bd']         = {'range':None,'idx': 6,'val': 3.61390e-03,'pmin':None,'pmax':None}
    par['Nu_collins'] = {'range':None,'idx': 7,'val': 8.54376e-01,'pmin':None,'pmax':None}
    par['Nd_collins'] = {'range':None,'idx': 8,'val':-9.99999e-01,'pmin':None,'pmax':None}
    par['au_collins'] = {'range':None,'idx': 9,'val': 6.88367e-01,'pmin':None,'pmax':None}
    par['ad_collins'] = {'range':None,'idx':10,'val': 1.79434e+00,'pmin':None,'pmax':None}
    par['bu_collins'] = {'range':None,'idx':11,'val': 4.81953e-02,'pmin':None,'pmax':None}
    par['bd_collins'] = {'range':None,'idx':12,'val': 6.99676e+00,'pmin':None,'pmax':None}

    par['BLNY'].update({'pmin': 0,'pmax':None})
    par['Nu'].update({'pmin':-1,'pmax':1})
    par['Nd'].update({'pmin':-1,'pmax':1})
    par['au'].update({'pmin': 0,'pmax':None})
    par['ad'].update({'pmin': 0,'pmax':None})
    par['bu'].update({'pmin': 0,'pmax':None})
    par['bd'].update({'pmin': 0,'pmax':None})
    par['Nu_collins'].update({'pmin':-1,'pmax':1})
    par['Nd_collins'].update({'pmin':-1,'pmax':1})
    par['au_collins'].update({'pmin': 0,'pmax':None})
    par['ad_collins'].update({'pmin': 0,'pmax':None})
    par['bu_collins'].update({'pmin': 0,'pmax':None})
    par['bd_collins'].update({'pmin': 0,'pmax':None})

    keys=par.keys()
    ordered_keys = range(len(keys))
    for k in keys:
      i=par[k]['idx']
      ordered_keys[i]=k

    self.mean=np.array([par[k]['val'] for k in ordered_keys]) 
    self.par=par
    self.ordered_keys=ordered_keys

  def apply_cuts(self,DF):
    DF_=DF
    par=self.par
    for k in par.keys():
      pmin=par[k]['pmin']
      pmax=par[k]['pmax']
      if pmin!=None: DF_=DF_[DF_[k]>pmin]
      if pmax!=None: DF_=DF_[DF_[k]<pmax]
    return DF_

  def gen_sample(self,npar=100000):
    mean=self.mean
    cov=self.cov
    sample=np.random.multivariate_normal(mean,cov,npar)
    self.DF0=pd.DataFrame(sample,columns=self.ordered_keys) 
    self.DF1=self.apply_cuts(self.DF0)
    
  def prepare_plot(self):
    par=self.par
    ncols=4
    nrows=4
    py.figure(figsize=(ncols*2.5,nrows*2))
    cnt=0
    AX={}
    for k in self.ordered_keys:
      cnt+=1
      AX[k]=py.subplot(nrows,ncols,cnt)
    self.AX=AX

  def plot_sample(self,DF,label,bins=100):
    par=self.par
    AX=self.AX
    flag=False
    for k in par.keys():
      if flag==False: 
        label_=label
        flag=True
      else: 
        label_=True

      AX[k].hist(\
        DF[k].values,\
        bins=bins,\
        histtype='step',\
        label=label,\
        normed=True,\
        range=par[k]['range']
        ) 

  def savefig(self):
    # cosmetics
    par=self.par
    AX=self.AX
    flag=False
    for k in par.keys():
      ax=AX[k]
      ax.locator_params(axis = 'y', nbins=5)
      ax.locator_params(axis = 'x', nbins=5)
      #ax.text(0.01,0.8,tex(k.replace('_','~')),transform=ax.transAxes)
      ax.set_xlabel(tex(k.replace('_','~')))
      #ax.set_ylim(0,1)
      ax.axvline(par[k]['val'],color='k',ls='--',alpha=0.5,label=tex('mean'))
      if k=='bd_collins': axl=ax

    axl.legend(frameon=0,bbox_to_anchor=(2.3,1.0))

    py.tight_layout()
    py.savefig('gallery/params_hist.pdf')

  def load_cpp_sample(self,fname):
    F=open(fname,'r')
    L=F.readlines()
    F.close()
    L=np.array([[float(x) for x in l.split()] for l in L])
    self.DFCPP=pd.DataFrame(L,columns=self.ordered_keys) 

if __name__=='__main__':
  sam=SAMPLER()
  sam.gen_sample()
  sam.plot_sample(sam.DF0,tex('sampler'))
  sam.plot_sample(sam.DF1,tex('sampler~with~cuts'))
  sam.load_cpp_sample('data/new_parameters_aug26.dat')
  sam.plot_sample(sam.DFCPP,tex('cpp'))
  sam.savefig()




