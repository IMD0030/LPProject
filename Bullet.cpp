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

void Novo(Nave n, GameObjectList *Bullets) {
	Bullet *tiro = new Bullet();
	tiro->posicao_x = n.p_x;
	tiro->posicao_y = n.p_y;
	Bullets->Adicionar(tiro);
}

void Bullet::Start(){
    std::cout << "Iniciei!" << std::endl;
}

void Bullet::Update(){
    std::cout << "Atualize!" << std::endl;
}

void Bullet::Render(){
    al_draw_filled_circle(this->posicao_x, this->posicao_y, this->raio, al_map_rgb(255, 0, 0));
}