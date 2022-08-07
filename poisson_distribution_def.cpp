#include <cmath>

// pdf definition

double poisson_pdf(double *x, double *par) {
	// mu --- par[0]
	return std::exp (x[0]*std::log(par[0]) - ROOT::Math::lgamma(x[0]+1) - par[0]);
}

// main program

void poisson_distribution_def() {

	// call function and set options
	TF1* efunc = new TF1("efunc",poisson_pdf,0.,20.,1);
	
	// set parameters, as read in above
	efunc->SetParameter(0,5);
	
	// define histogram and set options
	TH1D* h1 = new TH1D("h1","Poisson distribution; Values; Frecuency",100,0.0,20.0);

	// fill the histogram with random numbers
	for (int i = 0; i < 50000; i++) {
		h1->Fill(efunc->GetRandom());
	}

	// drawn the ditribution
	h1->Draw("hist");
}
