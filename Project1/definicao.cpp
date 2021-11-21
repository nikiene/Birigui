#include "structs.h"
#include "constantes.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int PL = 5, BL = 5;

void initBot(Player& b) {
	b.x1 = (width / 2) - 50;
	b.y1 = height / 4;
	b.x2 = (width / 2) + 50;
	b.y2 = b.y1 + 25;
}

void initPlayer(Player& p) {
	p.x1 = (width / 2) - 50;
	p.y1 = (3 * height) / 4;
	p.x2 = (width / 2) + 50;
	p.y2 = p.y1 + 25;
}

void initBall(Ball& b) {
	b.x = width / 2;
	b.y = height / 2;
	b.raio = 10.0;
}

void InitObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		obstaculo[i].ID = OBSTACULOS;
		obstaculo[i].velocidade = 1.0;
		obstaculo[i].status = MORTO;
	}
}

void CreateObstaculo(Obstaculo obstaculo[], int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		if (obstaculo[i].status == MORTO) {
			obstaculo[i].tipo = rand() % 2;
			obstaculo[i].posicao = rand() % 3;
			obstaculo[i].edgeRate = 1;
			obstaculo[i].edgeRate2 = 1;
			switch (obstaculo[i].posicao) {
			case 0:
				obstaculo[i].x1 = 280 + 25;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 30;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			case 1:
				obstaculo[i].x1 = 280 + 40;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 45;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			case 2:
				obstaculo[i].x1 = 280 + 55;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 70;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			case 3:
				obstaculo[i].status = MORTO;
			}
			return;
		}
	}
}

void UpdateObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (obstaculo[i].status == VIVO) {
			obstaculo[i].y1 += obstaculo[i].velocidade;
			obstaculo[i].y2 += obstaculo[i].velocidade + obstaculo[i].edgeRate2;
			obstaculo[i].edgeRate2 += (double) 0.15;
			if (obstaculo[i].posicao == 0) {
				obstaculo[i].x1 -= obstaculo[i].edgeRate;
				obstaculo[i].x2 -= obstaculo[i].edgeRate / 2;
				obstaculo[i].edgeRate += 0.29;
			}
			else if (obstaculo[i].posicao == 1) {
				obstaculo[i].x1 -= obstaculo[i].edgeRate / 2;
				obstaculo[i].x2 += obstaculo[i].edgeRate / 2;
				obstaculo[i].edgeRate += 0.15;
			}
			else if (obstaculo[i].posicao == 2) {
				obstaculo[i].x1 += obstaculo[i].edgeRate / 2;
				obstaculo[i].x2 += obstaculo[i].edgeRate;
				obstaculo[i].edgeRate += 0.29;
			}
			obstaculo[i].velocidade += 0.5;
			if (obstaculo[i].y1 < 150 && obstaculo[i].y1 < 250) {
				obstaculo[i].velocidade -= 0.01;
			}
			else if (obstaculo[i].y1 >= 150 && obstaculo[i].y1 < 315) {
				obstaculo[i].velocidade += 0.15;
			}
			else if (obstaculo[i].y1 >= 315 && obstaculo[i].y1 <= 500) {
				obstaculo[i].velocidade += 0.01;
			} if (obstaculo[i].y1 > height) {
				obstaculo[i].status = MORTO;
				obstaculo[i].velocidade = 1;
				obstaculo[i].edgeRate = 1;
				obstaculo[i].edgeRate2 = 1;
			}
		}
	}
}

void InitJogador(Jogador& jogador) {
	jogador.ID = JOGADOR;

	jogador.posicao = MEIO;

	jogador.x1 = 295; //25
	jogador.x2 = 345; //25
	jogador.y1 = 450; //parte inferior da tela "chao"
	jogador.y2 = 375; //chao + 75

	jogador.status = VIVO;
}

bool endgame(int PL, int BL) {
	if (PL == 0) {
		return true;
	}
	else if (BL == 0) {
		return true;
	}
}
