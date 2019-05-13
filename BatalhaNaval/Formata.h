#ifndef FORMATA_H
#define FORMATA_H
#include "Tabuleiro.h"
//#include "Batalha.h"

class Humano{
public:
	Humano(){}
	void imprimeJogo(Tabuleiro &t1, Tabuleiro &t2){
		system("tput reset");	
		char **p;
		p = t2.getMatriz();	
		cout << "JOGANDO" << endl << endl;
		t1.imprimeJogador();
		cout << "\t\t\t\t\t";
		t2.imprimeJogador();
		cout << endl;
		t1.imprimeConjunto(p);
	}
};

class Computador{
public:
	Computador(){}
	void imprimeJogo(Tabuleiro &t1, Tabuleiro &t2){
		system("tput reset");	
		char **p;
		p = t2.getMatriz();	

		cout << "JOGANDO" << endl << endl;
		t1.imprimeJogador();
		cout << "\t\t\t\t\t";
		t2.imprimeJogador();
		cout << endl;
		t1.imprimeConjuntoComputador(p);
	}
};
#endif
