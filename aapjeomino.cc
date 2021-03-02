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

bool AapjeOmino::leesIn (const char* invoernaam)
{
  // TODO: implementeer deze memberfunctie
  ifstream invoer (invoernaam, ios::in);
  if (!invoer.is_open()){
     cout<<"Kan file niet openen."<<endl;
    return;
  }
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
   int n = 4;
   int m = 3;
   for (int i = 0; i < n; i++) {
      cout << "      " << i;
   }
   cout << endl;
   for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++)
         cout << "      " << "N";
      cout << endl;
      for (int j = 0; j < n; j++) {
         if (j == 0)
            cout << i << "   " << "W" << "   " << "O";
         else
            cout << "  " << "W" << "   " << "O";
      }
      cout << endl;
      for (int j = 0; j < n; j++)
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
