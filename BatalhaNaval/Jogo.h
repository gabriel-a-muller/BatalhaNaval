#include "Batalha.h"

//Classe responsavel pelo manuseio dos comandos e chamadas das operacoes de jogo.
class Jogo{
private:
	Inteligencia player;
public:
	Jogo(){}
	void jogoHumano(); 
	void jogoComputador(); 
	void jogoMenu();
};

//Metodo que opera as chamadas para o modo jogador x jogador.
void Jogo::jogoHumano(){
	Batalha<Humano> jogo;
	cout << "Início" << endl;
	//o jogo só para ao dar empate ou encontrar algum vencedor.
	cin.clear();
	cin.ignore();
	jogo.criaTabuleiros();
	jogo.sessaoTiros();
	return;
}

//Metodo que faz a decisao da dificuldade do modo jogador x computador.
void Jogo::jogoComputador(){
	Batalha<Computador> jogo;
	Inteligencia player;
	player.criaTabuleiro(jogo.getTab2());
	
	cout << "Início" << endl;
	cin.clear();
	cin.ignore();
	jogo.criaTabuleiros(player.getVetor());
	jogo.sessaoTiros();
	return;
}


//Menu do jogo. Neste metodo eh apresentado as opcoes de jogo existentes
//e chamadas dos metodos pedidos pelo usuario.
void Jogo::jogoMenu(){
	cout << "BATALHA NAVAL! " << endl << endl;
	//laco de continuacao do jogo.
	while(1){
	try{	
		cout << endl << endl;
		cout << "Opções de jogo: " << endl << "1- Contra outro jogador" << endl << "2- Contra o computador" << endl;
		cout << "0- Sair do jogo" << endl;
		int d;
		cin >> d;
		cout << endl;
		if(d==1) jogoHumano();
		else if(d==2){ jogoComputador(); break;}
		else if(d==0) return;
		else throw(ExcecaoInvalida("Comando inexistente!"));
	}
	catch(ExcecaoInvalida &e){cout << e.consultaErro() << endl << endl;}
	}
}	
