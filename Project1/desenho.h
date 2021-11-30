#pragma once
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include "structs.h"
#include "placar.h"
#include "constantes.h"

extern void drawPlayer(Player& p);

extern void drawBall(Ball& b);

extern void drawPlacar(ALLEGRO_FONT* fontPlacarPontos, ALLEGRO_FONT* fontPlacarSets);

extern void DrawJogador(Jogador& jogador);

extern void DrawObstaculo(Obstaculo obstaculo[], int size);

extern void DrawPassedObstaculo(Obstaculo obstaculo[], int size);

extern void DrawBackgorund();

extern void DrawText(Jogador& jogador, int segundos, int minutos);

extern void DrawPlantas(Plantas plantas[], int size);

extern void DrawParallax(Parallax& parallax);

extern void DrawBitmap(ALLEGRO_BITMAP* bitmap, int x, int y);

extern void PlaySound(ALLEGRO_SAMPLE* sample);

extern void PlaySoundBaixo(ALLEGRO_SAMPLE* sample);

void initObstaculos(Obstaculos obstaculos[], int quantidade, ALLEGRO_BITMAP* imagemObstaculos);	

void liberaObstaculos(Obstaculos obstaculos[], int quantidade);

void desenhaPersonagem(Personagem& personagem);

void desenhaObstaculos(Obstaculos obstaculos[], int quantidade);
