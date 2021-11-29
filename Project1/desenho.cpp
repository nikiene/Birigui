#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "movimento.h"
#include "constantes.h"
#include "placar.h"


void drawPlayer(Player& p) {
	al_draw_filled_rectangle(p.x1, p.y1, p.x2, p.y2, al_map_rgb(255, 255, 255));
}

void drawBall(Ball& b) {
	al_draw_filled_circle(b.x, b.y, b.raio, al_map_rgb(255, 255, 255));
}

void drawPlacar(ALLEGRO_FONT* fontPlacarPontos, ALLEGRO_FONT* fontPlacarSets) {
	al_draw_textf(fontPlacarPontos, al_map_rgb(255, 255, 255), widthTenis / 2, heightTenis / 8, ALLEGRO_ALIGN_CENTER, "Player %d - %d Bot", pontosPlayer, pontosBot);
	al_draw_textf(fontPlacarSets, al_map_rgb(255, 255, 255), widthTenis / 2, (heightTenis / 8) + 20, ALLEGRO_ALIGN_CENTER, "%d x %d ", setsPlayer, setsBot);
}

void DrawJogador(Jogador& jogador) {
	al_draw_filled_rectangle(jogador.x1, jogador.y1, jogador.x2, jogador.y2, al_map_rgb(255, 0, 0));
}

void DrawObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CONE && obstaculo[i].y2 <= 450) {
			al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 0, 255));
		} if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CORRIMAO && obstaculo[i].y2 <= 450) {
			al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 255, 0));
		}
	}
}

void DrawPassedObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CONE && obstaculo[i].y2 >= 450) {
			al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 0, 255));
		} if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CORRIMAO && obstaculo[i].y2 >= 450) {
			al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 255, 0));
		}
	}
}