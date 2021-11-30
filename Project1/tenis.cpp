#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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
	ALLEGRO_FONT* fontHeader = NULL;
	ALLEGRO_FONT* fontBody = NULL;
	ALLEGRO_FONT* fontFinal = NULL;
	ALLEGRO_BITMAP* bgSheet = NULL;
	ALLEGRO_BITMAP* ballSheet = NULL;
	ALLEGRO_SAMPLE* somBatida = NULL;

	bool done = false;
	bool redraw = false;
	bool toRight = false;
	bool toLeft = true;
	bool mudouVelocidade1 = false;
	bool mudouVelocidade2 = false;
	int colidiu;

	Player player;
	Player bot;
	Ball ball;

	int xoff = 0;
	int yoff = 0;

	int mapColums = 20;
	int mapSize = 400;
	int titleSize = 80;

	//Inicializando posição do bot e do jogador
	initBot(bot);
	initPlayer(player);
	initBall(ball);

	//Inicialização de variáveis do allegro
	event_queue = al_create_event_queue();
	ballTimer = al_create_timer(0.05);
	botTimer = al_create_timer(0.15);
	colideTimer = al_create_timer(1.0 / 65.0);
	fontBody = al_load_font("fontePlacar.ttf", 18, NULL);
	fontHeader = al_load_font("fontePlacar.ttf", 25, NULL);
	fontFinal = al_load_font("fontePlacar.ttf", 50, NULL);
	bgSheet = al_load_bitmap("bgTenis.png");

	somBatida = al_load_sample("batida_sample.wav");

	//Desenhando player e bot
	drawPlayer(player);
	drawPlayer(bot);
	drawBall(ball);
	drawPlacar(fontBody, fontHeader);
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
					if (bot.x <= (width / 8) || ball.x > bot.x + bot.width) {
						toLeft = false;
						toRight = true;
					}
				}
				else {
					if (toRight) {
						movementRight(bot);
						if (bot.x + bot.width >= (7 * width) / 8 || ball.x < bot.x) {
							toLeft = true;
							toRight = false;
						}
					}
				}
			}
			if (ev.timer.source == colideTimer) {
				colidiu = colide(ball, player, bot, colidiuAntes);
			}
			//Movimentação da bola
			/*
			return 0 -> Não colidiu
			return 1 -> Colidiu ou com o player
			return 2 -> Colidiu com o bot
			return 3 -> Colidiu com as extremidades Y do cenário
			return 4 -> Colidiu com o canto esquerdo do cenário
			return 5 -> Colidiu com o canto direito do cenário
			*/
			if (ev.timer.source == ballTimer) {

				switch (colidiu) {
					case 0:
						moveBall(ball);
						break;
					case 1:
						ball.yDir *= -1;
						ball.y -= 5;
						moveBall(ball);
						PlaySound(somBatida);
						break;
					case 2:
						ball.yDir *= -1;
						ball.y += 5;
						moveBall(ball);
						PlaySound(somBatida);
						break;
					case 4:
						ball.xDir *= -1;
						ball.x += 5;
						moveBall(ball);
						break;
					case 5:
						ball.xDir *= -1;
						ball.x -= 5;
						moveBall(ball);
						break;
				}
			}
		}
		//Evento de tecla
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}

			if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
				if (player.x > (width / 8)) {
					movementLeft(player);
				}
			}

			if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
				if (player.x + player.width < (7 * width) / 8) {
					movementRight(player);
				}
			}
		}
		if (setsPlayer == 1) {
			mudouVelocidade1 = true;
			if (mudouVelocidade1) {
				al_set_timer_speed(botTimer, 0.1);
				mudouVelocidade1 = false;
			}
		}
		else if (setsPlayer == 2) {
			mudouVelocidade2 = true;
			mudouVelocidade1 = false;
			if (mudouVelocidade2) {
				al_set_timer_speed(botTimer, 0.05);
				mudouVelocidade2 = false;
			}
		}
		al_draw_bitmap(bgSheet, 0, 0, 0);
		drawPlacar(fontHeader, fontBody);
		drawPlayer(player);
		drawPlayer(bot);
		drawBall(ball);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}


	if (setsPlayer == 3) {
		al_clear_to_color(al_map_rgb(0, 255, 0));
		al_draw_text(fontFinal, al_map_rgb(255, 255, 255), width / 2 - width / 4, height / 2, 0, "Voce ganhou!");
	}
	else if (setsBot == 3) {
		al_clear_to_color(al_map_rgb(255, 0, 0));
		al_draw_text(fontFinal, al_map_rgb(255, 255, 255), width / 2 - width / 4, height / 2, 0, "Voce perdeu!");
	}
	al_flip_display();

	al_rest(3);
	//Zerando 
	zeraPlacar();


	//destroys
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(colideTimer);
	al_destroy_timer(botTimer);
	al_destroy_timer(ballTimer);
	al_destroy_font(fontHeader);
	al_destroy_font(fontBody);
	al_destroy_bitmap(player.sprite);
	al_destroy_bitmap(bot.sprite);
	al_destroy_bitmap(bgSheet);

	aceleracao = 1;

	return 0;
}