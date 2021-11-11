// -------------- ARQUIVOS OBJETOS -------------------

enum { JOGADOR, INIMIGO };

struct personagem {
	int ID;
	int posX;
	int posY;
	int vida;
	int velocidade;
	int bordaX;
	int bordaY;
	int pontos;
};

struct obstaculos {
	int ID;
	int posX;
	int posY;
	int velocidade;
	int bordaX;
	int bordaY;
	bool ativo;
};

struct mar {
	int ID;
	int posX;
	int posY;
};