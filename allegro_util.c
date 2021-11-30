#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "allegro_util.h"

ALLEGRO_DISPLAY* janela = NULL;
static ALLEGRO_PATH* dir = NULL;
ALLEGRO_FONT* fonte = NULL;
ALLEGRO_BITMAP* imagens[3] = { NULL, NULL, NULL };
ALLEGRO_SAMPLE* som = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

static int inicializa_font(void)
{
    al_init_font_addon();
    return al_init_ttf_addon();
}

static ALLEGRO_FONT* carrega_fonte(char* filename)
{
    al_set_path_filename(dir, filename);
    return al_load_ttf_font(al_path_cstr(dir, '/'), 32, 0);
}

static ALLEGRO_BITMAP* carrega_imagem(char* filename)
{
    al_set_path_filename(dir, filename);
    return al_load_bitmap(al_path_cstr(dir, '/'));
}

static ALLEGRO_SAMPLE* carrega_som(char* filename)
{
    al_set_path_filename(dir, filename);
    return al_load_sample(al_path_cstr(dir, '/'));
}

int inicializa_allegro(void)
{
    int sucesso = 0;

    if (!al_init()) {
        fprintf(stderr, "al_init\n");
    }
    else if (!al_init_primitives_addon()) {
        fprintf(stderr, "al_init_primitives_addon\n");
    }
    else if (!inicializa_font()) {
        fprintf(stderr, "inicializa_font\n");
    }
    else if (!al_init_image_addon()) {
        fprintf(stderr, "al_init_image_addon\n");
    }
    else if (!al_install_audio()) {
        fprintf(stderr, "al_install_audio\n");
    }
    else if (!al_init_acodec_addon()) {
        fprintf(stderr, "al_init_acodec_addon\n");
    }
    else if (!al_reserve_samples(1)) {
        fprintf(stderr, "al_reserve_samples\n");
    }
    else if (!al_install_mouse()) {
        fprintf(stderr, "al_install_mouse\n");
    }
    else if (!(dir = al_get_standard_path(ALLEGRO_RESOURCES_PATH))) {
        fprintf(stderr, "al_get_standard_path\n");
    }
    else if (!(fonte = carrega_fonte("halo3.ttf"))) {
        fprintf(stderr, "carrega_fonte\n");
    }
    else if (!(imagens[0] = carrega_imagem("img1.jpg"))) {
        fprintf(stderr, "carrega_imagem\n");
    }
    else if (!(imagens[1] = carrega_imagem("img2.jpg"))) {
        fprintf(stderr, "carrega_imagem\n");
    }
    else if (!(imagens[2] = carrega_imagem("img3.jpg"))) {
        fprintf(stderr, "carrega_imagem\n");
    }
    else if (!(som = carrega_som("slide.wav"))) {
        fprintf(stderr, "carrega_som\n");
    }
    else if (!(janela = al_create_display(800, 600))) {
        fprintf(stderr, "al_create_display\n");
    }
    else if (!(fila_eventos = al_create_event_queue())) {
        fprintf(stderr, "al_create_event_queue\n");
    }
    else {
        sucesso = 1;

        al_set_window_title(janela, "Revisão de C com Allegro");
        al_register_event_source(fila_eventos, al_get_display_event_source(janela));
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
    }

    if (!sucesso) {
        finaliza_allegro();
    }

    return sucesso;
}

void finaliza_allegro(void)
{
    if (fila_eventos) {
        al_unregister_event_source(fila_eventos, al_get_mouse_event_source());
        al_unregister_event_source(fila_eventos, al_get_display_event_source(janela));
        al_destroy_event_queue(fila_eventos);
    }
    if (janela) al_destroy_display(janela);
    if (som) al_destroy_sample(som);
    if (imagens[2]) al_destroy_bitmap(imagens[2]);
    if (imagens[1]) al_destroy_bitmap(imagens[1]);
    if (imagens[0]) al_destroy_bitmap(imagens[0]);
    if (fonte) al_destroy_font(fonte);
    if (dir) al_destroy_path(dir);
    al_uninstall_mouse();
    al_uninstall_audio();
    al_shutdown_image_addon();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
}