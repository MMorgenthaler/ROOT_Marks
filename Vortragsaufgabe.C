#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1.h"
#include "TRandom3.h"
using namespace std;

void Vortragsaufgabe() {
	TRandom3 *rndm = new TRandom3();
	int size = 1000;
/*
	ofstream myfile;
	myfile.open ("./Daten.txt");
	for(int i=0; i< size; i++) myfile << rndm->Landau(0.,1.) << "\n";
  	myfile.close();
*/

	double low = -10;
	double high = 10;
	int bins = 100;
	TH1D *hReal = new TH1D("hReal","hReal",bins,low,high);
	TH1D *hGaus = new TH1D("hGaus","hGaus",bins,low,high);
	TH1D *hLand = new TH1D("hLand","hLand",bins,low,high);
	TH1D *hExp  = new TH1D("hExp", "hExp", bins,low,high);

	fstream inFile("./Daten.txt");
	double a;
	while(inFile >> a) {
		hReal->Fill(a);
		hGaus->Fill(rndm->Gaus(0.,1.));
		hLand->Fill(rndm->Landau(0.,1.));
		hExp ->Fill(rndm->Exp(1.));
	}
	inFile.close();

	// Chi2 Version
	cout << "Chi2 Test" << endl;
	double chiGaus = hGaus->Chi2Test(hReal,"UUCHI2");
	double chiLand = hLand->Chi2Test(hReal,"UUCHI2");
	double chiExp  = hExp ->Chi2Test(hReal,"UUCHI2");
	cout << "Chi2-Wert Gauß: " << chiGaus << endl;
	cout << "Chi2-Wert Landau: " << chiLand << endl;
	cout << "Chi2-Wert Exponential: " << chiExp << endl;
	if(chiGaus < chiLand && chiGaus < chiExp) cout << "Die Daten sind normalverteilt" << endl;
	else if(chiLand < chiGaus && chiLand < chiExp) cout << "Die Daten sind landau-verteilt" << endl;
	else if(chiExp < chiLand && chiExp < chiGaus) cout << "Die Daten sind exponentiell verteilt" << endl;

	// Kolmogorov Version
	float alpha = 0.05;
	double threshold = sqrt((size+size)*log(2/alpha)/(2*size*size));
	cout << "\nKolmogorov Test" << endl;
	double KDGaus = hGaus->KolmogorovTest(hReal,"M");
	double KDLand = hLand->KolmogorovTest(hReal,"M");
	double KDExp  = hExp ->KolmogorovTest(hReal,"M");
	cout << "Kritischer Wert: " << threshold << endl;
	cout << "Kolmogorov Distanz Gauß: " << KDGaus << endl;
	cout << "Kolmogorov Distanz Landau: " << KDLand << endl;
	cout << "Kolmogorov Distanz Exponential: " << KDExp << endl;
	if(KDGaus < threshold) cout << "Die Daten sind normalverteilt" << endl;
	else if(KDLand < threshold) cout << "Die Daten sind landau-verteilt" << endl;
	else if(KDExp < threshold) cout << "Die Daten sind exponentiell verteilt" << endl;

	// Anderson-Darling Version
	double critVal = 0;
	if(int(alpha*100) == 1) critVal = 3.857;
	else if (int(alpha*100) == 5) {critVal = 2.492; 	cout << "ping" << endl;}
	else if (int(alpha*100) == 10) critVal = 1.933;
	cout << "\nAnderson-Darling Test" << endl;
	double ADGaus = hGaus->AndersonDarlingTest(hReal,"T");
	double ADLand = hLand->AndersonDarlingTest(hReal,"T");
	double ADExp  = hExp ->AndersonDarlingTest(hReal,"T");
	cout << "Kritischer Wert: " << critVal << endl;
	cout << "Normalisierte Teststatistik Gauß: " << ADGaus << endl;
	cout << "Normalisierte Teststatistik Landau: " << ADLand << endl;
	cout << "Normalisierte Teststatistik Exponential: " << ADExp << endl;
	if(ADGaus < critVal) cout << "Die Daten sind normalverteilt" << endl;
	else if(ADLand < critVal) cout << "Die Daten sind landau-verteilt" << endl;
	else if(ADExp < critVal) cout << "Die Daten sind exponentiell verteilt" << endl;






}