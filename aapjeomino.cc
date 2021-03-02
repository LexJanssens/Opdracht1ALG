// Implementatie van klasse AapjeOmino

#include <iostream>
#include "standaard.h"
#include "aapjeomino.h"

//*************************************************************************

AapjeOmino::AapjeOmino ()
{
  // TODO: implementeer (zo nodig) deze constructor

}  // default constructor

//*************************************************************************

bool AapjeOmino::leesIn (const char* invoernaam){
	// TODO: implementeer deze memberfunctie

	char letter;
	int nummer = 0;

	ifstream invoer (invoernaam, ios::in);

	if (!invoer.is_open()){ // checkt of het bestand wel to openen is
   	cout << "Kan file niet openen." << endl;
   	return false;
	}

	letter = invoer.get();
	cout << letter << endl;

	// checkt groote bord
	for (int i = 0; i < 2; i++){ // doe twee keer
		while(letter != ' ' && letter != '\n'){
			nummer = nummer * 10 + letter - '0';
			letter = invoer.get();
		}
		if (nummer > MaxDimensie){
			cout << "Het bord is te groot." << endl;
			return false;
		}
		nummer = 0;
		letter = invoer.get();
	}

	letter = invoer.get();

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
