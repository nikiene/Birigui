#ifndef ALLEGRO_UTIL_H_INCLUDED
#define ALLEGRO_UTIL_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

extern ALLEGRO_DISPLAY* janela;
extern ALLEGRO_FONT* fonte;
extern ALLEGRO_BITMAP* imagens[3];
extern ALLEGRO_SAMPLE* som;
extern ALLEGRO_EVENT_QUEUE* fila_eventos;

int inicializa_allegro(void);
void finaliza_allegro(void);

#endif /* ALLEGRO_UTIL_H_INCLUDED */