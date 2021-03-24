// Implementatie van klasse AapjeOmino

#include <iostream>
#include "standaard.h"
#include "aapjeomino.h"
#include "fstream"
#include <algorithm>

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

	// Bord op -1 & 0, zodat er geen stenen zijn.
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
	if (((i == 0 && aanBeurt) || (j == 0 && !aanBeurt)) ||
		(pot == nrStenen && bepaalMogelijkeZetten().size() == 0)) {
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
				cout << stenen[bord[i][j].first][bord[i][j].second];
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
	if (eindstand()) {
		cout << "Score Femke: " << static_cast<int>(stenenFemke.size()-stenenLieke.size()) << endl; //Femke-Lieke
		cout << "Score Lieke: " <<static_cast<int>(stenenLieke.size()-stenenFemke.size()) << endl; //Lieke-Femke
	}
}  // drukAf

//*************************************************************************

vector<Zet> AapjeOmino::bepaalMogelijkeZetten ()
{ 
	vector<Zet> zetten;
	Zet mogelijkeZet;
	int s;
	if (aanBeurt) {
		s = stenenLieke.size();
		for (int i = 0; i < hoogte; i++) {
			for (int j = 0; j < breedte; j++) {
				if (bord[i][j].first == -1 && (
					(i-1 >= 0 && bord[i-1][j].first != -1) ||
					(i+1 < hoogte && bord[i+1][j].first != -1) ||
					(j-1 >= 0 && bord[i][j-1].first != -1) ||
					(j+1 < breedte && bord[i][j+1].first != -1))) {
					for (int k = 0; k < s; k++) {
						for (int l = 0; l < 4; l++) {
							if ((i-1 < 0 || stenen[bord[i-1][j].first][(2+bord[i-1][j].second)%4] == stenen[stenenLieke[k]][(0+l)%4] ||
								bord[i-1][j].first == -1) &&
								(i+1 >= hoogte || (stenen[bord[i+1][j].first][(0+bord[i+1][j].second)%4] == stenen[stenenLieke[k]][(2+l)%4] ||
								bord[i+1][j].first == -1)) &&
								(j-1 < 0 || (stenen[bord[i][j-1].first][(1+bord[i][j-1].second)%4] == stenen[stenenLieke[k]][(3+l)%4] ||
								bord[i][j-1].first == -1)) &&
								(j+1 >= breedte || (stenen[bord[i][j+1].first][(3+bord[i][j+1].second)%4] == stenen[stenenLieke[k]][(1+l)%4] ||
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
				if (bord[i][j].first == -1 && (
					(i-1 >= 0 && bord[i-1][j].first != -1) ||
					(i+1 < hoogte && bord[i+1][j].first != -1) ||
					(j-1 >= 0 && bord[i][j-1].first != -1) ||
					(j+1 < breedte && bord[i][j+1].first != -1))) {
					for (int k = 0; k < s; k++) {
						for (int l = 0; l < 4; l++) {
							if ((i-1 < 0 || (stenen[bord[i-1][j].first][(2+bord[i-1][j].second)%4] == stenen[stenenFemke[k]][(0+l)%4] ||
								bord[i-1][j].first == -1)) &&
								(i+1 >= hoogte || (stenen[bord[i+1][j].first][(0+bord[i+1][j].second)%4] == stenen[stenenFemke[k]][(2+l)%4] ||
								bord[i+1][j].first == -1)) &&
								(j-1 < 0 || (stenen[bord[i][j-1].first][(1+bord[i][j-1].second)%4] == stenen[stenenFemke[k]][(3+l)%4] ||
								bord[i][j-1].first == -1)) &&
								(j+1 >= breedte || (stenen[bord[i][j+1].first][(3+bord[i][j+1].second)%4] == stenen[stenenFemke[k]][(1+l)%4] ||
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
	int grote;
	bool steenInHand = false;


	if (!integerInBereik("Steen_Index", i, 0, nrStenen-1)) 
		return false;
	if (!integerInBereik("Rotatie", r, 0, 4)) 
		return false;

	if (!integerInBereik ("Rij", rij, 0, MaxDimensie-1)) {
		return false;
	}
	if (!integerInBereik ("Kolom", kolom, 0, MaxDimensie-1)) {
		return false;
	}
	if (bord[rij][kolom].first != -1) {
		cout << "Dit vakje is niet leeg" << endl;
		return false;
	}
	
	if (!((rij-1 >= 0 && bord[rij-1][kolom].first != -1) ||
		(rij+1 < hoogte && bord[rij+1][kolom].first != -1) ||
		(kolom-1 >= 0 && bord[rij][kolom-1].first != -1) ||
		(kolom+1 < breedte && bord[rij][kolom+1].first != -1))) {
		cout << "Deze plek heeft geen aanliggende steen." << endl;
		return false;
	}
	
	if (!(
		(rij-1 < 0 || bord[rij-1][kolom].first == -1 || 
		stenen[i][r] == stenen[bord[rij-1][kolom].first][(bord[rij-1][kolom].second+2)%4]) && // checkt boven
		(kolom+1 >= breedte || bord[rij][kolom+1].first == -1 || 
		stenen[i][(r+1)%4] == stenen[bord[rij][kolom+1].first][(bord[rij][kolom+1].second+3)%4]) && // checkt rechts
		(rij+1 >= hoogte || bord[rij+1][kolom].first == -1 || 
		stenen[i][(r+2)%4] == stenen[bord[rij+1][kolom].first][bord[rij+1][kolom].second]) && // checkt onder
		(kolom-1 < 0 || bord[rij][kolom-1].first == -1 ||
		stenen[i][(r+3)%4] == stenen[bord[rij][kolom-1].first][(bord[rij][kolom-1].second+1)%4]))) { // checkt links
		cout << "Deze steen past niet." << endl;
		return false;
	}

	if (!aanBeurt) {
		grote = stenenFemke.size();
		for (int j = 0; j < grote; j++) {
			if (stenenFemke[j] == i) {
				stenenFemke.erase(stenenFemke.begin()+j);
				steenInHand = true;
			}
		}
		if (!steenInHand) {
			cout << "Femke heeft deze steen niet in haar hand." << endl;
			return false;
		}
	} else {
		grote = stenenLieke.size();
		for (int j = 0; j < grote; j++) {
			if (stenenLieke[j] == i) {
				stenenLieke.erase(stenenLieke.begin()+j);
				steenInHand = true;
			}
		}
		if (!steenInHand) {
			cout << "Lieke heeft deze steen niet in haar hand." << endl;
			return false;
		}	
	}
	bord[rij][kolom].first = i;
	bord[rij][kolom].second = r;
	actie = 1;
	wisselSpeler();
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
		if (buren[i] < beste)
			zetten.erase(zetten.begin() + i);
	}

	return zetten;
}  // bepaalGoedeZetten

//*************************************************************************

void AapjeOmino::doeSteenInPot () {
   pot--;
   if (!aanBeurt)
      stenenFemke.pop_back();
   else
      stenenLieke.pop_back();
}

//*************************************************************************

void AapjeOmino::unDoeZet (Zet zet)
{
	//Haal de zet Zet weer weg van het bord. Doe het in de hand van de speler
	//die nu niet aan de beurt is. Controleer of er zonder die steen zetten
	//mogelijk waren-> zo niet, doe de steen terug in de pot.
	bord[zet.getRij()][zet.getKolom()].first = -1;
	bord[zet.getRij()][zet.getKolom()].second = 0;

	wisselSpeler();
	// if ((bepaalMogelijkeZetten().size() == 0) &&
	// 	(pot <= nrStenen) && (actie == 0) && (!eindstand()))
	// 	doeSteenInPot();
	// else {
	if (!aanBeurt) {
		stenenFemke.push_back(zet.getI());
		sort(stenenFemke.begin(), stenenFemke.end());
	}
	else {
		stenenLieke.push_back(zet.getI());
		sort(stenenLieke.begin(), stenenLieke.end());
	}
	// }
}

//*************************************************************************

int AapjeOmino::besteScore (Zet &besteZet, long long &aantalStanden)
{
	vector<Zet> zetten;
	int maxscore = -nrStenen;
	int score = -nrStenen;
	int s;

	cout << "[ ";
	if (eindstand()) {
		if (aanBeurt) {
			cout << static_cast<int>(stenenFemke.size()-stenenLieke.size());
			cout << "] ";
			return static_cast<int>(stenenFemke.size()-stenenLieke.size());
		}
		else {
			cout << static_cast<int>(stenenLieke.size()-stenenFemke.size());
			cout << "] ";
			return static_cast<int>(stenenLieke.size()-stenenFemke.size());
		}
	}
	else {
		zetten = bepaalMogelijkeZetten();
		s = zetten.size();
		if (s == 0) {
			haalSteenUitPot();
			zetten = bepaalMogelijkeZetten();
			s = zetten.size();
			if (s == 0) {
				score = -besteScore(besteZet, aantalStanden);
				wisselSpeler();
			} else {
				doeZet(zetten[0]);
				score = -besteScore(besteZet, aantalStanden);
				if (score > maxscore) {
					maxscore = score;
					besteZet = zetten[0];
				}
				unDoeZet(zetten[0]);
			}
			doeSteenInPot();
		}
		else {
			for (int i = 0; i < s; i++) {
				doeZet(zetten[i]);
				score = -besteScore(besteZet, aantalStanden);
				if (score > maxscore) {
					maxscore = score;
					besteZet = zetten[i];
				}
				unDoeZet(zetten[i]);
			}	
		}
		cout << "] ";
		return maxscore;
	}
}  // besteScore

//*************************************************************************

bool AapjeOmino::genereerRandomSpel (int hoogte0, int breedte0,
	int nrStenen0, int nrStenenInHand0, int rij0, int kolom0,
	int minGetal, int maxGetal)
{
	if (!integerInBereik ("hoogte0", hoogte0, 1, MaxDimensie)) {
		return false;
	}

	if (!integerInBereik ("breedte0", breedte0, 1, MaxDimensie)) {
		return false;
	}

	if (nrStenen0 < nrStenenInHand0 * 2 + 1) {
		cout << "Er zijn te weinig stenen." << endl;
		return false;
	}

	if (!integerInBereik("rij0", rij0, 1, breedte) ||
		!integerInBereik("kolom0", kolom0, 1, hoogte)) {
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
	//genereer stenen
	for (int i = 0; i < nrStenen0; i++) {
	for (int j = 0; j < 4; j++) {
		stenen[i][j] = randomGetal(minGetal, maxGetal);
	}
	}
	// leggen beginsteen
	bord[rij0][kolom0].first = 0;
	bord[rij0][kolom0].second = 0;

	//verdelen van de beginstenen aan de spelers
	for (int i = 0; i < nrStenenInHand0 * 2; i++) {
		if (aanBeurt)
			stenenLieke.push_back(pot);
		else
			stenenFemke.push_back(pot);
		pot++;
		wisselSpeler();
	}
	return true;
}  // genereerRandomSpel

//*************************************************************************
