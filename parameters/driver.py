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
    cov=np.array([[float(x) for x in l.split()] for l in L])
    self.cov=cov
    
  def load_mean_values(self):

    par={}
    par['BLNY']       = {'idx': 0,'val': 2.36166e-02,'pmin': 0,'pmax':None}
    par['Nu']         = {'idx': 1,'val': 2.61971e-01,'pmin':-1,'pmax':1}
    par['Nd']         = {'idx': 2,'val':-1.95220e-01,'pmin':-1,'pmax':1}
    par['au']         = {'idx': 3,'val': 1.69586e+00,'pmin': 0,'pmax':None}
    par['ad']         = {'idx': 4,'val': 3.20601e-01,'pmin': 0,'pmax':None}
    par['bu']         = {'idx': 5,'val': 1.46831e-06,'pmin': 0,'pmax':None}
    par['bd']         = {'idx': 6,'val': 3.61390e-03,'pmin': 0,'pmax':None}
    par['Nu_collins'] = {'idx': 7,'val': 8.54376e-01,'pmin':-1,'pmax':1}
    par['Nd_collins'] = {'idx': 8,'val':-9.99999e-01,'pmin':-1,'pmax':1}
    par['au_collins'] = {'idx': 9,'val': 6.88367e-01,'pmin': 0,'pmax':None}
    par['ad_collins'] = {'idx':10,'val': 1.79434e+00,'pmin': 0,'pmax':None}
    par['bu_collins'] = {'idx':11,'val': 4.81953e-02,'pmin': 0,'pmax':None}
    par['bd_collins'] = {'idx':12,'val': 6.99676e+00,'pmin': 0,'pmax':None}

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

  def gen_sample(self,npar=10000):
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
        normed=True
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
      ax.set_ylim(0,1)
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
  sam.plot_sample(sam.DF1,tex('sampler~with~cuts'),bins=10)
  sam.load_cpp_sample('data/new_parameters_aug26.dat')
  sam.plot_sample(sam.DFCPP,tex('cpp'))
  sam.savefig()




