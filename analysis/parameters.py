#!/usr/bin/env python
import sys,os
import numpy as np
from numpy.random import uniform
from tools import save,load,checkdir
##########################################
import matplotlib.gridspec as gridspec
import matplotlib as mpl
#mpl.use('Agg')
import pylab as py
from  matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text',usetex=True)
##########################################

class HESS(object):

  def __init__(self):

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
    self.par=par
    
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
    self.order=order

  # routines to define parameters to scan chi2

  def _gen_scan_pars(self,pname,scale,sign):
    par=self.par
    order=self.order
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

  def gen_scan_pars(self):
    par=self.par
    order=self.order

    L=[]

    H='%7s'%''
    for o in order:
      H+='%15s'%o
    L.append(H)
    
    L.append(self._gen_scan_pars(None,0,1))
    
    for o in order:
      for i in range(10):
        L.append(self._gen_scan_pars(o,1/(2.0**i),1))
        L.append(self._gen_scan_pars(o,1/(2.0**i),-1))

    L=[l+'\n' for l in L]
    checkdir('data')
    F=open('data/scan_params.dat','w')
    F.writelines(L)
    F.close()

  # routines for analysis chi2 scan

  def _get_scan_data(self,fname):
    F=open(fname)
    L=F.readlines()
    F.close()
    L=[l.split() for l in L]
    
    # construct headres
    H={}
    cnt=0
    for h in L[0][2:]:
      H[h]=cnt
      cnt+=1
    
    # remove header table
    L=L[1:]
    
    # list or parameters
    K=['BLNY','Nu_c','Nd_c','au_c','ad_c','bu_c','bd_c','Nu_T','Nd_T','au_T','ad_T','bu_T','bd_T']
    
    # data to dict
    D={}
    for l in L: 
      D[l[0]]=[]
    
    for l in L: 
      D[l[0]].append([float(x) for x in l[2:]])
    
    data={} 
    chi20=D['FIT'][0][0]
    for k in K:
      data[k]={'h':[],'dchi2dxdx':[]}
      pars=D[k]
      i=H[k]
      for j in range(0,len(pars),2):
        chi2max=pars[j][0]
        chi2min=pars[j+1][0]
        pmax=pars[j][i]
        pmin=pars[j+1][i]
        h=0.5*(pmax-pmin)
        dchi2dxdx=(chi2max-2*chi20+chi2min)/h**2
        data[k]['h'].append(h)
        data[k]['dchi2dxdx'].append(dchi2dxdx)
    save(data,'data/%s.dchid2dxdx'%fname.split('/')[1].replace('.dat','')) 

  def get_scan_data(self):
   self._get_scan_data('hessian_collins/clas_p_pim.dat')
   self._get_scan_data('hessian_collins/clas_p_pip.dat')
   self._get_scan_data('hessian_collins/solid_3he_pip.dat')
   self._get_scan_data('hessian_collins/solid_3he_pim.dat')
   self._get_scan_data('hessian_collins/solid_p_pip.dat')
   self._get_scan_data('hessian_collins/solid_p_pim.dat')

  def _plot_hess_h(self,fname):
    print 'plotting ',fname

    data=load('data/%s.dchid2dxdx'%fname) 

    ncols,nrows=4,4
    py.figure(figsize=(ncols*5,nrows*3))
    
    # list or parameters
    K=['BLNY','Nu_c','Nd_c','au_c','ad_c','bu_c','bd_c','Nu_T','Nd_T','au_T','ad_T','bu_T','bd_T']

    cnt=1
    for k in K:
      ax=py.subplot(nrows,ncols,cnt)

      h=data[k]['h']  
      dchi2dxdx=data[k]['dchi2dxdx']  
    
      ax.plot(h,dchi2dxdx,'b-o')
      ax.set_xlabel(r'$h$')
      ax.set_ylabel(r'$\partial \chi^2/\partial^2 p$')
      ax.semilogx()
      ax.set_title(r'${\rm %s}$'%k.replace('_',' '))
      cnt+=1

      I=np.argsort(h)

      #if fname=='clas_p_pim':
      if k=='BLNY':i=I[-1]  
      if k=='Nu_c':i=I[-1]
      if k=='Nd_c':i=I[-1]
      if k=='au_c':i=I[-1]
      if k=='ad_c':i=I[-1]
      if k=='bu_c':i=I[-1]  
      if k=='bd_c':i=I[-1]  
      if k=='Nu_T':i=I[-1]
      if k=='Nd_T':i=I[-1]
      if k=='au_T':i=I[-5]
      if k=='ad_T':i=I[-4]
      if k=='bu_T':i=I[-5]
      if k=='bd_T':i=I[-5]


      ax.axvline(h[i],color='r',ls='--')
    py.tight_layout()
    checkdir('gallery')
    py.savefig('gallery/hess-%s.pdf'%fname)

  def plot_hess_h(self):
    #self._plot_hess_h('clas_p_pim')
    #self._plot_hess_h('clas_p_pip')
    #self._plot_hess_h('solid_3he_pip')
    #self._plot_hess_h('solid_3he_pim')
    #self._plot_hess_h('solid_p_pip')
    self._plot_hess_h('solid_p_pim')

  # routines to calculate hessian

  def _gen_hess_pars(self,hi,hj,Ki,Kj):
    par=self.par
    order=self.order
    L=''
    for o in order:
      if o==Ki:   L+='%15.5e'%(par[o]['val']+hi)
      elif o==Kj: L+='%15.5e'%(par[o]['val']+hj)
      else:       L+='%15.5e'%par[o]['val']
    return L

  def _get_target_par(self,Ki,Kj,All=False):
    par=self.par
    order=self.order
    L=''
    for o in order:
      if All==False:
        if o==Ki:   L+='%15s'%(Ki)
        elif o==Kj: L+='%15s'%(Kj)
        else:       L+='%15s'%''
      else:
        L+='%15s'%o
    return L

  def _get_hess_grid(self,fname):
    K=['BLNY','Nu_c','Nd_c','au_c','ad_c','bu_c','bd_c','Nu_T','Nd_T','au_T','ad_T','bu_T','bd_T']

    data=load('data/%s.dchid2dxdx'%fname) 
    H={}
    for k in K:
      h=data[k]['h']  
      I=np.argsort(h)
      if k=='BLNY':i=I[-1]  
      if k=='Nu_c':i=I[-1]
      if k=='Nd_c':i=I[-1]
      if k=='au_c':i=I[-1]
      if k=='ad_c':i=I[-1]
      if k=='bu_c':i=I[-1]  
      if k=='bd_c':i=I[-1]  
      if k=='Nu_T':i=I[-1]
      if k=='Nd_T':i=I[-1]
      if k=='au_T':i=I[-5]
      if k=='ad_T':i=I[-4]
      if k=='bu_T':i=I[-5]
      if k=='bd_T':i=I[-5]
      H[k]=h[i]
    
    # list or parameters
    npar=len(K)
    L=[]
    L.append('        %s'%self._get_target_par(None,None,All=True))
    for i in range(npar):
      for j in range(i,npar):
        hi=H[K[i]]
        hj=H[K[j]]
        #L.append('='*100)
        #L.append('h(%s)=%0.2e  h(%s)=%0.2e'%(K[i],hi,K[j],hj))
        #L.append('        %s'%self._get_target_par(K[i],K[j]))
        L.append('+%s +%s %s'%(K[i],K[j],self._gen_hess_pars(hi,hj,K[i],K[j])))
        L.append('+%s -%s %s'%(K[i],K[j],self._gen_hess_pars(hi,-hj,K[i],K[j])))
        L.append('-%s +%s %s'%(K[i],K[j],self._gen_hess_pars(-hi,hj,K[i],K[j])))
        L.append('-%s -%s %s'%(K[i],K[j],self._gen_hess_pars(-hi,-hj,K[i],K[j])))

    L=[l+'\n' for l in L]
    checkdir('data')
    F=open('data/%s.hesspar'%fname,'w')
    F.writelines(L)
    F.close()

  def get_hess_grid(self):
    self._get_hess_grid('clas_p_pim')
    self._get_hess_grid('clas_p_pip')
    self._get_hess_grid('solid_3he_pip')
    self._get_hess_grid('solid_3he_pim')
    self._get_hess_grid('solid_p_pip')
    self._get_hess_grid('solid_p_pim')

if __name__=='__main__':

  hess=HESS()
  #hess.gen_scan_pars()
  #hess.get_scan_data()
  #hess.plot_hess_h()
  hess.get_hess_grid()






















  

 


 




















