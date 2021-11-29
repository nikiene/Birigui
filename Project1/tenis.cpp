#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "constantes.h"
#include "desenho.h"
#include "definicao.h"
#include "placar.h"
#include "movimento.h"
#include "structs.h"

int tenis(ALLEGRO_DISPLAY* display) {
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* ballTimer = NULL;
	ALLEGRO_TIMER* botTimer = NULL;
	ALLEGRO_TIMER* colideTimer = NULL;
	ALLEGRO_FONT* fontPlacarSets = NULL;
	ALLEGRO_FONT* fontPlacarPontos = NULL;

	bool done = false;
	bool redraw = false;
	bool toRight = false;
	bool toLeft = true;

	Player player;
	Player bot;
	Ball ball;

	//Inicializando posição do bot e do jogador
	initBot(bot);
	initPlayer(player);
	initBall(ball);
	printf("Player - x1: %d x2: %d, y1: %d, y2: %d\n", player.x1, player.x2, player.y1, player.y2);
	printf("Bot - x1: %d x2: %d, y1: %d, y2: %d", bot.x1, bot.x2, bot.y1, bot.y2);

	//Inicialização de variáveis do allegro
	event_queue = al_create_event_queue();
	ballTimer = al_create_timer(0.05);
	botTimer = al_create_timer(0.2);
	colideTimer = al_create_timer(1.0 / 60.0);
	fontPlacarPontos = al_load_font("fontePlacar.ttf", 20, NULL);
	fontPlacarSets = al_load_font("fontePlacar.ttf", 25, NULL);

	//Desenhando player e bot
	drawPlayer(player);
	drawPlayer(bot);
	drawBall(ball);
	drawPlacar(fontPlacarPontos, fontPlacarSets);
	al_flip_display();

	//Registrando as origens de evento
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(ballTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(botTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(colideTimer));

	//Iniciando os timers
	al_start_timer(colideTimer);
	al_start_timer(ballTimer);
	al_start_timer(botTimer);

	while (setsBot < 3 && setsPlayer < 3 && !done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//Evento de timer
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//Movimentação do bot
			if (ev.timer.source == botTimer) {
				if (toLeft) {
					movementLeft(bot);
					if (bot.x1 <= 0) {
						toLeft = false;
						toRight = true;
					}
				}
				else {
					if (toRight) {
						movementRight(bot);
						if (bot.x2 >= widthTenis) {
							toLeft = true;
							toRight = false;
						}
					}
				}
			}
			//Movimentação da bola
			if (ev.timer.source == ballTimer) {
				moveBall(ball);
			}

			if (ev.timer.source == colideTimer) {
				colide(ball, player, bot);
			}

		}
		//Evento de tecla
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}

			if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
				if (player.x1 > 0) {
					movementLeft(player);
					printf("\nplayer x1: %d", player.x1);
				}
			}

			if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
				if (player.x2 < widthTenis) {
					movementRight(player);
					printf("\nplayer x1: %d", player.x1);
				}
			}
		}
		drawPlacar(fontPlacarPontos, fontPlacarSets);
		drawPlayer(player);
		drawPlayer(bot);
		drawBall(ball);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}


	//Zerando 
	zeraPlacar();


	//destroys
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(colideTimer);
	al_destroy_timer(botTimer);
	al_destroy_timer(ballTimer);
	al_destroy_font(fontPlacarPontos);
	al_destroy_font(fontPlacarSets);

	aceleracao = 1;
	ballYDirection = 1;
	ballXDirection = 1;

	return 0;
}