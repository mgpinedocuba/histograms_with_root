// including libraries

#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

// defining functions

double poisson_pdf(double *x, double *par) {
	// mu --- par[0]
	return std::exp (x[0]*std::log(par[0]) - ROOT::Math::lgamma(x[0]+1) - par[0]);
}

double poisson_fit(double *x, double *par) {
	// mu --- par[0]
	// A  --- par[1]
	return par[1] * std::exp (x[0]*std::log(par[0]) - ROOT::Math::lgamma(x[0]+1) - par[0]);
}

// mains function

void poisson_fitting() {
	
	// Creating the Canvas
	TCanvas *c1 = new TCanvas("c1","Fitting Poisson distribution",10,10,700,500);
	c1->SetFillColor(33);
	c1->SetFrameFillColor(33);
	c1->SetGrid();

	// defining the Poisson pdf
	TF1* efunc = new TF1("efunc",poisson_pdf,0.,20.,1);
	efunc->SetParameter(0,5.0);
	
	// filling the histogram with random numbers
	// obeying the Poisson pdf
	TH1D* h1 = new TH1D("h1","Poisson distribution; Values; Frecuency",100,0.0,20.0);
	h1->SetStats(0);
	for (int i = 0; i < 50000; i++) {
		h1->Fill(efunc->GetRandom());
	}
	
	// printing the histogram
	h1->Draw();	

	// defining and setting the first fit function
	TF1 *fitFcn1 = new TF1("fitFcn1",poisson_fit,0,20,2);
	fitFcn1->SetParameters(1,1);
	fitFcn1->SetParameter(0,5);
	fitFcn1->SetParameter(1,1);

	// defining and setting the second fit function
	TF1 *fitFcn2 = new TF1("fitFcn2",poisson_fit,0,20,2);
	fitFcn2->SetParameters(1,1);
	fitFcn2->SetParameter(0,5);
	fitFcn2->SetParameter(1,1);
	
	// fiting the first function with least square
	h1->Fit("fitFcn1","N");
	
	// fiting the second function with Maximun likelihood
	h1->Fit("fitFcn2","NL");
	
	// defining and setting the fit functions
	TF1 *fit_plt1 = new TF1("fit_plt1",poisson_fit,0,20,2);
	fit_plt1->SetLineColor(kRed);
	fit_plt1->SetLineWidth(4);
	fit_plt1->SetNpx(500);
	TF1 *fit_plt2 = new TF1("fit_plt2",poisson_fit,0,20,2);
	fit_plt2->SetLineColor(kGreen);
	fit_plt2->SetLineWidth(2);
	fit_plt2->SetNpx(500);

	// getting the parameters and printing
	double par1[2];
	fitFcn1->GetParameters(par1);
	fit_plt1->SetParameters(par1);
	fit_plt1->Draw("same");
	double par2[2];
	fitFcn2->GetParameters(par2);
	fit_plt2->SetParameters(par2);
	fit_plt2->Draw("same");
	
	// setting and printing the legend
	TLegend *legend=new TLegend(0.6,0.75,0.90,0.90);
	legend->SetTextFont(50);
	legend->SetTextSize(0.035);
	legend->AddEntry(fit_plt1,"Least square fit","l");
	legend->AddEntry(fit_plt2,"Maximun likelihood fit","l");
	legend->Draw();

}
