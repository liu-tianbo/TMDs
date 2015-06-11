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
//#include "hoppet_v1.h"
#include "/work/halla/solid/yez/TMDs/hoppet-1.1.5/include/hoppet_v1.h"
#include <ctime>



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


double Sudakov3unpoee( double b , double x, double z )
{
  return exp(-BNLYd*b*b/(x*x)-BNLYd*b*b/(z*z));
}

double Sudakov3poee(double adterm , double b , double x, double z )
{
  return exp(-BNLYd*b*b/(x*x)+adterm*b*b/(x*x)-BNLYd*b*b/(z*z)+adterm*b*b/(z*z));
}




const double euq2=4.0/9;
const double edq2=1.0/9;
const double CB=0.3894E9;

double er(double stat, double syst  )
 {return sqrt(stat*stat+ syst*syst  );   }

const int da1dim1ee=10,da1dim2ee=6;

double  data1ee[da1dim1ee][da1dim2ee]=
  {{0.0038   ,0.0204   ,0.0259  ,0.0414  , 0,  0},   
   {0.0170   ,0.0265   ,0.0341  ,0.0630  , 0,  0},
   {0.0262   ,0.0349   ,0.0412  ,0.1069  , 0,  0},
   {0.0335   ,0.0524   ,0.0784  ,0.1525  , 0,  0},
   {0.0111   ,0.0143   ,0.0134  ,0.0144  ,0.0176  ,0.0248}  ,
   {0.0124   ,0.0153   ,0.0183  ,0.0176  ,0.0232  ,0.0307}  ,
   {0.0127   ,0.0141   ,0.0226  ,0.0195  ,0.0274  ,0.0431}  ,
   {0.0103   ,0.0169   ,0.0204  ,0.0196  ,0.0274  ,0.0431}  ,
   {0.0162   ,0.0207   ,0.0285  ,0.0317  ,0.0457  ,0.0766}  ,
   {0.0237   ,0.0299   ,0.0400  ,0.0591  ,0.0726  ,0.1110}
                     
                     };
double error1ee[da1dim1ee][da1dim2ee]=
  {{er(0.0088,0.0026)   ,er(0.0047,0.0027)   ,er(0.0047,0.0029)  ,er(0.0056,0.0033)  ,0,0},
   {er(0.0047,0.0027)   ,er(0.0042,0.0029)   ,er(0.0052,0.0031)  ,er(0.0068,0.0041)  ,0,0},
   {er(0.0045,0.0029)   ,er(0.0048,0.0031)   ,er(0.0076,0.0033)  ,er(0.0129,0.0033)  ,0,0},
   {er(0.0056,0.0031)   ,er(0.0078,0.0037)   ,er(0.0133,0.0047)  ,er(0.0382,0.0086)  ,0,0},
   {er(0.0014,0.0005)   ,er(0.0012,0.0005)   ,er(0.0016,0.0006)  ,er(0.0017,0.0006)  ,er(0.0020,0.0007)  ,er(0.0012,0.0008)},
   {er(0.0012,0.0005)   ,er(0.0011,0.0006)   ,er(0.0017,0.0006)  ,er(0.0017,0.0006)  ,er(0.0019,0.0008)  ,er(0.0024,0.0008)},
   {er(0.0016,0.0006)   ,er(0.0016,0.0006)   ,er(0.0031,0.0012)  ,er(0.0029,0.0011)  ,er(0.0032,0.0018)  ,er(0.0035,0.0022)},
   {er(0.0017,0.0006)   ,er(0.0017,0.0006)   ,er(0.0029,0.0011)  ,er(0.0031,0.0011)  ,er(0.0034,0.0020)  ,er(0.0051,0.0024)},
   {er(0.0020,0.0010)   ,er(0.0019,0.0010)   ,er(0.0032,0.0019)  ,er(0.0034,0.0019)  ,er(0.0037,0.0025)  ,er(0.0062,0.0031)},
   {er(0.0026,0.0011)   ,er(0.0024,0.0011)   ,er(0.0035,0.0020)  ,er(0.0052,0.0024)  ,er(0.0061,0.0030)  ,er(0.0119,0.0039)}
   
                     };
double   zd1ee[da1dim1ee][da1dim2ee]=
  {{0.244    ,0.244    ,0.244   ,0.244   ,0, 0},
   {0.377    ,0.377    ,0.378   ,0.379   ,0, 0},
   {0.575    ,0.576    ,0.578   ,0.578   ,0, 0},
   {0.778    ,0.779    ,0.781   ,0.783   ,0, 0},
   {0.174    ,0.174    ,0.174   ,0.174   ,0.174   ,0.174},
   {0.244    ,0.244    ,0.244   ,0.244   ,0.244   ,0.244},
   {0.344    ,0.344    ,0.344   ,0.344   ,0.344   ,0.344},
   {0.444    ,0.444    ,0.444   ,0.444   ,0.444   ,0.445},
   {0.577    ,0.577    ,0.577   ,0.578   ,0.579   ,0.580},
   {0.772    ,0.772    ,0.773   ,0.774   ,0.775   ,0.776}
                           
                      };

double   xd1ee[da1dim1ee][da1dim2ee]=
  {{0.244    ,0.377    ,0.575   ,0.779   ,0, 0},
   {0.244    ,0.377    ,0.576   ,0.778   ,0, 0},
   {0.244    ,0.378    ,0.576   ,0.780   ,0, 0},
   {0.244    ,0.379    ,0.577   ,0.780   ,0, 0},
   {0.174    ,0.244    ,0.344   ,0.444   ,0.577  ,0.772},
   {0.174    ,0.244    ,0.344   ,0.444   ,0.577  ,0.772},
   {0.174    ,0.244    ,0.344   ,0.444   ,0.577  ,0.772},
   {0.174    ,0.244    ,0.344   ,0.444   ,0.578  ,0.774},
   {0.174    ,0.244    ,0.344   ,0.444   ,0.579  ,0.775},
   {0.174    ,0.244    ,0.344   ,0.445   ,0.580  ,0.776}
                      };


double  angle1ee[da1dim1ee][da1dim2ee]=
  {{0.704    ,0.708    ,0.697   ,0.701  , 0,  0},   
   {0.706    ,0.710    ,0.700   ,0.704  , 0,  0},
   {0.700    ,0.705    ,0.694   ,0.697  , 0,  0},
   {0.705    ,0.703    ,0.701   ,0.705  , 0,  0},
   {0.687    ,0.683    ,0.676   ,0.671   ,0.663   ,0.655}  ,
   {0.685    ,0.682    ,0.676   ,0.672   ,0.665   ,0.658}  ,
   {0.682    ,0.680    ,0.674   ,0.671   ,0.665   ,0.659}  ,
   {0.680    ,0.678    ,0.673   ,0.669   ,0.664   ,0.659}  ,
   {0.677    ,0.675    ,0.671   ,0.667   ,0.662   ,0.656}  ,
   {0.672    ,0.672    ,0.668   ,0.665   ,0.659   ,0.651}
                     
                     };


//////////////////////////////////////////////////////////////////////////////////////////

const int da2dim1ee=10,da2dim2ee=6;

double  data2ee[da2dim1ee][da2dim2ee]=
  {{0.0017   ,0.0091   ,0.0114  ,0.0169  ,0,0},
   {0.0075   ,0.0115   ,0.0139  ,0.0232  ,0,0},
   {0.0114   ,0.0144   ,0.0152  ,0.0346  ,0,0},
   {0.0135   ,0.0196   ,0.0251  ,0.0339  ,0,0},
   {0.0052   ,0.0066   ,0.0061  ,0.0065  ,0.0078  ,0.0105}  ,
   {0.0057   ,0.0070   ,0.0082  ,0.0077  ,0.0100  ,0.0125}  , 
   {0.0058   ,0.0063   ,0.0095  ,0.0080  ,0.0111  ,0.0166}  ,
   {0.0047   ,0.0074   ,0.0084  ,0.0078  ,0.0132  ,0.0177}  ,
   {0.0072   ,0.0090   ,0.0113  ,0.0123  ,0.0174  ,0.0270}  ,
   {0.0100   ,0.0122   ,0.0153  ,0.0216  ,0.0256  ,0.0352}  
                     };
double error2ee[da2dim1ee][da2dim2ee]=
  {{er(0.0041,0.0012)   ,er(0.0022,0.0013)   ,er(0.0022,0.0013)  ,er(0.0025,0.0015)  ,0,0},
   {er(0.0022,0.0013)   ,er(0.0019,0.0013)   ,er(0.0023,0.0014)  ,er(0.0028,0.0018)  ,0,0},
   {er(0.0020,0.0013)   ,er(0.0021,0.0014)   ,er(0.0030,0.0014)  ,er(0.0046,0.0021)  ,0,0},
   {er(0.0025,0.0015)   ,er(0.0032,0.0016)   ,er(0.0048,0.0018)  ,er(0.0135,0.0022)  ,0,0},
   {er(0.0011,0.0003)   ,er(0.0010,0.0003)   ,er(0.0014,0.0004)  ,er(0.0014,0.0004)  ,er(0.0017,0.0006)  ,er(0.0021,0.0006)},
   {er(0.0010,0.0003)   ,er(0.0009,0.0003)   ,er(0.0013,0.0004)  ,er(0.0013,0.0004)  ,er(0.0015,0.0006)  ,er(0.0019,0.0006)},
   {er(0.0014,0.0004)   ,er(0.0013,0.0004)   ,er(0.0019,0.0007)  ,er(0.0019,0.0007)  ,er(0.0022,0.0011)  ,er(0.0028,0.0012)},
   {er(0.0014,0.0004)   ,er(0.0013,0.0004)   ,er(0.0019,0.0007)  ,er(0.0022,0.0007)  ,er(0.0024,0.0011)  ,er(0.0039,0.0012)},
   {er(0.0017,0.0006)   ,er(0.0015,0.0006)   ,er(0.0022,0.0010)  ,er(0.0024,0.0011)  ,er(0.0028,0.0016)  ,er(0.0044,0.0017)},
   {er(0.0021,0.0006)   ,er(0.0019,0.0007)   ,er(0.0028,0.0011)   ,er(0.0040,0.0012)  ,er(0.0044,0.0017)  ,er(0.0083,0.0018)}
                     };



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int da3dim1ee=1,da3dim2ee=9;


double  data3ee[da3dim1ee][da3dim2ee]=
  {{-0.0020   ,0.0034   ,0.0115  ,0.0167  ,0.0224    ,0.0202   ,0.0254   ,0.0220    ,0.0212  }};

double error3ee[da3dim1ee][da3dim2ee]=
  {{er(0.0028,0.0008)   ,er(0.0017,0.0006)   ,er(0.0014,0.0011)  ,er(0.0013,0.0011)  ,er(0.0015,0.0014)  ,er(0.0018,0.0014)  ,
   er(0.0021,0.0017)   ,er(0.0021,0.0017)   ,er(0.0020,0.0017)                    }};

double   zd3ee[da3dim1ee][da3dim2ee]=
  {{0.230    ,0.231  ,0.233   ,0.239   ,0.258   ,0.302    ,0.349  ,0.406  ,0.488                           
                      }};

double   xd3ee[da3dim1ee][da3dim2ee]=
  {{0.300    ,0.299    ,0.295   ,0.289   ,0.281  ,0.276   ,0.270  ,0.262  ,0.252   
                      }};


double   pt3ee[da3dim1ee][da3dim2ee]=
  {{0.083    ,0.194    ,0.315   ,0.438   ,0.558  ,0.683   ,0.818  ,0.989  ,1.258   
                      }};
double   angle3ee[da3dim1ee][da3dim2ee]=
  {{0.685    ,0.683    ,0.680   ,0.678   ,0.677  ,0.677   ,0.677  ,0.677  ,0.678   
                      }};


const int da4dim1ee=1,da4dim2ee=9;


double  data4ee[da4dim1ee][da4dim2ee]=
  {{-0.0009   ,0.0015   ,0.0052  ,0.0076  ,0.0101    ,0.0091   ,0.0113   ,0.0096    ,0.0092  }};

double error4ee[da4dim1ee][da4dim2ee]=
  {{er(0.0023,0.0006)   ,er(0.0014,0.0004)   ,er(0.0012,0.0006)  ,er(0.0011,0.0006)  ,er(0.0012,0.0007)  ,er(0.0014,0.0007)  ,
   er(0.0016,0.0009)   ,er(0.0017,0.0009)   ,er(0.0016,0.0009)                    }};

double   zd4ee[da4dim1ee][da4dim2ee]=
  {{0.230    ,0.231  ,0.233   ,0.239   ,0.258   ,0.302    ,0.349  ,0.406  ,0.488                           
                      }};

double   xd4ee[da4dim1ee][da4dim2ee]=
  {{0.300    ,0.299    ,0.295   ,0.289   ,0.281  ,0.276   ,0.270  ,0.262  ,0.252   
                      }};


double   pt4ee[da4dim1ee][da4dim2ee]=
  {{0.083    ,0.194    ,0.315   ,0.438   ,0.558  ,0.683   ,0.818  ,0.989  ,1.258   
                      }};


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


double unpopdf_favfav_disdis(double x1, double  x2 , double xi1a, double xi2a ,double b ,int fh     )
{ 
  //fraginid_.FINI=0;
 double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

 double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf_ff=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffu(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffu(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffub(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffub(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;



  double pdfdf_ff=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffd(fh,-1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffd(fh,-1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,-1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffdb(fh,1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffdb(fh,1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;


double pdfuf_dd=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffu(fh,-1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffu(fh,-1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,-1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffub(fh,1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffub(fh,1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;



  double pdfdf_dd=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffd(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffd(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffdb(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffdb(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;

 double pdfsf_dd=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffs(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffs(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffsb(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffsb(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;



 return pdfuf_ff+pdfdf_ff+pdfuf_dd+pdfdf_dd+2*pdfsf_dd;

}


double unpopdf_favdis_disfav(double x1, double  x2 , double xi1a, double xi2a ,double b ,int fh     )
{
  // fraginid_.FINI=0;

 double bm2=1.5;

 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;

 double mu2=1.0/bs2;

 double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf_fd=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffu(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffu(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffub(fh,1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffub(fh,1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;



  double pdfdf_fd=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffd(fh,-1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffd(fh,-1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,-1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffdb(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffdb(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;


double pdfuf_df=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffu(fh,-1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffu(fh,-1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,-1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffub(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffub(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;



  double pdfdf_df=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffd(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffd(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffdb(fh,1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffdb(fh,1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;

 double pdfsf_dd=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffs(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffs(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffsb(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffsb(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;


 return pdfuf_fd+pdfdf_fd+pdfuf_df+pdfdf_df+2*pdfsf_dd;

}

double unpopdf_nonfav_nondis(double x1, double  x2 , double xi1a, double xi2a ,double b ,int fh     )
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
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffu(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffu(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   ) +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffu(fh,-1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffu(fh,-1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,-1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  )

 ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffub(fh,1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffub(fh,1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   ) +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffub(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffub(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
 )
                                                                                           ) ;



  double pdfdf=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffd(fh,-1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffd(fh,-1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,-1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   ) +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffd(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffd(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
			                             +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   ) )

  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffdb(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffdb(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   ) +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffdb(fh,1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffdb(fh,1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
 )
                                                                                           ) ;

double pdfsf_dd=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffs(fh,1,x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*ffs(fh,1,xi1,mu2)/(xi1)*(2.0/3.0*(1-z1)+4.0/3.0*(1+z1*z1)/(1-z1)*log(z1))
                                                     +as(mu2)/pi*ffg(fh,1,xi1,mu2)/xi1 *(2.0/3.0*z1 +4.0/3.0*(1+(1-z1)*(1-z1))/z1*log(z1)   )  ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*ffsb(fh,-1,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffsb(fh,-1,xi2,mu2)/(xi2)*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
		                                     +as(mu2)/pi*ffg(fh,-1,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  )
                                                                                           ) ;



 return pdfuf+pdfdf+4*pdfsf_dd;

}









double ker1_fun_unpoee_favfav_disdis(double b,double Q2, double pt, double z ,double x, double xi1a ,double xi2a )
 { 

   double crsunpo=(unpopdf_favfav_disdis(z, x ,xi1a,xi2a , b ,1 ))*(2*pi*pt)*(b/(2.0*pi))*(TMath::BesselJ0(pt*b))*
     Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3unpoee(b,z,x);
 return crsunpo ;
} 


double ker1_fun_unpoee_favdis_disfav(double b,double Q2, double pt, double z ,double x, double xi1a ,double xi2a )
 {
   double crsunpo=(unpopdf_favdis_disfav(z, x ,xi1a,xi2a , b ,1 ))*(2*pi*pt)*(b/(2.0*pi))*(TMath::BesselJ0(pt*b))*
     Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3unpoee(b,z,x);
 return crsunpo ;
} 

double ker1_fun_unpoee_nonfav_nondis(double b,double Q2, double pt, double z ,double x, double xi1a ,double xi2a )
 {
     

   double crsunpo=(unpopdf_nonfav_nondis(z, x ,xi1a,xi2a , b ,1 ))*(2*pi*pt)*(b/(2.0*pi))*(TMath::BesselJ0(pt*b))*
     Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3unpoee(b,z,x);
 return crsunpo ;
} 



double ker2_fun_unpoee_favfav_disdis(const double * xi)
{
  return ker1_fun_unpoee_favfav_disdis(xi[0],Q2it,xi[1], zit , xit , xi[2] ,xi[3]  );
}

double ker2_fun_unpoee_favdis_disfav(const double * xi)
{
  return ker1_fun_unpoee_favdis_disfav(xi[0],Q2it,xi[1], zit , xit , xi[2] ,xi[3]  );
}

double ker2_fun_unpoee_nonfav_nondis(const double * xi)
{
  return ker1_fun_unpoee_nonfav_nondis(xi[0],Q2it,xi[1], zit , xit , xi[2] ,xi[3]  );
}


double ker2_fun_unpoee_pt_favfav_disdis(const  double *  xi)
{
  return ker1_fun_unpoee_favfav_disdis(xi[0],Q2it,ptit, zit , xit  , xi[1] ,xi[2]     );
}

double ker2_fun_unpoee_pt_favdis_disfav(const  double *  xi)
{
   return ker1_fun_unpoee_favdis_disfav(xi[0],Q2it,ptit, zit , xit , xi[1] ,xi[2]  );
}


double ker2_fun_unpoee_pt_nonfav_nondis(const  double *  xi)
{
  return ker1_fun_unpoee_nonfav_nondis(xi[0],Q2it,ptit, zit , xit  , xi[1] ,xi[2]     );
}

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


double popdf_favfav_disdis(double x1, double  x2  ,double b  , double xi1a, double xi2a  )
{ 
 
  double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

 double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf_ff=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_u_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_u_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
				     ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_ub_mpi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_ub_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;



  double pdfdf_ff=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_d_mpi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_d_mpi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_db_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_db_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;


double pdfuf_dd=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_u_mpi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_u_mpi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
				     ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_ub_pi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_ub_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;




  double pdfdf_dd=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_d_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_d_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_db_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_db_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;

                                                     
 double pdfsf_dd=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_s_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_s_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_s_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_s_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;


 return pdfuf_ff+pdfdf_ff+pdfuf_dd+pdfdf_dd+2*pdfsf_dd;

}




double popdf_favdis_disfav(double x1, double  x2  ,double b  , double xi1a, double xi2a    )
{ 

 double bm2=1.5;

 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

 double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf_fd=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_u_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_u_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_ub_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_ub_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;



  double pdfdf_fd=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_d_mpi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_d_mpi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_db_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_db_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;


double pdfuf_df=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_u_mpi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_u_mpi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_ub_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_ub_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;




  double pdfdf_df=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_d_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_d_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_db_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_db_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;



double pdfsf_dd=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_s_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_s_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_s_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_s_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;


 return pdfuf_fd+pdfdf_fd+pdfuf_df+pdfdf_df+2*pdfsf_dd;

}

double popdf_nonfav_nondis(double x1, double  x2  ,double b , double xi1a, double xi2a    )
{ 

 

 double bm2=1.5;

 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

 double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 double z1=x1/xi1;
 double z2=x2/xi2;



double pdfuf=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_u_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_u_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                     +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_u_mpi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_u_mpi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                    )

 ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_ub_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_ub_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                     +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_ub_mpi(x2,mu2)/(1-x2) 
			                             +as(mu2)/pi*pof_ub_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
 
			   )                                                                                     ) ;



  double pdfdf=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_d_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_d_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                     +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_d_mpi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_d_mpi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                    )

 ) *
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_db_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_db_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                     +
                          ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_db_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_db_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
			   )
                                                                                           ) ;



double pdfsf_dd=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_s_pi(x1,mu2)/(1-x1) 
                                                     +as(mu2)/pi*pof_s_pi(xi1,mu2)/(xi1)*(4.0/3.0*(2.0*z1)/(1-z1)*log(z1))
                                                      ) *
				      ((1+as(mu2)/pi/3.0*(pi*pi-8.0 ) )*pof_s_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_s_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;




 return pdfuf+pdfdf+4*pdfsf_dd;

}




// double popdf_favfav_disdis(double x1, double  x2  ,double b     )
// { 
 
//   double bm2=1.5;
 
//  double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



//  double mu2=1.0/bs2;



//  double pdfuf_ff=euq2*(pof_u_pi(x1,mu2) ) *(pof_ub_mpi(x2,mu2)) ;



//  double pdfdf_ff=edq2*(pof_d_mpi(x1,mu2)) *(pof_db_pi(x2,mu2))  ;


//  double pdfuf_dd=euq2*(pof_u_mpi(x1,mu2)) *(pof_ub_pi(x2,mu2))  ;




//  double pdfdf_dd=edq2*(pof_d_pi(x1,mu2)) *(pof_db_mpi(x2,mu2)) ;                                                          



//  return pdfuf_ff+pdfdf_ff+pdfuf_dd+pdfdf_dd;

// }


// double popdf_favdis_disfav(double x1, double  x2  ,double b      )
// {  

//  double bm2=1.5;

//  double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



//  double mu2=1.0/bs2;



//  double pdfuf_fd=euq2*(pof_u_pi(x1,mu2)) *(pof_ub_pi(x2,mu2)) ;



//  double pdfdf_fd=edq2*(pof_d_mpi(x1,mu2))*(pof_db_mpi(x2,mu2)) ;


// double pdfuf_df=euq2*(pof_u_mpi(x1,mu2)) *(pof_ub_mpi(x2,mu2)) ;




//   double pdfdf_df=edq2*(pof_d_pi(x1,mu2) ) *(pof_db_pi(x2,mu2)) ;



//  return pdfuf_fd+pdfdf_fd+pdfuf_df+pdfdf_df;

// }

// double popdf_nonfav_nondis(double x1, double  x2  ,double b     )
// { 


//  double bm2=1.5;

//  double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



//  double mu2=1.0/bs2;



//  double pdfuf=euq2*(pof_u_pi(x1,mu2)+ pof_u_mpi(x1,mu2)) *(pof_ub_pi(x2,mu2)+pof_ub_mpi(x2,mu2) ) ;



//   double pdfdf=euq2*(pof_d_pi(x1,mu2)+pof_d_mpi(x1,mu2)) *(pof_db_pi(x2,mu2)+pof_db_mpi(x2,mu2) ) ;





//  return pdfuf+pdfdf;

// }


double ker1_fun_po1ee_favfav_disdis(double b,double Q2, double pt , double z , double x  ,double BNLY , double xi1a, double xi2a   )
{
 double crspo=(2*pi*pt)*(b*b/4.0)*(b/(2.0*pi))*(gsl_sf_bessel_Jnu(2,pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poee(BNLY,b,z,x)*popdf_favfav_disdis(z,x  , b ,  xi1a,  xi2a    );
 return crspo ;
} 

double ker1_fun_po1ee_favdis_disfav(double b,double Q2, double pt , double z , double x  ,double BNLY , double xi1a, double xi2a )
{
 double crspo=(2*pi*pt)*(b*b/4.0)*(b/(2.0*pi))*(gsl_sf_bessel_Jnu(2,pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poee(BNLY,b,z,x)*popdf_favdis_disfav(z,x  , b   ,  xi1a,  xi2a    );
 return crspo ;
} 

double ker1_fun_po1ee_nonfav_nondis(double b,double Q2, double pt , double z , double x  ,double BNLY  , double xi1a, double xi2a  )
{
 double crspo=(2*pi*pt)*(b*b/4.0)*(b/(2.0*pi))*(gsl_sf_bessel_Jnu(2,pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poee(BNLY,b,z,x)*popdf_nonfav_nondis(z,x , b   ,  xi1a,  xi2a   );
 return crspo ;
} 



double ker2_fun_poee_favfav_disdis(const double * xi)
{
  return ker1_fun_po1ee_favfav_disdis(xi[0],Q2it,xi[1], zit , xit , BNLYit ,xi[2] ,xi[3]  );
}


double ker2_fun_poee_favdis_disfav(const double * xi)
{
  return ker1_fun_po1ee_favdis_disfav(xi[0],Q2it,xi[1], zit , xit , BNLYit ,xi[2] ,xi[3]   );
}


double ker2_fun_poee_nonfav_nondis( const double * xi)
{
  return ker1_fun_po1ee_nonfav_nondis(xi[0],Q2it,xi[1], zit , xit , BNLYit ,xi[2] ,xi[3]   );
}

double ker2_fun_poee_pt_favfav_disdis( const   double *  xi)
{
  return ker1_fun_po1ee_favfav_disdis(xi[0],Q2it,ptit, zit , xit , BNLYit ,xi[1] ,xi[2]  );
}

double ker2_fun_poee_pt_favdis_disfav( const  double *  xi)
{
  return ker1_fun_po1ee_favdis_disfav(xi[0],Q2it,ptit, zit , xit , BNLYit ,xi[1] ,xi[2]    );
}

double ker2_fun_poee_pt_nonfav_nondis(const   double *  xi)
{
  return ker1_fun_po1ee_nonfav_nondis(xi[0],Q2it,ptit, zit , xit , BNLYit ,xi[1] ,xi[2]    );
}


 
double resee[100][18][50];
double unpo_UL[20][20][2];
double unpo_UC[20][20][2];
double unpo_UL_pt[20][20][2];
double unpo_UC_pt[20][20][2];

void unpo_UL_r ( int  numj ,int numi  ,double Q2in  ,  double zi[][da1dim2ee] ,double vali[][da1dim2ee]) 
{ 
  Q2it=Q2in;





 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,3.5 ,1   ,1 };
 







 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (vali[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=vali[j][i];

ROOT::Math::Functor wfunpo_favfav_disdis(&ker2_fun_unpoee_favfav_disdis,4);  
ROOT::Math::Functor wfunpo_favdis_disfav(&ker2_fun_unpoee_favdis_disfav,4);


ROOT::Math::IntegratorMultiDim igunpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
ROOT::Math::IntegratorMultiDim igunpo_favdis_disfav(ROOT::Math::IntegrationMultiDim::kADAPTIVE);


igunpo_favfav_disdis.SetFunction(wfunpo_favfav_disdis);
igunpo_favdis_disfav.SetFunction(wfunpo_favdis_disfav);

double valunpo1_favfav_disdis = igunpo_favfav_disdis.Integral(a,b);
double valunpo1_favdis_disfav = igunpo_favdis_disfav.Integral(a,b);


unpo_UL[j][i][0]=valunpo1_favfav_disdis;
unpo_UL[j][i][1]=valunpo1_favdis_disfav;

// cout<<valunpo1_favfav_disdis<<","<<valunpo1_favdis_disfav<<endl;

}  
 // cout<<"////////////////////////////////////////////////////////"<<endl;
}
}



void unpo_UC_r ( int  numj ,int numi , double Q2in  ,   double zi[][da1dim2ee] ,double vali[][da1dim2ee]) 
{ 
 Q2it=Q2in; 


 


 double a[4] =  {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,3.5 ,1   ,1 };
 

 







 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (vali[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=vali[j][i];

ROOT::Math::Functor wfunpo_favfav_disdis(&ker2_fun_unpoee_favfav_disdis,4);  
ROOT::Math::Functor wfunpo_nonfav_nondis(&ker2_fun_unpoee_nonfav_nondis,4);

 ROOT::Math::IntegratorMultiDim igunpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 
 ROOT::Math::IntegratorMultiDim igunpo_nonfav_nondis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 
 
igunpo_favfav_disdis.SetFunction(wfunpo_favfav_disdis);
igunpo_nonfav_nondis.SetFunction(wfunpo_nonfav_nondis);

double valunpo1_favfav_disdis = igunpo_favfav_disdis.Integral(a,b);
double valunpo1_nonfav_nondis = igunpo_nonfav_nondis.Integral(a,b);

unpo_UC[j][i][0]=valunpo1_favfav_disdis;
unpo_UC[j][i][1]=valunpo1_nonfav_nondis;

// cout<<valunpo1_favfav_disdis<<","<<valunpo1_nonfav_nondis<<endl;
   
} 
 // cout<<"////////////////////////////////////////////////////////"<<endl; 
}
}

void unpo_UL_pt_r( int  numj ,int numi , double Q2in , double zi[][da3dim2ee] ,  double vali[][da3dim2ee], double pti[][da3dim2ee]) 
{ 

  Q2it=Q2in;
 
//double chiv=0;
 
double a[3] = {b_l       ,0   ,0 };

 double b[3] = {b_u     ,1   ,1 };
 







 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (vali[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=vali[j][i];   
     ptit= pti[j][i]/zi[j][i];

 ROOT::Math::Functor wfunpo_favfav_disdis(&ker2_fun_unpoee_pt_favfav_disdis,3);  
 ROOT::Math::Functor wfunpo_favdis_disfav(&ker2_fun_unpoee_pt_favdis_disfav,3);


ROOT::Math::IntegratorMultiDim igunpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
ROOT::Math::IntegratorMultiDim igunpo_favdis_disfav(ROOT::Math::IntegrationMultiDim::kADAPTIVE);


igunpo_favfav_disdis.SetFunction(wfunpo_favfav_disdis);
igunpo_favdis_disfav.SetFunction(wfunpo_favdis_disfav);


   
double valunpo1_favfav_disdis = igunpo_favfav_disdis.Integral(a,b);
double valunpo1_favdis_disfav = igunpo_favdis_disfav.Integral(a,b);

unpo_UL_pt[j][i][0]=valunpo1_favfav_disdis;
unpo_UL_pt[j][i][1]=valunpo1_favdis_disfav;

//cout<<valunpo1_favfav_disdis<<","<<valunpo1_favdis_disfav<<endl;

}
 // cout<<"////////////////////////////////////////////////////////"<<endl;
}
} 


void unpo_UC_pt_r ( int  numj ,int numi  , double Q2in  ,  double zi[][da4dim2ee] ,   double vali[][da4dim2ee]   ,double pti[][da4dim2ee]) 
{ 

  Q2it=Q2in; 


double a[3] = {b_l   ,0   ,0 };

 double b[3] = {b_u  ,1   ,1 };








   for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
    if (vali[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=vali[j][i];   
       ptit= pti[j][i]/zi[j][i];

ROOT::Math::Functor wfunpo_favfav_disdis(&ker2_fun_unpoee_pt_favfav_disdis,3);  
ROOT::Math::Functor wfunpo_nonfav_nondis(&ker2_fun_unpoee_pt_nonfav_nondis,3);


 ROOT::Math::IntegratorMultiDim igunpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 
 ROOT::Math::IntegratorMultiDim igunpo_nonfav_nondis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 
 

igunpo_favfav_disdis.SetFunction(wfunpo_favfav_disdis);
igunpo_nonfav_nondis.SetFunction(wfunpo_nonfav_nondis);

double valunpo1_favfav_disdis = igunpo_favfav_disdis.Integral(a,b);
double valunpo1_nonfav_nondis = igunpo_nonfav_nondis.Integral(a,b);

unpo_UC_pt[j][i][0]=valunpo1_favfav_disdis;
unpo_UC_pt[j][i][1]=valunpo1_nonfav_nondis;
 
// cout<<valunpo1_favfav_disdis<<","<<valunpo1_nonfav_nondis<<endl;

}
 // cout<<"////////////////////////////////////////////////////////"<<endl;
}
}




/////////////////////////////////////////////////////////////////

double chis1ee_UL (double* fit , int  numj ,int numi ,int fa ,double Q2in  ,  double zi[][da1dim2ee] ,
		   double vali[][da1dim2ee],double data[][da1dim2ee],double error[][da1dim2ee], int nu  ,  double  angle[][da1dim2ee] ) 
{  
  double a[4] = {b_l   ,0  ,0  ,0  };

  double b[4] = {b_u ,3.5   ,1  ,1 }; 

double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

  #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (vali[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;
            Q2it=Q2in;
          zit=zi[j][i];
        xit=vali[j][i];

ROOT::Math::Functor wfpo_favfav_disdis(&ker2_fun_poee_favfav_disdis,4);  
ROOT::Math::Functor wfpo_favdis_disfav(&ker2_fun_poee_favdis_disfav,4);


ROOT::Math::IntegratorMultiDim igpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
ROOT::Math::IntegratorMultiDim igpo_favdis_disfav(ROOT::Math::IntegrationMultiDim::kADAPTIVE);



igpo_favfav_disdis.SetFunction(wfpo_favfav_disdis);
igpo_favdis_disfav.SetFunction(wfpo_favdis_disfav);


 double valunpo1_favfav_disdis = unpo_UL[j][i][0];
 double valunpo1_favdis_disfav = unpo_UL[j][i][1];

double valpo1_favfav_disdis = igpo_favfav_disdis.Integral(a,b);
double valpo1_favdis_disfav = igpo_favdis_disfav.Integral(a,b);

 
double  val1=valpo1_favfav_disdis/valunpo1_favfav_disdis;

double  val2=valpo1_favdis_disfav/valunpo1_favdis_disfav;


   
double val=angle[j][i]*(val1-val2)/(zit*xit) ;



resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}

double chis2ee_UC (double* fit , int  numj ,int numi ,int fa , double Q2in  ,   double zi[][da1dim2ee] ,
double vali[][da1dim2ee],double data[][da1dim2ee],double error[][da1dim2ee], int nu,double angle[][da1dim2ee]) 
{ 
double chiv=0;

 double a[4] = {b_l  ,0  ,0  ,0  };

 double b[4] = {b_u ,3.5 ,1, 1  };
 
 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}


 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (vali[j][i] < 0.000001 )
 {  continue;}
   //   if (Q2i[j][i] <1.5    ) continue;
           Q2it=Q2in; 
          zit=zi[j][i];
        xit=vali[j][i];

ROOT::Math::Functor wfpo_favfav_disdis(&ker2_fun_poee_favfav_disdis,4);  
ROOT::Math::Functor wfpo_nonfav_nondis(&ker2_fun_poee_nonfav_nondis,4);


 ROOT::Math::IntegratorMultiDim igpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 
 ROOT::Math::IntegratorMultiDim igpo_nonfav_nondis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 


igpo_favfav_disdis.SetFunction(wfpo_favfav_disdis);
igpo_nonfav_nondis.SetFunction(wfpo_nonfav_nondis);



double valunpo1_favfav_disdis = unpo_UC[j][i][0];
double valunpo1_nonfav_nondis = unpo_UC[j][i][1];


double valpo1_favfav_disdis = igpo_favfav_disdis.Integral(a,b);
double valpo1_nonfav_nondis = igpo_nonfav_nondis.Integral(a,b);

 

 

 double  val1=valpo1_favfav_disdis/valunpo1_favfav_disdis;

 double  val2=valpo1_nonfav_nondis/valunpo1_nonfav_nondis;
   
 double val=angle[j][i]*(val1-val2)/(zit*xit) ;



 resee[nu][j][i]=val;
 //  cout<<val<<endl;
 
  chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


 // cout<<"data="<<data[j][i]<<endl;
 //  cout<<"val= " <<val<<endl;  
 //  cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;

  //    cout<<nu<<j<<i<<","<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}



//cout<<"TChi^2="<<chiv<<endl;
return chiv;
}

double chis3ee_pt0_UL(double* fit , int  numj ,int numi ,int fa   , double Q2in , double zi[][da3dim2ee] ,
		   double vali[][da3dim2ee],double data[][da3dim2ee],double error[][da3dim2ee] ,double pti[][da3dim2ee], int nu,double angle[][da3dim2ee]) 
{ 
 
double chiv=0;
 
 double a[3] = {b_l ,0 ,0   };

 double b[3] = {b_u ,1 ,1 };

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

    #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (vali[j][i] < 0.000001 )
   {  continue; }

   //   if (Q2i[j][i] <1.5    ) continue;
              Q2it=Q2in;
    
           zit=zi[j][i];
        xit=vali[j][i];   
       ptit= pti[j][i]/zi[j][i];

ROOT::Math::Functor wfpo_favfav_disdis(&ker2_fun_poee_pt_favfav_disdis,3);  
ROOT::Math::Functor wfpo_favdis_disfav(&ker2_fun_poee_pt_favdis_disfav,3);

ROOT::Math::IntegratorMultiDim igpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
ROOT::Math::IntegratorMultiDim igpo_favdis_disfav(ROOT::Math::IntegrationMultiDim::kADAPTIVE);

igpo_favfav_disdis.SetFunction(wfpo_favfav_disdis);
igpo_favdis_disfav.SetFunction(wfpo_favdis_disfav); 
   
 double valunpo1_favfav_disdis =unpo_UL_pt[j][i][0];
 double valunpo1_favdis_disfav =unpo_UL_pt[j][i][1];

 

 double valpo1_favfav_disdis = igpo_favfav_disdis.Integral(a,b);
 double valpo1_favdis_disfav = igpo_favdis_disfav.Integral(a,b);


//  cout<<zit<<","<<xit<<","<<ptit<<","<<j<<","<<i<<","
// <<valunpo1_favfav_disdis<<","<<valunpo1_favdis_disfav<<","<<valpo1_favfav_disdis<<","<< valpo1_favdis_disfav<<endl;

 
double  val1=valpo1_favfav_disdis/valunpo1_favfav_disdis;

double  val2=valpo1_favdis_disfav/valunpo1_favdis_disfav;
   
double val=angle[j][i]*(val1-val2)/(zit*xit) ;


  chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);
  //    cout<<nu<<j<<i<<","<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;

 resee[nu][j][i]=val;
 // cout<<val<<endl;
 
 // cout<<"data="<<data[j][i]<<endl;
 //  cout<<"val= " <<val<<endl;  
 //  cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;

 }

 }
//cout<<"TChi^2="<<chiv<<endl;

 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}


return chiv;
} 


double chis4ee_pt0_UC (double* fit , int  numj ,int numi ,int fa , double Q2in  ,  double zi[][da4dim2ee] ,
		       double vali[][da4dim2ee],double data[][da4dim2ee],double error[][da4dim2ee], double pti[][da4dim2ee], int nu ,double angle[][da4dim2ee]) 
{ 

double chiv=0;

 double a[3] = {b_l  , 0  ,0 };

 double b[3] = {b_u  ,1   ,1 };

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

  #pragma omp parallel for 


   for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
    if (vali[j][i] < 0.000001 )
    { continue;      }

   //   if (Q2i[j][i] <1.5    ) continue;
             Q2it=Q2in; 
          zit=zi[j][i];
        xit=vali[j][i];   
       ptit= pti[j][i]/zi[j][i];

 ROOT::Math::Functor wfpo_favfav_disdis(&ker2_fun_poee_pt_favfav_disdis,3);  
 ROOT::Math::Functor wfpo_nonfav_nondis(&ker2_fun_poee_pt_nonfav_nondis,3);


 ROOT::Math::IntegratorMultiDim igpo_favfav_disdis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 
 ROOT::Math::IntegratorMultiDim igpo_nonfav_nondis(ROOT::Math::IntegrationMultiDim::kADAPTIVE); 


igpo_favfav_disdis.SetFunction(wfpo_favfav_disdis);
igpo_nonfav_nondis.SetFunction(wfpo_nonfav_nondis);


double valunpo1_favfav_disdis =unpo_UC_pt[j][i][0];
double valunpo1_nonfav_nondis =unpo_UC_pt[j][i][1];




double valpo1_favfav_disdis = igpo_favfav_disdis.Integral(a,b);
double valpo1_nonfav_nondis = igpo_nonfav_nondis.Integral(a,b);
 

 double  val1=valpo1_favfav_disdis/valunpo1_favfav_disdis;

 double  val2=valpo1_nonfav_nondis/valunpo1_nonfav_nondis;
   
 double val=angle[j][i]*(val1-val2)/(zit*xit) ;


 chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);

 resee[nu][j][i]=val;

 // cout<<j<<","<<i<<","<<valunpo1_favfav_disdis<<","<<valunpo1_nonfav_nondis<<","<<valpo1_favfav_disdis<<","<< valpo1_nonfav_nondis<<endl;

 // cout<<val<<endl;

 // cout<<"data="<<data[j][i]<<endl;
 //  cout<<"val= " <<val<<endl;  
 //  cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;

 }

 }


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;

return chiv;
} 


///////////////////////////////////////////////////////////compass_pi+/////////////////////////////////////////////////////////////////////////////////



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


const int da1dim1=1,da1dim2=9;
const int th1dim1=1,th1dim2=9;

double  data1[da1dim1][da1dim2]=
                    {{-0.0647  ,-0.0039  ,0.0078  ,-0.0007 ,0.0131  ,0.0085  ,0.0018  ,0.0214  ,-0.0085    }};
double error1[da1dim1][da1dim2]=
                    {{0.0252   ,0.0124   ,0.0093  ,0.0079  ,0.0088  ,0.0111  ,0.0146  ,0.0218  ,0.0376                   }};
double  Q2d1[da1dim1][da1dim2]=
                    {{1.24     ,1.45     ,1.67    ,1.99    ,2.79    ,4.54    ,7.4     ,11.8    ,23.8                         }};
double   xd1[da1dim1][da1dim2]=
                    {{0.006469  ,0.01059  ,0.01643 ,0.02556 ,0.03967 ,0.06255 ,0.1005  ,0.1609 ,0.2781                    }};
double   zd1[da1dim1][da1dim2]=
                    {{0.29      ,0.33     ,0.35    ,0.37    ,0.39    ,0.38    ,0.37    ,0.37   ,0.36                       }};
double   yd1[da1dim1][da1dim2]=
                    {{0.65      ,0.46     ,0.34    ,0.26    ,0.23    ,0.24    ,0.25    ,0.24   , 0.28	                      }};


 const int da2dim1=1 ,da2dim2=9;
 const int th2dim1=1 ,th2dim2=9;

double  data2[da2dim1][da2dim2]=
                    {{0.0214   ,0.0000   ,-0.0050 ,-0.0028 ,-0.0044 ,-0.0044 ,0.0245  ,0.0256  ,-0.0456        
                      }};
double error2[da2dim1][da2dim2]=
                    {{0.0114   ,0.0095   ,0.0092  ,0.0099  ,0.0114  ,0.0114  ,0.0157  ,0.0173  ,0.0401
                      }};
double  Q2d2[da2dim1][da2dim2]=
                    {{3.18     ,3.14     ,3.14    ,3.23    ,3.29    ,3.36    ,3.46    ,3.61    ,4.08    
                      }};
double   phtd2[da2dim1][da2dim2]=
                    {{0.1547   ,0.2519    ,0.3496  ,0.4482  ,0.5475  ,0.6681  ,0.817   ,1.042  ,1.549    
                      }};
double   xd2[da2dim1][da2dim2]=
                    {{0.043    ,0.042     ,0.041   ,0.041   ,0.041   ,0.04    ,0.04    ,0.039  ,0.038 
                      }};
double   zd2[da2dim1][da2dim2]=
                    {{0.35     ,0.35      ,0.35    ,0.35    ,0.36    ,0.37    ,0.39    ,0.41   ,0.43 
                      }};
double   yd2[da2dim1][da2dim2]=
                   {{ 0.29,   0.29,         0.3,    0.31,    0.32,     0.33,   0.34,     0.36,    0.43	  }};


 const int da3dim1=1 ,da3dim2=9;
 const int th3dim1=1 ,th3dim2=9;

double  data3[da3dim1][da3dim2]=
                   {{0.0013   ,-0.0055  ,0.0011  ,0.0134  ,0.0089  ,0.0106  ,-0.0048 ,-0.0107  ,0    
                     }};
double error3[da3dim1][da3dim2]=
                   {{0.0078   ,0.0090   ,0.0106  ,0.0122  ,0.0109  ,0.0124  ,0.0179  ,0.0243   ,0
                     }};
double  Q2d3[da3dim1][da3dim2]=
                   {{3.43     ,3.37     ,3.33    ,3.28    ,3.19    ,3.03    ,2.74    ,2.4      ,0  
                     }};
double   zd3[da3dim1][da3dim2]=
                   {{0.2237   ,0.2737   ,0.3237  ,0.3737  ,0.4448  ,0.5646  ,0.7164  ,0.8787   ,0
                     }};
double   xd3[da3dim1][da3dim2]=
                   {{0.037    ,0.039    ,0.041   ,0.042   ,0.044   ,0.046   ,0.046   ,0.045    ,0 
                      }};
double   yd3[da3dim1][da3dim2]=
                   {{0.36,     0.34,     0.32,    0.3,     0.28,   0.25,    0.22,    0.19	                    }};

/////////////////////////////////////////////////////////////////////////compass_pi-//////////////////////////////////////////////////////////////////////

 const int da4dim1=1, da4dim2=9;
 const int th4dim1=1, th4dim2=9;

double  data4[da4dim1][da4dim2]=
                    {{0.0261   ,0.0130   ,0.0192  ,-0.0015 ,-0.0120 ,0.0154  ,0.0021 ,0.0059  ,0.0076 
                     }};
double error4[da4dim1][da4dim2]=
                    {{0.0260   ,0.0128   ,0.0098  ,0.0084  ,0.0095  ,0.0121  ,0.0164 ,0.0251  ,0.0453
                     }};
double  Q2d4[da4dim1][da4dim2]=
                    {{1.24     ,1.46     ,1.68    ,2.02    ,2.82    ,4.59    ,7.42   ,11.9    ,23.9
                     }};                                                     
double   xd4[da4dim1][da4dim2]=
                    {{0.006453 ,0.01057  ,0.01641 ,0.02552 ,0.03964 ,0.06247 ,0.1004 ,0.1607  ,0.2781
                     }};
double   zd4[da4dim1][da4dim2]=
                    {{0.29     ,0.32     ,0.35    ,0.37    ,0.38    ,0.38    ,0.36   ,0.36    ,0.35
                     }};
double   yd4[da4dim1][da4dim2]=
                    {{0.65   ,0.47      ,0.35	 ,0.27	   ,0.24  ,0.25	    ,0.25    ,0.25     ,0.28
                     }};

 const int da5dim1=1, da5dim2=9;
 const int th5dim1=1, th5dim2=9;

double  data5[da5dim1][da5dim2]=
                    {{-0.0056  ,-0.0007  ,-0.0110 ,0.0142  ,0.0034  ,0.0136  ,0.0368 ,0.0143  ,0.1183        
                     }};
double error5[da5dim1][da5dim2]=
                    {{0.0123   ,0.0102   ,0.0099  ,0.0107  ,0.0122  ,0.0124  ,0.0171 ,0.0185  ,0.0433
                     }};
double  Q2d5[da5dim1][da5dim2]=
                    {{3.05     ,3        ,3.01    ,3.08    ,3.15    ,3.23    ,3.29   ,3.42    ,3.83 
                     }};                                                    
double phtd5[da5dim1][da5dim2]=
                    {{0.1545   ,0.252    ,0.3497  ,0.4483  ,0.5475  ,0.668   ,0.8168 ,1.042   ,1.554
                     }};
double   xd5[da5dim1][da5dim2]=
                    {{0.041    ,0.04     ,0.039   ,0.039   ,0.038   ,0.038   ,0.037  ,0.036   ,0.035
                     }};
double   zd5[da5dim1][da5dim2]=
                    {{0.35     ,0.35     ,0.35    ,0.35    ,0.35    ,0.36    ,0.38   ,0.4     ,0.42
                     }};
double   yd5[da5dim1][da5dim2]=
                    {{0.29,    0.3,     0.31,     0.32,    0.33,     0.34,      0.35,       0.38,      0.43                       }};

 const int da6dim1=1, da6dim2=9;
 const int th6dim1=1, th6dim2=9;

double  data6[da6dim1][da6dim2]=
                    {{0.0140   ,0.0140   ,0.0001  ,-0.0061 ,-0.0107 ,0.0086  ,0.0121 ,-0.0214 ,0}
                    };                    
double error6[da6dim1][da6dim2]=
                    {{0.0083   ,0.0096   ,0.0113  ,0.0132  ,0.0120  ,0.0138  ,0.0199 ,0.0254  ,0}
                    };
double  Q2d6[da6dim1][da6dim2]=
                    {{3.31     ,3.25     ,3.19    ,3.13    ,3.02    ,2.81    ,2.51   ,2.21    ,0}
                    };                                                      
double   zd6[da6dim1][da6dim2]=
                    {{0.2236   ,0.2736   ,0.3236  ,0.3736  ,0.4446  ,0.5643  ,0.7171 ,0.8794  ,0 } 
                    };
double   xd6[da6dim1][da6dim2]=
                    {{0.036    ,0.038     ,0.039   ,0.04   ,0.041   ,0.042   ,0.042  ,0.041   ,0}
                     };
double   yd6[da6dim1][da6dim2]=
                    {{0.37     ,0.35	  ,0.33   ,0.31	  ,0.28	   ,0.25    ,0.22   ,0.19    ,0}
                     };

//////////////////////////////////////////////////////////////herme_PI+////////////////////////////////////////////////////////////////////////////////

const int da7dim1=1,da7dim2=9;
const int th7dim1=1,th7dim2=9;

double  data7[da7dim1][da7dim2]=
  {{0.0038   ,0.0033   ,0.0036  ,0.0071  ,0.0279  ,0.0289  ,0.0150  ,0       ,0}      
  
                      };
double error7[da7dim1][da7dim2]=
  {{er(0.0071,0.0028) ,er(0.0066,0.0023)  ,er(0.0078,0.0019)  ,er(0.0073,0.0017)  ,er(0.0070,0.0018)  ,er(0.0091,0.0027)  ,er(0.0123,0.0042) ,0  ,0 }
   
     };
double  Q2d7[da7dim1][da7dim2]=
  {{1.281    ,1.631    ,2.017   ,2.467   ,3.203   ,4.321   ,6.179   ,0       ,0     } 
    
                      };
double   xd7[da7dim1][da7dim2]=
  {{0.036     ,0.056    ,0.076   ,0.098   ,0.133   ,0.186   ,0.275   ,0      ,0   } 
   
                      };

double   zd7[da7dim1][da7dim2]=
  {{0.336     ,0.356    ,0.367   ,0.376   ,0.379   ,0.379   ,0.375   ,0      ,0   }  
   
                      };


 const int da8dim1=1 ,da8dim2=9;
 const int th8dim1=1 ,th8dim2=9;

double  data8[da8dim1][da8dim2]=
                    {{0.0140   ,0.0185    ,0.0132  ,0.0100  ,0.0107  ,0.0142  ,0.0214  ,0       ,0}              
                      };
double error8[da8dim1][da8dim2]=
  {{er(0.0071,0.0050) ,er(0.0080,0.0042)  ,er(0.0080,0.0036)  ,er(0.0075,0.0030)  ,er(0.0055,0.0022)  ,er(0.0069,0.0012)  ,er(0.0110,0.0019) ,0  ,0 }
                      };
double  Q2d8[da8dim1][da8dim2]=
                    {{2.533    ,2.530    ,2.486   ,2.415   ,2.342   ,2.303   ,2.262   ,0       ,0}       
                      };
double   phtd8[da8dim1][da8dim2]=
                    {{0.110    ,0.211     ,0.290   ,0.370   ,0.488   ,0.669   ,0.954  ,0       ,0}      
                      };
double   xd8[da8dim1][da8dim2]=
                    {{0.109     ,0.106    ,0.100   ,0.093   ,0.086   ,0.080   ,0.073   ,0      ,0 }  
   
                      };

double   zd8[da8dim1][da8dim2]=
                   {{0.341     ,0.350    ,0.355   ,0.355   ,0.360   ,0.388   ,0.453   ,0      ,0   }  
                      };



 const int da9dim1=1 ,da9dim2=9;
 const int th9dim1=1 ,th9dim2=9;

double  data9[da9dim1][da9dim2]=
                   {{0.0060   ,0.0067   ,0.0182  ,0.0106  ,0.0144  ,0.0362  ,0.0349  ,0        ,0   } 
                     };
double error9[da9dim1][da9dim2]=
  {{   er(0.0048,0.0088) ,er(0.0057,0.0085)  ,er(0.0068,0.0082)  ,er(0.0078,0.0079)  ,er(0.0100,0.0076)  ,er(0.0119,0.0073)  ,er(0.0140,0.0071) ,0  ,0}
                     };
double  Q2d9[da9dim1][da9dim2]=
                   {{2.423    ,2.428    ,2.425   ,2.418   ,2.411   ,2.400   ,2.385      ,0        ,0 } 
                     };
double   zd9[da9dim1][da9dim2]=
                   {{0.234    ,0.303    ,0.373   ,0.447   ,0.523   ,0.593   ,0.663      ,0        ,0}
                     };
double   xd9[da9dim1][da9dim2]=
                   {{0.086    ,0.094    ,0.097   ,0.099   ,0.100   ,0.101   ,0.103      ,0        ,0}
                     };

///////////////////////////////////////////////////////////////hermes_pi-/////////////////////////////////////////////////

 const int da10dim1=1, da10dim2=9;
 const int th10dim1=1, th10dim2=9;

double  data10[da10dim1][da10dim2]=
  {{0.0007   ,-0.0234  ,-0.0034 ,-0.0232 ,-0.0127 ,-0.0531 ,-0.0752   ,0       ,0      }
  
                     };
double error10[da10dim1][da10dim2]=
  {{   er(0.0077,0.0053) ,er(0.0074,0.0050)  ,er(0.0089,0.0048)  ,er(0.0085,0.0046)  ,er(0.0084,0.0042)  ,er(0.0115,0.0037)  ,er(0.0160,0.0027) ,0  ,0  }
    
                     };
double  Q2d10[da10dim1][da10dim2]=
  {{1.278    ,1.629    ,2.011   ,2.451   ,3.192   ,4.291   ,6.125  ,0       ,0      } 
  
                     };                                                     
double   xd10[da10dim1][da10dim2]=
  {{0.035    ,0.055    ,0.076   ,0.098   ,0.133   ,0.186   ,0.275  ,0       ,0}     
 
                     };
double   zd10[da10dim1][da10dim2]=
  {{0.330    ,0.350    ,0.360   ,0.367   ,0.369   ,0.367   ,0.363  ,0       ,0}     
 
                     };

 const int da11dim1=1, da11dim2=9;
 const int th11dim1=1, th11dim2=9;

double  data11[da11dim1][da11dim2]=
                    {{-0.0134  ,-0.0192  ,-0.0246 ,-0.0083 ,-0.0236 ,-0.0354 ,-0.0364 ,0       ,0             } 
                     };
double error11[da11dim1][da11dim2]=
{{   er(0.0084,0.0138) ,er(0.0096,0.0121)  ,er(0.0095,0.0107)  ,er(0.0088,0.0093)  ,er(0.0063,0.0072)  ,er(0.0081,0.0039)  ,er(0.0132,0.0008) ,0  ,0 }
};
double  Q2d11[da11dim1][da11dim2]=
                    {{2.454    ,2.445    ,2.393   ,2.314   ,2.269   ,2.265   ,2.224  ,0       ,0    } 
                     };                                                    
double phtd11[da11dim1][da11dim2]=
                    {{0.110    ,0.211    ,0.290   ,0.369   ,0.488   ,0.670   ,0.951  ,0       ,0    } 
                     };
double   xd11[da11dim1][da11dim2]=
                    {{0.106    ,0.102    ,0.096   ,0.089   ,0.083   ,0.079   ,0.072  ,0       ,0    }  
 
                     };
double   zd11[da11dim1][da11dim2]=
                    {{0.337    ,0.346    ,0.350   ,0.348   ,0.349   ,0.371   ,0.433  ,0       ,0    } 
 
                     };


 const int da12dim1=1, da12dim2=9;
 const int th12dim1=1, th12dim2=9;

double  data12[da12dim1][da12dim2]=
                    {{-0.0155  ,-0.0252  ,-0.0307 ,-0.0204 ,-0.0246 ,-0.0278  ,-0.0393 ,0       ,0 }
                    };                    
double error12[da12dim1][da12dim2]=
 {{   er(0.0055,0.0012) ,er(0.0065,0.0046)  ,er(0.0079,0.0081)  ,er(0.0093,0.0118)  ,er(0.0122,0.0156)  ,er(0.0148,0.0191)  ,er(0.0174,0.0226) ,0  ,0 }
                    };
double  Q2d12[da12dim1][da12dim2]=
                    {{2.373    ,2.356    ,2.338   ,2.332   ,2.315   ,2.263   ,2.247  ,0       ,0 }
                    };                                                      
double   zd12[da12dim1][da12dim2]=
                    {{0.233    ,0.303    ,0.373   ,0.447   ,0.523   ,0.593   ,0.663  ,0       ,0   }
                    };
double   xd12[da12dim1][da12dim2]=
                    {{0.084    ,0.091    ,0.094   ,0.096   ,0.097   ,0.096   ,0.098  ,0       ,0     } 
 
                     };






//////////////////////////////////////////////////////////////////////////////////////////////////////////////


double compass_p_data_pip_x[9][8]={
 //Collins       sigma  <Q2> 	<y>	<pT>	<x>	<z>	<W>
  // -0.0040,	0.0189,	1.25,	0.66,	0.53,	0.0064,	0.285,	13.96,
  // -0.0151,	0.0091,	1.48,	0.47,	0.52,	0.0106,	0.321,	11.77,
  // 0.0039,	0.0068,	1.74,	0.36,	0.50,	0.0164,	0.345,	10.11,
  // 0.0008,	0.0055,	2.07,	0.27,	0.49,	0.0257,	0.360,	8.72,
  // -0.0032,	0.0056,	2.74,	0.23,	0.48,	0.0399,	0.367,	7.91,
  // -0.0135,	0.0065,	4.25,	0.23,	0.48,	0.0628,	0.364,	7.76,
  // -0.0425,	0.0077,	6.69,	0.22,	0.48,	0.1010,	0.361,	7.53,
  // -0.0406,	0.0097,	10.56,	0.22,	0.48,	0.1623,	0.360,	7.21,
  // -0.0569,	0.0125,	20.85,	0.24,	0.51,	0.2892,	0.360,	6.92

  {-0.0154,	0.0179,	1.24,	0.65,	0.54,	0.0065,	0.285,	13.86},
  {-0.0125,	0.0085,	1.46,	0.47,	0.52,	0.0106,	0.321,	11.69},
  {0.0039,	0.0064,	1.71,	0.35,	0.51,	0.0164,	0.347,	10.04},
  {0.0016,	0.0052,	2.04,	0.27,	0.49,	0.0257,	0.363,	8.65},
  {-0.0092,	0.0053,	2.7,	0.23,	0.48,	0.0399,	0.37,	7.86},
  {-0.01,	0.0062,	4.2,	0.23,	0.48,	0.0627,	0.367,	7.73},
  {-0.0371,	0.0075,	6.65,	0.22,	0.48,	0.1009,	0.365,	7.52},
  {-0.0362,	0.0096,	10.48,	0.22,	0.48,	0.1621,	0.363,	7.19},
  {-0.0531,	0.0127,	20.94,	0.24,	0.51,	0.2876,	0.361,	6.94}




};

double compass_p_data_pim_x[9][8]={
  //Collins     sigma  <Q2> 	<y>	<pT>	<x>	<z>	<W>
  // -0.0276,	0.0193,	1.25,	0.66,	0.53,	0.0064,	0.286,	13.98,
  // 0.0097,	0.0094,	1.49,	0.48,	0.52,	0.0106,	0.320,	11.80,
  // 0.0084,	0.0072,	1.75,	0.36,	0.50,	0.0164,	0.343,	10.14,
  // 0.0047,	0.0058,	2.08,	0.27,	0.49,	0.0257,	0.357,	8.74,
  // 0.0065,	0.0060,	2.75,	0.23,	0.48,	0.0398,	0.362,	7.92,
  // 0.0264,	0.0071,	4.25,	0.23,	0.48,	0.0627,	0.356,	7.76,
  // 0.0327,	0.0086,	6.68,	0.22,	0.48,	0.1008,	0.351,	7.53,
  // 0.0381,	0.0112,	10.55,	0.22,	0.48,	0.1620,	0.347,	7.21,
  // 0.0646,	0.0147,	20.71,	0.24,	0.51,	0.2884,	0.344,	6.91

  {-0.0299,	0.0186,	1.24,	0.65,	0.54,	0.0064,	0.286,	13.89},
  {0.0048,	0.009,	1.47,	0.47,	0.52,	0.0106,	0.32,	11.72},
  {0.0118,	0.0069,	1.72,	0.35,	0.5,	0.0164,	0.344,	10.07},
  {0.005,	0.0056,	2.05,	0.27,	0.49,	0.0257,	0.359,	8.67},
  {0.0071,	0.0058,	2.7,	0.23,	0.48,	0.0398,	0.365,	7.87},
  {0.0248,	0.007,	4.21,	0.23,	0.48,	0.0626,	0.359,	7.73},
  {0.0292,	0.0086,	6.64,	0.22,	0.48,	0.1007,	0.353,	7.52},
  {0.0494,	0.0113,	10.48,	0.22,	0.48,	0.1619,	0.349,	7.19},
{0.0754,	0.0152,	20.77,	0.24,	0.51,	0.2867,	0.345,	6.93}





};

double compass_p_data_pip_pt[9][8]={
 //Collins      sigma  <Q2> 	<y>	<pT>	<x>	<z>	<W>
  // -0.0037,	0.0076,	3.65,	0.28,	0.15,	0.0529,	0.343,	8.64,
  // -0.0084,	0.0063,	3.60,	0.28,	0.25,	0.0521,	0.341,	8.67,
  // -0.0147,	0.0060,	3.58,	0.29,	0.35,	0.0509,	0.341,	8.77,
  // -0.0165,	0.0063,	3.66,	0.29,	0.45,	0.0510,	0.342,	8.87,
  // -0.0108,	0.0071,	3.74,	0.30,	0.55,	0.0509,	0.348,	8.97,
  // -0.0189,	0.0071,	3.83,	0.31,	0.67,	0.0507,	0.361,	9.09,
  // -0.0101,	0.0096,	3.97,	0.32,	0.82,	0.0505,	0.380,	9.24,
  // -0.0028,	0.0101,	4.21,	0.34,	1.04,	0.0505,	0.402,	9.51,
  // -0.0238,	0.0221,	4.97,	0.39,	1.56,	0.0515,	0.414,	10.28


  {-0.0097,	0.0073,	3.54,	0.28,	0.15,	0.0517,	0.346,	8.57},
  {-0.0088,	0.006,	3.49,	0.28,	0.25,	0.0507,	0.345,	8.61},
  {-0.0156,	0.0057,	3.44,	0.29,	0.35,	0.0493,	0.344,	8.73},
  {-0.0118,	0.006,	3.52,	0.29,	0.45,	0.0492,	0.345,	8.85},
  {-0.0127,	0.0068,	3.58,	0.3,	0.55,	0.0489,	0.35,	8.96},
  {-0.0133,	0.0068,	3.67,	0.31,	0.67,	0.0485,	0.363,	9.08},
  {-0.0103,	0.0091,	3.79,	0.32,	0.82,	0.0483,	0.382,	9.23},
  {0.0014,	0.0097,	4.01,	0.34,	1.04,	0.0481,	0.404,	9.5},
  {-0.0114,	0.0212,	4.69,	0.39,	1.56,	0.0483,	0.415,	10.28}







};

double compass_p_data_pim_pt[9][8]={
 //Collins      sigma  <Q2> 	<y>	<pT>	<x>	<z>	<W>
  // 0.0061,	0.0082,	3.45,	0.29,	0.15,	0.0495,	0.344,	8.73,
  // 0.0081,	0.0068,	3.40,	0.29,	0.25,	0.0486,	0.341,	8.77,
  // 0.0056,	0.0064,	3.37,	0.30,	0.35,	0.0475,	0.340,	8.89,
  // 0.0137,	0.0069,	3.47,	0.30,	0.45,	0.0477,	0.338,	9.00,
  // 0.0178,	0.0077,	3.56,	0.31,	0.55,	0.0478,	0.340,	9.10,
  // 0.0234,	0.0077,	3.65,	0.32,	0.67,	0.0476,	0.349,	9.22,
  // 0.0143,	0.0104,	3.78,	0.33,	0.82,	0.0474,	0.364,	9.37,
  // 0.0426,	0.0111,	3.96,	0.34,	1.04,	0.0469,	0.384,	9.63,
  // 0.0258,	0.0239,	4.50,	0.39,	1.56,	0.0461,	0.398,	10.37,

  {0.0081,	0.008,	3.35,	0.28,	0.15,	0.0485,	0.347,	8.66},
  {0.0096,	0.0066,	3.29,	0.29,	0.25,	0.0474,	0.344,	8.71},
  {0.0059,	0.0062,	3.26,	0.29,	0.35,	0.0462,	0.342,	8.85},
  {0.0122,	0.0067,	3.33,	0.3,	0.45,	0.0461,	0.34,	8.97},
  {0.0156,	0.0075,	3.42,	0.31,	0.55,	0.046,	0.342,	9.08},
  {0.0217,	0.0075,	3.5,	0.32,	0.67,	0.0457,	0.351,	9.21},
  {0.0202,	0.0102,	3.61,	0.33,	0.82,	0.0454,	0.366,	9.36},
  {0.0358,	0.0108,	3.78,	0.34,	1.04,	0.0447,	0.386,	9.61},
  {0.0184,	0.0233,	4.26,	0.39,	1.56,	0.0435,	0.4,	10.37}





};

double compass_p_data_pip_z[9][8]={

 //Collins      sigma  <Q2> 	<y>	<pT>	<x>	<z>	<W>
  // -0.0083,	0.0048,	3.86,	0.33,	0.45,	0.0482,	0.223,	9.42,
  // -0.0123,	0.0057,	3.85,	0.32,	0.47,	0.0498,	0.273,	9.24,
  // -0.0094,	0.0068,	3.83,	0.31,	0.49,	0.0512,	0.324,	9.06,
  // -0.0190,	0.0079,	3.80,	0.29,	0.51,	0.0525,	0.374,	8.84,
  // -0.0115,	0.0070,	3.70,	0.27,	0.54,	0.0542,	0.445,	8.50,
  // -0.0120,	0.0081,	3.51,	0.24,	0.57,	0.0561,	0.565,	8.04,
  // -0.0126,	0.0117,	3.20,	0.21,	0.56,	0.0563,	0.716,	7.59,
  // -0.0356,	0.0156,	2.79,	0.19,	0.47,	0.0539,	0.878,	7.23

  {-0.0067,	0.0046,	3.71,	0.33,	0.45,	0.0464,	0.223,	9.42},
  {-0.0073,	0.0055,	3.71,	0.32,	0.47,	0.048,	0.274,	9.21},
  {-0.0082,	0.0065,	3.68,	0.31,	0.5,	0.0494,	0.324,	9.03},
  {-0.0201,	0.0076,	3.64,	0.29,	0.52,	0.0507,	0.374,	8.81},
  {-0.0162,	0.0067,	3.54,	0.27,	0.54,	0.0523,	0.445,	8.48},
  {-0.0072,	0.0077,	3.37,	0.24,	0.57,	0.0542,	0.565,	8.02},
  {-0.0155,	0.0109,	3.07,	0.21,	0.56,	0.0545,	0.716,	7.58},
  {-0.0465,	0.0147,	2.7,	0.19,	0.47,	0.0525,	0.877,	7.22}


  
};

double compass_p_data_pim_z[9][8]={

 //Collins      sigma  <Q2> 	<y>	<pT>	<x>	<z>	<W>
  // 0.0049,	0.0051,	3.71,	0.34,	0.45,	0.0461,	0.223,	9.51,
  // 0.0214,	0.0061,	3.67,	0.33,	0.48,	0.0471,	0.273,	9.34,
  // 0.0114,	0.0073,	3.62,	0.31,	0.50,	0.0480,	0.323,	9.18,
  // 0.0175,	0.0087,	3.55,	0.30,	0.52,	0.0488,	0.373,	8.97,
  // 0.0293,	0.0077,	3.43,	0.27,	0.54,	0.0501,	0.444,	8.61,
  // 0.0203,	0.0091,	3.20,	0.24,	0.55,	0.0511,	0.564,	8.12,
  // -0.0029,	0.0132,	2.84,	0.21,	0.53,	0.0502,	0.716,	7.66,
  // 0.0067,	0.0173,	2.47,	0.19,	0.43,	0.0479,	0.879,	7.28


  {0.0057,	0.005,	3.57,	0.34,	0.45,	0.0444,	0.223,	9.5},
  {0.024,	0.006,	3.54,	0.32,	0.48,	0.0455,	0.273,	9.31},
  {0.0107,	0.0071,	3.49,	0.31,	0.5,	0.0464,	0.323,	9.14},
  {0.0164,	0.0084,	3.42,	0.3,	0.52,	0.0472,	0.373,	8.92},
  {0.0235,	0.0075,	3.3,	0.27,	0.54,	0.0484,	0.444,	8.58},
  {0.021,	0.0088,	3.08,	0.24,	0.55,	0.0495,	0.564,	8.1},
  {-0.0014,	0.0127,	2.75,	0.21,	0.53,	0.0488,	0.716,	7.64},
  {0.0019,	0.0168,	2.42,	0.19,	0.43,	0.0471,	0.878,	7.27}





};


double Jlab_N_data_pip_x[4][9]={

//#   <Q^2>   <x>    <y>    <z>  <Phperp> Collins  stat. and syst. and fit usr #
  {1.38,   0.156,    0.81,    0.50,   0.435,  -0.050,   0.128,   0.029,  0.044}, 
  {1.76,   0.206,    0.78,    0.52,   0.380,   0.146,   0.143,   0.041,  0.057},   
  {2.16,   0.265,    0.75,    0.54,   0.320,  -0.050,   0.097,   0.027,  0.034},  
  {2.68,   0.349,    0.70,    0.58,   0.240,  -0.348,   0.153,   0.051,  0.109}  
  
};

double Jlab_N_data_pim_x[4][9]={

  //#   <Q^2>   <x>    <y>    <z>  <Phperp> Collins  stat. and syst. and fit usr #

  {1.38,   0.156,    0.81,    0.50,   0.435,  -0.137,  0.084,   0.023,  0.036}, 
  {1.76,   0.206,    0.78,    0.52,   0.380,  0.036,   0.114,   0.032,  0.048},  
  {2.16,   0.265,    0.75,    0.54,   0.320,  0.039,   0.067,   0.019,  0.028},  
{2.68,   0.349,    0.70,    0.58,   0.240,  0.015,   0.076,   0.021,  0.032}  


};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


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










double unpopdf_dis_P(double x1, double  x2 , double xi1a, double xi2a ,double b ,int fh  ,int ch   )
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
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(1,x1,mu2)/(1-x1) +as(mu2)/pi*pdf(1,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi*pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
                          ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffu(fh,ch,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffu(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) + 

			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(-1,x1,mu2)/(1-x1)+as(mu2)/pi* pdf(-1,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffub(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffub(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) );

 double pdfdf=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(2,x1,mu2)/(1-x1) +as(mu2)/pi*pdf(2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffd(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffd(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) + 
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(-2,x1,mu2)/(1-x1)
                                                                            +as(mu2)/pi* pdf(-2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffdb(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffdb(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) );



 return pdfuf+pdfdf;

}

double unpopdf_dis_D(double x1, double  x2 , double xi1a, double xi2a ,double b ,int fh  ,int ch   )
{ 

  //fraginid_.FINI=0;

 double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

 double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 double z1=x1/xi1;
 double z2=x2/xi2;



 double pdfuf1=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(1,x1,mu2)/(1-x1) +as(mu2)/pi*pdf(1,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
                          ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffu(fh,ch,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffu(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) + 

			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(-1,x1,mu2)/(1-x1)+as(mu2)/pi* pdf(-1,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffub(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffub(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) );

 double pdfuf2=(1-x1)*(1-x2)*euq2*(
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(2,x1,mu2)/(1-x1) +as(mu2)/pi*pdf(2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
                          ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffu(fh,ch,x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*ffu(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) + 

			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(-2,x1,mu2)/(1-x1)+as(mu2)/pi* pdf(-2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffub(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffub(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) );

 double pdfdf1=(1-x1)*(1-x2)*edq2*(
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(2,x1,mu2)/(1-x1) +as(mu2)/pi*pdf(2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffd(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffd(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) + 
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*pdf(-2,x1,mu2)/(1-x1)
                                                                            +as(mu2)/pi* pdf(-2,xi1,mu2)/xi1 *2.0/3.0*(1-z1)
                                                                            +as(mu2)/pi* pdf(0,xi1,mu2)/xi1 *1.0/2.0*(1-z1)*z1  ) *
			  ((1+as(mu2)/pi/3.0*(-8.0 ) )*ffdb(fh,ch,x2,mu2)/(1-x2)
                                                     +as(mu2)/pi*ffdb(fh,ch,xi2,mu2)/xi2*(2.0/3.0*(1-z2)+4.0/3.0*(1+z2*z2)/(1-z2)*log(z2))
                                                     +as(mu2)/pi*ffg(fh,ch,xi2,mu2)/xi2 *(2.0/3.0*z2 +4.0/3.0*(1+(1-z2)*(1-z2))/z2*log(z2)   )  ) );
double pdfdf2=(1-x1)*(1-x2)*edq2*(
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



 return pdfuf1+pdfdf1+pdfuf2+pdfdf2;

}





double Sit;



double ker1_fun_unpo_N(double b,double Q2, double pt, double z ,double x , double xi1a, double zi2a ,int cn   )
 { 

    double funpo=unpopdf_dis_N( x, z ,  xi1a, zi2a , b ,1  ,  cn   );

 
 double crsunpo=Singma0(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*pi))*(TMath::BesselJ0(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3unpoDIS(b,x,z);
 return crsunpo ;
} 


double ker1_fun_unpo_P(double b,double Q2, double pt, double z ,double x , double xi1a, double zi2a ,int cn   )
 { 

    double funpo=unpopdf_dis_P( x, z ,  xi1a, zi2a , b ,1  ,  cn   );

 
 double crsunpo=Singma0(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*pi))*(TMath::BesselJ0(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3unpoDIS(b,x,z);
 return crsunpo ;
} 


double ker1_fun_unpo_D(double b,double Q2, double pt, double z ,double x , double xi1a, double zi2a ,int cn   )
 { 

   double funpo=unpopdf_dis_D( x, z ,  xi1a, zi2a , b ,1  ,  cn   );

 
 double crsunpo=Singma0(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*pi))*(TMath::BesselJ0(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3unpoDIS(b,x,z);
 return crsunpo ;
} 


double ker2_fun_unpo_pip_xz_N(const double * xi)
{
  return ker1_fun_unpo_N(xi[0],Q2it,xi[1]/zit,zit,xit, xi[2],xi[3],1  );
}

double ker2_fun_unpo_pim_xz_N(const double * xi)
{
  return ker1_fun_unpo_N(xi[0],Q2it,xi[1]/zit,zit,xit, xi[2],xi[3],-1  );
}


double ker2_fun_unpo_pip_xz_P(const double * xi)
{
  return ker1_fun_unpo_P(xi[0],Q2it,xi[1]/zit,zit,xit, xi[2],xi[3],1  );
}

double ker2_fun_unpo_pim_xz_P(const double * xi)
{
  return ker1_fun_unpo_P(xi[0],Q2it,xi[1]/zit,zit,xit, xi[2],xi[3],-1  );
}

double ker2_fun_unpo_pip_xz_D(const double * xi)
{
  return ker1_fun_unpo_D(xi[0],Q2it,xi[1]/zit,zit,xit, xi[2],xi[3],1  );
}

double ker2_fun_unpo_pim_xz_D(const double * xi)
{
  return ker1_fun_unpo_D(xi[0],Q2it,xi[1]/zit,zit,xit, xi[2],xi[3],-1  );
}


double ker2_fun_unpo_pip_ph_P(const double * xi)
{
  return ker1_fun_unpo_P(xi[0],Q2it,phtit/zit,zit,xit, xi[1],xi[2],1  );
}

double ker2_fun_unpo_pim_ph_P(const double * xi)
{
  return ker1_fun_unpo_P(xi[0],Q2it,phtit/zit,zit,xit, xi[1],xi[2],-1  );
}

double ker2_fun_unpo_pip_ph_D(const double * xi)
{
  return ker1_fun_unpo_D(xi[0],Q2it,phtit/zit,zit,xit, xi[1],xi[2],1  );
}

double ker2_fun_unpo_pim_ph_D(const double * xi)
{
  return ker1_fun_unpo_D(xi[0],Q2it,phtit/zit,zit,xit, xi[1],xi[2],-1  );
}





double unpo_dis_x_P_pip[1][20];
double unpo_dis_z_P_pip[1][20];
double unpo_dis_ph_P_pip[1][20];

double unpo_dis_x_D_pip[1][20];
double unpo_dis_z_D_pip[1][20];
double unpo_dis_ph_D_pip[1][20];


double unpo_dis_x_P_pim[1][20];
double unpo_dis_z_P_pim[1][20];
double unpo_dis_ph_P_pim[1][20];

double unpo_dis_x_D_pim[1][20];
double unpo_dis_z_D_pim[1][20];
double unpo_dis_ph_D_pim[1][20];

double unpo_dis_x_P_pip_cop[1][20];
double unpo_dis_z_P_pip_cop[1][20];
double unpo_dis_ph_P_pip_cop[1][20];

double unpo_dis_x_P_pim_cop[1][20];
double unpo_dis_z_P_pim_cop[1][20];
double unpo_dis_ph_P_pim_cop[1][20];


double unpo_dis_x_N_pip[1][20];
double unpo_dis_x_N_pim[1][20];

const  double S_compass=160*0.94*2;
const  double S_hermes=27.6*0.94*2;
const  double S_Jlab=5.9*0.94*2;

void unpo_dis_x_N_pip_c ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]   ) 
{ 
 


 Sit=S_Jlab;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 



   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
       Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_N,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_N_pip[j][i]=valunpo1;



}  
}
}

void unpo_dis_x_N_pim_c ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]   ) 
{ 
 


 Sit=S_Jlab;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 



   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
       Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_N,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_N_pim[j][i]=valunpo1;



}  
}
}










void unpo_dis_x_P_pip_c ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]   ) 
{ 
 


 Sit=S_hermes;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 



   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
       Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_P_pip[j][i]=valunpo1;



}  
}
}

void unpo_dis_x_P_pip_copa ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]   ) 
{ 
 


 Sit=S_compass;

 double a[4] = {b_l  ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 



   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
       Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_P_pip_cop[j][i]=valunpo1;



}  
}
}



void unpo_dis_x_D_pip_c( int  numj ,int numi  ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]   ) 
{ 




 Sit=S_compass;

 double a[4] = {b_l   ,0   ,0   ,0 };

 double b[4] = {b_u ,1  ,1   ,1 };
 





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
 Q2it=Q2i[j][i];


ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_D,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_D_pip[j][i]=valunpo1;

}  
}
}

void unpo_dis_z_P_pip_c( int  numj ,int numi   ,  double zi[][9] ,double xi[][9]  ,double Q2i[][9]  ) 
{ 
 



 Sit=S_hermes;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
 Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_z_P_pip[j][i]=valunpo1;



}  
}
}

void unpo_dis_z_P_pip_copa( int  numj ,int numi   ,  double zi[][9] ,double xi[][9]  ,double Q2i[][9]  ) 
{ 
 



 Sit=S_compass;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
 Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_z_P_pip_cop[j][i]=valunpo1;



}  
}
}



void unpo_dis_z_D_pip_c ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9]  ,double Q2i[][9]  ) 
{ 




 Sit=S_compass;

 double a[4] = {b_l   ,0   ,0   ,0 };

 double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
 Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_xz_D,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_z_D_pip[j][i]=valunpo1;

}  
}
}

void unpo_dis_ph_P_pip_c ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9] , double phi[][9]    ) 
{ 
 



 Sit=S_hermes;

 double a[3] = {b_l   ,0   ,0   };

  double b[3] = {b_u ,1  ,1   };
 





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
         phtit=phi[j][i];
 Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_ph_P,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_ph_P_pip[j][i]=valunpo1;

}  
}
}

void unpo_dis_ph_P_pip_copa ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9] , double phi[][9]    ) 
{ 
 



 Sit=S_compass;

 double a[3] = {b_l   ,0   ,0   };

  double b[3] = {b_u ,1  ,1   };
 





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
         phtit=phi[j][i];
 Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_ph_P,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_ph_P_pip_cop[j][i]=valunpo1;

}  
}
}

void unpo_dis_ph_D_pip_c( int  numj ,int numi   ,  double zi[][9] ,double xi[][9]  ,double Q2i[][9], double phi[][9]  ) 
{ 
 



 Sit=S_compass;

 double a[3] = {b_l   ,0   ,0   };

 double b[3] = {b_u ,1  ,1    };
 





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
         phtit=phi[j][i];
 Q2it=Q2i[j][i];


ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pip_ph_D,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_ph_D_pip[j][i]=valunpo1;

}  
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void unpo_dis_x_P_pim_c ( int  numj ,int numi  ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]  ) 
{ 
  



 Sit=S_hermes;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
        
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_P_pim[j][i]=valunpo1;

}  
}
}

void unpo_dis_x_P_pim_copa ( int  numj ,int numi  ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]  ) 
{ 
  



 Sit=S_compass;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
        
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_P_pim_cop[j][i]=valunpo1;

}  
}
}

void unpo_dis_x_D_pim_c( int  numj ,int numi   ,  double zi[][9] ,double xi[][9]  ,double Q2i[][9]  ) 
{ 
 



 Sit=S_compass;

 double a[4] = {b_l   ,0   ,0   ,0 };

 double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_D,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_x_D_pim[j][i]=valunpo1;

}  
}
}

void unpo_dis_z_P_pim_c( int  numj ,int numi  ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]  ) 
{ 
 



 Sit=S_hermes;

 double a[4] = {b_l  ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
         Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_z_P_pim[j][i]=valunpo1;

}  
}
}

void unpo_dis_z_P_pim_copa( int  numj ,int numi  ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]  ) 
{ 
 



 Sit=S_compass;

 double a[4] = {b_l   ,0   ,0   ,0 };

  double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
         Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_P,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_z_P_pim_cop[j][i]=valunpo1;

}  
}
}

void unpo_dis_z_D_pim_c ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]  ) 
{ 
  



 Sit=S_compass;

 double a[4] = {b_l   ,0   ,0   ,0 };

 double b[4] = {b_u ,1  ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_xz_D,4); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_z_D_pim[j][i]=valunpo1;

}  
}
}

void unpo_dis_ph_P_pim_c ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]  ,double phi[][9] ) 
{ 
 



 Sit=S_hermes;

 double a[3] = {b_l      ,0   ,0 };

  double b[3] = {b_u   ,1   ,1 };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
         phtit=phi[j][i];
         Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_ph_P,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);
double valunpo1 = igunpo.Integral(a,b);

unpo_dis_ph_P_pim[j][i]=valunpo1;

}  
}
}

void unpo_dis_ph_P_pim_copa ( int  numj ,int numi   ,  double zi[][9] ,double xi[][9] ,double Q2i[][9]  ,double phi[][9] ) 
{ 
 



 Sit=S_compass;

 double a[3] = {b_l      ,0   ,0 };

  double b[3] = {b_u   ,1   ,1 };
 





 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
         phtit=phi[j][i];
         Q2it=Q2i[j][i];


ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_ph_P,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_ph_P_pim_cop[j][i]=valunpo1;

}  
}
}


void unpo_dis_ph_D_pim_c( int  numj ,int numi   ,  double zi[][9] ,double xi[][9]  ,double Q2i[][9]  ,double phi[][9]  ) 
{ 
 



 Sit=S_compass;

 double a[3] = {b_l   ,0   ,0   };

 double b[3] = {b_u ,1  ,1    };
 






 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 
   if (xi[j][i] < 0.000001 ) break;
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
        xit=xi[j][i];
        phtit=phi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfunpo(&ker2_fun_unpo_pim_ph_D,3); 
ROOT::Math::IntegratorMultiDim igunpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igunpo.SetFunction(wfunpo);

double valunpo1 = igunpo.Integral(a,b);

unpo_dis_ph_D_pim[j][i]=valunpo1;

}  
}
}





/////////////////////////////////////////////////////////////////////////////////////////









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












double popdf_dis_P_pi(double x1, double  x2  ,double b , double xi1a, double xi2a     )
{
  double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

// double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 //double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_pi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;

 // double pdfubf=(1-x1)*(1-x2)*euq2*(
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_ub(x1,mu2)/(1-x1)   ) *
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_ub_pi(x2,mu2)/(1-x2) 
 // 				                     +as(mu2)/pi*pof_ub_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                          ) ;



  double pdfdf=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;

 // double pdfdbf=(1-x1)*(1-x2)*edq2*(
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_db(x1,mu2)/(1-x1)   ) *
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_db_pi(x2,mu2)/(1-x2) 
 //                                                     +as(mu2)/pi*pof_db_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;

  return pdfuf+pdfdf;
  //  return pdfuf+pdfdf+pdfubf+pdfdbf;
}



double popdf_dis_P_pim(double x1, double  x2  ,double b  , double xi1a, double xi2a   )
{
  double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

// double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 //double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_mpi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;

 // double pdfubf=(1-x1)*(1-x2)*euq2*(
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_ub(x1,mu2)/(1-x1)   ) *
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_ub_mpi(x2,mu2)/(1-x2) 
 // 				                     +as(mu2)/pi*pof_ub_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;



  double pdfdf=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;

 // double pdfdbf=(1-x1)*(1-x2)*edq2*(
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_db(x1,mu2)/(1-x1)   ) *
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_db_mpi(x2,mu2)/(1-x2) 
 //                                                     +as(mu2)/pi*pof_db_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;

 return pdfuf+pdfdf;
 // return pdfuf+pdfdf+pdfubf+pdfdbf;
}


double popdf_dis_D_pi(double x1, double  x2  ,double b  , double xi1a, double xi2a    )
{
  double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

// double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 //double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf1=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_pi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;

 // double pdfubf1=(1-x1)*(1-x2)*euq2*(
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_ub(x1,mu2)/(1-x1)   ) *
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_ub_pi(x2,mu2)/(1-x2) 
 // 				                     +as(mu2)/pi*pof_ub_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;

double pdfuf2=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_pi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;

 // double pdfubf2=(1-x1)*(1-x2)*euq2*(
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_db(x1,mu2)/(1-x1)   ) *
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_ub_pi(x2,mu2)/(1-x2) 
 // 				                     +as(mu2)/pi*pof_ub_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;



  double pdfdf1=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;

 // double pdfdbf1=(1-x1)*(1-x2)*edq2*(
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_db(x1,mu2)/(1-x1)   ) *
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_db_pi(x2,mu2)/(1-x2) 
 //                                                     +as(mu2)/pi*pof_db_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;

  double pdfdf2=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_pi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;

 // double pdfdbf2=(1-x1)*(1-x2)*edq2*(
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_ub(x1,mu2)/(1-x1)   ) *
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_db_pi(x2,mu2)/(1-x2) 
 //                                                     +as(mu2)/pi*pof_db_pi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;


 return pdfuf1+pdfdf1+pdfuf2+pdfdf2;
 // return pdfuf1+pdfdf1+pdfubf1+pdfdbf1+pdfuf2+pdfdf2+pdfubf2+pdfdbf2;
}



double popdf_dis_D_pim(double x1, double  x2  ,double b  , double xi1a, double xi2a    )
{
  double bm2=1.5;
 
 double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



 double mu2=1.0/bs2;

// double xi1=(1-x1)*xi1a+x1;
 double xi2=(1-x2)*xi2a+x2;

 //double z1=x1/xi1;
 double z2=x2/xi2;

 double pdfuf1=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_mpi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;

 // double pdfubf1=(1-x1)*(1-x2)*euq2*(
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_ub(x1,mu2)/(1-x1)   ) *
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_ub_mpi(x2,mu2)/(1-x2) 
 // 				                     +as(mu2)/pi*pof_ub_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;

double pdfuf2=(1-x1)*(1-x2)*euq2*(
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_u_mpi(x2,mu2)/(1-x2) 
				                     +as(mu2)/pi*pof_u_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )                          
                                                                                           ) ;

 // double pdfubf2=(1-x1)*(1-x2)*euq2*(
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_db(x1,mu2)/(1-x1)   ) *
 // 				     ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_ub_mpi(x2,mu2)/(1-x2) 
 // 				                     +as(mu2)/pi*pof_ub_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;



  double pdfdf1=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_d(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;

 // double pdfdbf1=(1-x1)*(1-x2)*edq2*(
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_db(x1,mu2)/(1-x1)   ) *
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_db_mpi(x2,mu2)/(1-x2) 
 //                                                     +as(mu2)/pi*pof_db_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;

  double pdfdf2=(1-x1)*(1-x2)*edq2*(
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_u(x1,mu2)/(1-x1)   ) *
				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_d_mpi(x2,mu2)/(1-x2) 
                                                     +as(mu2)/pi*pof_d_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
		                                      )
                                                                                           ) ;

 // double pdfdbf2=(1-x1)*(1-x2)*edq2*(
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pop_ub(x1,mu2)/(1-x1)   ) *
 // 				      ((1+as(mu2)/pi/3.0*(-8.0 ) )*pof_db_mpi(x2,mu2)/(1-x2) 
 //                                                     +as(mu2)/pi*pof_db_mpi(xi2,mu2)/(xi2)*(4.0/3.0*(2.0*z2)/(1-z2)*log(z2))
 // 		                                      )
 //                                                                                           ) ;


   return pdfuf1+pdfdf1+pdfuf2+pdfdf2;
 // return pdfuf1+pdfdf1+pdfubf1+pdfdbf1+pdfuf2+pdfdf2+pdfubf2+pdfdbf2;
}




// double popdf_dis_P_pi(double x1, double  x2  ,double b     )
// {
//   double bm2=1.5;
 
//  double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;

// double mu2=1.0/bs2;

//  double pdfuf=euq2*(pop_u(x1,mu2) ) *    (pof_u_pi(x2,mu2) ) ;

//  // double pdfubf=euq2*(pop_ub(x1,mu2) ) *  (pof_ub_pi(x2,mu2) ) ;

//   double pdfdf=edq2*(pop_d(x1,mu2) ) *    (pof_d_pi(x2,mu2)  ) ;

//   // double pdfdbf=edq2*(pop_db(x1,mu2) ) *   (pof_db_pi(x2,mu2)  ) ;

//  return pdfuf+pdfdf
//    //+pdfubf+pdfdbf
// ;
// }



// double popdf_dis_P_pim(double x1, double  x2  ,double b     )
// {
//   double bm2=1.5;
 
//  double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;

//  double mu2=1.0/bs2;

//  double pdfuf=euq2*(pop_u(x1,mu2)) *  (pof_u_mpi(x2,mu2) ) ;

//  // double pdfubf=euq2*(pop_ub(x1,mu2)) *(pof_ub_mpi(x2,mu2)) ;

//  double pdfdf=edq2*(pop_d(x1,mu2)) * (pof_d_mpi(x2,mu2) ) ;

//  // double pdfdbf=edq2*(pop_db(x1,mu2)) *(pof_db_mpi(x2,mu2)) ;

//  return pdfuf+pdfdf
//    //+pdfubf+pdfdbf
// ;
// }


// double popdf_dis_D_pi(double x1, double  x2  ,double b   )
// {
//   double bm2=1.5;
 
//  double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;

//  double mu2=1.0/bs2;

//  double pdfuf1=euq2*(pop_u(x1,mu2)) *  (pof_u_pi(x2,mu2) ) ;

//  // double pdfubf1=euq2*(pop_ub(x1,mu2) ) * (pof_ub_pi(x2,mu2) ) ;

// double pdfuf2=euq2*(pop_d(x1,mu2) ) *  (pof_u_pi(x2,mu2)   ) ;

// // double pdfubf2=euq2*(pop_db(x1,mu2) ) *  (pof_ub_pi(x2,mu2)   ) ;

//   double pdfdf1=edq2*(pop_d(x1,mu2)) *   (pof_d_pi(x2,mu2) ) ;

//   // double pdfdbf1=edq2*(pop_db(x1,mu2)) *  (pof_db_pi(x2,mu2)  ) ;

//   double pdfdf2=edq2*(pop_u(x1,mu2) ) *  (pof_d_pi(x2,mu2)  ) ;

//   // double pdfdbf2=edq2*(pop_ub(x1,mu2) ) *   (pof_db_pi(x2,mu2)  ) ;

//  return pdfuf1+pdfdf1+pdfuf2+pdfdf2
//    //+pdfubf1+pdfdbf1+pdfubf2+pdfdbf2
// ;
// }



// double popdf_dis_D_pim(double x1, double  x2  ,double b      )
// {
//   double bm2=1.5;
 
//  double bs2= b*b/(1+b*b/(bm2*bm2) )/C1/C1;



//  double mu2=1.0/bs2;



//  double pdfuf1=euq2*(pop_u(x1,mu2) ) *  (pof_u_mpi(x2,mu2)  ) ;

//  // double pdfubf1=euq2*(pop_ub(x1,mu2) ) *   (pof_ub_mpi(x2,mu2)  ) ;

// double pdfuf2=euq2*(pop_d(x1,mu2) ) *   (pof_u_mpi(x2,mu2)   ) ;

// // double pdfubf2=euq2*( pop_db(x1,mu2)  ) *  (pof_ub_mpi(x2,mu2)  ) ;

//   double pdfdf1=edq2*(pop_d(x1,mu2) ) *  (pof_d_mpi(x2,mu2)  ) ;

//   // double pdfdbf1=edq2*(pop_db(x1,mu2) ) *  (pof_db_mpi(x2,mu2) ) ;

//   double pdfdf2=edq2*(pop_u(x1,mu2) ) *   (pof_d_mpi(x2,mu2)   ) ;

//   // double pdfdbf2=edq2*(pop_ub(x1,mu2) ) *   (pof_db_mpi(x2,mu2)    ) ;

//  return pdfuf1+pdfdf1+pdfuf2+pdfdf2
//    //+pdfubf1+pdfdbf1+pdfubf2+pdfdbf2
// ;
// }



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






double ker1_fun_po_D_pip(double b,double Q2, double pt, double z ,double x   ,  double BNLY , double xi1a, double xi2a )
 { 

   double funpo=popdf_dis_D_pi( x, z  , b ,  xi1a,  xi2a  );

 
 double crsunpo=Singma0_collins(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*z))*(b/(2.0*pi))*(TMath::BesselJ1(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poDIS(BNLY,b,x,z);
 return crsunpo ;
} 

double ker1_fun_po_D_pim(double b,double Q2, double pt, double z ,double x   ,  double BNLY , double xi1a, double xi2a )
 { 

   double funpo=popdf_dis_D_pim( x, z  , b ,  xi1a,  xi2a   );

 
 double crsunpo=Singma0_collins(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*z))*(b/(2.0*pi))*(TMath::BesselJ1(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poDIS(BNLY,b,x,z);
 return crsunpo ;
} 



double ker1_fun_po_P_pip(double b,double Q2, double pt, double z ,double x  ,  double BNLY , double xi1a, double xi2a  )
 { 

   double funpo=popdf_dis_P_pi( x, z  , b ,  xi1a,  xi2a  );

 
 double crsunpo=Singma0_collins(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*z))*(b/(2.0*pi))*(TMath::BesselJ1(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poDIS(BNLY,b,x,z);
 return crsunpo ;
} 

double ker1_fun_po_P_pim(double b,double Q2, double pt, double z ,double x   ,  double BNLY , double xi1a, double xi2a  )
 { 

   double funpo=popdf_dis_P_pim( x, z  , b,  xi1a,  xi2a   );

 
 double crsunpo=Singma0_collins(Q2,Sit,x)*(funpo)*(2*pi*pt/z)*(b/(2.0*z))*(b/(2.0*pi))*(TMath::BesselJ1(pt*b))*
   Sudakov1(Q2,b)*Sudakov2(Q2,b)*Sudakov3poDIS(BNLY,b,x,z);
 return crsunpo ;
} 


double ker2_fun_po_pip_xz_N(const double * xi)
{
  return ker1_fun_po_N_pip(xi[0],Q2it,xi[1]/zit,zit,xit , BNLYit ,xi[2] ,xi[3]   );
}

double ker2_fun_po_pim_xz_N(const double * xi)
{
  return ker1_fun_po_N_pim(xi[0],Q2it,xi[1]/zit,zit,xit  , BNLYit ,xi[2] ,xi[3]  );
}


double ker2_fun_po_pip_xz_P(const double * xi)
{
  return ker1_fun_po_P_pip(xi[0],Q2it,xi[1]/zit,zit,xit , BNLYit ,xi[2] ,xi[3]   );
}

double ker2_fun_po_pim_xz_P(const double * xi)
{
  return ker1_fun_po_P_pim(xi[0],Q2it,xi[1]/zit,zit,xit  , BNLYit ,xi[2] ,xi[3]  );
}



double ker2_fun_po_pip_xz_D(const double * xi)
{
  return ker1_fun_po_D_pip(xi[0],Q2it,xi[1]/zit,zit,xit  , BNLYit ,xi[2] ,xi[3]  );
}

double ker2_fun_po_pim_xz_D(const double * xi)
{
  return ker1_fun_po_D_pim(xi[0],Q2it,xi[1]/zit,zit,xit  , BNLYit ,xi[2] ,xi[3]  );
}


double ker2_fun_po_pip_ph_P(const double * xi)
{
  return ker1_fun_po_P_pip(xi[0],Q2it,phtit/zit,zit,xit  , BNLYit ,xi[1] ,xi[2]  );
}

double ker2_fun_po_pim_ph_P(const double * xi)
{
  return ker1_fun_po_P_pim(xi[0],Q2it,phtit/zit,zit,xit  , BNLYit ,xi[1] ,xi[2]  );
}

double ker2_fun_po_pip_ph_D(const double * xi)
{
  return ker1_fun_po_D_pip(xi[0],Q2it,phtit/zit,zit,xit  , BNLYit ,xi[1] ,xi[2]  );
}

double ker2_fun_po_pim_ph_D(const double * xi)
{
  return ker1_fun_po_D_pim(xi[0],Q2it,phtit/zit,zit,xit  , BNLYit ,xi[1] ,xi[2] );
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double a[4] = {b_l   ,0,0,0 };

double b[4] = {b_u ,1,1,1  };



double chisdis_x_N_Jlab_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
				double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu  ,double y[][9]  ) 
{ 
 Sit=S_Jlab;

double chiv=0;

double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_xz_N,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);


 double valunpo1 = unpo_dis_x_N_pip[j][i];


double valpo1 = igpo.Integral(a,b);


// double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));

 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_x_N_Jlab_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
   Sit=S_Jlab;


double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_xz_N,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_x_N_pim[j][i];


double valpo1 = igpo.Integral(a,b);

// double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}













double chisdis_x_D_compass_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
				double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu  ,double y[][9]  ) 
{ 
 Sit=S_compass;

double chiv=0;

double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_xz_D,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);


 double valunpo1 = unpo_dis_x_D_pip[j][i];


double valpo1 = igpo.Integral(a,b);


 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));

 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_x_D_compass_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
   Sit=S_compass;


double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_xz_D,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_x_D_pim[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}






double chisdis_z_D_compass_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 

 Sit=S_compass;

 

double chiv=0;


 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];


ROOT::Math::Functor wfpo(&ker2_fun_po_pip_xz_D,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_z_D_pip[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_z_D_compass_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
  

 Sit=S_compass;



double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];


ROOT::Math::Functor wfpo(&ker2_fun_po_pim_xz_D,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_z_D_pim[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}



double chisdis_ph_D_compass_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double phi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{
  Sit=S_compass;

double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];
          phtit=phi[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_ph_D,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);


 double valunpo1 = unpo_dis_ph_D_pip[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_ph_D_compass_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9],  double phi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
   Sit=S_compass;

double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

// #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];
          phtit=phi[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_ph_D,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_ph_D_pim[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}



//////////////////////////////////////////////////hermes///////////////////////////////////////////////////////////////////////////////////////////


double chisdis_x_P_hermes_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu) 
{
 Sit=S_hermes;

double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

#pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);


 double valunpo1 = unpo_dis_x_P_pip[j][i];


double valpo1 = igpo.Integral(a,b);


 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_x_P_hermes_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu) 
{ 
  Sit=S_hermes;

double chiv=0;

 double chiv_g[numj][numi];

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);


 double valunpo1 = unpo_dis_x_P_pim[j][i];


double valpo1 = igpo.Integral(a,b);


 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}






double chisdis_z_P_hermes_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu) 
{ 
 Sit=S_hermes;

double chiv=0;

 double chiv_g[numj][numi];

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);



 double valunpo1 = unpo_dis_z_P_pip[j][i];


double valpo1 = igpo.Integral(a,b);


 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_z_P_hermes_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu) 
{ 
 
 Sit=S_hermes;

double chiv=0;

 double chiv_g[numj][numi];

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_z_P_pim[j][i];


double valpo1 = igpo.Integral(a,b);


 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}



double chisdis_ph_P_hermes_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double phi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu) 
{ 
 Sit=S_hermes;

double chiv=0;

 double chiv_g[numj][numi];


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];
          phtit=phi[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_ph_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_ph_P_pip[j][i];


double valpo1 = igpo.Integral(a,b);


 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_ph_P_hermes_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9],  double phi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu) 
{ 
 Sit=S_hermes;
double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];
          phtit=phi[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_ph_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);



 double valunpo1 = unpo_dis_ph_P_pim[j][i];


double valpo1 = igpo.Integral(a,b);


 
double  val=valpo1/valunpo1;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}

//////////////////////////////////////////////////////////////compass2//////////////////////////////////



double chisdis_x_P_compass_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
 Sit=S_compass;

double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

#pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);


 double valunpo1 = unpo_dis_x_P_pip_cop[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_x_P_compass_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
 Sit=S_compass;

double chiv=0;

 double chiv_g[numj][numi];

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);


 double valunpo1 = unpo_dis_x_P_pim_cop[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}






double chisdis_z_P_compass_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
 Sit=S_compass;

double chiv=0;

 double chiv_g[numj][numi];

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);



 double valunpo1 = unpo_dis_z_P_pip_cop[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_z_P_compass_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
 Sit=S_compass;

double chiv=0;

 double chiv_g[numj][numi];

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_xz_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_z_P_pim_cop[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
 double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}



double chisdis_ph_P_compass_pip (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9] ,double phi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
  
 Sit=S_compass;


double chiv=0;

 double chiv_g[numj][numi];


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for
 

 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];
          phtit=phi[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pip_ph_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);

 double valunpo1 = unpo_dis_ph_P_pip_cop[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}


double chisdis_ph_P_compass_pim (double* fit , int  numj ,int numi ,  double zi[][9] ,
double xi[][9],  double phi[][9] ,double Q2i[][9],double data[][9],double error[][9], int nu ,double y[][9] ) 
{ 
 Sit=S_compass;

double chiv=0;

 double chiv_g[numj][numi];

for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
  chiv_g[j][i]=0;
 }}

 #pragma omp parallel for


 for(int i=0 ; i<numi ; ++i )
{
 for(int j=0 ; j<numj ; ++j )
{ 
   if (xi[j][i] < 0.000001 )
     {   continue; }
   //   if (Q2i[j][i] <1.5    ) continue;

          zit=zi[j][i];
          xit=xi[j][i];
          Q2it=Q2i[j][i];
          phtit=phi[j][i];

ROOT::Math::Functor wfpo(&ker2_fun_po_pim_ph_P,4);  
ROOT::Math::IntegratorMultiDim igpo(ROOT::Math::IntegrationMultiDim::kADAPTIVE);
igpo.SetFunction(wfpo);



 double valunpo1 = unpo_dis_ph_P_pim_cop[j][i];


double valpo1 = igpo.Integral(a,b);

 double DD=2*(1-y[j][i])/(1+(1-y[j][i])*(1-y[j][i]));
 
double  val=-valpo1/valunpo1/DD;


resee[nu][j][i]=val;
//  cout<<val<<endl;
 
chiv_g[j][i]=(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i]);


//   //  cout<<"data="<<data[j][i]<<endl;
//   cout<<"val= " <<val<<endl;  
  // cout<<"Chi^2="<<(val-data[j][i])*(val-data[j][i])/(error[j][i]*error[j][i])<<endl;
} 
 // cout<<chiv<<endl;
}


 for(int j=0 ; j<numj ; ++j )
{
 for(int i=0 ; i<numi ; ++i )
{ 

  chiv+=chiv_g[j][i];

 }}

//cout<<"TChi^2="<<chiv<<endl;
return chiv;

}











double  data13[1][9], data14[1][9] , data15[1][9], data16[1][9] ,data17[1][9] ,data18[1][9], data19[1][9],data20[1][9];
double  error13[1][9],  error14[1][9] ,  error15[1][9],  error16[1][9] , error17[1][9] , error18[1][9], error19[1][9] , error20[1][9];
double  Q2d13[1][9],  Q2d14[1][9] ,  Q2d15[1][9],  Q2d16[1][9] , Q2d17[1][9] , Q2d18[1][9] , Q2d19[1][9] , Q2d20[1][9];
double  zd13[1][9],  zd14[1][9] ,  zd15[1][9],  zd16[1][9] , zd17[1][9] , zd18[1][9], zd19[1][9] , zd20[1][9];
double  xd13[1][9],  xd14[1][9] ,  xd15[1][9],  xd16[1][9] , xd17[1][9] , xd18[1][9], xd19[1][9] , xd20[1][9];
double  phtd14[1][9],  phtd17[1][9] ;
double  yd13[1][9], yd14[1][9] , yd15[1][9], yd16[1][9] ,yd17[1][9] ,yd18[1][9],yd19[1][9] ,yd20[1][9];



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



void fcn(  Double_t *par  )
{
//time_t tstart, tend;
//tstart = time(0);

 BNLYit=par[0];
 Nuit=par[1];
 Ndit=par[2];
 auit=par[3];
 adit=par[4];
 buit=par[5];
 bdit=par[6];

 Nuit_t=par[7];
 Ndit_t=par[8];
 auit_t=par[9];
 adit_t=par[10];
 buit_t=par[11];
 bdit_t=par[12];

 // Nuit_t=0;
 // Ndit_t=0;
 // auit_t=0;
 // adit_t=0;
 // buit_t=0;
 // bdit_t=0;



  Nubit_t=0;
  Ndbit_t=0;
  aubit_t=0;
  adbit_t=0;
  bubit_t=0;
  bdbit_t=0;

 


 double asQ0 = as(2.4), Q0=sqrt(2.4);

  hoppetEvolve(asQ0, Q0, nloop, 1.0, heralhc_init, Q0);  

 // for( int i=0 ; i<10 ;++i)
 //   {
 //     cout<< pof_u_pi(  (1+i)*0.05,  3.0  )<<endl;
 //    cout<< pof_u_pi(  (1+i)*0.05,    110.0  )<<endl;

 // }

  double v[24];

   v[0]= chis1ee_UL(par,da1dim1ee , da1dim2ee,  0 ,  110.0 ,  zd1ee ,xd1ee  , data1ee , error1ee, 0, angle1ee );
  v[1]= chis2ee_UC(par,da2dim1ee , da2dim2ee,  0 , 110.0 ,   zd1ee ,xd1ee  , data2ee , error2ee, 1,angle1ee );
  v[2]= chis3ee_pt0_UL(par,da3dim1ee , da3dim2ee,  0 , 110.0,    zd3ee ,xd3ee  , data3ee , error3ee,pt3ee  , 2,angle3ee ); 
  v[3]= chis4ee_pt0_UC(par,da4dim1ee , da4dim2ee,  0 , 110.0   ,   zd4ee ,xd4ee  , data4ee , error4ee,pt4ee  , 3,angle3ee);
    v[4]= chisdis_x_D_compass_pip  (par ,1 ,9 ,zd1 ,xd1        ,Q2d1 , data1,  error1, 4 ,yd1);
    v[5]= chisdis_ph_D_compass_pip (par ,1 ,6 ,zd2 ,xd2 ,phtd2 ,Q2d2 , data2,  error2, 5 ,yd2);
    v[6]= chisdis_z_D_compass_pip  (par ,1 ,8 ,zd3 ,xd3        ,Q2d3 , data3,  error3, 6 ,yd3);
    v[7]= chisdis_x_D_compass_pim  (par ,1 ,9 ,zd4 ,xd4        ,Q2d4 , data4,  error4, 7 ,yd4);
    v[8]= chisdis_ph_D_compass_pim (par ,1 ,6 ,zd5 ,xd5 ,phtd5 ,Q2d5 , data5,  error5, 8 ,yd5);
    v[9]= chisdis_z_D_compass_pim  (par ,1 ,8 ,zd6 ,xd6        ,Q2d6 , data6,  error6, 9 ,yd6);
    v[10]=chisdis_x_P_hermes_pip   (par ,1 ,7 ,zd7 ,xd7        ,Q2d7 , data7,  error7, 10);
    v[11]=chisdis_ph_P_hermes_pip  (par ,1 ,6 ,zd8 ,xd8 ,phtd8 ,Q2d8 , data8,  error8, 11);
    v[12]=chisdis_z_P_hermes_pip   (par ,1 ,7 ,zd9 ,xd9        ,Q2d9 , data9,  error9, 12);
    v[13]=chisdis_x_P_hermes_pim   (par ,1 ,7 ,zd10,xd10       ,Q2d10, data10, error10,13);
    v[14]=chisdis_ph_P_hermes_pim  (par ,1 ,6 ,zd11,xd11,phtd11,Q2d11, data11, error11,14);
    v[15]=chisdis_z_P_hermes_pim   (par ,1 ,7 ,zd12,xd12       ,Q2d12, data12, error12,15);
    v[16]=chisdis_x_P_compass_pip  (par ,1 ,9 ,zd13,xd13       ,Q2d13, data13, error13,16 ,yd13);
    v[17]=chisdis_ph_P_compass_pip (par ,1 ,6 ,zd14,xd14,phtd14,Q2d14, data14, error14,17 ,yd14);
    v[18]=chisdis_z_P_compass_pip  (par ,1 ,8 ,zd15,xd15       ,Q2d15, data15, error15,18 ,yd15 );
    v[19]=chisdis_x_P_compass_pim  (par ,1 ,9 ,zd16,xd16       ,Q2d16, data16, error16,19 ,yd16 );
    v[20]=chisdis_ph_P_compass_pim (par ,1 ,6 ,zd17,xd17,phtd17,Q2d17, data17, error17,20 ,yd17 );
    v[21]=chisdis_z_P_compass_pim  (par ,1 ,8 ,zd18,xd18       ,Q2d18, data18, error18,21 ,yd18 );
    v[22]=chisdis_x_N_Jlab_pip     (par ,1 ,4 ,zd19,xd19       ,Q2d19, data19, error19,22 ,yd19 );
    v[23]=chisdis_x_N_Jlab_pim     (par ,1 ,4 ,zd20,xd20       ,Q2d20, data20, error20,23 ,yd20 );

   double  f1=0;

      for(int i=0 ; i<24 ; ++i )
	{f1= f1+v[i];
	  //	  cout<<i<<","<<v[i]<<endl;
}
 
   
    cout <<f1<<" "<<par[0]<<" "<<par[1]<<" "<<par[2]<<" "<<par[3]<<" "<<par[4]<<" "<<par[5] <<" "<<par[6]
    
    <<" "<<par[7]<<" "<<par[8]<<" "<<par[9]<<" "<<par[10]<<" "<<par[11]<<" "<<par[12]

// cout <<"chi^2="<<f1<<",adterm="<<par[0]<<",Nu_c="<<par[1]<<",Nd_c="<<par[2]<<",au_c="<<par[3]<<",ad_c="<<par[4]<<",bu_c="<<par[5] <<",bd_c="<<par[6]
  
//      <<",Nu_t="<<par[7]<<",Nd_t="<<par[8]<<",au_t="<<par[9]<<",ad_t="<<par[10]<<",bu_t="<<par[11]<<",bd_t="<<par[12]
   //    <<",Nub_t="<<par[13]<<",Ndb_t="<<par[14]<<",aub_t="<<par[15]<<",adb_t="<<par[16]<<",bub_t="<<par[17]<<",bdb_t="<<par[18]
                    <<endl;
    
   
//tend = time(0);

//cout << "One rountine   took " << difftime(tend, tstart) << " second(s)." << endl;
  
}

















double unpo1[9][12]={

};

double unpo2[da1dim1ee][da1dim2ee][2]={



};


double unpo3[da2dim1ee][da2dim2ee][2]={



};

double unpo4[da3dim1ee][da3dim2ee][2]={




};



double unpo5[da4dim1ee][da4dim2ee][2]={

};


int main()
{
 const int long_list=2000;
     
  double par_space[long_list][13];

 char tem[2000];

    ifstream outfile_p ("error_estimate/new_parameters.dat" );
   if(outfile_p.is_open()){


   for(int line=0 ; line<14  ;++line ){
    outfile_p.getline(tem,2000 ,'\n');
    }


   for(int j=0; j < long_list ;++j ){   	 
     outfile_p >>par_space[j][0]>>par_space[j][1]>>par_space[j][2]>>par_space[j][3]>>par_space[j][4]>>par_space[j][5]>>par_space[j][6]>>par_space[j][7]
>>par_space[j][8]>>par_space[j][9]>>par_space[j][10]>>par_space[j][11]>>par_space[j][12];
   	     }}
   else cout<< "Unable to open file ";
   outfile_p.close();


  for(int j=0; j < long_list ;++j ){  for(int i=0; i <13 ;++i ){ 

      cout<< par_space[j][i] <<endl;

    }
  }

 for(int i=0 ; i<9 ;++i  )
   {



     data13[0][i]=compass_p_data_pip_x[i][0];
        error13[0][i]=sqrt(compass_p_data_pip_x[i][1]*compass_p_data_pip_x[i][1]);
      Q2d13[0][i]=compass_p_data_pip_x[i][2];
       zd13[0][i]=compass_p_data_pip_x[i][6];
       xd13[0][i]=compass_p_data_pip_x[i][5];
       yd13[0][i]=compass_p_data_pip_x[i][3];

     data14[0][i]=compass_p_data_pip_pt[i][0];
        error14[0][i]=sqrt(compass_p_data_pip_pt[i][1]*compass_p_data_pip_pt[i][1]);
      Q2d14[0][i]=compass_p_data_pip_pt[i][2];
       zd14[0][i]=compass_p_data_pip_pt[i][6];
       xd14[0][i]=compass_p_data_pip_pt[i][5];
     phtd14[0][i]=compass_p_data_pip_pt[i][4];
       yd14[0][i]=compass_p_data_pip_pt[i][3];

     data15[0][i]=compass_p_data_pip_z[i][0];
    error15[0][i]=sqrt(compass_p_data_pip_z[i][1]*compass_p_data_pip_z[i][1]);
      Q2d15[0][i]=compass_p_data_pip_z[i][2];
       zd15[0][i]=compass_p_data_pip_z[i][6];
       xd15[0][i]=compass_p_data_pip_z[i][5];
       yd15[0][i]=compass_p_data_pip_z[i][3];


     data16[0][i]=compass_p_data_pim_x[i][0];
    error16[0][i]=sqrt(compass_p_data_pim_x[i][1]*compass_p_data_pim_x[i][1]);
      Q2d16[0][i]=compass_p_data_pim_x[i][2];
       zd16[0][i]=compass_p_data_pim_x[i][6];
       xd16[0][i]=compass_p_data_pim_x[i][5];
       yd16[0][i]=compass_p_data_pim_x[i][3];

     data17[0][i]=compass_p_data_pim_pt[i][0];
    error17[0][i]=sqrt(compass_p_data_pim_pt[i][1]*compass_p_data_pim_pt[i][1]);
      Q2d17[0][i]=compass_p_data_pim_pt[i][2];
       zd17[0][i]=compass_p_data_pim_pt[i][6];
       xd17[0][i]=compass_p_data_pim_pt[i][5];
     phtd17[0][i]=compass_p_data_pim_pt[i][4];
       yd17[0][i]=compass_p_data_pim_pt[i][3];

     data18[0][i]=compass_p_data_pim_z[i][0];
    error18[0][i]=sqrt(compass_p_data_pim_z[i][1]*compass_p_data_pim_z[i][1]);
      Q2d18[0][i]=compass_p_data_pim_z[i][2];
       zd18[0][i]=compass_p_data_pim_z[i][6];
       xd18[0][i]=compass_p_data_pim_z[i][5];
       yd18[0][i]=compass_p_data_pim_z[i][3];



  
}


 for(int i=0 ; i<4 ;++i  )
   {
  data19[0][i]=Jlab_N_data_pip_x[i][5];
    error19[0][i]=sqrt(Jlab_N_data_pip_x[i][6]*Jlab_N_data_pip_x[i][6]+Jlab_N_data_pip_x[i][7]*Jlab_N_data_pip_x[i][7]+Jlab_N_data_pip_x[i][8]*Jlab_N_data_pip_x[i][8]);
      Q2d19[0][i]=Jlab_N_data_pip_x[i][0];
       zd19[0][i]=Jlab_N_data_pip_x[i][3];
       xd19[0][i]=Jlab_N_data_pip_x[i][1];
       yd19[0][i]=Jlab_N_data_pip_x[i][2];

    data20[0][i]=Jlab_N_data_pim_x[i][5];
    error20[0][i]=sqrt(Jlab_N_data_pim_x[i][6]*Jlab_N_data_pim_x[i][6]+Jlab_N_data_pim_x[i][7]*Jlab_N_data_pim_x[i][7]+Jlab_N_data_pim_x[i][8]*Jlab_N_data_pim_x[i][8]);
      Q2d20[0][i]=Jlab_N_data_pim_x[i][0];
       zd20[0][i]=Jlab_N_data_pim_x[i][3];
       xd20[0][i]=Jlab_N_data_pim_x[i][1];
       yd20[0][i]=Jlab_N_data_pim_x[i][2];

   }



  hoppetStartExtended(ymax,dy,Qmin,Qmax,dlnlnQ,nloop,order, scheme);

  list_pdf_f();
  list_ff_f();


  //////////////////////////////////////////////////////////////////unpo_part/////////////////////////////
 


    unpo_dis_x_D_pip_c  ( 1 , 9  ,   zd1 ,xd1 ,Q2d1         ) ;
 cout<<1<<endl;
    unpo_dis_ph_D_pip_c ( 1 , 9  ,   zd2 ,xd2 ,Q2d2 ,phtd2  ) ;
 cout<<2<<endl;
    unpo_dis_z_D_pip_c  ( 1 , 9  ,   zd3 ,xd3 ,Q2d3         ) ;
 cout<<3<<endl;
    unpo_dis_x_D_pim_c  ( 1 , 9  ,   zd4 ,xd4 ,Q2d4         ) ;
 cout<<4<<endl;
    unpo_dis_ph_D_pim_c ( 1 , 9  ,   zd5 ,xd5 ,Q2d5 ,phtd5  ) ;
 cout<<5<<endl;
    unpo_dis_z_D_pim_c  ( 1 , 9  ,   zd6 ,xd6 ,Q2d6         ) ;
 cout<<6<<endl;

    /////////////////////////////////////////////////////////////////

    unpo_dis_x_P_pip_c  ( 1 , 9  ,   zd7 ,xd7 ,Q2d7         ) ;
 cout<<7<<endl;
    unpo_dis_ph_P_pip_c ( 1 , 9  ,   zd8 ,xd8 ,Q2d8 ,phtd8  ) ;
 cout<<8<<endl;
    unpo_dis_z_P_pip_c  ( 1 , 9  ,   zd9 ,xd9 ,Q2d9         ) ;
 cout<<9<<endl;
    unpo_dis_x_P_pim_c  ( 1 , 9  ,   zd10,xd10,Q2d10        ) ;
 cout<<10<<endl;
    unpo_dis_ph_P_pim_c ( 1 , 9  ,   zd11,xd11,Q2d11,phtd11 ) ;
 cout<<11<<endl;
    unpo_dis_z_P_pim_c  ( 1 , 9  ,   zd12,xd12,Q2d12        ) ;
 cout<<12<<endl;

    ////////////////////////////////////////////////////////////////

    unpo_dis_x_P_pip_copa  ( 1 , 9  ,   zd13 ,xd13 ,Q2d13         ) ;
 cout<<13<<endl;
    unpo_dis_ph_P_pip_copa ( 1 , 9  ,   zd14 ,xd14 ,Q2d14,phtd14  ) ;
 cout<<14<<endl;
    unpo_dis_z_P_pip_copa  ( 1 , 9  ,   zd15 ,xd15 ,Q2d15         ) ;
 cout<<15<<endl;
    unpo_dis_x_P_pim_copa  ( 1 , 9  ,   zd16 ,xd16 ,Q2d16        ) ;
 cout<<16<<endl;
    unpo_dis_ph_P_pim_copa ( 1 , 9  ,   zd17 ,xd17 ,Q2d17,phtd17 ) ;
 cout<<17<<endl;
    unpo_dis_z_P_pim_copa  ( 1 , 9  ,   zd18 ,xd18 ,Q2d18        ) ;
 cout<<18<<endl;


    unpo_dis_x_N_pip_c  ( 1 , 4  ,   zd19 ,xd19 ,Q2d19         ) ;
 cout<<19<<endl;
    unpo_dis_x_N_pim_c  ( 1 , 4  ,   zd20 ,xd20 ,Q2d20         ) ;

    cout<<20<<endl;

   



   
     unpo_UL_r(da1dim1ee , da1dim2ee,   110.0,  zd1ee ,xd1ee );
  cout<<21<<endl;
     unpo_UC_r(da2dim1ee , da2dim2ee,   110.0,  zd1ee ,xd1ee );
  cout<<22<<endl;
    unpo_UL_pt_r(da3dim1ee , da3dim2ee,   110.0,  zd3ee ,xd3ee ,pt3ee);
  cout<<23<<endl;
    unpo_UC_pt_r(da4dim1ee , da4dim2ee,   110.0,  zd4ee ,xd4ee ,pt4ee);
    cout<<24<<endl;
    
    
     cout <<"chi^2="<<" "<<",adterm="<<" "<<",Nu_c="<<" "<<",Nd_c="<<" "<<",au_c="<<" "<<",ad_c="<<" "<<",bu_c="<<" "<<",bd_c="<<" "   
    <<",Nu_t="<<" "<<",Nd_t="<<" "<<",au_t="<<" "<<",ad_t="<<" "<<",bu_t="<<" "<<",bd_t="<<endl;

    for(int j=0; j<long_list ;++j )
      {

	fcn( par_space[j]  );


}
  





  



cout<<"done"<<endl;

 return 0;
}
