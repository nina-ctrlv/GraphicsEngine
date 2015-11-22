#include <allegro5/allegro.h> 
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Matrix.hpp"

#include "Display.hpp"

namespace
{
    std::vector<Matrix> points;
    Matrix p1(-50, -50, 50);
    Matrix p2(-50, 50, 50);
    Matrix p3(50, 50, 50);
    Matrix p4(50, -50, 50);
    Matrix p5(50, -50, -50);
    Matrix p6(50, 50, -50);
    Matrix p7(-50, 50, -50);
    Matrix p8(-50, -50, -50);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    points.push_back(p7);
    points.push_back(p8);

    std::vector<Matrix> screenPoints = points;

    Matrix camera(0, 0, 200);

    Matrix orthogonal(4, 4);
    Matrix scale(4, 4);
    Matrix convert2D(4, 4);

	int FPS = 60;
	int width = 640;
	int height = 480;
    double n = 100;
    double f = -200;
    double r = width/8;
    double l = -width/8;
    double t = height/8;
    double b = -height/8;

	enum MYKEYS {
	KEY_ESC, KEY_W, KEY_A, KEY_S, KEY_D
	};

	bool key[5] = {false, false, false, false, false};
}


Display::Display()
	: eventQueue{NULL}, timer{NULL}, display{NULL}
{
    updateScreenPoints();
	al_init();
	al_init_primitives_addon();
	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(width, height);
	
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_install_keyboard();

	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
}

Display::~Display()
{
	al_destroy_event_queue(eventQueue);
	al_destroy_timer(timer);
	al_destroy_display(display);
}

void Display::run()
{
	al_flip_display();
	al_start_timer(timer);

	while (!key[KEY_ESC])
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

		bool redraw = false;

		if (ev.type == ALLEGRO_EVENT_TIMER)
			redraw = false;
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				key[KEY_ESC] = true;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_W)
				key[KEY_W] = true;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_A)
				key[KEY_A] = true;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_S)
				key[KEY_S] = true;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_D)
				key[KEY_D] = true;
			
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				key[KEY_ESC] = false;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_W)
				key[KEY_W] = false;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_A)
				key[KEY_A] = false;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_S)
				key[KEY_S] = false;
			if (ev.keyboard.keycode ==  ALLEGRO_KEY_D)
				key[KEY_D] = false;

			redraw = true;
		}
    

        al_clear_to_color(al_map_rgb(255, 255, 255));
	    al_flip_display();

        drawObjects();

		if (redraw)
		{
			al_clear_to_color(al_map_rgb(255, 255, 255));
			if(key[KEY_W])
				al_draw_line(0, 0, 640, 480, al_map_rgb(0, 0, 0), 1.0);
			if(key[KEY_A])
				al_draw_line(0, 480, 640, 0, al_map_rgb(0, 0, 0), 1.0);
			if(key[KEY_S])
				al_draw_line(0, 240, 640, 240, al_map_rgb(0, 0, 0), 1.0);
			if(key[KEY_D])
				al_draw_line(320, 0, 320, 480, al_map_rgb(0, 0, 0), 1.0);
			al_flip_display();
		}

	}
}

void Display::drawObjects() {
       
}

void Display::updateScreenPoints() {
    for(int i = 0; i < screenPoints.size(); i++) {
        screenPoints.at(i) = worldToScreen(points.at(i));
    }
}

void Display::worldToScreen(Matrix point) {
    
}