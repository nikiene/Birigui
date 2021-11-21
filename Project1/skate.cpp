#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "constantes.h"
#include "desenho.h"
#include "definicao.h"
#include "placar.h"
#include "movimento.h"
#include "structs.h"

int skate(ALLEGRO_DISPLAY* display) {
	bool done = false;
	bool redraw = true;
	const int FPS = 60;

	Jogador jogador;
	Obstaculo obstaculos[10];

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* gameTimer = NULL;
	ALLEGRO_TIMER* obstaculoTimer = NULL;
	ALLEGRO_TIMER* updateObstaculoTimer = NULL;
	ALLEGRO_TIMER* gameTime = NULL;

	if (!al_init())
		return -1;

	if (!display)
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	gameTimer = al_create_timer(1.0 / FPS);
	obstaculoTimer = al_create_timer(0.6);
	updateObstaculoTimer = al_create_timer(0.035);
	gameTime = al_create_timer(1.0);

	srand(time(NULL));

	InitJogador(jogador);
	InitObstaculo(obstaculos, numeroObstaculos);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(gameTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(obstaculoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(updateObstaculoTimer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	ALLEGRO_FONT* font18 = al_load_font("Roboto-Regular.ttf", 18, 0);

	al_start_timer(gameTimer);
	al_start_timer(obstaculoTimer);
	al_start_timer(updateObstaculoTimer);
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);



		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;

			if (keys[UP]) {
				if (!pulo) {
					pulo = true;
				}
			}

			if (keys[LEFT]) {
				MoveJogadorLeft(jogador);
				keys[LEFT] = false;
			}

			if (keys[RIGHT]) {
				MoveJogadorRight(jogador);
				keys[RIGHT] = false;
			}

			if (pulo == true) {
				MakeJogadorJump(jogador);
			}
		} if (ev.timer.source == obstaculoTimer) {
			CreateObstaculo(obstaculos, numeroObstaculos);
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);
			}
			CreateObstaculo(obstaculos, numeroObstaculos);
		} if (ev.timer.source == updateObstaculoTimer) {
			UpdateObstaculo(obstaculos, numeroObstaculos);

			if (Collision(obstaculos, jogador)) {
				al_flush_event_queue(event_queue);
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_flip_display();
				al_rest(3);
				done = true;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			DrawObstaculo(obstaculos, numeroObstaculos);
			DrawJogador(jogador);
			DrawPassedObstaculo(obstaculos, numeroObstaculos);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}


	al_destroy_display(display);

	return 0;
}
