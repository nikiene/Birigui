#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include "movimento.h"
#include "constantes.h"
#include "placar.h"
#include "definicao.h"


void drawPlayer(Player& p) {
	al_draw_bitmap(p.sprite, p.x, p.y, 0);
}

void drawBall(Ball& b) {
	al_draw_filled_circle(b.x, b.y, b.raio, al_map_rgb(255, 255, 255));
}

void drawPlacar(ALLEGRO_FONT* fontHeader, ALLEGRO_FONT* fontBody) {
	al_draw_text(fontHeader, al_map_rgb(255, 255, 255), 2 * widthSkate / 10 + 5, 4 * heightSkate / 9, ALLEGRO_ALIGN_CENTER, "Pts");
	al_draw_textf(fontBody, al_map_rgb(255, 255, 255), 2 * widthSkate / 10 + 5, 4 * heightSkate / 9 + 20, ALLEGRO_ALIGN_CENTER, "P %d - %d B", pontosPlayer, pontosBot);
	al_draw_text(fontHeader, al_map_rgb(255, 255, 255), (8 * widthSkate) / 10 - 5, (4 * heightSkate / 9), ALLEGRO_ALIGN_CENTER, "Sets ");
	al_draw_textf(fontBody, al_map_rgb(255, 255, 255), (8 * widthSkate) / 10 - 5, (4 * heightSkate / 9) + 20, ALLEGRO_ALIGN_CENTER, "%d - %d ", setsPlayer, setsBot);
}

void DrawJogador(Jogador& jogador) {
	if (imagemJogador > 5) {
		if (imagemJogador == 7) {
			imagemJogador = 0;
		}
		jogador.sprite = al_load_bitmap("jogador2.png");
		al_draw_bitmap(jogador.sprite, jogador.x1, jogador.y2, 0);

	}
	else {
		jogador.sprite = al_load_bitmap("jogador1.png");
		al_draw_bitmap(jogador.sprite, jogador.x1, jogador.y2, 0);
	}

	al_destroy_bitmap(jogador.sprite);
	//al_draw_filled_rectangle(jogador.x1, jogador.y1, jogador.x2, jogador.y2, al_map_rgb(255, 0, 0));
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

void DrawBackgorund() {
	ALLEGRO_BITMAP* ceu;
	ceu = al_load_bitmap("backgroundSkate.png");
	al_draw_bitmap(ceu, 0, 0, 0);
	al_destroy_bitmap(ceu);

	ALLEGRO_BITMAP* chao;
	chao = al_load_bitmap("rua.png");
	al_draw_bitmap(chao, 0, 160, 0);
	al_destroy_bitmap(chao);
}

void DrawText(Jogador& jogador, int segundos, int minutos) {

	ALLEGRO_FONT* font = al_load_font("fontePlacar.ttf", 35, 0);

	if (jogador.status == VIVO)
	{
		if (segundos < 10) {
			al_draw_textf(font, al_map_rgb(255, 211, 0), 10, 10, 0, "%d : 0%d", minutos, segundos);
		}
		else {
			al_draw_textf(font, al_map_rgb(255, 211, 0), 10, 10, 0, "%d : %d", minutos, segundos);
		}
	}
	else {
		if (minutos == 1) {
			al_draw_text(font, al_map_rgb(255, 211, 0), widthSkate / 2, heightSkate / 3, ALLEGRO_ALIGN_CENTER, "BOA!");
			al_draw_text(font, al_map_rgb(255, 211, 0), widthSkate / 2, (heightSkate / 3 + heightSkate / 3) - 105, ALLEGRO_ALIGN_CENTER, "Voce venceu o meu desafio e");
			al_draw_text(font, al_map_rgb(255, 211, 0), widthSkate / 2, (heightSkate / 3 + heightSkate / 3) - 65, ALLEGRO_ALIGN_CENTER, "provou ser o proprio choris!");
		}
		else {
			al_draw_text(font, al_map_rgb(255, 211, 0), widthSkate / 2, heightSkate / 3, ALLEGRO_ALIGN_CENTER, "VOCE PERDEU!");
			al_draw_text(font, al_map_rgb(255, 211, 0), widthSkate / 2, (heightSkate / 3 + heightSkate / 3) - 105, ALLEGRO_ALIGN_CENTER, "Tente Novamente!");
		}
	}

	al_destroy_font(font);
}

void PlaySound(ALLEGRO_SAMPLE* sample) {
	al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
}

void PlaySoundBaixo(ALLEGRO_SAMPLE* sample) {
	al_play_sample(sample, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
}

void DrawPlantas(Plantas plantas[], int size) {
	for (int i = 0; i < size; i++) {
		if (plantas[i].status == VIVO && plantas[i].tipo == 1 && plantas[i].tipoArvore == 0) {
			plantas[i].sprite = al_load_bitmap("arvore1.png");
			al_draw_bitmap(plantas[i].sprite, plantas[i].x, plantas[i].y, ALLEGRO_ALIGN_CENTER);
			al_destroy_bitmap(plantas[i].sprite);
		} if (plantas[i].status == VIVO && plantas[i].tipo == 1 && plantas[i].tipoArvore == 1) {
			plantas[i].sprite = al_load_bitmap("arvore2.png");
			al_draw_bitmap(plantas[i].sprite, plantas[i].x, plantas[i].y, ALLEGRO_ALIGN_CENTER);
			al_destroy_bitmap(plantas[i].sprite);
		} if (plantas[i].status == VIVO && plantas[i].tipo == 0) {
			plantas[i].sprite = al_load_bitmap("arbusto.png");
			al_draw_bitmap(plantas[i].sprite, plantas[i].x, plantas[i].y, ALLEGRO_ALIGN_CENTER);
			al_destroy_bitmap(plantas[i].sprite);
		}
	}
}

void DrawParallax(Parallax& parallax) {
	al_draw_bitmap(parallax.sprite, parallax.x, parallax.y, 0);

	if (parallax.x + widthSkate < widthSkate)
		al_draw_bitmap(parallax.sprite, parallax.x + widthSkate, parallax.y, 0);
}

void desenhaPersonagem(Personagem& personagem) {
	//al_draw_filled_rectangle(personagem.posX, personagem.posY, personagem.posX + 60, personagem.posY + 130, al_map_rgb(255, 0, 0));
	al_draw_tinted_scaled_rotated_bitmap_region(personagem.imagemPersonagem, personagem.curFrame * personagem.frameLargura, 0, personagem.frameLargura, personagem.frameAltura, al_map_rgb(255, 255, 255), 0, 0, (personagem.posX - personagem.frameLargura + 30), (personagem.posY - personagem.frameAltura + 30), 1.8, 1.8, 0, 0);
}

void liberaObstaculos(Obstaculos obstaculos[], int quantidade) {
	for (int i = 0; i < quantidade; i++) {
		if (!obstaculos[i].ativo) {
			if (rand() % 500 == 0) {
				obstaculos[i].posX = widthSurf;
				obstaculos[i].posY = rand() % heightSurf + (heightSurf / 3) + 50;
				obstaculos[i].ativo = true;
				obstaculos[i].curFrame = rand() % obstaculos[i].maxFrame;
				break;
			}
		}
	}
}

void desenhaObstaculos(Obstaculos obstaculos[], int quantidade) {
	for (int i = 0; i < quantidade; i++) {
		if (obstaculos[i].ativo) {
			//al_draw_filled_circle(obstaculos[i].posX, obstaculos[i].posY, 10, al_map_rgb(255, 0, 0));
			al_draw_bitmap_region(obstaculos[i].imagemObstaculos, obstaculos[i].curFrame * obstaculos[i].frameLargura, 0, obstaculos[i].frameLargura, obstaculos[i].frameAltura, obstaculos[i].posX - 20, obstaculos[i].posY - 30, 0);
		}
	}
}
