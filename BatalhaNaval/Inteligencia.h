#ifndef INTELIGENCIA_H
#define INTELIGENCIA_H
#include <random>
#include "Batalha.h"
#include "Pilha.h"

class Inteligencia {
private:
	vector<Barco> cv1;	
	Pilha<Ponto> p;
	char s;
	bool step;
	string jogada;
public:
	Inteligencia();
	Inteligencia(const Inteligencia& i);

	//metodos get da classe
	string getJogada(){return jogada;}
	const vector<Barco>& getVetor() {return cv1;}
	const Pilha<Ponto>& getP(){return p;}
	
	//metodos de criacao.
	void mudaSentido();
	void criaTabuleiro(Tabuleiro &tc);
	
	//metodos da inteligencia de busca das posicoes.
	void coordenadas(int x, int y, char **m);
	bool modoCaca(Tabuleiro &tab1);
	bool modoAcerto(Ponto &pp, Tabuleiro &tab1);
	string computaIA(Tabuleiro &tab1);

};

Inteligencia::Inteligencia():cv1(11),p(200){
	Barco f("Fragata",2,2), b("Balizador",2,2), c("Contratorpedeiro",3,2), cz("Cruzador",3,2), pa("Porta-aviões",4,2);
	for(int i=0;i<3;i++){
		cv1[i] = f; 
		cv1[i+3] = b;
	}
	for(int i=6;i<8;i++){
		cv1[i] = c;
		cv1[i+2] = cz;
	}
	s = 'h';
	cv1[10] = pa;
	step = false;
	jogada = "";
}

//construtor de copia.
Inteligencia::Inteligencia(const Inteligencia& i){
	cv1 = i.cv1;
	p   = i.p;
	s   = i.s;
	step = i.step;
	jogada = i.jogada;
} 

void Inteligencia::mudaSentido(){
	if(s == 'h') s = 'v';
	else if(s == 'v') s = 'h';
	return;
}

//Cria o tabuleiro aleatoriamente para o jogador COMPUTADOR.
//Retorna void.
void  Inteligencia::criaTabuleiro(Tabuleiro &tc){
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0,14);
	int x,y;
	int t,i;
while(tc.getBarcos() < 11){
try{
	i = tc.getBarcos();
	x = dist(mt);
	y = dist(mt);
	t = cv1[i].getTamanho();
	if(tc.inserePosicao(x,y,s,t)){
		cv1[i].setXY(x,y,s);	
	}
	mudaSentido();
}
catch(ExcecaoInvalida &e){}
}
}

//Recebe uma posicao (x,y) como parametro e a matriz do tabuleiro
//Empilha na pilha p ate 4 jogadas possiveis
void Inteligencia::coordenadas(int x, int y, char **m){
	//norte.
	if( (x-1) >= 0 && m[x-1][y] != ' ' && m[x-1][y] != 'X'){
		Ponto N(x-1,y);
		p.empilha(N);
	}//sul
	if( (x+1) <= 14 && m[x+1][y] != ' ' && m[x+1][y] != 'X'){
		Ponto S(x+1,y);
		p.empilha(S);
	}//oeste
	if( (y-1) >= 0 && m[x][y-1] != ' ' && m[x][y-1] != 'X'){
		Ponto O(x,y-1);
		p.empilha(O);
	}//leste
	if( (x+1) <= 14 && m[x][y+1] != ' ' && m[x][y+1] != 'X'){
		Ponto L(x,y+1);
		p.empilha(L);
	}
	return;
}

//Procura por um barco no tabuleiro atirando aleatoriamente em posicoes pares.
//Recebe a referencia de um Tabuleiro como parametro.
//Retorna true caso acerte um barco, false caso agua.
//Ao acertar um barco, empilha ate 4 possiveis futuras posicoes
bool Inteligencia::modoCaca(Tabuleiro &tab1){
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0,14);
	int x,y;
	char **m;

while(1){
try{
	x = dist(mt); y = dist(mt);
	while(x%2!=0 || y%2!=0){
		x = dist(mt); y = dist(mt);
	}
	stringstream ss;
	ss << (char)(y+65) << x+1;
	jogada = ss.str();
	if(tab1.setTiro(x,y)){
		m = tab1.getMatriz();
		coordenadas(x,y,m);
		return true;
	}
	return false;
}
catch(ExcecaoInvalida &e){}
}
}

//Atira no ponto recebido como parametro
//Retorna true se acertou, false caso contrario.
//Caso tenha acertado, cria ate no maximo outras 4 
//possiveis jogadas.
bool Inteligencia::modoAcerto(Ponto &pp, Tabuleiro &tab1){
	int x,y;
	char **m;
while(1){
try{
	x = pp.getX();
	y = pp.getY();
	stringstream ss;
	ss << (char)(y+65) << x+1;
	jogada = ss.str();
	if(tab1.setTiro(x,y)){		
		m = tab1.getMatriz();
		coordenadas(x,y,m);
		return true;
	}
	return false;
}

catch(ExcecaoInvalida &e){
	pp = p.desempilha();
	if(p.PilhaVazia()) break;
}}return false;}

//Metodo responsavel por organizar as jogadas do computador.
//Retorna uma string com a jogada realizada.
string Inteligencia::computaIA(Tabuleiro &tab1){
	if(p.PilhaVazia()){
		modoCaca(tab1);
	}
	else if(p.PilhaVazia()==false){
		Ponto aux = p.desempilha();
		modoAcerto(aux,tab1);
	}
	return jogada;
}
#endif
