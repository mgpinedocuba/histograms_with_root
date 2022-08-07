// including libraries

#include "TH1.h"
#include "TF1.h"
#include <cmath>

// pdf definition

double breitwigner_pdf(double *x, double *par) {
	// gamma --- par[0]
	// x0    --- par[1]
	double gammahalf = par[0]/2.0;
	return gammahalf/(TMath::Pi() * ((x[0]-par[1])*(x[0]-par[1]) + gammahalf*gammahalf));
}

// main program

void breitwigner_distribution_def() {

	// call function and set options
	TF1* efunc = new TF1("efunc",breitwigner_pdf,0.,20.,2);
	
	// set parameters, as read in above
	efunc->SetParameter(0,2.5);
	efunc->SetParameter(1,10.0);
	
	// define histogram and set options
	TH1D* h1 = new TH1D("h1","Breir-Wigner distribution; Values; Frecuency",100,0.0,20.0);

	// fill the histogram with random numbers
	for (int i = 0; i < 50000; i++) {
		h1->Fill(efunc->GetRandom());
	}

	// drawn the ditribution
	h1->Draw("hist");

}
