//========================================================= includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <cfortran.h>
#include <stdio.h>
#include <ctime>


#include <fit_sets.h>

PROTOCCALLSFSUB3(CORSET,corset,PVOID,PVOID,INT)
#define   CORSET(VCOR,CCOR,NPARAM)  CCALLSFSUB3(CORSET,corset,PVOID,PVOID,INT,VCOR,CCOR,NPARAM)
PROTOCCALLSFSUB3(CORGEN,corgen,PVOID,PVOID,INT)
#define   CORGEN(VCOR,XCOR,NPARAM)  CCALLSFSUB3(CORGEN,corgen,PVOID,PVOID,INT,VCOR,XCOR,NPARAM)

using namespace std;


double chi2_calc(double BLNY_new, double Nu_new, double Nd_new,double au_new, double ad_new, double bu_new, 
		 double bd_new, double Nu_t_new, double Nd_t_new, double au_t_new, double ad_t_new, double bu_t_new, double bd_t_new)
 {
  
   double chi2 = 220.; // PLUG YOUR FUNCTION HERE! THIS IS A DUMMY FUNCTION NOW
   return chi2;
 }
 
 
 

//========================================================= main
int main(int argc, char **argv)
{
  int    npar = 13; // number of parameters
  
  double percentile50 = 248.3; // for 249 dof

  double percentile90 = 278.0; // for 249 dof

  double Delta_chi2 = percentile90 - percentile50; // 90% C.L.

// Found by Peng:
   double Minimun_chi2 =  218.407;

// paramers [0] - mean [1] error from MINUIT
    double  BLNY[2]   =         {2.36166e-02,   7.17002e-04};  //0 
    double    Nu[2]   =         {2.61971e-01,   2.46543e-02};  //1  
    double    Nd[2]   =         {-1.95220e-01,   7.15875e-03}; //2   
    double    au[2]   =         {1.69586e+00,   7.59358e-03};  //3 
    double    ad[2]   =         {3.20601e-01,   4.01160e-02};  //4  
    double    bu[2]   =         {1.46831e-06,   5.38257e-01};  //5   
    double    bd[2]   =         {3.61390e-03,   7.93746e-01};  //6   
    double    Nu_t[2] =         {8.54376e-01,   8.65518e-02};  //7   
    double    Nd_t[2] =         {-9.99999e-01,   1.25156e-01}; //8    
    double    au_t[2] =         {6.88367e-01,   4.33534e-02};  //9   
    double    ad_t[2] =         {1.79434e+00,   3.17379e-01};  //10   
    double    bu_t[2] =         {4.81953e-02,   3.88934e-02};  //11   
    double    bd_t[2] =         {6.99676e+00,  2.64818e+00};   //12 

// parameters to generate
  double BLNY_new, Nu_new, Nd_new, au_new, ad_new, bu_new, bd_new, Nu_t_new, Nd_t_new, au_t_new, ad_t_new, bu_t_new, bd_t_new;

// correlation matrix will be here
  double correlation_matrix[npar][npar];

// read correlation matrix
  const char* CORR = "correlation_matrix.dat";
 
   ifstream in;
   in.open(CORR); // fit 

   if(!in) {
     cerr << "Unable to open file with correlation matrix! " << CORR << endl;
   } else {
     cout << "Correlation matrix: " << CORR << endl;
   }

  for (int i = 1; i <= 13; ++i) {
     for (int j = 1; j <= 13; ++j) {
      in >> correlation_matrix[i-1][j-1];
      cout << correlation_matrix[i-1][j-1] << " ";
    }
    cout << endl;
  }
  
  in.close();
// done reading  
  
  
// float should be used for CORSET and CORGEN
  float vcor[npar][npar];
  float ccor[npar][npar];
  float xcor[npar];

//  double vcor[npar][npar];
//  double ccor[npar][npar];
//  double xcor[npar];

// MAIN correlation matrix
  for (int i = 0; i < npar; i++){
    for (int j = 0; j < npar; j++){
      vcor[i][j] = correlation_matrix[i][j]; // I have to use float precision...
    }
  }
//END MAIN correlation matrix

// prepare for generation vcor->ccor:
  CORSET(vcor,ccor,npar);

//  for (int i = 0; i < npar; i++){
//    for (int j = 0; j < npar; j++){
//      cout << ccor[i][j] << " "; // I have to use float precision...
//    }
//    cout << endl;
//  }

  int   generated_set_number = 0;

// new parameters to be written in this file:
  FILE *par_write = fopen( "new_parameters.dat", "w" );

  
  do{
// Generate correlated random numbers using vcor:
    CORGEN(ccor,xcor,npar);

//    cout << xcor[0] << endl;
// Assign new parameters:    
    BLNY_new = xcor[0] * BLNY[1]  + BLNY[0];
    Nu_new   = xcor[1] * Nu[1]    + Nu[0];
    Nd_new   = xcor[2] * Nd[1]    + Nd[0];
    au_new   = xcor[3] * au[1]    + au[0]; 
    ad_new   = xcor[4] * ad[1]    + ad[0];
    bu_new   = xcor[5] * bu[1]    + bu[0];
    bd_new   = xcor[6] * bd[1]    + bd[0];
    Nu_t_new = xcor[7] * Nu_t[1]  + Nu_t[0]; 
    Nd_t_new = xcor[8] * Nd_t[1]  + Nd_t[0];
    au_t_new = xcor[9] * au_t[1]  + au_t[0];
    ad_t_new = xcor[10] * ad_t[1] + ad_t[0];
    bu_t_new = xcor[11] * bu_t[1] + bu_t[0];
    bd_t_new = xcor[12] * bd_t[1] + bd_t[0];

// Make sure that -1 < Nu_t, Nd_t < 1,    au, ad, bu, bd > 0 
    if(
    Nu_t_new > 1. || Nu_t_new < -1. ||
    Nd_t_new > 1. || Nd_t_new < -1. ||
    au_t_new < 0. || ad_t_new < 0.  ||
    bu_t_new < 0. || bd_t_new < 0.  ||
    au_new < 0.   || ad_new < 0.  ||
    bu_new < 0.   || bd_new < 0.  
    ) continue;
 
 
// Now calculate chi2 with new parameters:
   double chi2 = chi2_calc(BLNY_new, Nu_new, Nd_new, au_new, ad_new, bu_new, bd_new, Nu_t_new, Nd_t_new, au_t_new, ad_t_new, bu_t_new, bd_t_new);
 
 
// Are the new parameters within Delta_chi2 of the minimum?
    if( ( chi2 - Minimun_chi2 ) <= Delta_chi2 ){
     printf("%8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f \n",BLNY_new, Nu_new, Nd_new, au_new, ad_new, bu_new, bd_new, Nu_t_new, Nd_t_new, au_t_new, ad_t_new, bu_t_new, bd_t_new);
      //write parameter set...
      fprintf(par_write,"%8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f %8.6f \n",BLNY_new, Nu_new, Nd_new, au_new, ad_new, bu_new, bd_new, Nu_t_new, Nd_t_new, au_t_new, ad_t_new, bu_t_new, bd_t_new);      
      generated_set_number++;
    }


  } while ( generated_set_number < 2000 ); //  

   
  cout << "All "<< generated_set_number << " sets were generated." << endl;  
}



 
