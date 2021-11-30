#include <allegro5/allegro.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
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

int boxe(ALLEGRO_DISPLAY* display) 
{
    ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
    ALLEGRO_BITMAP* player = 0, * bot = NULL, * jeb = NULL, * gancho = NULL, * chute = NULL, * vida_p = NULL, * vida_b = NULL, * final = NULL;
    ALLEGRO_AUDIO_STREAM* musica = NULL;
    ALLEGRO_BITMAP* background;
    ALLEGRO_SAMPLE* sample = NULL;
    int PL = 3, BL = 3;

    bool sair = false;
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    al_init_image_addon();


    if (!al_install_audio())
    {
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        return false;
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        return false;
    }

    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        return false;
    }

    musica = al_load_audio_stream("theme.ogg", 4, 1024);
    if (!musica)
    {
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_event_queue(fila_eventos);
        al_destroy_display(display);
        al_destroy_sample(sample);
        return false;
    }

    sample = al_load_sample("soco.wav");
    if (!sample)
    {
        fprintf(stderr, "Falha ao carregar sample.\n");
        al_destroy_display(display);
        return false;
    }


    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);

    background = al_load_bitmap("background.jpg");
    al_draw_bitmap(background, 0, 0, 0);


    // Configura o título da display
    al_set_window_title(display, "Boxe birigui");

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(display);
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(display);
        return -1;
    }

    // locando bitmaps
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

    final = al_create_bitmap(640, 480);
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

    // Alocamos o botão para fechar a aplicação
    //OLHA AQUI KRL

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
        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);


            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                //AÇÃO JEB vermelho
                if (evento.mouse.x >= 80 &&
                    evento.mouse.x <= 180 &&
                    evento.mouse.y >= 380 &&
                    evento.mouse.y <= 430
                    )
                {
                    acaoP = 1;
                    acaoB = rand() % 3 + 1;
                    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    printf_s("JEB-VERMELHO, %d, %d\n", acaoP, acaoB);
                    printf_s("%s", combat(acaoP, acaoB, PL, BL));
                    printf_s("player: %d, bot %d\n", PL, BL);
                    endgame(BL, PL);

                }
                //AÇÃO CHUTE verde
                else if (evento.mouse.x >= 280 &&
                    evento.mouse.x <= 380 &&
                    evento.mouse.y >= 380 &&
                    evento.mouse.y <= 430
                    )
                {
                    acaoP = 3;
                    acaoB = rand() % 3 + 1;
                    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    printf_s("CHUTE-VERDE, %d, %d\n", acaoP, acaoB);
                    printf_s("%s", combat(acaoP, acaoB, PL, BL));
                    printf_s("player: %d,bot %d\n", PL, BL);
                    endgame(BL, PL);
                }
                //AÇÃO GANCHO azul
                else if (evento.mouse.x >= 480 &&
                    evento.mouse.x <= 580 &&
                    evento.mouse.y >= 380 &&
                    evento.mouse.y <= 430
                    )
                {
                    acaoP = 2;
                    acaoB = rand() % 3 + 1;
                    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                    printf_s("GANCHO-AZUL, %d, %d\n", acaoP, acaoB);
                    printf_s("%s\n", combat(acaoP, acaoB, PL, BL));
                    printf_s("player: %d,bot %d\n", PL, BL);
                    endgame(BL, PL);

                }
            }
        }

        // Limpamos a tela


        // Colorindo player de acordo com a acao

        if (acaoP == 1)
        {
            player = al_load_bitmap("jeb_p.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(player, 20, 123, 0);


        }
        else if (acaoP == 2)
        {

            player = al_load_bitmap("varios_p.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(player, 20, 122, 0);

        }
        else if (acaoP == 3)
        {
            player = al_load_bitmap("chute_p.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(player, 20, 122, 0);

        }
        else
        {

            player = al_load_bitmap("base_pn.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(player, 20, 122, 0);


        }

        //bot

        if (acaoB == 1)
        {
            bot = al_load_bitmap("jeb_b.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(bot, 340, 122, 0);

        }
        else if (acaoB == 2)
        {
            bot = al_load_bitmap("varios_b.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(bot, 340, 122, 0);


        }
        else if (acaoB == 3)
        {

            bot = al_load_bitmap("chute_b.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(bot, 340, 122, 0);

        }
        else
        {

            bot = al_load_bitmap("base_b.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(bot, 340, 122, 0);


        }

        //vida player


        if (PL == 3)
        {
            vida_p = al_load_bitmap("vida3.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(vida_p, 120, 60, 0);
        }
        else if (PL == 2)
        {

            vida_p = al_load_bitmap("vida2.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(vida_p, 120, 60, 0);
        }
        else if (PL == 1)
        {

            vida_p = al_load_bitmap("vida1.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(vida_p, 120, 60, 0);
        }

        else {


            final = al_load_bitmap("botwin.png");
            al_draw_bitmap(final, 0, 0, 0);
            al_flip_display();
            al_rest(3.0);
            sair = true;
        }

        //vida bot


        if (BL == 3)
        {

            vida_b = al_load_bitmap("vida3.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(vida_b, 460, 60, 0);

        }
        else if (BL == 2)
        {

            vida_b = al_load_bitmap("vida2.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(vida_b, 460, 60, 0);

        }
        else if (BL == 1)
        {

            vida_b = al_load_bitmap("vida1.png");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(vida_b, 460, 60, 0);
        }

        else {

            final = al_load_bitmap("playerwin.jpg");
            al_draw_bitmap(final, 0, 0, 0);
            al_flip_display();
            al_rest(3.0);
            sair = true;
        }

        // Colorimos o bitmap dos botões


        //al_clear_to_color(al_map_rgb(255, 0, 0));


        // Desenhamos os retângulos na tela

        al_set_target_bitmap(al_get_backbuffer(display));



        al_draw_bitmap(jeb, 80, 380, 0);
        jeb = al_load_bitmap("jeb.png");



        al_draw_bitmap(gancho, 480, 380, 0);
        gancho = al_load_bitmap("combo.png");



        al_draw_bitmap(chute, 280, 380, 0);
        chute = al_load_bitmap("chute.png");

        al_draw_bitmap(final, 0, 0, 0);


        // Atualiza a tela
        al_flip_display();
    }


    // Desaloca os recursos utilizados na aplicação

    al_destroy_bitmap(player);
    al_destroy_bitmap(bot);
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(jeb);
    al_destroy_bitmap(chute);
    al_destroy_bitmap(gancho);
    al_destroy_audio_stream(musica);
    al_destroy_sample(sample);
    al_destroy_bitmap(background);

    return 0;
}