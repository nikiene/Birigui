#pragma once
#include "structs.h"
#include "constantes.h"
#include "placar.h"

//Variáveis
extern double aceleracao;
extern int velocidadeBase;

extern bool pulo;
extern int velocidadeMaxPulo;
extern int gravidade;
extern int velocidadePulo;
extern bool colidiuAntes;

extern bool keysHub[6];


void movementLeft(Player& p);

void movementRight(Player& p);

void moveBall(Ball& b);

int colide(Ball& ball, Player& player, Player& bot, bool& colidiuAntes);

bool passouDoBot(Ball& ball, Player& player, Player& bot);

bool passouDoPlayer(Ball& ball, Player& player, Player& bot);

void MoveJogadorLeft(Jogador& jogador);

void MoveJogadorRight(Jogador& jogador);

void MakeJogadorJump(Jogador& jogador);

int Collision(Obstaculo obstaculo[], Jogador& jogador);

const char* combat(int acaoP, int acaoB, int& PL, int& BL);

int game(int PL, int BL);

void colidirObstaculos(Obstaculos obstaculos[], int quantidade, Personagem& personagem, ALLEGRO_SAMPLE_INSTANCE* insMedalhas);

void moveObstaculos(Obstaculos obstaculos[], int quantidade);

void personagemMoveCima(Personagem& personagem);

void personagemMoveBaixo(Personagem& personagem);

void personagemMoveEsquerda(Personagem& personagem);

void personagemMoveDireira(Personagem& personagem);