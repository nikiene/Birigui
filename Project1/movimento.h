#pragma once
#include "structs.h"
#include "constantes.h"
#include "placar.h"

//Variáveis
extern double aceleracao;
extern int ballXDirection;
extern int ballYDirection;
extern int velocidadeBase;

extern bool pulo;
extern int velocidadeMaxPulo;
extern int gravidade;
extern int velocidadePulo;

extern bool keysHub[6];


void movementLeft(Player& p);

void movementRight(Player& p);

void moveBall(Ball& b);

bool colide(Ball& ball, Player& player, Player& bot);

void MoveJogadorLeft(Jogador& jogador);

void MoveJogadorRight(Jogador& jogador);

void MakeJogadorJump(Jogador& jogador);

int Collision(Obstaculo obstaculo[], Jogador& jogador);

const char* combat(int acaoP, int acaoB);
