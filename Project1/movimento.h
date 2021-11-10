#pragma once
#include "structs.h"

//Variáveis
double aceleracao = 1.0;
int ballXDirection = 1;
int ballYDirection = 1;
const int velocidadeBase = 10;


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
	for (int i = 1; i < (player.x2 - player.x1); i++) {
		for (int j = 0; j < (player.y2 - player.y1) - 1; j++) {
			if (ball.x == player.x1 + i && ball.y == player.y1 + j) {
				printf("\nplayer: colidiiu em x = %d", player.x1 + i);
				//if (ball.x - player.x1 > player.x2 - ball.x)
					//ballXDirection *= -1;

				printf("\nAceleracao: %d", aceleracao);
				ballYDirection *= -1;
				return true;

			}
		}
	}
	//Colisão com o bot
	for (int i = 1; i < (bot.x2 - bot.x1); i++) {
		for (int j = 0; j < (bot.y2 - bot.y1) - 1; j++) {
			if (ball.x == bot.x1 + i && ball.y == bot.y1 + j) {
				printf("\nbot: colidiiu em x = %d", bot.x1 + i);
				//if (ball.x - bot.x1 > bot.x2 - ball.x)
					//ballXDirection *= -1;


				ballYDirection *= -1;
				return true;
			}
		}
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