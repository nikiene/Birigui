#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//o enum cria um vetor que associa seu valor ao número de sua posição. Assim, em vez de usar número, é usado o nome em seu lugar.
enum TECLAS {CIMA, BAIXO, DIREITA, ESQUERDA};

// Função main:
int main()
{
	//				VARIÁVEIS DO JOGO
	// Variáveis da resolução do display
	const int largura = 800;
	const int altura = 600;

	// Variáveis da posição do personagem no jogo
	int pos_x = 100;
	int pos_y = 100;

	// Variáveis para a fila de eventos
	ALLEGRO_EVENT_QUEUE *fila_evento = NULL; // Cria ponteiro fila_evento do tipo ALLEGRO_EVENT_QUEUE 
	
	// Variáveis para o loop principal
	bool fim = false;
	bool teclas[] = { false, false, false, false }; // O enum será útil aqui. Onde, em vez de usar número para se obter o valor false, é usado os nomes que estão no enum.
	//				INICIALIZAÇÃO DO ALLEGRO
	
	// Cria um ponteiro inicializado com NULL. 
	ALLEGRO_DISPLAY *display = NULL;

	// al_init() é uma função que permite a inicialização dos recursos do jogo.
	// Sem ela, o jogo não funciona.
	if (!al_init()) {
		al_show_native_message_box(NULL, "AVISO!", "ERRO:", "Allegro não pode ser inicializar", NULL, NULL);
		return -1;
	}

	display = al_create_display(largura, altura);

	if (!display) {
		al_show_native_message_box(NULL, "AVISO!", "ERROR!", "Não foi possível inicializar o display", NULL, NULL);
		return -1;
	}

	//				INICIALIZAÇÃO DOS ADDONS
	// Toda função do Allegro precisa ser inicializada pelos addons.
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//				CRIAR FILA DE EVENTOS E DEMAIS DISPOSITIVOS
	// No campo das variáveis foi criado o ponteiro fila_evento com valor NULL.
	// Agora, para sua utilização, é atribuido a função que cria eventos a esse ponteiro.
	fila_evento = al_create_event_queue();

	//				REGISTRO DE SOURCES
	// Agora é necessário que aja um registro dos eventos, qualquer que forem criados, para serem
	// atribuidos ao pontiero fila_evento. Assim:
	al_register_event_source(fila_evento, al_get_display_event_source(display)); // a função al_get_display_event_source pede um parametro que, no caso, é o ponteiro display.
	al_register_event_source(fila_evento, al_get_keyboard_event_source()); // Aqui a função al_register_event_source permite que o ponteiro fila_evento receba os dados do teclado pelo al_get_keyboard_event_source().
	al_register_event_source(fila_evento, al_get_mouse_event_source()); // Igual ao anterio, mas para o mouse.

	//				LOOP PRINCIPAL

	while (!fim) 
	{
		ALLEGRO_EVENT ev; // Esse tipo ALLEGRO_EVENT cria uma variável que aceita "qualquer tipo de evento" estabelecido.
		al_wait_for_event(fila_evento, &ev); // A função al_wait_for_event aguarda uma ação (entrada de dados). Quando entra dados, o ev recebe e manda para o ponteiro fila_evento.

		//				LÓGICA DO JOGO
		// Como a variável ev aceita qualquer tipo de entrada de dados, o if a seguir faz a comparação dos dados de entrada para executar seu comando.
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) /* ALLEGRO_EVENT_KEY_DOWN é o reconhecimento de que um botão qualquer foi apertado */
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) // Como o comando acima reconhece qualquer tecla apertada. Agora, vem a validação de qual tecla foi apertada para executar o if.
			{ 
				fim = true;
			}
			switch (ev.keyboard.keycode) 
			{
				case ALLEGRO_KEY_UP:
					teclas[CIMA] = true; // Aplicação do enum dentro do vetor. O valor original do vetor é false...
					break;
				case ALLEGRO_KEY_DOWN:
					teclas[BAIXO] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					teclas[DIREITA] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					teclas[ESQUERDA] = true;
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					teclas[CIMA] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					teclas[BAIXO] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					teclas[DIREITA] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					teclas[ESQUERDA] = false;
					break;
			}
		}

		//				MOVIMENTO DO OBJETO
		pos_y -= teclas[CIMA] * 10;
		pos_y += teclas[BAIXO] * 10;
		pos_x += teclas[DIREITA] * 10;
		pos_x -= teclas[ESQUERDA] * 10;

		//				DESENHO DO OBJETO
		al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 0));
		
		//				MOSTRA NO DISPLAY E BACKBUFFER
		al_flip_display(); // Mostra o que é feito no display.
		al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa o display a cada movimentação.

		
	}

	//				DESTRUIÇÃO DOS EVENTOS USADOS
	al_destroy_display(display);
	al_destroy_event_queue(fila_evento);

	return 0;
}