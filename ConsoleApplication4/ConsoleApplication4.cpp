#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>

class Reflektor {
private:
	short int ile_liter;
	short int* permutacja;
public:
	void set_ile_liter(int a);
	short int* get_permutacja();
	void wczytaj_permutacje();
};

class Wirnik {
private:
	short int ile_liter;
	short int* permutacja_poczatkowa;
	short int ile_obraca;
	short int* litery_obracajace;
	short int* przesuniecia;
	short int obecna_pozycja = 1;
	short int* powrot;
public:
	//~Wirnik();
	void set_ile_liter(short int a);
	void set_ile_obraca(short int a);
	void wczytaj_permutacje();
	void wczytaj_obracajace();
	short int* get_przesuniecia();
	short int get_obecna_pozycja();
	void set_obecna_pozycja(short int a);
	void przesun();
	void ustaw_przesuniecia();
	bool czy_obrocic();
	short int* get_powrot();
};

//Wirnik::~Wirnik() {}
void Wirnik::set_ile_liter(short int a) {
	this->ile_liter = a;
}
short int* Wirnik::get_powrot() {
	return powrot;
}
void Wirnik::set_ile_obraca(short int a) {
	this->ile_obraca = a;
}
void Wirnik::wczytaj_permutacje() {
	this->permutacja_poczatkowa = new short[ile_liter];
	for (int i = 0; i < ile_liter; i++) {
		scanf("%hi", &permutacja_poczatkowa[i]);
	}
}
void Wirnik::wczytaj_obracajace() {
	this->litery_obracajace = new short[ile_obraca];
	for (int i = 0; i < ile_obraca; i++) {
		scanf("%hd", &litery_obracajace[i]);
	}
}
short int* Wirnik::get_przesuniecia() {
	return przesuniecia;
}
short int Wirnik::get_obecna_pozycja() {
	return obecna_pozycja;
}
void Wirnik::set_obecna_pozycja(short int a) {
	this->obecna_pozycja = a;
}
void Wirnik::przesun() {
	if (obecna_pozycja == ile_liter) obecna_pozycja = 1;
	else obecna_pozycja++;
}
void Wirnik::ustaw_przesuniecia() {
	this->przesuniecia = new short[ile_liter];
	this->powrot = new short[ile_liter];
	for (int i = 0; i < ile_liter; i++) {
		//this->przesuniecia[i] = this->szukaj_p(i + 1) - i;
		przesuniecia[i] = permutacja_poczatkowa[i] - i - 1;
		powrot[i + przesuniecia[i]] = -przesuniecia[i];
	}
}
bool Wirnik::czy_obrocic() {
	if (obecna_pozycja != ile_liter)
		for (int i = 0; i < ile_obraca; i++) {
			if (obecna_pozycja + 1 == litery_obracajace[i]) return true;
		}
	else for (int i = 0; i < ile_obraca; i++) {
		if (1 == litery_obracajace[i]) return true;
	}
	return false;
}



short int* Reflektor::get_permutacja() {
	return permutacja;
}
void Reflektor::set_ile_liter(int a) {
	this->ile_liter = a;
}
void Reflektor::wczytaj_permutacje() {
	//this->permutacja = (short int*)malloc(ile_liter * sizeof(int));
	this->permutacja = new short[ile_liter];
	for (int i = 0; i < ile_liter; i++) {
		scanf("%hd", &permutacja[i]);
	}
}



int main()
{
	short int ile_liter = 0;
	scanf("%hd", &ile_liter);
	short int ile_wirnikow = 0;
	scanf("%hd", &ile_wirnikow);
	Wirnik* wirniki = new Wirnik[ile_wirnikow];
	for (int i = 0; i < ile_wirnikow; i++) {
		wirniki[i].set_ile_liter(ile_liter);
		wirniki[i].wczytaj_permutacje();
		short int ile_obraca;
		scanf("%hd", &ile_obraca);
		wirniki[i].set_ile_obraca(ile_obraca);
		wirniki[i].wczytaj_obracajace();
	}
	short int liczba_reflektorow;
	scanf("%hd", &liczba_reflektorow);
	Reflektor* reflektory = new Reflektor[liczba_reflektorow];
	for (int i = 0; i < liczba_reflektorow; i++) {
		reflektory[i].set_ile_liter(ile_liter);
		reflektory[i].wczytaj_permutacje();
	}

	short int liczba_zadan;
	scanf("%hd", &liczba_zadan);
	for (int i = 0; i < liczba_zadan; i++) {
		short int ile_aktywnych_wirnikow;
		scanf("%hd", &ile_aktywnych_wirnikow);
		Wirnik* aktywne_wirniki = new Wirnik[ile_aktywnych_wirnikow];
		for (int j = 0; j < ile_aktywnych_wirnikow; j++) {
			short int indeks_wirnika;
			scanf("%hd", &indeks_wirnika);
			aktywne_wirniki[j] = wirniki[indeks_wirnika];
			short int pozycja_poczatkowa;
			scanf("%hd", &pozycja_poczatkowa);
			aktywne_wirniki[j].ustaw_przesuniecia();
			aktywne_wirniki[j].set_obecna_pozycja(pozycja_poczatkowa);
		}
		short int indeks_reflektora;
		scanf("%hd", &indeks_reflektora);
		Reflektor aktywny_reflektor = reflektory[indeks_reflektora];
		bool odwrocony_2 = false;
		bool odwrocony_1 = false;
		for (;;) {
			short int oryginal;
			scanf("%hd", &oryginal);
			if (oryginal == 0) break;
			else {
				if (ile_aktywnych_wirnikow > 2 && aktywne_wirniki[1].czy_obrocic() && odwrocony_2) {
					aktywne_wirniki[2].przesun();
					aktywne_wirniki[1].przesun();
					aktywne_wirniki[0].przesun();
				}
				else if (ile_aktywnych_wirnikow > 1 && aktywne_wirniki[0].czy_obrocic() && odwrocony_1) {
					if (!odwrocony_2) odwrocony_2 = true;
					aktywne_wirniki[1].przesun();
					aktywne_wirniki[0].przesun();
				}
				else {
					aktywne_wirniki[0].przesun();
					if (!odwrocony_1) odwrocony_1 = true;
				}
				int indeks = oryginal - 1;
				for (int j = 0; j < ile_aktywnych_wirnikow; j++) {
					indeks = (indeks + (aktywne_wirniki[j].get_przesuniecia()[(indeks + aktywne_wirniki[j].get_obecna_pozycja() - 1 + ile_liter) % ile_liter] + ile_liter) % ile_liter) % ile_liter;
					if (indeks < 0) indeks += ile_liter;
				}
				indeks = aktywny_reflektor.get_permutacja()[indeks] - 1;
				for (int j = ile_aktywnych_wirnikow - 1; j >= 0; j--) {
					indeks = (indeks + (aktywne_wirniki[j].get_powrot()[(indeks + aktywne_wirniki[j].get_obecna_pozycja() - 1 + ile_liter) % ile_liter] + ile_liter) % ile_liter) % ile_liter;
				}
				printf("%d\n", indeks + 1);

			}
		}
		delete[] aktywne_wirniki;
	}
	delete[] wirniki;
	delete[] reflektory;
	return 0;
}