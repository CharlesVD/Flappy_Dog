#include <stdio.h>
#include <cstdlib>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap_draw.h>

ALLEGRO_DISPLAY *ventana;

int main(int argc, char **argv)
{
	
	ALLEGRO_KEYBOARD_STATE estadoTeclado;
	
	bool figuras = al_init_primitives_addon();
	bool inicio_allegro = al_init();
	bool teclado = al_install_keyboard();
	bool imagenes = al_init_image_addon();
	
	
	if(!figuras)
	{
		fprintf(stderr, "Error: No pudo cargar figuras.\n");
		return -1;
	}
	if(!imagenes)
	{
		fprintf(stderr, "Error: No pudo cargar imagenes.\n");
		return -1;
	}
	if(!inicio_allegro) 
	{
		fprintf(stderr, "Error: Allegro no pudo iniciar.\n");
		return -1;
	}
	
	if(!teclado) 
	{
		fprintf(stderr, "Error: El teclado no se detecto.\n");
		return -1;
	}
	
	ALLEGRO_BITMAP *perro[4];
	perro[0] = al_load_bitmap("0.png");
	perro[1] = al_load_bitmap("1.png");
	perro[2] = al_load_bitmap("2.png");
	perro[3] = al_load_bitmap("3.png");
	
	ALLEGRO_BITMAP *arbol[3];
	arbol[0] = al_load_bitmap("arbol1.png");
	arbol[1] = al_load_bitmap("arbol2.png");
	arbol[2] = al_load_bitmap("arbol3.png");
	
	ALLEGRO_BITMAP *cerca;
	cerca = al_load_bitmap("Cerca.png");
	
	ALLEGRO_BITMAP *Perder;
	Perder = al_load_bitmap("Perder.png");
	
	const int Mx = 600;
	const int My = 600;
	al_create_display(Mx,My);
	int cielo=0;
	int DegradCielo=0;
	int DegradSol=0;
	int Tierra=0;
	
	int perroX = 0;
	int perroY = 500;
	int perroE = 0;
	int tiempoE = 0;
	bool salta=false;
	bool arriba=false;
	bool perder=false;
	
	int arbolX1=Mx;
	int arbolX2=Mx+rand() % 600;
	int arbolX3=Mx+rand() % 600;
	int ArbolE1=rand() % 3;
	int ArbolE2=rand() % 3;
	int ArbolE3=rand() % 3;
	
	int cercaX=Mx;
	int cercaY=520;
	int nivel=1;
	while(true)
	{
		cielo=0;
		DegradCielo=0;
		DegradSol=0;
		Tierra=0;
		
		al_get_keyboard_state(&estadoTeclado);
		if (al_key_down(&estadoTeclado, ALLEGRO_KEY_ESCAPE)) 
		{
			break;
		}
		
		while(DegradCielo<155)
		{
			al_draw_line(0,cielo,Mx,cielo,al_map_rgb(50+(cielo/3),50+(cielo/3),100+DegradCielo),3);
			DegradCielo++;
			cielo+=3;
		}
		
		
		while(DegradSol<75)
		{
			al_draw_circle(Mx/2, 400, DegradSol*2, al_map_rgb(255-DegradSol,255-DegradSol,DegradSol*-2.5),3);
			DegradSol++;
		}
		
		while(Tierra<155)
		{
			al_draw_line(0,445+Tierra,Mx,445+Tierra,al_map_rgb(70,100+Tierra,100),1);
			Tierra++;
		}
		if(perder==false)
		{
			if(salta==false)
			{
				tiempoE++;
				if(tiempoE==15)
				{
					perroE++;
					if(perroE>2)
					{
						perroE=1;
					}
					tiempoE=0;
				}
				
				if(al_key_down(&estadoTeclado,ALLEGRO_KEY_RIGHT) && perroX<Mx-100 )
				{
					//al_clear_to_color(al_map_rgb(0,0,0));
					perroX++;
				}
				if(al_key_down(&estadoTeclado,ALLEGRO_KEY_LEFT) && perroX>0)
				{
					//al_clear_to_color(al_map_rgb(0,0,0));
					perroX--;
				}
				if(al_key_down(&estadoTeclado,ALLEGRO_KEY_SPACE))
				{
					//al_clear_to_color(al_map_rgb(0,0,0));
					perroE=3;
					arriba=true;
					salta=true;
				}
			}
			else
			{
				if(arriba==true)
				{
					perroY-=1;
					if(perroY<=420)
					{
						arriba=false;
					}
				}
				else
				{
					perroY+=1;
					if(perroY==500)
					{
						salta=false;
						perroE=0;
					}
				}
			}
			
			al_draw_bitmap(arbol[ArbolE1],arbolX1,400,0);
			arbolX1-=nivel;
			if(arbolX1<=-60)
			{
				arbolX1=Mx;
				ArbolE1=rand() % 3;
			}
			
			al_draw_bitmap(arbol[ArbolE2],arbolX2,400,0);
			arbolX2-=nivel;
			if(arbolX2<=-60)
			{
				arbolX2=Mx+rand() % 500;
				ArbolE2=rand() % 3;
			}

			al_draw_bitmap(arbol[ArbolE3],arbolX3,400,0);
			arbolX3-=nivel;
			if(arbolX3<=-60)
			{
				arbolX3=Mx+rand() % 500;
				ArbolE3=rand() % 3;
			}
			
			al_draw_bitmap(cerca,cercaX,cercaY,0);
			cercaX-=nivel;
			if(cercaX<=-60)
			{
				cercaX=Mx;
				nivel+=1;
			}
			
			al_draw_bitmap(perro[perroE],perroX,perroY,0);
			
	//		if( (perroX)>cercaX && (perroX+100)<cercaX && cercaY-20==perroY)
	//		{
	//			printf("Pierdes");
	//		}
			
			if( ((perroX+30)<cercaX && (perroX+60)>cercaX) && perroY+20<=cercaY && perroY+30>=cercaY )
			{
				perder=true;
			}
		}
		else
		{
			al_draw_bitmap(Perder,(Mx/2)-150,My/2,0);
			if(al_key_down(&estadoTeclado,ALLEGRO_KEY_ENTER) )
			{
				perroX = 0;
				perroY = 500;
				perroE = 0;
				tiempoE = 0;
				salta=false;
				arriba=false;
				cercaX=Mx;
				cercaY=520;
				nivel=1;
				perder=false;
			}
		}
		//printf("Perro: x=%d y=%d\nCerca: x=%d y=%d\n",perroX,perroY,cercaX,cercaY);
		al_flip_display();
		al_rest(0.001);
	}
	al_destroy_display(ventana);
	return 0;
} 
