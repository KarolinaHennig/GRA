#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5\mouse.h>
#include <allegro5/allegro_font.h>
#include "allegro5\keyboard.h"


int main()
{
	al_init();
	al_init_image_addon();
	al_install_mouse();
	al_install_keyboard();
	int pos_gracz = 280;
	int pos_x, pos_y;
	bool done = false;
	bool z_gra = false;
	bool z_ranking = false;
	bool z_instrukcja = false;
	bool done2 = false;
	bool menu = false;


	ALLEGRO_DISPLAY * okno = al_create_display(800, 550);
	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	ALLEGRO_BITMAP * tlo = al_load_bitmap("start.jpg");
	ALLEGRO_BITMAP * start = al_load_bitmap("przycisk_start.jpg");
	ALLEGRO_BITMAP * ranking = al_load_bitmap("przycis_ranking.jpg");
	ALLEGRO_BITMAP * wyjscie = al_load_bitmap("przycisk_wyjscie.jpg");
	ALLEGRO_BITMAP * kursor = al_load_bitmap("kursor.png");
	ALLEGRO_BITMAP * gra = al_load_bitmap("droga.jpg");
	ALLEGRO_BITMAP * instrukcja = al_load_bitmap("przycisk_instrukcja.jpg");
	ALLEGRO_BITMAP * tlo_instrukcja = al_load_bitmap("instrukcja.jpg");
	ALLEGRO_BITMAP * tlo_ranking = al_load_bitmap("ranking.jpg");
	ALLEGRO_BITMAP * gracz = al_load_bitmap("auto.png");


	if (!al_init())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO INIT FAIL", NULL, NULL);
	if (!al_init_native_dialog_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO NATIVE DIALOG INIT FAIL", NULL, NULL);
	if (!al_init_image_addon())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO IMAGE INIT FAIL", NULL, NULL);
	if (!al_install_keyboard())
		al_show_native_message_box(NULL, NULL, NULL, "ALLEGRO KEYBOARD INIT FAIL", NULL, NULL);

	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());


poczatek:
	al_hide_mouse_cursor(okno);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				if ((pos_x > 273) && (pos_x < 518) && (pos_y > 426) && (pos_y < 515)) //PRZYCISK WYJSCIE
				{
					done = true;
				}

				else if ((pos_x > 273) && (pos_x < 518) && (pos_y > 50) && (pos_y < 131)) //PRZYCISK START
				{
					done = true;
					z_gra = true;
				}

				else if ((pos_x > 273) && (pos_x < 518) && (pos_y > 170) && (pos_y < 259)) //PRZYCISK RANKING
				{
					done = true;
					z_ranking = true;
				}
				else if ((pos_x > 273) && (pos_x < 518) && (pos_y > 298) && (pos_y < 387)) //PRZYCISK RANKING
				{
					done = true;
					z_instrukcja = true;
				}
			}
		}

		al_draw_bitmap(tlo, 0, 0, 0);
		al_draw_bitmap(start, 273, 50, 0);
		al_draw_bitmap(ranking, 273, 170, 0);
		al_draw_bitmap(wyjscie, 273, 426, 0);
		al_draw_bitmap(instrukcja, 273, 298, 0);
		al_draw_bitmap(kursor, pos_x, pos_y, 0);
		al_flip_display();
	}
	if (z_gra)
	{
		done = false;
		z_gra = false;

		while (!done2)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done2 = true;
					break;
				}
			}
			al_draw_bitmap(gra, 0, 0, 0);
			al_draw_bitmap(gracz, pos_gracz, 400, 0);
			al_flip_display();
		}
		done2 = false;
		goto poczatek;
	}

	if (z_ranking)
	{

		done = false;
		z_ranking = false;
		while (!done2)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done2 = true;
					break;
				}
			}
			al_draw_bitmap(tlo_ranking, 0, 0, 0);
			al_flip_display();
		}
		done2 = false;
		goto poczatek;
	}
	if (z_instrukcja)
	{
		done = false;
		z_instrukcja = false;
		while (!done2)
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done2 = true;
					break;
				}
			}
			al_draw_bitmap(tlo_instrukcja, 0, 0, 0);
			al_flip_display();
		}
		done2 = false;
		goto poczatek;
	}


	al_destroy_bitmap(kursor);
	al_destroy_bitmap(start);
	al_destroy_bitmap(ranking);
	al_destroy_bitmap(wyjscie);
	al_destroy_bitmap(tlo);
	al_destroy_display(okno);
	return 0;
}
