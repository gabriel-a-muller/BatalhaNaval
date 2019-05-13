Batalha Naval
Autor: Gabriel Alexandre Müller.

O programa implementado consiste no jogo batalha naval, com duas opções de jogo, a primeira pode-se jogar duas pessoas e a
segunda joga-se contra o computador.

Regras de jogo:
	-Vence quem destruir todos os barcos do adversário primeiro.
	-Não é possível atirar em lugares já atingidos.
	-Tabuleiro 15x15. (Linhas de 1 a 15; Colunas de A a O).
	-11 barcos no total. (Tamanhos entre 2 e 4).
	-Máximo de 70 tiros por jogador.
	
Entrada:
	Primeiramente, o jogador deve escolher o modo de jogo no menu de jogo.
	Ao escolher um dos modos, abrirá a opção de posicionamento dos barcos para o tabuleiro 1.
		-Se o modo de jogor for Humano x Computador, o segundo tabuleiro terá posicionamento aleatório.
		-Caso for o modo Humano x Humano, ambos irão posicionar os seus barcos manualmente, sendo o jogador 1
	o primeiro.

	 O posicionamento dependerá de dois dados de entrada, sendo o primeiro o sentido desejado (Horizontal/Vertical), seguido
    pela posição inicial do barco:

				Insira o sentido: H
				Insira a posição: O15

	Em seguida iniciará o processo de tiros. A entrada deve seguir os seguintes exemplos:

		A0, B15, K12, G7.

	Há a opção de desistência, basta digitar "00" como entrada e o vencedor será o adversário do desistente.
