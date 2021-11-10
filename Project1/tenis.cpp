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

int tenis(ALLEGRO_DISPLAY* display);
int teste(ALLEGRO_DISPLAY* display);

int main() {
	ALLEGRO_DISPLAY* display1 = NULL;
	ALLEGRO_DISPLAY* display2 = NULL;
	ALLEGRO_DISPLAY* display3 = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	bool emGame = false;


	bool terminou = false;

	if (!al_init()) //returns a value of -1 if
		return -1;  //Allegro does not initialize properly

	display1 = al_create_display(height, width);


	if (!display1) {
		return -1;
	}

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	while (!terminou) {
		if (emGame == true) {
			emGame = false;
		}
		while (!emGame) {
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (ev.keyboard.keycode == ALLEGRO_KEY_1 && emGame == false) {
					emGame = true;
					display2 = al_create_display(width, height);
					tenis(display2);
				}
				if (ev.keyboard.keycode == ALLEGRO_KEY_2 && emGame == false) {
					emGame = true;
					display3 = al_create_display(width, height);
					teste(display3);
				}
				if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE & emGame == false) {
					terminou = true;
				}
			}
			emGame = false;
			al_flip_display();
		}
	}

	al_destroy_display(display1);
	return 0;
}

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


	//Inicializando ADDONS e instalações
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();

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
						if (bot.x2 >= width) {
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
				if (player.x2 < width) {
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

int teste(ALLEGRO_DISPLAY* display) {
	// Variável representando a janela principal
	// Inicializamos a biblioteca
	al_init();

	// Criamos a nossa janela - dimensões de 640x480 px

	// Preenchemos a janela de branco
	al_clear_to_color(al_map_rgb(255, 255, 255));

	// Atualiza a tela
	al_flip_display();

	// Segura a execução por 10 segundos
	al_rest(1.0);


	al_destroy_display(display);
	// Finaliza a janela
	return 0;
}

