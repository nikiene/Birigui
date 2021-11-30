#pragma once
#include <allegro5/allegro.h>

struct Player {
	int id;
	int x;
	int y;
	int width;
	int height;

	ALLEGRO_BITMAP* sprite;
};

struct Ball {
	int x;
	int y;
	int width;
	int height;
	double xDir;
	int yDir;
	double raio;
	ALLEGRO_BITMAP* sprite;
};

enum COLISAO {
	NAOCOLIDIU,
	X,
	Y
};

enum IDS {
	JOGADOR,
	OBSTACULOS,
	BOT
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

enum KEYS {
	DOWN,
	LEFT,
	RIGHT,
	UP,
	SPACE,
	Z,
	ENTER
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

	ALLEGRO_BITMAP* sprite;
};

struct Obstaculo {
	int ID;

	bool status;

	int tipo;

	int posicao;

	float x1;
	float x2;
	float y1;
	float y2;

	float edgeRate;
	float edgeRate2;

	float velocidade;

	ALLEGRO_BITMAP* sprite;
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

struct Plantas {
	bool status;

	int ladoPista;

	int tipo;
	int tipoArvore;

	float x;
	float y;

	float edgeRate;
	float edgeRate2;

	float velocidade;

	ALLEGRO_BITMAP* sprite;
};

struct Parallax {
	float x;
	float y;
	float velx;
	float vely;
	int dirx;
	int diry;

	ALLEGRO_BITMAP* sprite;
};

struct Personagem {
	int ID;
	int posX;
	int posY;
	int vida;
	int velocidade;
	int bordaX;
	int bordaY;
	int pontos;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameLargura;
	int frameAltura;
	int coluna;
	int linha;
	int direcao;
	ALLEGRO_BITMAP* imagemPersonagem;
};

struct Obstaculos {
	int ID;
	int posX;
	int posY;
	int velocidade;
	int bordaX;
	int bordaY;
	bool ativo;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameLargura;
	int frameAltura;
	int coluna;
	int linha;
	int direcao;
	ALLEGRO_BITMAP* imagemObstaculos;
};

