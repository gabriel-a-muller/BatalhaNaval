#ifndef PILHA_H
#define PILHA_H
#include <iostream>
#include <vector>
using namespace std;

//Classe que caracteriza um ponto de jogada.
//Utilizada em um processo de pilha de jogadas.
class Ponto{
private:
	int x,y;
	char dado;
public:
	Ponto(){}
	Ponto(int x, int y){this->x = x; this->y = y;}
	Ponto(const Ponto &p){x = p.x; y = p.y; dado = p.dado;}
	int getX(){return x;}
	int getY(){return y;}
	char getDado(){return dado;}
	void setDado(char d){dado = d;}
};


template<typename T>
class Pilha {
private:
	std::vector<T> pilha;
    int _topo;
    
public:
    Pilha() : pilha(10){_topo=0;}
    Pilha<T>(int t) : pilha(t){_topo = 0;}
	void empilha(T dado);
	T desempilha();
	T topo();
	int getPosTopo();
	void limparPilha();
	bool PilhaVazia();
	bool PilhaCheia();
};

template<typename T> void Pilha<T>::empilha(T dado){
    if(PilhaCheia() == true) throw 1;
    pilha[_topo] = dado;
    _topo++;
}
template<typename T> T Pilha<T>::desempilha(){
    if(PilhaVazia() == 1) throw 2;
    else{
    _topo--;
    return pilha[_topo];
    }
    
}
template<typename T> T Pilha<T>::topo(){
    
    if(_topo == 0) throw 3;
    return pilha[_topo-1];
}	 	  	 	      	   	 	      	      	 	  	 	
template<typename T> int Pilha<T>::getPosTopo(){
    if(_topo==0) throw 4;
    return _topo-1;
    
}
template<typename T> void Pilha<T>::limparPilha(){
    _topo = 0;
}
template<typename T> bool Pilha<T>::PilhaVazia(){
    if(_topo==0) return true;
    else return false;
}
template<typename T> bool Pilha<T>::PilhaCheia(){
    if(_topo==(int)pilha.capacity()) return true;
    else return false;
}
#endif
