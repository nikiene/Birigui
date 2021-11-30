#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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

	//2 = algo relacionado ao minigame 4 = npc pedrito  1 = paredes  0 = grama 3 = rua/calçada não defini muito bem oq é
	//4 Pedrito cima
	/*
	5 =Talonito direita
	6 = Nikito esquerda
	*/

	int map[] = {
				  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,4,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,5,0,1,
				  1,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,
				  1,0,3,3,3,3,3,3,3,6,3,3,3,3,3,3,3,3,0,1,
				  1,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,
				  1,0,8,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,7,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,1,
				  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

	//PROJECT VARIABLES

	bool done = false;//finalizar o loop 
	bool render = false;//desenhar
	bool inGame = false;

	//animacao player/ ball1
	bool draw = true, active = false;
	int dir = DOWN, sourceX = 80, sourceY = 0;

	
	bool collision = false;//colisao
	Sprite ball1;//player
	Sprite ball2;//npc

	

	ball2.x = width / 2;
	ball2.y = height / 2;

	//local de fala
	bool local_fala = false, explicacao = true;

	int npc_fala = 0;//verificar com qual npc esta interagindo

	int contador = 0;//contar as quantidades de fala

	//allegro variables
	ALLEGRO_KEYBOARD_STATE keyState;//animacao
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_DISPLAY* displayTenis = NULL;
	ALLEGRO_DISPLAY* displayBoxe = NULL;
	ALLEGRO_DISPLAY* displaySurf = NULL;
	ALLEGRO_DISPLAY* displaySkate = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer;
	ALLEGRO_TIMER* playerTimer;
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
	al_install_audio();
	al_init_acodec_addon();

	//PROJECT INIT

	bgSheet = al_load_bitmap("background02.png"); //mapa  paleta de sprites para o mapa

	npc = al_load_bitmap("bicho_aleatorio.png");//imagem do npc

	//local mapa
	xoff = -80 * 4.5; //movimentação do mapa
	yoff = -80 * 5.5;

	font18 = al_load_font("arial.ttf", 18, 0);//font de texto

	ball1.image = al_load_bitmap("playerImg.png");// imagem o player  animacao

	//pegar parametros do tamanho dos sprites
	ball1.w = al_get_bitmap_width(ball1.image);
	ball1.h = al_get_bitmap_height(ball1.image);

	ball1.x = width / 2;
	ball1.y = ((height * 4) / 5) - 190;

	ball2.w = 75;
	ball2.h = 75;

	ball1.bx = ball1.w / 2 - 5;
	ball1.by = ball1.h / 2 - 10;

	ball2.bx = ball2.w / 2 - 5;
	ball2.by = ball2.h / 2 - 10;

	//TIMER INIT AND STARTUP

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	playerTimer = al_create_timer(1.0 / 15);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(playerTimer));//animacao
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	while (!done)
	{
		while (inGame == false)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			al_get_keyboard_state(&keyState);//animacao

			//movimentação
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
				active = true;

				if (keys[UP] )
				{
					ball1.y -= 2;
					yoff += keys[UP] * 5;
					dir = UP;//animacao
				}
				else if (keys[DOWN] )
				{
					ball1.y += 2;
					yoff -= keys[DOWN] * 5;
					dir = DOWN;//animacao
				}
				else if (keys[LEFT] )
				{
					ball1.x -= 2;
					xoff += keys[LEFT] * 5;
					dir = LEFT;//animacao
				}
				else if (keys[RIGHT] )
				{
					ball1.x += 2;
					xoff -= keys[RIGHT] * 5;
					dir = RIGHT;//animacao
				}
				else if (explicacao)
				{
					contador++;
					explicacao = false;
				}
				else
				{
					active = false;//animacao
				}



				//colisoes
				//npc de cima  // npc fala 1
				if (ball1.x + (ball1.bx / 2) > ((75.4 * 8) + xoff) - ball2.bx &&
					ball1.x + 10 < ((75 * 8) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((65 * 3) + yoff) - ball2.by &&
					ball1.y < ((65 * 3) + yoff) + ball2.by)
				{
					collision = true;
				}
				//npc da esquerda
				else if (ball1.x + (ball1.bx / 2) > ((68 * 3) + xoff) - ball2.bx &&
					ball1.x + 10 < ((66 * 3) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((83 * 12) + yoff) - ball2.by &&
					ball1.y < ((83 * 12) + yoff) + ball2.by)
					collision = true;
				//nc da direita
				else if (ball1.x + (ball1.bx / 2) > ((78 * 18) + xoff) - ball2.bx &&
					ball1.x + 10 < ((77.5 * 18) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((76 * 9) + yoff) - ball2.by &&
					ball1.y < ((75 * 9) + yoff) + ball2.by)
					collision = true;

				//npc do meio
				else if (ball1.x + (ball1.bx / 2) > ((76 * 10) + xoff) - ball2.bx &&
					ball1.x + 10 < ((76 * 10) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((84 * 10) + yoff) - ball2.by &&
					ball1.y < ((84 * 10) + yoff) + ball2.by)
					collision = true;

				//npc do comeco
				else if (ball1.x + (ball1.bx / 2) > ((77 * 12) + xoff) - ball2.bx &&
					ball1.x + 10 < ((76 * 12) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((77.8 * 17) + yoff) - ball2.by &&
					ball1.y < ((77.4 * 17) + yoff) + ball2.by)
					collision = true;

				//paredes
				else if (ball1.x + (ball1.bx / 2) > ((80 * 19) + xoff) ||
					ball1.x + 10 < 80 + xoff ||
					ball1.y + (ball1.by / 2) > (80 * 19) + yoff ||
					ball1.y < (80 * 1) + yoff)
					collision = true;
				else
				{
					collision = false;
				}




				//falas e indação de qual npc esta interagindo no momento
				//local fala do npc de cima
				if (ball1.x + (ball1.bx / 2) > ((70 * 8) + xoff) - ball2.bx &&
					ball1.x + 10 < ((81 * 8) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((52 * 3) + yoff) - ball2.by &&
					ball1.y < ((78 * 3) + yoff) + ball2.by)
				{
					npc_fala = 1;
					local_fala = true;
				}
				//esquerda
				else if (ball1.x + (ball1.bx / 2) > ((55 * 3) + xoff) - ball2.bx &&
					ball1.x + 10 < ((78 * 3) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((80 * 12) + yoff) - ball2.by &&
					ball1.y < ((86 * 12) + yoff) + ball2.by)
				{
					npc_fala = 2;
					local_fala = true;
				}
				//direita
				else if (ball1.x + (ball1.bx / 2) > ((74 * 18) + xoff) - ball2.bx &&
					ball1.x + 10 < ((80 * 18) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((76 * 9) + yoff) - ball2.by &&
					ball1.y < ((83 * 9) + yoff) + ball2.by)
				{
					npc_fala = 3;
					local_fala = true;
				}//meio
				else if (ball1.x + (ball1.bx / 2) > ((70 * 10) + xoff) - ball2.bx &&
					ball1.x + 10 < ((82 * 10) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((78 * 10) + yoff) - ball2.by &&
					ball1.y < ((90 * 10) + yoff) + ball2.by)
				{
					npc_fala = 4;
					local_fala = true;
				}
				//comeco
				else if (ball1.x + (ball1.bx / 2) > ((73 * 12) + xoff) - ball2.bx &&
					ball1.x + 10 < ((80 * 12) + xoff) + ball2.bx &&
					ball1.y + (ball1.by / 2) > ((74 * 17) + yoff) - ball2.by &&
					ball1.y < ((80 * 17) + yoff) + ball2.by)
				{
					npc_fala = 5;
					local_fala = true;
				}
				else
				{
					local_fala = false;
					npc_fala = 0;
				}
				//animacao
				if (active)
				{
					sourceX += ball1.w / 3;
				}
				else
					sourceX = 80;

				if (sourceX >= ball1.w)
					sourceX = 0;
				sourceY = dir;
				draw = true;

			}


			//RENDER
			if (render && al_is_event_queue_empty(event_queue))
			{
				render = false;

				for (int i = 0; i < mapSize; i++)// desenha o mapa MAPA
				{
					al_draw_bitmap_region(bgSheet, titleSize * map[i], 0, titleSize, titleSize,
						xoff + titleSize * (i % mapColums), yoff + titleSize * (i / mapColums), 0);

				}


				//animacao
				if (draw)
				{
					al_start_timer(playerTimer);
					al_draw_bitmap_region(ball1.image, sourceX, sourceY * ball1.h / 4, 80, 80, ball1.x, ball1.y, NULL);

				}



				if (local_fala)//fala
				{

					if (contador > 0)
					{	 //desenhar o local para as falas
						al_draw_filled_rectangle(0, 0, width, height, al_map_rgba_f(0, 0, 0, 0.7));
						al_draw_filled_rectangle(0, (height * 4) / 6, width, height, al_map_rgba_f(0, 0, 0, 0.9));
					}
					//fala npc cima >>tenis
					if (contador == 1 && npc_fala == 1) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Pedrito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Vejo que voce esta interessado em tenis. Ja que e assim vou te explicar as regras mas primeiro ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "voce pode me chamar de 'Pedrito' mas voce sabia o saque mais rapido ja registrado pela Associacao");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "dos Tenista Profissionais foi dado em 2012 pelo australiano Samuel Groth, com incriveis 263km/h ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 710, NULL, "durante o torneio de Busan, na Coreia do Sul e ainda encaixou mais 2 saques de 253km/h e de 255km/h.");

					}
					else if (contador == 2 && npc_fala == 1)

					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Pedrito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "E no jogo agora voce vai precisar marcar alguns set para vencer do seu adversario, voce tambem pode");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "se movimentar para esquerda e direita utilizando as teclas 'A'(esquerda) e 'D'(direita). Voce so ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "precisa chegar perto o suficiente para rebater e bom jogo.");
					}
					else if (contador == 3 && npc_fala == 1)
					{
						contador = 0;
						inGame = true;
						displayTenis = al_create_display(widthTenis, heightTenis);
						tenis(displayTenis);
						al_set_target_backbuffer(display);
						inGame = false;
					}



					//fala npc esquerda>>skate
					if (contador == 1 && npc_fala == 2) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Nikito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Parece que voce quer andar de Skate, sabia que ele surgiu na California, Estados Unidos, nos anos 60.");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "Foi inventado por alguns surfistas, como uma brincadeira para um dia no qual nao havia ondas no mar. ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "Eles utilizaram rodinhas de patins. Ja em 1965 foram fabricados os primeiros skates e realizados os");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 710, NULL, "primeiros campeonatos.");
						
					}

					else if (contador == 2 && npc_fala == 2)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Nikito");//continuar com a fala depois //feito
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Agora como jogar, para ir para esquerda e direita use as teclas 'A' e 'D' ou seta esquerda e direita  ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "e a tecla 'W', seta pra cima ou espaco para pulas e se quiser sair do minigame so pressionar a tecla 'esc'.");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "No minigame voce vai presisar desviar dos 2 tipos de obstaculos o buraco que pode ser pulado e o cone ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 710, NULL, "que nao pode pular por cima, voce precisa sobreviver por 1 min para ganhar, boa sorte.");
					}
					else if (contador == 3 && npc_fala == 2)
					{
						displaySkate = al_create_display(width, height);
						skate(displaySkate);
						inGame = true;
						contador = 0;

					}
					else if (contador == 4 && npc_fala == 2) {
						displaySkate = al_create_display(widthSkate, heightSkate);
						inGame = true;
						skate(displaySkate);
						al_set_target_backbuffer(display);
						contador = 0;
						inGame = false;
						
					}

					//fala npc direita>>surf
					if (contador == 1 && npc_fala == 3) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Talonito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Parece que temos um desafiante, pode me chamar de Talonito, sabia que o surf e conhecido como o ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "'esporte dos Deuse'. Na Polinésia, somente os reis podiam pratica-lo em pe na prancha enquanto os ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "suditos deveriam ficar deitados por isso que nao se deve subestimar o surf.");

					}
					else if (contador == 2 && npc_fala == 3)

					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Talonito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Agora, para vencer esse desafio voce precisa coletar 5 medalhas, voce pode se movimentar utilizando ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "as setas que tem ai no teclado para ir pra cima, baixo, direita e esquerda, boa sorte.");
					}
					else if (contador == 3 && npc_fala == 3)
					{
						contador = 0;
						inGame = true;
						displaySurf = al_create_display(widthSurf, heightSurf);
						surf(displaySurf);
						al_set_target_backbuffer(display);
						inGame = false;
						
					}



					//fala npc meio
					if (contador == 1 && npc_fala == 4) {
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Shodito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Para andar pressione as setas do teclado e para interagir com os npc clique na tecla 'z'.");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "Oi, voce pode me chamar de 'Shodito', e irei te falar onde estao os lugares para voce jogar");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "e tambem vou falar sobre umas curiosidades sobre as olimpiadas que pode te interessar eu acho.");

					}
					else if (contador == 2 && npc_fala == 4)

					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Shodito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Voce sabia que os JOGOS Olimpicos se originaram na Grecia Antiga numa cidade de Olimpiaonde tiveram ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "um forte vinculo religioso e erm dedicados a Zeus(Deus dos deuses dentro da mitologia grega)");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "e que as argolas na bandeira das olimpiadas representa os 5 continentes habitados no mundo.");
					}
					else if (contador == 3 && npc_fala == 4)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Shodito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Agora vou falar onde voce pode jogar, falando com o cara la em cima voce pode joga um ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "pouco de tenis mas se quiser pode jogar quantas vezes quiser indo pela direita voce ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "pode surfar falando com a passoa, na direcao de baixo pode praticar um boxe e na esquerda ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 710, NULL, "pode andar de skate.");

					}
					else if (contador == 4 && npc_fala == 4)
					{
						contador = 0;
					}
					//fala npc comeco // baixo>>>boxe
					if (contador == 1 && npc_fala == 5)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Branquito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Que tal tentar jogar uma partida de Boxe, pode me chamar de Branquito, sabia que ele era ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "popular na Inglaterra nos seculos XVIII e XIX, as lutas eram feitas com as maos descobertas ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "e muito brutais e ele so foi reformado em 1867 com as Regras de Quensberry, que previam rounds ");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 710, NULL, "de três minutos e o uso de luvas, so entraram em vigor em 1872.");
					}
					else if (contador == 2 && npc_fala == 5)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Branquito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "Deixa eu te explicar como as regras aqui, o jogo é baseado em prever a habilidade do inimigo, voce");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "tem 3 opcoes de habilidade, sendo elas 'jeb', 'chute' e 'combo' cada um tem uma certa vantagem ");//continuar com a fala depois
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 690, NULL, "sobre a outra, para nocautear o inimigo, tera que acertar 5 golpes nele.");

					}
					else if (contador == 3 && npc_fala == 5)
					{
						al_draw_text(font18, al_map_rgb(255, 255, 0), width / 12, 630, ALLEGRO_ALIGN_CENTRE, "Branquito");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 650, NULL, "a ordem de vantagens é:");
						al_draw_text(font18, al_map_rgb(255, 255, 0), 15, 670, NULL, "JEB > CHUTE > COMBO > JEB ");

					}
					else if (contador == 4 && npc_fala == 5)
					{
						inGame = true;
						displayBoxe = al_create_display(widthBoxe, heightBoxe);
						boxe(displayBoxe);
						contador = 0;
						al_set_target_backbuffer(display);
					}
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
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
	}
	//DESTROY ALLEGRO OBJECTS

	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_timer(playerTimer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}


