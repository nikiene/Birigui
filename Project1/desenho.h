#pragma once
#include <allegro5/allegro_primitives.h>
#include "structs.h"
#include "placar.h"


void drawPlayer(Player& p) {
	al_draw_filled_rectangle(p.x1, p.y1, p.x2, p.y2, al_map_rgb(255, 255, 255));
}

void drawBall(Ball& b) {
	al_draw_filled_circle(b.x, b.y, b.raio, al_map_rgb(255, 255, 255));
}

void drawPlacar(ALLEGRO_FONT* fontPlacarPontos, ALLEGRO_FONT* fontPlacarSets) {
	al_draw_textf(fontPlacarPontos, al_map_rgb(255, 255, 255), width / 2, height / 8, ALLEGRO_ALIGN_CENTER, "Player %d - %d Bot", pontosPlayer, pontosBot);
	al_draw_textf(fontPlacarSets, al_map_rgb(255, 255, 255), width / 2, (height / 8) + 20, ALLEGRO_ALIGN_CENTER, "%d x %d ", setsPlayer, setsBot);
}