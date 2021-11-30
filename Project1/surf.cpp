#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "constantes.h"
#include "desenho.h"
#include "definicao.h"
#include "placar.h"
#include "movimento.h"
#include "structs.h"


const int FPS = 60;
const int QTD_OBSTACULOS = 10;

int surf(ALLEGRO_DISPLAY* display)
{// imagem do c�u
	int x = widthSurf / 2;
	int y = heightSurf / 2;
	int ceuLargura = 0;
	int ceuAltura = 0;
	// -----------------------------------------------------
	// imagem do mar
	//int marLargura = 0;
	//int marAltura = 0;

	const int maxFrame = 4;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 5;
	float frameOndaLargura = 135;
	float frameOndaAltura = 167;
	float frameOndaInernaLargura = 962;
	float frameOndaInternaAltura = 502;

	// ------------- VARI�VEIS DO JOGO ----------------------
	// Cria a vari�vel da fila de entos
	ALLEGRO_EVENT_QUEUE* filaEventos = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_FONT* fontVida = NULL;
	ALLEGRO_FONT* fontGameOver = NULL;
	ALLEGRO_FONT* fontGameOverTexto = NULL;
	ALLEGRO_BITMAP* imagemCeu = NULL; // Ponteiro para a imagem do c�u
	ALLEGRO_BITMAP* imagemMar[maxFrame]; // Ponteiro para a imagem do mar
	ALLEGRO_BITMAP* onda = NULL;
	ALLEGRO_BITMAP* ondaInterna = NULL;
	ALLEGRO_BITMAP* imagemPersonagem = NULL;
	ALLEGRO_BITMAP* imagemObstaculos = NULL;
	ALLEGRO_SAMPLE* trilhaSonora = NULL;
	ALLEGRO_SAMPLE* medalhas = NULL;
	ALLEGRO_SAMPLE_INSTANCE* insTrilhaSonora = NULL;
	ALLEGRO_SAMPLE_INSTANCE* insMedalhas = NULL;


	// -----------------------------------------------------

	// Vari�veis para o loop principal
	bool fim = false;
	bool desenha = true;
	bool gameOver = false;
	bool teclas[] = { false, false, false, false, false }; // O enum ser� �til aqui. Onde, em vez de usar n�mero para se obter o valor false, � usado os nomes que est�o no enum.

	// -------------- INICIALIZA��O DE OBJETOS ------------------
	Personagem personagem;
	Obstaculos obstaculos[QTD_OBSTACULOS];

	// ----------------------- CRIAR FILA DE EVENTOS E DEMAIS DISPOSITIVOS ---------
	// No campo das vari�veis foi criado o ponteiro fila_evento com valor NULL.
	// Agora, para sua utiliza��o, � atribuido a fun��o que cria eventos a esse ponteiro.
	filaEventos = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	// ------------------------ Fontes ----------------------------------------------
	fontVida = al_load_font("orange.ttf", 36, NULL);
	fontGameOver = al_load_font("baiser.ttf", 48, NULL);
	fontGameOverTexto = al_load_font("arial.ttf", 18, NULL);
	// -----------------------------------------------------------------------------
	// ------------------------- Ceu -----------------------------------------------
	imagemCeu = al_load_bitmap("ceu.png"); // Aqui a fun��o "linka" o arquivo da imagem ao ponteiro imagemCeu
	// -----------------------------------------------------------------------------
	// ------------------------ Onda ------------------------------------------------
	onda = al_load_bitmap("onda.png");
	al_convert_mask_to_alpha(onda, al_map_rgb(186, 254, 202));
	ondaInterna = al_load_bitmap("ondaInterna.png");
	// ------------------------------------------------------------------------------
	// ----------------------- Personagem -------------------------------------------
	imagemPersonagem = al_load_bitmap("personagem.png");
	al_convert_mask_to_alpha(imagemPersonagem, al_map_rgb(186, 254, 202));
	// -----------------------------------------------------------------------------
	// ---------------------- Obstaculo --------------------------------------------
	imagemObstaculos = al_load_bitmap("medalhas.png");
	al_convert_mask_to_alpha(imagemObstaculos, al_map_rgb(255, 255, 255));
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	// ------------------Trilha sonora -------------------------------------
	al_reserve_samples(2);
	trilhaSonora = al_load_sample("onda.ogg");
	insTrilhaSonora = al_create_sample_instance(trilhaSonora);
	al_attach_sample_instance_to_mixer(insTrilhaSonora, al_get_default_mixer());
	al_set_sample_instance_playmode(insTrilhaSonora, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(insTrilhaSonora, 0.8);

	medalhas = al_load_sample("medalhas.ogg");
	insMedalhas = al_create_sample_instance(medalhas);
	al_attach_sample_instance_to_mixer(insMedalhas, al_get_default_mixer());
	// ----------------------- REGISTRO DE SOURCES ---------------------------------
	// Agora � necess�rio que aja um registro dos eventos, qualquer que forem criados, para serem
	// atribuidos ao pontiero fila_evento. Assim:
	al_register_event_source(filaEventos, al_get_display_event_source(display)); // a fun��o al_get_display_event_source pede um parametro que, no caso, � o ponteiro display.
	al_register_event_source(filaEventos, al_get_keyboard_event_source()); // Aqui a fun��o al_register_event_source permite que o ponteiro fila_evento receba os dados do teclado pelo al_get_keyboard_event_source().
	al_register_event_source(filaEventos, al_get_mouse_event_source()); // Igual ao anterio, mas para o mouse.
	al_register_event_source(filaEventos, al_get_timer_event_source(timer));

	// ----------------------- FUN��ES INICIAIS -------------------------------------
	//initMar(onda);
	initPersonagem(personagem, imagemPersonagem);
	initObstaculos(obstaculos, QTD_OBSTACULOS, imagemObstaculos);


	// ----------------------- LOOP PRINCIPAL ---------------------------------------
	al_start_timer(timer);

	while (!fim)
	{
		ALLEGRO_EVENT ev; // Esse tipo ALLEGRO_EVENT cria uma vari�vel que aceita "qualquer tipo de evento" estabelecido.
		al_wait_for_event(filaEventos, &ev); // A fun��o al_wait_for_event aguarda uma a��o (entrada de dados). Quando entra dados, o ev recebe e manda para o ponteiro fila_evento.

		// ------------------- L�GICA DO JOGO
		// Como a vari�vel ev aceita qualquer tipo de entrada de dados, o if a seguir faz a compara��o dos dados de entrada para executar seu comando.
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			fim = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {/* ALLEGRO_EVENT_KEY_DOWN � o reconhecimento de que um bot�o qualquer foi apertado */
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				fim = true;
				break;
			case ALLEGRO_KEY_W:
				teclas[UP] = true; // Aplica��o do enum dentro do vetor. O valor original do vetor � false...
				break;
			case ALLEGRO_KEY_S:
				teclas[DOWN] = true;
				break;
			case ALLEGRO_KEY_D:
				teclas[RIGHT] = true;
				break;
			case ALLEGRO_KEY_A:
				teclas[LEFT] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				teclas[ENTER] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				teclas[UP] = false;
				break;
			case ALLEGRO_KEY_S:
				teclas[DOWN] = false;
				break;
			case ALLEGRO_KEY_D:
				teclas[RIGHT] = false;
				break;
			case ALLEGRO_KEY_A:
				teclas[LEFT] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				teclas[ENTER] = false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			// ------------------- MOVIMENTO DO OBJETO -----------------

			desenha = true;

			if (teclas[UP])
				personagemMoveCima(personagem);
			if (teclas[DOWN])
				personagemMoveBaixo(personagem);
			if (teclas[LEFT])
				personagemMoveEsquerda(personagem);
			if (teclas[RIGHT])
				personagemMoveDireira(personagem);
			if (++frameCount >= frameDelay) {
				if (++curFrame >= maxFrame)
					curFrame = 0;

				frameCount = 0;
			}
			if (!gameOver) {
				liberaObstaculos(obstaculos, QTD_OBSTACULOS);
				moveObstaculos(obstaculos, QTD_OBSTACULOS);
				colidirObstaculos(obstaculos, QTD_OBSTACULOS, personagem, insMedalhas);

				if (personagem.vida <= 0)
					fim = true;
			}
		}

		if (desenha && al_is_event_queue_empty(filaEventos)) {
			// -------------- DESENHO DO OBJETO ----------------
			desenha = false;
			if (!gameOver) {
				// Desenho os bitmaps
				// C�u
				al_draw_scaled_rotated_bitmap(imagemCeu, 0, 0, 0, 0, 0.5, 0.65, 0, 0);
				//Mar
				al_draw_tinted_scaled_rotated_bitmap_region(ondaInterna, curFrame * frameOndaInernaLargura, 0, frameOndaInernaLargura, frameOndaInternaAltura, al_map_rgb(255, 255, 255), 0, 0, 0, heightSurf / 3, 1.1, 1.8, 0, 0);
				desenhaPersonagem(personagem);
				desenhaObstaculos(obstaculos, QTD_OBSTACULOS);

				//desenhaMar(onda);
				al_draw_tinted_scaled_rotated_bitmap_region(onda, curFrame * frameOndaLargura, 0, frameOndaLargura, frameOndaAltura, al_map_rgb(255, 255, 255), 0, 0, -8, heightSurf / 3 - 13, 2, 3.2, 0, 0);

				al_draw_textf(fontVida, al_map_rgb(0, 0, 0), widthSurf / 2, 20, ALLEGRO_ALIGN_CENTRE, "CAPTURE as medalhas: %d", personagem.vida);

			}


			// ------------------- MOSTRA NO DISPLAY E BACKBUFFER
			al_flip_display(); // Mostra o que � feito no display.
			al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa o display a cada movimenta��o.
		}

	}

	if (personagem.vida == 0) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(fontGameOver, al_map_rgb(255, 255, 255), widthSurf / 2, heightSurf / 2, ALLEGRO_ALIGN_CENTER, "Voce venceu!");
		al_flip_display();
		pontoSurf++;
		al_rest(2.0);
	}
	else {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(fontGameOver, al_map_rgb(255, 255, 255), widthSurf / 2, heightSurf / 2, ALLEGRO_ALIGN_CENTER, "Voce perdeu!");
		al_flip_display();
		al_rest(2.0);
	}

	for (int i = 0; i <= 6; i++)
		keys[i] = false;

	// --------------------- DESTRUI��O DOS EVENTOS USADOS
	al_destroy_sample_instance(insTrilhaSonora);
	al_destroy_sample_instance(insMedalhas);
	al_destroy_font(fontGameOverTexto);
	al_destroy_font(fontVida);
	al_destroy_font(fontGameOver);
	al_destroy_bitmap(imagemObstaculos);
	al_destroy_bitmap(imagemPersonagem);
	al_destroy_bitmap(ondaInterna);
	al_destroy_bitmap(onda);
	al_destroy_bitmap(imagemCeu);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(filaEventos);

	return 0;
}