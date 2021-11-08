#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>



const int height = 800;
const int width = 800;

struct Player {
	int x1;
	int y1;
	int x2;
	int y2;
};

struct Ball {
	int x;
	int y;
	int raio;
};

//Assinatura de funções
void initPlayer(Player& p);
void initBot(Player& b);
void drawPlayer(Player& p);
void movementLeft(Player& p);
void movementRight(Player& p);
void initBall(Ball& b);
void drawBall(Ball& b);
void moveBall(Ball& b);
bool colide(Ball& b, Player& p, Player& bot);

//Variáveis globais
double aceleracao = 1;
int ballXDirection = 1;
int ballYDirection = 1;

int main() {

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* ballTimer = NULL;
	ALLEGRO_TIMER* botTimer = NULL;
	ALLEGRO_TIMER* colideTimer = NULL;

	bool done = false;
	bool redraw = false;
	bool toRight = false;
	bool toLeft = true;

	Player player;
	Player bot;
	Ball ball;

	if (!al_init()) {
		return -1;
	}

	display = al_create_display(width, height);

	if (!display) {
		return -1;
	}

	//Inicializando ADDONS e instalações
	al_init_primitives_addon();
	al_install_keyboard();

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
	colideTimer = al_create_timer(0.05);

	//Desenhando player e bot
	drawPlayer(player);
	drawPlayer(bot);
	drawBall(ball);
	al_flip_display();

	//Registrando as origens de evento
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(ballTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(botTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(colideTimer));

	//Iniciando os timers
	al_start_timer(ballTimer);
	al_start_timer(colideTimer);
	al_start_timer(botTimer);

	while (!done) {
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
			if (ev.keyboard.keycode == ALLEGRO_KEY_N) {
				al_set_new_window_position(100, 100);
			}
		}
		drawPlayer(player);
		drawPlayer(bot);
		drawBall(ball);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	//destroys
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(colideTimer);
	al_destroy_timer(botTimer);
	al_destroy_timer(ballTimer);

	return 0;
}


void initPlayer(Player& p) {
	p.x1 = (width / 2) - 50;
	p.y1 = (3 * height) / 4;
	p.x2 = (width / 2) + 50;
	p.y2 = p.y1 + 25;
}

void drawPlayer(Player& p) {
	al_draw_filled_rectangle(p.x1, p.y1, p.x2, p.y2, al_map_rgb(255, 255, 255));
}

void initBot(Player& b) {
	b.x1 = (width / 2) - 50;
	b.y1 = height / 4;
	b.x2 = (width / 2) + 50;
	b.y2 = b.y1 + 25;
}

void movementLeft(Player& p) {
	p.x1 -= 50;
	p.x2 -= 50;
}

void movementRight(Player& p) {
	p.x1 += 50;
	p.x2 += 50;
}

void initBall(Ball& b) {
	b.x = width / 2;
	b.y = height / 2;
	b.raio = 10.0;
}

void drawBall(Ball& b) {
	al_draw_filled_circle(b.x, b.y, b.raio, al_map_rgb(255, 255, 255));
}

void moveBall(Ball& b) {
	al_draw_filled_circle(b.x, b.y, b.raio, al_map_rgb(0, 0, 0));
	int velocidade = 10;
	b.x += ((velocidade / 4) * aceleracao) * ballXDirection;
	b.y += (velocidade * aceleracao) * ballYDirection;
	aceleracao += 0.002;
}

bool colide(Ball& ball, Player& player, Player& bot) {

	//Colisão com o jogador
	for (int i = 1; i < (player.x2 - player.x1) - 1; i++) {
		if (ball.x == player.x1 + i && ball.y >= player.y1) {
			printf("\nplayer: colidiiu em x = %d", player.x1 + i);
			//if (ball.x - player.x1 > player.x2 - ball.x)
				//ballXDirection *= -1;
			

			ballYDirection *= -1;
			return true;
		}
	}
	
	//Colisão com o bot
	for (int i = 1; i < (bot.x2 - bot.x1) - 1; i++) {
		if (ball.x == bot.x1 + i && ball.y <= bot.y2) {
			printf("\nbot: colidiiu em x = %d", bot.x1 + i);
			//if (ball.x - bot.x1 > bot.x2 - ball.x)
				//ballXDirection *= -1;


			ballYDirection *= -1;
			return true;
		}
	}
	//Colisão com os cantos
	if (ball.x >= width || ball.x <= 0) {
		ballXDirection *= -1;
		return true;
	}

	if (ball.y <= 0 || ball.y >= height) {
		ballYDirection *= -1;
		ball.x = width / 2;
		ball.y = height / 2;
		return true;
	}

	return false; 
}
