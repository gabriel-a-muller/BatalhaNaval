#include "Jogo.h"

int main (int argc, char** argv){
	Jogo naval;
	int d;
	char c;
	if(argc == 1) naval.jogoMenu();
	else{
		c = *argv[1];
		d = c - '0';
		if(argc == 2){
			if(d==1) naval.jogoHumano();
			else if(d==2) naval.jogoComputador();}}
	return 0;
}
