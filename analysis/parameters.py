#!/usr/bin/env python
import sys,os
import numpy as np
from numpy.random import uniform
from tools import save,load,checkdir
from numpy import linalg as LA
##########################################
import matplotlib.gridspec as gridspec
import matplotlib as mpl
#mpl.use('Agg')
import pylab as py
from  matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text',usetex=True)
##########################################

class dep_HESS(object):

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

  def _X_get_scan_data(self,fname):
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

    print H
    
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

  def _get_scan_data(self,fname):
    F=open(fname)
    L=F.readlines()
    F.close()
    L=[l.split() for l in L]

    # get parameter names  
    params=sorted(set([l[0] for l in L[2:]]))

    # get parameters column index
    icols={}
    for p in params:
      for i in range(len(L[0])):
        if L[0][i]==p: icols[p]=i

    # get dchidxdx
    data={} 
    chi20=float(L[1][2])
    for p in params:
      data[p]={'h':[],'dchi2dxdx':[]}
      rows=[l for l in L if l[0]==p]
      icol=icols[p]
      for i in range(0,len(rows),2): 
        chi2max=float(rows[i][2])
        chi2min=float(rows[i+1][2])
        pmax=float(rows[i][icol])
        pmin=float(rows[i+1][icol])
        h=0.5*(pmax-pmin)
        dchi2dxdx=(chi2max-2*chi20+chi2min)/h**2

        data[p]['h'].append(h)
        data[p]['dchi2dxdx'].append(dchi2dxdx)

        fmt='%s %0.4e %0.4e %0.2e %0.2e %0.2e %0.2e %0.4e'
        print fmt%(p,pmin,pmax,chi20,chi2min,chi2max,h,dchi2dxdx)
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
    params=self.order

    # retrieve 
    data=load('data/%s.dchid2dxdx'%fname) 
    H={}
    for p in params:
      H[p]=data[p]['h'][0]
    
    # list or parameters
    npar=len(params)
    L=[]
    L.append('        %s'%self._get_target_par(None,None,All=True))
    for i in range(npar):
      for j in range(i,npar):
        hi=H[K[i]]
        hj=H[K[j]]

        L.append('='*100)
        L.append('h(%s)=%0.2e  h(%s)=%0.2e'%(K[i],hi,K[j],hj))
        L.append('        %s'%self._get_target_par(K[i],K[j]))

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
    #self._get_hess_grid('clas_p_pip')
    #self._get_hess_grid('solid_3he_pip')
    #self._get_hess_grid('solid_3he_pim')
    #self._get_hess_grid('solid_p_pip')
    #self._get_hess_grid('solid_p_pim')

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

    self.P0 =np.array([par[o]['val'] for o in order])
    self.dP0=np.array([par[o]['err'] for o in order])

  def _gen_hess_pars(self,hi,hj,Ki,Kj):
    par=self.par
    order=self.order
    L=''
    flag=False
    for o in order:
      if o==Ki:   L+='%15.5e'%(par[o]['val']+hi)
      elif o==Kj: L+='%15.5e'%(par[o]['val']+hj)
      else:       L+='%15.5e'%par[o]['val']
      if o=='bu_T' or o=='bd_T':
        if par[o]['val']+hi<0 and flag==False:
          self.cnt+=1
          flag=True
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

  def get_hess_grid(self):
    order=self.order
    par=self.par

    # list or parameters
    npar=len(order)
    L=[]
    L.append('        %s'%self._get_target_par(None,None,All=True))
    self.cnt=0
    L.append('----- ----- %s'%(self._gen_hess_pars(0,0,'-','-')))
    for i in range(npar):
      for j in range(i,npar):
          pi=order[i]
          pj=order[j]
          hi=par[pi]['err']
          hj=par[pj]['err']

          #L.append('='*100)
          #L.append('h(%s)=%0.2e  h(%s)=%0.2e'%(pi,hi,pj,hj))
          #L.append('        %s'%self._get_target_par(pi,pj))

          if i!=j:
            L.append('+%s +%s %s'%(pi,pj,self._gen_hess_pars(hi,hj,pi,pj)))
            L.append('+%s -%s %s'%(pi,pj,self._gen_hess_pars(hi,-hj,pi,pj)))
            L.append('-%s +%s %s'%(pi,pj,self._gen_hess_pars(-hi,hj,pi,pj)))
            L.append('-%s -%s %s'%(pi,pj,self._gen_hess_pars(-hi,-hj,pi,pj)))
          else:
            L.append('+%s  %s %s'%(pi,pj,self._gen_hess_pars(hi,0,pi,pj)))
            L.append('-%s  %s %s'%(pi,pj,self._gen_hess_pars(-hi,0,pi,pj)))

    print self.cnt
    L=[l+'\n' for l in L]
    checkdir('data')
    F=open('data/hessgrid.dat','w')
    F.writelines(L)
    F.close()

  def get_old_hessian(self):
    F=open('data/correlation_matrix.dat')
    L=F.readlines()
    F.close()
    L=[l.strip().split() for l in L if l.strip()!='']
    L=[[float(x) for x in l] for l in L]
    corr=np.array(L)
    ndim=len(L)
    cov=np.zeros((ndim,ndim))
    for i in range(ndim):
      for j in range(ndim):
        cov[i,j]=corr[i,j]*self.dP0[i]*self.dP0[j]
    hess=LA.inv(cov)
    save(hess,'data/old.hess')

  def get_new_hessian(self,fname):
    path='hessian_collins/hessian_results/'

    # get off diagonal parts
    F=open(path+fname+'.out')
    L=F.readlines()
    F.close()
    L=[l.strip().split() for l in L] 

    # construct dict as
    # D[par1,par2] = {'P,P':#,'P,M':#,...}
    D={}
    for l in L:
      p1,p2=l[:2]
      key='%s,%s'%(p1.replace('M_','').replace('P_',''),p2.replace('M_','').replace('P_',''))
      if key not in D: D[key]={}
      key2='%s,%s'%(p1.split('_')[0],p2.split('_')[0])
      if float(l[-1])>0:
        D[key][key2]=float(l[-1])
      else:
        D[key][key2]=None

    # get diagonal parts
    F=open(path+fname+'.diag')
    L=F.readlines()
    F.close()
    L=[l.strip().split() for l in L] 

    for l in L:
      p1,p2=l[:2]
      key='%s,%s'%(p1.replace('M_','').replace('P_',''),p2.replace('M_','').replace('P_',''))
      if key=='FIRST,FIRST': 
        D['central']=float(l[-1])
        continue
      if key not in D: D[key]={}
      key2='%s,0'%(p1.split('_')[0])
      if float(l[-1])>0:
        D[key][key2]=float(l[-1])
      else:
        D[key][key2]=None


    # construct hessian
    npar=len(self.order)
    H=np.zeros((npar,npar))
    for k in D:
      if k=='central': continue
      #print k
      #continue
      #for kk in D[k]:
      #  print '\t',kk,D[k][kk]

      # get target entry at hess matrix (I,J)
      p1,p2=k.split(',')
      for i in range(npar): 
        if self.order[i]==p1: I=i
        if self.order[i]==p2: J=i

      # step size for target entry
      hi=self.par[p1]['err']
      hj=self.par[p2]['err']

      # compute hess entry
      if all([x!=None for x in [D[k][kk] for kk in ['P,P','M,M','P,M','M,P']]]):
        #print D[k]['P,P']
        #print D[k]['M,M']
        #print D[k]['P,M']
        #print D[k]['M,P']
        #print (4*hi*hj)
        if I!=J: 
          H[I,J]=(D[k]['P,P']+D[k]['M,M']-D[k]['P,M']-D[k]['M,P'])/(4*hi*hj)
        elif I==J:
          H[I,J]=(D[k]['P,0']+D[k]['M,0']-2*D['central'])/(hi**2)
      else:
        H[I,J]=None

    for i in range(npar):
      for j in range(npar):
        if i<j: H[j,i]=H[i,j]

    # get final hessian = 1/2 dchi2/dxdy
    H*=0.5


    # print hessian
    row='%10s'%''
    for i in range(npar): row+='%10s'%self.order[i]
    print row
    for i in range(npar):
      row='%10s  '%self.order[i]
      for j in range(npar): 
        if np.isnan(H[i,j])==False:
          row+='%10.2e'%H[i,j]
        else:
          row+='%10s'%''
      print row

    # save hessian
    save(H,'data/'+fname+'.hess')

  def gen_mcpar(self,fname):
    """
    this routine generates MC pars. to visualize the impact with respect to 
    original cov matrix
    """

    H0=load('data/old.hess')
    H=load('data/'+fname+'.hess')
    ndim=H0.shape[0]
    I=[i for i in range(ndim) if np.isnan(H[0][i])==False]
    nrdim=len(I)

    RH0=np.copy(H0[I,:][:,I])
    RH=np.copy(H[I,:][:,I])

    P0=self.P0[I]
    SAMPLE0 = np.random.multivariate_normal(P0,LA.inv(RH0),10000).T
    SAMPLE  = np.random.multivariate_normal(P0,LA.inv(RH0+RH),10000).T
    names=[self.order[i] for i in I]

    ncols,nrows=3,4
    py.figure(figsize=(ncols*5,nrows*3))
    for i in range(nrdim):
      print i
      ax=py.subplot(nrows,ncols,i+1)
      Range=None
      bins=100
      ax.hist(SAMPLE0[i],histtype='stepfilled',range=Range,color='Yellow',bins=bins)
      ax.hist(SAMPLE[i],histtype='stepfilled',range=Range,color='b',bins=bins)

      pmap={}
      pmap['BLNY']=r'$BLNY$'
      pmap['Nu_c']=r'$N_{u(c)}$'
      pmap['Nd_c']=r'$N_{d(c)}$'
      pmap['au_c']=r'$a_{u(c)}$'
      pmap['ad_c']=r'$a_{d(c)}$'
      pmap['bu_c']=r'$b_{u(c)}$'
      pmap['bd_c']=r'$b_{d(c)}$'
      pmap['Nu_T']=r'$N_{u(T)}$'
      pmap['Nd_T']=r'$N_{d(T)}$'
      pmap['au_T']=r'$a_{u(T)}$'
      pmap['ad_T']=r'$a_{d(T)}$'
      pmap['bu_T']=r'$b_{u(T)}$'
      pmap['bd_T']=r'$b_{d(T)}$'

      ax.text(0.1,0.8,pmap[names[i]],transform=ax.transAxes,size=20)
      #ax.legend(frameon=0,fontsize=20,loc='best')
      #ax.tick_params(axis='both', which='major', labelsize=20)
    py.tight_layout()
    py.savefig('gallery/%s.pdf'%fname)

  def gen_hess_par(self,fname):

    H0=load('data/old.hess')
    H=load('data/'+fname+'.hess')
    ndim=H0.shape[0]
    I=[i for i in range(ndim) if np.isnan(H[0][i])==False]
    nrdim=len(I)
 
    RH0=np.copy(H0[I,:][:,I])
    RH=np.copy(H[I,:][:,I])

    HTOT=RH0+RH
    W,V=LA.eig(HTOT)
    V=np.transpose(V)
    for i in range(W.size): 
      if W[i]<0: continue
      V[i]/=W[i]**0.5

    L=[]

    h='%5s'%''
    for name in self.order: h+='%15s'%name
    L.append(h)
    print h
    

    P0=np.copy(self.P0)
    for i in range(W.size):
      if W[i]<0: continue
      PP=np.copy(P0)
      PP[I]+=V[i]
      PM=np.copy(P0)
      PM[I]-=V[i]
      lp='+%5d'%i
      for p in PP: lp+='%15.5e'%p
      lm='-%5d'%i
      for p in PM: lm+='%15.5e'%p
      L.append(lp)
      L.append(lm)
      print lp
      print lm

    L=[l+'\n' for l in L]
    F=open('data/'+fname+'.eig','w')
    F.writelines(L)
    F.close()


if __name__=='__main__':

  hess=HESS()
  #hess.get_hess_grid()
  #hess.get_new_hessian('clas_p_pim')
  #hess.get_new_hessian('clas_p_pip')
  #hess.get_new_hessian('solid_3he_pim')
  #hess.get_new_hessian('solid_3he_pip')
  #hess.get_new_hessian('solid_p_pim')
  #hess.get_new_hessian('solid_p_pip')
  #hess.get_old_hessian()

  #hess.gen_mcpar('clas_p_pim')
  #hess.gen_mcpar('clas_p_pip')
  #hess.gen_mcpar('solid_3he_pim')
  #hess.gen_mcpar('solid_3he_pip')
  #hess.gen_mcpar('solid_p_pim')
  #hess.gen_mcpar('solid_p_pip')

  hess.gen_hess_par('clas_p_pim')
  hess.gen_hess_par('clas_p_pip')
  hess.gen_hess_par('solid_3he_pim')
  hess.gen_hess_par('solid_3he_pip')
  hess.gen_hess_par('solid_p_pim')
  hess.gen_hess_par('solid_p_pip')















  

 


 




















