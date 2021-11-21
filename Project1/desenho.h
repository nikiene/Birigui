#pragma once
#include <allegro5/allegro_primitives.h>
#include "structs.h"
#include "placar.h"
#include "constantes.h"

extern void drawPlayer(Player& p);

extern void drawBall(Ball& b);

extern void drawPlacar(ALLEGRO_FONT* fontPlacarPontos, ALLEGRO_FONT* fontPlacarSets);

extern void DrawJogador(Jogador& jogador);

extern void DrawObstaculo(Obstaculo obstaculo[], int size);

extern void DrawPassedObstaculo(Obstaculo obstaculo[], int size);