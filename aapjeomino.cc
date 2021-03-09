// Implementatie van klasse AapjeOmino

#include <iostream>
#include "standaard.h"
#include "aapjeomino.h"
#include "fstream"

//*************************************************************************

AapjeOmino::AapjeOmino ()
{
// TODO: implementeer (zo nodig) deze constructor

}  // default constructor

//*************************************************************************

bool AapjeOmino::leesIn (const char* invoernaam) 
{
	int beginStenen, rijStartSteen, kolomStartSteen, getal;

	ifstream invoer (invoernaam, ios::in);

	if (!invoer.is_open()) { // checkt of het bestand wel to openen is
		cout << "Kan file niet openen." << endl;
		return false;
	}

	invoer >> hoogte;
	invoer.get();
	if (hoogte > MaxDimensie){
		cout << "Het bord is te hoog." << endl;
		return false;
	}

	invoer >> breedte;
	invoer.get();
	if (breedte > MaxDimensie){
		cout << "Het bord is te breedt." << endl;
		return false;
	}

	invoer >> nrStenen;
	invoer.get();
	invoer >> beginStenen;
	invoer.get();
	if (nrStenen < beginStenen * 2 + 1) {
		cout << "Er zijn te weinig stenen." << endl;
		return false;
	}

	invoer >> rijStartSteen;
	invoer.get();
	invoer >> kolomStartSteen;
	invoer.get();
	if (rijStartSteen >= MaxDimensie || kolomStartSteen >= MaxDimensie || rijStartSteen < 0 || kolomStartSteen < 0) {
		cout << "De startsteen ligt niet op het bord." << endl;
		return false;
	}

	//Bord op -1 & 0, zodat er geen stenen zijn.
	for (int i = 0; i < MaxDimensie; i++) {
		for (int j = 0; j < MaxDimensie; j++) {
			bord[i][j].first = -1;
			bord[i][j].second = 0;
		}
	}

	// stopt de stenen in de index lijst
	// en initialiseert 
	for (int i = 0; i < nrStenen; i++) { 
		stenenFemke[i] = -1;
		stenenLieke[i] = -1;
		for (int j = 0; j < 4; j++) {
			invoer >> getal;
			stenen[i][j] = getal;
		}
		invoer.get();
	}

	// legen beginsteen
	bord[rijStartSteen][kolomStartSteen].first = 0;
	bord[rijStartSteen][kolomStartSteen].second = 0;

	//verdelen van de beginstenen aan de spelers
	for (int i = 0; i < 2 * beginStenen; i++) {
		haalSteenUitPot();
		wisselSpeler();
	}

	invoer.close();

	return true;
}	// leesIn

//*************************************************************************

bool AapjeOmino::eindstand ()
{
   int i = 0, j = 0;
   while (stenenLieke[i] != -1) //hoeveelheid stenen Lieke
      i++;
   while (stenenFemke[j] != -1) //hoeveelheid stenen Femke
      j++

   cout << "Score Femke: " << j-i << endl; //Femke-Lieke
   cout << "Score Lieke: " << i-j << endl; //Lieke-Femke
   return false;
}  // eindstand

//*************************************************************************

void AapjeOmino::drukAf()
{
	for (int i = 0; i < breedte; i++) {
		cout << "      " << i;
	}
	cout << endl;
	for (int i = 0; i < hoogte; i++) {
		for (int j = 0; j < breedte; j++) {
			cout << "      ";
			if (bord[i][j].first == -1)
				cout << "-";
			else
				cout << stenen[bord[i][j].first][0];
		}
		cout << endl;
		for (int j = 0; j < breedte; j++) {
			if (j == 0) {
				if (bord[i][j].first == -1)
					cout << i << "   " << "-" << "   " << "-";
				else
					cout << i << "   " << stenen[bord[i][j].first][(3+bord[i][j].second)%4] << "   " << stenen[bord[i][j].first][(1+bord[i][j].second)%4];
			} else {
				if (bord[i][j].first == -1)
					cout << "  " << "-" << "   " << "-";
				else
					cout << "  " << stenen[bord[i][j].first][(3+bord[i][j].second)%4] << "   " << stenen[bord[i][j].first][(1+bord[i][j].second)%4];
			}
		}
		cout << endl;
		for (int j = 0; j < breedte; j++) {
			cout << "      ";
			if (bord[i][j].first == -1)
				cout << "-";
			else
				cout << stenen[bord[i][j].first][(2+bord[i][j].second)%4];
		}
		cout << endl;
	}
	cout << endl;
}  // drukAf

//*************************************************************************

vector<Zet> AapjeOmino::bepaalMogelijkeZetten ()
{ vector<Zet> zetten;

	// TODO: implementeer deze memberfunctie

	return zetten;

}  // bepaalMogelijkeZetten

//*************************************************************************

int AapjeOmino::haalSteenUitPot ()
{
	int i = 0; 
	if (aanBeurt) {
		while (stenenLieke[i] != -1) {
			i++;
		}
		stenenLieke[i] = pot;
		pot++;
	} else {
		while (stenenLieke[i] != -1) {
			i++;
		}
		stenenLieke[i] = pot;
		pot++;
	}
	return 0;
}  // haalSteenUitPot

//*************************************************************************

void AapjeOmino::wisselSpeler ()
{
	aanBeurt = 1 - aanBeurt;
}  // wisselSpeler

//*************************************************************************

bool AapjeOmino::doeZet (Zet zet)
{
	// TODO: implementeer deze memberfunctie

	return true;

}  // doeZet

//*************************************************************************

vector<Zet> AapjeOmino::bepaalGoedeZetten ()
{ 
	vector<Zet> zetten;

	// TODO: implementeer deze memberfunctie

	return zetten;
}  // bepaalGoedeZetten

//*************************************************************************

int AapjeOmino::besteScore (Zet &besteZet, long long &aantalStanden)
{
	// TODO: implementeer deze memberfunctie

	return 0;

}  // besteScore

//*************************************************************************

bool AapjeOmino::genereerRandomSpel (int hoogte0, int breedte0,
	int nrStenen0, int nrStenenInHand0, int rij0, int kolom0,
	int minGetal, int maxGetal)
{
	// TODO: implementeer deze memberfunctie

	return true;

}  // genereerRandomSpel

//*************************************************************************
