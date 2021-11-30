#pragma once
#include "structs.h"
#include "constantes.h"

void initBot(Player& b);

void initPlayer(Player& p);

void initBall(Ball& b);

void InitObstaculo(Obstaculo obstaculo[], int size);

void CreateObstaculo(Obstaculo obstaculo[], int size);

void UpdateObstaculo(Obstaculo obstaculo[], int size);

void InitJogador(Jogador& jogador);

int endgame(int PL, int BL);

