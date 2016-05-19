#!/apps/python/bin/
##/home/yez/anaconda/bin/python

import sys, os, traceback
import numpy as np

EXP = ['-SOLID','-CLAS12']
exps= ['solid','clas']
TGT = ['-PROTON', '-NEUTRON']
tgts= ['p', '3he']
PID = ['-PI+', '-PI-']
pids= ['pip', 'pim']

filename = 'params_hessian.dat'
lines = open(filename, 'r').readlines()

N=len(lines)-1
BLNY = np.zeros(N,dtype=float)
Nu_c = np.zeros(N,dtype=float)
Nd_c = np.zeros(N,dtype=float)
au_c = np.zeros(N,dtype=float)
ad_c = np.zeros(N,dtype=float)
bu_c = np.zeros(N,dtype=float)
bd_c = np.zeros(N,dtype=float)
Nu_T = np.zeros(N,dtype=float)
Nd_T = np.zeros(N,dtype=float)
au_T = np.zeros(N,dtype=float)
ad_T = np.zeros(N,dtype=float)
bu_T = np.zeros(N,dtype=float)
bd_T = np.zeros(N,dtype=float)
ID =   np.zeros(N,dtype='int64')
Type = np.empty(N,dtype='S5')

print '--- Reading parameter file ', filename
count=1
for j in range(1, len(lines)):
    # print '%d/%d'%(j, len(lines))
    value= lines[j].split()

    i=j-1
    Type[i] = str(value[0])
    if i>1 and Type[i]==Type[i-1]:
        count=count+1
    else:
        count=1
        
    ID[i]=count
    BLNY[i] = float(value[1])
    Nu_c[i] = float(value[2])
    Nd_c[i] = float(value[3])
    au_c[i] = float(value[4])
    ad_c[i] = float(value[5])
    bu_c[i] = float(value[6])
    bd_c[i] = float(value[7])
    Nu_T[i] = float(value[8])
    Nd_T[i] = float(value[9])
    au_T[i] = float(value[10])
    ad_T[i] = float(value[11])
    bu_T[i] = float(value[12])
    bd_T[i] = float(value[13])

print '--- Done!'

home = '/work/halla/solid/yez/TMDs/hessian_collins/'
for i in range(0,2):
    for j in range(0,2):
        for k in range(0,2):
            if exps[j]=='clas' and tgts=='3he':
                continue
            for l in range(0, N):

                gen_file = '%s_%s_%s/ChiSQ_%s_%d.dat'%(exps[i], tgts[j], pids[k], Type[l], ID[l])
                if os.path.isfile(gen_file):
                    print '^^^^ File %s exits, skipped!'%gen_file
                    continue

                ###################
                ##Create command file
                batchfile = './batch_files/run_%d_%d_%d_%s_%d'%(i,j,k,Type[l],ID[l])
                print 'creating batch file', batchfile
                of = open(batchfile,'w')
                line = 'cd %s'%home
                print >> of, line
                PAR = '%f  %f  %f  %f  %f  %f  %f  %f  %f  %f  %f  %f  %f'\
                        %(BLNY[l],Nu_c[l],Nd_c[l],au_c[l],ad_c[l],bu_c[l],bd_c[l],Nu_T[l],Nd_T[l],au_T[l],ad_T[l],bu_T[l],bd_T[l])
                line = './GetCollins.exe %s %s %s %s %d %s'%(EXP[i], TGT[j], PID[k], Type[l], ID[l], PAR)
                print >> of, line
                of.close()
                os.system('chmod +x %s'%batchfile)
                ###################
                
                ###################
                ##Create job script
                jobfile = './batch_files/job_%d_%d_%d_%s_%d'%(i,j,k,Type[l],ID[l])
                print 'creating batch file', jobfile
                of2 = open(jobfile,'w')
                line='PROJECT     solid'
                print >> of2, line
                line='COMMAND     %s/%s'%(home, batchfile)
                print >> of2, line
                line='JOBNAME     job_%d_%d_%d_%d'%(i,j,k,l)
                print >> of2, line
                line='TRACK       simulation'
                print >> of2, line
                line='TIME        200'
                print >> of2, line
                line='MEMORY      1024 MB'
                print >> of2, line
                line='OS          centos65'
                print >> of2, line
                of2.close()
                #################
                
                # Submit the job
                os.system('jsub %s'%jobfile)
                print '--- Job %s has been submitted'%jobfile

print 'All jobs have been submitted!'
