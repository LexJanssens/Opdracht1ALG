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

bool AapjeOmino::leesIn (const char* invoernaam){
	// TODO: implementeer deze memberfunctie
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
	
	for (int i = 0; i < nrStenen; i++) {
		stenen[i] = new Steen;
		for (int j = 0; j < 4; j++) {
			invoer >> getal;
			stenen[i]->beschrijving[j] = getal;
		}
		invoer.get();
	}
	
	invoer.close();
	
	return true;
}  // leesIn

//*************************************************************************

bool AapjeOmino::eindstand ()
{
  // TODO: implementeer deze memberfunctie
  //Hier komt de eindstand functie te staan
  return false;

}  // eindstand

//*************************************************************************

//n en m worden lengte en hoogte. N O Z W kunnen worden aangepast naar bord[i][j] uiteindelijk
void AapjeOmino::drukAf()
{
   for (int i = 0; i < breedte; i++) {
      cout << "      " << i;
   }
   cout << endl;
   for (int i = 0; i < hoogte; i++) {
      for (int j = 0; j < breedte; j++)
         cout << "      " << "N";
      cout << endl;
      for (int j = 0; j < breedte; j++) {
         if (j == 0)
            cout << i << "   " << "W" << "   " << "O";
         else
            cout << "  " << "W" << "   " << "O";
      }
      cout << endl;
      for (int j = 0; j < breedte; j++)
         cout << "      " << "Z";
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
  // TODO: implementeer deze memberfunctie

  return 0;

}  // haalSteenUitPot

//*************************************************************************

void AapjeOmino::wisselSpeler ()
{
  // TODO: implementeer deze memberfunctie

}  // wisselSpeler

//*************************************************************************

bool AapjeOmino::doeZet (Zet zet)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // doeZet

//*************************************************************************

vector<Zet> AapjeOmino::bepaalGoedeZetten ()
{ vector<Zet> zetten;

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
