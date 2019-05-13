#ifndef TABULEIRO_H
#define TABULEIRO_H 

#include <sstream>
#include "Barco.h"

class Tabuleiro{

private:
	char** matriz; //' ' TIRO NA AGUA ; B = BARCO ; ~ = AGUA ; X = ACERTO EM BARCO ;
	int tiros;
	int qtdBarcos;
	int jogador;
public:
	Tabuleiro();
	Tabuleiro(int j);
	Tabuleiro(const Tabuleiro& t);
	~Tabuleiro();

	//metodos get da classe.
	int	getTiros(){return tiros;}
	int getBarcos(){return qtdBarcos;}
	char** getMatriz(){return matriz;}
	int getJogador(){return jogador;}
	

	void setBarcos(int b){qtdBarcos = b;}
	void setJogador(int j){jogador = j;}

	//metodos para posicionamento dos barcos.
	bool verificaCelula(int x, int y);
	bool verificaPosicao(int x, int y, char s, int t);
	bool inserePosicao(int x, int y, char s, int t);
	bool barcoDestruido(Barco b);

	//metodos para diferentes tipos de impressao em tela.
	void imprimeConjunto(char **m);
	void imprimeConjuntoComputador(char** m);
	void imprimeEscondido();
	void imprimeVisivel();
	void imprimeJogador(){cout << "Jogador " << jogador << ":";}

	//metodos para recebimento dos tiros.
	bool setTiro(int x, int y);
		
};

Tabuleiro::Tabuleiro(){
	matriz = new char*[15];
	for(int i = 0; i < 15; i++)
   		matriz[i] = new char[15];
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			matriz[i][j] = '~';
		}
	}
	jogador = 0;
	tiros = 70;
	qtdBarcos = 0;
}

Tabuleiro::Tabuleiro(int j){
	matriz = new char*[15];
	for(int i = 0; i < 15; i++)
   		matriz[i] = new char[15];
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			matriz[i][j] = '~';
		}
	}
	jogador = j;
	tiros = 70;
	qtdBarcos = 0;
}

Tabuleiro::Tabuleiro(const Tabuleiro& t){
	tiros = t.tiros;
	qtdBarcos = t.qtdBarcos;
	matriz = new char*[15];
	for(int i=0;i<15;i++)
		matriz[i] = new char[15];	
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++)
			matriz[i][j] = t.matriz[i][j];
	}
	jogador = t.jogador;
}

Tabuleiro::~Tabuleiro(){ 
	for(int i=0;i<15;i++){
		delete matriz[i];
	}
	delete matriz;
}

//Verifica se a celula eh agua.
//Recebe a posicao a ser verificada como parametro.
//Retorna true caso a celula seja agua, false caso contrario.
bool Tabuleiro::verificaCelula(int x, int y){
	if(matriz[x][y] != '~') return false;
	else if(matriz[x][y] == '~') return true;
	else return false;
}

//Verifica se a posicao e sentido inserido como parametro eh
//valida para o tamanho do barco.
//Return true caso haja espaco suficiente para o barco.
bool Tabuleiro::verificaPosicao(int x, int y, char s, int t){
	if( x < 0 || x > 14 || y < 0 || y > 14) return false;

	if(s == 'v' || s == 'V'){
		if( (14-x) < (t-1) ) return false;
		for(int i=0;i<t;i++)
			if(!verificaCelula(x+i,y)) return false;
	}
	else if(s == 'h' || s == 'H'){
		if( (14-y) < (t-1) ) return false;
		for(int i=0;i<t;i++)
			if(!verificaCelula(x,y+i)) return false;
	}
	return true;
}

//Insere o barco na posicao e sentido enviados como parametro.
//Havera chamada da funcao de verificacao.
//Retorna void.
bool Tabuleiro::inserePosicao(int x, int y, char s, int t){
	if(verificaPosicao(x,y,s,t)){
		if(s == 'v' || s == 'V'){
			for(int i=0;i<t;i++)
				matriz[x+i][y] = 'B';
		}
		else if(s == 'h' || s == 'H'){
			for(int i=0;i<t;i++)
				matriz[x][y+i] = 'B';
		}
	}
	else throw(ExcecaoInvalida("Posição Inválida!"));
	qtdBarcos++;
	return true;
}


//Recebe um barco destruido (vida = 0) como parametro.
//Imprime o nome do barco destruido.
//Retorna void.
bool Tabuleiro::barcoDestruido(Barco b){
	if(b.getVida()>0) return false;
	//string nome = b.getNome();
	//cout << endl << nome << " destruído!" << endl;
	qtdBarcos--;
	return true;
}

//Recebe um ponteiro duplo como parametro contendo uma matriz m[15][15].
//Imprime a matriz do tabuleiro atual ao lado da recebida como parametro.
//Impressao sem barcos visiveis.
//Retorna void.
void Tabuleiro::imprimeConjunto(char** m){
	cout << "   A B C D E F G H I J K L M N O" << "		" << "   A B C D E F G H I J K L M N O" << endl;
	for(int i=0;i<15;i++){
		if((i+1) < 10)	cout << " " << i+1 << " ";
		else cout << i+1 << " ";
		for(int j=0;j<15;j++){
			if(matriz[i][j] == 'B') 
				cout << '~' << " ";
			else
				cout << matriz[i][j] << " ";
		}
		cout << "		";
		if((i+1) < 10)	cout << " " << i+1 << " ";
		else cout << i+1 << " ";
		for(int j=0;j<15;j++){
			if(m[i][j] == 'B') 
				cout << '~' << " ";
			else
				cout << m[i][j] << " ";
		}	
		cout << endl;
	}
	return;
}

////Recebe um ponteiro duplo como parametro contendo uma matriz m[15][15].
//Imprime a matriz do tabuleiro atual ao lado da recebida como parametro.
//Impressao com barcos do jogador humano visiveis.
//Retorna void.
void Tabuleiro::imprimeConjuntoComputador(char** m){
	cout << "   A B C D E F G H I J K L M N O" << "		" << "   A B C D E F G H I J K L M N O" << endl;
	for(int i=0;i<15;i++){
		if((i+1) < 10)	cout << " " << i+1 << " ";
		else cout << i+1 << " ";
		for(int j=0;j<15;j++){
			cout << matriz[i][j] << " ";
		}
		cout << "		";
		if((i+1) < 10)	cout << " " << i+1 << " ";
		else cout << i+1 << " ";
		for(int j=0;j<15;j++){
			if(m[i][j] == 'B') 
				cout << '~' << " ";
			else
				cout << m[i][j] << " ";
			//cout << m[i][j] << " ";
		}	
		cout << endl;
	}
	return;
}

//Imprime a matriz do tabuleiro atual com os barcos escondidos.
//Retorna void.
void Tabuleiro::imprimeEscondido(){
	cout << "   A B C D E F G H I J K L M N O" << endl;
	for(int i=0;i<15;i++){
		if((i+1) < 10)	cout << " " << i+1 << " ";
		else cout << i+1 << " ";
		for(int j=0;j<15;j++){
			if(matriz[i][j] != 'X') 
				cout << '~' << " ";
			else
				cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

//Imprime a matriz do tabuleiro atual com os barcos visiveis.
//Retorna void.
void Tabuleiro::imprimeVisivel(){
	cout << "   A B C D E F G H I J K L M N O" << endl;
	for(int i=0;i<15;i++){
		if((i+1) < 10)	cout << " " << i+1 << " ";
		else cout << i+1 << " ";
		for(int j=0;j<15;j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

//Recebe a posicao de um tiro como parametro.
//Verifica se eh uma posicao valida. Throw, caso nao seja.
//Retorna true caso tenha acertado um barco, false caso acerte agua.
bool Tabuleiro::setTiro(int x, int y){
	if(x<0 || x>14 || y<0 || y>14) throw (ExcecaoInvalida("Posição de tiro inválida."));
	if(matriz[x][y] == 'X' || matriz[x][y] == ' ') throw(ExcecaoInvalida("Posição de tiro inválida."));
	if(matriz[x][y] == '~'){
		matriz[x][y] = ' ';
		tiros--;
		return false;
	}
	if(matriz[x][y] == 'B'){
		matriz[x][y] = 'X';
		tiros--;
		return true;
	}
	else return false;
}
#endif
