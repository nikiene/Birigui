#include "structs.h"
#include "constantes.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int imagemJogador = 0;
int skate = 0;
bool aux = false;

void initBot(Player& b) {
	b.x = (widthTenis / 2) - 50;
	b.y = heightTenis / 8;
	b.width = 60;
	b.height = 25;

	b.sprite = al_load_bitmap("botSprite.png");
}

void initPlayer(Player& p) {
	p.id = JOGADOR;
	p.x = (widthTenis / 2) - 50;
	p.y = (3 * heightTenis) / 4;
	p.width = 60;
	p.height = 25;

	p.sprite = al_load_bitmap("playerSprite.png");
}

void initBall(Ball& b) {
	b.x = widthTenis / 2;
	b.y = heightTenis / 2;
	b.width = 20;
	b.height = 20;
	b.raio = 5.5;
	b.xDir = 1;
	b.yDir = 1;
}


void InitObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		obstaculo[i].ID = OBSTACULOS;
		obstaculo[i].velocidade = 1.0;
		obstaculo[i].status = MORTO;
	}
}

void CreateObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (i == 0 && obstaculo[i].status == MORTO) {
			obstaculo[i].tipo = CORRIMAO;
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
				obstaculo[i].x1 = 280 + 40;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 45;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			}
			return;

		}
		else if (i > 0 && obstaculo[i].status == MORTO) {
			obstaculo[i].tipo = rand() % 1;
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
				if (obstaculo[i].tipo != obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao ||
					obstaculo[i].tipo == obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao) {
					obstaculo[i].status = MORTO;
				}
				break;
			case 1:
				obstaculo[i].x1 = 280 + 40;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 45;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				if (obstaculo[i].tipo != obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao ||
					obstaculo[i].tipo == obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao) {
					obstaculo[i].status = MORTO;
				}
				break;
			case 2:
				obstaculo[i].x1 = 280 + 55;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 70;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				if (obstaculo[i].tipo != obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao ||
					obstaculo[i].tipo == obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao) {
					obstaculo[i].status = MORTO;
				}
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
			obstaculo[i].edgeRate2 += 0.15;
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

	jogador.x1 = 295;
	jogador.x2 = 345;
	jogador.y1 = 450;
	jogador.y2 = 375;

	jogador.status = VIVO;
}

int endgame(int PL, int BL) {
	if (PL <= 0) {
		printf_s("você Ganhou! Deseja começar de novo?");
		return 1;
	}
	else if (BL <= 0) {
		printf_s("você Perdeu! Deseja começar de novo?");
		return 0;
	}
}


void InitPlantas(Plantas plantas[], int size) {
	for (int i = 0; i < size; i++) {
		plantas[i].velocidade = 1.0;
		plantas[i].status = MORTO;
	}
}

void CreatePlantas(Plantas plantas[], int size) {
	for (int i = 0; i < size; i++) {
		if (plantas[i].status == MORTO) {
			plantas[i].tipo = rand() % 2;
			if (plantas[i].tipo == 1) {
				plantas[i].y = 100;
				plantas[i].tipoArvore = rand() % 2;
				if (plantas[i].tipoArvore == 0) {
					plantas[i].y = 80;

				}
			}
			plantas[i].edgeRate = 1;
			plantas[i].edgeRate2 = 1;
			plantas[i].y = 130;
			plantas[i].ladoPista = rand() % 2;
			switch (plantas[i].ladoPista) {
			case 0:
				plantas[i].x = (rand() % 100) + 80;
				plantas[i].status = VIVO;
				break;
			case 1:
				plantas[i].x = (rand() % 100) + 450;
				plantas[i].status = VIVO;
				break;
			case 2:
				plantas[i].status = MORTO;
				break;
			}
			return;
		}
	}


}

void UpdatePlantas(Plantas plantas[], int size) {
	for (int i = 0; i < size; i++) {
		if (plantas[i].status == VIVO) {
			plantas[i].y += plantas[i].velocidade;
			if (plantas[i].ladoPista == 0) {
				plantas[i].x -= plantas[i].edgeRate / 2;
				plantas[i].edgeRate += 0.1;
			}
			else if (plantas[i].ladoPista == 1) {
				plantas[i].x += plantas[i].edgeRate / 2;
				plantas[i].edgeRate += 0.1;
			}

			plantas[i].velocidade += 0.1;
			plantas[i].edgeRate += 0.5;

			if (plantas[i].y > height) {
				plantas[i].velocidade = 2;
				plantas[i].edgeRate = 1;
				plantas[i].edgeRate2 = 1;
				plantas[i].status = MORTO;
			}
		}
	}
}

void InitParallax(Parallax& parallax, float x, float y, float velx, float vely, int dirX, int dirY, ALLEGRO_BITMAP* image) {
	parallax.x = x;
	parallax.y = y;
	parallax.velx = velx;
	parallax.vely = vely;
	parallax.dirx = dirX;
	parallax.diry = dirY;
	parallax.sprite = image;
}

void UpdateParallax(Parallax& parallax) {
	parallax.x += parallax.velx * parallax.dirx;
	if (parallax.x + width <= 0)
		parallax.x = 0;
}

void initPersonagem(Personagem& personagem, ALLEGRO_BITMAP* imagemPersonagem) {
	personagem.ID = JOGADOR;
	personagem.posX = 100;
	personagem.posY = (heightSurf / 2) + (heightSurf / 4);
	personagem.bordaX = 60;
	personagem.bordaY = 100;
	personagem.velocidade = 7;
	personagem.vida = 5;
	personagem.pontos = 0;

	personagem.maxFrame = 10;
	personagem.curFrame = 0;
	personagem.frameCount = 0;
	personagem.frameDelay = 50;
	personagem.frameLargura = 97;
	personagem.frameAltura = 112;
	personagem.coluna = 9;
	personagem.direcao = 1;
	personagem.imagemPersonagem = imagemPersonagem;
}

void initObstaculos(Obstaculos obstaculos[], int quantidade, ALLEGRO_BITMAP* imagemObstaculos) {
	for (int i = 0; i < quantidade; i++) {
		obstaculos[i].ID = OBSTACULOS;
		obstaculos[i].velocidade = 20;
		obstaculos[i].bordaX = 8;
		obstaculos[i].bordaY = 8;
		obstaculos[i].ativo = true;

		obstaculos[i].maxFrame = 9;
		obstaculos[i].curFrame = 0;
		obstaculos[i].frameLargura = 41;
		obstaculos[i].frameAltura = 65;
		obstaculos[i].imagemObstaculos = imagemObstaculos;
	}
}