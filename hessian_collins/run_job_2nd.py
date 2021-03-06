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

of0 = open('norun.dat','w')

home = '/work/halla/solid/yez/TMDs/hessian_collins/'
for i in range(0,2):
    for j in range(0,2):
        if exps[i]=='clas' and tgts[j]=='3he':
                continue

        for k in range(0,2):

            filename = '%s_%s_%s.hesspar'%(exps[i], tgts[j], pids[k])
            lines = open(filename, 'r').readlines()

            N=len(lines)-1

            print '--- Reading parameter file ', filename
            for l in range(1, len(lines)):
                # print '%d/%d'%(j, len(lines))
                value= lines[l].split()

                Type1  = str(value[0])
                Type2  = str(value[1])
                BLNY  = float(value[2])
                Nu_c  = float(value[3])
                Nd_c  = float(value[4])
                au_c  = float(value[5])
                ad_c  = float(value[6])
                bu_c  = float(value[7])
                bd_c  = float(value[8])
                Nu_T  = float(value[9])
                Nd_T  = float(value[10])
                au_T  = float(value[11])
                ad_T  = float(value[12])
                bu_T  = float(value[13])
                bd_T  = float(value[14])

                gen_file = '%s_%s_%s/ChiSQ_%s_%s.dat'%(exps[i], tgts[j], pids[k], Type1 , Type2 )
                if os.path.isfile(gen_file):
                    print '^^^^ File %s exits, skipped!'%gen_file
                    continue

                print >> of0, gen_file

                ###################
                ##Create command file
                batchfile = './batch_files/run_%d_%d_%d_%s_%s'%(i,j,k,Type1 ,Type2 )
                print 'creating batch file', batchfile
                of = open(batchfile,'w')
                line = 'cd %s'%home
                print >> of, line
                PAR = '%e  %e  %e  %e  %e  %e  %e  %e  %e  %e  %e  %e  %e'\
                        %(BLNY ,Nu_c ,Nd_c ,au_c ,ad_c ,bu_c ,bd_c ,Nu_T ,Nd_T ,au_T ,ad_T ,bu_T ,bd_T )
                line = './GetCollins.exe %s %s %s %s %s %s'%(EXP[i], TGT[j], PID[k], Type1 , Type2 , PAR)
                print >> of, line
                of.close()
                os.system('chmod +x %s'%batchfile)
                ###################
                
                ###################
                ##Create job script
                jobfile = './batch_files/job_%d_%d_%d_%s_%s'%(i,j,k,Type1 ,Type2 )
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
                line='TIME        400'
                print >> of2, line
                line='MEMORY      2048 MB'
                print >> of2, line
                line='OS          centos65'
                print >> of2, line
                of2.close()
                #################
                
                # Submit the job
                # os.system('jsub %s'%jobfile)
                print '--- Job %s has been submitted'%jobfile

print 'All jobs have been submitted!'
