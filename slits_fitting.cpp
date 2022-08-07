// including libraries

#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

// defining functions

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

double nslit_fit(double *x, double *par) {
	// A       --- par[0]
	// width   --- par[1]
	// n_slits --- par[2]
  return par[0] * single(x,&par[1]) * nslit0(x,&par[1]);
}

// mains function

void slits_fitting() {
	
	// Creating the Canvas
	TCanvas *c1 = new TCanvas("c1","Fitting Double slit distribution",10,10,700,500);
	c1->SetFillColor(33);
	c1->SetFrameFillColor(33);
	c1->SetGrid();

	// defining the Gaussian pdf
	TF1* efunc = new TF1("efunc",nslit,-10.,+10.,2);
	efunc->SetParameter(0,0.2);
	efunc->SetParameter(1,2);
	
	// filling the histogram with random numbers
	// obeying the Gaussian pdf
	TH1D* h1 = new TH1D("h1","Double slit distribution; Values; Frecuency",200,-10.0,10.0);
	h1->SetStats(0);
	for (int i = 0; i < 50000; i++) {
		h1->Fill(efunc->GetRandom());
	}
	
	// printing the histogram
	h1->Draw();	

	// defining and setting the first fit function
	TF1 *fitFcn1 = new TF1("fitFcn1",nslit_fit,-10,10,3);
	fitFcn1->SetParameters(1,1,1);
	fitFcn1->SetParameter(0,400);
	fitFcn1->SetParameter(1,0.2);
	fitFcn1->SetParameter(2,2);

	// defining and setting the second fit function
	TF1 *fitFcn2 = new TF1("fitFcn2",nslit_fit,-10,10,3);
	fitFcn2->SetParameters(1,1,1);
	fitFcn2->SetParameter(0,400);
	fitFcn2->SetParameter(1,0.2);
	fitFcn2->SetParameter(2,2);
	
	// fiting the first function with least square
	h1->Fit("fitFcn1","N");
	
	// fiting the second function with Maximun likelihood
	h1->Fit("fitFcn2","NL");
	
	// defining and setting the fit functions
	TF1 *fit_plt1 = new TF1("fit_plt1",nslit_fit,-10,+10,3);
	fit_plt1->SetLineColor(kRed);
	fit_plt1->SetLineWidth(4);
	fit_plt1->SetNpx(500);
	TF1 *fit_plt2 = new TF1("fit_plt2",nslit_fit,-10,+10,3);
	fit_plt2->SetLineColor(kGreen);
	fit_plt2->SetLineWidth(2);
	fit_plt2->SetNpx(500);

	// getting the parameters and printing
	double par1[3];
	fitFcn1->GetParameters(par1);
	fit_plt1->SetParameters(par1);
	fit_plt1->Draw("same");
	double par2[3];
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
