// Implementatie van klasse Zet
// zet.cc
// Laatste verandering : 29-3-2021 
// Geschreven door : Bart Aaldering (s2969866) en Lex Janssens (s2989344)
// Compiler : GNU GCC Compiler
// Beschrijving :
/*
 Hierin staan de functies bedoeld voor een zet. Waardes zoals het steen-
 nummer, rotatie en positie worden hierin opgeslagen en worden ook
 gebruikt bij het controleren van mogelijke zetten.
*/
#include "standaard.h"
#include "zet.h"
#include <iostream>
using namespace std;

//*************************************************************************

Zet::Zet ()
{
	i = 0; //steen nr
	r = 0; //rotatie steen
	rij = 0; 
	kolom = 0;
}  // default constructor

//*************************************************************************

void Zet::setDefaultWaardes ()
{
	i = -1;
	r = -1;
	rij = -1;
	kolom = -1;
}  // setDefaultWaardes

//*************************************************************************

void Zet::setWaardes (int i0, int r0, int rij0, int kolom0)
{

	if (i0>=0)
		i = i0;
	else {
		i = 0;
		cout << endl;
		cout << "i0 mag niet negatief zijn, maar is " << i0 << endl;
	}

	if (integerInBereik ("r0", r0, 0, 3))
		r = r0;
	else
		r = 0;

	if (rij0>=0)
		rij = rij0;
	else {
		rij = 0;
		cout << endl;
		cout << "rij0 mag niet negatief zijn, maar is " << rij0 << endl;
	}

	if (kolom0>=0)
		kolom = kolom0;
	else {
		kolom = 0;
		cout << endl;
		cout << "kolom0 mag niet negatief zijn, maar is " << kolom0 << endl;
	}
}  // setWaardes

//*************************************************************************

int Zet::getI ()
{
	return i;
}  // getI

//*************************************************************************

int Zet::getR ()
{
	return r;
}  // getR

//*************************************************************************

int Zet::getRij ()
{
	return rij;
}  // getRij

//*************************************************************************

int Zet::getKolom ()
{
	return kolom;
}  // getKolom

//*************************************************************************

void Zet::drukAf ()
{
	cout << "(steen " << i << ", rotatie " << r << ", vakje [" 
		<< rij << "," << kolom << "])" << endl;
}  // drukAf

