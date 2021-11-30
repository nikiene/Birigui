#pragma once
#include "structs.h"
#include "constantes.h"

extern bool aux;

void initBot(Player& b);

void initPlayer(Player& p);

void initBall(Ball& b);

void InitObstaculo(Obstaculo obstaculo[], int size);

void CreateObstaculo(Obstaculo obstaculo[], int size);

void UpdateObstaculo(Obstaculo obstaculo[], int size);

void InitJogador(Jogador& jogador);

int endgame(int PL, int BL);

void InitPlantas(Plantas plantas[], int size);

void CreatePlantas(Plantas plantas[], int size);

void UpdatePlantas(Plantas plantas[], int size);

void InitParallax(Parallax& parallax, float x, float y, float velx, float vely, int dirX, int dirY, ALLEGRO_BITMAP* image);

void UpdateParallax(Parallax& parallax);

void initObstaculos(Obstaculos obstaculos[], int quantidade, ALLEGRO_BITMAP* imagemObstaculos);

void initPersonagem(Personagem& personagem, ALLEGRO_BITMAP* imagemPersonagem);
