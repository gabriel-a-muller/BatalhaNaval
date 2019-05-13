#ifndef BARCO_H
#define BARCO_H

#include <iostream>
#include <string>
using namespace std;

//Classe para tratamento de excecao.
class ExcecaoInvalida {
private:
	string erro;
public:
	ExcecaoInvalida(string errotxt = ""){erro=errotxt;}
	string consultaErro()const{return erro;}
};

//Classe que representa os barcos do tabuleiro.
class Barco{
private:
	string nome;
	int tamanho;
	int vida;
	int x,y;
	char sentido;
	int jogador;
public:
	Barco() {}
	Barco(string n, int t, int j=0);
	Barco(const Barco& b);

	//metodos get da classe.
	string getNome(){return nome;}
	int getTamanho(){return tamanho;}
	int getVida(){return vida;}
	int getX(){return x;}
	int getY(){return y;}
	char getSentido(){return sentido;}
	int getJogador(){return jogador;}
	
	//metodos set da classe.
	void setXY(int x, int y, char s);	
	void setJogador(int j) {jogador = j;}

	bool verificaTiro(int x, int y);
};

//Construtor da classe Barco.
//Parametros: nome, tamanho, posicoes iniciais, sentido.
Barco::Barco(string n, int t, int j){
	nome = n; tamanho = t; 
	vida = t;
	jogador = j;
}

//Construtor de copia.
Barco::Barco(const Barco& b){
	nome = b.nome; tamanho = b.tamanho; sentido = b.sentido;
	x = b.x; y = b.y;
	vida = b.vida;
	jogador = b.jogador;
}

void Barco::setXY(int x, int y, char s){
	this->x = x;
	this->y = y;
	sentido = s;
	return;
}

//Metodo que verifica se o barco foi acertado ou nao.
//Parametros: recebe a posicao do tiro como parametro.
//Se a posicao do tiro estiver no intervalo de posicoes do barco, decrementa vida.
//Retorna true caso o barco for destruido, false caso contrario.
bool Barco::verificaTiro(int x, int y){
	if(sentido == 'h' || sentido == 'H'){
		if((this->x) != x) return false;	
		int aux = y - (this->y);
		if(aux >= tamanho || aux < 0) return false;
		vida--;
	}
	else if(sentido == 'v' || sentido == 'V'){
		if(this->y != y){return false;}	
		int aux = x - this->x;
		if(aux >= tamanho || aux < 0){return false;}
		vida--;
	}
	if(vida == 0){return true;}
	return false;
	//throw(ExcecaoInvalida("Sentido Inválido."));
}
#endif
