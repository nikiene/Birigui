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

const int numeroObstaculosSkate = 10;
const int numeroPlantas = 250;

/**/
int skate(ALLEGRO_DISPLAY* displaySkate) {
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	int segundos = 0;
	int minutos = 0;

	Jogador jogador;
	Obstaculo obstaculos[numeroObstaculosSkate];
	Plantas plantas[numeroPlantas];
	Parallax BG;
	Parallax MG;
	Parallax FG1;
	Parallax FG2;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* gameTimer = NULL;
	ALLEGRO_TIMER* obstaculoTimer = NULL;
	ALLEGRO_TIMER* updateObstaculoTimer = NULL;
	ALLEGRO_TIMER* relogioJogo = NULL;

	ALLEGRO_SAMPLE* somSkate = NULL;
	ALLEGRO_SAMPLE* musica = NULL;
	ALLEGRO_SAMPLE* somPulo = NULL;

	ALLEGRO_BITMAP* bgImage = NULL;
	ALLEGRO_BITMAP* mgImage = NULL;
	ALLEGRO_BITMAP* fgImage = NULL;

	event_queue = al_create_event_queue();
	gameTimer = al_create_timer(1.0 / FPS);
	obstaculoTimer = al_create_timer(0.6);
	updateObstaculoTimer = al_create_timer(0.035);
	relogioJogo = al_create_timer(1.0);

	al_set_window_title(displaySkate, "Skate birigui");

	somSkate = al_load_sample("skate.wav");
	somPulo = al_load_sample("pulo.wav");
	musica = al_load_sample("cbj.wav");

	bgImage = al_load_bitmap("montanha.png");
	mgImage = al_load_bitmap("nuvem2.png");
	fgImage = al_load_bitmap("nuvem1.png");

	al_reserve_samples(3);

	srand(time(NULL));

	InitJogador(jogador);
	InitPlantas(plantas, numeroPlantas);
	InitObstaculo(obstaculos, numeroObstaculos);

	InitParallax(BG, 0, 85, 0.25, 0, -1, 1, bgImage);
	InitParallax(MG, 0, 10, 0.5, 0, -1, 1, mgImage);
	InitParallax(FG1, 0, 50, 0.75, 0, -1, 1, fgImage);
	InitParallax(FG2, 0, 90, 1, 0, -1, 1, fgImage);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(gameTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(obstaculoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(updateObstaculoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(relogioJogo));
	al_register_event_source(event_queue, al_get_display_event_source(displaySkate));

	al_start_timer(gameTimer);
	al_start_timer(obstaculoTimer);
	al_start_timer(updateObstaculoTimer);
	al_start_timer(relogioJogo);
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (aux == false)
		{
			aux = true;
			PlaySound(musica);

		}
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			UpdateParallax(BG);
			UpdateParallax(MG);
			UpdateParallax(FG1);
			UpdateParallax(FG2);
			redraw = true;

			if (keys[UP]) {
				if (!pulo) {
					pulo = true;
					PlaySoundBaixo(somPulo);
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

			imagemJogador++;
			CreatePlantas(plantas, numeroPlantas);

			CreateObstaculo(obstaculos, numeroObstaculos);
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);

			}
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);
			}
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);
				CreatePlantas(plantas, numeroPlantas);

			}
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);

			}
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);

			}
			CreateObstaculo(obstaculos, numeroObstaculos);




		} if (ev.timer.source == updateObstaculoTimer) {
			UpdateObstaculo(obstaculos, numeroObstaculos);
			UpdatePlantas(plantas, numeroPlantas);

			if (Collision(obstaculos, jogador)) {
				al_stop_samples();
				al_flush_event_queue(event_queue);
				al_clear_to_color(al_map_rgb(186, 0, 0));
				DrawText(jogador, segundos, minutos);
				al_flip_display();
				al_rest(5);
				done = true;
			}

		}  if (ev.timer.source == relogioJogo) {

			CreatePlantas(plantas, numeroPlantas);

			if (tmpSkate == 0) {
				PlaySoundBaixo(somSkate);
			}

			tmpSkate++;

			segundos++;

			if (segundos == 60)
			{
				minutos++;
				segundos = 0;
			}

			if (minutos == 1) {
				jogador.status = MORTO;
				al_flush_event_queue(event_queue);
				al_clear_to_color(al_map_rgb(119, 198, 110));
				DrawText(jogador, segundos, minutos);
				al_flip_display();
				al_rest(5.5);
				pontoSkate++;
				done = true;
			}

			if (tmpSkate == 3) {

				PlaySoundBaixo(somSkate);
				tmpSkate = 1;
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

			DrawBackgorund();

			DrawParallax(BG);
			DrawParallax(MG);
			DrawParallax(FG1);
			DrawParallax(FG2);

			DrawText(jogador, segundos, minutos);

			DrawPlantas(plantas, numeroPlantas);

			DrawObstaculo(obstaculos, numeroObstaculos);
			DrawJogador(jogador);
			DrawPassedObstaculo(obstaculos, numeroObstaculos);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	for (int i = 0; i <= 6; i++)
		keys[i] = false;

	aux = false;

	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);

	al_destroy_sample(somPulo);
	al_destroy_sample(somSkate);
	al_destroy_sample(musica);

	al_destroy_timer(gameTimer);
	al_destroy_timer(obstaculoTimer);
	al_destroy_timer(updateObstaculoTimer);
	al_destroy_timer(relogioJogo);

	al_destroy_event_queue(event_queue);
	al_destroy_display(displaySkate);

	return 0;
}