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
	if (!integerInBereik ("Hoogte", hoogte, 1, MaxDimensie)) {
		return false;
	}

	invoer >> breedte;
	invoer.get();
	if (!integerInBereik ("Breedte", breedte, 1, MaxDimensie)) {
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
		if (aanBeurt)
			stenenLieke.push_back(pot);
		else
			stenenFemke.push_back(pot);
   		pot++;
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
   int k = stenenFemke.size();
   int l = stenenLieke.size();
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
      cout << i << ": ";
      for (int j = 0; j < 4; j++)
         cout << stenen[i][j] << ",";
      cout << "  ";
	}
	cout << endl << "Femke: ";

	for (int i = 0; i < k; i++) {
      cout << stenenFemke[i] << ": ";
      for (int j = 0; j < 4; j++)
         cout << stenen[stenenFemke[i]][j] << ",";
      cout << "  ";
	}
	cout << endl << "Lieke: ";

	for (int i = 0; i < l; i++) {
      cout << stenenLieke[i] << ": ";
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
   Zet mogelijkeZet;
int s;
   if (aanBeurt) {
      s = stenenLieke.size();
      for (int i = 0; i < hoogte; i++) {
         for (int j = 0; j < breedte; j++) {
            for (int k = 0; k < s; k++) {
               if ((i-1 >= 0 && bord[i-1][j].first != -1) ||
                   (i+1 < hoogte && bord[i+1][j].first != -1) ||
                   (j-1 >= 0 && bord[i][j-1].first != -1) ||
                   (j+1 < breedte && bord[i][j+1].first != -1)) {
                  for (int l = 0; l < 4; l++) {
                     if ((i-1 >= 0 && (stenen[bord[i-1][j].first][(2+bord[i-1][j].second)%4] == stenen[stenenLieke[k]][(0+l)%4] ||
                         bord[i-1][j].first == -1)) &&
                         (i+1 < hoogte && (stenen[bord[i+1][j].first][(0+bord[i+1][j].second)%4] == stenen[stenenLieke[k]][(2+l)%4] ||
                         bord[i+1][j].first == -1)) &&
                         (j-1 >= 0 && (stenen[bord[i][j-1].first][(1+bord[i][j-1].second)%4] == stenen[stenenLieke[k]][(3+l)%4] ||
                         bord[i][j-1].first == -1)) &&
                         (j+1 < breedte && (stenen[bord[i][j+1].first][(3+bord[i][j+1].second)%4] == stenen[stenenLieke[k]][(1+l)%4] ||
                         bord[i][j+1].first == -1))) {
                            mogelijkeZet.setWaardes(stenenLieke[k], (l)%4, i, j);
                            zetten.push_back(mogelijkeZet);
                     }
                  }
               }
            }
         }
      }
   }
   else {
      s = stenenFemke.size();
      for (int i = 0; i < hoogte; i++) {
         for (int j = 0; j < breedte; j++) {
            for (int k = 0; k < s; k++) {
               if ((i-1 >= 0 && bord[i-1][j].first != -1) ||
                   (i+1 < hoogte && bord[i+1][j].first != -1) ||
                   (j-1 >= 0 && bord[i][j-1].first != -1) ||
                   (j+1 < breedte && bord[i][j+1].first != -1)) {
                  for (int l = 0; l < 4; l++) {
                     if ((i-1 >= 0 && (stenen[bord[i-1][j].first][(2+bord[i-1][j].second)%4] == stenen[stenenFemke[k]][(0+l)%4] ||
                         bord[i-1][j].first == -1)) &&
                         (i+1 < hoogte && (stenen[bord[i+1][j].first][(0+bord[i+1][j].second)%4] == stenen[stenenFemke[k]][(2+l)%4] ||
                         bord[i+1][j].first == -1)) &&
                         (j-1 >= 0 && (stenen[bord[i][j-1].first][(1+bord[i][j-1].second)%4] == stenen[stenenFemke[k]][(3+l)%4] ||
                         bord[i][j-1].first == -1)) &&
                         (j+1 < breedte && (stenen[bord[i][j+1].first][(3+bord[i][j+1].second)%4] == stenen[stenenFemke[k]][(1+l)%4] ||
                         bord[i][j+1].first == -1))) {
                            mogelijkeZet.setWaardes(stenenFemke[k], (l)%4, i, j);
                            zetten.push_back(mogelijkeZet);
                     }
                  }
               }
            }
         }
      }
   }
	return zetten;
}  // bepaalMogelijkeZetten

//*************************************************************************

int AapjeOmino::haalSteenUitPot ()
{
	if (pot >= nrStenen) {
		cout << "De pot is leeg." << endl;
		return -1;
	}

	if (bepaalMogelijkeZetten().size() > 0) {
		cout << "Er kan nog een steen worden aangelegd." << endl;
		return -1;
	}

	if (actie != 0) {
		cout << "Je hebt al een actie gedaan." << endl;
		return -1;
	}

	if (aanBeurt)
		stenenLieke.push_back(pot);
	else
		stenenFemke.push_back(pot);
   	pot++;
	actie = 2;
	return 0;
}  // haalSteenUitPot

//*************************************************************************

void AapjeOmino::wisselSpeler ()
{
	actie = 0;
	aanBeurt = 1 - aanBeurt;
}  // wisselSpeler

//*************************************************************************

bool AapjeOmino::doeZet (Zet zet)
{
	int i = zet.getI();
	int r = zet.getR();
	int rij = zet.getRij();
	int kolom = zet.getKolom();
	int size;

	actie = 1;

	if (!integerInBereik("Steen_Index", i, 0, nrStenen - 1)) 
		return false;
	if (!integerInBereik("Rotatie", r, 0, 4)) 
		return false;

	if (!integerInBereik ("Rij", rij, 1, MaxDimensie)) {
		return false;
	}
	if (!integerInBereik ("Kolom", kolom, 1, MaxDimensie)) {
		return false;
	}
	if (bord[rij][kolom].first != -1) {
		cout << "Dit vakje is niet leeg" << endl;
		return false;
	}
	
	if ((rij-1 >= 0 && bord[rij-1][kolom].first != -1) ||
		(rij+1 < hoogte && bord[rij+1][kolom].first != -1) ||
		(kolom-1 >= 0 && bord[rij][kolom-1].first != -1) ||
		(kolom+1 < breedte && bord[rij][kolom+1].first != -1)) {
		cout << "Deze plek heeft geen aanliggende steen." << endl;
		return false;
	}
	
	if (!(
		(rij-1 <= 0 || bord[rij-1][kolom].first != -1 || 
		stenen[i][r] == stenen[bord[rij-1][kolom].first][(r+2)%4]) && // checkt boven
		(kolom+1 < breedte || bord[rij][kolom+1].first != -1 || 
		stenen[i][(r+1)%4] == stenen[bord[rij][kolom+1].first][(r+3)%4]) && // checkt rechts
		(rij+1 < hoogte || bord[rij+1][kolom].first != -1 || 
		stenen[i][(r+2)%4] == stenen[bord[rij+1][kolom].first][r]) && // checkt onder
		(kolom-1 >= 0 || bord[rij][kolom-1].first != -1 ||
		stenen[i][(r+3)%4] == stenen[bord[rij][kolom-1].first][(r+1)%4]))) { // checkt links
		cout << "Deze steen past niet." << endl;
		return false;
	}
	bord[rij][kolom].first = i;
	bord[rij][kolom].second = r;

	if (!aanBeurt) {
		size = stenenFemke.size();
		for (int j = 0; j < size; j++) {
			if (stenenFemke[j] == i) {
				stenenFemke.erase(stenenFemke.begin()+j);
				break;
			}
			cout << "Femke heeft deze steen niet in haar hand." << endl;
			return false;
		}
	} else {
		size = stenenLieke.size();
		for (int j = 0; j < size; j++) {
			if (stenenLieke[j] == i) {
				stenenLieke.erase(stenenLieke.begin()+j);
				break;
			} 
			cout << "Lieke heeft deze steen niet in haar hand." << endl;
			return false;
		}		
	}
	return true;
}  // doeZet

//*************************************************************************

vector<Zet> AapjeOmino::bepaalGoedeZetten ()
{
	vector<Zet> zetten = bepaalMogelijkeZetten();
	int sizeZetten = zetten.size();
	int buren[sizeZetten]; //buren waarbij het kan aansluiten, al bepaald, dus alleen maar tellen.
	int beste = 1; //maximale hoeveelheid buren van een steen in zetten
	for (int i = 0; i < sizeZetten; i++) {
		buren[i] = 0;
		if (zetten[i].getRij()-1 >= 0 && bord[zetten[i].getRij()-1][zetten[i].getKolom()].first != -1)
			buren[i]++;
		if (zetten[i].getRij()+1 < hoogte && bord[zetten[i].getRij()+1][zetten[i].getKolom()].first != -1)
			buren[i]++;
		if (zetten[i].getKolom()-1 >= 0 && bord[zetten[i].getRij()][zetten[i].getKolom()-1].first != -1)
			buren[i]++;
		if (zetten[i].getKolom()+1 < breedte && bord[zetten[i].getRij()][zetten[i].getKolom()+1].first != -1)
			buren[i]++;
		if (buren[i] > beste)
			beste = buren[i];
	}
	//haal alle stenen eruit met minder buren dan 'beste'
	for (int i = sizeZetten-1; i >= 0; i--) {
		cout << buren[i] << endl;
		if (buren[i] < beste)
			zetten.erase(zetten.begin() + i);
	}

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
