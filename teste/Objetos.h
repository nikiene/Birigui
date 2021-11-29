#pragma once

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