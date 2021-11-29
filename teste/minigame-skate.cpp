#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "objetos.h"

const int width = 640;
const int height = 480;

const int numeroObstaculos = 10;

bool pulo = false;

int velocidadeMaxPulo = 16;
int gravidade = 1;
int velocidadePulo = velocidadeMaxPulo;

int imagemJogador = 0;

int segundos = 0;
int minutos = 0;

enum KEYS {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

bool keys[4] = {
	false,
	false,
	false,
	false
};

void DrawBackgorund();
void DrawText(Jogador& jogador);

void InitJogador(Jogador& jogador);
void DrawJogador(Jogador& jogador);
void MoveJogadorLeft(Jogador& jogador);
void MoveJogadorRight(Jogador& jogador);
void MakeJogadorJump(Jogador& jogador);

void InitObstaculo(Obstaculo obstaculo[], int size);
void DrawObstaculo(Obstaculo obstaculo[], int size);
void CreateObstaculo(Obstaculo obstaculo[], int size);
void UpdateObstaculo(Obstaculo obstaculo[], int size);
void DrawPassedObstaculo(Obstaculo obstaculo[], int size);

int Collision(Obstaculo obstaculo[], Jogador& jogador);

int main(void) {
	bool done = false;
	bool redraw = true;
	const int FPS = 60;

	Jogador jogador;
	Obstaculo obstaculos[10];

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* gameTimer = NULL;
	ALLEGRO_TIMER* obstaculoTimer = NULL;
	ALLEGRO_TIMER* updateObstaculoTimer = NULL;
	ALLEGRO_TIMER* relogioJogo = NULL;

	if (!al_init())
		return -1;

	display = al_create_display(width, height);

	if (!display)
		return -1;

	al_init_ttf_addon();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();
	gameTimer = al_create_timer(1.0 / FPS);
	obstaculoTimer = al_create_timer(0.6);
	updateObstaculoTimer = al_create_timer(0.035);
	relogioJogo = al_create_timer(1.0);


	srand(time(NULL));

	InitJogador(jogador);
	InitObstaculo(obstaculos, numeroObstaculos);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(gameTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(obstaculoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(updateObstaculoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(relogioJogo));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(gameTimer);
	al_start_timer(obstaculoTimer);
	al_start_timer(updateObstaculoTimer);
	al_start_timer(relogioJogo);

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

			imagemJogador++;

			CreateObstaculo(obstaculos, numeroObstaculos);
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);
			}
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);
			}
			if (rand() % 10 == 0) {
				CreateObstaculo(obstaculos, numeroObstaculos);
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
			
			if (Collision(obstaculos, jogador)) {
				al_flush_event_queue(event_queue);
				al_clear_to_color(al_map_rgb(186, 0, 0));
				DrawText(jogador);
				al_flip_display();
				al_rest(5);
				done = true;
			}
			
		} if (ev.timer.source == relogioJogo) {

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
				DrawText(jogador);
				al_flip_display();
				al_rest(5);
				done = true;
			}


		} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
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

			al_draw_filled_rectangle(0, 160, 640, 480, al_map_rgb(0, 255, 0));
			DrawBackgorund();

			DrawText(jogador);

			DrawObstaculo(obstaculos, numeroObstaculos);
			DrawJogador(jogador);
			DrawPassedObstaculo(obstaculos, numeroObstaculos);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	al_destroy_timer(gameTimer);
	al_destroy_timer(obstaculoTimer);
	al_destroy_timer(updateObstaculoTimer);
	al_destroy_timer(relogioJogo);

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}

void DrawBackgorund() {
	ALLEGRO_BITMAP* ceu;
	ceu = al_load_bitmap("background.png");
	al_draw_bitmap(ceu, 0, 0, 0);
	al_destroy_bitmap(ceu);

	ALLEGRO_BITMAP* chao;


}

void DrawText(Jogador& jogador) {

	ALLEGRO_FONT* font = al_load_font("fonte.ttf", 30, 0);

	if (jogador.status == VIVO)
	{
		if (segundos < 10) {
			al_draw_textf(font, al_map_rgb(255, 211, 0), 10, 10, 0, "%d : 0%d", minutos, segundos);
		} else {
			al_draw_textf(font, al_map_rgb(255, 211, 0), 10, 10, 0, "%d : %d", minutos, segundos);
		}
	} else {
		if (minutos == 1){
			al_draw_text(font, al_map_rgb(255, 211, 0), width / 2, height / 3, ALLEGRO_ALIGN_CENTER, "BOA!");
			al_draw_text(font, al_map_rgb(255, 211, 0), width / 2, (height / 3 + height / 3) - 105, ALLEGRO_ALIGN_CENTER, "Voce venceu o meu desafio e");
			al_draw_text(font, al_map_rgb(255, 211, 0), width / 2, (height / 3 + height / 3) - 65, ALLEGRO_ALIGN_CENTER, "provou ser o proprio choris!");
		} else {
			al_draw_text(font, al_map_rgb(255, 211, 0), width / 2, height / 3, ALLEGRO_ALIGN_CENTER, "VOCE PERDEU!");
			al_draw_text(font, al_map_rgb(255, 211, 0), width / 2, height / 3 + height / 3, ALLEGRO_ALIGN_CENTER, "Tente Novamente!");
		}
	}

	al_destroy_font(font);
}

void InitJogador(Jogador& jogador) {
	jogador.ID = JOGADOR;

	jogador.posicao = MEIO;

	jogador.x1 = 295; //25
	jogador.x2 = 345; //25
	jogador.y1 = 450; //parte inferior da tela "chão"
	jogador.y2 = 375; //chão + 75

	jogador.status = VIVO;
}

void DrawJogador(Jogador& jogador) {
	if (imagemJogador > 5) {
		if (imagemJogador == 7) {
			imagemJogador = 0;
		}
		jogador.sprite = al_load_bitmap("jogador2.png");
		al_draw_bitmap(jogador.sprite, jogador.x1, jogador.y2, 0);
		
	} else {
		jogador.sprite = al_load_bitmap("jogador1.png");
		al_draw_bitmap(jogador.sprite, jogador.x1, jogador.y2, 0);
	}
	
	al_destroy_bitmap(jogador.sprite);
	//al_draw_filled_rectangle(jogador.x1, jogador.y1, jogador.x2, jogador.y2, al_map_rgb(255, 0, 0));
}

void MoveJogadorLeft(Jogador& jogador) {
	if (jogador.posicao != ESQUERDA) {
		jogador.posicao -= 1;
		jogador.x1 -= 90;
		jogador.x2 -= 90;
	}
}

void MoveJogadorRight(Jogador& jogador) {
	if (jogador.posicao != DIREITA) {
		jogador.posicao += 1;
		jogador.x1 += 90;
		jogador.x2 += 90;
	}
}

void MakeJogadorJump(Jogador& jogador) {
	jogador.y1 -= velocidadePulo;
	jogador.y2 -= velocidadePulo;

	velocidadePulo -= gravidade;

	if (velocidadePulo < -velocidadeMaxPulo) {
		velocidadePulo = velocidadeMaxPulo;
		pulo = false;
	}
}

void InitObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		obstaculo[i].ID = OBSTACULOS;
		obstaculo[i].velocidade = 1.0;
		obstaculo[i].status = MORTO;
	}
}

void CreateObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (i == 0 && obstaculo[i].status == MORTO) {
			obstaculo[i].tipo = CORRIMAO;
			obstaculo[i].posicao = rand() % 3;
			obstaculo[i].edgeRate = 1;
			obstaculo[i].edgeRate2 = 1;
			switch (obstaculo[i].posicao) {
			case 0:
				obstaculo[i].x1 = 280 + 25;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 30;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			case 1:
				obstaculo[i].x1 = 280 + 40;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 45;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			case 2:
				obstaculo[i].x1 = 280 + 55;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 70;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			case 3:
				obstaculo[i].x1 = 280 + 40;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 45;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				break;
			}
			return;

		} else if (i > 0 && obstaculo[i].status == MORTO) {
			obstaculo[i].tipo = rand() % 1;
			obstaculo[i].posicao = rand() % 3;
			obstaculo[i].edgeRate = 1;
			obstaculo[i].edgeRate2 = 1;
			switch (obstaculo[i].posicao) {
			case 0:
				obstaculo[i].x1 = 280 + 25;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 30;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				if (obstaculo[i].tipo != obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao ||
					obstaculo[i].tipo == obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao) {
					obstaculo[i].status = MORTO;
				}
				break;
			case 1:
				obstaculo[i].x1 = 280 + 40;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 45;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				if (obstaculo[i].tipo != obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao ||
					obstaculo[i].tipo == obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao) {
					obstaculo[i].status = MORTO;
				}
				break;
			case 2:
				obstaculo[i].x1 = 280 + 55;
				obstaculo[i].y1 = 145;
				obstaculo[i].x2 = 280 + 70;
				obstaculo[i].y2 = 150;
				obstaculo[i].status = VIVO;
				if (obstaculo[i].tipo != obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao ||
					obstaculo[i].tipo == obstaculo[0].tipo && obstaculo[i].posicao == obstaculo[0].posicao) {
					obstaculo[i].status = MORTO;
				}
				break;
			case 3:
				obstaculo[i].status = MORTO;
			}
			return;
		}
	} 
	
}

void UpdateObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (obstaculo[i].status == VIVO) {
			obstaculo[i].y1 += obstaculo[i].velocidade;
			obstaculo[i].y2 += obstaculo[i].velocidade + obstaculo[i].edgeRate2;
			obstaculo[i].edgeRate2 += 0.15;
			if (obstaculo[i].posicao == 0) {
				obstaculo[i].x1 -= obstaculo[i].edgeRate;
				obstaculo[i].x2 -= obstaculo[i].edgeRate / 2;
				obstaculo[i].edgeRate += 0.29;
			}
			else if (obstaculo[i].posicao == 1) {
				obstaculo[i].x1 -= obstaculo[i].edgeRate / 2;
				obstaculo[i].x2 += obstaculo[i].edgeRate / 2;
				obstaculo[i].edgeRate += 0.15;
			}
			else if (obstaculo[i].posicao == 2) {
				obstaculo[i].x1 += obstaculo[i].edgeRate / 2;
				obstaculo[i].x2 += obstaculo[i].edgeRate;
				obstaculo[i].edgeRate += 0.29;
			}
			obstaculo[i].velocidade += 0.5;
			if (obstaculo[i].y1 < 150 && obstaculo[i].y1 < 250) {
				obstaculo[i].velocidade -= 0.01;
			}
			else if (obstaculo[i].y1 >= 150 && obstaculo[i].y1 < 315) {
				obstaculo[i].velocidade += 0.15;
			}
			else if (obstaculo[i].y1 >= 315 && obstaculo[i].y1 <= 500) {
				obstaculo[i].velocidade += 0.01;
			} if (obstaculo[i].y1 > height) {
				obstaculo[i].status = MORTO;
				obstaculo[i].velocidade = 1;
				obstaculo[i].edgeRate = 1;
				obstaculo[i].edgeRate2 = 1;
			}
		}
	}
}

void DrawObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CONE && obstaculo[i].y2 <= 450) {
			obstaculo[i].sprite = al_load_bitmap("cone.png");
			al_draw_bitmap(obstaculo[i].sprite, obstaculo[i].x1, obstaculo[i].y1, 0);
			al_destroy_bitmap(obstaculo[i].sprite);
			//al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 0, 255));
		} if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CORRIMAO && obstaculo[i].y2 <= 450) {
			obstaculo[i].sprite = al_load_bitmap("bueiro.png");
			al_draw_bitmap(obstaculo[i].sprite, obstaculo[i].x1, obstaculo[i].y1 + 15, 0);
			al_destroy_bitmap(obstaculo[i].sprite);
			//al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 255, 0));
		}

	}
}

void DrawPassedObstaculo(Obstaculo obstaculo[], int size) {
	for (int i = 0; i < size; i++) {
		if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CONE && obstaculo[i].y2 >= 450) {
			obstaculo[i].sprite = al_load_bitmap("cone.png");
			al_draw_bitmap(obstaculo[i].sprite, obstaculo[i].x1, obstaculo[i].y1, 0);
			al_destroy_bitmap(obstaculo[i].sprite);
			//al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 0, 255));
		} if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CORRIMAO && obstaculo[i].y2 >= 450) {
			obstaculo[i].sprite = al_load_bitmap("bueiro.png");
			al_draw_bitmap(obstaculo[i].sprite, obstaculo[i].x1, obstaculo[i].y1 + 15, 0);
			al_destroy_bitmap(obstaculo[i].sprite);
			//al_draw_filled_rectangle(obstaculo[i].x1, obstaculo[i].y1, obstaculo[i].x2, obstaculo[i].y2, al_map_rgb(0, 255, 0));
		}

	}
}

int Collision(Obstaculo obstaculo[], Jogador& jogador) {
	for (int i = 0; i < numeroObstaculos; i++) {
		//não deve ser pulado
		if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CONE) {
			if (obstaculo[i].x1 < jogador.x1 + 50 &&
				obstaculo[i].x1 + 50 > jogador.x1 &&
				obstaculo[i].y1 < jogador.y2 + 75 &&
				obstaculo[i].y1 + 50 > jogador.y2 &&
				(obstaculo[i].y2 > 350 && obstaculo[i].y1 < 450)) {
				jogador.status = MORTO;
				return 1;
			}
		}
		//TODO: 
		//deve ser pulado
		else if (obstaculo[i].status == VIVO && obstaculo[i].tipo == CORRIMAO) {
			if (obstaculo[i].x1 < jogador.x1 + 50 &&
				obstaculo[i].x1 + 50 > jogador.x1 &&
				obstaculo[i].y1 < jogador.y2 + 75 &&
				obstaculo[i].y1 + 25 > jogador.y2 &&
				(obstaculo[i].y2 > 448 && obstaculo[i].y1 < 450)) {
				jogador.status = MORTO;
				return 1;
			}
		}
	}
	return 0;
}

