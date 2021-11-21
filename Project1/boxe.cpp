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
#include "jogos.h"

int boxe(ALLEGRO_DISPLAY* display) 
{   //setando variaveis
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    ALLEGRO_BITMAP* botao_sair = NULL, * player = 0, * bot = NULL, * jeb = NULL, * gancho = NULL, * chute = NULL, * vida_p = NULL, * vida_b = NULL;
    
    int sair = 0;
    int acaoP = 0, acaoB = 0;

    // Configura o t�tulo da janela
    al_set_window_title(display, "Boxe birigui");

    
    al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

    // Alocamos o ret�ngulo central da tela
    player = al_create_bitmap(30, 150);
    if (!player)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(display);
        return -1;
    }
    bot = al_create_bitmap(30, 150);
    if (!player)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(display);
        return -1;
    }
    jeb = al_create_bitmap(100, 50);
    if (!jeb)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(display);
        return -1;
    }
    gancho = al_create_bitmap(100, 50);
    if (!gancho)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(display);
        return -1;
    }
    chute = al_create_bitmap(100, 50);
    if (!chute)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(display);
        return -1;
    }

    vida_p = al_create_bitmap(10, 10);
    if (!vida_p)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(display);
        return -1;
    }
    vida_b = al_create_bitmap(10, 10);
    if (!vida_b)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(display);
        return -1;
    }



    // Alocamos o bot�o para fechar a aplica��o
    //OLHA AQUI KRL
    botao_sair = al_create_bitmap(100, 50);
    if (!botao_sair)
    {
        fprintf(stderr, "Falha ao criar bot�o de sa�da.\n");
        al_destroy_bitmap(player);
        al_destroy_display(display);
        return -1;
    }

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        al_destroy_display(display);
        return -1;
    }


    al_register_event_source(fila_eventos, al_get_mouse_event_source());


    int na_player = 0;
    while (!sair)
    {
           ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);


            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    sair = true;
            }

            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
            {

                if (evento.mouse.x >= width / 2 - al_get_bitmap_width(player) / 2 &&
                    evento.mouse.x <= width / 2 + al_get_bitmap_width(player) / 2 &&
                    evento.mouse.y >= height / 2 - al_get_bitmap_height(player) / 2 &&
                    evento.mouse.y <= height / 2 + al_get_bitmap_height(player) / 2)
                {
                    na_player = 1;
                }
                else
                {
                    na_player = 0;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                //A��O JEB vermelho
                if (evento.mouse.x >= 80 &&
                    evento.mouse.x <= 180 &&
                    evento.mouse.y >= 380 &&
                    evento.mouse.y <= 430
                    )
                {
                    acaoP = 1;
                    acaoB = rand() % 3 + 1;
                    al_clear_to_color(al_map_rgb(255, 255, 0));
                    printf_s("JEB-VERMELHO, %d, %d\n", acaoP, acaoB);
                    printf_s("%s", combat(acaoP, acaoB));
                    printf_s("player: %d, bot %d\n", PL, BL);
                    if (endgame(BL, PL))
                        sair = true;

                }
                //A��O CHUTE verde
                else if (evento.mouse.x >= 280 &&
                    evento.mouse.x <= 380 &&
                    evento.mouse.y >= 380 &&
                    evento.mouse.y <= 430
                    )
                {
                    acaoP = 3;
                    acaoB = rand() % 3 + 1;
                    al_set_target_bitmap(player);
                    al_clear_to_color(al_map_rgb(0, 255, 0));
                    printf_s("CHUTE-VERDE, %d, %d\n", acaoP, acaoB);
                    printf_s("%s", combat(acaoP, acaoB));
                    printf_s("player: %d,bot %d\n", PL, BL);
                    if (endgame(BL, PL))
                        sair = true;
                }
                //A��O GANCHO azul
                else if (evento.mouse.x >= 480 &&
                    evento.mouse.x <= 580 &&
                    evento.mouse.y >= 380 &&
                    evento.mouse.y <= 430
                    )
                {
                    acaoP = 2;
                    acaoB = rand() % 3 + 1;
                    al_set_target_bitmap(player);
                    al_clear_to_color(al_map_rgb(0, 0, 255));
                    printf_s("GANCHO-AZUL, %d, %d\n", acaoP, acaoB);
                    printf_s("%s\n", combat(acaoP, acaoB));
                    printf_s("player: %d,bot %d\n", PL, BL);
                    if (endgame(BL, PL))
                        sair = true;

                }
            }

           // Limpamos a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Colorimos o bitmap correspondente ao ret�ngulo central,
        // com a cor condicionada ao conte�do da flag na_area_central
        al_set_target_bitmap(player);
        if (!na_player)
        {
            al_clear_to_color(al_map_rgb(255, 255, 255));
        }
        else
        {
            al_clear_to_color(al_map_rgb(0, 255, 0));
        }

        // Colorimos o bitmap do bot�o de sair


        al_set_target_bitmap(vida_p);
        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_set_target_bitmap(vida_b);
        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_set_target_bitmap(jeb);
        al_clear_to_color(al_map_rgb(255, 0, 0));

        al_set_target_bitmap(bot);
        al_clear_to_color(al_map_rgb(255, 255, 255));

        al_set_target_bitmap(chute);
        al_clear_to_color(al_map_rgb(0, 255, 0));

        al_set_target_bitmap(gancho);
        al_clear_to_color(al_map_rgb(0, 0, 255));


        // Desenhamos os ret�ngulos na tela
        al_set_target_bitmap(al_get_backbuffer(display));

        al_draw_bitmap(player, 120, 120, 0);

        al_draw_bitmap(vida_p, 120, 170, 0);

        al_draw_bitmap(vida_b, 510, 170, 0);

        al_draw_bitmap(bot, 510, 120, 0);

        al_draw_bitmap(botao_sair, width - al_get_bitmap_width(botao_sair) - 10,
            height - al_get_bitmap_height(botao_sair) - 10, 0);

        al_draw_bitmap(jeb, 80, 380, 0);

        al_draw_bitmap(chute, 280, 380, 0);

        al_draw_bitmap(gancho, 480, 380, 0);




        // Atualiza a tela
        al_flip_display();
    }

    // Desaloca os recursos utilizados na aplica��o
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(player);
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);

    return 0;
}