// Implementatie van klasse AapjeOmino

#include <iostream>
#include "standaard.h"
#include "aapjeomino.h"
#include "fstream"

//*************************************************************************

AapjeOmino::AapjeOmino()
{
}  // default constructor

//*************************************************************************

// returnt wie er aan de beurt is
int AapjeOmino::fAanBeurt()
{
	return aanBeurt;
}

//*************************************************************************

// sorteert de vector A
vector<int> AapjeOmino::sorteer(vector<int> &A)
{
	int n = A.size();
	int temp;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n -i; j++) {
			if (A[j] > A[j+1]) {
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}
		}
	}
	return A;
}

//*************************************************************************

// Leest een spel in vanuit een tekstbestand dat geopend word met de invoernaam
// Het verdeeld de stenen over het bord(stenen[][]),
// de twee handen(stenenFemke, stenenLieke) en de pot(pot).
// Ook word er gecontroleerd of eerste drie regels aan de specificaties voldoen
bool AapjeOmino::leesIn(const char* invoernaam)
{
	int aantalBeginStenen, rijStartSteen, kolomStartSteen, getal;
	ifstream invoer (invoernaam, ios::in);

	if (!invoer.is_open()) {
		cout << "Kan file niet openen." << endl;
		return false;
	}

	invoer >> hoogte;
	invoer.get();
	if (!integerInBereik ("Hoogte", hoogte, 1, MaxDimensie))
		return false;

	invoer >> breedte;
	invoer.get();
	if (!integerInBereik ("Breedte", breedte, 1, MaxDimensie))
		return false;

	invoer >> nrStenen;
	invoer.get();
	invoer >> aantalBeginStenen;
	invoer.get();
	if (nrStenen < aantalBeginStenen * 2 + 1) {
		cout << "Er zijn te weinig stenen." << endl;
		return false;
	}

	invoer >> rijStartSteen;
	invoer.get();
	invoer >> kolomStartSteen;
	invoer.get();
	if (!integerInBereik("rijStartSteen", rijStartSteen, 1, breedte) ||
	!integerInBereik("kolomStartSteen", kolomStartSteen, 1, hoogte))
		return false;

	// Bord op -1 & 0, zodat hij leeg is
	for (int i = 0; i < MaxDimensie; i++) {
		for (int j = 0; j < MaxDimensie; j++) {
			bord[i][j].first = -1;
			bord[i][j].second = 0;
		}
	}

	// stopt de beschrijving van de stenen in de stenen lijst
	for (int i = 0; i < nrStenen; i++) {
		for (int j = 0; j < 4; j++) {
			invoer >> getal;
			stenen[i][j] = getal;
		}
		invoer.get();
	}

	// leggen beginsteen
	bord[rijStartSteen][kolomStartSteen].first = 0;
	bord[rijStartSteen][kolomStartSteen].second = 0;

	// verdelen van de beginstenen aan de spelers
	for (int i = 0; i < aantalBeginStenen * 2; i++) {
	stenenHand[aanBeurt].push_back(pot);
	pot++;
		wisselSpeler();
	}
	invoer.close();

	return true;
}	// leesIn

//*************************************************************************

// Controleer of er een eindstand is bereikt
bool AapjeOmino::eindstand()
{
	int i = stenenHand[0].size(), j = stenenHand[1].size();
	if (i == 0 || j == 0 ||
		(pot == nrStenen && bepaalMogelijkeZetten().size() == 0)) {
		return true;
	}
	return false;
}  // eindstand

//*************************************************************************

// Drukt de hele stand (stenen in de twee handen en de pot, bord en
// de speler aan beurt) af op het scherm.
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
				cout << stenen[bord[i][j].first][bord[i][j].second];
		}
		cout << endl;
		for (int j = 0; j < breedte; j++) {
			if (j == 0) {
				if (bord[i][j].first == -1)
					cout << i << "   " << "-" << "   " << "-";
				else
					cout << i << "   "
					<< stenen[bord[i][j].first][(3+bord[i][j].second)%4] << "   "
					<< stenen[bord[i][j].first][(1+bord[i][j].second)%4];
			} else {
				if (bord[i][j].first == -1)
					cout << "  " << "-" << "   " << "-";
				else
					cout << "  "
					<< stenen[bord[i][j].first][(3+bord[i][j].second)%4] << "   "
					<< stenen[bord[i][j].first][(1+bord[i][j].second)%4];
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
	cout << "Stenen pot: " << endl;
	vector<int> St;
	for (int i = pot; i < nrStenen; i++) {
		St.push_back(i);
	}
	drukSteenAf(St);
	cout << endl << "Femke: " << endl;
	drukSteenAf(stenenHand[0]);
	cout << endl << "Lieke: " << endl;
	drukSteenAf(stenenHand[1]);
	cout << endl;
	if (aanBeurt)
		cout << "Lieke is aan de beurt" << endl;
	else
		cout << "Femke is aan de beurt" << endl;
	if (eindstand()) {
		cout << "Score Femke: " << static_cast<int>(stenenHand[1].size()-stenenHand[0].size()) << endl; //Femke-Lieke
		cout << "Score Lieke: " << static_cast<int>(stenenHand[0].size()-stenenHand[1].size()) << endl; //Lieke-Femke
	}
}  // drukAf

void AapjeOmino::drukSteenAf(vector<int> S)
{
	cout << "      ";
	for (int i = 0; i < static_cast<int>(S.size()); i++) {
		cout << stenen[S[i]][0] << "           ";
	}
	cout << endl;
	for (int i = 0; i < static_cast<int>(S.size()); i++) {
		cout << S[i] << ":  " << stenen[S[i]][3] << "   " << stenen[S[i]][1] << "   ";
	}
	cout << endl << "      ";
	for (int i = 0; i < static_cast<int>(S.size()); i++) {
		cout << stenen[S[i]][2] << "           ";
	}
}
//*************************************************************************

// Bepaalt alle mogelijke zetten voor de speler die aan de beurt is:
// de combinaties (steen, rotatie, rij, kolom) die aansluiten bij de stenen
// op het bord.
vector<Zet> AapjeOmino::bepaalMogelijkeZetten()
{
	vector<Zet> zetten;
	Zet mogelijkeZet;
	int grote = stenenHand[aanBeurt].size();

	// dubbele for loop loopt ieder bord vakje af
	for (int i = 0; i < hoogte; i++) {
		for (int j = 0; j < breedte; j++) {

			// checkt of de plek vrij is & er tenminste een aanliggende steen is
			if (bord[i][j].first == -1 && (
				(i-1 >= 0 && bord[i-1][j].first != -1) ||
				(i+1 < hoogte && bord[i+1][j].first != -1) ||
				(j-1 >= 0 && bord[i][j-1].first != -1) ||
				(j+1 < breedte && bord[i][j+1].first != -1))) {

				// gaat elke steen in de hand van de speler aan de beurt af
				for (int k = 0; k < grote; k++) {
					for (int l = 0; l < 4; l++) { // gaat iedere rotatie af
						if ( // elke zijde is of een zijkant of leeg of sluit aan
							(i-1 < 0 ||
							stenen[bord[i-1][j].first][(2+bord[i-1][j].second)%4]
							== stenen[stenenHand[aanBeurt][k]][(0+l)%4] ||
							bord[i-1][j].first == -1) && // boven
							(i+1 >= hoogte ||
							(stenen[bord[i+1][j].first][(0+bord[i+1][j].second)%4]
							== stenen[stenenHand[aanBeurt][k]][(2+l)%4] ||
							bord[i+1][j].first == -1)) && // onder
							(j-1 < 0 ||
							(stenen[bord[i][j-1].first][(1+bord[i][j-1].second)%4]
							== stenen[stenenHand[aanBeurt][k]][(3+l)%4] ||
							bord[i][j-1].first == -1)) && // links
							(j+1 >= breedte ||
							(stenen[bord[i][j+1].first][(3+bord[i][j+1].second)%4]
							== stenen[stenenHand[aanBeurt][k]][(1+l)%4] ||
							bord[i][j+1].first == -1))) { // rechts
							mogelijkeZet.setWaardes(stenenHand[aanBeurt][k], (l)%4, i, j);
							zetten.push_back(mogelijkeZet);
						}
					}
				}
			}
		}
	}
	return zetten;
}  // bepaalMogelijkeZetten

//*************************************************************************

// Haalt voor de speler die op dit moment aan de beurt is, een steen uit
// de pot(pot) en stopt deze in de speler zijn hand(stenenLiek/stenenFemke)
int AapjeOmino::haalSteenUitPot()
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
		cout << "Er is al een steen uit de pot gehaald." << endl;
		return -1;
	}
	stenenHand[aanBeurt].push_back(pot);
	pot++;
	actie = 2;
	return 0;
}  // haalSteenUitPot

//*************************************************************************

// Wisselt de speler die aan de beurt is
void AapjeOmino::wisselSpeler()
{
	aanBeurt = 1 - aanBeurt;
	actie = 0;
}  // wisselSpeler

//*************************************************************************

// Plaatst Zet zet op het bord voor de speler die aan de beurt is:
// hij stopt steen i met rotatie r op vakje(rij,kolom).
// Ook word gecontroleerd of het wel een geldige zet is.
bool AapjeOmino::doeZet(Zet zet)
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
	if (!integerInBereik ("Rij", rij, 0, MaxDimensie-1))
		return false;
	if (!integerInBereik ("Kolom", kolom, 0, MaxDimensie-1))
		return false;

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

	if (!( // kijkt of de steen past voor elk aanliggend vakje
		// checkt boven
		(rij-1 < 0 || bord[rij-1][kolom].first == -1 ||
		stenen[i][r] ==
		stenen[bord[rij-1][kolom].first][(bord[rij-1][kolom].second+2)%4]) &&
		// checkt rechts
		(kolom+1 >= breedte || bord[rij][kolom+1].first == -1 ||
		stenen[i][(r+1)%4] ==
		stenen[bord[rij][kolom+1].first][(bord[rij][kolom+1].second+3)%4]) &&
		// checkt onder
		(rij+1 >= hoogte || bord[rij+1][kolom].first == -1 ||
		stenen[i][(r+2)%4] ==
		stenen[bord[rij+1][kolom].first][bord[rij+1][kolom].second]) &&
		// checkt links
		(kolom-1 < 0 || bord[rij][kolom-1].first == -1 ||
		stenen[i][(r+3)%4] ==
		stenen[bord[rij][kolom-1].first][(bord[rij][kolom-1].second+1)%4]))) {
		cout << "Deze steen past niet." << endl;
		return false;
	}

	// kijkt of de spelere aan de beurt de steen wel in haar hand heeft
grote = stenenHand[aanBeurt].size();
for (int j = 0; j < grote; j++) {
	if (stenenHand[aanBeurt][j] == i) {
		stenenHand[aanBeurt].erase(stenenHand[aanBeurt].begin()+j);
		steenInHand = true;
	}
}
if (!steenInHand) {
	if (aanBeurt)
		cout << "Lieke heeft deze steen niet in haar hand." << endl;
	else
		cout << "Femke heeft deze steen niet in haar hand." << endl;
	return false;
}

	bord[rij][kolom].first = i;
	bord[rij][kolom].second = r;
	actie = 1;
	wisselSpeler();
	return true;
}  // doeZet

//*************************************************************************

// Bepaalt alle goede zetten voor de speler die aan de beurt is:
// de mogelijke zetten met zoveel mogelijk buurvakjes.
// En retourneert een vector met al deze zetten.
vector<Zet> AapjeOmino::bepaalGoedeZetten()
{
	vector<Zet> zetten = bepaalMogelijkeZetten();
	int sizeZetten = zetten.size();
	int buren[sizeZetten]; // aantal buren waarbij kan aansluiten
	int beste = 1; // maximale hoeveelheid buren van een steen in zetten

	for (int i = 0; i < sizeZetten; i++) {
		buren[i] = 0;
		if (zetten[i].getRij()-1 >= 0 &&
			bord[zetten[i].getRij()-1][zetten[i].getKolom()].first != -1)
			buren[i]++;
		if (zetten[i].getRij()+1 < hoogte &&
			bord[zetten[i].getRij()+1][zetten[i].getKolom()].first != -1)
			buren[i]++;
		if (zetten[i].getKolom()-1 >= 0 &&
			bord[zetten[i].getRij()][zetten[i].getKolom()-1].first != -1)
			buren[i]++;
		if (zetten[i].getKolom()+1 < breedte &&
			bord[zetten[i].getRij()][zetten[i].getKolom()+1].first != -1)
			buren[i]++;
		if (buren[i] > beste)
			beste = buren[i];
	}

	// haal alle stenen eruit met minder buren dan 'beste'
	for (int i = sizeZetten-1; i >= 0; i--) {
		if (buren[i] < beste)
			zetten.erase(zetten.begin() + i);
	}

	return zetten;
}  // bepaalGoedeZetten

//*************************************************************************

// Haalt de laatste gepakte steen uit de hand van de bijbehorende speler
// En stopt deze terug in de pot
void AapjeOmino::doeSteenInPot()
{
	pot--;
	stenenHand[aanBeurt].pop_back();
}  // doeSteenInPot

//*************************************************************************

// Haalt de Zet zet weer weg van het bord. Doe het in de hand van de speler
// die nu niet aan de beurt is. Controleer of er zonder die steen zetten
// mogelijk waren -> zo niet, doe de steen terug in de pot.
void AapjeOmino::unDoeZet (Zet zet)
{
	wisselSpeler();
	bord[zet.getRij()][zet.getKolom()].first = -1;
	bord[zet.getRij()][zet.getKolom()].second = 0;
stenenHand[aanBeurt].push_back(zet.getI());
sorteer(stenenHand[aanBeurt]);
}  // unDoeZet

//*************************************************************************

// Bepaalt met behulp van brute force de eindscore voor de speler die in
// de huidige stand (= de stand van de huidige recursieve aanroep) aan de beurt is,
// wanneer beide spelers vanaf dit punt optimaal verder spelen.
// De score is het aantal resterende stenen van de andere speler min
// het aantal resterende stenen van de huidige speler (hoe hoger hoe beter).
// De berekende eindscore word geretourneerd en als de huidige speler in
// deze beurt daadwerkelijk een steen kan opleggen
// (eventueel na een steen uit de pot gehaald te hebben),
// bevat parameter besteZet een zet voor de huidige speler aan beurt
// die tot de beste score kan leiden
// Anders bevat parameter besteZet een passende default waarde
// Het aantalStanden is gelijk aan het aantal standen dat we hebben
// bekeken bij het bepalen van de beste eindscore
// aan het eind is de stand in het spel is onveranderd
int AapjeOmino::besteScore (Zet &besteZet, long long &aantalStanden)
{
	vector<Zet> zetten;
	int maxscore = -nrStenen;
	int score = -nrStenen;
	int aantalMogenlijkeZetten;

	aantalStanden++;
	if (eindstand()) {
	return eindscore();
	}
	else {
		zetten = bepaalMogelijkeZetten();
		aantalMogenlijkeZetten = zetten.size();
		if (aantalMogenlijkeZetten == 0) { // geen mogenlijke zetten
			haalSteenUitPot();
			zetten = bepaalMogelijkeZetten();
			aantalMogenlijkeZetten = zetten.size();
			if (aantalMogenlijkeZetten == 0) { // na pakken kan nog steeds geen zet
				wisselSpeler();
				niv++;
				score = -besteScore(besteZet, aantalStanden);
				niv--;
				if (score > maxscore) {
					maxscore = score;
					if (niv == 0)
						besteZet.setDefaultWaardes();
				}
				wisselSpeler();
			} else { // na het pakken kan er wel een zet
				for (int i = 0; i < aantalMogenlijkeZetten; i++) {
					doeZet(zetten[i]);
					niv++;
					score = -besteScore(besteZet, aantalStanden);
					niv--;
					if (score >= maxscore) {
						maxscore = score;
						if (niv == 0)
							besteZet = zetten[i];
					}
					unDoeZet(zetten[i]);
				}
			}
			doeSteenInPot();
		}
		else { // er is wel een mogenlijke zet
			for (int i = 0; i < aantalMogenlijkeZetten; i++) {
				doeZet(zetten[i]);
				niv++;
				score = -besteScore(besteZet, aantalStanden);
				niv--;
				if (score >= maxscore) {
					maxscore = score;
					if (niv == 0)
				besteZet = zetten[i];
				}
				unDoeZet(zetten[i]);
			}
		}
		return maxscore;
	}
}  // besteScore

//*************************************************************************

int AapjeOmino::eindscore() {
return static_cast<int>(stenenHand[1-aanBeurt].size()-stenenHand[aanBeurt].size());
}

// Genereer een spel met bepaalde parameters en random getallen tussen
// minGetal en maxGetal (inclusief) op de stenen.
bool AapjeOmino::genereerRandomSpel (int hoogte0, int breedte0,
	int nrStenen0, int nrStenenInHand0, int rij0, int kolom0,
	int minGetal, int maxGetal)
{
	if (!integerInBereik ("hoogte0", hoogte0, 1, MaxDimensie))
		return false;

	if (!integerInBereik ("breedte0", breedte0, 1, MaxDimensie))
		return false;

	if (nrStenen0 < nrStenenInHand0 * 2 + 1) {
		cout << "Er zijn te weinig stenen." << endl;
		return false;
	}

	if (!integerInBereik("rij0", rij0, 1, breedte0) ||
	!integerInBereik("kolom0", kolom0, 1, hoogte0)) {
		cout << "De startsteen ligt niet op het bord." << endl;
		return false;
	}
	
	hoogte = hoogte0;
	breedte = breedte0;
	nrStenen = nrStenen0;

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
	stenenHand[aanBeurt].push_back(pot);
	pot++;
	wisselSpeler();
	}
	return true;
}  // genereerRandomSpel

//*************************************************************************
