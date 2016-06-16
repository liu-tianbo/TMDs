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
            
            filename = '%s_%s_%s.eig'%(exps[i], tgts[j], pids[k])
            line = open(filename, 'r').readlines()
            print '--- Reading parameter file ', filename
            
            N = (len(line)-2)/2

            Oc_tens_u = np.zeros(1, dtype=float)#{{{
            Op_tens_u = np.zeros(N, dtype=float)
            Om_tens_u = np.zeros(N, dtype=float)
           
            Oc_tens_u_jlab = np.zeros(1, dtype=float)
            Op_tens_u_jlab = np.zeros(N, dtype=float)
            Om_tens_u_jlab = np.zeros(N, dtype=float)
         
            Oc_tens_d = np.zeros(1, dtype=float)
            Op_tens_d = np.zeros(N, dtype=float)
            Om_tens_d = np.zeros(N, dtype=float)
            
            Oc_tens_d_jlab = np.zeros(1, dtype=float)
            Op_tens_d_jlab = np.zeros(N, dtype=float)
            Om_tens_d_jlab = np.zeros(N, dtype=float)
              
            Oc_trans_x = np.zeros((1,100), dtype=float)
            Op_trans_x = np.zeros((N,100), dtype=float)
            Om_trans_x = np.zeros((N,100), dtype=float)
     
            Oc_trans_u = np.zeros((1,100), dtype=float)
            Op_trans_u = np.zeros((N,100), dtype=float)
            Om_trans_u = np.zeros((N,100), dtype=float)
         
            Oc_trans_d = np.zeros((1,100), dtype=float)
            Op_trans_d = np.zeros((N,100), dtype=float)
            Om_trans_d = np.zeros((N,100), dtype=float)#}}}
            
            ip = 0
            im = 0
            for l in range(1, len(line)):
                value= line[l].split()#{{{
                Type  = str(value[0])
                ID  = int(value[1])
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

                types = ''
                if Type=='+':
                    types='P'
                elif Type=='-':
                    types='M'
                elif Type=='C':
                    types='C'#}}}

                #gen_file = '%s_%s_%s/Tensor_%s_%d.dat'%(exps[i], tgts[j], pids[k], types, ID )
                gen_file = '%s_%s_%s/Old_%s_%d.dat'%(exps[i], tgts[j], pids[k], types, ID )
                if os.path.isfile(gen_file):
                    print '^^^^ Reading file %s!'%gen_file
                    lines = open(gen_file, 'r').readlines()

                    values= lines[0].split()#{{{
                    Type_n  = str(value[0])
                    ID_n  = int(values[1])
                    BLNY_n  = float(values[2])
                    Nu_c_n  = float(values[3])
                    Nd_c_n  = float(values[4])
                    au_c_n  = float(values[5])
                    ad_c_n  = float(values[6])
                    bu_c_n  = float(values[7])
                    bd_c_n  = float(values[8])
                    Nu_T_n  = float(values[9])
                    Nd_T_n  = float(values[10])
                    au_T_n  = float(values[11])
                    ad_T_n  = float(values[12])
                    bu_T_n  = float(values[13])
                    bd_T_n  = float(values[14])
                    ChiSQ = float(values[15])

                    if abs(BLNY_n-BLNY)>1e-3:
                        print "Don't match for %s %s %s %s %d"%(exps[i], tgts[j], pids[k], types, ID)#}}}

                    values= lines[1].split()#{{{
                    tensor_up = float(values[0])
                    tensor_up_jlab = float(values[1])
                    tensor_down = float(values[2])
                    tensor_down_jlab = float(values[3])#}}}

                    trans_x = np.zeros(100, dtype=float)#{{{
                    trans_u = np.zeros(100, dtype=float)
                    trans_d = np.zeros(100, dtype=float)
                    for l in range(2, len(lines)):
                        values= lines[l].split()
                        trans_x[l-2] = float(values[0])
                        trans_u[l-2] = float(values[1])
                        trans_d[l-2] = float(values[2])#}}}

                    if Type=='C':#{{{
                        Oc_tens_u[0] = tensor_up
                        Oc_tens_d[0] = tensor_down
                        Oc_tens_u_jlab[0] = tensor_up_jlab
                        Oc_tens_d_jlab[0] = tensor_down_jlab
                        for m in range(0,100):
                            Oc_trans_x[0][m] = trans_x[m]
                            Oc_trans_u[0][m] = trans_u[m]
                            Oc_trans_d[0][m] = trans_d[m]
#}}}

                    if Type=='+':#{{{
                        Op_tens_u[ip] = tensor_up
                        Op_tens_d[ip] = tensor_down
                        Op_tens_u_jlab[ip] = tensor_up_jlab
                        Op_tens_d_jlab[ip] = tensor_down_jlab
                        for m in range(0,100):
                            Op_trans_x[ip][m] = trans_x[m]
                            Op_trans_u[ip][m] = trans_u[m]
                            Op_trans_d[ip][m] = trans_d[m]
                        ip=ip+1
#}}}

                    if Type=='-':#{{{
                        Om_tens_u[im] = tensor_up
                        Om_tens_d[im] = tensor_down
                        Om_tens_u_jlab[im] = tensor_up_jlab
                        Om_tens_d_jlab[im] = tensor_down_jlab
                        for m in range(0,100):
                            Om_trans_x[im][m] = trans_x[m]
                            Om_trans_u[im][m] = trans_u[m]
                            Om_trans_d[im][m] = trans_d[m]
                        im=im+1#}}}

            print 'N = %d,  ip = %d, im = %d'%(N, ip, im)
            if N==ip and N ==im:
                dO2_tens_u = 0.0
                dO2_tens_d = 0.0
                dO2_tens_u_jlab = 0.0
                dO2_tens_d_jlab = 0.0
                dO2_trans_u = np.zeros(100, dtype=float)
                dO2_trans_d = np.zeros(100, dtype=float)
                for l in range(0, N):
                    dO2_tens_u += (Op_tens_u[l] - Om_tens_u[l])**2
                    dO2_tens_d += (Op_tens_d[l] - Om_tens_d[l])**2
                    dO2_tens_u_jlab += (Op_tens_u_jlab[l] - Om_tens_u_jlab[l])**2
                    dO2_tens_d_jlab += (Op_tens_d_jlab[l] - Om_tens_d_jlab[l])**2

   
                    for m in range(0, 100):
                        dO2_trans_u[m] += (Op_trans_u[l][m] - Om_trans_u[l][m])**2
                        dO2_trans_d[m] += (Op_trans_d[l][m] - Om_trans_d[l][m])**2


                dO_tens_u = 1./2. * dO2_tens_u**0.5
                dO_tens_d = 1./2. * dO2_tens_d**0.5
                dO_tens_u_jlab = 1./2. * dO2_tens_u_jlab**0.5
                dO_tens_d_jlab = 1./2. * dO2_tens_d_jlab**0.5
                dO_trans_u = np.zeros(100, dtype=float)
                dO_trans_d = np.zeros(100, dtype=float)
                for m in range(0, 100):
                    dO_trans_u[m] = 1./2. * dO2_trans_u[m]**0.5
                    dO_trans_d[m] = 1./2. * dO2_trans_d[m]**0.5

                #out_file = 'out_%s_%s_%s.dat'%(exps[i], tgts[j], pids[k])
                out_file = 'old_%s_%s_%s.dat'%(exps[i], tgts[j], pids[k])
                of = open(out_file, 'w')
                
                lines0 = '## T_u  dO_u   T_d  dO_d  T_u  dO_u   T_d_jlab  dO_d_jlab  T_u  dO_u_jlab   T_d  dO_d_jlab' 
                print >> of,lines0
                lines0= '%e  %e  %e  %e  %e  %e  %e  %e'%(Oc_tens_u[0], dO_tens_u,Oc_tens_d[0], dO_tens_d, Oc_tens_u_jlab[0], dO_tens_u_jlab,Oc_tens_d_jlab[0], dO_tens_d_jlab) 
                print >> of,lines0
              
                lines0 = '## x    h_u   dO_h_u    h_d   dO_h_d'
                print >> of,lines0
               
                for m in range(0, 100):
                    if abs(Oc_trans_x[0][m]-Op_trans_x[0][m])>1e-3 or abs(Oc_trans_x[0][m]-Om_trans_x[0][m])>1e-3:
                        print "ERROR: xbj values doesn't match!!!"
                    else:
                        lines0= '%e  %e  %e  %e  %e'%(Oc_trans_x[0][m],Oc_trans_u[0][m], dO_trans_u[m],Oc_trans_d[0][m], dO_trans_d[m])
                        print >> of,lines0
                of.close()




print 'All jobs have been submitted!'
