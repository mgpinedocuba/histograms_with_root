// including libraries

#include "TH1.h"
#include "TF1.h"
#include <cmath>

// pdf definition

double normal_pdf(double *x, double *par) {
	// x0    --- par[0]
	// sigma --- par[1]
	double tmp = (x[0]-par[0])/par[1];
	return (1.0/(std::sqrt(2 * TMath::Pi()) * std::fabs(par[1]))) * std::exp(-tmp*tmp/2);
}

// main program

void normal_dist() {

	// call function and set options
	TF1* efunc = new TF1("efunc",normal_pdf,0.,20.,2);
	
	// set parameters, as read in above
	efunc->SetParameter(0,10.0);
	efunc->SetParameter(1, 2.0);
	
	// define histogram and set options
	TH1D* h1 = new TH1D("h1","Gaussian distribution; Values; Frecuency",100,0.0,20.0);

	// fill the histogram with random numbers
	for (int i = 0; i < 50000; i++) {
		h1->Fill(efunc->GetRandom());
	}

	// drawn the ditribution
	h1->Draw("hist");

}
