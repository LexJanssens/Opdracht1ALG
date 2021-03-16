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
	if (!integerInBereik ("Hoogte", hoogte, 1, 10)) {
		return false;
	}

	invoer >> breedte;
	invoer.get();
	if (!integerInBereik ("Breedte", breedte, 1, 10)) {
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
	if (!integerInBereik("rijStartSteen", rijStartSteen, 1, breedte) ||
        !integerInBereik("kolomStartSteen", kolomStartSteen, 1, hoogte)) {
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
	for (int i = 0; i < beginStenen * 2; i++) {
		haalSteenUitPot();
		wisselSpeler();
	}
	invoer.close();
	return true;
}	// leesIn

//*************************************************************************

bool AapjeOmino::eindstand ()
{
	int i = stenenLieke.size(), j = stenenFemke.size();

   	if (((i == 0 && aanBeurt) || (j == 0 && !aanBeurt)) && pot == nrStenen) {
      	cout << "Score Femke: " << j-i << endl; //Femke-Lieke
      	cout << "Score Lieke: " << i-j << endl; //Lieke-Femke
      	return true;
   	}
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
	
	//stenen:
	cout << "Stenen pot: ";
	for (int i = pot; i < nrStenen; i++) {
      for (int j = 0; j < 4; j++)
         cout << stenen[i][j] << ",";
      cout << "  ";
	}
	cout << endl << "Femke: ";
	for (int i = 0; i < stenenFemke.size()-1; i++) {
      for (int j = 0; j < 4; j++)
         cout << stenen[stenenFemke[i]][j] << ",";
      cout << "  ";
	}
	cout << endl << "Lieke: ";
	for (int i = 0; i < stenenLieke.size()-1; i++) {
      for (int j = 0; j < 4; j++)
         cout << stenen[stenenLieke[i]][j] << ",";
      cout << "  ";
	}
	cout << endl;
	if (aanBeurt)
      cout << "Lieke is aan de beurt" << endl;
   	else
      cout << "Femke is aan de beurt" << endl;
	
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
	if (aanBeurt) 
		stenenLieke.push_back(pot);
	else 
		stenenFemke.push_back(pot);
	pot++;
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
