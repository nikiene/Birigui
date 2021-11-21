#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include "constantes.h"
#include "desenho.h"
#include "definicao.h"
#include "placar.h"
#include "movimento.h"
#include "structs.h"

int surf(ALLEGRO_DISPLAY* display)
{
	//				VARI�VEIS DO JOGO
	// Vari�veis da resolu��o do display

	// Vari�veis da posi��o do personagem no jogo
	int pos_x = 100;
	int pos_y = 100;

	// Vari�veis para a fila de eventos
	ALLEGRO_EVENT_QUEUE* fila_evento = NULL; // Cria ponteiro fila_evento do tipo ALLEGRO_EVENT_QUEUE 

	// Vari�veis para o loop principal
	bool fim = false;
	
	//				INICIALIZA��O DO ALLEGRO
	// al_init() � uma fun��o que permite a inicializa��o dos recursos do jogo.
	// Sem ela, o jogo n�o funciona.
	if (!al_init()) {
		al_show_native_message_box(NULL, "AVISO!", "ERRO:", "Allegro n�o pode ser inicializar", NULL, NULL);
		return -1;
	}

	if (!display) {
		al_show_native_message_box(NULL, "AVISO!", "ERROR!", "N�o foi poss�vel inicializar o display", NULL, NULL);
		return -1;
	}

	//				CRIAR FILA DE EVENTOS E DEMAIS DISPOSITIVOS
	// No campo das vari�veis foi criado o ponteiro fila_evento com valor NULL.
	// Agora, para sua utiliza��o, � atribuido a fun��o que cria eventos a esse ponteiro.
	fila_evento = al_create_event_queue();

	//				REGISTRO DE SOURCES
	// Agora � necess�rio que aja um registro dos eventos, qualquer que forem criados, para serem
	// atribuidos ao pontiero fila_evento. Assim:
	al_register_event_source(fila_evento, al_get_display_event_source(display)); // a fun��o al_get_display_event_source pede um parametro que, no caso, � o ponteiro display.
	al_register_event_source(fila_evento, al_get_keyboard_event_source()); // Aqui a fun��o al_register_event_source permite que o ponteiro fila_evento receba os dados do teclado pelo al_get_keyboard_event_source().
	al_register_event_source(fila_evento, al_get_mouse_event_source()); // Igual ao anterio, mas para o mouse.

	//				LOOP PRINCIPAL

	while (!fim)
	{
		ALLEGRO_EVENT ev; // Esse tipo ALLEGRO_EVENT cria uma vari�vel que aceita "qualquer tipo de evento" estabelecido.
		al_wait_for_event(fila_evento, &ev); // A fun��o al_wait_for_event aguarda uma a��o (entrada de dados). Quando entra dados, o ev recebe e manda para o ponteiro fila_evento.

		//				L�GICA DO JOGO
		// Como a vari�vel ev aceita qualquer tipo de entrada de dados, o if a seguir faz a compara��o dos dados de entrada para executar seu comando.
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) /* ALLEGRO_EVENT_KEY_DOWN � o reconhecimento de que um bot�o qualquer foi apertado */
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) // Como o comando acima reconhece qualquer tecla apertada. Agora, vem a valida��o de qual tecla foi apertada para executar o if.
			{
				fim = true;
			}
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true; // Aplica��o do enum dentro do vetor. O valor original do vetor � false...
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			}
		}

		//				MOVIMENTO DO OBJETO
		pos_y -= keys[UP] * 10;
		pos_y += keys[DOWN] * 10;
		pos_x += keys[RIGHT] * 10;
		pos_x -= keys[LEFT] * 10;

		//				DESENHO DO OBJETO
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 0));

		//				MOSTRA NO DISPLAY E BACKBUFFER
		al_flip_display(); // Mostra o que � feito no display.
		al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa o display a cada movimenta��o.


	}

	//				DESTRUI��O DOS EVENTOS USADOS
	al_destroy_display(display);
	al_destroy_event_queue(fila_evento);

	for (int i = 0; i < 4; i++) {
		keys[i] = false;
	}

	return 0;
}