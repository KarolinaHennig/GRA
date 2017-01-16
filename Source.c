#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5\mouse.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
#include <string>



using namespace std;


int main()
{
	int dlugosc_gry = 0;
	int timer2 = 0;
	int ranking_czas[5];
	string nazwa_gracza;
	string nazwa1, nazwa2, nazwa3, nazwa4, nazwa5;
	fstream plik;
	plik.open("ranking.txt", ios::in | ios::out | ios::binary);
	if (plik.good() == true)
	{
		for (int i = 0; i < 5; i++)
		{
			plik >> ranking_czas[i];
		}
	}

	fstream plik2;
	plik2.open("ranking_nazwa.txt", ios::in | ios::out );
	if (plik2.good() == true)
	{
		plik2 >> nazwa1 >> nazwa2 >> nazwa3 >> nazwa4 >> nazwa5;
	}

	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_ttf_addon();
	int pos_gracz_x = 295;
	int pos_gracz_y = 400;
	int pos_x, pos_y;
	int ruch_droga = -450;
	int pos_x_przec;
	int pos_y_przec;
	int pos_pas = -450;
	int pos_x_czesci;
	int pos_y_czesci;
	int FPS = 60;
	int pomocznicza[11];
	bool done = false;
	bool z_gra = false;
	bool z_ranking = false;
	bool z_instrukcja = false;
	bool done2 = false;
	bool menu = false;
	bool wpis_nazwy = false;
	bool wpis_do_rankingu = false;
	int ruch = false;
	int ruch2 = false;
	int hp = 5;
	int poz_rank;
	int p;




	ALLEGRO_DISPLAY * okno = al_create_display(800, 550);
	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	ALLEGRO_TIMER * timer = NULL;
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
	ALLEGRO_BITMAP * droga_czesc1 = al_load_bitmap("droga_czesc1.png");
	ALLEGRO_BITMAP * droga_czesc2 = al_load_bitmap("droga_czesc2.png");
	ALLEGRO_BITMAP * droga_czesc3 = al_load_bitmap("droga_czesc3.png");
	ALLEGRO_BITMAP * droga_czesc4 = al_load_bitmap("droga_czesc4.png");
	ALLEGRO_BITMAP * tlo_nazwa_gracza = al_load_bitmap("nazwa_gracza.jpg");
	ALLEGRO_BITMAP * przeciwnik = al_load_bitmap("przeciwnik.png");
	ALLEGRO_BITMAP * czesc1 = al_load_bitmap("czesc1.png");
	ALLEGRO_BITMAP * czesc2 = al_load_bitmap("czesc2.png");
	ALLEGRO_BITMAP * element = al_load_bitmap("czesc1.png");
	ALLEGRO_FONT   *czcionka = al_load_ttf_font("ARIALNB.ttf", 16, 0);
	ALLEGRO_FONT   *czcionka24 = al_load_ttf_font("ARIALNB.ttf", 24, 0);






	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));


poczatek:

	if(wpis_do_rankingu)
	{
		p = 0;
		for (int i = 0; i<5; i++)
		{
			pomocznicza[i + 1] = ranking_czas[i];
		}
		while (dlugosc_gry < ranking_czas[p])
		{
			p++;
		}
		if(p==4)
		{
			nazwa5 = nazwa_gracza;
		}
        if(p==3)
		{
			nazwa5 = nazwa4;
			nazwa4 = nazwa_gracza;
		}
		if(p==2)
		{
			nazwa5 = nazwa4;
			nazwa4 = nazwa3;
			nazwa3 = nazwa_gracza;
		}
		if(p==1)
		{
			nazwa5 = nazwa4;
			nazwa4 = nazwa3;
			nazwa3 = nazwa2;
			nazwa2 = nazwa_gracza;
		}
		if (p == 0)
		{
			nazwa5 = nazwa4;
			nazwa4 = nazwa3;
			nazwa3 = nazwa2;
			nazwa2 = nazwa1;
			nazwa1 = nazwa_gracza;
		}
		ranking_czas[p] = dlugosc_gry;
		for (p = p + 1; p<5; p++)
		{
			ranking_czas[p] = pomocznicza[p];
		}
		wpis_do_rankingu = false;
	}


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
					wpis_nazwy = true;
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

	if (wpis_nazwy)
	{
		nazwa_gracza.clear();
		bool done_wpis = false;
		while (!done_wpis)
		{


			ALLEGRO_EVENT ev3;
			al_wait_for_event(event_queue, &ev3);


			if (ev3.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev3.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done_wpis = true;
					break;
				case ALLEGRO_KEY_Q:
					nazwa_gracza = nazwa_gracza+"q";
					break;
				case ALLEGRO_KEY_W:
					nazwa_gracza = nazwa_gracza+"w";
					break;
				case ALLEGRO_KEY_E:
					nazwa_gracza = nazwa_gracza + "e";
					break;
				case ALLEGRO_KEY_R:
					nazwa_gracza = nazwa_gracza + "r";
					break;
				case ALLEGRO_KEY_T:
					nazwa_gracza = nazwa_gracza + "t";
					break;
				case ALLEGRO_KEY_Y:
					nazwa_gracza = nazwa_gracza + "y";
					break;
				case ALLEGRO_KEY_U:
					nazwa_gracza = nazwa_gracza + "u";
					break;
				case ALLEGRO_KEY_I:
					nazwa_gracza = nazwa_gracza + "i";
					break;
				case ALLEGRO_KEY_O:
					nazwa_gracza = nazwa_gracza + "o";
					break;
				case ALLEGRO_KEY_P:
					nazwa_gracza = nazwa_gracza + "p";
					break;
				case ALLEGRO_KEY_A:
					nazwa_gracza = nazwa_gracza + "a";
					break;
				case ALLEGRO_KEY_S:
					nazwa_gracza = nazwa_gracza + "s";
					break;
				case ALLEGRO_KEY_D:
					nazwa_gracza = nazwa_gracza + "d";
					break;
				case ALLEGRO_KEY_F:
					nazwa_gracza = nazwa_gracza + "f";
					break;
				case ALLEGRO_KEY_G:
					nazwa_gracza = nazwa_gracza + "g";
					break;
				case ALLEGRO_KEY_H:
					nazwa_gracza = nazwa_gracza + "h";
					break;
				case ALLEGRO_KEY_J:
					nazwa_gracza = nazwa_gracza + "j";
					break;
				case ALLEGRO_KEY_K:
					nazwa_gracza = nazwa_gracza + "k";
					break;
				case ALLEGRO_KEY_L:
					nazwa_gracza = nazwa_gracza + "l";
					break;
				case ALLEGRO_KEY_Z:
					nazwa_gracza = nazwa_gracza + "z";
					break;
				case ALLEGRO_KEY_X:
					nazwa_gracza = nazwa_gracza + "x";
					break;
				case ALLEGRO_KEY_C:
					nazwa_gracza = nazwa_gracza + "c";
					break;
				case ALLEGRO_KEY_V:
					nazwa_gracza = nazwa_gracza + "v";
					break;
				case ALLEGRO_KEY_B:
					nazwa_gracza = nazwa_gracza + "b";
					break;
				case ALLEGRO_KEY_N:
					nazwa_gracza = nazwa_gracza + "n";
					break;
				case ALLEGRO_KEY_M:
					nazwa_gracza = nazwa_gracza + "m";
					break;
				case ALLEGRO_KEY_ENTER:
					done_wpis = true;
					z_gra = true;
					break;
				}

			}
			al_draw_bitmap(tlo_nazwa_gracza, 0, 0, 0);
			al_draw_textf(czcionka, al_map_rgb(213, 0, 0), 310, 210, 0, nazwa_gracza.c_str());
			al_flip_display();
		}
		done_wpis = false;
		wpis_nazwy = false;
	}

	if (z_gra)
	{
		int powtarzanie_ruchu = 0;
		done = false;
		bool kolizja = false;
		z_gra = false;
		int i = 1;
		int losowanie;
		int rand1, rand2;
		pos_y_przec = 0;
		pos_x_przec = (160 + ((rand() % 4) * 150));
		pos_y_czesci = 20;
		pos_x_czesci = (150 + ((rand() % 4) * 150));
		double czas;
		double czas2;
		hp = 100;
		double roznica;
		al_start_timer(timer);
		time_t timer1;
		while (!done2)
		{

			timer1 = (clock() / CLOCKS_PER_SEC);
			dlugosc_gry = (timer1 - timer2);
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);


			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done2 = true;
					timer2 = timer1;
					break;

				case ALLEGRO_KEY_LEFT:
					if (pos_gracz_x > 150)
					{
						pos_gracz_x -= 150;
					}
					break;
				case ALLEGRO_KEY_RIGHT:
					if (pos_gracz_x < 550)
					{
						pos_gracz_x += 150;
					}
					break;

				}
			}

			if (powtarzanie_ruchu < 98)
			{
				ruch_droga = ruch_droga + 5;
				pos_pas = pos_pas + 5;
				powtarzanie_ruchu++;
			}
			else
			{
				ruch_droga = -450;
				pos_pas = -450;
				powtarzanie_ruchu = 0;
			}


			if (pos_y_przec < 350)
			{
				pos_y_przec = pos_y_przec + 8;
			}
			else if ((pos_y_przec = 340) && (pos_x_przec >= pos_gracz_x - 30) && (pos_x_przec <= pos_gracz_x + 30))
			{
				hp = (hp - 25);
				goto ruch;

			}
			else {
			ruch:
				rand2 = (rand() % 4);
				pos_x_przec = (160 + (rand2 * 150));
				pos_y_przec = -20;
			}



			if (pos_y_czesci < 550)
			{

				pos_y_czesci = pos_y_czesci + 5;
			}
			else if (((pos_y_czesci = 360) && (pos_x_czesci >= pos_gracz_x - 30) && (pos_x_czesci <= pos_gracz_x + 30)))
			{
				if (hp + 15 <= 100) { hp = hp + 15; goto ruch2; }
				if ((hp < 100) && (hp + 15>100)) { hp = 100; goto ruch2; }
				else goto ruch2;
			}


			else {
			ruch2:
			jeszcze_raz:
				rand1 = (rand() % 4);
				pos_x_czesci = (150 + (rand1 * 150));
				if (rand1 == rand2) { goto jeszcze_raz; }
				pos_y_czesci = -20;
				losowanie = (rand() % 2);
				if (losowanie == 1)
				{
					element = al_load_bitmap("czesc2.png");
				}
				else { element = al_load_bitmap("czesc1.png"); }
			}


			if (hp <= 0)
			{
				done2 = true;
				timer2 = timer1;
				wpis_do_rankingu = true;
			}



			al_draw_bitmap(droga_czesc1, 0, 0, 0);
			al_draw_bitmap(droga_czesc2, 0, ruch_droga, 0);
			al_draw_bitmap(droga_czesc3, 0, 0, 0);
			al_draw_bitmap(droga_czesc4, 0, pos_pas, 0);
			al_draw_bitmap(przeciwnik, pos_x_przec, pos_y_przec, 0);
			al_draw_bitmap(element, pos_x_czesci, pos_y_czesci, 0);
			al_draw_bitmap(gracz, pos_gracz_x, pos_gracz_y, 0);
			al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 0, 0, 0, "SPRAWNOSC:");
			al_draw_textf(czcionka24, al_map_rgb(0, 255, 0), 20, 15, 0, "%d%s", hp, "%");
			al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 0, 50, 100, "CZAS GRY:");
			al_draw_textf(czcionka24, al_map_rgb(0, 255, 0), 35, 70, 100, "%d", dlugosc_gry);
			al_flip_display();

		}



		done2 = false;

		goto poczatek;
	}

	if (z_ranking)
	{

		done = false;
		z_ranking = false;
		poz_rank = 250;
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

			for (int i = 0; i <5; i++)
			{
				al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 300, 250+(i*20), 0, "%d", ranking_czas[i]);
			}
			al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 450, 250, 0, nazwa1.c_str());
			al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 450, 270, 0, nazwa2.c_str());
			al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 450, 290, 0, nazwa3.c_str());
			al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 450, 310, 0, nazwa4.c_str());
			al_draw_textf(czcionka, al_map_rgb(0, 255, 0), 450, 330, 0, nazwa5.c_str());



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

	plik << ranking_czas[0] << " " << ranking_czas[1] << " " << ranking_czas[2] << " " << ranking_czas[3] << " " << ranking_czas[4];
	plik.close();
	plik2 << nazwa1 << endl << nazwa2 << endl << nazwa3 << endl << nazwa4 << endl << nazwa5;
	plik2.close();
	al_destroy_bitmap(kursor);
	al_destroy_bitmap(start);
	al_destroy_bitmap(ranking);
	al_destroy_bitmap(wyjscie);
	al_destroy_bitmap(tlo);
	al_destroy_display(okno);

	return 0;
}
