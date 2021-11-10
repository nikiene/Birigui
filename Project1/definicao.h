#pragma once
#include "structs.h"
#include "constantes.h"

void initBot(Player& b) {
	b.x1 = (width / 2) - 50;
	b.y1 = height / 4;
	b.x2 = (width / 2) + 50;
	b.y2 = b.y1 + 25;
}

void initPlayer(Player& p) {
	p.x1 = (width / 2) - 50;
	p.y1 = (3 * height) / 4;
	p.x2 = (width / 2) + 50;
	p.y2 = p.y1 + 25;
}

void initBall(Ball& b) {
	b.x = width / 2;
	b.y = height / 2;
	b.raio = 10.0;
}
