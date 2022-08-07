// including libraries

#include "TH1.h"
#include "TF1.h"
#include <cmath>

// pdf definition

double single(double *x, double *par) {
  return pow(sin(TMath::Pi()*par[0]*x[0])/(TMath::Pi()*par[0]*x[0]),2);
}

double nslit0(double *x,double *par){
  return pow(sin(TMath::Pi()*par[1]*x[0])/sin(TMath::Pi()*x[0]),2);
}

double nslit(double *x, double *par){
	// width   --- par[0]
	// n_slits --- par[1]
  return single(x,par) * nslit0(x,par);
}

// main program

void slits_distribution_def() {

	// call function and set options
	TF1* efunc = new TF1("efunc",nslit,-10.,+10.,2);
	
	// set parameters, as read in above
	efunc->SetParameter(0,0.2);
	efunc->SetParameter(1,2);
	
	// define histogram and set options
	TH1D* h1 = new TH1D("h1","Double slit distribution; Values; Frecuency",200,-10.0,+10.0);

	// fill the histogram with random numbers
	for (int i = 0; i < 50000; i++) {
		h1->Fill(efunc->GetRandom());
	}

	// drawn the ditribution
	h1->Draw("hist");

}
