#ifndef BATALHA_H
#define BATALHA_H

#include "Tabuleiro.h"
#include "Formata.h"
#include "Inteligencia.h"
#include <vector>
#include <typeinfo>

template <typename T=Computador>
class Batalha{

private:
	Tabuleiro t1,t2;
	Inteligencia ia;
	vector <Barco> bv1, bv2;
	T formata;
	int jogador;
	int barcoDestruido;
	string aux,aux1;
public:
	Batalha();
	//metodos get set
	Tabuleiro& getTab2(){return t2;}
	vector<Barco> getB1(){return bv1;}
	vector<Barco> getB2(){return bv2;}
	T getFormata(){return formata;}
	void setVetor(vector<Barco> c){bv2 = c;}

	//Metodos da classe responsaveis pela criacao de tabuleiros.
	void insereBarco(Barco &b);
	void criaTabuleiros();
	void criaTabuleiros(vector<Barco> c);
	
	//Metodos para recebimento e organizacao dos tiros.
	void setTiro();
	void sessaoTiros();	
	
};

//Construtor padrao.
//Cria todos os barcos possiveis e os armazena em vetores
//para utilizacao nos tabuleiros.
template<typename T> Batalha<T>::Batalha():bv1(11),bv2(11){
	Barco f("Fragata",2), b("Balizador",2), c("Contratorpedeiro",3), cz("Cruzador",3), pa("Porta-aviões",4);
	for(int i=0;i<3;i++){
		f.setJogador(1);
		b.setJogador(1);
		bv1[i] = f;
		bv1[i+3] = b;
		f.setJogador(2);
		b.setJogador(2);
		bv2[i] = f;
		bv2[i+3] = b;
	}
	for(int i=6;i<8;i++){
		c.setJogador(1);
		cz.setJogador(1);
		bv1[i] = c;
		bv1[i+2] = cz;
		c.setJogador(2);
		cz.setJogador(2);
		bv2[i] = c;
		bv2[i+2] = cz;
	}
	pa.setJogador(1);
	bv1[10] = pa;
	pa.setJogador(2);
	bv2[10] = pa;

	barcoDestruido = -1;
	jogador = 1; //primeiro jogador
}

//Insere o barco enviado como parametro.
//Havera tratamento de excecao se necessario.
//Retorna void.
template<typename T> void Batalha<T>::insereBarco(Barco &b){
	string nome = b.getNome();
	int tamanho = b.getTamanho();
	int jogador = b.getJogador();
	string sent = "";
	int x,y;
	cout << "Barco atual: " << nome << endl << endl;
while(1){
try{
	cout << "Insira o sentido: ";
	
	cin.clear();
	getline(cin,sent);
	char s = sent[0];
	if(s != 'H' && s!='h' && s!='V' && s!='v') throw(ExcecaoInvalida("Sentido Inválido!"));

	cout << "Insira a posição: ";
	cin.clear();
	string input,one="";
	getline(cin,input);
	
	stringstream ss,sss;
	ss << input[0];
	sss << input[1] << input[2] << input[3];
	char k;
	ss >> k;
	sss >> x;
	y = (int)k - 65;
	x--;
	if(jogador==1) t1.inserePosicao(x,y,s,tamanho);
	else t2.inserePosicao(x,y,s,tamanho);
	
	b.setXY(x,y,s);
	break;
}
catch(ExcecaoInvalida &e){ 
	system("tput reset");
	cout << "Posicionamento" << endl;
	if(jogador==1){ t1.imprimeJogador(); cout << endl; t1.imprimeVisivel();}
	else {t2.imprimeJogador(); cout << endl; t2.imprimeVisivel();}
	cout << endl;
	cout << e.consultaErro() << endl << endl;
			
}
}
	return;
}

//Cria os dois tabuleiros existentes do jogo.
//Posiciona os barcos no tabuleiro, um tabuleiro por vez.
//Usado em caso de jogo Humano vs Humano.
template<typename T> void Batalha<T>::criaTabuleiros(){
	system("tput reset");
	cout << "Posicionamento" << endl;
	t1.imprimeJogador(); cout << endl;
	t1.imprimeVisivel();
	cout << endl;
	for(int i=0;i<11;i++){
		insereBarco(bv1[i]);
		system("tput reset");
		cout << "Posicionamento" << endl;
		t1.imprimeJogador(); cout << endl;
		t1.imprimeVisivel();
		cout << endl;
	}	

	system("tput reset");
	cout << "Posicionamento" << endl;
	t2.imprimeJogador(); cout << endl;
	t2.imprimeVisivel();
	cout << endl;
	for(int i=0;i<11;i++){
		insereBarco(bv2[i]);
		system("tput reset");
		cout << "Posicionamento" << endl;
		t2.imprimeJogador(); cout << endl;
		t2.imprimeVisivel();
		cout << endl;
	}		
	t1.setJogador(1);
	t2.setJogador(2);
	return;
}

template<typename T> void Batalha<T>::criaTabuleiros(vector <Barco> cv1){
	system("tput reset");
	t1.setJogador(1);
	t2.setJogador(2);
	cout << "Posicionamento" << endl;
	t1.imprimeJogador(); cout << endl;
	t1.imprimeVisivel();
	cout << endl;
	for(int i=0;i<11;i++){
		insereBarco(bv1[i]);
		system("tput reset");
		cout << "Posicionamento" << endl;
		t1.imprimeJogador(); cout << endl;
		t1.imprimeVisivel();
		cout << endl;
	}
	bv2 = cv1;
	return;	
}

//Seta os tiros recebidos como entrada.
//Verifica excecoes.
//Opcao de	 desistencia (00).
template<typename T> void Batalha<T>::setTiro(){
	int x,y;
while(1){
try{
	if(barcoDestruido != -1){
		if(jogador==1){
				cout << bv1[barcoDestruido].getNome() << " destruído!" << endl << endl;
				bv1.erase(bv1.begin()+barcoDestruido);}
		else{
				cout << bv2[barcoDestruido].getNome() << " destruído!" << endl << endl;
				bv2.erase(bv2.begin()+barcoDestruido);}
		barcoDestruido = -1;}

	cout << "Digite 00 para desistencia." << endl;
	cout << "Jogador " << jogador << ": ";
	cin.clear();
	string input,one="";

	getline(cin,input);
	stringstream ss,sss;
	ss << input[0];
	sss << input[1] << input[2] << input[3];
	char k;
	ss >> k;
	sss >> x;
	y = (int)k - 65;
	x--;	
	
	if(x < 0 && y < 0){
		if(jogador == 1) t1.setBarcos(0);
		else t2.setBarcos(0);
		break;
	}
	if(jogador == 1){ 
		t2.setTiro(x,y);
		for(int i=0; i < t2.getBarcos(); i++){
			bv2[i].verificaTiro(x,y);
			
			if(t2.barcoDestruido(bv2[i])){
				barcoDestruido = i;
				string temp = bv2[i].getNome();
				stringstream imp;
				imp << temp << " do jogador 2 destruído!";
				bv2.erase(bv2.begin()+barcoDestruido);
				aux = imp.str();
			}
		}
		jogador = 2;
	}
	else{
		t1.setTiro(x,y); 
		for(int i=0; i < t1.getBarcos(); i++){
			bv1[i].verificaTiro(x,y);
			if(t1.barcoDestruido(bv1[i])){	
				barcoDestruido = i;	
				string temp = bv1[i].getNome();
				stringstream imp;
				imp << bv1[i].getNome() << " do jogador 1 destruído!";
				bv1.erase(bv1.begin()+barcoDestruido);
				aux = imp.str();
			}
		}
		jogador = 1;
	}
	break;
}
catch(ExcecaoInvalida &e){ 
	formata.imprimeJogo(t1,t2);
	cout << e.consultaErro() << endl << endl;
}			
}
	return;
}

//Funcao que organiza de forma estetica 
//do processo dos tiros.
//Analisa o tipo de jogo (se eh contra o computador ou nao)
//Define o vencedor.
template<typename T> void Batalha<T>::sessaoTiros(){
	string tName = typeid(T).name();
	while(t1.getBarcos() != 0 && t2.getBarcos() != 0 && t1.getTiros() != 0 && t2.getTiros() != 0){
		formata.imprimeJogo(t1,t2);		
		cout << "Jogada: " << aux1 << endl;
	
		cout << aux << endl << endl;
		barcoDestruido = -1;
	
		if(tName=="10Computador" && jogador == 2){
			int x,y;
			jogador = 1;
			string input = ia.computaIA(t1);
			aux1 = input;
			stringstream ss,sss;
			ss << input[0];
			sss << input[1] << input[2] << input[3];
			char k;
			ss >> k;
			sss >> x;
			y = (int)k - 65;
			x--;	
			for(int i=0; i < t1.getBarcos(); i++){
			bv1[i].verificaTiro(x,y);
			if(t1.barcoDestruido(bv1[i])){
				barcoDestruido = i;
				string temp = bv1[i].getNome();
				stringstream imp;
				imp << temp << " do jogador 1 destruído!";
				bv1.erase(bv1.begin()+barcoDestruido);
				aux = imp.str();
			}
		}
		}
		else setTiro();
	}
	if(t1.getBarcos() == 0 || t2.getTiros() == 0) cout << "Jogador 2 Venceu!" << endl;
	else cout << "Jogador 1 Venceu!" << endl;	
}
#endif
