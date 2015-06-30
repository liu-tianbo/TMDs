#include <omp.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "TSystem.h"
#include "TMath.h"
#include "Math/Interpolator.h"
#include "Math/Integrator.h"
#include "Math/IntegratorMultiDim.h"
#include "Math/AllIntegrationTypes.h"
#include "Math/Functor.h"
#include "Math/GaussIntegrator.h"
#include "TMinuit.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TH1F.h"
#include "gsl/gsl_sf_bessel.h"
#include "gsl/gsl_sf_gamma.h"
#include <Math/SpecFuncMathCore.h>
#include "TLatex.h"
#include "hoppet_v1.h"
//#include "/work/halla/solid/yez/TMDs/hoppet-1.1.5/include/hoppet_v1.h"
#include <ctime>

#include "TStyle.h" 


#define Log log
#define Power pow

 using namespace std;
extern "C" {
  void setct10_(int * iset);
}

extern "C" {
  double ct10pdf_(int * iparton, double * x, double * q);
}


 double pdf ( int  iparton , double  x , double q2  ) 
{ int Iset = 100; 
 setct10_(&Iset);
 double q = sqrt(q2);
return ct10pdf_(&iparton,&x,&q);
} 

const int num_x=1000;
double list_x[num_x];
double list_pdf[5][num_x];


typedef struct { int FINI; } mycommonF77;


extern mycommonF77 fraginid_;




extern "C" {
void fdss_(int*IH,int*IC,int*IO,double*X,double*Q2,double*U,double*UB,
double*D,double*DB,double*S,double*SB,double*C,double*B,double*GL);
}




 double ffu (int hadron,int charge ,double x,double q2) 
{
int IO=1;
 double U, UB, D, DB, S, SB, C, B, GL;
fdss_(&hadron,&charge,&IO,&x,&q2,&U,&UB,&D,&DB,&S,&SB,&C,&B,&GL);
 return U/x;
} 

 double ffub (int hadron,int charge ,double x,double q2) 
{int IO=1;
 double U, UB, D, DB, S, SB, C, B, GL;
fdss_(&hadron,&charge,&IO,&x,&q2,&U,&UB,&D,&DB,&S,&SB,&C,&B,&GL);
 return UB/x;
} 

 double ffd (int hadron,int charge ,double x,double q2) 
{int IO=1;
 double U, UB, D, DB, S, SB, C, B, GL;
fdss_(&hadron,&charge,&IO,&x,&q2,&U,&UB,&D,&DB,&S,&SB,&C,&B,&GL);
 return D/x;
} 

 double ffdb (int hadron,int charge ,double x,double q2) 
{int IO=1;
 double U, UB, D, DB, S, SB, C, B, GL;
fdss_(&hadron,&charge,&IO,&x,&q2,&U,&UB,&D,&DB,&S,&SB,&C,&B,&GL);
 return DB/x;
} 

 double ffs (int hadron,int charge ,double x,double q2) 
{int IO=1;
 double U, UB, D, DB, S, SB, C, B, GL;
fdss_(&hadron,&charge,&IO,&x,&q2,&U,&UB,&D,&DB,&S,&SB,&C,&B,&GL);
 return S/x;
} 

 double ffsb (int hadron,int charge ,double x,double q2) 
{int IO=1;
 double U, UB, D, DB, S, SB, C, B, GL;
fdss_(&hadron,&charge,&IO,&x,&q2,&U,&UB,&D,&DB,&S,&SB,&C,&B,&GL);
 return SB/x;
} 

 double ffg (int hadron,int charge ,double x,double q2) 
{int IO=1;
 double U, UB, D, DB, S, SB, C, B, GL;
fdss_(&hadron,&charge,&IO,&x,&q2,&U,&UB,&D,&DB,&S,&SB,&C,&B,&GL);
 return GL/x;
} 


extern "C" {
void dssvfit_(double*X,double*Q2,double*DUV,double*DDV,double*DUBar,double*DDBar,double*DSTR,double*DGLU);
}

extern "C" {
  void dssvini_(int * iset);
}


double gpu (double x,double q2) 
{int Iset = 0; 
 dssvini_(&Iset);

 double U, UB, D, DB, S, GL;
dssvfit_(&x,&q2,&U,&D,&UB,&DB,&S,&GL);
 return (U+UB)/x;
} 

double gpd (double x,double q2) 
{int Iset = 0; 
 dssvini_(&Iset);

 double U, UB, D, DB, S, GL;
dssvfit_(&x,&q2,&U,&D,&UB,&DB,&S,&GL);
 return (D+DB)/x;
} 



double list_ff[5][num_x];

void list_ff_f()
{
   for( int j=0 ;j< num_x ;++j)
    {
fraginid_.FINI=0;
 list_ff[1+1][j]=ffu (1,1 ,list_x[j],2.4);
fraginid_.FINI=0;
 list_ff[1-1][j]=ffu (1,-1 ,list_x[j],2.4);
fraginid_.FINI=0;
 list_ff[1+3][j]=ffs (1, 1 ,list_x[j],2.4);

}
}



void list_pdf_f()
{
  
 
  for (int i=0; i<num_x ;++i )
    {
      list_x[i]=1.0/pow(1.02,num_x-1)*pow(1.02,i);
      //    cout<<list_x[i]<<endl;
}

  list_x[num_x-1]=1; 

  double value_u;
  double value_d;


  for( int j=0 ;j< num_x ;++j)
    {

      if(list_x[j]<0.00001   )
	{ value_u=gpu(0.00001,2.4);  
          value_d=gpd(0.00001,2.4);
	}else{
	value_u=gpu(list_x[j],2.4 );
        value_d=gpd(list_x[j],2.4 );

}

 list_pdf[2+1][j]=0.5*(pdf(1,list_x[j],2.4)+value_u);
 list_pdf[2-1][j]=pdf(-1,list_x[j],2.4);
 list_pdf[2+2][j]=0.5*(pdf(2,list_x[j],2.4)+value_d);
 list_pdf[2-2][j]=pdf(-2,list_x[j],2.4);    

}
}


 double pdf_n( int  iparton , double  x   ) 
{
 ROOT::Math::Interpolator intera_x (num_x,ROOT::Math::Interpolation::kAKIMA);
  //  ROOT::Math::Interpolator intera_x (num_x,ROOT::Math::Interpolation::kAKIMA);
    intera_x.SetData(num_x,list_x,list_pdf[2+iparton]);

     return intera_x.Eval(x) ;


}




 double ff_nn( int  iparton , double  x   ) 
{
 ROOT::Math::Interpolator intera_y (num_x,ROOT::Math::Interpolation::kAKIMA);
  //  ROOT::Math::Interpolator intera_x (num_x,ROOT::Math::Interpolation::kAKIMA);
   intera_y.SetData(num_x,list_x,list_ff[1+iparton]);

     return intera_y.Eval(x) ;




}




const double pi= TMath::Pi(); 
 double S;
const double compass=160.0*2*0.94;
const double hermas=27.6*2*0.94;
const double alf=1.0/137;
const double C1=2.0*exp(-TMath::EulerGamma());
//const double nf=4.0;
const double CA=3.0;
const double CF=4.0/3;
//const double Bb0=(11.0-(2.0/3)*nf);

const double Mp=0.93;




const double A1=CF;
const double B1=-(3.0/2)*CF;

//const double Q02=2.4;
const double bm=1.5;

const double LQCD2_5=0.225*0.225;


double b_l=0.00001;
 double b_u=10; 

double as ( double X )
{ 

double  Bb0f_5=  (11.0-(2.0/3.0)*5.0);

double  Bb1f_5=  102.0-38.0*5.0/3.0;

 double LQCD2f_5=LQCD2_5;

// double X2=X;

  //   return 4*pi*(1/(Bb0f(X2)*Log(X/LQCD2f(X2))) - (Bb1f(X2)*Log(Log(X/LQCD2f(X2))))/(Power(Bb0f(X2),3)*Power(Log(X/LQCD2f(X2)),2)));

  
 return 4*pi*(1/(Bb0f_5*Log(X/LQCD2f_5)) - (Bb1f_5*Log(Log(X/LQCD2f_5)))/(Power(Bb0f_5,3)*Power(Log(X/LQCD2f_5),2)));
 

 }



const double re3=1.202;
const double Nc=3.0;



double Sudakovkernel( double mu2 , double Q2  ,double LQCD2,double nf   )
{



double Bb0=(11.0-(2.0/3)*nf);
 
 double Bb1=102.0-38.0*nf/3;
 double A1=CF;
 double A2= CF*((67.0/36.0-pi*pi/12.0)*CA-5.0/18.0*nf);
 double B1=-(3.0/2.0)*CF;
 // double B2=CF*CF*(pi*pi/4.0-3.0/16.0-3*re3)+CF*Nc*(11.0/36.0*pi*pi-193.0/48.0+3.0/2.0*re3)+CF*nf*(-1.0/18.0*pi*pi+17.0/24.0);
 double B2=0;
return

(2*(54*A1*Power(Bb0,5)*Power(Log(mu2/LQCD2),4)*(-1 + Log(Log(mu2/LQCD2))) - 
       8*Power(Bb1,2)*(B2 + A2*Log(Q2/mu2))*(2 + 6*Log(Log(mu2/LQCD2)) + 9*Power(Log(Log(mu2/LQCD2)),2)) + 
       27*Power(Bb0,3)*Power(Log(mu2/LQCD2),3)*(-8*A2*Bb0 + 2*A1*Bb1 + 2*(-4*A2*Bb0 + B1*Power(Bb0,2) + A1*Bb1
 + A1*Power(Bb0,2)*Log(Q2/mu2))*Log(Log(mu2/LQCD2)) + 
          A1*Bb1*Power(Log(Log(mu2/LQCD2)),2)) + 2*Bb1*Log(mu2/LQCD2)*
        (54*B2*Power(Bb0,2) + 19*A2*Bb1 + 6*(18*B2*Power(Bb0,2) + 5*A2*Bb1)*Log(Log(mu2/LQCD2)) + 18*A2*Bb1*Power(Log(Log(mu2/LQCD2)),2) + 
          54*A2*Power(Bb0,2)*Log(Q2/mu2)*(1 + 2*Log(Log(mu2/LQCD2)))) - 
       54*Power(Bb0,2)*Power(Log(mu2/LQCD2),2)*(4*B2*Power(Bb0,2) + 6*A2*Bb1 - B1*Bb0*Bb1 + (4*A2 - B1*Bb0)*Bb1*Log(Log(mu2/LQCD2)) + 
						Bb0*Log(Q2/mu2)*(4*A2*Bb0 - A1*Bb1
 - A1*Bb1*Log(Log(mu2/LQCD2))))))/(27.*Power(Bb0,6)*Power(Log(mu2/LQCD2),3));


}



double Sudakov1( double Q2 , double b )
{

 double bs2= b*b/(1+b*b/(bm*bm) )/C1/C1;
 double upL1= Sudakovkernel( Q2 ,  Q2  , LQCD2_5 ,5.0  );
 double downL1= Sudakovkernel( 1/bs2 , Q2 ,   LQCD2_5 ,5.0    );
 return exp(-(upL1-downL1));

}


double Sudakov2( double Q2 ,double b )
{
double g2=0.842;
 
  double Q12=2.4;
  
 double bs2= b*b/(1+b*b/(bm*bm) );

 return exp(-(g2*log(Q2/Q12)/2)*log(b*b/bs2)/2 );

}


const  double BNLYd= 0.042;




const double euq2=4.0/9;
const double edq2=1.0/9;
const double CB=0.3894E9;



double phtit,ptit;
double BNLYit;
double Q2it;
double zit;
double xit;

#pragma omp threadprivate(zit)
#pragma omp threadprivate(xit)
#pragma omp threadprivate(ptit)
#pragma omp threadprivate(phtit)
#pragma omp threadprivate(Q2it)






double Nuit, Ndit, Nuit_t, Nubit_t ,Ndit_t  ,Ndbit_t ,
       auit, adit,   auit_t, aubit_t,  adit_t, adbit_t ,
       buit, bdit,  buit_t, bdit_t, bubit_t, bdbit_t   ;

void  heralhc_init(const double & x,
                   const double & Q,
                   double * pdf_a) { 
  
  // Nuit=       1.00000e+01  ;
  // Ndit=      -1.53931e+00  ;
  // auit=       7.96969e+00  ;
  // adit=       1.43211e+00  ;
  // buit=       1.18983e+00  ;
  // bdit=       7.20196e-09  ;


  double  uv  =x* Nuit * pow(x,auit) * pow(1-x,buit)   * ff_nn(1 ,x) ;
  double  ub  =x* Ndit * pow(x,adit) * pow(1-x,bdit)   * ff_nn(-1,x) ;
  double  sv  =x* Ndit * pow(x,adit) * pow(1-x,bdit)   * ff_nn(3,x) ;

  // double  uv  =x* Nuit * pow(x,auit) * pow(1-x,buit)   * ff_nn (1 ,x) ;
  // double  ub  =x* Ndit * pow(x,adit) * pow(1-x,bdit)   * ff_nn (-1 ,x) ;
 // double  dv  =x* Ndit * pow(x,adit) * pow(1-x,bdit)   * ffd (1,1 ,x,2.4) ;
 // double  db  =x* Nuit * pow(x,auit) * pow(1-x,buit)   * ffd (1,-1 ,x,2.4) ;



  double  uv_t  =pow(auit_t+buit_t,auit_t+buit_t)/pow(auit_t,auit_t)/pow(buit_t,buit_t)*x* Nuit_t * pow(x,auit_t) * pow(1-x,buit_t)   * pdf_n (1 ,x) ;
 // double  ub_t  =x* Nubit_t * pow(x,aubit_t) * pow(1-x,bubit_t)   * pdf_n (-1 ,x) ;
  double  dv_t  =pow(adit_t+bdit_t,adit_t+bdit_t)/pow(adit_t,adit_t)/pow(bdit_t,bdit_t)*x* Ndit_t * pow(x,adit_t) * pow(1-x,bdit_t)   * pdf_n (2 ,x) ;
 // double  db_t  =x* Ndbit_t * pow(x,adbit_t) * pow(1-x,bdbit_t)   * pdf_n (-2 ,x) ;


 


// double  uv_t  =0 ;
// double  ub_t  =0 ;
// double  dv_t  =0 ;
// double  db_t  =0 ;



  pdf_a[ 0+6] = 0;
  pdf_a[2+6] = uv_t;
  pdf_a[-2+6] = dv_t;
  pdf_a[ 3+6] = sv;
  pdf_a[-3+6] = 0;

  pdf_a[ 1+6] = uv;
  pdf_a[-1+6] = ub;



  pdf_a[ 4+6] = 0;
  pdf_a[-4+6] = 0;

 

 
  pdf_a[ 5+6] = 0;
  pdf_a[ 6+6] = 0; 
  pdf_a[-5+6] = 0;
  pdf_a[-6+6] = 0;





}


double pof_s_pi(  double x,  double Q2  )
{

  

  double Q= sqrt(Q2);
  double pdf_a[13];
  hoppetEval(x, Q, pdf_a);
  return pdf_a[6+3]/x;



  }




double pof_u_pi(  double x,  double Q2  )
{

 

  double Q= sqrt(Q2);
  double pdf_a[13];
  hoppetEval(x, Q, pdf_a);
  return pdf_a[6+1]/x;



  }


double pof_ub_pi(  double x,  double Q2  )
{

 


  double Q= sqrt(Q2);
 double pdf_a[13];
  hoppetEval(x, Q, pdf_a);
  return pdf_a[6-1]/x;


 
}





double pof_u_mpi( double x,  double Q2  )
{ 
  return pof_ub_pi(  x,   Q2  );
 }


double pof_ub_mpi(  double x,  double Q2  )
{
  return pof_u_pi(   x,   Q2  );
}




double pof_d_pi(   double x,  double Q2  )
{
return  pof_ub_pi(   x,   Q2  );
}


double pof_db_pi(   double x,  double Q2  )
{
return  pof_u_pi(    x,   Q2  );
}



double pof_d_mpi(   double x,  double Q2  )
{
return  pof_ub_mpi(   x,   Q2  );
}




double pof_db_mpi(   double x,  double Q2  )
{
return  pof_u_mpi(   x,   Q2  );
}






double Sit;





const  double S_compass=160*0.94*2;
const  double S_hermes=27.6*0.94*2;
const  double S_Jlab=5.9*0.94*2;


////////////////////////////////////////////////////////////////////////
////////////////////// BEGINNING ///////////////////////////////////////


const  double S_Jlab12=11.*0.94*2;

double UNPOLARISED_PIP[5000]; // we will store here unpolarised cross sections
double UNPOLARISED_PIM[5000]; // we will store here unpolarised cross sections

double POLARISED_PIP[5000]; // we will store here polarised cross sections
double POLARISED_PIM[5000]; // we will store here polarised cross sections

double ERROR_POLARISED_PIP[5000]; // we will store here polarised cross sections
double ERROR_POLARISED_PIM[5000]; // we will store here polarised cross sections


double Singma0( double Q2 , double Si ,double x )
{
return (2*pi*alf*alf)*(1+(1-Q2/(x*Si))*(1-Q2/(x*Si)))/(Q2*Q2);
}

double Singma0_collins( double Q2 , double Si ,double x )
{

 double y=Q2/(Si*x);

 double val= (2*pi*alf*alf)*(1+(1-Q2/(x*Si))*(1-Q2/(x*Si)))/(Q2*Q2);
 
 double cof=(2*(1-y)/(1+(1-y)*(1-y)));

return  val*cof;
}

const  double BNLYf= 0.212/2.0;
const  double  g3=0;

double Sudakov3unpoDIS( double b , double x, double z )
{
  return exp(-BNLYf*b*b-g3*pow(0.01/x,0.2)-BNLYd*b*b/(z*z));
}

double Sudakov3poDIS(double adterm , double b , double x, double z )
{
  return exp(-BNLYf*b*b-g3*pow(0.01/x,0.2)-BNLYd*b*b/(z*z)+adterm*b*b/(z*z));
}


double unpopdf_dis_N(double x1, double  x2 , double xi1a, double xi2a ,double b ,int fh  ,int ch   )
{ 

  //fraginid_.FINI=0;

 double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

 double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 double z1=x1/xi1;
 double z2=x2/xi2;



 double pdfuf=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(2,x1,mu2)/(1-x1) +as(mu2)/pi*pdf(2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi*pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
                          ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffu(fh,ch,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffu(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) + 

			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(-2,x1,mu2)/(1-x1)+as(mu2)/pi* pdf(-2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffub(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffub(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) );

 double pdfdf=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(1,x1,mu2)/(1-x1) +as(mu2)/pi*pdf(1,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffd(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffd(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) + 
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(-1,x1,mu2)/(1-x1)
                                                                            +as(mu2)/pi* pdf(-1,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffdb(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffdb(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) );



 return pdfuf+pdfdf;

}


double ker1_fun_unpo_N(double b,double Q2, double pt, double z ,double x , double xi1a, double zi2a ,int cn   )
 { 

    double funpo=unpopdf_dis_N( x, z ,  xi1a, zi2a , b ,1  ,  cn   );

 
 double crsunpo=Singma0(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*pi))*(TMath::BesselJ0(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3unpoDIS(b,x,z);
 return crsunpo ;
} 



double ker2_fun_unpo_pip_xz_N(const double * xi)
{
  return ker1_fun_unpo_N(xi[0],Q2it,phtit/zit,zit,xit, xi[1],xi[2],1  );
}

double ker2_fun_unpo_pim_xz_N(const double * xi)
{
  return ker1_fun_unpo_N(xi[0],Q2it,phtit/zit,zit,xit, xi[1],xi[2],-1  );
}



void UNPOLARISED_N_PIP ( int numi   ,  double zi[] ,double xi[] ,double Q2i[] , double phti[]  ) 
{ 
 


 Sit=S_Jlab12;

 double a[3] =  {b_l   ,0  ,0 };

 double b[3] =  {b_u   ,1  ,1 };





 
 for(int i=0 ; i<numi ; ++i )
{ 

          zit=zi[i];
        xit=xi[i];
       Q2it=Q2i[i];
       phtit=phti[i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_N,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

UNPOLARISED_PIP[i]=valunpo1;

 

}  

}


void UNPOLARISED_N_PIM ( int numi   ,  double zi[] ,double xi[] ,double Q2i[] , double phti[]  ) 
{ 
 


 Sit=S_Jlab12;

 double a[3] =  {b_l   ,0  ,0 };

 double b[3] =  {b_u   ,1  ,1 };





 
 for(int i=0 ; i<numi ; ++i )
{ 

          zit=zi[i];
        xit=xi[i];
       Q2it=Q2i[i];
       phtit=phti[i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_N,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

UNPOLARISED_PIM[i]=valunpo1;

 

}  

}




double pop_u(  double x,  double Q2  )
{
  double Q= sqrt(Q2);
  double pdf_a[13];
  hoppetEval(x, Q, pdf_a);
 return pdf_a[6+2]/x;
 //  return ffu (1,1 ,x,Q2) ;

  }





double pop_d(   double x,  double Q2  )
{
  double Q= sqrt(Q2);
double pdf_a[13];
  hoppetEval(x, Q, pdf_a);
    return pdf_a[6-2]/x;
    //    return ffd (1,1 ,x,Q2);
  
}





double popdf_dis_N_pi(double x1, double  x2  ,double b , double xi1a, double xi2a     )
{
  double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

 //double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 //double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_pi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;




  double pdfdf=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;



  return pdfuf+pdfdf;
  //  return pdfuf+pdfdf+pdfubf+pdfdbf;
}



double popdf_dis_N_pim(double x1, double  x2  ,double b  , double xi1a, double xi2a   )
{
  double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

// double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 //double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_mpi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;





  double pdfdf=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;


 return pdfuf+pdfdf;
 // return pdfuf+pdfdf+pdfubf+pdfdbf;
}




double ker1_fun_po_N_pip(double b,double Q2, double pt, double z ,double x  ,  double BNLY , double xi1a, double xi2a  )
 { 

   double funpo=popdf_dis_N_pi( x, z  , b ,  xi1a,  xi2a  );

 
 double crsunpo=Singma0_collins(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*z))*(b/(2.0*pi))*(TMath::BesselJ1(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poDIS(BNLY,b,x,z);
 return crsunpo ;
} 

double ker1_fun_po_N_pim(double b,double Q2, double pt, double z ,double x   ,  double BNLY , double xi1a, double xi2a  )
 { 

   double funpo=popdf_dis_N_pim( x, z  , b,  xi1a,  xi2a   );

 
 double crsunpo=Singma0_collins(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*z))*(b/(2.0*pi))*(TMath::BesselJ1(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poDIS(BNLY,b,x,z);
 return crsunpo ;
} 



double ker2_fun_po_pip_xz_N(const double * xi)
{
  return ker1_fun_po_N_pip(xi[0],Q2it,phtit/zit,zit,xit , BNLYit ,xi[1] ,xi[2]   );
}

double ker2_fun_po_pim_xz_N(const double * xi)
{
  return ker1_fun_po_N_pim(xi[0],Q2it,phtit/zit,zit,xit  , BNLYit ,xi[1] ,xi[2]  );
}




void POLARISED_N_PIP ( int numi   ,  double zi[] ,double xi[] ,double Q2i[] , double phti[]  ) 
{ 
 


 Sit=S_Jlab12;

 double a[3] =  {b_l   ,0  ,0 };

 double b[3] =  {b_u   ,1  ,1 };





 
 for(int i=0 ; i<numi ; ++i )
{ 

        zit=zi[i];
        xit=xi[i];
       Q2it=Q2i[i];
      phtit=phti[i];

ROOT::Math::Functor wfunpo(&ker2_fun_po_pip_xz_N,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

POLARISED_PIP[i]=valunpo1;



}  

}


void POLARISED_N_PIM ( int numi   ,  double zi[] ,double xi[] ,double Q2i[] , double phti[]  ) 
{ 
 


 Sit=S_Jlab12;

 double a[3] =  {b_l   ,0  ,0 };

 double b[3] =  {b_u   ,1  ,1 };





 
 for(int i=0 ; i<numi ; ++i )
{ 

        zit=zi[i];
        xit=xi[i];
       Q2it=Q2i[i];
      phtit=phti[i];

ROOT::Math::Functor wfunpo(&ker2_fun_po_pim_xz_N,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

POLARISED_PIM[i]=valunpo1;


}  

}


//////////////////////////////////////////////////////////////////
////////////////////// END ///////////////////////////////////////











 









 




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 double   ymax  = 12.;        //      ! max value of ln 1/x
 double   dy    = 0.1;        //     ! the internal grid spacing (smaller->higher accuarcy)
                                // ! 0.1 should provide at least 10^{-3} accuracy 
 double   Qmin  = 0.5;  //   ! smallest Q value in tabulation
 double   Qmax  = 1e+5;       // ! largest Q value in tabulation
 double   dlnlnQ = dy/4.;     // ! tabulation spacing in dlnlnQ (dy/4 recommended)
 int   nloop  = 1;            // ! the number of loops to initialise (max=3!)
 int   order  = -6;           // ! numerical interpolation order (-6 is a good choice)

 int   scheme = 5;            // ! 1=unpol-MSbar, 2=unpol-DIS, 3=Pol-MSbar, 
                                // ! 4=frag, 5=TransMsbar






double Q2val[5000],xval[5000],zval[5000],ptval[5000],yval[5000],Astat[5000],N[5000],coverage[5000],coef[3][5000];

bool VERBOSE = false; // print everything or not



// Reading data from Zhihong, returns total number of bins
int read_data(int target_flag=3, int particle_flag=1, int flag_t=0){
	//target_flag = 1->"p", 2->"d2" or 3->"3he"
	//particle_flag = 1->pip,2->pim
	//Q2_flag = 1 ~ 4
	//z_flag  = 1 ~ 4
	//flag_t: //1->Colllins, 2->Sivers,3->Pretzelosity

	TString target = "X";
	if(target_flag==1)
		target ="p";
	else if(target_flag==2)
		target ="d2";
	else if(target_flag==3)
		target ="3he";
	else{
		cerr<<"I don't know this particle flag!"<<endl;
	}
	TString particle = "X";
	if(particle_flag==1)
		particle ="pip";
	else if(particle_flag==2)
		particle ="pim";
	else{
		cerr<<"I don't know this particle flag!"<<endl;
	}
	TString filename;
	
	int ncount=0;
	
	for(int Q2_flag = 1; Q2_flag <=4; Q2_flag++){
	for(int z_flag = 1; z_flag <=4; z_flag++){
	
	filename.Form("../data/results_wider2/%s_%s_%d_%d.dat",target.Data(),particle.Data(),z_flag,Q2_flag);
	ifstream infile(filename);
	
	

	gStyle->SetOptStat(0);
	int count1,count2;
	
	
	//double temp;
	int pt_flag = -1;

	infile >> count1;
	int pt_temp,x_temp;
	while(infile >> pt_flag >> count2){
		for (int j1=0;j1<count2;j1++){
			infile >> pt_temp >> x_temp >> zval[ncount] >> Q2val[ncount] >> ptval[ncount] >> xval[ncount] >> yval[ncount] >> Astat[ncount] >> N[ncount]>>
				coverage[ncount] >> coef[0][ncount] >> coef[1][ncount] >> coef[2][ncount];
				
				

			if(pt_temp==pt_flag && x_temp== j1){

				Astat[ncount] *= coef[2-flag_t][ncount]; //coef[0]->Sivers,coef[1]->Collins, coef[2]->Pretzelosity

				//Only use the data points with err<5%
				
				if (Astat[ncount]>0.&&Astat[ncount]<0.05){
					if(VERBOSE) cout<<Form("--- bin=%d z=%d, Q=%d pt = %f, x = %f, Astat= %f",ncount,z_flag,Q2_flag, ptval[ncount],xval[ncount], Astat[ncount])<<endl;
					ncount ++;
				}
				
			}
		}
	}

	infile.close();
	}
	}
	
	return ncount-1; // total number of bins
	
}




bool GENERATE_DATA = false; // generate pseudodata 

//========================================================= main
int main(int argc, char **argv)
{
   const int long_list = 2000; // number of parameter sets generated
   int set_used = 0; // best fit
     
   double par_space[long_list][13]; // each line consists of 14 parameters


   ifstream outfile_p ("error_estimate/new_parameters.dat" ); // this is the file 

   if(outfile_p.is_open()){


   for(int j=0; j < long_list ;++j ){   	 
     outfile_p >>par_space[j][0]>>par_space[j][1]>>par_space[j][2]>>par_space[j][3]>>par_space[j][4]
     >>par_space[j][5]>>par_space[j][6]>>par_space[j][7]>>par_space[j][8]>>par_space[j][9]
     >>par_space[j][10]>>par_space[j][11]>>par_space[j][12];
   	     }
   }
   else {
    cout << "Unable to open file "; 
    return 1;
   }
   
   outfile_p.close();

// print parameters (optional)
  if(VERBOSE){
  for(int j=0; j < long_list ;++j ){  
   cout << j << " " ;
   for(int i=0; i <13 ;++i ){ 

      cout<< par_space[j][i] << " ";

    }
    cout << endl;
  }
  cout << " End parameter file "<< endl;
  } 

  // FIRST argument : DATA or NO
 // we should be able to generate pseudodata by typing collins.exe -DATA 
  if(strcmp(argv[1],"-DATA")== 0)
    {
      GENERATE_DATA = true;
    } else {
      GENERATE_DATA = false;
    }
    
// Second argument: which set to use
   set_used = strtol(argv[2],NULL,0); // argv[2] should go 1, 2, ..., longlist if 0 then best fit is used
   
   if( GENERATE_DATA) {
   
   if(VERBOSE) cout << "Pseudo data will be generated." << endl; 
   
   }

   if(VERBOSE) cout << "Set number " << set_used << " will be used for computation." << endl; 
 
   if(GENERATE_DATA){
   
    // READ DATA FROM ZHIHONG
   
	int target_flag = 3; // 1->p, 2->d2, 3->3he
	int particle_flag = 1; //1->pip, 2->pim

	int flag_t = 1; //1->Colllins, 2->Sivers,3->Pretzelosity
	
	int number_pip_bins = read_data(target_flag, particle_flag, flag_t); // READ SOLID DATA
	
	if(VERBOSE) cout << "Total number of pi+ data points is " << number_pip_bins << endl;



    // START HOPPET
    hoppetStartExtended(ymax,dy,Qmin,Qmax,dlnlnQ,nloop,order, scheme);

    list_pdf_f();
    list_ff_f();


//BEST FIT -> par_space[0][j] j = 0,..,12
   BNLYit=par_space[0][0];
   Nuit=par_space[0][1];
   Ndit=par_space[0][2];
   auit=par_space[0][3];
   adit=par_space[0][4];
   buit=par_space[0][5];
   bdit=par_space[0][6];

   Nuit_t=par_space[0][7];
   Ndit_t=par_space[0][8];
   auit_t=par_space[0][9];
   adit_t=par_space[0][10];
   buit_t=par_space[0][11];
   bdit_t=par_space[0][12];

 


   double asQ0 = as(2.4), Q0=sqrt(2.4);

   hoppetEvolve(asQ0, Q0, nloop, 1.0, heralhc_init, Q0);  



   //number_pip_bins= 3;
   //CALCULATE UNPOLARISED CROSS-SECTION IN EACH BIN
   UNPOLARISED_N_PIP ( number_pip_bins,  zval, xval, Q2val, ptval);


   //CALCULATE ASYMMETRY IN EACH BIN
   POLARISED_N_PIP ( number_pip_bins,  zval, xval, Q2val, ptval);


   //WRITE ALL DATA IN A DATA FILE

   TString filename = "solid_data_3he_pip.dat";
 
   ofstream outfile(filename);
	
   // format of the pseudo-data
   // bin z x Q2 pt unpolarised_cross-section polarised_cross-section error_polarised_cross-section
	
  for( int i = 0; i < number_pip_bins; i++){
	
   outfile << i << " " << zval[i] << " " << xval[i] << " " << Q2val[i] << " " << ptval[i] << " " << UNPOLARISED_PIP[i] << " " << POLARISED_PIP[i]/UNPOLARISED_PIP[i] << " " << POLARISED_PIP[i]/UNPOLARISED_PIP[i]*Astat[i] << endl;
	
	
   }
    
   outfile.close();
    

   particle_flag = 2; //1->pip, 2->pim

   int number_pim_bins = read_data(target_flag, particle_flag, flag_t); // READ SOLID DATA
	
   if(VERBOSE) cout << "Total number of pi- data points is " << number_pim_bins << endl;

    
    //number_pim_bins= 3;
   //CALCULATE UNPOLARISED CROSS-SECTION IN EACH BIN
   UNPOLARISED_N_PIM ( number_pim_bins,  zval, xval, Q2val, ptval);


   //CALCULATE ASYMMETRY IN EACH BIN
   POLARISED_N_PIM ( number_pim_bins,  zval, xval, Q2val, ptval);


   //WRITE ALL DATA IN A DATA FILE

   filename = "solid_data_3he_pim.dat";
 
   ofstream outfile1(filename);
	
   // format of the pseudo-data
   // bin z x Q2 pt unpolarised_cross-section polarised_cross-section error_polarised_cross-section
	
  for( int i = 0; i < number_pip_bins; i++){
	
   outfile1 << i << " " << zval[i] << " " << xval[i] << " " << Q2val[i] << " " << ptval[i] << " " << UNPOLARISED_PIM[i] << " " << POLARISED_PIM[i]/UNPOLARISED_PIM[i] << " " << POLARISED_PIM[i]/UNPOLARISED_PIM[i]*Astat[i] << endl;
	
	
   }
    
   outfile1.close();
   
   


    }

 // we will use just one set of parameters at a time
    if(!GENERATE_DATA){
    
    // read generated data first
    
    TString filename = "solid_data_3he_pip.dat";
 
 
    ifstream infile(filename);
    
    // count number of lines first
    int nlines = 0;
    
    for (string s; getline(infile,s); ) {
        ++nlines;
    }
   infile.close();
   
   infile.open(filename,std::ifstream::in);
   // count number of lines first
   int number_pip_bins = nlines ;
    
   if(VERBOSE) cout << " Number of lines in  " <<  filename << " is = " << number_pip_bins << endl;
    

   // format of the pseudo-data
   // bin z x Q2 pt unpolarised_cross-section polarised_cross-section error_polarised_cross-section 	
   for( int i = 0; i < number_pip_bins; i++){
	int nbin =0;
    infile >> nbin >> zval[i] >> xval[i] >> Q2val[i] >> ptval[i] >> UNPOLARISED_PIP[i] >> POLARISED_PIP[i] >> ERROR_POLARISED_PIP[i];
	
   }    
   infile.close();

  
  

  
  
      // START HOPPET
    hoppetStartExtended(ymax,dy,Qmin,Qmax,dlnlnQ,nloop,order, scheme);

    list_pdf_f();
    list_ff_f();


//BEST FIT -> par_space[0][j] j = 0,..,12
   BNLYit=par_space[set_used][0];
   Nuit=par_space[set_used][1];
   Ndit=par_space[set_used][2];
   auit=par_space[set_used][3];
   adit=par_space[set_used][4];
   buit=par_space[set_used][5];
   bdit=par_space[set_used][6];

   Nuit_t=par_space[set_used][7];
   Ndit_t=par_space[set_used][8];
   auit_t=par_space[set_used][9];
   adit_t=par_space[set_used][10];
   buit_t=par_space[set_used][11];
   bdit_t=par_space[set_used][12];

 


   double asQ0 = as(2.4), Q0=sqrt(2.4);

   hoppetEvolve(asQ0, Q0, nloop, 1.0, heralhc_init, Q0);  


  
    
   Sit=S_Jlab12;
   double a[3] =  {b_l   ,0  ,0 };

   double b[3] =  {b_u   ,1  ,1 };

   double chi2_pip = 0;
  
  
 
   for(int i=0 ; i<number_pip_bins ; ++i )
   { 

        zit=zval[i];
        xit=xval[i];
       Q2it=Q2val[i];
      phtit=ptval[i];

   ROOT::Math::Functor wfunpo(&ker2_fun_po_pip_xz_N,3); 
   ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
   igunpo.SetFunction(wfunpo);

   double value = igunpo.Integral(a,b);

   chi2_pip += pow((value/UNPOLARISED_PIP[i] - POLARISED_PIP[i]),2) / pow((ERROR_POLARISED_PIP[i]),2);
   }  
 
   if(VERBOSE) cout << chi2_pip << endl;
    
    


// PI- data now:
  filename = "solid_data_3he_pim.dat";
 
  infile.open(filename,std::ifstream::in);
    
    // count number of lines first
    nlines = 0;
    
    for (string s; getline(infile,s); ) {
        ++nlines;
    }
   infile.close();
   
   infile.open(filename,std::ifstream::in);
   // count number of lines first
   int number_pim_bins = nlines ;
    
   if(VERBOSE) cout << " Number of lines in  " <<  filename << " is = " << number_pip_bins << endl;
    

   // format of the pseudo-data
   // bin z x Q2 pt unpolarised_cross-section polarised_cross-section error_polarised_cross-section 	
   for( int i = 0; i < number_pip_bins; i++){
	int nbin =0;
    infile >> nbin >> zval[i] >> xval[i] >> Q2val[i] >> ptval[i] >> UNPOLARISED_PIM[i] >> POLARISED_PIM[i] >> ERROR_POLARISED_PIM[i];
	
   }    
   infile.close();
	
 
 
   double chi2_pim = 0;

 
   for(int i=0 ; i<number_pim_bins ; ++i )
   { 

        zit=zval[i];
        xit=xval[i];
       Q2it=Q2val[i];
      phtit=ptval[i];

   ROOT::Math::Functor wfunpo(&ker2_fun_po_pim_xz_N,3); 
   ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
   igunpo.SetFunction(wfunpo);

   double value = igunpo.Integral(a,b);

   chi2_pim += pow((value/UNPOLARISED_PIM[i] - POLARISED_PIM[i]),2) / pow((ERROR_POLARISED_PIM[i]),2);
   }  
   if(VERBOSE) cout << chi2_pim << endl;
   
   
   //WRITE chi2 IN A FILE
   TString filename_write; 
   filename_write.Form("chi2_%d.dat",set_used);
 
   ofstream outfile(filename_write);
	
 	
   // write number of set used, chi2 for pi-, number of points for pi-, chi2 for pi+, number of points for pi+  and the sums	
   outfile << set_used << " " << chi2_pim << " " << number_pim_bins << " " << chi2_pip << " "  << number_pip_bins << " "<< chi2_pim + chi2_pip  << " " << number_pim_bins + number_pip_bins << " " << endl;
	
	
   outfile.close();
   
   // write files with transversity at 10 GeV^2 

   double Q2 = 10;
   
   double xmin = 1.e-4;
   double xmax = 0.999;
   
   int npoints = 100;
   
   double step = (xmax-xmin)/npoints;


   filename_write.Form("transversity_u_%d.dat",set_used);
 
   ofstream outfile_u(filename_write);
      
   
   for( int i = 0; i <= npoints; i++){
    double x = xmin + i * step;
    outfile_u << x << " " << x * pop_u(x,Q2) << endl;  
   }
   
   outfile_u.close(); 
    
 
   filename_write.Form("transversity_d_%d.dat",set_used);
 
   ofstream outfile_d(filename_write);
      
   
   for( int i = 0; i <= npoints; i++){
    double x = xmin + i * step;
    outfile_d << x << " " << x * pop_d(x,Q2) << endl;  
   }
   
   outfile_d.close(); 
   
    
   }

   if(VERBOSE) cout<<"done"<<endl;

   return 0;
}
