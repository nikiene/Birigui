#pragma once
#include <allegro5/allegro.h>

struct Player {
	int x1;
	int y1;
	int x2;
	int y2;
};

struct Ball {
	int x;
	int y;
	double raio;
};

enum IDS {
	JOGADOR,
	OBSTACULOS
};

enum STATUS {
	MORTO,
	VIVO
};

enum POSICOES {
	ESQUERDA,
	MEIO,
	DIREITA
};

enum OBSTACULOS {
	CONE,
	CORRIMAO
};

struct Jogador {
	int ID;

	bool status;

	int posicao;

	int x1;
	int x2;
	int y1;
	int y2;
};

struct Obstaculo {
	int ID;

	bool status;

	int tipo;

	int posicao;

	double x1;
	double x2;
	double y1;
	double y2;

	double edgeRate;
	double edgeRate2;

	double velocidade;
};

enum KEYS {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	Z
};

struct personagem {
	int ID;
	int posX;
	int posY;
	int vida;
	int velocidade;
	int bordaX;
	int bordaY;
	int pontos;
};

struct obstaculos {
	int ID;
	int posX;
	int posY;
	int velocidade;
	int bordaX;
	int bordaY;
	bool ativo;
};

struct mar {
	int ID;
	int posX;
	int posY;
};

struct Sprite
{
	float x;
	float y;
	float velX;
	float velY;
	float dirX;
	float dirY;

	int bx;
	int by;
	int w;
	int h;

	ALLEGRO_BITMAP* image;
};

