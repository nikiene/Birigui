#pragma once
int pontosBot = 0;
int pontosPlayer = 0;
int setsBot = 0;
int setsPlayer = 0;

void zeraPontuacao() {
	pontosPlayer = 0;
	pontosBot = 0;
}

void zeraPlacar() {
	zeraPontuacao();
	setsPlayer = 0;
	setsBot = 0;
}
