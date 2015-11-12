#include <iostream>
#include <cstring>
#include <typeinfo>
#include <allegro5/allegro.h>
#include "GameObject.h"
#include "GameObjectList.h"
#include "Bullet.h"
#include <math.h> 
#include "Nave.h"

Bullet::Bullet() {
	
}

void Bullet::Novo(Nave n, GameObjectList *Bullets) {
	Bullet *tiro = new Bullet();
	tiro->posicao_x = n.p_x + n.tamanho/2;
	tiro->posicao_y = n.p_y;
	tiro->raio = SIZEBULLET;
	tiro->velocidade_y = 15;
	std::cout << "Bala adicionada x: "<< n.p_x << " e y: " << n.p_y << std::endl;
	Bullets->Adicionar(tiro);
}

void Bullet::Start(){
    std::cout << "Iniciei!" << std::endl;
}

void Bullet::Update(){
	this->posicao_y -= this->velocidade_y;

	if (this->posicao_y <= 0) {
		this->posicao_y = 0;

		std :: cout << "essa bala precisa ser destruida" << std::endl;
	}

    std::cout << "Atualize!" << std::endl;
}

void Bullet::Render(){
    al_draw_filled_circle(this->posicao_x, this->posicao_y, this->raio, al_map_rgb(255, 0, 0));
}