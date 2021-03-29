// Definitie van klasse Zet
// zet.h
// Laatste verandering : 29-3-2021
// Geschreven door : Bart Aaldering (s2969866) en Lex Janssens (s2989344)
// Compiler : GNU GCC Compiler
// Beschrijving :
/*
 Declaraties van object Zet
*/
#ifndef ZetHVar  // voorkom dat dit bestand meerdere keren
#define ZetHVar  // ge-include wordt

class Zet
{ 
	public:
	// Default constructor
	Zet ();

	// Geef de vier velden waardes die in combinatie niet voor kunnen
	// komen, als default voor `geen echte zet'.
	void setDefaultWaardes ();

	// Geef alle vier velden een waarde.
	// Controleer nog wel of het zinnige waardes zijn.
	void setWaardes (int i0, int r0, int rij0, int kolom0);

	// Vier getters:
	int getI ();
	int getR ();
	int getRij ();
	int getKolom ();

	// Druk de vier waardes van de zet af op het scherm
	void drukAf ();

	private:
	int i,  // nummer van de steen
		r,  // rotatie
		rij, kolom;  // vakje op het bord

};

#endif

