#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "constantes.h"
#include "desenho.h"
#include "definicao.h"
#include "placar.h"
#include "movimento.h"
#include "structs.h"
#include "jogos.h"

int main(int argc, char** argv)
{
	//MAPA
	int xoff = 0;
	int yoff = 0;

	int mapColums = 20;
	int mapSize = 400;
	int titleSize = 80;

	//2 = entrada minigame 4 = npcs  1 = paredes  0 = grama 3 = rua/cal�ada n�o defini muito bem oq �
	int map[] = {
				  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				  1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,4,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,4,0,1,
				  1,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,
				  1,2,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,2,1,
				  1,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,
				  1,0,4,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,4,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	//PROJECT VARIABLES

	bool done = false;//finalizar o loop 
	bool render = false;//desenhar
	bool inGame = false;

	bool bound = false; // verificar se a colisao esta no local certo
	bool collision = false;//colisao
	Sprite ball1;//player
	Sprite ball2;//npc

	ball1.x = width / 2;
	ball1.y = (height * 4) / 5;

	ball2.x = width / 2;
	ball2.y = height / 2;

	//local de fala
	bool local_fala = false;

	int npc_fala = 0;//verificar com qual npc esta interagindo

	int contador = 0;//contar as quantidades de fala

	//allegro variables

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_DISPLAY* displayTenis = NULL;
	ALLEGRO_DISPLAY* displayBoxe = NULL;
	ALLEGRO_DISPLAY* displaySurf = NULL;
	ALLEGRO_DISPLAY* displaySkate = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font18 = NULL;
	ALLEGRO_BITMAP* bgSheet = NULL;
	ALLEGRO_BITMAP* npc = NULL;


	//ALLEGRO INIT FUNCTIONS

	if (!al_init())
	{
		return -1;
	}

	display = al_create_display(width, height);

	if (!display)
	{
		return -1;
	}

	//ADDONS INSTALL

	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();

	//PROJECT INIT

	bgSheet = al_load_bitmap("background02.png"); //mapa  paleta de sprites para o mapa

	npc = al_load_bitmap("bicho_aleatorio.png");//imagem do npc

	//local mapa
	xoff = -80 * 5; //movimenta��o do mapa
	yoff = -80 * 12;

	font18 = al_load_font("arial.ttf", 18, 0);//font de texto

	ball1.image = al_load_bitmap("ball1.png");// imagem o player

	//pegar parametros do tamanho dos sprites
	ball1.w = al_get_bitmap_width(ball1.image);
	ball1.h = al_get_bitmap_height(ball1.image);

	ball2.w = 75;
	ball2.h = 75;

	ball1.bx = ball1.w / 2 - 5;
	ball1.by = ball1.h / 2 - 10;

	ball2.bx = ball2.w / 2 - 5;
	ball2.by = ball2.h / 2 - 10;

	//TIMER INIT AND STARTUP

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	while (!done)
	{	
		while(inGame == false) {
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			//movimenta��o
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					if (contador > 0)
						keys[LEFT] = false;
					else
						keys[LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					if (contador > 0)
						keys[RIGHT] = false;
					else
						keys[RIGHT] = true;
					break;
				case ALLEGRO_KEY_UP:
					if (contador > 0)
						keys[UP] = false;
					else
						keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					if (contador > 0)
						keys[DOWN] = false;
					else
						keys[DOWN] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = true;
					break;
				case ALLEGRO_KEY_Z:
					keys[Z] = true;
					if (local_fala)
					{
						contador++;
					}
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[SPACE] = false;
					break;
				case ALLEGRO_KEY_Z:
					keys[Z] = false;
					break;
				}
			}
			//tempo fps
			else if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				render = true;

				if (keys[UP])
				{
					ball1.y -= 2;
					yoff += keys[UP] * 5;
				}
				else if (keys[DOWN])
				{
					ball1.y += 2;
					yoff -= keys[DOWN] * 5;
				}
				else if (keys[LEFT])
				{
					ball1.x -= 2;
					xoff += keys[LEFT] * 5;
				}
				else if (keys[RIGHT])
				{
					ball1.x += 2;
					xoff -= keys[RIGHT] * 5;
				}
				if (keys[SPACE])
					bound = true;
				else
					bound = false;
			}
		
			//colisoes
			//npc de cima  // npc fala 1
			if (ball1.x + ball1.bx > ((75.4 * 8) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((75 * 8) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((65 * 3) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((65 * 3) + yoff) + ball2.by)
			{
				collision = true;
			}
			//npc da esquerda
			else if (ball1.x + ball1.bx > ((68 * 3) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((66 * 3) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((83 * 12) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((83 * 12) + yoff) + ball2.by)
				collision = true;
			//nc da direita
			else if (ball1.x + ball1.bx > ((78 * 18) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((77.5 * 18) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((76 * 9) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((75 * 9) + yoff) + ball2.by)
				collision = true;

			//npc do meio
			else if (ball1.x + ball1.bx > ((76 * 10) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((76 * 10) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((84 * 10) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((84 * 10) + yoff) + ball2.by)
				collision = true;

			//npc do comeco
			else if (ball1.x + ball1.bx > ((77 * 12) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((76 * 12) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((77.8 * 17) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((77.4 * 17) + yoff) + ball2.by)
				collision = true;

			//paredes
			else if (ball1.x + ball1.bx > ((80 * 19) + xoff) ||
				ball1.x - ball1.bx< 80 + xoff ||
				ball1.y + ball1.by >(80 * 19) + yoff ||
				ball1.y - ball1.by < (80 * 1) + yoff)
				collision = true;

			//local para o jogo

			else
			{
				collision = false;
			}
			//falas e inda��o de qual npc esta interagindo no momento
			//local fala do npc de cima
			if (ball1.x + ball1.bx > ((70 * 8) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((81 * 8) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((52 * 3) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((78 * 3) + yoff) + ball2.by)
			{
				npc_fala = 1;
				local_fala = true;
			}//esquerda
			else if (ball1.x + ball1.bx > ((55 * 3) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((78 * 3) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((80 * 12) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((86 * 12) + yoff) + ball2.by)
			{
				npc_fala = 2;
				local_fala = true;
			}
			//direita
			else if (ball1.x + ball1.bx > ((74 * 18) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((80 * 18) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((76 * 9) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((83 * 9) + yoff) + ball2.by)
			{
				npc_fala = 3;
				local_fala = true;
			}//meio
			else if (ball1.x + ball1.bx > ((70 * 10) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((82 * 10) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((78 * 10) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((90 * 10) + yoff) + ball2.by)
			{
				npc_fala = 4;
				local_fala = true;
			}
			//comeco
			else if (ball1.x + ball1.bx > ((73 * 12) + xoff) - ball2.bx &&
				ball1.x - ball1.bx < ((80 * 12) + xoff) + ball2.bx &&
				ball1.y + ball1.by >((74 * 17) + yoff) - ball2.by &&
				ball1.y - ball1.by < ((80 * 17) + yoff) + ball2.by)
			{
				npc_fala = 5;
				local_fala = true;
			}
			else
			{
				local_fala = false;
				npc_fala = 0;
			}



		//RENDER
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;

				for (int i = 0; i < mapSize; i++)// desenha o mapa MAPA
				{
					al_draw_bitmap_region(bgSheet, titleSize * map[i], 0, titleSize, titleSize,
						xoff + titleSize * (i % mapColums), yoff + titleSize * (i / mapColums), 0);
					if (map[i] == 4)// desenha o sprite o npc no moapa
					{
						al_draw_bitmap(npc, xoff + titleSize * (i % mapColums), yoff + titleSize * (i / mapColums), 0);


					}


				}



				al_draw_bitmap(ball1.image, ball1.x - ball1.w / 2, ball1.y - ball1.h / 2, 0);

				if (bound)
				{
					//pode apagar se quisar (feito s� ara verificar as colisoes)

					al_draw_filled_rectangle(ball1.x - ball1.bx, ball1.y - ball1.by, ball1.x + ball1.bx, ball1.y + ball1.by, al_map_rgba_f(.6, 0, .6, .6));


					// npc de cima
					al_draw_filled_rectangle(((70 * 8) + xoff) - ball2.bx, ((52 * 3) + yoff) - ball2.by, ((81 * 8) + xoff) + ball2.bx, ((78 * 3) + yoff) + ball2.by, al_map_rgba_f(.5, 0, .6, .6));//fala
					al_draw_filled_rectangle(((75.4 * 8) + xoff) - ball2.bx, ((65 * 3) + yoff) - ball2.by, ((75 * 8) + xoff) + ball2.bx, ((65 * 3) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//colisa

					// npc da esquerda
					al_draw_filled_rectangle(((68 * 3) + xoff) - ball2.bx, ((83 * 12) + yoff) - ball2.by, ((66 * 3) + xoff) + ball2.bx, ((83 * 12) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//colisao
					al_draw_filled_rectangle(((55 * 3) + xoff) - ball2.bx, ((80 * 12) + yoff) - ball2.by, ((78 * 3) + xoff) + ball2.bx, ((86 * 12) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//fala

					//npc da direita
					al_draw_filled_rectangle(((78 * 18) + xoff) - ball2.bx, ((76 * 9) + yoff) - ball2.by, ((77.5 * 18) + xoff) + ball2.bx, ((75 * 9) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//colisao
					al_draw_filled_rectangle(((74 * 18) + xoff) - ball2.bx, ((70 * 9) + yoff) - ball2.by, ((80 * 18) + xoff) + ball2.bx, ((83 * 9) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//fala

					//npc da meio
					al_draw_filled_rectangle(((76 * 10) + xoff) - ball2.bx, ((84 * 10) + yoff) - ball2.by, ((76 * 10) + xoff) + ball2.bx, ((84 * 10) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//colisao
					al_draw_filled_rectangle(((70 * 10) + xoff) - ball2.bx, ((78 * 10) + yoff) - ball2.by, ((82 * 10) + xoff) + ball2.bx, ((90 * 10) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//fala

					//npc da comeco
					al_draw_filled_rectangle(((77 * 12) + xoff) - ball2.bx, ((77.8 * 17) + yoff) - ball2.by, ((76 * 12) + xoff) + ball2.bx, ((77.4 * 17) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//colisao
					al_draw_filled_rectangle(((73 * 12) + xoff) - ball2.bx, ((74 * 17) + yoff) - ball2.by, ((80 * 12) + xoff) + ball2.bx, ((80 * 17) + yoff) + ball2.by, al_map_rgba_f(.6, 0, .6, .6));//fala

					//parede de cima
					al_draw_filled_rectangle((80 * 1) + xoff, ((80 * 1) + yoff) - 80, (80 * 20) + xoff, (80 * 1) + yoff, al_map_rgba_f(.6, 0, .6, .6));//colisao

					//parede esquerda
					al_draw_filled_rectangle(((80 * 1) + xoff) - 80, (80 * 1) + yoff, (80 * 1) + xoff, (80 * 20) + yoff, al_map_rgba_f(.6, 0, .6, .6));//colisao

					//parede direita
					al_draw_filled_rectangle(((80 * 19) + xoff), (80 * 1) + yoff, (80 * 20) + xoff, (80 * 20) + yoff, al_map_rgba_f(.6, 0, .6, .6));//colisao

					//parede de baixo
					al_draw_filled_rectangle((80 * 1) + xoff, (80 * 19) + yoff, (80 * 20) + xoff, (80 * 20) + yoff, al_map_rgba_f(.6, 0, .6, .6));//colisao

					//local do minigame
					//esquerda
					al_draw_filled_rectangle(((80 * 1) + xoff), ((80 * 10) + yoff), ((80 * 2) + xoff), ((80 * 11) + yoff), al_map_rgba_f(.6, 0, .6, .6));

					//cima
					al_draw_filled_rectangle(((80 * 9) + xoff), ((80 * 1) + yoff), ((80 * 10) + xoff), ((80 * 2) + yoff), al_map_rgba_f(.6, 0, .6, .6));

					//direita
					al_draw_filled_rectangle(((80 * 18) + xoff), ((80 * 10) + yoff), ((80 * 19) + xoff), ((80 * 11) + yoff), al_map_rgba_f(.6, 0, .6, .6));

				}

				if (local_fala)//fala
				{

					if (contador > 0)
					{	 //desenhar o local para as falas
						al_draw_filled_rectangle(0, 0, width, height, al_map_rgba_f(0, 0, 0, 0.7));
						al_draw_filled_rectangle(0, (height * 4) / 6, width, height, al_map_rgba_f(0, 0, 0, 0.9));
					}
					//fala npc cima
					if (contador == 1 && npc_fala == 1) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 1 falas 1");
						displayTenis = al_create_display(width, height);
						tenis(displayTenis);
					}
					else if (contador == 2 && npc_fala == 1)
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 1 falas 2");
					else if (contador == 3 && npc_fala == 1)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 1 falas 3");

					}
					else if (contador == 4 && npc_fala == 1)
						contador = 0;

					//fala npc esquerda
					if (contador == 1 && npc_fala == 2) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 2 falas 1");
						displaySkate = al_create_display(width, height);
						skate(displaySkate);
						inGame = true;
					}

					else if (contador == 2 && npc_fala == 2)
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 2 falas 2");
					else if (contador == 3 && npc_fala == 2)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 2 falas 3");

					}
					else if (contador == 4 && npc_fala == 2)
						contador = 0;

					//fala npc direita
					if (contador == 1 && npc_fala == 3) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 3 falas 1");
						displaySurf = al_create_display(width, height);
						surf(displaySurf);
						inGame = true;
					}
					else if (contador == 2 && npc_fala == 3)
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 3 falas 2");
					else if (contador == 3 && npc_fala == 3)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 3 falas 3");

					}
					else if (contador == 4 && npc_fala == 3)
						contador = 0;

					//fala npc meio
					if (contador == 1 && npc_fala == 4) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 4 falas 1");
						displayBoxe = al_create_display(width, height);
						boxe(displayBoxe);
						inGame = true;
					}
					else if (contador == 2 && npc_fala == 4)
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 4 falas 2");
					else if (contador == 3 && npc_fala == 4)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 4 falas 3");

					}
					else if (contador == 4 && npc_fala == 4)
						contador = 0;

					//fala npc comeco // baixo
					if (contador == 1 && npc_fala == 5)
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 5 falas 1");
					else if (contador == 2 && npc_fala == 5)
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 5 falas 2");
					else if (contador == 3 && npc_fala == 5)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 420, ALLEGRO_ALIGN_CENTRE, "npc 5 falas 3");

					}
					else if (contador == 4 && npc_fala == 5)
						contador = 0;

				}

				if (collision)//quando acontecer o colisao o player volta para o lado oposto que veio
				{
					al_draw_text(font18, al_map_rgb(255, 255, 0), width / 2, 20, ALLEGRO_ALIGN_CENTRE, "Collision!");
					if (keys[RIGHT] == true)
					{
						keys[RIGHT] = false;
						ball1.x -= 10;
						xoff += 17;
					}
					else if (keys[LEFT] == true)
					{
						keys[LEFT] = false;
						ball1.x += 10;
						xoff -= 17;
					}
					else if (keys[DOWN] == true)
					{
						keys[DOWN] = false;
						ball1.y -= 10;
						yoff += 17;
					}

					else if (keys[UP] == true)
					{
						keys[UP] = false;
						ball1.y += 10;
						yoff -= 17;
					}

				}

				al_flip_display();
			}
		}
	}
	//DESTROY ALLEGRO OBJECTS

	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}


