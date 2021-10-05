#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>



const int height = 800;
const int width = 800;

struct Player {
	int x;
	int y;
};


void initPlayer(Player& p);
void drawPlayer(Player& p);

int main() {

	ALLEGRO_DISPLAY* display = NULL;
	
	bool done = false;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	Player player;


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


	initPlayer(player);
	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_draw_filled_rectangle(width / 2 - 25, height / 2 - 25, width / 2 + 25, height / 2 + 25, al_map_rgb(255, 255, 255));
	al_flip_display();

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}
		}
		al_flip_display();
	}


	//destroys
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}


void initPlayer(Player& p) {
	p.x = width / 2;
	p.y = height / 4;
}

void drawPlayer(Player& p) {
	al_draw_filled_rectangle(p.x - 25, p.y, p.x + 25, p.y, al_map_rgb(0, 0, 255));
}

