##!/apps/python/bin/
#/home/yez/anaconda/bin/python

import sys, os, traceback
import numpy as np

EXP = ['-SOLID','-CLAS12']
exps= ['solid','clas']
TGT = ['-PROTON', '-NEUTRON']
tgts= ['p', '3he']
PID = ['-PI+', '-PI-']
pids= ['pip', 'pim']

of0= open("fails_par.dat",'w')

home = '/work/halla/solid/yez/TMDs/seg_collins/'
for i in range(0,2):
    for j in range(0,2):
        if exps[i]=='clas' and tgts[j]=='3he':
                continue

        for k in range(0,2):

            filename = 'hessgrid.dat'
            #filename = './%s_%s_%s.hesspar'%(exps[i], tgts[j], pids[k])
            lines = open(filename, 'r').readlines()

            N=len(lines)-1
            
            out_filename = './hessian/%s_%s_%s.diag'%(exps[i], tgts[j], pids[k])
            of = open(out_filename,'w')

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
                # print 'Reading %s and saved into %s'%(gen_file,out_filename)
                if os.path.isfile(gen_file):
                    new_lines = open(gen_file,'r').readlines()
                    new_value = new_lines[0].split()
                    ChiSQ = float(new_value[15])
                else:
                    print 'count not find the result! %s'%gen_file
                    ChiSQ = -11111
                    print >> of0, '%s %s %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e'\
                        %(Type1, Type2, BLNY,Nu_c,Nd_c,au_c,ad_c,bu_c,bd_c,Nu_T,Nd_T,au_T,ad_T,bu_T,bd_T)

                print >> of, '%6s %6s %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e %14.5e'\
                        %(Type1,Type2,BLNY,Nu_c,Nd_c,au_c,ad_c,bu_c,bd_c,Nu_T,Nd_T,au_T,ad_T,bu_T,bd_T,ChiSQ)

            of.close()

print 'All jobs have been submitted!'
