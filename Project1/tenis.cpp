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


void initPlayer(Player& p);
void initBot(Player& b);
void drawPlayer(Player& p);
void movementLeft(Player& p);
void movementRight(Player& p);

int main() {

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* gameTimer = NULL;
	ALLEGRO_TIMER* botTimer = NULL;


	bool done = false;
	bool redraw = false;
	const int FPS = 60;
	int botMovimenta = 0;
	bool toRight = false;
	bool toLeft = true;

	Player player;
	Player bot;


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


	initBot(bot);
	initPlayer(player);
	printf("Player - x1: %d x2: %d, y1: %d, y2: %d\n", player.x1, player.x2, player.y1, player.y2);
	printf("Bot - x1: %d x2: %d, y1: %d, y2: %d", bot.x1, bot.x2, bot.y1, bot.y2);


	event_queue = al_create_event_queue();
	gameTimer = al_create_timer(1.0 / FPS);
	botTimer = al_create_timer(0.2);


	drawPlayer(player);
	drawPlayer(bot);
	al_flip_display();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(gameTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(botTimer));

	al_start_timer(botTimer);
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
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
		}


		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}
			if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
				movementLeft(player);
			}

			if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
				movementRight(player);
			}
		}

		drawPlayer(player);
		drawPlayer(bot);
		al_flip_display();
	}


	//destroys
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

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
	al_draw_filled_rectangle(p.x2, p.y1, p.x2 + 50, p.y2, al_map_rgb(0, 0, 0));
}

void movementRight(Player& p) {
	p.x1 += 50;
	p.x2 += 50;
	al_draw_filled_rectangle(p.x1, p.y1, p.x1 - 50, p.y2, al_map_rgb(0, 0, 0));
}

