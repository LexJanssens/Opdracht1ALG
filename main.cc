// Hoofdprogramma voor oplossing voor eerste programmeeropdracht Algoritmiek,
// voorjaar 2021: Aapje Omino.
//
// Biedt de gebruiker een menustructuur om
// * een instantie van Aapje Omino in te lezen, en daarmee het spel te spelen,
//   waarbij de gebruiker steeds
//   - (zo nodig) een steen uit de pot kan halen
//   - een zet kan uitvoeren (een steen op het bord leggen)
//   - kan vragen om de `goede' zetten
//   - kan vragen om de score voor de speler die aan de beurt is, als beide
//     spelers vanaf dit moment optimaal verder spelen
// * experimenten te doen, waarbij een gretige strategie met een optimale
//   strategie vergeleken wordt.
//
// Naam student 1, naam student 2

#include <iostream>
#include <string>
#include <ctime>  // voor clock() en clock_t
#include <cstdlib>
#include "standaard.h"
#include "zet.h"
#include "aapjeomino.h"
#include <thread>
using namespace std;
const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam

//*************************************************************************

//Algemene informatie schrijvers van het programma
void infoblokje() {
    cout << "AapjeOmino" << endl
         << "Geschreven door Bart Aaldering (s2969866)," << endl
         << "student Informatica (Artificial Intelligence) te Leiden" << endl
         << "en Lex Janssens (s2989344)," << endl
         << "student Informatica (Artificial Intelligence) te Leiden" << endl
         << "Inleverdatum: 28-3-2021 23:59" << endl;
}//info

// Schrijf de zetten in vector zetten met een passende kop naar het scherm.
void schrijfZetten (string kop, vector<Zet> zetten)
{ size_t nrZetten;

  cout << endl;
  cout << kop << endl;

  nrZetten = zetten.size();
  if (nrZetten>0)
  { for (size_t i=0;i<nrZetten;i++)
    { cout << i << ": ";
      zetten[i].drukAf();
    }
  }
  else
    cout << "Helaas, 0 zetten." << endl;

}  // schrijfZetten

//*************************************************************************

// Schrijf het menu op het scherm (afhankelijk van nrZetten),
// en vraag een keuze van de gebruiker.
// Retourneer: de keuze van de gebruiker
int keuzeUitMenu (size_t nrZetten)
{ int keuze;

  cout << endl;
  if (nrZetten==0)
    cout << "1. Een steen uit de pot halen" << endl;
  else
    cout << "1. Een zet uitvoeren" << endl;
  cout << "2. De `goede' zetten bepalen" << endl;
  cout << "3. Optimale score bepalen" << endl;
  cout << "4. Stoppen met dit spel" << endl;
  cout << endl;
  cout << "Maak een keuze: ";
  cin >> keuze;

  return keuze;

}  // keuzeUitMenu

//*************************************************************************

// Speel het spel op het bord van ao1.
// Hierbij krijgt de gebruiker herhaaldelijk de keuze om
// * (zo nodig) een steen uit de pot te halen
// * een zet uit te voeren (een steen op het bord leggen)
// * te vragen om de `goede' zetten
// * te vragen om de score voor de speler die aan de beurt is, als beide
//   spelers vanaf dit moment optimaal verder spelen
//
// Voor elke iteratie van het menu wordt de stand afgedrukt, met de mogelijke
// zetten voor de huidige speler aan de beurt.
//
// Dit alles gaat door
// * totdat er een eindstand is bereikt (een van de spelers heeft geen
//   stenen meer en/of de huidige speler kan niets meer doen)
// * of totdat de gebruiker aangeeft dat hij wil stoppen met het spel
void doeSpel (AapjeOmino *ao1)
{ int keuze,
      stnr,             // steen die uit pot gehaald wordt
      zetNr,            // nummer van de zet die gedaan moet worden
      score;            // returnwaarde van besteScore
  long long aantalStanden;  // aantal bekeken standen bij aanroep besteScore
  vector<Zet> zetten;
  size_t nrZetten;
  Zet besteZet;
  clock_t t1, t2;

  keuze = 0;
  while (keuze!=4 && !ao1->eindstand())
  {
    ao1 -> drukAf ();

    zetten = ao1 -> bepaalMogelijkeZetten();
    schrijfZetten ("Mogelijke zetten voor de speler aan de beurt:", zetten);
    nrZetten = zetten.size();

    keuze = keuzeUitMenu(nrZetten);

    switch (keuze)
    { case 1: if (nrZetten==0)
              { stnr = ao1 -> haalSteenUitPot();
                if (stnr!=-1)  // gelukt om een steen uit de pot te halen
                { zetten = ao1 -> bepaalMogelijkeZetten();
                  if (zetten.size()==0)
                    ao1 -> wisselSpeler();
                }
              }
              else
              { cout << endl;
                cout << "Geef het nummer van een mogelijke zet (0.."
                     << nrZetten-1 << "): ";
                  // ook als je hiervoor net de `goede' zetten hebt
                  // opgevraagd, moet je kiezen uit alle mogelijke zetten
                cin >> zetNr;
                if (integerInBereik("zetNr", zetNr, 0, nrZetten-1))
                  ao1->doeZet(zetten[zetNr]);
              }
              break;
      case 2: zetten = ao1 -> bepaalGoedeZetten();
              schrijfZetten("`Goede' zetten voor speler aan beurt zijn:",
                             zetten);
              break;
      case 3: t1 = clock();
              aantalStanden = 0;
              score = ao1 -> besteScore(besteZet, aantalStanden);
              t2 = clock();
              cout << endl;
              cout << "Optimale score = " << score << endl;
              cout << "Een beste zet is: ";
              besteZet.drukAf();
              cout << "We hebben hiervoor " << aantalStanden
                   << " standen bekeken." << endl;
              cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
              break;
      case 4: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }  // switch

  }  // while

  if (ao1->eindstand())
  { ao1 -> drukAf();
    cout << endl;
    cout << "De huidige stand is een eindstand.\n";
  }

}  // doeSpel

//*************************************************************************
void experiment(int i, int n, double &gScore, double &gTijd, double &gEind, long long int &gStanden)
{
   AapjeOmino *ao1;
	clock_t t1,t2;
	long long int standen1;
	Zet besteZet;
	vector<Zet> zetten;

   ao1 = new AapjeOmino;

   ao1->genereerRandomSpel(7, 7, n, n/4, 3, 3, 1, n);

   t1 = clock ();
   gScore = ao1->besteScore(besteZet, gStanden);
   t2 = clock ();

   gTijd += (((double)(t2-t1))/CLOCKS_PER_SEC);

   while (!ao1->eindstand()) {
      if (ao1->fAanBeurt() == 0) {
         zetten = ao1->bepaalGoedeZetten(); //speler 1
         if (zetten.size() == 0) {
            ao1->haalSteenUitPot();
            zetten = ao1->bepaalGoedeZetten();
            if (zetten.size()==0)
               ao1->wisselSpeler();
            else
               ao1->doeZet(zetten[0]);
         }
         else
            ao1->doeZet(zetten[randomGetal(0,zetten.size()-1)]);
      }
      else {
         zetten = ao1->bepaalMogelijkeZetten();
         if (zetten.size() == 0) {
            ao1->haalSteenUitPot();
            zetten = ao1->bepaalMogelijkeZetten();
            if (zetten.size() == 0)
               ao1->wisselSpeler();
            else
               ao1->doeZet(zetten[0]);
         }
         else {
            besteZet = zetten[0];
            ao1->besteScore(besteZet, standen1); //speler 2
            ao1->doeZet(besteZet); //speler 2
         }
      }
   }
   gEind += ao1->eindscore();
   cout << i+1 << "/10" << endl;
   delete ao1;

} //experimenten

// Voert de experimenten uit zoals beschreven in de opdracht.
void doeExperimenten()
{
   int n;
	cout << "Welke N wordt er gebruikt? ";
	cin >> n;
	cout << endl;

	double gScore = 0, gTijd = 0, gEind = 0;
   long long int gStanden = 0;
   double tScore = 0, tTijd = 0, tEind = 0;
   long long int tStanden = 0;

   cout << "N = " << n << endl;
   for (int i = 0; i < 10; i++) {
      gScore = 0;
      gTijd = 0;
      gEind = 0;
      gStanden = 0;

      experiment(i, n, gScore, gTijd, gEind, gStanden);
      tStanden += gStanden;
      tTijd += gTijd;
      tScore += gScore;
      tEind += gEind;
   }
   cout << "Gemiddelde tijd: " << tTijd / 10 << endl;
	cout << "Gemiddelde score: " << tScore / 10 << endl;
	cout << "Gemiddelde standen: " << tStanden / 10 << endl;
	cout << "Gemiddelde eindstand: " << tEind / 10 << endl;
   //cout << "Done" << endl;
}  // doeExperimenten

//*************************************************************************

void hoofdmenu()
{ AapjeOmino *ao1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
                    // en weer weg te gooien
  int keuze;
  char invoernaam[MaxBestandsNaamLengte+1];

  do
  {
    cout << endl;
    cout << "1. Een spel spelen" << endl;
    cout << "2. Experimenten doen" << endl;
    cout << "3. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1: ao1 = new AapjeOmino();
              cout << "Geef de naam van het tekstbestand met het spel: ";
              cin >> invoernaam;
              if (ao1 -> leesIn (invoernaam))
                doeSpel (ao1);
              delete ao1;  // netjes opruimen
              break;
      case 2: doeExperimenten();
              break;
      case 3: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

  } while (keuze!=3);

}  // hoofdmenu

//*************************************************************************

int main()
{
  infoblokje();
  hoofdmenu();
  return 0;
}
