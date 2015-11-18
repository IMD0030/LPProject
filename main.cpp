#define LARGURA 800
#define ALTURA 600
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include <cstring>
#include "Nave.h"
#include "GameObject.h"
#include "GameObjectList.h"
#include "Bullet.h"
#include "Utils.h"
#include <string.h>
#include <sstream>
#include "Asteroide.h"

using namespace std;


int main() {

    if (!al_init()) {
		cout << "Erro inicializando allegro" << endl;
	}


	cout << "Teste de git" << endl;
	/*MAXIMO DE INIMIGOS */
	int MAXINIMIGO = 10;
	/*FREQUENCIA QUE O INIMIGO APARECE*/
	int FREQUENCIAIMIGO=30;
	/*Variavel que verifica estado do jogo*/
    bool finalized = false;
    /*CONTADOR DA FREQUENCIA DE INIMIGO*/
    int astInimigo = 0;
    /* VARIAVEIS PARA MUDAR A POSIÇÃO DO NOVO IMIGO*/
    float astPX = 0, oldastPX = 0, velPY = 0;
    int menorPX=1;

    /*VARIAVEIS DO ALLEGRO*/
	ALLEGRO_DISPLAY *tela = al_create_display(LARGURA, ALTURA);
	ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
    ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    ALLEGRO_SAMPLE *shoot=NULL, *explosion=NULL;
    ALLEGRO_EVENT evento;
    ALLEGRO_KEYBOARD_STATE estado_teclado;

    /* INSTALÇÕES DO ALLEGRO */
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_install_audio();	
	al_reserve_samples(10);
	shoot = al_load_sample( "Sound/shoot.ogg" );
	explosion = al_load_sample("Sound/explosion.wav");
	/*Iniciar Eventos */
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_start_timer(timer);
	

    /*Player Nave Do Jogador*/
    Nave *navePlayer = new Nave(LARGURA/2, ALTURA);
    /*OBJETOS DO JOGO, BALAS E INIMIGOS */
    Bullet *bullet = new Bullet();
    Asteroide *aste = new Asteroide();

    /*Lista de Objetos (Inimigos ou Asteroides)*/
    GameObjectList *ListaBullets = new GameObjectList();
    GameObjectList *ListaAsteroides = new GameObjectList();
    
    

	
	//testes
	//aste->Novo(ListaAsteroides, LARGURA/2, 2, 2);
	//al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
	while (!finalized) {


		al_wait_for_event(fila_eventos, &evento);
		al_get_keyboard_state(&estado_teclado);
		
		if(al_key_down(&estado_teclado, ALLEGRO_KEY_W) || al_key_down(&estado_teclado, ALLEGRO_KEY_UP)) {
			navePlayer->Up();
		}
		if(al_key_down(&estado_teclado, ALLEGRO_KEY_S) || al_key_down(&estado_teclado, ALLEGRO_KEY_DOWN)) {
			navePlayer->Down();
		}
		if(al_key_down(&estado_teclado, ALLEGRO_KEY_A) || al_key_down(&estado_teclado, ALLEGRO_KEY_LEFT)) {
			navePlayer->Left();
		}
		if(al_key_down(&estado_teclado, ALLEGRO_KEY_D) || al_key_down(&estado_teclado, ALLEGRO_KEY_RIGHT)){
			navePlayer->Right();
		}

		//navePlayer->Update(estado_teclado*, evento);

		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			if(evento.keyboard.keycode == 59 || evento.keyboard.keycode==ALLEGRO_KEY_ESCAPE) {
				finalized = true;
			}
			if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
				bullet->Novo(*navePlayer, ListaBullets);
				al_play_sample(shoot, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			}
			if(evento.keyboard.keycode == ALLEGRO_KEY_I){
				while(oldastPX == astPX){
					astPX = rand()%(LARGURA-menorPX)+menorPX;
				}
				oldastPX=astPX;
				velPY = rand()%(10-3)+5;
				aste->Novo(ListaAsteroides, astPX, 2, 1);
			}
			else {
				//navePlayer->Update(&estado_teclado, evento);
				//navePlayer->Update(&estado_teclado);
				cout << "KEYDOWN: " << evento.keyboard.keycode << endl;
			}
			
		}
		while(oldastPX == astPX){
			astPX = rand()%(LARGURA-menorPX)+menorPX;
		}
		oldastPX=astPX;
		velPY = rand()%(10-2)+2;
		velPY = 2;

		if (evento.type == ALLEGRO_EVENT_TIMER) {
			
			astInimigo++;
			if(astInimigo >= FREQUENCIAIMIGO && ListaAsteroides->ObjectCont() < MAXINIMIGO){
				//cout << "Criando novo asteroide";
				aste->Novo(ListaAsteroides, astPX, 2, velPY);
				astInimigo = 0;
			}
			//asteroide definido e criado


			// desenhar
			ListaBullets->Render();
			ListaAsteroides->Render();
			navePlayer->Render();

	

			al_flip_display();
			al_clear_to_color(al_map_rgb(255, 255, 255));

			// atualizar estado
			ListaBullets->Update();
			ListaAsteroides->Update();
			navePlayer->Impacto(ListaAsteroides);
			

			if(ListaBullets->ImpactoFirstElement(navePlayer, ListaAsteroides)){
				al_play_sample(explosion, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

			}
		}

	}

	return 0;
}