#pragma once
#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "constantes.h"
#include "desenho.h"
#include "definicao.h"
#include "placar.h"
#include "movimento.h"
#include "structs.h"
#include "skate.cpp"

//Variáveis
double aceleracao = 1.0;
int ballXDirection = 1;
int ballYDirection = 1;
int velocidadeBase = 10;
bool keys[6] = {
	false,
	false,
	false,
	false,
	false,
	false
};

bool pulo = false;
int velocidadeMaxPulo = 16;
int gravidade = 1;
int velocidadePulo = velocidadeMaxPulo;


void movementLeft(Player& p) {
	p.x1 -= 50;
	p.x2 -= 50;
}

void movementRight(Player& p) {
	p.x1 += 50;
	p.x2 += 50;
}

void moveBall(Ball& b) {
	al_draw_filled_circle(b.x, b.y, b.raio, al_map_rgb(0, 0, 0));
	b.x += ((velocidadeBase / 4) * aceleracao) * ballXDirection;
	b.y += (velocidadeBase * aceleracao) * ballYDirection;
	aceleracao += 0.002;

}

bool colide(Ball& ball, Player& player, Player& bot) {
	//Colisão com o jogador
	if ((ball.x >= player.x1 && ball.x <= player.x2) && (ball.y >= player.y1 && ball.y <= player.y2)) {
		//if (ball.x - player.x1 > player.x2 - ball.x)
			//ballXDirection *= -1;
		ballYDirection *= -1;
		return true;

	}
	//Colisão com o bot
	if ((ball.x >= bot.x1 && ball.x <= bot.x2) && (ball.y >= bot.y1 && ball.y <= bot.y2)) {
		//if (ball.x - player.x1 > player.x2 - ball.x)
			//ballXDirection *= -1;
		ballYDirection *= -1;
		return true;

	}
	//Colisão com os cantos
	if (ball.x >= width || ball.x <= 0) {
		ballXDirection *= -1;
		return true;
	}

	if (ball.y <= 0 || ball.y >= height) {
		if (ball.y <= 0) {
			if (++pontosPlayer == 5) {
				zeraPontuacao();
				setsPlayer++;
			}
		}
		else if (ball.y >= height) {
			if (++pontosBot == 5) {
				zeraPontuacao();
				setsBot++;
			}
		}
		ballYDirection *= -1;
		ball.x = width / 2;
		ball.y = height / 2;
		return true;
	}

	return false;
}

void MoveJogadorLeft(Jogador& jogador) {
	if (jogador.posicao != ESQUERDA) {
		jogador.posicao -= 1;
		jogador.x1 -= 90;
		jogador.x2 -= 90;
	}
}

void MoveJogadorRight(Jogador& jogador) {
	if (jogador.posicao != DIREITA) {
		jogador.posicao += 1;
		jogador.x1 += 90;
		jogador.x2 += 90;
	}
}

void MakeJogadorJump(Jogador& jogador) {
	jogador.y1 -= velocidadePulo;
	jogador.y2 -= velocidadePulo;

	velocidadePulo -= gravidade;

	if (velocidadePulo < -velocidadeMaxPulo) {
		velocidadePulo = velocidadeMaxPulo;
		pulo = false;
	}
}

int Collision(Obstaculo obstaculo[], Jogador& jogador) {
	for (int i = 0; i < numeroObstaculos; i++) {
		//não deve ser pulado
		if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CONE) {
			if (obstaculo[i].x1 < jogador.x1 + 50 &&
				obstaculo[i].x1 + 50 > jogador.x1 &&
				obstaculo[i].y1 < jogador.y2 + 75 &&
				obstaculo[i].y1 + 50 > jogador.y2 &&
				(obstaculo[i].y2 > 350 && obstaculo[i].y1 < 450)) {
				jogador.status = MORTO;
				return 1;
			}
		}
		//TODO: 
		//deve ser pulado
		else if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CORRIMAO) {
			if (obstaculo[i].x1 < jogador.x1 + 50 &&
				obstaculo[i].x1 + 50 > jogador.x1 &&
				obstaculo[i].y1 < jogador.y2 + 75 &&
				obstaculo[i].y1 + 25 > jogador.y2 &&
				(obstaculo[i].y2 > 425 && obstaculo[i].y1 < 450)) {
				jogador.status = MORTO;
				return 1;
			}
		}
	}
	return 0;
}

const char* combat(int acaoP, int acaoB) {
	if (acaoP == 1 && acaoB == 1) {
		return "os golpes se encontram, mas n�o machucam nenhum dos lutadores!\n";
	}
	else if (acaoP == 1 && acaoB == 2) {
		PL = PL - 1;
		return "o jogador 1 levou um gancho em cheio!\n";
	}
	else if (acaoP == 1 && acaoB == 3) {
		BL = BL - 1;
		return "o jogador 2 levou um jeb bem no nariz! Deve ter machucado\n";
	}
	else if (acaoP == 2 && acaoB == 1) {
		BL = BL - 1;
		return "o jogador 2 levou um gancho em cheio!\n";
	}
	else if (acaoP == 2 && acaoB == 2) {
		return "os golpes se encontram, mas n�o machucam nenhum dos lutadores!\n";
	}
	else if (acaoP == 2 && acaoB == 3) {
		PL = PL - 1;
		return "o jogador 2 da um chute no estomago do jogador 1\n";
	}
	else if (acaoP == 3 && acaoB == 1) {
		PL = PL - 1;
		return "o jogador 1 levou um jeb bem no nariz! Deve ter machucado\n";
	}
	else if (acaoP == 3 && acaoB == 2) {
		BL = BL - 1;
		return "o jogador 1 da um chute no estomago do jogador 2\n";
	}
	else if (acaoP == 3 && acaoB == 3) {
		return "os golpes se encontram, mas n�o machucam nenhum dos lutadores!\n";
	}
	return "error";
};
