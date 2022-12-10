/*
 *
 PUBLIC DOMAIN 2022
 THIS CODE IS A HACKY MESS - READ IT AT YOUR OWN RISK!
 *
 */



#ifdef __ANDROID__
// ANDROID uses CPP not C
extern "C" {
#endif


#define INST_AMICO_TEXTURES
#include "amico.h"
// #define printf //
// 12 rows X 20 cells = 240
// 240 / 8bits = 30bytes
// 10 10
// 9 2 9
// 8 4 8





// update time
void intern_update_time(void)
{
	u8 c  = g_game_counter>>6; // abit slower then normal minute, but better then too fast!
	u8 t = g_gamestate.time;

	c = c & 1;
	t = t & 1;

	//printf("c %d t %d test %d \n", c , t , c != t );

	if(c  != t ) // test for change
		g_gamestate.time++;


}



void intern_black_and_white_BG(u32 side)
{

	if(side)
	{
		amico_rectangle( 255, 255, 255,  160, 0, 320,240 );
		amico_rectangle(0, 0, 0,    0, 0, 160,240 );
	}
	else
	{

		amico_rectangle( 255, 255, 255,   0, 0, 160,240 );
		amico_rectangle(0, 0, 0,   160, 0, 320,240 );
	}
}

void intern_do_flashing_heads(u32 side, u32 i, u32 skipBG)
{

	// flashing characters

	//amico_rectangle( 20, 20, 20,   160, 0, 320, 218 );




	LOG_FLASHING_HEADS("intern_do_flashing_heads side %d i %d skipBG %d\n", side, i, skipBG);

	if(!(side&1) ) // SHILLS
	{

		if(!skipBG)
		{
			// flash BG colours
			if(g_game_counter&4)
				amico_rectangle(115, 115, 255, 0, 0, 320, 240);
			else
				amico_rectangle(113, 255, 255, 0, 0, 320, 240);
		}
		/*
			switch(g_texture_map_shills[i].TPAGE)
			{
			case 1:
				screen.sprites = TPAGE01;
				break;
			case 2:
				screen.sprites = TPAGE02;
				break;
			case 3:
				screen.sprites = TPAGE03;
				break;
			case 4:
				screen.sprites = TPAGE04;
				break;
			}
		 */



		// screen.sprite(Rect(g_texture_map_shills[i].textU, g_texture_map_shills[i].textV, 4, 4), Point(15, 20) ,  Point(7, 7), ( (g_game_counter>>1)%100)/2.0f, SpriteTransform::HORIZONTAL);
		amico_sprite(g_texture_map_shills[i].TPAGE,   g_texture_map_shills[i].textU, g_texture_map_shills[i].textV,  32, 32,    160, 120,    ( (g_game_counter)&0x3F)*10, 1);

		// amico_rectangle(113, 255, 255,  0, 230,  320,240);
		amico_rectangle(115, 115, 255,    0, 0,  320, 20);

		// good shell
		//screen.sprites = TPAGE01;
		//screen.sprite(Rect(g_texture_map_shills[0].textU, g_texture_map_shills[0].textV, 4, 4), Point(224, 142) ,  Point(0, 0), 3.0f, SpriteTransform::HORIZONTAL);
		// amico_sprite(01,   g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,  32, 32,    224, 142,    300, 1, 0);
		// amico_sprite(  g_texture_map_shills[0].TPAGE,   g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,  32, 32,     320-32, 32+0,     200, 1, 0);
		amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,  32, 32,     320-32, 32+0,     200, 1);

		if(skipBG)
			amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,  32, 32,     32, 32+0,     200, 1);

		// amico_text_top1_line( (char *) g_texture_map_shills[i].name );
		if(skipBG) //move it
			render_text(68, 10, 100, (char *) g_texture_map_shills[i].name );
		else
			render_text(12, 10, 100, (char *) g_texture_map_shills[i].name );
		// screen.pen = Pen(255, 255, 255);
		// screen.text((char *)(g_texture_map_shills[i].name), minimal_font,  Point(4, 4 ) ,  false, TextAlign::left);

	}
	else
	{  /// HATERS

		// flash BG colours
		if(!skipBG)
		{
			if(g_game_counter&4)
				amico_rectangle(10, 10, 10, 0, 0, 320, 240);
			else
				amico_rectangle(186, 161, 127, 0, 0, 320, 240);
		}
		/*
					switch(g_texture_map_haters[i].TPAGE)
					{
					case 1:
						screen.sprites = TPAGE01;
						break;
					case 2:
						screen.sprites = TPAGE02;
						break;
					case 3:
						screen.sprites = TPAGE03;
						break;
					case 4:
						screen.sprites = TPAGE04;
						break;
					}
		 */

		// screen.sprite(Rect(g_texture_map_haters[i].textU, g_texture_map_haters[i].textV, 4, 4), Point(10, 20) ,  Point(7, 7), ( (g_game_counter>>1)%32)/2.0f, SpriteTransform::HORIZONTAL);
		amico_sprite(g_texture_map_haters[i].TPAGE,   g_texture_map_haters[i].textU, g_texture_map_haters[i].textV,  32, 32,     160, 120,    ( (g_game_counter)&0x3F)*10, 1);

		//screen.text((char *)(g_texture_map_haters[i].name), minimal_font,  Point(10, 10 ));//,  false, TextAlign::center_center);
		//	screen.pen = Pen(186, 161, 127);
		//	screen.text((char *)(g_texture_map_haters[i].name), outline_font,  Point(150, 10 ) ,  false, TextAlign::center_center);

		//screen.pen = Pen(0, 0, 0);
		// amico_rectangle(186, 161, 127, 0, 230, 320,240);
		amico_rectangle(0, 0, 0, 0, 0, 320, 20);
		//	screen.sprites = TPAGE03;
		//	screen.sprite(Rect(g_texture_map_haters[0].textU, g_texture_map_haters[0].textV, 4, 4), Point(225, 142) ,  Point(0, 0), 3.0f, SpriteTransform::HORIZONTAL);

		//bad shell
		//amico_sprite( g_texture_map_haters[0].TPAGE,   g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32,     320-32, 32+0,     200, 1, 0);
		//amico_sprite( g_texture_map_shills[0].TPAGE,   g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,  32, 32,     320-32, 32+0,     200, 1, 0);
		// amico_sprite(g_texture_map_haters[0].TPAGE,   g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32,    320-32, 32+0,     200 , 1, 0);

		amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,   32, 32,    320-32, 32+0,     200 , 1);

		if(skipBG)
			amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,   32, 32,    32, 32+0,     200 , 1);


		// amico_text_top1_line( (char *) g_texture_map_haters[i].name );
		if(skipBG) //move it
			render_text(68, 10, 100, (char *) g_texture_map_haters[i].name );
		else
			render_text(12, 10, 100, (char *) g_texture_map_haters[i].name );
		//screen.pen = Pen(0, 0, 0);
		//screen.text((char *)(g_texture_map_haters[i].name), minimal_font,  Point(4, 4 ) ,  false, TextAlign::left);

	}





	amico_rectangle( 0, 0, 0,   0, 210,  320, 30 );
	LOG_FLASHING_HEADS("intern_do_flashing_heads ((g_game_counter>>INTRO_SCROLL_TEXT_SPEED) ) %d \n ", ((g_game_counter>>INTRO_SCROLL_TEXT_SPEED) )); //

	//		render_text( 0 , 215, 100, g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+( cnt - 22 ) );
	{
		// char str[40];
		u32 start =  120+( ( (g_text_scroll_counter++)>>INTRO_SCROLL_TEXT_SPEED)  );

		LOG_FLASHING_HEADS("intern_do_flashing_heads start =  = %d strlen %d \n", start, strlen( (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN)); //

		if(start>strlen( (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN))
		{
			LOG_FLASHING_HEADS("intern_do_flashing_heads  if(start>strlen( (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN)) g_game_counter %d start %d  %d \n ",(g_game_counter>>INTRO_SCROLL_TEXT_SPEED), start, ((g_game_counter>>INTRO_SCROLL_TEXT_SPEED) -22)); //


			g_function_loop = update_level_zero; //update_splash;
			g_player.shoot_dpad =0;
			g_gamestate.cheat_big_heads =1;
			g_player.shoot_timer=BUTTON_PRESS_TIME*2;
			g_text_scroll_counter = 0;
			g_game_counter = 0;
			g_player.TPAGE = 1;	 g_player.textU = g_player.textV = 0; 	// Force to TT for attack mode for levelzero
			amico_stop_all_SFX();
			amico_BGM_quiet_time(0);
			//amico_play_BGM_audio(3);//intro
			MACRO_CLEAR_SCREEN

#ifdef BETA_DEMO
			g_gamestate.cheat_testing = 1; // start game demo instead of loop
#endif


		}

		// start = start % strlen(g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN);
		// sprintf(str,"%0.*s", 39, g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN + start);



		LOG_FLASHING_HEADS("intern_do_flashing_heads g_game_counter %s \n ",(char *)g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+start);
		// render_text(0, 215, 100, g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN + len);

		//if it crashes here (not a capital letter/number, it hasn't been decripted in update_splash(void)!
		render_text(0, 215, 100, (char *)g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+start);

	}

} // intern_do_flashing_heads(u32 i)




void intern_do_C64_loading_screen(void)
{
	u32 i;

	// C64 loading bards
	for(i=0; i<24; i++)
	{

		char R, G, B;


		switch( rand()%16)
		{


		// white    0xff    0xff    0xff    2
		case 1:
			R = 0xff;
			G = 0xff;
			B = 0xff;
			break;

			// red    0x88    0x00    0x00    3
		case 2:
			R = 0x88;
			G = 0x0;
			B = 0x0;
			break;

			// cyan    0xaa    0xff    0xee    4
		case 3:
			R = 0xaa;
			G = 0xff;
			B = 0xee;
			break;

			// purple    0xcc    0x44    0xcc    5
		case 4:
			R = 0xcc;
			G = 0x44;
			B = 0xcc;
			break;

			// green    0x00    0xcc    0x55    6
		case 5:
			R = 0;
			G = 0xcc;
			B = 0x55;
			break;

			// blue    0x00    0x00    0xaa    7
		case 6:
			R = 0;
			G = 0;
			B = 0xaa;
			break;

			// yellow    0xee    0xee    0x77    8
		case 7:
			R = 0xee;
			G = 0xee;
			B = 0x77;
			break;

			// orange    0xdd    0x88    0x55    9
		case 8:
			R = 0xdd;
			G = 0x88;
			B = 0x55;
			break;

			// brown    0x66    0x44    0x00    10
		case 9:
			R = 0x66;
			G = 0x44;
			B = 0;
			break;

			// l,red    0xff    0x77    0x77    11
		case 10:
			R = 0xff;
			G = 0x77;
			B = 0x77;
			break;

			// d,gray    0x33    0x33    0x33    12
		case 11:
			R = 0x33;
			G = 0x33;
			B = 0x33;
			break;

			// gray    0x77    0x77    0x77    13
		case 12:
			R = 0x77;
			G = 0x77;
			B = 0x77;
			break;
			// lgreen    0xaa    0xff    0x66    14
		case 13:
			R = 0xaa;
			G = 0xff;
			B = 0x66;
			break;

			// l,blue    0x00    0x88    0xff    15
		case 14:
			R = 0;
			G = 0x88;
			B = 0x88;
			break;

			// l,gray    0xbb    0xbb    0xbb    16
		case 15:
			R = 0xbb;
			G = 0xbb;
			B = 0xbb;
			break;


			// black    0x00    0x00    0x00    1
		default:
			R = 0x0;
			G = 0x0;
			B = 0x0;
			break;
		}

		amico_rectangle(R, G, B, 0, i*10, 320, 10);

	}

}

// poor man's percent - not in critical loop!
//intern_calc_percent(g_gamestate.level_bullets_hit,  g_gamestate.level_bullets_used );
//ie g_total_bullets_hit  / g_total_bullets_used
#define LOG_PERC //  printf

u32 intern_calc_percent(s32 numerator , s32 denominator)
{
	u32 ret =0;
	LOG_PERC( "intern_calc_percent %d / %d \n", numerator ,  denominator );



	if(numerator == 0 )
		return 0;

	if(denominator == 0 )
		return 0;


	if(denominator == numerator )
		return 100;

	if(denominator == 1 )
		return numerator;


	numerator*=100;

	do
	{
		numerator -=denominator;
		ret++;
		LOG_PERC( "DIV %d ret %d \n", numerator ,  ret );
	}while(numerator>0);

	if(numerator < -50)
		ret--;

	return ret;

}

// from: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
s32 intern_rand_comparison(void *a, void *b)
{
	// (void)a; (void)b;
	u32 test;

#if 0 //def _DEBUG_

	LOG_RAND("\n intern_rand_comparison  a %p \n",a);
	LOG_RAND("\n intern_rand_comparison  b %p \n",b);

	if(!a)
	{
		LOG_RAND("\n intern_rand_comparison  a NULL %p \n",a);
		return 0;
	}
	if(!b)
	{
		LOG_RAND("\n intern_rand_comparison  b NULL %p \n",b);
		return 0;
	}

#endif



#ifdef __NOT_USED__
	test = rand();

#else
	test = rand();
#endif
	test += g_stereo_counter_random;

	LOG_RAND("\n intern_rand_comparison  test %d \n",test);
	test = (test & 1); //rand() % 2
	// LOG_RAND("\n intern_rand_comparison  test %d \n",test);
	return test ? +1 : -1;
}






void swap (char *a, char *b, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++, a++, b++)
	{
		char t;

		t = *a;
		*a = *b;
		*b = t;
	}
}

void _qsort (void *basearg, size_t count, size_t size,
		s32 (*compar) ( void *,  void *) )
{
	char *base = (char *) basearg;
	size_t i;
	size_t mid;

	tail_recurse:
	if (count < 2)
		return;

	/* The symbol table and DWARF tables, which is all we use this
     routine for, tend to be roughly sorted.  Pick the middle element
     in the array as our pivot point, so that we are more likely to
     cut the array in half for each recursion step.  */
	swap (base, base + (count>>1) * size, size);

	mid = 0;
	for (i = 1; i < count; i++)
	{
		if ((*compar) (base, base + i * size) > 0)
		{
			++mid;
			if (i != mid)
				swap (base + mid * size, base + i * size, size);
		}
	}

	if (mid > 0)
		swap (base, base + mid * size, size);

	/* Recurse with the smaller array, loop with the larger one.  That
     ensures that our maximum stack depth is log count.  */
	if (2 * mid < count)
	{
		_qsort (base, mid, size, compar);
		base += (mid + 1) * size;
		count -= mid + 1;
		goto tail_recurse;
	}
	else
	{
		_qsort (base + (mid + 1) * size, count - (mid + 1),
				size, compar);
		count = mid;
		goto tail_recurse;
	}
}


void intern_randomize_init_lists(void)
{
	u32 i;
	u32 t;

	// return;
	LOG_RAND2("\n randomizeHaters  1 update_credit g_gamestate.wave = 0x%x \n", g_gamestate.wave);
	// amico_text_top2_line("\n randomizeHaters  1 update_credit");

	// first run!
	if(g_gamestate.wave == 0xAA) // stupid, but it's not used until select
	{

#if 1
		i = 0;


		t = g_game_counter;
		t +=  rand();
		//t = t >>1; // div 2
		//if( t & 1 )
		//	t--; // seed with even number only?
		// t = 0;


		LOG_RAND2("\n 1 srand(%d);  \n", t);

		LOG_RAND2("\n 0 (%d);  g_game_counter \n", t);
		// t = t >> (g_game_counter % 2);


		if( t & 1 ) //   flip floppers
		{
			t_data_head32 temp = g_texture_map_shills[i];
			g_texture_map_shills[i] = g_texture_map_haters[i];
			g_texture_map_haters[i] = temp;
			LOG_RAND2("0 hater swapped %s  \n ", g_texture_map_haters[i].name);
		}
		else
		{
			LOG_RAND2("0 hater NOT swapped %s  \n ", g_texture_map_haters[i].name);
		}

		i++; //1


		t -=  rand();


		LOG_RAND2("\n 1 (%d);   \n", t);
		//	t = t >> (g_game_counter % 2);
		if( t & 1 ) // flip 2nd last slots - flip floppers
		{
			t_data_head32 temp = g_texture_map_shills[i];
			g_texture_map_shills[i] = g_texture_map_haters[i];
			g_texture_map_haters[i] = temp;
			LOG_RAND2("2nd last hater swapped %s \n ", g_texture_map_haters[i].name);
			//srand(t);
		}
		else
		{
			LOG_RAND2("2nd last hater NOT swapped %s \n ", g_texture_map_haters[i].name);
		}

		i++; //2

		t += rand();

		LOG_RAND2("\n t3 (%d); rand(); \n", t);

		//	t = t >> (g_game_counter % 2);
		if( t & 1 ) // flip 3rd last
		{
			t_data_head32 temp = g_texture_map_shills[i];
			g_texture_map_shills[i] = g_texture_map_haters[i];
			g_texture_map_haters[i] = temp;
			LOG_RAND2("3rd last hater swapped %s \n ", g_texture_map_haters[i].name);
		}
		else
		{
			LOG_RAND2("3rd last hater NOT swapped %s \n ", g_texture_map_haters[i].name);
		}

		i++;//3


		t -=  rand();


		LOG_RAND2("\n t4 (%d);   VSync(-1); \n", t);

		//	t = t >> (g_game_counter % 2);
		if( t & 1 ) // flip 4th last slots - flip floppers
		{
			t_data_head32 temp = g_texture_map_shills[i];
			g_texture_map_shills[i] = g_texture_map_haters[i];
			g_texture_map_haters[i] = temp;
			LOG_RAND2("4th last hater swapped %s \n ", g_texture_map_haters[i].name);
		}
		else
		{
			LOG_RAND2("4th last hater NOT swapped %s \n ", g_texture_map_haters[i].name);
		}


		i++;//4


		t +=  rand();


		LOG_RAND2("\n t5 (%d);    \n", t);

		//	t = t >> (g_game_counter % 2);
		if( t & 1 ) // flip 4th last slots - flip floppers
		{
			t_data_head32 temp = g_texture_map_shills[i];
			g_texture_map_shills[i] = g_texture_map_haters[i];
			g_texture_map_haters[i] = temp;
			LOG_RAND2("5th last hater swapped %s \n ", g_texture_map_haters[i].name);
		}
		else
		{
			LOG_RAND2("5th last hater NOT swapped %s \n ", g_texture_map_haters[i].name);
		}


		// shared slots,
		// extra hacky, would be better if it was dynamic, done every randomize, but CBF finding them or tracking them once shuffled





		g_gamestate.wave = 0; // clear flag
	} //first run

	LOG_RAND2("\n qsort \n");




	{
#define SHARED_SHILL_SLOT 33

		s8 c =  g_texture_map_shills[SHARED_SHILL_SLOT].name[5];

		LOG_RAND2("\n swap random %d %X \n", t,  c);

		if( c == 'J' )  // do nothing - JOHN HANCOCK  "JOHN HANCOCK" ,1,32,96}
		{
			g_texture_map_shills[SHARED_SHILL_SLOT].TPAGE = 1;
			g_texture_map_shills[SHARED_SHILL_SLOT].textU = 32;
			g_texture_map_shills[SHARED_SHILL_SLOT].textV = 96;
			sprintf((char *)g_texture_map_shills[SHARED_SHILL_SLOT].name, "JOHN HANCOCK"); //H


			LOG_RAND2("\n 33 shill shared slots - JOHN HANCOCK (%d); \n", c);
		}
		else if( c == 'R' ) //	replace  {  "JOHN HANCOCK" ,1,32,96},  with METALJUSUSROCKS
		{
			g_texture_map_shills[SHARED_SHILL_SLOT].TPAGE = 3;
			g_texture_map_shills[SHARED_SHILL_SLOT].textU = 0;
			g_texture_map_shills[SHARED_SHILL_SLOT].textV = 160;
			sprintf((char *)g_texture_map_shills[SHARED_SHILL_SLOT].name, "METALJUSUSROCKS"); //J

			LOG_RAND2("\n 33 shill shared slots -   METALJUSUSROCKS (%d); \n", c);

		}
		else  //	replace with {  "JOHN RIGGS" ,2,32,32}, //5
		{
			g_texture_map_shills[SHARED_SHILL_SLOT].TPAGE = 2;
			g_texture_map_shills[SHARED_SHILL_SLOT].textU = 32;
			g_texture_map_shills[SHARED_SHILL_SLOT].textV = 32;
			sprintf((char *)g_texture_map_shills[SHARED_SHILL_SLOT].name, "JOHN RIGGS"); //R

			LOG_RAND2("\n 33 shill shared slots -   JOHN RIGGS (%d); \n", c);

		}

#undef SHARED_SHILL_SLOT
	}


	//if statement to skip sorting or not
	IF_SKIPP_RANDOM
	{
		s32 cnt;
		cnt = (AMICO_NONE_BOSSES);// -1 to make bosses zero based
		//cnt--;//doxxers don't get sorted
		// cnt--;cnt--;
		//cnt--;
		LOG_RAND2("\n qsort cnt %d \n", cnt);

#if 1 


		// v is an array of elements to sort.
		// size is the number of elements in array
		// left and right is start and end of array
		//(*comp)(void*, void*) is a pointer to a function
		// which accepts two void* as its parameter
		// void _qsort(void* v, int size, int left, int right,         int (*comp)(void*, void*))
		_qsort(&(g_texture_map_shills[0]), cnt-1, sizeof(t_data_head32 ),  intern_rand_comparison); //


		LOG_RAND2("\n qsort  1 update_credit %d \n",cnt);

		_qsort( &(g_texture_map_haters[0]), cnt, sizeof(t_data_head32 ),  intern_rand_comparison);

		LOG_RAND2("\n qsort  2 update_credit %d \n",cnt);
#else
		qsort(&(g_texture_map_shills[0]), cnt, sizeof(t_data_head32 ), intern_rand_comparison);
		LOG_RAND2("\n qsort  1 qsort(&(g_texture_map_shills[0]), cnt, sizeof(t_data_head32 ), intern_rand_comparison); %d \n",cnt);

		qsort(&(g_texture_map_haters[0]), cnt, sizeof(t_data_head32 ), intern_rand_comparison);
		LOG_RAND2("\n qsort  2 qsort(&(g_texture_map_haters[0]), cnt, sizeof(t_data_head32 ), intern_rand_comparison); %d \n",cnt);
#endif
	}
#endif




	// reinit global vars after sorting
	{
		t_data_head32 *friends;
		t_data_head32 *enemies;



		if(g_gamestate.p_side) // 1 Haters
		{
			enemies = g_texture_map_shills;
			friends = g_texture_map_haters;
		}
		else // 0 shill
		{
			friends = g_texture_map_shills;
			enemies = g_texture_map_haters;
		}



		// init lists
		for(i=0; i<=MAX_SHILLS ; i++) // bosses at the end
		{
			//INSTANCE t_AI_youtubers g_AI_friends[MAX_SHILLS+1];
			//INSTANCE t_AI_youtubers g_AI_enemies[MAX_SHILLS+1];
			g_AI_friends[i].TPAGE = friends[i].TPAGE;
			g_AI_friends[i].textU = friends[i].textU;
			g_AI_friends[i].textV = friends[i].textV;
			g_AI_enemies[i].TPAGE = enemies[i].TPAGE;
			g_AI_enemies[i].textU = enemies[i].textU;
			g_AI_enemies[i].textV = enemies[i].textV;


			g_AI_friends[i].posX = 	g_AI_enemies[i].posX = 0;


		}

	}

}

void update_game_AI(void)
{
	u32 npc;


	npc = (u8) g_gamestate.wave;

	LOG_GAME_UPDATE("update_game_AI npc %d \n", npc);


	if(g_gamestate.enemy_next <  npc )
	{

		//	if(g_gamestate.enemy_next < g_gamestate.friend_next)
		{
			if(g_gamestate.enemy_next < npc ) // g_gamestate.cnt_enemy
			{
				npc = g_gamestate.enemy_next&3;
				//npc = (g_game_counter+g_gamestate.enemy_next)&3;
				npc = add_NPC(npc, AI_STATE_PLAYER_TOWARD, g_gamestate.enemy_next,  SIDE_ENEMY);



				LOG_GAME_UPDATE("new enemy, npc %d, cnt: %d phase  %d \n", npc, g_gamestate.enemy_alive , g_gamestate.wave);
			}

		}




		/*
			if( g_gamestate.phase > 30  && npc <  g_gamestate.phase)
			{
				g_AI_enemies[npc].speed = 250;
				LOG_GAME_UPDATE("BOSS  npc %d, cnt: %d phase  %d \n", npc, g_gamestate.cnt_enemy , g_gamestate.phase);
			}
			else
		 */




	} // 	if(g_gamestate.cnt_enemy <  npc || g_gamestate.cnt_friend <  npc)
	else if( (g_gamestate.friend_next ==  npc ) && (g_gamestate.enemy_alive +  g_gamestate.friend_alive) == 0 ) //&& g_gamestate.enemy_next ==  npc && g_gamestate.friend_next ==  npc )// new phase only when everything is gone
	{

		if(g_gamestate.wave)
		{
			//u32 r;

			add_smart_bomb(); // clear bullets/fires etc
			g_player.AI_hit_cnt = 255;
			g_player.dpad = g_player.shoot_timer = g_player.shoot_dpad = 0;
			g_player.posX = MAP_START_PLAYER_POSX;
			g_player.posY = MAP_START_PLAYER_POSY;
			amico_stop_all_SFX();

			g_player.dpad = g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME*2;
			amico_BGM_quiet_time(1);
			g_function_loop = update_new_game_wave;
			//r = rand()%20;
			//amico_play_SFX(50-r, SFX_HIT_ENEMY_VOL); //top 50 voices are long and funny
			MACRO_CLEAR_SCREEN
			g_game_counter = 0;

			// unlock bosses
			//	if( g_gamestate.wave > (AMICO_NONE_BOSSES) && g_unlocked_bosses_level > 1)
			//		g_unlocked_bosses_level--;
		}


#ifdef BOSS_TEST
		//g_gamestate.wave =  (BOSS_WAVE);
		g_gamestate.wave =   1+(MAX_SHILLS-g_unlocked_bosses_level) ;
#else
		g_gamestate.wave++;
#endif
		g_gamestate.enemy_next = 0;
		g_gamestate.friend_next = 0;

		// center player
		g_player.posX = MAP_START_PLAYER_POSX;
		g_player.posY = MAP_START_PLAYER_POSY;



#if 0
		if(npc>MAX_SHILLS)
			if( (g_gamestate.wave >> 5) > g_gamestate.level)
			{
				g_gamestate.level++;
				g_gamestate.wave = 1; // waves start at 1
				LOG_GAME_UPDATE("NEW g_gamestate.diff %d!\n", g_gamestate.level);
			}
#endif
		LOG_GAME_UPDATE("NEW PHASE %d!\n", g_gamestate.wave);
	}
} //void update_game_AI(void)


void update_game(void)
{
	/*
#define MAP_BOUNDING_SIDES 4
#define MAP_BOUNDING_TOP 32
#define MAP_BOUNDING_BOT 1
	 */
	LOG_GAME_UPDATE("\n g_player.shoot_dpad %d g_player.dpad %d g_function_loop();  %x   amico: This is %s() from %s, line %d \n", g_player.shoot_dpad ,g_player.dpad, g_function_loop,__FUNCTION__, __FILE__, __LINE__);
#define LOG_SHELL_BONUS // printf
#define SHELL_BONUS ( (1+g_gamestate.level) *100)
	//calc points
	{
		u32 x,y;

		x = (s32) (g_player.posX>>6);
		y = (s32) (g_player.posY>>6);

		if(y < 15+MAP_BOUNDING_TOP)// top
		{
			// LOG_SHELL_BONUS("X %d Y %d\n", x, y);

			if(x < MAP_BOUNDING_SIDES+32) // left
			{
				if(g_shell_bonus != g_gamestate.time)
				{
					g_shell_bonus = g_gamestate.time;
					g_gamestate.p_score-=SHELL_BONUS;
					LOG_SHELL_BONUS("g_game_counter %d X %d Y %d\n",g_game_counter, x, y);
				}
			}
			else if(x > 320-(MAP_BOUNDING_SIDES+15) ) // right
			{
				if(g_shell_bonus != g_gamestate.time)
				{
					g_shell_bonus = g_gamestate.time;
					g_gamestate.p_score-=SHELL_BONUS;
					LOG_SHELL_BONUS("g_game_counter %d X %d Y %d\n",g_game_counter, x, y);
				}
			}
		}
		else if(y > 240-(MAP_BOUNDING_BOT+33))// bot
		{
			// LOG_SHELL_BONUS("X %d Y %d\n", x, y);


			if(x < MAP_BOUNDING_SIDES+32) // left
			{
				if(g_shell_bonus != g_gamestate.time)
				{
					g_shell_bonus = g_gamestate.time;
					g_gamestate.p_score-=SHELL_BONUS;
					LOG_SHELL_BONUS("g_game_counter %d X %d Y %d\n",g_game_counter, x, y);
				}
			}
			else if(x > 320-(MAP_BOUNDING_SIDES+20) ) // right
			{
				if(g_shell_bonus != g_gamestate.time)
				{
					g_shell_bonus = g_gamestate.time;
					g_gamestate.p_score-=SHELL_BONUS;
					LOG_SHELL_BONUS("g_game_counter %d X %d Y %d\n",g_game_counter, x, y);
				}
			}
		}
		else if(x > 145 && x < 145+40 && y > 120 && y < 120+40) // center
		{
			if(g_shell_bonus != g_gamestate.time)
			{
				g_shell_bonus = g_gamestate.time;
				g_gamestate.p_score+=SHELL_BONUS;
				LOG_SHELL_BONUS("g_game_counter %d X %d Y %d\n",g_game_counter, x, y);
			}
		}

	}

	// game logic
	// if( (g_game_counter & 255 ) == (255- g_gamestate.phase))//% 250 ==0)
	// if( (g_game_counter & 255 ) == (255- g_gamestate.time>> 8))//% 250 ==0)
	// if( (g_game_counter & (255-g_gamestate.phase) ) == (255- g_gamestate.phase))//== (255- g_gamestate.time>> 8))//% 250 ==0)
	// if( (g_game_counter & (15) ) == 15) // about 1sec


	// LOG_GAME_UPDATE("update_game level %d -  %d  %d \n", g_game_counter,  (g_game_counter & 511 ) , (511- g_gamestate.wave) );


	//TODO done LEVEL BOSS BG FLASHING
	// magic numbers to fudge zero starting numbers with 1 starting ones :/
	//	if(g_gamestate.enemy_next > AMICO_NONE_BOSSES)

	if(g_gamestate.enemy_next > (1+MAX_SHILLS)-AMICO_BOSSES &&  g_gamestate.enemy_next >  (4+g_gamestate.wave - (MAX_SHILLS-g_unlocked_bosses_level)) )  // boss extra power!
	{
		amico_BGM_quiet_time(1); //make BGM quieter for TT crazy talk

		if(g_game_counter & 32 )
		{
			s32 SFX;

#if 0
			u32 level = (g_gamestate.level) + (g_gamestate.wave);// - (MAX_SHILLS-g_unlocked_bosses_level));

			//printf("level %d g_gamestate.wave %d  g_gamestate.enemy_next %d\n",level, g_gamestate.wave , g_gamestate.enemy_next);

			amico_BGM_quiet_time(1); // should be put somewhere better!

			printf("level %d, SFX_LAST-11 %d\n",level, SFX_LAST-11);

#if 1



			level = level % (SFX_LAST-11);

			level = SFX_AMICO_AGAIN+(SFX_LAST-level); //
#else

			if( level > SFX_LAST-11)
				level = SFX_AMICO_AGAIN+(SFX_LAST-level); //
#endif



			printf("real level %d\n",level);

			if(g_gamestate.BG_MAIN == 1)
			{

				if(g_gamestate.time & 8) // shill
					amico_play_SFX( level  ); //promote your channel, make a reaction video
				else
					amico_play_SFX( level+1  ); //promote your channel, make a reaction video


			}
			else if(g_gamestate.BG_MAIN == 42)
			{

				if(g_gamestate.time & 8) // shill
					amico_play_SFX( level+2  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( level+3 );//39 23 25 35


			}

			else if(g_gamestate.BG_MAIN == 83)
			{

				if(g_gamestate.time & 8) // shill
					amico_play_SFX(  level+4  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( level+5 );//39 23 25 35


			}

			else if(g_gamestate.BG_MAIN == 126)
			{

				if(g_gamestate.time & 8) // shill
					amico_play_SFX( level+6  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( level+7  );//39 23 25 35


			}

			else if(g_gamestate.BG_MAIN == 167)
			{

				if(g_gamestate.time & 8) // shill
					amico_play_SFX( level+8  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( level+9  );//39 23 25 35


			}

			else if(g_gamestate.BG_MAIN == 210)
			{

				if(g_gamestate.time & 8) // shill
					amico_play_SFX(level+10  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( level+11  );//39 23 25 35


			}




			g_gamestate.BG_MAIN++;
			intern_black_and_white_BG(g_game_counter & 4 );


#else

			if(g_gamestate.BG_MAIN == 1)
			{

				SFX = (g_gamestate.level) + (g_gamestate.wave); //get and inc
				LOG_GAME_UPDATE("level %d g_gamestate.wave++; //get and inc\n",SFX);

				SFX = SFX % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX
				LOG_GAME_UPDATE("level %d level % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX\n",SFX);

				SFX += SFX_AMICO_AGAIN; // move to after amico again SFX
				LOG_GAME_UPDATE("level %d evel += SFX_AMICO_AGAIN; // move to after amico again SFX \n",SFX);

				SFX -= ADD_TO_SFX; // remove extra from below
				LOG_GAME_UPDATE("level %d level -= ADD_TO_SFX; // remove extra from below	\n",SFX);

				if(SFX < SFX_AMICO_AGAIN)
					SFX = SFX_AMICO_AGAIN;

				if(g_gamestate.time & 1) // shill
					amico_play_SFX( SFX  ); //promote your channel, make a reaction video
				else
					amico_play_SFX( SFX+1  ); //promote your channel, make a reaction video


			}
			else if(g_gamestate.BG_MAIN == 42)
			{


				SFX = (g_gamestate.level) + (g_gamestate.wave); //get and inc
				LOG_GAME_UPDATE("level %d g_gamestate.wave++; //get and inc\n",SFX);

				SFX = SFX % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX
				LOG_GAME_UPDATE("level %d level % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX\n",SFX);

				SFX += SFX_AMICO_AGAIN; // move to after amico again SFX
				LOG_GAME_UPDATE("level %d evel += SFX_AMICO_AGAIN; // move to after amico again SFX \n",SFX);

				SFX -= ADD_TO_SFX; // remove extra from below
				LOG_GAME_UPDATE("level %d level -= ADD_TO_SFX; // remove extra from below	\n",SFX);

				if(SFX < SFX_AMICO_AGAIN)
					SFX = SFX_AMICO_AGAIN;

				if(g_gamestate.time & 1) // shill
					amico_play_SFX( SFX+2  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( SFX+3 );//39 23 25 35


			}
			else if(g_gamestate.BG_MAIN == 83)
			{


				SFX = (g_gamestate.level) + (g_gamestate.wave); //get and inc
				LOG_GAME_UPDATE("level %d g_gamestate.wave++; //get and inc\n",SFX);

				SFX = SFX % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX
				LOG_GAME_UPDATE("level %d level % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX\n",SFX);

				SFX += SFX_AMICO_AGAIN; // move to after amico again SFX
				LOG_GAME_UPDATE("level %d evel += SFX_AMICO_AGAIN; // move to after amico again SFX \n",SFX);

				SFX -= ADD_TO_SFX; // remove extra from below
				LOG_GAME_UPDATE("level %d level -= ADD_TO_SFX; // remove extra from below	\n",SFX);

				if(SFX < SFX_AMICO_AGAIN)
					SFX = SFX_AMICO_AGAIN;

				if(g_gamestate.time & 1) // shill
					amico_play_SFX(  SFX+4  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( SFX+5 );//39 23 25 35


			}
			else if(g_gamestate.BG_MAIN == 126)
			{

				SFX = (g_gamestate.level) + (g_gamestate.wave); //get and inc
				LOG_GAME_UPDATE("level %d g_gamestate.wave++; //get and inc\n",SFX);

				SFX = SFX % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX
				LOG_GAME_UPDATE("level %d level % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX\n",SFX);

				SFX += SFX_AMICO_AGAIN; // move to after amico again SFX
				LOG_GAME_UPDATE("level %d evel += SFX_AMICO_AGAIN; // move to after amico again SFX \n",SFX);

				SFX -= ADD_TO_SFX; // remove extra from below
				LOG_GAME_UPDATE("level %d level -= ADD_TO_SFX; // remove extra from below	\n",SFX);

				if(SFX < SFX_AMICO_AGAIN)
					SFX = SFX_AMICO_AGAIN;



				if(g_gamestate.time & 1) // shill
					amico_play_SFX( SFX+6  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( SFX+7  );//39 23 25 35


			}
			else if(g_gamestate.BG_MAIN == 167)
			{


				SFX = (g_gamestate.level) + (g_gamestate.wave); //get and inc
				LOG_GAME_UPDATE("level %d g_gamestate.wave++; //get and inc\n",SFX);

				SFX = SFX % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX
				LOG_GAME_UPDATE("level %d level % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX\n",SFX);

				SFX += SFX_AMICO_AGAIN; // move to after amico again SFX
				LOG_GAME_UPDATE("level %d evel += SFX_AMICO_AGAIN; // move to after amico again SFX \n",SFX);

				SFX -= ADD_TO_SFX; // remove extra from below
				LOG_GAME_UPDATE("level %d level -= ADD_TO_SFX; // remove extra from below	\n",SFX);

				if(SFX < SFX_AMICO_AGAIN)
					SFX = SFX_AMICO_AGAIN;


				if(g_gamestate.time & 1) // shill
					amico_play_SFX( SFX+8  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( SFX+9  );//39 23 25 35


			}
			else		if(g_gamestate.BG_MAIN == 210)
			{

				SFX = (g_gamestate.level) + (g_gamestate.wave); //get and inc
				LOG_GAME_UPDATE("level %d g_gamestate.wave++; //get and inc\n",SFX);

				SFX = SFX % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX
				LOG_GAME_UPDATE("level %d level % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX\n",SFX);

				SFX += SFX_AMICO_AGAIN; // move to after amico again SFX
				LOG_GAME_UPDATE("level %d evel += SFX_AMICO_AGAIN; // move to after amico again SFX \n",SFX);

				SFX -= ADD_TO_SFX; // remove extra from below
				LOG_GAME_UPDATE("level %d level -= ADD_TO_SFX; // remove extra from below	\n",SFX);

				if(SFX < SFX_AMICO_AGAIN)
					SFX = SFX_AMICO_AGAIN;

				if(g_gamestate.time & 1) // shill
					amico_play_SFX(SFX+10  ); //promote your channel, make a reaction video

				else
					amico_play_SFX( SFX+11  );//39 23 25 35


			}




			g_gamestate.BG_MAIN++;
			// play TT talk
#endif
		} //if(g_game_counter & 32 )

		if(g_no_boss_flashing == 0)
			intern_black_and_white_BG(g_game_counter & 4 );
	}
	else //not flashing boss
		g_gamestate.BG_MAIN += g_game_counter&1;


	{// new NPC






		if(g_gamestate.friend_next >= 1+(g_gamestate.wave >>3) )  // come out after 1/4 of the friend wave
		{
			u32 enemy_pacing =  g_gamestate.level;

			if( g_gamestate.enemy_next < 8 || g_gamestate.wave-g_gamestate.enemy_next < 8) // g_gamestate.wave > 30 &&
			{
				enemy_pacing = 0;//slow
			}


			//	printf("g_game_counter %d enemy_pacing %d\n", g_game_counter, enemy_pacing);

			switch(enemy_pacing)
			{
			case 0:
				if( (g_game_counter & 127 ) == (127- (g_gamestate.wave) ) )//% 250 ==0)
					update_game_AI();
				break;

			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				if( (g_game_counter & 63 ) == (63- g_gamestate.wave))//% 250 ==0)
					update_game_AI();
				break;



			case 6:
			case 7:
			case 8:
			case 9:

				if( (g_game_counter & 31 ) == (31- (g_gamestate.wave) &31) )//% 250 ==0)
					update_game_AI();
				break;


			case 10:
			case 11:
			case 12:
			case 13:
				if( (g_game_counter & 15 ) == (15- (g_gamestate.wave) &15) )//% 250 ==0)
					update_game_AI();
				break;


			default:
				if( (g_game_counter & 7 ) == (7- (g_gamestate.wave) &7) )//% 250 ==0)
					update_game_AI();
				break;


			} // switch( g_gamestate.level ) update_game_AI


		}



		if( g_gamestate.friend_next < g_gamestate.wave &&   (g_game_counter & 127 ) == (127- (g_gamestate.wave) )  )
		{

			//			if( g_gamestate.friend_next < g_gamestate.wave )//% 250 ==0)
			{
				u32 npc;

				npc = ( (g_gamestate.friend_next+1)) &3;
				//npc = (g_game_counter+g_gamestate.enemy_next)&3;
				npc = add_NPC(npc, AI_STATE_PLAYER_TOWARD, g_gamestate.friend_next, SIDE_FRIEND);


				LOG_GAME_UPDATE("new enemy, npc %d, cnt: %d phase  %d \n", npc, g_gamestate.friend_alive, g_gamestate.wave);

			}




		}

	}// new NPC


	LOG_GAME_UPDATE("\n g_player.shoot_dpad %d g_player.dpad %d g_function_loop();  %x   amico: This is %s() from %s, line %d \n", g_player.shoot_dpad ,g_player.dpad, g_function_loop,__FUNCTION__, __FILE__, __LINE__);


	// player movement logic
	game_collision_move((t_runner*)&g_player, 5, -8, 5, 1);

	LOG_GAME_UPDATE("\n g_player.shoot_dpad %d g_player.dpad %d g_function_loop();  %x   amico: This is %s() from %s, line %d \n", g_player.shoot_dpad ,g_player.dpad, g_function_loop,__FUNCTION__, __FILE__, __LINE__);



	{


		if(g_player.shoot_dpad) //if(g_player.shoot_timer == 0 )
		{
			// add_bullet(t_runner * runner, u8 dpad, u32 center_offsetDown_fixed, u32 center_offsetLeft_fixed)

			//g_player.shoot_dpad == CONTROL_DPAD_UP_DOWN ||
			if( (   g_player.shoot_dpad == CONTROL_DPAD_LEFT_RIGHT )   ) // CONTROL_DPAD_ALL_DIR = all buttons
			{



#ifdef _RELEASE_

				if(!g_gamestate.cheat_testing)
				{
					u32 cost;

					//if(g_gamestate.enemy_next > AMICO_NONE_BOSSES)
					// (MAX_SHILLS)-AMICO_BOSSES) // &&  g_gamestate.enemy_next >  (4+g_gamestate.wave - (MAX_SHILLS-g_unlocked_bosses_level)) )  // boss extra power!
					//	return; // no smart bomb when theres a boss!


					if(g_gamestate.enemy_next > (1+MAX_SHILLS)-AMICO_BOSSES &&  g_gamestate.enemy_next >  (4+g_gamestate.wave - (MAX_SHILLS-g_unlocked_bosses_level)) )  // boss extra power!
						return; // no smart bomb when theres a boss!


					// cost of smart bomb??
					cost =  GAME_CALCULATE_SMART_BOMB_COST; // g_gamestate.wave * 10 * (1+g_gamestate.level); // take!


					if( g_gamestate.p_score > cost )
						g_gamestate.p_score -=cost;
					else
						return;
				}
#endif

#if 0
				if(cost > 50)
					g_gamestate.p_bullets -= cost-40; //  add

				if(cost > 150)
					g_gamestate.p_health -= cost-140;
#endif



				add_smart_bomb();

				if(!g_gamestate.cheat_testing)
				{
					//from new_wave
					u32 sfx = g_gamestate.level+g_gamestate.wave; // get current number
					sfx %= (SFX_LAST-SFX_TOMMY_TALK); // limit it
					sfx += SFX_TOMMY_TALK; // add start


					amico_stop_all_SFX();
					// MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
					MACRO_PLAY_STEREO_SFX(sfx);
				}

				g_player.shoot_timer = BUTTON_PRESS_TIME*2;


			}
			else
			{
				add_bullet((t_runner*)&g_player, g_player.shoot_dpad,  PLAYER_SHOOT_CENTER_DOWN , PLAYER_SHOOT_CENTER_LEFT, SIDE_FRIEND);
				g_gamestate.level_bullets_used++;
				g_player.shoot_timer = BUTTON_PRESS_TIME;
				g_gamestate.p_bullets--;

				if(g_gamestate.p_bullets == 0) // bullet logic
				{
					g_gamestate.p_health -=20; // take!
					g_gamestate.p_bullets +=20; //  add
				}

			}


			g_player.shoot_dpad=0;

		}


	}// bullet


	//shell anim
	if( g_gamestate.shell_corners_ticks )
	{
		if( g_gamestate.shell_corners_ticks == 255)
		{
			g_gamestate.shell_corners_ticks = g_gamestate.shell_corners = 0;
		}
	}// shell anim


	if(g_gamestate.p_health < 0) // bullet logic
	{

		g_game_counter = 0;
		add_smart_bomb();
		g_function_loop = update_dead;
		amico_BGM_quiet_time(1);
		MACRO_CLEAR_SCREEN
	}


	// game_bullet_bullet_collision( );
	game_render();
	game_AI_enemies();
	game_AI_friends();
	intern_update_time();
	g_game_counter++;



#if 0
	if(g_gamestate.cheat_big_heads)
	{

		if(g_gamestate.cheat_big_heads & CHEATS_UNLIMITED_BULLETS)
		{
			g_gamestate.p_bullets = 255;
		}

		if(g_gamestate.cheat_big_heads & CHEATS_UNLIMITED_LIVES)
		{
			g_gamestate.p_health = 255;
		}
	}
#endif

#ifdef BETA_DEMO
	if(g_gamestate.time & 1)
	{
		amico_rectangle(0, 0, 0,      0, 120,     320, 18);
		render_text(118, 130,        100, (char *) "-- DEMO --" ); //amico_text_continue();
	}

#endif




}

void update_level_zero(void)
{

	u32 i;


	LOG_ZERO("\n update_level_zero %d \n", g_game_counter);

	if(g_game_counter == 0) // first run, init it
	{
		LOG_ZERO("\n update_level_zero  doing init %d \n", g_game_counter);
		MACRO_GAME_RESET_AND_RANDOMIZE_LIST
		g_gamestate.wave = 0; //12 amico level
		g_gamestate.level = 0;
		g_gamestate.time = 0;

	}

	// no audio
	amico_stop_all_SFX();



	g_game_counter++;

	//g_gamestate.cheat_big_heads = g_game_counter&8 ;




	//	if( (g_game_counter & 127 ) == (127- (g_gamestate.wave) ) )//% 250 ==0)
	//	update_game_AI();

	if( g_gamestate.enemy_next < (AMICO_NONE_BOSSES) && ( (g_game_counter & 31 ) == (31- (g_gamestate.wave) &31)) )
	{
		//	add_NPC(i&3, (i&1)+1, i,  SIDE_ENEMY);
		//	add_NPC(i&3, (i&1)+1, i,  SIDE_FRIEND);
		i = g_gamestate.time;

		LOG_ZERO("\n update_level_zero adding NPC's' time %d \n", i);

		if(rand()&1)
			i = add_NPC(rand()&3, AI_STATE_PLAYER_TOWARD, g_gamestate.enemy_next,  SIDE_ENEMY);
		else
			i = add_NPC(rand()&3, AI_STATE_PLAYER_TOWARD, g_gamestate.friend_next,  SIDE_FRIEND);

		g_AI_enemies[i].speed = g_AI_friends[i].speed=  (g_gamestate.time+1) *5;
		// g_AI_enemies[i].seed = g_AI_friends[i].seed= g_gamestate.time&0xF;
		g_AI_enemies[i].AI_personal_tolerance = g_AI_friends[i].AI_personal_tolerance= 1;

		g_AI_enemies[i].AI_tick = g_AI_friends[i].AI_tick= 255;
		LOG_ZERO("\n add_NPC  %d \n", i);
	}


	LOG_ZERO("\n update_level_zero 1 %d \n", g_game_counter);

#if 0
	game_render();
#else



	intern_update_time();

	render_map();

	render_fires();
	render_runner_hits();
	amico_stop_all_SFX();

	render_bullets();
	amico_stop_all_SFX();


#if 0
	if(g_player.AI_hit_cnt)
	{
		if(g_game_counter & 16)
			amico_rectangle(255, 255, 255, (g_player.posX>>6)-16, (g_player.posY>>6) -16, 16, 32 );
		//		else
		//		amico_rectangle(155,155, 155, (g_player.posX>>6)-16, (g_player.posY>>6) -16, 16, 32 );


		g_player.AI_hit_cnt--;
	}
#endif


#endif


	//if(g_gamestate.time & 1)
	{


		amico_rectangle(0, 0,0,  0, 0,        320, MAP_BOUNDING_TOP);
		//amico_rectangle(0, 0, 0,      0, 120,     320, 32);
		render_text(0, 10,        100, (char *) " TOMMY NEEDS TO CLEAR THE AIR TO START" ); //amico_text_continue();

#ifdef __NOT_USED__
		if(g_gamestate.time & 2)
			render_text(60, 20,        100, (char *)        "      HOLD  [ AND ]" ); //amico_text_continue();
		else
			render_text(54, 20,        100, (char *)  " OR PRESS SHOULDER BUTTON" ); //amico_text_continue();
#else
		if(g_gamestate.time & 2)
			render_text(50, 20,        100, (char *) "HIT ANALOG, SHOULDER OR [ ] " ); //amico_text_continue();
		else
			render_text(50, 20,        100, (char *) "   KEYBOARD: SPACE BAR" ); //amico_text_continue();
#endif
		//g_gamestate.BG_MAIN++;
		g_gamestate.BG_MAIN+=g_gamestate.time&1; // g_game_counter&1;//add on every odd

	}


	LOG_ZERO("\n update_level_zero before game_AI_enemies %d \n", g_game_counter);


	game_AI_enemies();
	// no audio
	amico_stop_all_SFX();

	game_AI_friends();
	amico_stop_all_SFX();


	LOG_ZERO("\n update_level_zero 2 %d \n", g_game_counter);
	// player movement logic
	game_collision_move((t_runner*)&g_player, 5, -8, 5, 1);
	amico_stop_all_SFX();

	LOG_ZERO("\n update_level_zero 3 %d \n", g_game_counter);



	render_runner( (t_runner*)&g_player, 3);//.frame, g_player.posX, g_player.posY,	g_player.dir & 1);


	//TODO 0000 update_level_zero

	if(g_player.shoot_dpad) //if(g_player.shoot_timer == 0 )
	{

		GOTO_EXIT:


		g_game_counter = g_gamestate.cheat_big_heads = g_gamestate.wave = g_gamestate.level = 0;


		g_player.AI_hit_cnt = 255;
		g_player.dpad = 0;
		g_player.shoot_timer=BUTTON_PRESS_TIME*2;


		g_player.posX = MAP_START_PLAYER_POSX;
		g_player.posY = MAP_START_PLAYER_POSY;
		amico_stop_all_SFX();

		//r = rand()%20;
		//amico_play_SFX(50-r, SFX_HIT_ENEMY_VOL); //top 50 voices are long and funny
		MACRO_CLEAR_SCREEN

		if( g_player.TPAGE == 1 && ( g_player.textU + g_player.textV ) == 0) // it's Tommy! no player selected... still in intro
		{
			MACRO_GAME_RESET_AND_RANDOMIZE_LIST
			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
			g_function_loop = update_intro; // back to select a character
			return;
		}

		if( ( g_player.shoot_dpad == CONTROL_DPAD_LEFT_RIGHT )   ) // CONTROL_DPAD_ALL_DIR = all buttons
		{



			MACRO_GAME_RESET_AND_RANDOMIZE_LIST
			amico_BGM_quiet_time(1);
			g_player.dpad = g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME*2;
			g_function_loop = update_new_game_wave;

			return;


			//  g_function_loop = update_game;
		}
	}



	if( (g_gamestate.time % (AMICO_NONE_BOSSES+5) ) == 0)
	{


		//reset

		memset((u8*) &g_AI_friends[0], 0,  sizeof(t_AI_youtubers) * (MAX_SHILLS+1 ) );
		memset((u8*) &g_AI_enemies[0], 0,  sizeof(t_AI_youtubers) * (MAX_SHILLS+1) );
		memset((u8*) &g_runner_hits[0], 0, sizeof(t_runner_hit) * (MAX_ENTITIES) );
		memset((u8*) &g_fires[0], 0, sizeof(t_pos) * MAX_ENTITIES);
		memset((u8*) &g_bullets[0], 0, sizeof(t_bullet) * MAX_ENTITIES);
		// don't clear memset(&g_gamestate, 0, sizeof(g_gamestate));

		intern_randomize_init_lists();


		g_player.posX = MAP_START_PLAYER_POSX;
		g_player.posY = MAP_START_PLAYER_POSY;

		g_gamestate.wave=(u8) rand();//(rand() & 0xFF);
		g_gamestate.cheat_big_heads = g_gamestate.wave &1;

		g_gamestate.wave%=MAX_SHILLS;



		g_gamestate.enemy_next = g_gamestate.friend_next = g_gamestate.enemy_alive = g_gamestate.friend_alive = 0;


		if(g_gamestate.time > ( 5*(AMICO_NONE_BOSSES+4) )  ) // do 5 time then random out
		{


			if( (rand() & 1) )
			{
				goto GOTO_EXIT; // clear and got to next screen
			}

			g_game_counter = 0; //start again

		}

	}






}


// splash screens


#ifndef __NOT_USED__
#ifndef UNIT_32BLIT // SDL only
extern int SDL_GetCPUCount(void);
#endif
#endif



 
void update_splash(void)
{

	u8 cnt = (g_game_counter>>3);
	// g_game_counter+=2;
	g_game_counter++;

	//BG
	amico_rectangle( 0, 0, 0,   0, 0, 320,240 );









#ifndef _DEBUG_
#if 1 //ndef UNIT_32BLIT


		//if(g_gamestate.wave == 0xAA) // first run
	{
		char text[512];

		//warning/loading/BGM sync bar
		amico_rectangle( 66, 66, 66,   8, 240-24, 320-16, 24 );



		// loading progress bar
#ifdef __NOT_USED__
		amico_rectangle( 104, 252, 252,   8, 240-10, 60-7+cnt,10 );
#else
		amico_rectangle( 104, 252, 252,   8, 240-10, 60-7+cnt,10 );
#endif

#if 1 //ndef BETA
		// printf("%d\n", g_game_counter>>3 ); //%127


		//	LOG_SCROLL_TEXT("\n cnt %d \n", cnt);


		if(	cnt < 5 )
			sprintf(text, (char *) "SYSTEM START - BACK TO EXIT");

		else if(	cnt < 10 )
			sprintf(text, (char *) "SYSTEM LAUNCHED - BACK TO EXIT"); // sprintf(text, (char *) "SYSTEM CHECK.");

		else if(	cnt < 15 )
			sprintf(text, (char *) "SYSTEM INITIALIZING - BACK TO EXIT");

		else if(	cnt < 25 )
			sprintf(text, (char *)  "PRESS A TO LOAD LAST SAVE.");


		else if(	cnt < 35 )
			sprintf(text, (char *)  "PRESS A TO LOAD LAST SAVE..");


		else if(	cnt < 45 )
			sprintf(text, (char *)  "PRESS A TO LOAD LAST SAVE...");


		else if(	cnt < 55 )
			sprintf(text, (char *) "LOADING INTO RAM.");

		else if(	cnt < 65 )
			sprintf(text, (char *) "LOADING INTO RAM..");

		else if(	cnt < 75 )
			sprintf(text, (char *) "LOADING INTO RAM...");


		else if(	cnt < 85 )
			sprintf(text, (char *) "LOADING INTO RAM... OK");

		else if(	cnt < 90 )
			sprintf(text, (char *) "CONFIGURING DATA.");

		else if(	cnt < 95 )
			sprintf(text, (char *) "CONFIGURING DATA..");

		else if(	cnt < 100 )
			sprintf(text, (char *) "CONFIGURING DATA... OK");


		else if(	cnt < 110 )
			sprintf(text, (char *) "FINAL SANATIY CHECK.");

		else if(	cnt < 120 )
			sprintf(text, (char *) "FINAL SANATIY CHECK..");

		else if(	cnt < 130 )
			sprintf(text, (char *) "FINAL SANATIY CHECK...");

		else if(	cnt < 140 )
			sprintf(text, (char *) "FINAL SANATIY CHECK....");

		else if(	cnt < 150 )
			sprintf(text, (char *) "FINAL SANATIY CHECK.... FAILED");


		else if(	cnt < 190 )
		{
#ifdef __NOT_USED__
			sprintf(text, (char *) "CRITAL EXPECTION ERROR ON LINE %05d", rand()  & 0xFFFF );
#else
			sprintf(text, (char *) "CRITAL EXPECTION ERROR ON LINE %05d", rand()%999999); 
#endif
		}

		else if(	cnt < 200 )
			sprintf(text, (char *) "INITIATING SAFE SHUTDOWN.");



		else if(	cnt < 210 )
			sprintf(text, (char *) "INITIATING SAFE SHUTDOWN..");


		else if(	cnt < 220 )
			sprintf(text, (char *) "INITIATING SAFE SHUTDOWN...");


		else if(	cnt < 230 )
			sprintf(text, (char *) "INITIATING SAFE SHUTDOWN....");


		else if(	cnt < 240 )
			sprintf(text, (char *) "INITIATING SAFE SHUTDOWN.... FAILED");


		else if(	cnt < 248 )
		{
#ifdef __NOT_USED__
			sprintf(text, (char *) "%05d%05d%05d%05d%05d%05d%05d",rand() & 0xFFFF , rand()  & 0xFFFF , rand()  & 0xFFFF , rand()  & 0xFFFF  ,rand()  & 0xFFFF , rand()  & 0xFFFF , rand()  & 0xFFFF );
#else
			sprintf(text, (char *) "%08d%09d%09d%07d",+rand()%999999,+rand()%99999999, +rand()%99999999, +rand()%99999);
#endif
		}
		else
			sprintf(text, (char *) " PAIRING WITH MERLIN AND CONNECTING..");

		if(	cnt > 199 && cnt < 247)
			if(cnt&2)
				if(cnt&1)
				{
#ifdef __NOT_USED__
					sprintf(text, (char *) "CRITAL EXPECTION ERROR ON LINE %05d", rand()& 0xFFFF);
#else
					sprintf(text, (char *) "CRITAL EXPECTION ERROR ON LINE %05d", rand()& 0xFFFF); 
#endif




				}

		// sprintf(text, (char *) "CPU: %d" , SDL_GetCPUCount() );

		render_text(16, 240-20, 100, text);

#endif// BETA


		if(g_game_counter & 32)
			render_text(8, 180, 100, (char *)"EPILEPSY AND OFFENSIVE CONTENT WARNING!"); //render_text(8, 180, 100, (char *)"  MAJOR SEIZURE AND LANGUAGE WARNING!");

	} //if(g_gamestate.wave == 0xAA) // first run




#ifdef NO_BGM // CENSORED - NO BAD MUSIC
#define BGM_START 31
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+0] = 'C';
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+1] = 'E';
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+2] = 'N';
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+3] = 'S';
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+4] = 'O';
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+5] = 'R';
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+6] = 'E';
	g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[BGM_START+7] = 'D';
#undef BGM_START

#endif // NO_BGM


#define HARDWARE_INFO_START 40

	
#ifdef __NOT_USED__

	 



#else // 32blit

	// should use 32blit timer class...  too lazy :/





#ifdef __ANDROID__
	{
		// TODO 00000 setting timing to core counts :/

		s32 CPUS = SDL_GetCPUCount();

		if(CPUS == 4) //OUYA
		{
			// if(cnt<237)
			//	if(cnt<150)
			// g_game_counter+=7;
			if(cnt<185)
				g_game_counter+=2;
		}
		else if(CPUS == 8) //mobile?
		{
			// if(cnt<198)
			if(cnt<80)
				g_game_counter+=3;
		}
		else
		{
			if(cnt< 103)
				g_game_counter++;
		}


		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+2] = 'A';
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+3] = 'N';
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+4] = 'D';
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+5] = '0'+CPUS/10;
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+6] = '0'+CPUS;


	}//  __ANDROID__


#elif defined ( __EMSCRIPTEN__ )
	{
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+2] = 'W';
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+3] = 'E';
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+4] = 'B';


		//web timer
		if(cnt<222) //105)
			g_game_counter++;

	} //__EMSCRIPTEN__

#else
	{


#ifndef UNIT_32BLIT
		//my PC timer
		if(cnt<103) //105)
			g_game_counter++;

		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+2] = 'P';
		g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[HARDWARE_INFO_START+3] = 'C';
#endif



	}
#endif


#endif //  32blit targets
#undef HARDWARE_INFO_START

	//if(0)
	if( g_game_counter > 128 &&   g_player.shoot_dpad  )
	{



#ifdef __NOT_USED__



		bad_random();
#else

#endif


		// skip if not into

		// check for saved game and load state.

		if(  g_player.shoot_dpad & CONTROL_DPAD_D )
		{
#ifdef __NOT_USED__



		bad_random();
#else

#endif

			if(amico_load_data())
			{
				__NOT_USED___2ND_READ_WORKED:

#ifdef __NOT_USED__



		bad_random();
#else

#endif
				intern_randomize_init_lists();

				if(g_gamestate.level > 0 ||  g_gamestate.wave > 5 ) // recreate increasing diff which isn't saved
				{
					u32 i;
					// mid level wave of  35-50 = 42
					u32 max = g_gamestate.level * 42 + g_gamestate.wave;


					if(max > 255)
						max = 251;// max

					for(i=0;i<=(MAX_SHILLS); i++) // find name
					{



						g_AI_enemies[i].phase = g_AI_friends[i].phase =max-i;

					}




					//for(i=0;i<g_gamestate.level; i++) // find name
					{
						g_AI_shoot_dist = INIT_SHOOT_DIST + ( (1+g_gamestate.level)*AI_SHOOT_DIST_INC)  + g_gamestate.wave;

						// g_AI_shoot_dist_center+= 3;
					}


					if(g_gamestate.level > 9) // for lvl 10
					{
						for(max=10;max<=g_gamestate.level; max++) // each level
							for(i=0;i<=50; i++) // each row
							{
								u32 level =i;

								//u32 g_cur_map[MAX_LEVEL+1][15]
								LOG_DEST("\n");
								if(level >= 0)
								{
									u32 r;
									u32 new_row;
									LOG_DEST("\n\n");
									for(r=2;r<15;r++)
									{
										new_row = g_cur_map[level][r];

										if(new_row > 0)
										{

											if(rand() & 1)
											{
												new_row = new_row & (u32)rand();
												LOG_DEST("NO_SELF_DESTRUCTION L%d  R:%d g_cur_map[level][row] 0x%X  -> 0x%X \n",level, r, g_cur_map[level][r] , new_row );
												g_cur_map[level][r] = new_row; // remove blocks
											}


										}
									}
								}

								//else
								//	g_cur_map[level][row] = g_cur_map[level][row] | (u32)rand(); // add blocks


							}
					}// 	if(g_gamestate.level > 9) // for lvl 10


				}



			}
#ifdef __NOT_USED__ // sometimes doesn't load on the 1st time :/
			else // try again
			{
				if(amico_load_data())
					goto __NOT_USED___2ND_READ_WORKED;
			}
#endif //__NOT_USED__


			amico_BGM_quiet_time(1); // continues to new wave

			return;
		}// if A
		else
			goto finished_splash;





	}







#ifndef __NOT_USED__


	//fade in
	if(g_game_counter < SPLASH_MAX_CYCLES )
	{

		render_text(0, 15, 100, (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN);
		render_text(0, 25, 100, (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+40);

		render_text(0, 35, 100, (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+80);

		render_text(84, 60, 100, (char *)"- MADE WITH 32BLIT -");



		amico_sprite(04, 96, 192, 32, 32,      155,     120,     cnt ,  0);


		return;
	}



#else




	if(g_game_counter < SPLASH_MAX_CYCLES )
	{
		//render_text(90, 15, 100, (char *)"- 10-10 AMICO AGAIN -");




		render_text(0, 15, 100, (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+1);
		render_text(0, 25, 100, (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+41);

		render_text(12, 35, 100, (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN+81);



		// old amico_sprite(04, 0, 224, 64, 32,      155,     120,     cnt , 0, 0);
		// amico_sprite(04, 0, 160, 96, 64,      155,     120,    128 + ( cnt >> 1) , 0, 0);
		amico_sprite(04, 0, 160, 96, 64,      155,     120,    50 + ( cnt >> 1) , 0);




		return;
	}

#endif 

	//render_text(12, 10, 100, (char *) g_texture_map_shills[i].name );
#endif // debug
#endif // 32BLIT
	// g_game_counter = 0;



	finished_splash:

	MACRO_GAME_RESET_AND_RANDOMIZE_LIST

	// TODO: done flip boss order
	//the start of bosses is the real intro
	//the bosses were originally at the start of the array and skipped over via the TT 2 shells screen.


	g_text_scroll_counter = 0; // reset scroll counter




	// skip to end (the bosses)
	MACRO_SKIP_TO_INTRO_COUNTER
	g_function_loop = update_intro;
	MACRO_CLEAR_SCREEN


	// play again to make extra loud!
	MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);


}

// #define printf //




void update_intro(void)
{



	u32 i = g_game_counter>>7;
	u32 side = g_game_counter>>6;

	LOG_INTRO("\n update_intro %d \n",g_game_counter);
	//screen.alpha = 255;
	i%= AMICO_NONE_BOSSES+12; // loop extra is for Tommy's 10-10 x10

	amico_rectangle( 0, 0, 0,   0, 0, 320,240 ); 




	// TODO done splash flip boss order

	//LOG_INTRO("g_unlocked_bosses_level %d i %d g_game_counter>>3 %d  %d  %d \n ", g_unlocked_bosses_level, i, (((g_text_scroll_counter)>>INTRO_SCROLL_TEXT_SPEED)) , g_game_counter, strlen(g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN) ); //

	// stupid thing, just kept growing!
	if( i > AMICO_NONE_BOSSES) //g_unlocked_bosses_level)  // skip bosses with flashing anim seq.
	{

		u32 drop = g_game_counter;
		LOG_INTRO("\n AMICO_BOSSES  update_credit drop %d \n",drop);
		drop -=34<<7;// new start
		drop = drop>>1; //half it
		LOG_INTRO("\n AMICO_BOSSES  update_credit drop %d \n",drop);


		LOG_INTRO("\n 2 AMICO_BOSSES  update_credit %d \n",!(side&1));
		LOG_INTRO("\n 2 AMICO_BOSSES  g_game_counter<<7 %d \n",g_game_counter>>7);
		//starts at 34 TT head anim intro and flashing Amico again 10 10
		if(drop < 182) // TT head and two shells colliding anim intro
		{

			MACRO_SLOW_DOWN;
			if(g_game_counter&2)
			{
				intern_black_and_white_BG(0);
			}
			else
			{
				intern_black_and_white_BG(1);

			}



			LOG_INTRO("\n drop < 180  update_credit %d \n", drop );
			LOG_INTRO("\n drop&1  update_credit %d \n", drop&1 );
			//if(drop&1) // flash big tallarico
			if(g_game_counter&1)
			{

				LOG_INTRO("\n drop&1  1  %d \n", drop );
#ifdef __NOT_USED__
				//amico_sprite(01,          0, 0, 32, 64,                                                            160,     120+8,    600 , 0, 0);
				amico_sprite(01,          0, 0, 32, 64,                                                            160,     120+8,    600 , 0);
#else
				amico_sprite(01,          0, 0, 32, 64,                                                            160,     120+8,    400 , 0);
#endif
				///amico_sprite(01,          0, 0, 32, 64,                                                            64,         -100,    600 , 0, 0);
				//amico_sprite(u8 TPAGE, u32 texture_u, u32 texture_v, u32 texture_w, u32 texture_h,                  s32 posX, s32 posY, s32 scale , u8 h_flip, u8 alpha);
			}


		}
		else // flashing TT and 10-10 amico again
		{
			LOG_INTRO("\n else  1  %d \n",!(side&1));


			if(g_game_counter&8)
			{
				intern_black_and_white_BG(0);

				//shills BG
				//amico_rectangle( 255, 255, 255,   0, 0, 160,240 );
				//haters BG
				//amico_rectangle(0, 0, 0,   160, 0, 320,240 );
			}
			else
			{
				intern_black_and_white_BG(1);
				//shills BG
				//amico_rectangle( 255, 255, 255,  160, 0, 320,240 );
				//haters BG
				//amico_rectangle(0, 0, 0,    0, 0, 160,240 );
			}




			// flash tallarico
			if(drop&2)
			{
				amico_sprite(01,    0, 0, 32, 64,      320/2,  64,     260 , g_game_counter&64);
			}
			else
			{
				amico_sprite(01,    0, 0, 32, 64,      320/2,    64+ 4,      300 , g_game_counter&64);
			}

			if((g_game_counter&64) )
			{

				LOG_INTRO("\n flash 10-10  %d \n",!(side&1));


				// amcio again
				amico_sprite(03,   4*8, 20*8,  8*8+1, 4*8,     160-16,  120+48,    280 , 0);

				// 10-10
				amico_sprite(04,  64, 224,       64, 32,       145, 175,     320 , 0);

				if( (g_game_counter%64) ==0) // do only once here, default init of youtubers
				{

					if( g_game_counter < 8000)//only first time!
					{
						amico_stop_all_SFX();
						LOG_INTRO("play SFX_AMICO_AGAIN" );
						MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
					}

					intern_randomize_init_lists();
					g_game_counter++;

				}

			}
			else
			{
				// amcio again

				amico_sprite(03, 4*8, 20*8,    8*8+1, 4*8,     160-16,  120+46,    300 , 0);





			}


			// BG
			amico_rectangle( 0, 0, 0,   0, 210, 320,30 );

			{
				// small string not needed, render_text limited to 40 chars
				//char str[40];
				u32 start = 120+( ( (g_text_scroll_counter++)>>INTRO_SCROLL_TEXT_SPEED)  );

				if(start>strlen( (char *) g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN))
				{
					g_gamestate.cheat_big_heads =1;
					g_function_loop = update_level_zero; //update_splash;
					g_player.dpad = g_player.shoot_dpad =0;
					g_player.shoot_timer=BUTTON_PRESS_TIME*2;
					g_text_scroll_counter =0;
					g_game_counter = 0;

					MACRO_CLEAR_SCREEN
					amico_stop_all_SFX();
					amico_BGM_quiet_time(0);
					//amico_play_BGM_audio(3);//intro

				}

				// start = start % strlen(g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN);
				//sprintf(str,"%0.*s", 39, g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN + start);

				// len = len % strlen(g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN);

				LOG_INTRO("g_game_counter %d %d \n ",(g_game_counter>>INTRO_SCROLL_TEXT_SPEED), ((g_game_counter>>INTRO_SCROLL_TEXT_SPEED) -22)); //
				// render_text(0, 215, 100, g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN + len);
				render_text(0, 215, 100, ((char *)g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN)+start);

			}


		}
		LOG_INTRO("\n drop  drop %d \n", 0 );
		if(drop > 182)
		{
			drop = 140; // move shells back
			LOG_INTRO("\n drop > 180  1 update_credit %d \n",drop);

			if(g_player.shoot_dpad &  CONTROL_DPAD_D)
			{
				LOG_INTRO2("\n  CONTROL_DPAD_U  g_game_counter %d drop %d \n",g_game_counter, drop );
				//	srand(g_game_counter & 0xFF);
				intern_randomize_init_lists();
				g_function_loop = update_select;
				g_player.shoot_dpad =0;
				g_player.shoot_timer=BUTTON_PRESS_TIME*2;
				g_gamestate.p_side = 0;
				g_game_counter =0;
				MACRO_CLEAR_SCREEN


			}else if(g_player.shoot_dpad &  CONTROL_DPAD_U)
			{
				LOG_INTRO2("\n  CONTROL_DPAD_U  g_game_counter %d drop %d \n",g_game_counter, drop );
				g_player.shoot_dpad =0;
				g_player.shoot_timer=BUTTON_PRESS_TIME*2;
				g_gamestate.p_side = 0;
				//	srand(g_game_counter & 0xFF);
				g_game_counter =0; //AMICO_BOSSES <<7;
				intern_randomize_init_lists();
			}

		}
		LOG_INTRO("\n amico_sprite amico_sprite amico_sprite  drop %d \n", 0 );



		LOG_INTRO("g_texture_map_haters %d %d %d \n", g_texture_map_haters[0].TPAGE,   g_texture_map_haters[0].textU, g_texture_map_haters[0].textV);

		//shells
		amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,  32, 32,    drop-64-16, 56+0,    350 , 1);
		amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,   32, 32,   16+64+320-drop, 56+0,    350 , 1);




	}
	else if (i<=AMICO_NONE_BOSSES) // g_unlocked_bosses_level ) // do the shills and haters youtubers credits
	{
		LOG_INTRO("\n i<=AMICO_NONE_BOSSES  i %d side %d \n", i, side);

		intern_do_flashing_heads( side,  i, 0);
	}// flashing characters
#if 0
	else if (i < (MAX_SHILLS + AMICO_BOSSES) )
	{ // high score for BOSS times

		u32 toprow = ( (g_game_counter>>4) - 0 );

		LOG_INTRO("toprow %d \n ",toprow); //


	}// high score for BOSS times
#endif
	else
	{

		LOG_INTRO2("\n  RESET  g_game_counter %d i %d \n",g_game_counter, i );
		// g_game_counter =   34<<7; //0 reset
		MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
	}


	g_game_counter++;

	LOG_INTRO("\n g_game_counter %d \n",g_game_counter);
	if(g_player.shoot_dpad &  CONTROL_DPAD_D) // cross
	{
		// sort list again!
		//srand(g_game_counter);
		//qsort(&g_texture_map_shills[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		//qsort(&g_texture_map_haters[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		// srand(g_game_counter & 0xFF);
		g_player.shoot_dpad =0;
		g_player.shoot_timer=BUTTON_PRESS_TIME*2;
		intern_randomize_init_lists();
		LOG_INTRO2("\n  CONTROL_DPAD_D  g_game_counter %d i %d \n",g_game_counter, i );
#if 1
		if( i < 182 ) /// is doing fancy intro, skip it
		{
			g_game_counter =  4700; //=  365; //MAX_SHILLS << 7; // skip it
			g_text_scroll_counter =0;
			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
		}
		else
		{
			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
			g_game_counter = 0;
			g_function_loop = update_select; // change to select
			MACRO_CLEAR_SCREEN

		}

#endif
	}
	else if(g_player.shoot_dpad &  CONTROL_DPAD_U) // TRIANGLE
	{
		LOG_INTRO2("\n  CONTROL_DPAD_U  g_game_counter %d i %d \n",g_game_counter, i );
		//	srand(g_game_counter & 0xFF);
		// g_game_counter = 34<<7;// MAX_SHILLS << 7;
		MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
		g_text_scroll_counter =0;
		intern_randomize_init_lists();
	}


	LOG_INTRO2("\n   g_game_counter %d i %d \n",g_game_counter, i );

}

#define PAUSE_DPAD_COUNTER 60


void update_pause(void)
{

	/*
	 *
	 *
// easy
// 5,6 play voices - hold up and hold down


// med
// 4 next level -   Clock wise U R D L  x2
// 2 bullets and health - Counter Clock wise U L D R  x2


// hard
// 1 big heads  -    L D D R  D D R U
// 3 unlock bosses - U L L U  D R R D

	 */
	// 9 (0 counter + 8 PAD inputs

	static u8 allCheats[CHEAT_TOTAL][9] = {
			{0,   CHEAT_EGO_MODE  }, // CHEAT_EGO_MODE
			{0,   CHEAT_GOD_MODE  }, // CHEAT_GOD_MODE
			{0,   CHEAT_UNLOCK_BOSSES  }, // CHEAT_UNLOCK_BOSSES
			{0,   CHEAT_NEXT_LEVEL  }, // CHEAT_NEXT_LEVEL
			{0,   CHEAT_VOICE_UP  }, // CHEAT_VOICE_UP
			{0,   CHEAT_VOICE_DOWN  }, // CHEAT_VOICE_DOWN
			{0,   CHEAT_VOICE_LEFT  }, // CHEAT_VOICE_LEFT
			{0,   CHEAT_VOICE_RIGHT  }, // CHEAT_VOICE_RIGHT
			{0,   CHEAT_TESTING  }, // CHEAT_TESTING
			{0,   CHEAT_ENDING  } // CHEAT_ENDING


	};
	static u8 button_cnt=0, voice_sample = 0;

	u32 i,cheat;


	// LOG_PAUSE("\n update_pause %d \n");

	intern_do_C64_loading_screen();

	// render_top();
	//render_map();
	g_gamestate.BG_MAIN++;




	// Tommy
	// amico_sprite(01, 0, 0, 32, 64,      320/2,    139,      340 , 0, 0);
	amico_sprite(01, 0, 0, 32, 64,      320/2,    120,      400 ,  0);


	//pause
	//	amico_rectangle(0, 0, 0,      0, 120,     320, 18);
	render_text(118, 130,        100, (char *) "-- PAUSED --" ); //amico_text_continue();


#ifdef __NOT_USED__


	// amcio again
	amico_sprite(03,   4*8, 20*8,  8*8+1, 4*8,     160-10,  120+48+14,    280 ,  0);

	if(!(g_game_counter&32) )
	{
		if((g_game_counter&16) )
			amico_sprite(01,    0, 0, 32, 64,      320/2,    104+ 4,      800 , 0);
		else
		{

			// 10-10
			amico_sprite(04,  64, 224,       64, 32,       145+6,     175+14,     320 ,  0);
		}



	}
	//else
	//	amico_rectangle(0, 0, 0, 0, 100,    320, 18);


#else

	// amcio again
	amico_sprite(03,   4*8, 20*8,  8*8+1, 4*8,     160-16,  120+48+32-8,    280 , 0);

	if(!(g_game_counter&32) )
	{
		if((g_game_counter&16) )
			; //amico_sprite(01,    0, 0, 32, 64,      320/2,    116,      400 , 0, 0);
		else
		{
			// 10-10
			amico_sprite(04,  64, 224,       64, 32,       145,      175+32-8,            320 , 0);

		}



	}




#endif


	// TODO: moved to main loop before first run
	//amico_stop_all_SFX();



	g_game_counter++;




	if(g_player.shoot_timer)
	{
		g_player.shoot_timer--;
		//printf(".");

	}
	else
	{



		if(g_game_counter&32)
		{


			amico_rectangle(0, 0, 0,   0, 55,    320, 22);
			render_text(90, 64, 100, (char *) "PRESS A TO CONTINUE" ); //amico_text_continue();




			if(button_cnt > 7)//clear all after 8 buttons entered
			{

				for(i=0; i<CHEAT_TOTAL; i++)
					allCheats[i][0] = 0;

				//g_player.dpad =0;
				//g_player.shoot_timer=PAUSE_DPAD_COUNTER;
				button_cnt = 0;
				LOG_PAUSE("\n cheat CLEARED \n");
				// continue as normal
			}

			if(g_player.dpad)
			{


#ifdef _DEBUG_

				if(g_player.dpad &  CONTROL_DPAD_U)
				{
					// g_player.dpad =0;
					//g_player.shoot_timer=PAUSE_DPAD_COUNTER;

					LOG_PAUSE("\n CONTROL_DPAD_U button_cnt:%d \n", button_cnt);
				}
				else if(g_player.dpad &  CONTROL_DPAD_R)
				{
					// g_player.dpad =0;
					//g_player.shoot_timer=PAUSE_DPAD_COUNTER;

					LOG_PAUSE("\n CONTROL_DPAD_R  button_cnt:%d \n", button_cnt);
				}
				else if(g_player.dpad &  CONTROL_DPAD_D)
				{
					// g_player.dpad =0;
					//g_player.shoot_timer=PAUSE_DPAD_COUNTER;

					LOG_PAUSE("\n CONTROL_DPAD_D  button_cnt:%d \n", button_cnt);
				}
				else if(g_player.dpad &  CONTROL_DPAD_L)
				{
					// g_player.dpad =0;
					//g_player.shoot_timer=PAUSE_DPAD_COUNTER;

					LOG_PAUSE("\n CONTROL_DPAD_L  button_cnt:%d \n", button_cnt);
				}

#endif




				for(cheat=0; cheat<CHEAT_TOTAL; cheat++)
				{
					//for(i=0; i<8; i++)
					{

						LOG_PAUSE("\n comparing g_player.dpad:%d allCheats[%d][1+%d]:%d\n", g_player.dpad, cheat, button_cnt, allCheats[cheat][1+button_cnt]);

						// process button
						if(button_cnt == allCheats[cheat][0]  // and make sure it's in order
														  && g_player.dpad  == allCheats[cheat][1+button_cnt]) //check dpad to list, starts at 1
						{
							LOG_PAUSE("\nCounting cheat #%d process checking:%d button_cnt:%d allCheats[cheat][0]: %d\n", cheat+1, button_cnt, button_cnt, allCheats[cheat][0]);
							allCheats[cheat][0]++;
							//check next cheat

						}


					}



				}
				g_player.dpad =0;
				g_player.shoot_timer=PAUSE_DPAD_COUNTER;



				button_cnt++;

			}






		}


	}

	for(cheat=0; cheat<CHEAT_TOTAL; cheat++)
	{ //process entered cheat
		i = allCheats[cheat][0];

		if(i==8)
		{
			LOG_PAUSE("\n cheat worked %d button_cnt %d \n", cheat, button_cnt);

			switch(cheat)
			{


			case 0:
				LOG_PAUSE("\n CHEAT_EGO_MODE - big heads -  \n");
				g_gamestate.cheat_big_heads = 1;
				MACRO_PLAY_STEREO_SFX(TOMMY_TALK_WHAT_EGO); // what ego is going on there
				//add_smart_bomb(); //clear bullets
				g_function_loop = update_game;
				amico_BGM_quiet_time(0);
				break;

			case 1:
				LOG_PAUSE("\n CHEAT_GOD_MODE -     bullets and health -  \n");
				g_gamestate.p_bullets = 10101010;
				g_gamestate.p_health =  10101010;
				//g_gamestate.p_score =   10101010;
				MACRO_PLAY_STEREO_SFX(TOMMY_TALK_JUST_NEED_THE_MONEY); // we just need the money
				//add_smart_bomb(); //clear bullets
				g_function_loop = update_game;
				amico_BGM_quiet_time(0);

				LOG_PAUSE("\n CCW x2- bullets and health cheat \n");
				break;


			case 2:
				LOG_PAUSE("\n CHEAT_UNLOCK_BOSSES  -    \n");
				g_unlocked_bosses_level = 1;

				add_smart_bomb(); //clear bullets
				g_gamestate.p_side	= g_player.frame=0;
				g_function_loop = update_intro;
				amico_BGM_quiet_time(0);
				MACRO_PLAY_STEREO_SFX(TOMMY_TALK_NOT_REAL_FRIENDS); // not real friends
				break;



			case 3:
				LOG_PAUSE("\n CHEAT_NEXT_LEVEL -   \n");
				g_gamestate.level++;


				//start 10; //good 60;
				//g_AI_shoot_dist +=  AI_SHOOT_DIST_INC;
				g_AI_shoot_dist = INIT_SHOOT_DIST + ( (1+g_gamestate.level)*AI_SHOOT_DIST_INC)  + g_gamestate.wave;


				//5;// 20;
				//g_AI_shoot_dist_center+= 3;

				// if(g_unlocked_bosses_level > 1)
				//	g_unlocked_bosses_level--;

				MACRO_PLAY_STEREO_SFX(TOMMY_TALK_HARDCORE_ELITIST); // hardcore elitist
				// add_smart_bomb(); //clear bullets
				g_function_loop = update_game;
				amico_BGM_quiet_time(0);

				break;




			case 4:
				LOG_PAUSE("\n CHEAT_VOICE   \n");

				if( voice_sample == SFX_LAST)
					voice_sample = 0;
				else
					voice_sample++;

				amico_play_SFX(voice_sample); // hardcore elitist
				break;




			case 5:
				LOG_PAUSE("\n CHEAT_VOICE_ \n");

				if( voice_sample == 0)
					voice_sample = SFX_LAST;
				else
					voice_sample--;

				amico_play_SFX(voice_sample); // hardcore elitist
				break;


			case 6:
				LOG_PAUSE("\n CHEAT_VOICE_LEFT  \n");
				amico_play_SFX(voice_sample); // hardcore elitist
				g_no_boss_flashing = 1;
				break;


			case 7:
				LOG_PAUSE("\n CHEAT_VOICE_RIGHT right x8 \n");
				amico_play_SFX(voice_sample); // hardcore elitist
				g_no_boss_flashing = 0;
				break;

			case 8:
				LOG_PAUSE("\n CHEAT_TESTING_MODE -  Left, Right X4 \n");
				g_gamestate.cheat_testing = 1;
				//game_reset();
				g_function_loop = update_game;
				amico_BGM_quiet_time(0);

				MACRO_PLAY_STEREO_SFX(TOMMY_TALK_SKIP_DEVELOPMENT);
				add_smart_bomb(); //clear bullets
				// amico_play_SFX(TOMMY_TALK_WHAT_EGO); // what ego is going on there
				break;

			case 9:  // CHEAT_ENDING 
				LOG_PAUSE("\n CHEAT_ENDING \n");
				g_gamestate.cheat_testing = 0;
				MACRO_SET_GAME_TO_FINAL_CREDITS
				amico_BGM_quiet_time(0);
				add_smart_bomb(); //clear bullets
				MACRO_PLAY_STEREO_SFX(TOMMY_TALK_OUT_OF_BUSINESS);

				break;


			default:
				LOG_PAUSE("\n error cheat \n");
				break;

			}



			for(i=0; i<CHEAT_TOTAL; i++)
				allCheats[i][0] = 0;

			//g_player.dpad =0;
			//g_player.shoot_timer=PAUSE_DPAD_COUNTER;
			button_cnt = 0;

			return;




		}

	}



	if(g_player.shoot_dpad)
	{
		// sort list again!
		//srand(g_game_counter);
		//qsort(&g_texture_map_shills[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		//qsort(&g_texture_map_haters[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		// srand(g_game_counter & 0xFF);

		g_function_loop = update_game;
		amico_BGM_quiet_time(0);
		button_cnt = g_player.shoot_dpad =0;
		g_player.shoot_timer=BUTTON_PRESS_TIME;
		MACRO_CLEAR_SCREEN

	}

	render_top();


	render_text(4, 240-8,        100, (char *)DATE_STRING ); //amico_text_continue();

}


void update_dead(void)
{

	char text[512];
	u32 acc_avg =0;
	LOG_GAME_WAVE("\n update_dead \n");


	// render_top();
	// render_map();
	// render_runner_hits();



	intern_do_C64_loading_screen();

	// render_runner( (t_runner*)&g_player, 3);//.frame, g_player.posX, g_player.posY,	g_player.dir & 1);

	amico_sprite( g_player.TPAGE, g_player.textU, g_player.textV,  4*8, 4*8,    50, 75,     315,   !(g_game_counter&128));
	amico_sprite( g_player.TPAGE, g_player.textU, g_player.textV,  4*8, 4*8,    320-50, 75,  315,     (g_game_counter&128));

	if(g_total_bullets_used == 0)
		g_total_bullets_used  =1;


	{


		u32 bull_avg = 0;
		u32 friends_saved_avg = 0;
		char scroll[1024];



#if 0
		acc = 	(u32) ( (float)((float)g_gamestate.level_bullets_hit / (float)g_gamestate.level_bullets_used) * 100.0);
		acc_avg = (u32) ( (float)((float)(g_total_bullets_hit+g_gamestate.level_bullets_hit)  / (float) (g_total_bullets_used+g_gamestate.level_bullets_used) ) * 100.0);
#else


		bull_avg = intern_calc_percent((s32)(g_total_bullets_hit+g_gamestate.level_bullets_hit),  (s32) (g_total_bullets_used+g_gamestate.level_bullets_used));

		friends_saved_avg = intern_calc_percent((s32)g_total_friends_saved,  (s32) g_total_friends );



		/*
			u32 hit = g_gamestate.level_bullets_hit << 8;
			u32 used = g_gamestate.level_bullets_used << 8;
			u32 av = (u32) ( g_total_bullets_hit  / g_total_bullets_used );


			acc_avg = av >> 8;
		 */
		// LOG_GAME_WAVE( "ACC hit/used=av %d/%d=%d %d \n", hit, used, av, acc_avg );



		LOG_GAME_WAVE( "g_total_friends_saved %d \n", g_total_friends_saved );
		LOG_GAME_WAVE( "g_total_friends %d \n", g_total_friends );
		LOG_GAME_WAVE( "friends_saved_avg %d \n", friends_saved_avg );

#endif

		//	printf( "ACC %d/%d=%d %d/%d=%d\n",g_gamestate.level_bullets_hit ,g_gamestate.level_bullets_used,acc, g_total_bullets_hit, g_total_bullets_used, acc_avg );

		// removed acc TMK
		// sprintf(scroll, "T:%d F:%d/%d/%d B:%d/%d=%d:%d =%d",time,  g_gamestate.level_friends_saved, g_gamestate.wave-1, friends_saved_avg, g_gamestate.level_bullets_hit, g_gamestate.level_bullets_used , acc, acc_avg,  friends_saved_avg + acc *( (g_gamestate.level+1)*2));




		sprintf(scroll, "%06d %09d LVL %02d-%02d F:%02d #:%02d",
				g_gamestate.time, g_gamestate.p_score,
				g_gamestate.level,g_gamestate.wave,
				friends_saved_avg, bull_avg);



		amico_rectangle(0, 0, 0,   0, 200, 320, 25);
		render_text(8,  202, 100, (char *) scroll); //scroll 63 chars that should be enough and safe



	}


	//	amico_rectangle(0, 0, 0,   0, 0, 320, 25);
	//	render_text(0,  10, 100, (char *) text); //scroll 63 chars that should be enough and safe




	//GAME OVER!
	amico_rectangle(0, 0, 0,      0, 120,     320, 18);




	if(g_gamestate.p_side == 0) // shill
		render_text(50, 125,        100, (char *) "-- YOUR SHILL'N IS OVER! --" ); //amico_text_continue();
	else
		render_text(50, 125,        100, (char *) "-- YOUR TROLL'N IS OVER! --" ); //amico_text_continue();



	if(g_gamestate.p_side == 0) // shill
		sprintf(text, (char *) "      BIG ANNOUNCEMENTS COMING SOON!");
	else
		sprintf(text, (char *) "   DELETE YOUR CHANNEL AND MOVE ON!");

	amico_rectangle(0, 0, 0,   0, 185, 320, 15);
	render_text(0,  188, 100, (char *) text); //scroll 63 chars that should be enough and safe


	if( (g_game_counter%128) == 0)
	{
		amico_stop_all_SFX();


		if(g_gamestate.p_side == 0) // shill
		{

			LOG_GAME_WAVE("g_gamestate.level %d g_gamestate.wave %d  (SFX_LAST-SFX_TOMMY_TALK) %d\n ", g_gamestate.level, g_gamestate.wave, (SFX_LAST-SFX_TOMMY_TALK) );

			if(g_gamestate.BG_MAIN&1)
				amico_play_SFX( TOMMY_TALK_PROMOTE_YOUR_CHANNEL  ); //promote your channel, make a reaction video
			else
				amico_play_SFX( TOMMY_TALK_GET_YOUR_NAME_IN_CREDITS  ); //promote your channel, make a reaction video

		}
		else
		{

			if(g_gamestate.BG_MAIN&1)
				amico_play_SFX(TOMMY_TALK_WHOS_LAUGHING_NOW  );//39 23 25 35
			else
				amico_play_SFX(TOMMY_TALK_WHY_DO_YOU_HATE_ME );//TOMMY_TALK_NEGATIVE_EVIL   ); // TOMMY_TALK_IT_DOESNT_MEAN_HELL  );//39 23 25 35


		}

		g_gamestate.BG_MAIN++;
	}




	if( (g_player.shoot_dpad &&  g_game_counter > 196) || g_game_counter > 4000) // continue
	{


		// sort list again!
		//srand(g_game_counter);
		//qsort(&g_texture_map_shills[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		//qsort(&g_texture_map_haters[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		g_function_loop = update_intro;
		g_game_counter =  g_player.dpad = g_player.shoot_dpad =0;
		//
		g_player.shoot_timer=BUTTON_PRESS_TIME*2;
		g_gamestate.p_side = 0xFF;
		// srand(g_game_counter & 0xFF);
		g_total_friends_saved = g_total_friends  = g_total_bullets_hit = g_total_bullets_used = g_player.frame  = g_game_counter = 0;

		add_smart_bomb();
		amico_stop_all_SFX();
		amico_BGM_quiet_time(0);
		// amico_play_BGM_audio(3);//intro
		MACRO_CLEAR_SCREEN
		MACRO_GAME_RESET_AND_RANDOMIZE_LIST

	}





	g_game_counter++;





}




void update_new_game_wave(void)
{
	char *friendName, *haterName, scroll[1024], haterString[128], freindString[128];

	u8 BF_TPAGE,BE_TPAGE;
	u8 BF_textU, BE_textU;
	u8 BF_textV, BE_textV;

	u32 i,wave, newlevel;
	LOG_GAME_WAVE("\n update_new_game_wave level:%d wave:%d\n", g_gamestate.level, g_gamestate.wave);


	// render_top();
	// render_map();
	// render_runner_hits();


	// g_gamestate.cheat_testing =1;

	if(g_gamestate.wave + g_gamestate.level == 0)// level zero
	{
		sprintf(scroll, "                      COME ALONG WITH THIS JOURNEY ####"); //GET READY FOR AMICO FAMILY FRIENDLY FUN!
		intern_do_C64_loading_screen();
	}
	else // normal loop
	{
		newlevel = g_gamestate.level;

		//if( g_gamestate.wave > BOSS_WAVE ) //boss wave!
		if( g_gamestate.wave > (MAX_SHILLS-g_unlocked_bosses_level) ) //boss wave!
			newlevel++;

		if(g_gamestate.wave > 1)
			wave = g_gamestate.wave-2; // -1 to get to zero base number, game starts at wave 1, and it's already been incremented
		else
			wave = 0;


		LOG_GAME_WAVE("\n update_new_game_wave level newlevel:%d wave:%d g_unlocked_bosses_level %d\n", newlevel, wave, g_unlocked_bosses_level);


		if(g_gamestate.p_side == SIDE_SHILL) // shill side
		{
			for(i=0;i<=(MAX_SHILLS); i++) // find shill name
			{

				if(
						g_AI_friends[wave].TPAGE == g_texture_map_shills[i].TPAGE &&
						g_AI_friends[wave].textU == g_texture_map_shills[i].textU &&
						g_AI_friends[wave].textV == g_texture_map_shills[i].textV

				)
				{
					BF_TPAGE = g_AI_friends[wave].TPAGE;
					BF_textU = g_AI_friends[wave].textU;
					BF_textV = g_AI_friends[wave].textV;

					friendName = (char *) g_texture_map_shills[i].name;
					break; // from loop
				}
			}

			for(i=0;i<=(MAX_SHILLS); i++) // find hater name
			{
				if(
						g_AI_enemies[wave].TPAGE == g_texture_map_haters[i].TPAGE &&
						g_AI_enemies[wave].textU == g_texture_map_haters[i].textU &&
						g_AI_enemies[wave].textV == g_texture_map_haters[i].textV

				)
				{
					BE_TPAGE = g_AI_enemies[wave].TPAGE;
					BE_textU = g_AI_enemies[wave].textU;
					BE_textV = g_AI_enemies[wave].textV;

					haterName = (char *) g_texture_map_haters[i].name;
					break; // from loop
				}
			}

		}
		else // hater
		{

			for(i=0;i<=(MAX_SHILLS); i++) // find name
			{


				if(
						g_AI_enemies[wave].TPAGE == g_texture_map_shills[i].TPAGE &&
						g_AI_enemies[wave].textU == g_texture_map_shills[i].textU &&
						g_AI_enemies[wave].textV == g_texture_map_shills[i].textV

				)
				{
					BE_TPAGE = g_AI_enemies[wave].TPAGE;
					BE_textU = g_AI_enemies[wave].textU;
					BE_textV = g_AI_enemies[wave].textV;
					friendName = (char *) g_texture_map_shills[i].name;
					break;// from loop
				}
			}

			for(i=0;i<=(MAX_SHILLS); i++) // find name
			{

				if(
						g_AI_friends[wave].TPAGE == g_texture_map_haters[i].TPAGE &&
						g_AI_friends[wave].textU == g_texture_map_haters[i].textU &&
						g_AI_friends[wave].textV == g_texture_map_haters[i].textV

				)
				{
					BF_TPAGE = g_AI_friends[wave].TPAGE;
					BF_textU = g_AI_friends[wave].textU;
					BF_textV = g_AI_friends[wave].textV;

					haterName = (char *) g_texture_map_haters[i].name;
					break;// from loop
				}


			}

		}// hater


		LOG_GAME_WAVE("wave %d friendName- %s haterName-%s\n",wave, friendName, haterName );
		//if(g_gamestate.p_side == SIDE_SHILL)


		switch(newlevel )
		{
		case 0:
			sprintf(haterString, "%s, JUST GIVE IT A CHANCE!",  haterName);
			sprintf(freindString, "%s, THANK YOU FOR YOUR THOUGHTS",  friendName);
			break;

		case 1:
			sprintf(haterString, ".... %s JUST NEEDS TO PLAY IT!",  haterName );
			sprintf(freindString, "I LIKE EVERYTHING ABOUT %s!",  friendName);
			break;


		case 2:
			sprintf(haterString, "ITS NOT FOR YOU %s AND THAT IS OKAY!",  haterName);
			sprintf(freindString, "%s, ARE YOUR PARENTS STILL ALIVE",  friendName);
			break;

		case 3:
			sprintf(haterString, "  ... THEN DONT BUY IT %s!",  haterName );
			sprintf(freindString, "EXCLUSIVE ANNOUNCEMENTS ON %s",  friendName );
			break;

		case 4:
			sprintf(haterString, " %s ARE YOU HIGH MY MAN!",  haterName );
			sprintf(freindString, "WE ARE THE UNDERDOGS %s!  ",  friendName );
			break;

		case 5:
			sprintf(haterString, "%s HAS NEVER MADE A CONSOLE!", haterName );
			sprintf(freindString, "%s... FREE T-SHIRTS AND HATS INCOMING",  friendName );
			break;

		case 6:
			sprintf(haterString, " %s WANTS TO DESTROY A SMALL COMPANY!",  haterName );
			sprintf(freindString, "WATCH! LIKE! AND SUBSCRIBE! TO %s.... ", friendName );
			break;

		case 7:
			sprintf(haterString, "%s OBSESSED HATER, I DONT LIKE YOU!",haterName );
			sprintf(freindString, "%s 90 PERCENT LAUNCH TITLE!",  friendName);
			break;

		case 8:
			sprintf(haterString, "%s LEGAL INCOMING!",  haterName );
			sprintf(freindString, "%s THE REAL MARKETING HASNT STARTED YET.... ",friendName );
			break;

		case 9:
			sprintf(haterString, "... %s NEEDS TO GET A LIFE!",  haterName );
			sprintf(freindString, "YES %s! THE DELAYS WILL MAKE IT BETTER!", friendName );
			break;



		case 10:
			sprintf(haterString, "%s IS A GAMING COMMUNIST RACIST",  haterName );
			sprintf(freindString, "%s... HIDE YOUR KIDS, HIDE YOUR WIFE ",  friendName);
			break;



		case 11:
			sprintf(haterString, "%s IS NEGATIVE AND EVIL!",  haterName );
			sprintf(freindString, "%s, WE ARE FOCUSED AND DETERMINED!!! ",  friendName);
			break;



		case 12:
			sprintf(haterString, "%s... HARASSES ME, MY FAMILY AND MY STAFF!!", haterName );
			sprintf(freindString, "%s IS FINALLY IN A VIDEO GAME CREDIT SCREEN! ",  friendName);
			break;

		case 13:
			sprintf(haterString, " ########",  haterName );
			sprintf(freindString, "IT'S QUIET TIME %s  ",  friendName);
			break;

		default:
			sprintf(haterString, " ####################" );
			sprintf(freindString, "%s GOODBYE MY FRIEND! ",  friendName);
			break;

		}




		//intern_do_C64_loading_screen();
		// C64 loading bards

		//TODO 1 LEVEL ENDING DISPLAY

		//if( g_gamestate.wave > (BOSS_WAVE) +1 ) //boss wave!
		if( g_gamestate.wave > (MAX_SHILLS-g_unlocked_bosses_level)+2 ) //boss wave!
		{


			LOG_GAME_WAVE("NEW LEVEL UNLOCKED! g_gamestate.wave %d wave %d friendName- %s haterName-%s\n", g_gamestate.wave, wave, friendName, haterName );
			if(g_no_boss_flashing == 0)
				intern_black_and_white_BG(g_game_counter & 4 );

			//if(g_gamestate.p_side == 0) // shill




			amico_sprite( BF_TPAGE, BF_textU, BF_textV,  4*8, 4*8,    50, 75,     315,   !(g_game_counter&128) );
			amico_sprite( BE_TPAGE, BE_textU, BE_textV,  4*8, 4*8,    320-50, 75,  315,     (g_game_counter&128) );




			if(g_game_counter&64)
			{
				sprintf(scroll, "## YOUR HARD WORK HAS UNLOCKED THEM! ##");

				amico_rectangle(0, 0, 0,   0, 225,  320, 15);
				render_text(5,  229, 100, (char *) scroll);
			}
			else
			{

				u32 p =  g_gamestate.level;

				if(p > 0)
				{
					//p =  p % 20;// only 15 URLs, cheats, messages 0-15
					p =  p * 41; // 41 char's each

				}

				g_LEVEL_FINISH_CHEAT[p+40] = 0; // replace x with null

				sprintf(scroll, "%s", &g_LEVEL_FINISH_CHEAT[p]);

				amico_rectangle(0, 0, 0,   0, 225,  320, 15);
				render_text(5,  229, 100, scroll);

			}




		}
		else
			intern_do_C64_loading_screen();





		sprintf(scroll, "                                             %s... %s! ", freindString, haterString);


	} // end of normal loop


	i = strlen(scroll);
	wave = (g_game_counter>>2) ;





	LOG_GAME_WAVE("%s %d \n", scroll, i);

	if(wave&1)
	{
		amico_sprite(01,    0, 0, 32, 64,      160,  120,     260 ,  0);
		// g_gamestate.BG_green = g_gamestate.BG_red = g_gamestate.BG_blue = 0;

	}
	else
	{
		amico_sprite(01,    0, 0, 32, 64,      160,   110+ 4,      300, 0);
		// g_gamestate.BG_green = g_gamestate.BG_red = g_gamestate.BG_blue = 100;

	}

	LOG_GAME_WAVE("wave %d %d \n", wave, i);

	wave = wave % i;

	amico_rectangle(0, 0, 0,   0, 165, 320, 15);
	render_text(0,  169, 100, (char *) scroll+ wave); //scroll 63 chars that should be enough and safe

	LOG_GAME_WAVE("wave %d \n", wave);

	if(wave == 0) // && g_game_counter < 2) // todo do once?
	{
		u32 sfx = g_gamestate.level+g_gamestate.wave; // get current number
		sfx %= (SFX_LAST-SFX_TOMMY_TALK); // limit it
		sfx += SFX_TOMMY_TALK; // add start
		g_game_counter+=4;

		amico_stop_all_SFX();
		LOG_GAME_WAVE("g_gamestate.level %d g_gamestate.wave %d  (SFX_LAST-SFX_TOMMY_TALK) %d\n ", g_gamestate.level, g_gamestate.wave, sfx );
		MACRO_PLAY_STEREO_SFX( sfx  );

	}

	LOG_GAME_WAVE("scroll g_game_counter %d %d %d \n",  g_game_counter, (g_game_counter>>1),wave);

	i *= 2;

	// show bonus
	//if(0)
	{


		s32 time = g_gamestate.time-g_game_start_time;

		u32 bulletperc = 0;
		//u32 acc_avg = 0;
		u32 friends_saved_avg = 0;

		if(g_gamestate.level_bullets_used && g_gamestate.wave > 1)
		{

#if 0
			acc = 	(u32) ( (float)((float)g_gamestate.level_bullets_hit / (float)g_gamestate.level_bullets_used) * 100.0);
			acc_avg = (u32) ( (float)((float)(g_total_bullets_hit+g_gamestate.level_bullets_hit)  / (float) (g_total_bullets_used+g_gamestate.level_bullets_used) ) * 100.0);
#else


			bulletperc = intern_calc_percent((s32)g_gamestate.level_bullets_hit,  (s32) g_gamestate.level_bullets_used );
			//acc_avg = intern_calc_percent((s32)(g_total_bullets_hit+g_gamestate.level_bullets_hit),  (s32) (g_total_bullets_used+g_gamestate.level_bullets_used));

			// friends_saved_avg = intern_calc_percent((s32)g_total_friends_saved,  (s32) g_total_friends );
			friends_saved_avg = intern_calc_percent((s32)	g_gamestate.level_friends_saved,(s32) g_gamestate.wave-1 );




			/*
			u32 hit = g_gamestate.level_bullets_hit << 8;
			u32 used = g_gamestate.level_bullets_used << 8;
			u32 av = (u32) ( g_total_bullets_hit  / g_total_bullets_used );


			acc_avg = av >> 8;
			 */
			// LOG_GAME_WAVE( "ACC hit/used=av %d/%d=%d %d \n", hit, used, av, acc_avg );
			LOG_GAME_WAVE( "ACC bulletperc %d \n", bulletperc );


			LOG_GAME_WAVE( "g_total_friends_saved %d \n", g_total_friends_saved );
			LOG_GAME_WAVE( "g_total_friends %d \n", g_total_friends );
			LOG_GAME_WAVE( "friends_saved_avg %d \n", friends_saved_avg );

#endif

			//	printf( "ACC %d/%d=%d %d/%d=%d\n",g_gamestate.level_bullets_hit ,g_gamestate.level_bullets_used,acc, g_total_bullets_hit, g_total_bullets_used, acc_avg );

			// removed acc TMK
			// sprintf(scroll, "T:%d F:%d/%d/%d B:%d/%d=%d:%d =%d",time,  g_gamestate.level_friends_saved, g_gamestate.wave-1, friends_saved_avg, g_gamestate.level_bullets_hit, g_gamestate.level_bullets_used , acc, acc_avg,  friends_saved_avg + acc *( (g_gamestate.level+1)*2));

			sprintf(scroll, "T%d %02d-%02d F%d/%d=%d #%d/%d=%d WIN:%04d",time,  g_gamestate.level, g_gamestate.wave, g_gamestate.level_friends_saved, g_gamestate.wave-1, friends_saved_avg, g_gamestate.level_bullets_hit, g_gamestate.level_bullets_used , bulletperc,  GAME_CALCULATE_END_WAVE_BONUS);

			amico_rectangle(0, 0, 0,   0, 0, 320, 25);
			render_text(3,  10, 100, (char *) scroll); //scroll 63 chars that should be enough and safe



			// display 10k bonus
			//if(0)
			if( g_gamestate.wave > (MAX_SHILLS-g_unlocked_bosses_level)+2 )
				;
			else
			{

				if( g_gamestate.p_score > g_game_CUR_BONUS)
				{

					if(g_gamestate.p_side == 0) // shill
						sprintf(scroll, "1010 SIGNAL BOOST SHILL BONUS %09d",g_gamestate.p_score+GAME_CALCULATE_BONUS);
					else
						sprintf(scroll, "1010 SOCIAL BOOST DRAMA BONUS %09d",g_gamestate.p_score+GAME_CALCULATE_BONUS);
					//sprintf(scroll, " NEVER GO FULL AMICO WARNING!! ");

				}
				else
					sprintf(scroll, "NO BOOST FOR U, %09d IS %d SHORT",g_gamestate.p_score, g_game_CUR_BONUS-g_gamestate.p_score);



				amico_rectangle(0, 0, 0,   0, 205, 320, 15);
				render_text(5,  209, 100, (char *) scroll); //scroll 63 chars that should be enough and safe

			}
		}




	}



	g_game_counter++;





	//TODO wave text cheat time	if(g_gamestate.cheat_testing)
#ifdef _RELEASE_
	// if(g_gamestate.cheat_testing)
	//	i = i << 1;
	i = i >> 2;
#else


#endif

	if(g_player.shoot_dpad &&  g_game_counter > i) // continue
	{
		// redo bonus on exit - once




		if(g_gamestate.level_bullets_used)
		{

			s32 time = g_gamestate.time-g_game_start_time;

			u32 bulletperc,friends_saved_avg;

			// do 10k bonus
			if( g_gamestate.wave > (MAX_SHILLS-g_unlocked_bosses_level)+2 )
			{

			}
			else if(g_gamestate.p_score > g_game_CUR_BONUS)
			{
				g_gamestate.p_score += GAME_CALCULATE_BONUS;
				g_game_CUR_BONUS = g_gamestate.p_score +INIT_BONUS_INCR; // next bonus
				g_gamestate.p_health += GAME_CALCULATE_BONUS;
				g_gamestate.p_bullets += GAME_CALCULATE_BONUS;
			}



#if 0
			acc = 	(u32) ( (float)((float)g_gamestate.level_bullets_hit / (float)g_gamestate.level_bullets_used) * 100.0);
#else
			//acc =  intern_calc_percent(g_gamestate.level_bullets_hit , g_gamestate.level_bullets_used);

			bulletperc =  intern_calc_percent((s32)g_gamestate.level_bullets_hit,  (s32) g_gamestate.level_bullets_used );

			// friends_saved_avg = intern_calc_percent((s32)g_total_friends_saved,  (s32) g_total_friends );

			friends_saved_avg = intern_calc_percent((s32)	g_gamestate.level_friends_saved,(s32) g_gamestate.wave-1 );

#endif




			LOG_GAME_WAVE( "g_total_friends_saved %d \n", g_total_friends_saved );
			LOG_GAME_WAVE( "g_total_friends %d \n", g_total_friends );
			LOG_GAME_WAVE( "friends_saved_avg %d \n", friends_saved_avg );

			g_total_bullets_used += g_gamestate.level_bullets_used;
			g_total_bullets_hit +=  g_gamestate.level_bullets_hit;

			g_total_friends_saved += g_gamestate.level_friends_saved;
			g_total_friends += g_gamestate.wave-1;


			//if(acc>0)
			{
				// g_gamestate.p_score +=	friends_saved_avg *( (g_gamestate.level+1)*10) +acc *( (g_gamestate.level+1)*10);
				g_gamestate.p_score += GAME_CALCULATE_END_WAVE_BONUS;

			}

		}

		// srand( (g_game_counter+g_gamestate.time) & 0xFFFF);
		g_game_counter = 0;
		amico_stop_all_SFX();

		//g_game_level_time = (g_gamestate.wave+1)*( (g_gamestate.level+1)*10); // next bonus time
		//g_game_level_time = ( (g_gamestate.wave+1) *100);
		//g_game_level_time /= (g_gamestate.level+1); // next bonus time

		g_gamestate.friend_alive = g_gamestate.friend_next = g_gamestate.enemy_alive = g_gamestate.enemy_next = \
				g_gamestate.level_friends_saved = g_gamestate.level_bullets_used = g_gamestate.level_bullets_hit = 0;
		g_game_start_time = g_gamestate.time+2; // new start time.

		// sort list again!
		//srand(g_game_counter);
		//qsort(&g_texture_map_shills[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		//qsort(&g_texture_map_haters[10], MAX_SHILLS-10, sizeof(t_data_head32 ), intern_rand_comparison);
		g_function_loop = update_game;
		g_player.dpad = g_player.shoot_dpad =0;
		g_player.shoot_timer=BUTTON_PRESS_TIME*2;



		LOG_GAME_WAVE2(" i %d!\n", i);
		LOG_GAME_WAVE2(" g_unlocked_bosses_level %d!\n", g_unlocked_bosses_level);

		LOG_GAME_WAVE2("  g_gamestate.wave   %d!\n",  g_gamestate.wave  );


		LOG_GAME_WAVE2(" (MAX_SHILLS-g_unlocked_bosses_level) %d!\n", ((MAX_SHILLS-g_unlocked_bosses_level)) );


		// check if completed wave was bosses
		//if( g_gamestate.wave > (BOSS_WAVE)+1  )
		if( g_gamestate.wave > (MAX_SHILLS-g_unlocked_bosses_level)+2 )
		{

			u32 speed = PLAYER_INIT_SPEED; // init speed



			intern_randomize_init_lists(); // reoder them?


			LOG_GAME_WAVE2("NEW g_unlocked_bosses_level %d!\n", g_unlocked_bosses_level);
			LOG_GAME_WAVE2("NEW g_gamestate.level %d!\n", g_gamestate.level);
			LOG_GAME_WAVE2("NEW g_gamestate.wave %d!\n", g_gamestate.wave);

			if(g_unlocked_bosses_level > 2)
			{
				g_unlocked_bosses_level--; // don't drop to 0??  the good/evil shell

				g_gamestate.level++;
				g_gamestate.wave = 1; // waves start at 1

				g_gamestate.p_score += GAME_CALCULATE_BONUS;
				g_gamestate.p_health += GAME_CALCULATE_BONUS;
				g_gamestate.p_bullets += GAME_CALCULATE_BONUS;
				// no reset at end of level g_game_CUR_BONUS = g_gamestate.p_score +INIT_BONUS_INCR; // next bonus

				//g_AI_shoot_dist +=  AI_SHOOT_DIST_INC;
				g_AI_shoot_dist = INIT_SHOOT_DIST + ( (1+g_gamestate.level)*AI_SHOOT_DIST_INC)  + g_gamestate.wave;

				//g_AI_shoot_dist_center+= 3;

				speed += NEW_LEVEL_PLAYER_SPEED_INC; //5; // loop to zero if over 255

#ifndef _DEBUG_
				//TODO				if(g_gamestate.level > 9 && g_gamestate.level < 14)
				//					g_gamestate.cheat_testing = g_gamestate.cheat_big_heads = 0; // clear cheats
#endif

				if(speed > 255)
					speed = 255;

				g_player.speed=speed;


			}
			else
			{

				// ending

				intern_randomize_init_lists();
				// g_game_counter=6401;
				//g_game_counter=14300;

				LOG_GAME_WAVE2("NEW MACRO_SET_GAME_TO_FINAL_CREDITS \n");

				MACRO_SET_GAME_TO_FINAL_CREDITS;

				LOG_GAME_WAVE2("NEW MACRO_SET_GAME_TO_FINAL_CREDITS 4\n");
				amico_BGM_quiet_time(0);
				LOG_GAME_WAVE2("NEW MACRO_SET_GAME_TO_FINAL_CREDITS 5\n");
				return;

			}


		}

		if(g_gamestate.wave + g_gamestate.level == 0) // finished level zero
		{
			MACRO_GAME_RESET_AND_RANDOMIZE_LIST
#if 1
			g_gamestate.wave++;
			// g_gamestate.p_score=g_gamestate.p_health=999999;
#else
#if 1
			//TODO 0 set new wave ending
			g_gamestate.level = 14;
			g_gamestate.wave=49;
			g_unlocked_bosses_level =2;
			g_gamestate.p_score=g_gamestate.p_health=999999;
#else
			//TODO 0 set new wave ending
			g_gamestate.cheat_testing =1;
			g_gamestate.level = 4;
			g_gamestate.wave=40;
			g_unlocked_bosses_level =16-4;
			g_gamestate.p_score=g_gamestate.p_health=999999;

#endif

#endif
		}



		// inc distance
		g_AI_shoot_dist = INIT_SHOOT_DIST + ( (1+g_gamestate.level)*AI_SHOOT_DIST_INC)  + g_gamestate.wave;

		//#define NO_SELF_DESTRUCTION
		// start corrupting level data
#ifndef NO_SELF_DESTRUCTION

		//	LOG_DEST("NO_SELF_DESTRUCTION level\n");

		if(g_gamestate.level > 9) // for lvl 10
		{
			u32 level = g_gamestate.wave-1;

			//u32 g_cur_map[MAX_LEVEL+1][15]
			LOG_DEST("\n");
			if(level >= 0)
			{
				u32 r;
				u32 new_row;
				LOG_DEST("\n\n");
				for(r=2;r<15;r++)
				{
					new_row = g_cur_map[level][r];

					if(new_row > 0)
					{

						if(rand() & 1)
						{
							new_row = new_row & (u32)rand();
							LOG_DEST("NO_SELF_DESTRUCTION L%d  R:%d g_cur_map[level][row] 0x%X  -> 0x%X \n",level, r, g_cur_map[level][r] , new_row );
							g_cur_map[level][r] = new_row; // remove blocks
						}


					}
				}
			}

			//else
			//	g_cur_map[level][row] = g_cur_map[level][row] | (u32)rand(); // add blocks


		}




#endif


		amico_save_data();// run before clear_screen! it'll freeze up a bit.
		amico_BGM_quiet_time(0);

		//testing intern_randomize_init_lists();

		MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
		MACRO_CLEAR_SCREEN


	}





}

void update_select(void)
{
	u32 drop  = g_game_counter>>7;
	s32 max_players;
	s32 min_players;
	char str[256]={0};

	// LOG_SELECT("\n update_select %p \n",g_function_loop);
	// g_player.dir++;


	//max_players = (BOSS_WAVE); //MAX_SHILLS-g_unlocked_bosses_level;
	max_players = MAX_SHILLS-g_unlocked_bosses_level;
	min_players = 0;


	if(g_player.frame == 0) // select a side
	{

		if(g_gamestate.p_side == 0) //shill
		{
			//shills
			amico_rectangle(113, 255, 255,  0, 32, 320,240-32);
			//screen.sprites = TPAGE01;
			//screen.sprite(Rect(g_texture_map_shills[0].textU, g_texture_map_shills[0].textV, 4, 4), Point(16, 32) ,  Point(0, 0), 4.0f, SpriteTransform::HORIZONTAL);
			// amico_sprite(01, g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,  32, 32,  64, 32+0,  600 , 0, 0);
			// side shell
			// amico_sprite( g_texture_map_shills[0].TPAGE, g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,  32, 32,  160, 140,  300 , 0, 0);
			amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,  32, 32,  160, 140,  300 ,  0);
			//screen.pen = Pen(0, 0, 0);
			//screen.text("-- Shill --", minimal_font,  Point(64+16+8, 240-64 ) ,  false, TextAlign::center_center);
			// screen.text("Personal friend of Tommy Tallarico and defender of Amico. ", minimal_font,  Point(10, 128 ) );
			/*
			amico_rectangle(0, 0, 0,     0, 0, 320, 32);
			//amico_text_top1_line("Choose your side:     -- Shill --");
			//amico_text_top2_line("       Friend and defender of Tommy Tallarico.");
			amico_text(2, 10, 100, "Choose your side!     -- Shill --");
			amico_text(2, 22, 100, "Friend and defender of Tommy Tallarico.");
			 */
			amico_rectangle(0, 0, 0,   0, 0, 320, 44);
			// amico_text_top1_line("Choose your side:     -- Hater --");
			// amico_text_top2_line("       Truth  and  memes   of Tommy Tallarico.");
			render_text(64-16, 10, 100, "CHOOSE YOUR SIDE -- SHILL --");
			render_text(8, 22, 100, "FRIEND AND DEFENDER OF TOMMY TALLARICO.");
			// render_text(160-50, 34, 100, "-- SHILL --");

#ifdef __NOT_USED__
			
			sprintf(str, "UP/DOWN FOR BGM VOLUME %03d/100", (g_SET_BGM_VOL*100) /255);
#else
			// 32blit VOL is 16bit 0-65535
			sprintf(str, "UP/DOWN FOR BGM VOLUME %03d/100", (u32) ( (g_SET_BGM_VOL/65535.0) * 100.0));
#endif

			render_text(64-16, 34, 100, str);



		}
		else
		{

			//haters
			amico_rectangle(186, 161, 127, 0, 32, 320,240-32);
			// screen.sprites = TPAGE03;
			// screen.sprite(Rect(g_texture_map_haters[0].textU, g_texture_map_haters[0].textV, 4, 4), Point(320-(128+15),  drop-128) ,  Point(0, 0), 4.0f, SpriteTransform::HORIZONTAL);
			// screen.sprite(Rect(g_texture_map_haters[0].textU, g_texture_map_haters[0].textV, 4, 4), Point(16, 32) ,  Point(0, 0), 4.0f, SpriteTransform::HORIZONTAL);
			//side shell
			//amico_sprite( g_texture_map_haters[0].TPAGE, g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32,    160, 140,  300 , 0, 0);

			amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,  32, 32,  160, 140,  300 ,  0);
			amico_rectangle(0, 0, 0,   0, 0, 320, 44);
			// amico_text_top1_line("Choose your side:     -- Hater --");
			// amico_text_top2_line("       Truth  and  memes   of Tommy Tallarico.");
			render_text(64-16, 10, 100, "CHOOSE YOUR SIDE -- HATER --");
			render_text(8, 22, 100,"SEARCH FOR TRUTH AND LOL ON INTV AMICO.");
			// render_text(160-50, 34, 100, "-- HATER --");


#ifdef __NOT_USED__
			
			sprintf(str, "UP/DOWN FOR SFX VOLUME %03d/100", (g_SET_SFX_VOL*100) /255);
#else
			// 32blit VOL is 16bit 0-65535
			sprintf(str, "UP/DOWN FOR SFX VOLUME %03d/100", (u32) ( (g_SET_SFX_VOL/65535.0) * 100.0));
#endif


			render_text(64-16, 34, 100, str);

		}

		//screen.pen = Pen(0, 0, 0);
		//screen.text("Choose your side ", minimal_font,  Point(160, 10 ) ,  false, TextAlign::center_center);

		if(g_player.shoot_dpad &  CONTROL_DPAD_D || g_player.shoot_dpad &  CONTROL_DPAD_L )
		{
			g_player.frame++;
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;
			g_player.posX = min_players;
			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);
			intern_randomize_init_lists();

			//g_game_counter =0;
		}
#if  1 //_DEBUG_ // no going back - that's cheating into the list - do a reset you dirty flip floppers! lol
		else	if(g_player.shoot_dpad &  CONTROL_DPAD_U)
		{
			g_player.frame=0;
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;
			g_player.posX =11;
			// srand( (g_game_counter+g_gamestate.time) & 0xFFFF);
			//g_game_counter =0;
		}

#endif

		if(g_player.shoot_timer > 0)
			g_player.shoot_timer--;
		else if(g_player.dpad &  CONTROL_DPAD_R ||
				g_player.dpad &  CONTROL_DPAD_L
		)
		{
			amico_stop_all_SFX();
			g_gamestate.p_side = (g_gamestate.p_side+1)&1;
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;
			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
			amico_BGM_quiet_time(0); // set BGM vol
			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);
			//g_game_counter =0;
		}
		else if(g_gamestate.p_side && g_player.dpad &  CONTROL_DPAD_D	)
		{
			amico_stop_all_SFX();
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;

			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);

			g_SET_SFX_VOL-=VOL_CHANGE;

			if(g_SET_SFX_VOL < VOL_CHANGE*2)
				g_SET_SFX_VOL = 0;



			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
			amico_BGM_quiet_time(0); // set BGM vol
			// amico_play_SFX( SFX_TOMMY_TALK+ (g_SET_SFX_VOL) % (SFX_LAST-SFX_TOMMY_TALK)    );
			//g_game_counter =0;
		}
		else if(g_gamestate.p_side && g_player.dpad &  CONTROL_DPAD_U	)
		{
			amico_stop_all_SFX();
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;

			g_SET_SFX_VOL+= VOL_CHANGE; // unsigned auto wraps


			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);

			if(g_SET_SFX_VOL > VOL_MAX-VOL_CHANGE*2)
				g_SET_SFX_VOL = VOL_MAX;

			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
			amico_BGM_quiet_time(0); // set BGM vol
			// amico_play_SFX( SFX_TOMMY_TALK+ (g_SET_SFX_VOL) % (SFX_LAST-SFX_TOMMY_TALK)     );
			//g_game_counter =0;
		}
		else if(!g_gamestate.p_side && g_player.dpad &  CONTROL_DPAD_D	)
		{
			amico_stop_all_SFX();
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;


			g_SET_BGM_VOL-=VOL_CHANGE;


			if(g_SET_BGM_VOL < VOL_CHANGE*2)
				g_SET_BGM_VOL = 0;

			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);

			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
			amico_BGM_quiet_time(0); // set BGM vol
			// amico_play_SFX( SFX_TOMMY_TALK+ (g_SET_SFX_VOL) % (SFX_LAST-SFX_TOMMY_TALK)    );
			// amico_play_BGM_audio(g_SET_BGM_VOL & 1);


			//g_game_counter =0;
		}
		else if(!g_gamestate.p_side && g_player.dpad &  CONTROL_DPAD_U	)
		{
			amico_stop_all_SFX();
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;


			g_SET_BGM_VOL+=VOL_CHANGE;


			if(g_SET_BGM_VOL > VOL_MAX-VOL_CHANGE*2)
				g_SET_BGM_VOL = VOL_MAX;

			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);

			MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
			amico_BGM_quiet_time(0); // set BGM vol
			// amico_play_SFX( SFX_TOMMY_TALK+ (g_SET_SFX_VOL) % (SFX_LAST-SFX_TOMMY_TALK)     );
			// amico_play_BGM_audio(g_SET_BGM_VOL & 1);
			//g_game_counter =0;
		}

		/* todo done BGM vol
		 *
INSTANCE u8 g_SET_BGM_VOL;

#ifdef __NOT_USED__
INSTANCE u8 g_SET_SFX_VOL; //max
INSTANCE u8 g_SET_BGM_VOL; //max

#else
INSTANCE u16 g_SET_SFX_VOL; //max
INSTANCE u16 g_SET_BGM_VOL; //max
#endif
		 *
		 */

		render_text(30, 240-25, 100, "TO CHANGE SFX VOL - UP AND DOWN");
		amico_rectangle(0, 0, 0,  0, 240-32, 320,32);
		g_game_counter++;
	}
	else if(g_player.frame == 1) // select a player
	{
		if(g_gamestate.p_side == 0) // select a shill
		{
			//shills
			// amico_rectangle(250, 250, 250,  0, 0,  320,240);
			amico_rectangle(113, 255, 255,  0, 32,  320,240-32);
			//			amico_rectangle(250, 250, 250,  0, 0,  320, 20);
			amico_rectangle(0, 0, 0, 0, 0, 320, 32);
			// amico_text_top1_line("Choose your player:");
			// amico_text_top2_line((char *)g_texture_map_shills[g_player.posX].name);
			render_text(8, 10, 100, "CHOOSE YOUR PLAYER!");
			render_text(8, 22, 100, (char *)g_texture_map_shills[g_player.posX].name);
			//screen.pen = Pen(0, 0, 0);
			//screen.text((char *)g_texture_map_shills[g_player.posX].name, minimal_font,  Point(160, 10 ) ,  false, TextAlign::center_center);
			/*
			switch( g_texture_map_shills[g_player.posX].TPAGE)
			{
			case 1:
				screen.sprites = TPAGE01;
				break;
			case 2:
				screen.sprites = TPAGE02;
				break;
			case 3:
				screen.sprites = TPAGE03;
				break;
			case 4:
				screen.sprites = TPAGE04;
				break;
			}
			screen.sprite(Rect(g_texture_map_shills[g_player.posX].textU, g_texture_map_shills[g_player.posX].textV, 4, 4), Point(128, 96) ,  Point(7, 7), 4.0f, SpriteTransform::HORIZONTAL);
			 */
			amico_sprite(g_texture_map_shills[g_player.posX].TPAGE, g_texture_map_shills[g_player.posX].textU, g_texture_map_shills[g_player.posX].textV, 32, 32,    160, 120+16,  600 , 1);
		}
		else // select a hater
		{
			//haters
			//amico_rectangle(250, 250, 250, 0, 0, 320,240);
			amico_rectangle(186, 161, 127,    0, 32, 320,240-32);
			amico_rectangle(0, 0, 0,     0, 0, 320, 32);
			// amico_text_top1_line("Choose your player:");
			// amico_text_top2_line((char *)g_texture_map_haters[g_player.posX].name);
			render_text(8, 10, 100,"CHOOSE YOUR PLAYER!");
			render_text(8, 22, 100,(char *)g_texture_map_haters[g_player.posX].name);

			//	screen.pen = Pen(0, 0, 0);
			//	screen.text((char *)g_texture_map_haters[g_player.posX].name, minimal_font,  Point(160, 10 ) ,  false, TextAlign::center_center);
			/*
			switch( g_texture_map_haters[g_player.posX].TPAGE)
			{
			case 1:
				screen.sprites = TPAGE01;
				break;
			case 2:
				screen.sprites = TPAGE02;
				break;
			case 3:
				screen.sprites = TPAGE03;
				break;
			case 4:
				screen.sprites = TPAGE04;
				break;
			}
			screen.sprite(Rect(g_texture_map_haters[g_player.posX].textU, g_texture_map_haters[g_player.posX].textV, 4, 4), Point(128, 96) ,  Point(7, 7), 4.0f, SpriteTransform::HORIZONTAL);
			 */
			amico_sprite(g_texture_map_haters[g_player.posX].TPAGE, g_texture_map_haters[g_player.posX].textU, g_texture_map_haters[g_player.posX].textV,  32, 32,    160, 120+16,  600 , 1);
		}
		g_game_counter++;

		if(g_player.shoot_dpad &  CONTROL_DPAD_D || g_player.shoot_dpad &  CONTROL_DPAD_L)
		{
			// g_player.frame--; back a screen?
			if(!g_gamestate.p_side)
			{
				amico_play_BGM_audio(g_gamestate.p_side);
				g_player.TPAGE = g_texture_map_shills[g_player.posX].TPAGE;
				g_player.textU = g_texture_map_shills[g_player.posX].textU;
				g_player.textV = g_texture_map_shills[g_player.posX].textV;
			}
			else
			{
				amico_play_BGM_audio(g_gamestate.p_side);
				g_player.TPAGE = g_texture_map_haters[g_player.posX].TPAGE;
				g_player.textU = g_texture_map_haters[g_player.posX].textU;
				g_player.textV = g_texture_map_haters[g_player.posX].textV;
			}

			g_player.shoot_timer = g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME*2;
			// g_player.posX = g_player.posY = 128<<6;
			g_player.dir = 1;
			g_player.posX = MAP_START_PLAYER_POSX;
			g_player.posY = MAP_START_PLAYER_POSY;
			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);
			g_game_counter =0;
			MACRO_GAME_RESET_AND_RANDOMIZE_LIST
			// g_function_loop = update_game;

			amico_BGM_quiet_time(0);

			g_gamestate.cheat_big_heads =1;
			g_function_loop = update_level_zero;
			MACRO_CLEAR_SCREEN

		}
		else if(g_player.shoot_dpad &  CONTROL_DPAD_U || g_player.shoot_dpad &  CONTROL_DPAD_R)
		{
			g_player.frame=0;
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;
			g_player.posX =min_players;
			// srand( (g_game_counter+g_player.frame+min_players+g_gamestate.time) & 0xFFFF);
			//g_game_counter =0;
		}

		if(g_player.shoot_timer > 0)
			g_player.shoot_timer--;
		else if(g_player.dpad &  CONTROL_DPAD_R  || g_player.dpad &  CONTROL_DPAD_U )
		{

			LOG_SELECT("g_player.posX %d ,  ", g_player.posX );

			g_player.posX++;
			if(g_player.posX > max_players )
				g_player.posX = min_players;

			LOG_SELECT(" %d \n ", g_player.posX );

			// srand(g_game_counter+min_players+g_player.posX);

			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;
			//g_game_counter =0;
			// amico_play_SFX(g_player.posX-11, SFX_HIT_ENEMY_VOL);

			{
				u32 track = g_player.posX;
				track = track % (SFX_TOMMY_TALK-1);
				amico_stop_all_SFX();
				amico_play_SFX(track);
			}



		}
		else if(g_player.dpad &  CONTROL_DPAD_L || g_player.dpad &  CONTROL_DPAD_D)
		{
			s32 test = (s32)g_player.posX;


			LOG_SELECT("down %d,  ", test );

			test--;
			if(  test <  min_players)
				g_player.posX = max_players;
			else
				g_player.posX--;

			LOG_SELECT("  %d  \n ", g_player.posX );
			g_player.shoot_dpad =0;
			g_player.shoot_timer=BUTTON_PRESS_TIME;


			// srand(g_game_counter+min_players+g_player.posX);

			{
				u32 track = g_player.posX;
				track = track % (SFX_TOMMY_TALK-1);
				amico_stop_all_SFX();
				amico_play_SFX(track);
			}

		}


	}
}
// 8x8
// 0: A - P
// 8: Q - Z - arrows, $ $
// 16: 0 - 9 - . ? ! music
// 24: heart1, 2 checkers5, 6 bull

#define CHAR_SPACE 8
void render_text(u32 posX, u32 posY, s32 scale, char *string)
{
	u32 i, len, U, V;
	u8 c;

	LOG_TEXT("posX %d, posY %d, scale %d, %s \n", posX,  posY,  scale, string);

	// hack
#ifdef __NOT_USED__
	scale -= 5;
	posX+=4;
	posY+=4;
#else
	posX+=2;
	posY+=4;
#endif

#if 0

	if((u32) string < 32) // single special char - yes, using a pointer as an uint...
	{
		// ARROWS $ $
		/// HERE
		// 24: heart1, 2 checkers5, 6 bull
		U = 0;
		V = 24;
		U += FONT_Y_OFFSET; // start Y
		amico_sprite(FONT_TPAGE,          U, V, 8, 8,         posX,     posY,    scale , 0, 0);
		return;
	}
#endif

	// process string ------------
	len=strlen(string);

	LOG_TEXT("len=strlen(string); %d  \n", len);


	if(len > 40) //limit string to screen width
		len = 40;

	for(i=0;i<len; i++)
	{
		c = string[i];

		LOG_TEXT("i: %d c: %c \n", i, c);


		if(c == 32) //space
		{
			posX+=CHAR_SPACE;
			continue;
		}

		//first mostlikely cases
		if(c > 47 && c < 58) // 0-9 zero digit
		{
			U = 8 * (c - '0');
			V = 16;
		}
		else if(c > 64 && c < 81) // A - P
		{
			U = 8 * (c - 'A');
			V = 0;
		}
		else if(c > 80 && c < 91) // Q - Z
		{
			U = 8 * (c - 'Q');
			V = 8;
		}
		// special string chars -.!$?
		else if(c == '-')
		{
			U = 8 * 10;
			V = 16;
		}
		else if(c == '.')
		{
			U = 8 * 11;
			V = 16;
		}
		else if(c == '?')
		{
			U = 8 * 12;
			V = 16;
		}
		else if(c == '!')
		{
			U = 8 * 13;
			V = 16;
		}
		else if(c == '$')
		{
			U = 8 * 14;
			V = 8;
		}
		else if(c == '/')
		{
			U = 8 * 10;
			V = 8;
		}
		else if(c == '=')
		{
			U = 8 * 11;
			V = 8;
		}
		else if(c == ',')
		{
			U = 8 * 12;
			V = 8;
		}
		else if(c == '@') // Smile face
		{
#if 0
			if( ( (u32)string&1) == 0)
				U = 8 * 13;
			else
				U = 8 * 14;
#endif
			U = 8 * 13;
			V = 8;
		}
		else if(c == '$')
		{
			U = 8 * 14;
			V = 8;
		}

		//last row 8*3=24
		else if(c == '+')
		{
			U = 8 * 7;
			V = 24;
		}


		else if(c == ':')
		{
			U = 8 * 8;
			V = 24;
		}


		else if(c == '\'')
		{
			U = 8 * 9;
			V = 24;

		}



		else if(c == '(')
		{
			U = 8 * 10;
			V = 24;

		}
		else if(c == ')')
		{
			U = 8 * 11;
			V = 24;
		}
		else if(c == '#') // heart
		{

#ifdef __NOT_USED__
			if( ( (u32)string&1) == 0)
#else
				if( ( (u32)i&1) == 0)
#endif


					U = 8;
				else
					U = 0;

			V = 24;
		}
		else if(c == '_')
		{
			U = 16;
			V = 24;
		}
		else if(c == '[')
		{
			U = 32;
			V = 24;
		}
		else if(c == ']')
		{
			U = 40;
			V = 24;
		}
		else
			//95 underscore
			//			if(c > 96) // small caps chars
		{
			printf(" len %d  (%d char %c) Char lower case! string %s\n",len,  c, c, string);
			printf(" len %d  (%d char %c) Char lower case! string %s\n",len,  c, c, string);
			printf(" len %d  (%d char %c) Char lower case! string %s\n",len,  c, c, string);
			printf(" len %d  (%d char %c) Char lower case! string %s\n",len,  c, c, string);
			printf(" len %d  (%d char %c) Char lower case! string %s\n",len,  c, c, string);

			exit(0);//c -= 32; // turn into big capitals
		}



		V += FONT_Y_OFFSET; // start Y 224
		amico_sprite(FONT_TPAGE,   U, V, 8, 8,    posX,     posY,    scale ,  0);
		posX+=CHAR_SPACE;
	}
}
void render_runner(t_runner* runner, u32 side)
{
	s32 posX = -16 + (runner->posX>>6);// -16 mid head
	s32 posY = -16 + (runner->posY>>6); // -16 mid runner
	u32 dir = (u32)  runner->dir;
	u32 dpad = runner->dpad;
	u32 frame = runner->frame>>5;



	if(dpad == 0 )// no input
	{
		//runner->dir = dir =  runner->old_dir;// keep old dir, for this frame, and next
		//runner->frame =32; //shoot frame?
	}
	else
		runner->frame+=	runner->speed>>1;// update frame if moving



	if(side == 3) // player
		side = 0;
	else
	{

		if(g_gamestate.p_side ) // SIDE_HATER
		{

			//flip the runner colours.. hacky
			if(side == 1)
				side = 2;
			else
				side = 1;
		}

		if(frame&2) // beat
		{
			//if(g_game_counter&1) // flash
			side = 0;
		}

	}


	posX += 8; //mid

	//dir = dir & 1;
	//screen.alpha = 255;
	//if(1) // render runner
	{
		// if(frame>6)
		{
			//runner->frame = frame = 0;
			//runner->frame = runner->speed=0;
		}
		//screen.sprites = TPAGE03;//run anim
		//screen.sprite(Rect(0,frame*4, 4, 4), Point(posX+(frame&1), posY+14.f) , Point(0, 0), 0.5f, dir);
		amico_sprite( 5,    side * 32,  frame*32,  32, 32,   (posX+(frame&1)), 8+( posY+14 ),     50, dir);
	}
	//if(1) // render head
	{
		u32 u = (u32) runner->textU;
		u32 v = (u32) runner->textV;
		s32  headforward = 4;

		if(dir)
			headforward=-headforward; // reverse for right dir;
		// screen.sprite(Rect(u,v, 4, 4), Point(posX-headforward, posY-(frame&1) ), Point(0, 0), 0.5f, dir );


		if(g_gamestate.cheat_big_heads )
		{
			headforward *=2;

			amico_sprite( runner->TPAGE,    u, v,  32, 32,  posX-headforward, posY-(frame&1),     100, dir);
		}
		else
			amico_sprite( runner->TPAGE,    u, v,  32, 32,  (posX-headforward), (8+posY)-(frame&1),     50, dir);

	}




}
void render_bullets(void)
{
	u32 i, r, g, b;
	u32 test;
	//screen.alpha = 255;
	//screen.sprites = TPAGE04;//map


	for(i=0; i<MAX_ENTITIES; i++)
	{
		test = g_bullets[i].posX;
		if(test)
		{
			//g_bullets[b].posX += g_bullets[b].speed;
			//g_bullets[b].posY += g_bullets[b].speed;
			test = game_collision_move((t_runner *) &g_bullets[i], 8, 8, 2, 0);
			if(test)
			{
				// screen.sprite(Rect(31,3, 1, 1), Point(g_bullets[b].posX/64.f, g_bullets[b].posY/64.f)); // , Point(0, 0), 0.5f, dir);
				//amico_sprite( 4, 31*8, 3*8, 1*8, 1*8,     8+(g_bullets[b].posX>>6), 8+(g_bullets[b].posY>>6) ,     100, 0, 0);
				// amico_sprite( 4, 7*16, 1*16, 1*8, 1*8,     8+(g_bullets[b].posX>>6), 8+(g_bullets[b].posY>>6) ,     100, 0, 0);
				// texture = 	(&g_player == g_bullets[b].owner)? 1:0; // if it's the player not (zero if the player)
				//texture = 7;
				// texture = 	++g_bullets[b].sprite >> 7; //0-3
				//texture+=3;

#ifdef LOG_DEBUG_COL


#else
				// heart bullet
				// amico_sprite( 4,  texture*8,3*8, 1*8, 1*8,    8+(g_bullets[b].posX>>6), 8+(g_bullets[b].posY>>6) ,     100, 0, 0);


				// amico_rectangle(255, 255, 255, 2+(g_bullets[b].posX>>6), 2+(g_bullets[b].posY>>6), 4, 4 );
				/*
				if(texture & 1)
					amico_rectangle(255, 255, 255,   8+(g_bullets[b].posX>>6), 8+(g_bullets[b].posY>>6), 4, 4 );
				else
					amico_rectangle(0, 0, 0,   8+(g_bullets[b].posX>>6), 8+(g_bullets[b].posY>>6), 4, 4 );
				 */


				if(g_game_counter & 1)
				{
					r = g = b = 127;
				}
				else
				{
					r = g = b = 64;
				}
				amico_rectangle(r,g,b,   8+(g_bullets[i].posX>>6), 8+(g_bullets[i].posY>>6), 4, 4 );
#endif



				if(game_bullet_runner_collision( &g_bullets[i]) )
					g_bullets[i].posX =0;



			}
			else //bullet dead
			{
				add_fires(g_bullets[i].posX, g_bullets[i].posY );
				g_bullets[i].posX = 0;
			}
		}
	}
}
void render_top(void)
{

	char line[64];


	// do sides
	{
		//u8 var = g_gamestate.BG_SIDES;
		// TOP
		amico_rectangle(0, 0,0,  0, 0,        320, MAP_BOUNDING_TOP);
		// BOT
		//amico_rectangle(0, 0, 0, 0, 240-MAP_BOUNDING_BOT,   320, MAP_BOUNDING_BOT);

		//SIDES
		//amico_rectangle(100, 100,var, 0, 0, MAP_BOUNDING_SIDES, 240);
		//amico_rectangle(100, 100,var, 320-MAP_BOUNDING_SIDES, 0, MAP_BOUNDING_SIDES, 240);
	}






	//TODO: 32blit error! g_gamestate.wave > 100
	if(g_gamestate.wave > 100)
	{
		printf("32blit error! g_gamestate.wave > 100\n");
		exit(1);
	}



	// sprintf(line_bot, "Lvl %03d Score %d Time %d %p",g_gamestate.phase, g_gamestate.p_score, g_gamestate.time, g_game_counter);
	//36 sprintf(line_bot, "Lvl %03d Score %d Time %d F%d-A%d E%d-A%d",g_gamestate.phase, g_gamestate.p_score, g_gamestate.time, g_gamestate.friend_next, g_gamestate.friend_alive, g_gamestate.enemy_next, g_gamestate.enemy_alive);

	sprintf(line, "%06d %09d LVL %02d-%02d/%02d F%02d/%02d",  g_gamestate.time, g_gamestate.p_score,  g_gamestate.level,g_gamestate.wave,  g_gamestate.level_friends_saved, g_gamestate.friend_next, g_gamestate.friend_alive);
	render_text(12, 10, 100, line );

	// sprintf(line_top, "BUL %03d HLTH %03d  F%d-A%d E%d-A%d", g_gamestate.p_bullets, g_gamestate.p_health, g_gamestate.friend_next, g_gamestate.friend_alive, g_gamestate.enemy_next, g_gamestate.enemy_alive);
	sprintf(line,    "# %08d @ %08d %03d/%03d E%02d/%02d", g_gamestate.p_bullets, g_gamestate.p_health,   g_gamestate.level_bullets_hit, g_gamestate.level_bullets_used, g_gamestate.enemy_next, g_gamestate.enemy_alive);
	render_text(12, 20, 100, line );



	// render_text(12, 231, 100, line_bot);



#if 0
	amico_rectangle(TOP_PANEL_R, TOP_PANEL_G, TOP_PANEL_B, 0, 0,320, 32);
	render_text(2, 10, 100, "test TesT -.!$? 0123456789 00");
	render_text(122, 128, 400, (char *)1);
	//amico_text_top1_line(  "12345678901234567890123456789012345678901234567890123456789012345678901234567890" );
	//amico_text_top2_line(  "12345678901234567890123456789012345678901234567890123456789012345678901234567890" );
#endif
}


// this should be a dynamic generated TMD
void render_map(void)
{
	u32 r,c,byte;
	u32 posX, posY;
	u32  data, cell;

	//	screen.alpha = 255;
	//	screen.sprites = TPAGE04;//map
	if( g_gamestate.p_side) // hater
	{

		// center
		//amico_sprite(g_texture_map_haters[0].TPAGE, g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32, 	160, 120,  75 + (g_game_counter&9) , 0, 0);
		amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,   32, 32, 	  160, 120+20,  75 + (g_game_counter&9) , 0 );
		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_BOT_LEFT > 0;

		// bottom left
		//amico_sprite(g_texture_map_shills[0].TPAGE, g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,  32, 32,  	18,  240-24,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,   32, 32,  	12,  240-10,  75 + (10*c) ,  0);
		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_TOP_LEFT > 0;

		// top left
		// amico_sprite(g_texture_map_haters[0].TPAGE, g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32, 	18, 64-18,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,    32, 32, 	12, 64-20,  75 + (10*c) , 0);

		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_TOP_RIGHT > 0;
		// top right
		// amico_sprite(g_texture_map_haters[0].TPAGE, g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32,  	 320-18, 64-18,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,    32, 32,  	 320-12, 64-20,  75 + (10*c) ,  0);


		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_BOT_RIGHT > 0;
		// bottom right
		// amico_sprite(g_texture_map_haters[0].TPAGE, g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32,  	 320-18, 240-24,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,  32, 32,  	 320-12, 240-10,  75 + (10*c) ,  0);
	}
	else // shill
	{

		// center
		//amico_sprite(g_texture_map_shills[0].TPAGE, g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,  32, 32, 	160, 120,  75 + (g_game_counter&8) , 0, 0);
		amico_sprite(AMICO_GOOD_SHELL_TPAGE, AMICO_GOOD_SHELL_TEXTU, AMICO_GOOD_SHELL_TEXTV,    32, 32, 	160, 120+20,  75 + (g_game_counter&8) ,  0);

		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_BOT_LEFT > 0;

		// bottom left
		// amico_sprite(g_texture_map_haters[0].TPAGE, g_texture_map_haters[0].textU, g_texture_map_haters[0].textV,  32, 32,  	18, 240-24,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,    32, 32,  	12, 240-10,  75 + (10*c) ,  0);
		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_TOP_LEFT > 0;

		// top left
		//amico_sprite(g_texture_map_shills[0].TPAGE, g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,   32, 32, 	18, 64-18,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,     32, 32, 	12, 64-20,  75 + (10*c) ,  0);

		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_TOP_RIGHT > 0;

		// top right
		// amico_sprite(g_texture_map_shills[0].TPAGE, g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,   32, 32,  	 320-18, 64-18,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,     32, 32,  	 320-12, 64-20,  75 + (10*c) ,  0);

		c = g_gamestate.shell_corners&MAP_SHELL_CORNER_BOT_RIGHT > 0;

		// bottom right
		//amico_sprite(g_texture_map_shills[0].TPAGE, g_texture_map_shills[0].textU, g_texture_map_shills[0].textV,   32, 32,  	 320-18, 240-24,  75 + (10*c) , 0, 0);
		amico_sprite(AMICO_BAD_SHELL_TPAGE, AMICO_BAD_SHELL_TEXTU, AMICO_BAD_SHELL_TEXTV,    32, 32,  	 320-12, 240-10,  75 + (10*c) ,  0);

	}

	// if( g_game_counter&1024 )
	// 	g_gamestate.shell_corners++;
	{

		u32 level = g_gamestate.level + g_gamestate.wave;


		level = level % MAX_LEVEL;


		for(r=0; r<15;r++)
		{
			posY = r *16;
			posX=0;
			data =  g_cur_map[level ][r];
			for(byte=0; byte<20;byte++)
			{
				cell= data & (1<< byte);
				//cell = cell & 3; // 2 bits
				cell = cell>0;
				//cell++; // add level for unique tiles
				// screen.sprite(Rect(0,cell*2, 2, 2), Point(posX, posY)); // , Point(0, 0), 0.5f, dir);
				// amico_sprite( 4,    0,  cell*2*8,  2*8, 2*8,    posX+8, posY+8,     100, 0, 0);
				// 	amico_sprite( 4,   16, cell*16,  16, 16,    posX+8, posY+8,     100, 0, 0);
				//brick	2	32	224


				if(cell)
					amico_sprite( MAP_BRICK_TPAGE,  MAP_BRICK_U, MAP_BRICK_V,  32, 32,    posX+8, posY+8,     50,  0);

				posX+=16;
			}
		}
	}


}

void amico_secret_end(void)
{

	s32 i;

	LOG_FIN_TEXT("amico_secret_end %d\n", g_game_counter);



	g_game_counter++;
	i =   ( (g_game_counter)&0x1FF);


	intern_do_C64_loading_screen();


	//amico_sprite(3,   0, 0,    32, 256,    160, (511 -( (g_game_counter)&0x1FF))*2,    200, 1);

	if( i < 256)
		amico_sprite(3,          0, 0,       16, 128,       160, 130,      150, 0);

	else if( i < 512)
		amico_sprite(3,          16, 0,       16, 128,       160, 130,      150, 0);




	if( g_game_counter > 4048) // repeat a few times then exit
	{
		amico_play_BGM_audio(3);//intro
		MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);

		add_smart_bomb();
		g_player.dpad = g_player.shoot_dpad =0;
		g_player.shoot_timer=BUTTON_PRESS_TIME*2;
		g_function_loop = update_dead;

	}
}


void update_final_credits(void)
{


	u32 youtuber;
	u32 side;
	u32 textlen;



	youtuber = g_game_counter>>7;
	side = g_game_counter>>6;

	if(side > 255)
		side = g_game_counter>>7; // used as 8bit


	LOG_FIN_TEXT2("update_final_credits FINTXT: g_gamestate.cheat_testing  %d   youtuber %d side %d textlen %d \n", g_gamestate.cheat_testing  ,  youtuber, side, textlen );


	// g_gamestate.cheat_testing = 0;

	// over right the intro message with out message



	LOG_FIN_TEXT2("\n\n");

	LOG_FIN_TEXT2("SFX_AMICO_AGAIN leaving! if(g_game_counter < 2) 1 g_game_counter %d  \n", g_game_counter);

	if(g_game_counter > 20)
	{

		//screen.alpha = 255;
		youtuber %= (MAX_SHILLS); // loop
		//i =  (MAX_SHILLS-1)- i; // backwards


		LOG_FIN("\n update_final_credits g_game_counter > 20 %d i  %d side %d \n", g_game_counter, youtuber , side);


		amico_rectangle( 0, 0, 0,   0, 0, 320,240 ); 

		if(g_game_counter&1)
			intern_black_and_white_BG(g_game_counter&4);
		else
			intern_do_C64_loading_screen();



#if 0 // remove playing intro on repeat


#ifdef __NOT_USED__
		if(( g_game_counter  % 2382 ) == 0)
#else
			if(( g_game_counter % 2200 ) == 0)
#endif

			{
				LOG_FIN("SFX_AMICO_AGAIN & reseting BGM played %d \n", g_game_counter);
				amico_play_BGM_audio(3);//intro
				//AMICO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
				//g_gamestate.wave = 0;
			}
			else

#endif
			{ // play TT talk

				s32 SFX;// =  (g_gamestate.level) + (g_gamestate.wave);// - (MAX_SHILLS-g_unlocked_bosses_level));

				//printf("level %d g_gamestate.wave %d  g_gamestate.enemy_next %d\n",level, g_gamestate.wave , g_gamestate.enemy_next);

				// amico_BGM_quiet_time(1); // should be put somewhere better!



				if(g_gamestate.wave != side)
				{
					g_gamestate.wave = side;

					// SFX = side % ((SFX_LAST-SFX_AMICO_AGAIN)+1); // allowable SFX
					// SFX = side % ((SFX_LAST-SFX_AMICO_AGAIN)+2); // removed +2 to get 10 10 amico again
					SFX = side % ((SFX_LAST-SFX_AMICO_AGAIN)+2); // removed +2 to get 10 10 amico again
					//SFX += SFX_AMICO_AGAIN;
					SFX =SFX_LAST - SFX;
					//SFX++;
					LOG_FIN(" SFX %d \n",SFX);
					/*
				SFX = SFX % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX
				LOG_FIN("level %d level % (SFX_LAST-SFX_AMICO_AGAIN); // allowable SFX\n",SFX);

				SFX += SFX_AMICO_AGAIN+1; // move to after amico again SFX
				LOG_FIN("level %d evel += SFX_AMICO_AGAIN; // move to after amico again SFX \n",SFX);

				SFX -= 1; // remove extra from below
				LOG_FIN("level %d level -= ADD_TO_SFX; // remove extra from below	\n",SFX);


					 */

					if(SFX <= SFX_AMICO_AGAIN)
						;// skip the first amico again, the last is too long
					else
					{
						if(g_gamestate.time & 1) // shill
							amico_play_SFX( SFX  ); //promote your channel, make a reaction video
						else
						{
#ifdef __NOT_USED__
							if(SFX > SFX_LAST-2) //last two (46/47) are long! don't repeat
								;// do nothing
#else
							if(SFX >  47-2) //use playstations numbers
								;// do nothing
#endif
							else
							{
								if(SFX == SFX_LAST) // shill
									amico_play_SFX( SFX_LAST   ); //promote your channel, make a reaction video
								else
									amico_play_SFX(  SFX-1 ); //promote your channel, make a reaction video
							}
						}
					}

				}



				g_gamestate.BG_MAIN++;

			}// play TT talk




	}


	LOG_FIN_TEXT2("SFX_AMICO_AGAIN leaving! if(g_game_counter < 2)2 g_game_counter %d  \n", g_game_counter);


	//if(temp_str) // if real end
	//	g_text_scroll_counter=textlen-g_game_counter; // (100+g_game_counter);  // don't do backwards

	intern_do_flashing_heads( side,  youtuber, 1);

	LOG_FIN_TEXT2("SFX_AMICO_AGAIN leaving! if(g_game_counter < 2)2 g_game_counter %d  \n", g_game_counter);

	g_game_counter--;

	intern_update_time();
	LOG_FIN_TEXT2("SFX_AMICO_AGAIN leaving! if(g_game_counter < 2)2 g_game_counter %d  \n", g_game_counter);


	amico_sprite( g_player.TPAGE, g_player.textU, g_player.textV,  4*8, 4*8,    50,   240-(80+16),     315,   !(g_game_counter&128) );
	amico_sprite( g_player.TPAGE, g_player.textU, g_player.textV,  4*8, 4*8,    320-50,  240-(80+16),  315,     (g_game_counter&128) );

	LOG_FIN("%d\n", g_game_counter);




	if(g_total_bullets_used == 0)
		g_total_bullets_used  =1;

	// score
	{


		u32 bull_avg = 0;
		u32 friends_saved_avg = 0;
		char scroll[1024];



#if 0
		acc = 	(u32) ( (float)((float)g_gamestate.level_bullets_hit / (float)g_gamestate.level_bullets_used) * 100.0);
		acc_avg = (u32) ( (float)((float)(g_total_bullets_hit+g_gamestate.level_bullets_hit)  / (float) (g_total_bullets_used+g_gamestate.level_bullets_used) ) * 100.0);
#else


		bull_avg = intern_calc_percent((s32)(g_total_bullets_hit+g_gamestate.level_bullets_hit),  (s32) (g_total_bullets_used+g_gamestate.level_bullets_used));

		friends_saved_avg = intern_calc_percent((s32)g_total_friends_saved,  (s32) g_total_friends );



		/*
				u32 hit = g_gamestate.level_bullets_hit << 8;
				u32 used = g_gamestate.level_bullets_used << 8;
				u32 av = (u32) ( g_total_bullets_hit  / g_total_bullets_used );


				acc_avg = av >> 8;
		 */
		// LOG_GAME_WAVE( "ACC hit/used=av %d/%d=%d %d \n", hit, used, av, acc_avg );



		LOG_GAME_WAVE( "g_total_friends_saved %d \n", g_total_friends_saved );
		LOG_GAME_WAVE( "g_total_friends %d \n", g_total_friends );
		LOG_GAME_WAVE( "friends_saved_avg %d \n", friends_saved_avg );

#endif

		//	printf( "ACC %d/%d=%d %d/%d=%d\n",g_gamestate.level_bullets_hit ,g_gamestate.level_bullets_used,acc, g_total_bullets_hit, g_total_bullets_used, acc_avg );

		// removed acc TMK
		// sprintf(scroll, "T:%d F:%d/%d/%d B:%d/%d=%d:%d =%d",time,  g_gamestate.level_friends_saved, g_gamestate.wave-1, friends_saved_avg, g_gamestate.level_bullets_hit, g_gamestate.level_bullets_used , acc, acc_avg,  friends_saved_avg + acc *( (g_gamestate.level+1)*2));




		sprintf(scroll, "%06d %09d LVL %02d-%02d F:%02d #:%02d",
				g_gamestate.time, g_gamestate.p_score,
				g_gamestate.level,50, //g_gamestate.wave,
				friends_saved_avg, bull_avg);



		amico_rectangle(0, 0, 0,   0, 200, 320, 12);
		render_text(8,  202, 100, (char *) scroll); //scroll 63 chars that should be enough and safe



	}



	if(g_game_counter < 10) // finished
	{
		LOG_FIN("SFX_AMICO_AGAIN leaving! if(g_game_counter < 2)5 g_game_counter %d \n", g_game_counter);



		g_player.shoot_dpad = g_gamestate.BG_SNARTBOMB = 222;
		g_gamestate.BG_MAIN = g_player.shoot_timer=255;

		//g_function_loop = update_splash;

		amico_BGM_quiet_time(0);
		amico_stop_all_SFX();

		MACRO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);
		MACRO_CLEAR_SCREEN
		g_game_counter =0;



		g_function_loop = update_dead; 

	}

	LOG_FIN_TEXT2("update_final_credits FINTXT: OG text copied %d\n", 0);



}


void render_fires(void)
{
	u32 b, texture;
	u32 posX, posY;
	u32 speed;

	for(b=0; b<MAX_ENTITIES; b++)
	{
		posX = g_fires[b].posX;
		if(posX)
		{
			//g_bullets[b].posX += g_bullets[b].speed;
			//g_bullets[b].posY += g_bullets[b].speed;
			posY = g_fires[b].posY;
			speed = g_fires[b].speed++;
			// screen.sprite(Rect(30,3, 2, 2), Point(posX, posY), Point(0, 0), 2.0f, speed & 4); // , Point(0, 0), 0.5f, dir);
			//screen.alpha = 255;
			//screen.sprites = TPAGE04;//map
			// screen.sprite(Rect(14,2, 2, 2), Point(posX, posY), speed & SpriteTransform::HORIZONTAL);  // , Point(0, 0), 0.5f, dir);
			texture = speed&1;
			//checkers texture+=3;
			amico_sprite( BULLET_FIRE_TPAGE,  BULLET_FIRE_U + texture*8,  BULLET_FIRE_V,  8,  8,  8+( posX>>6 ), 8+(posY>>6),     100,  0);


			if(speed > 250)
			{
				g_fires[b].posX = 0;
			}
		}
	}
}



void render_runner_hits(void)
{
	u32 b; //, texture;
	u32 test;
	u32 speed;

	for(b=0; b<MAX_ENTITIES; b++)
	{

		test = g_runner_hits[b].posX;
		if(test)
		{


			speed = g_runner_hits[b].speed++;

			g_runner_hits[b].runner->posX = g_runner_hits[b].posX;
			g_runner_hits[b].runner->dir =  speed&1;
			render_runner( (t_runner*) g_runner_hits[b].runner, g_runner_hits[b].side); //3 );
			g_runner_hits[b].runner->posX = 0; // very hacky, i know


			// texture = speed&1;
			// texture+=3;
			//amico_sprite( 4,  texture*8,3*8, 1*8, 1*8,   8+( posX>>6 ), 8+(posY>>6),     100,  0, 0);

			if(speed > 250)
			{
				g_runner_hits[b].runner =  (t_AI_youtubers*) 0;
				g_runner_hits[b].posX = 0;
			}
		}
	}
}




u32 add_NPC(u32 shell, u8 AI_state, u8 start, u8 side)
{

	t_AI_youtubers *AI_array;
	u32 found_NPC, speed;

	LOG_NPC("add_NPC  shell %d, AI_state %d, start %d, side %d  \n", shell, AI_state, start, side );

	// testing start += AMICO_NONE_BOSSES;


	if(side) // 1 SIDE_ENEMY
	{
		AI_array = g_AI_enemies;
		g_gamestate.enemy_next++;
		g_gamestate.enemy_alive++;

		LOG_NPC("add_NPC  g_gamestate.enemy_next %d, g_gamestate.enemy_alive %d, start %d, side %d  \n", g_gamestate.enemy_next, g_gamestate.enemy_alive );
	}
	else // 0 SIDE_FRIEND
	{
		AI_array = g_AI_friends;
		g_gamestate.friend_next++;
		g_gamestate.friend_alive++;

		LOG_NPC("add_NPC  g_gamestate.friend_next %d, g_gamestate.friend_next %d, start %d, side %d  \n", g_gamestate.friend_next, g_gamestate.friend_next );

	}



	if(start > MAX_SHILLS)
		start = start - (MAX_SHILLS);


	for(found_NPC=start; found_NPC<MAX_SHILLS; found_NPC++)
		if(!AI_array[found_NPC].posX)
			break;





	AI_array +=found_NPC; // move pointer to free space


#if 1
	//AI_array->seed = AI_array->phase + found_NPC << 3;//( ( (g_game_counter  & 0xFF) - found_NPC) & 0xFF) ;


#else



	AI_array->seed = (u8) (g_game_counter>>7 & 0xFF) ;


	AI_array->seed >>= 1;

	AI_array->seed += found_NPC;

#endif




	if(side == SIDE_FRIEND) // friend NPC logic
	{

		if(g_gamestate.p_side == SIDE_HATER ) // hater friends get faster
		{


			AI_array->phase++; // haters get faster
			//speed = (AI_array->phase *8);
			speed = ( (AI_array->phase) *2);

			LOG_NPC("add_NPC SIDE_FRIEND SIDE_HATER speed %d phase %d \n", speed, AI_array->phase );


		}
		else // shill friends get slower
		{

			// AI_array->AI_hits = 0;

			AI_array->phase++;

			speed = ( (AI_array->phase) *7);

			if(speed > 255)
				speed = 245;// min


			speed = 255-speed;

			LOG_NPC("add_NPC SIDE_FRIEND SIDE_SHILL speed %d phase %d \n", speed, AI_array->phase );

			//speed = AI_array->phase;
			//speed-=6;

			//TODO: check for loop?
			//if(speed > 255)
			//	speed = 255;

			// AI_array->phase = (u8)speed;  // shills get slower


		}

		AI_array->AI_hits = 0;

#if 0 // friends can't be hit more then once
		if(found_NPC > AMICO_NONE_BOSSES) // boss extra hits!
		{
			// AI_array->AI_hits = g_gamestate.level +1;
			AI_array->AI_hits = start - AMICO_NONE_BOSSES;
		}

#endif


#if 0
		if(g_gamestate.p_side == SIDE_HATER )
		{

			AI_array->phase++; // haters get faster
			AI_array->AI_hits = g_gamestate.level;

			if(found_NPC > AMICO_NONE_BOSSES) // boss extra power!
			{
				AI_array->phase++; // increase boss phase
				AI_array->AI_hits = g_gamestate.level +1;


			}


			speed = (AI_array->phase *8);


		}
		else
		{

			AI_array->AI_hits = 0;




			speed = AI_array->phase;
			speed-=6;

			//TODO: check for loop?
			//if(speed > 255)
			//	speed = 255;

			AI_array->phase = (u8)speed;  // shills get slower


		}
#endif
	}// if(side == SIDE_FRIEND) // friend NPC logic
	else
	{ // enemy NPC



		// speed = (3+AI_array->phase *8);
		// only enemies can have hit protection...
		speed = (1+(g_gamestate.level>>1)) * g_gamestate.wave; // loop to zero if over 255



		if(found_NPC > AMICO_NONE_BOSSES)  // boss extra power!
		{
			AI_array->phase++; // increase boss phase
			// AI_array->AI_hits = g_gamestate.level +1;
			AI_array->AI_hits = start - AMICO_NONE_BOSSES;
			AI_array->AI_hit_cnt = 255;
			// printf("added #%d side:%d shell:%d phase:%d seed:%d speed:%d  AI_array->AI_hits:%d \n", found_NPC, side, shell, AI_array->phase,  AI_array->seed, AI_array->speed, AI_array->AI_hits);


		}

		LOG_NPC("add_NPC SIDE_HATER speed %d phase %d \n", speed, AI_array->phase );




	} // enemy NPC


	AI_array->AI_tick = start*10;

	if(speed > 255)
		speed = 10; //MAX

	if(speed < 10)
		speed = 545; //MIN



	AI_array->speed = speed;




	// printf("added #%d side:%d shell:%d phase:%d seed:%d speed:%d\n", found_NPC, side, shell, AI_array->phase,  AI_array->seed, AI_array->speed);


#if 0

	//g_gamestate.killed++;
	g_gamestate.nextphase++;
	g_gamestate.cnt_enemy++;
	g_AI_enemies[c].posX = 32 << 6;
	g_AI_enemies[c].posY = (240-32) << 6;
	g_AI_enemies[c].speed = (c * 6)+9; // bigger is faster

	g_AI_enemies[found_NPC].AI_hits = g_gamestate.nextphase*2;

	if(g_gamestate.p_side & 1) // 0 is one - 1 is phase two
		g_AI_enemies[c].AI_personal_tolerance =  (c * 6); //phase two - more - more aggressive last
	else
		g_AI_enemies[c].AI_personal_tolerance =  255 - (c * 6); //phase one -  less is more aggressive last

	if( g_gamestate.p_side)
	{
		u32 p;
		p = g_AI_enemies[c].speed + (5 * g_gamestate.p_side);
		if(p > 255)
			g_AI_enemies[c].speed = 255;
		else
			g_AI_enemies[c].speed = (u8) p;
	}

	g_AI_enemies[c].AI_state =  AI_STATE_PLAYER_TOWARD;
	g_gamestate.shell_corners = MAP_SHELL_CORNER_BOT_LEFT;


	if(g_gamestate.current_enemy & 1)
		g_AI_enemies[c].dpad = CONTROL_DPAD_RD; // point in right dir
	else
		g_AI_enemies[c].dpad = CONTROL_DPAD_RU; // point in right dir
	printf(" g_AI_enemies[c].speed  %d\n", g_AI_enemies[c].speed  );

	g_gamestate.current_enemy++;


	add_NPC(MAP_SHELL_CORNER_TOP_LEFT, AI_STATE_PLAYER_TOWARD, 255, 10, SIDE_ENEMY);
#endif

	// come from 3 corners

	// TODO 0 FIX ADD_NPC LOC - very hacky and probably more problems!
#define TOP_UI 20
#define SIDE_EDGES 30
#define IF_TOP_OR_DOWN_SHELL_POS if( (u32) (AI_array->phase ) & 1)
	// if( (u32) (found_NPC) & 1)

	{

		if(shell == MAP_SHELL_CORNER_TOP_RIGHT) // top right
		{

			AI_array->posX = (320-10) << 6;
			AI_array->posY = (TOP_UI + SIDE_EDGES) << 6;
			g_gamestate.shell_corners = MAP_SHELL_CORNER_TOP_RIGHT;



			//if( (u32) (found_NPC) & 1)
			IF_TOP_OR_DOWN_SHELL_POS
			{
				AI_array->posX += 10 << 6; //right
				AI_array->posY += 7 << 6;; //down
				AI_array->dir = CONTROL_DPAD_D;

			}
			else
			{

				AI_array->posX -= 17 << 6; // left
				AI_array->posY -= 15 << 6;; //up

				AI_array->dir = CONTROL_DPAD_L;
			}



		}
		else if(shell == MAP_SHELL_CORNER_BOT_RIGHT) // bot right

		{
			AI_array->posX = (320-10) << 6;
			AI_array->posY = (240-22) << 6;
			g_gamestate.shell_corners = MAP_SHELL_CORNER_BOT_RIGHT;


			// if( (u32)  (found_NPC)  & 1)
			IF_TOP_OR_DOWN_SHELL_POS
			{
				AI_array->posX -= 12 << 6; //left
				AI_array->posY += 10 << 6;; //down
				AI_array->dir = CONTROL_DPAD_L;

			}
			else
			{

				AI_array->posX += 10 << 6; // right
				AI_array->posY -= 12 << 6;; //up

				AI_array->dir = CONTROL_DPAD_U;
			}

		}
		else if(shell == MAP_SHELL_CORNER_TOP_LEFT ) // top left
		{


			AI_array->posX = (SIDE_EDGES) << 6;
			AI_array->posY =  (TOP_UI + SIDE_EDGES) << 6;

			g_gamestate.shell_corners = MAP_SHELL_CORNER_TOP_LEFT;



			// if( (u32)  (found_NPC)  & 1)
			IF_TOP_OR_DOWN_SHELL_POS
			{
				AI_array->posX += 12 << 6; //right
				AI_array->posY -= 10 << 6;; //up
				AI_array->dir = CONTROL_DPAD_R;

			}
			else
			{

				AI_array->posX -= 10 << 6; // left
				AI_array->posY += 12 << 6;; //down

				AI_array->dir = CONTROL_DPAD_D;
			}



		}
		else // if(shell == MAP_SHELL_CORNER_BOT_LEFT) // bot left
		{

			AI_array->posX = (SIDE_EDGES) << 6;
			AI_array->posY = (240-SIDE_EDGES) << 6;

			g_gamestate.shell_corners = MAP_SHELL_CORNER_BOT_LEFT;

			//if( (u32) (found_NPC)  & 1)
			IF_TOP_OR_DOWN_SHELL_POS
			{
				AI_array->posX += 12 << 6; //right
				AI_array->posY += 10 << 6;; //down
				AI_array->dir = CONTROL_DPAD_R;
			}
			else
			{
				AI_array->posX -= 10 << 6; // left
				AI_array->posY -= 12 << 6;; //up

				AI_array->dir = CONTROL_DPAD_U;
			}
		}




		//	LOG_NPC("add_NPC NPC: X:%d Y:%d startx %d starty %d \n",AI_array->posX>>6, AI_array->posY>>6, startx>>6, starty>>6 );
	}

#undef IF_TOP_OR_DOWN_SHELL_POS
#undef TOP_UI 
#undef SIDE_EDGES 



	AI_array->AI_state =  AI_state;


	if(g_gamestate.p_side & 1) // 0 is one - 1 is phase two
		AI_array->AI_personal_tolerance =  (found_NPC * 5); //phase two - more - more aggressive last
	else
		AI_array->AI_personal_tolerance =  226 - (found_NPC * 5); //phase one -  less is more aggressive last



	return found_NPC;
}



void add_smart_bomb(void)
{
	u32 i;

	// clear bullets and fires
	for(i=0; i<MAX_ENTITIES; i++)
	{
		g_runner_hits[i].posX = g_bullets[i].posX = g_fires[i].posX = 0;
	}

	// clear enemies
	//if(0)
	for(i=0; i< MAX_SHILLS ; i++) // bosses at the end
	{

		if(g_AI_friends[i].posX)
		{
			//amico_play_SFX(SFX_HIT_FRIEND_ID, SFX_HIT_FRIEND_VOL);

			if( g_AI_friends[i].AI_hits == 0 )
			{
				add_runner_hit(&g_AI_friends[i], 1);
				g_AI_friends[i].posX = 0;
				if(g_gamestate.friend_alive)
					g_gamestate.friend_alive--;

#if 0 //def USE_GAME_CALCULATE_HIT_SCORE
				g_gamestate.p_score += MACRO_GAME_CALCULATE_FRIEND_HIT_SCORE;
				g_gamestate.p_health += MACRO_GAME_CALCULATE_FRIEND_HIT_HEALTH;
				g_gamestate.p_bullets += MACRO_GAME_CALCULATE_FRIEND_HIT_BULLETS;
#endif
			}
			else
			{
				g_AI_friends[i].AI_hits--;
				g_AI_friends[i].AI_hit_cnt = 255;
			}

		}

		if(g_AI_enemies[i].posX)
		{
			//amico_play_SFX(SFX_HIT_ENEMY_ID, SFX_HIT_ENEMY_VOL);
			if( g_AI_enemies[i].AI_hits == 0 )
			{
				add_runner_hit(&g_AI_enemies[i], 2);
				g_AI_enemies[i].posX = 0;
				if(g_gamestate.enemy_alive)
					g_gamestate.enemy_alive--;

#if 0// def USE_GAME_CALCULATE_HIT_SCORE
				g_gamestate.p_score += MACRO_GAME_CALCULATE_EMEMY_HIT_SCORE;
				// g_gamestate.p_health += GAME_CALCULATE_HATER_HIT_HEALTH;
#endif
			}
			else
			{
				g_AI_enemies[i].AI_hits--;
				g_AI_enemies[i].AI_hit_cnt = 255;
			}
		}

	}

	g_gamestate.BG_MAIN = 0;
	g_gamestate.BG_SNARTBOMB =32;

	// g_gamestate.BG_red = 150;

}

u32 add_bullet(t_runner* runner, u8 dpad, u32 center_offsetDown_fixed, u32 center_offsetLeft_fixed, u32 side)
{
	u32 b;
	u32 test;
	for(b=0; b<MAX_ENTITIES; b++)
	{
		test = g_bullets[b].posX;
		if(!test)
		{

			g_bullets[b].speed = BULLET_SPEED;
			//g_bullets[b].owner = runner;
			/*
			if(runner->dpad)
				g_bullets[b].dpad = runner->dpad;
			else
				{
				g_bullets[b].dpad = (runner->dir==0 ?CONTROL_DPAD_L :CONTROL_DPAD_R );
				}
			 */
			g_bullets[b].dpad = dpad;
			g_bullets[b].posX = runner->posX - center_offsetLeft_fixed;
			g_bullets[b].posY = runner->posY + center_offsetDown_fixed;
			g_bullets[b].owner = runner;

			LOG_BULLET("B: X %d Y %d \n", g_bullets[b].posX, g_bullets[b].posY);

			//amico_play_SFX(SFX_SHOT_ID, SFX_SHOT_VOL);
			amico_play_SFX( SFX_MOO1+(b&1)+(2*side));

			return 1;
		}
	}
	return 0;
}

void add_fires(u32 posX, u32 posY )
{
	u32 test;
	u32 b;
	for(b=0; b<MAX_ENTITIES; b++)
	{
		test = g_fires[b].posX;
		if(test == 0)
		{
			//g_bullets[b].posX += g_bullets[b].speed;
			//g_bullets[b].posY += g_bullets[b].speed;
			g_fires[b].posX = posX;
			g_fires[b].posY = posY;
			g_fires[b].speed = AI_FIRE_TIME_START;
			return;
		}
	}
}



void add_runner_hit(t_AI_youtubers *runner, u8 side)
{
	u32 test;
	u32 b;
	// printf("add_runner_hit\n");

	for(b=0; b<MAX_ENTITIES; b++)
	{
		test =  g_runner_hits[b].posX;
		if(test == 0)
		{

			g_runner_hits[b].posX = runner->posX;
			g_runner_hits[b].side = side;
			g_runner_hits[b].runner = runner;
			g_runner_hits[b].speed =AI_FIRE_TIME_START; // short hit anim

			//add_fires(g_runner_hits[b].posX-1025, g_runner_hits[b].posY );
			return;
		}
	}
}


void game_reset(void) // reset game
{

	//s32 i;

	//t_data_head32 *friends;
	//t_data_head32 *enemies;



	memset((u8*) &g_AI_friends[0], 0,  sizeof(t_AI_youtubers) * (MAX_SHILLS+1 ) );
	memset((u8*) &g_AI_enemies[0], 0,  sizeof(t_AI_youtubers) * (MAX_SHILLS+1) );
	memset((u8*) &g_runner_hits[0], 0, sizeof(t_runner_hit) * (MAX_ENTITIES) );
	memset((u8*) &g_fires[0], 0, sizeof(t_pos) * MAX_ENTITIES);
	memset((u8*) &g_bullets[0], 0, sizeof(t_bullet) * MAX_ENTITIES);
	// don't clear memset(&g_gamestate, 0, sizeof(g_gamestate));

	g_player.speed=PLAYER_INIT_SPEED;

	// don't do here, not very random! intern_randomize_init_lists();


#if 0
	for(i=0; i<MAX_ENTITIES; i++)
	{
		g_bullets[i].posX = g_fires[i].posX = 0;
	}

#endif


	g_text_scroll_counter = g_game_counter = g_total_friends_saved = g_total_friends  = g_total_bullets_used = g_total_bullets_hit = 0;

	g_game_start_time = 0;
	//g_game_level_time = 20;
	g_game_CUR_BONUS = 10000;
	g_gamestate.time = g_gamestate.level = 0;
	g_gamestate.wave = 0; // waves start at 1, but reset to 0
	g_gamestate.friend_alive = g_gamestate.enemy_alive = 0;
	g_gamestate.friend_next = g_gamestate.enemy_next =0;
	g_gamestate.level_friends_saved =0;

	//g_gamestate.wave = 39;
	//g_gamestate.level = 2;

	//g_game_counter = 510;

	//g_gamestate.BG_MAIN = g_gamestate.BG_SIDES = 0;
	g_gamestate.BG_MAIN = 0;
	amico_stop_all_SFX();
	// AMICO_PLAY_STEREO_SFX(SFX_AMICO_AGAIN);


#ifdef _DEBUG_


	g_gamestate.p_score =   1010;
	g_gamestate.p_bullets = 99999;
	g_gamestate.p_health =  99999;
	g_gamestate.level = 0;

#if 0


	//TODO 1 LEVEL ENDING SET WAVE
	//g_gamestate.wave =   (MAX_SHILLS-g_unlocked_bosses_level) +1; // first boss level

	g_unlocked_bosses_level =  (AMICO_BOSSES)-2;
	g_gamestate.wave =   25; //35; //(MAX_SHILLS) ; // first boss level
	g_gamestate.level =  14; //14; // (13); // first boss level
	g_gamestate.cheat_testing = 1;

#endif

#else
	g_gamestate.p_score = 1010;
	g_gamestate.p_bullets = 1010;
	g_gamestate.p_health = 1010;
#endif


#if 0

	//g_gamestate.wave =   (MAX_SHILLS-g_unlocked_bosses_level) +1; // first boss level

	g_unlocked_bosses_level = 2; //(AMICO_BOSSES)-2;
	g_gamestate.wave =   MAX_SHILLS; //(MAX_SHILLS) ; // first boss level
	g_gamestate.level =  13; // (13); // first boss level
	g_gamestate.cheat_testing = 1;

#endif


	g_player.AI_hit_cnt = 255;
	g_player.dpad =  g_player.shoot_dpad = 0;
	g_player.shoot_timer=BUTTON_PRESS_TIME*2;
	g_player.posX = MAP_START_PLAYER_POSX;
	g_player.posY = MAP_START_PLAYER_POSY;



}


void amico_init(void)
{


	if(g_AI_enemies)
	{
		free(g_AI_enemies);
		free(g_AI_friends);
		free(g_runner_hits);
		free(g_fires);
		free(g_bullets);
	}




	g_AI_enemies = (t_AI_youtubers*) malloc( sizeof(t_AI_youtubers) * (MAX_SHILLS+1) );
	// printf("g_AI_enemies  %#010x\n", g_AI_enemies);

	g_AI_friends = (t_AI_youtubers*) malloc( sizeof(t_AI_youtubers) * (MAX_SHILLS+1 ) );
	// printf("g_AI_friends  %#010x\n", g_AI_friends);

	g_runner_hits = (t_runner_hit*) malloc( sizeof(t_runner_hit) * (MAX_ENTITIES ) );
	// printf("g_runner_hits  %#010x\n", g_runner_hits);


	g_fires = (t_pos*) malloc( sizeof(t_pos) * (MAX_ENTITIES) );
	// printf("g_fires  %#010x\n", g_fires);


	g_bullets = (t_bullet*) malloc( sizeof(t_bullet) * (MAX_ENTITIES ) );
	// printf("g_bullets  %#010x\n", g_bullets);

	memset((u8*) &g_player, 0, sizeof(g_player));

	memset((u8*) &g_gamestate, 0, sizeof(g_gamestate));
	//memset(&g_runner_hits, 0, sizeof(t_runner_hit) * MAX_ENTITIES);



	// don't use here! MACRO_GAME_RESET_AND_RANDOMIZE_LIST
	game_reset();

	g_no_boss_flashing =0;


	// init global vars
	g_SET_SFX_VOL = SFX_VOL_DEFAULT;
	g_SET_BGM_VOL = BGM_VOL_DEFAULT;


	g_AI_shoot_dist = INIT_SHOOT_DIST;




	MACRO_CLEAR_SCREEN
	amico_stop_all_SFX();

	amico_play_BGM_audio(2); // 2 is intro track
	amico_BGM_quiet_time(0); // set BGM vol



	g_text_scroll_counter= g_game_counter=0;


	g_player.shoot_timer=0;

	g_player.dir = g_player.dpad = CONTROL_DPAD_R;
	g_player.posX = MAP_START_PLAYER_POSX;
	g_player.posY = MAP_START_PLAYER_POSY;
	g_player.speed=PLAYER_INIT_SPEED;



	g_player.dpad = g_player.shoot_dpad =0;
	g_player.shoot_timer=BUTTON_PRESS_TIME*2;

	// init to TT for attack mode
	g_player.TPAGE = 1;
	g_player.textU = 0;
	g_player.textV = 0;

	//	g_game_counter = 64000;
	//TODO 0 set init loop



	g_function_loop =  update_splash; //update_level_zero;// update_splash; //update_splash; //update_level_zero;// update_splash; //update_final_credits; //update_select; //update_splash;  //update_select; //update_select; //update_game; //update_intro; //update_select; //update_credit;
	//g_gamestate.cheat_testing = 1; // start game demo instead of loop

	// g_function_loop = update_level_zero; //update_level_zero;/
	//g_function_loop = update_select;
	//amico_text_init();
	// srand(g_game_counter);
	g_gamestate.shell_corners = 17;
	// srand(VSync(-1));
	// g_game_counter =AMICO_BOSSES <<4;//press A
	// printf("\n srand \n");


	g_unlocked_bosses_level = (AMICO_BOSSES);
	g_gamestate.wave = 0xAA; // used to check first run random.. stupid, but it's reset before use
	g_gamestate.enemy_next = 0;



#if 0 // doesn't work any more on release, i don't know why, i dont care :/
	update_splash();
	intern_randomize_init_lists();
	g_gamestate.cheat_testing = 0;
	g_gamestate.cheat_big_heads = 1;
	MACRO_SET_GAME_TO_FINAL_CREDITS;
#endif



}



void amico_deinit(void)
{
	free(g_AI_enemies);
	free(g_AI_friends);
	free(g_runner_hits);
	free(g_fires);
	free(g_bullets);

}


// this is a complete mess! okay extra mess!
u32 game_AI_enemies(void)
{
	u32 i;

	LOG_NPC("game_AI_enemies: g_game_counter %d \n", g_game_counter);

	for(i=0; i<MAX_SHILLS; i++)
	{
		LOG_NPC("game_AI_enemies: AI  %d \n", i);

		LOG_NPC("game_AI_enemies: AI test  %d \n", i);

		LOG_NPC("game_AI_enemies: AI posX %d \n", g_AI_enemies[i].posX);
		LOG_NPC("game_AI_enemies: AI test  %d \n", i);




		if(g_AI_enemies[i].posX > 0) // active
		{
			u32 ret;
			u8 op_dpad;
#if 0
			if( g_AI_enemies[i].AI_tick > g_AI_enemies[i].AI_personal_tolerance)
			{
				g_AI_enemies[i].AI_state ==  AI_STATE_RANDOM1;
				g_AI_enemies[i].AI_tick = 0;
			}
#endif

			LOG_NPC("game_AI_enemies: processing NPC %d \n", i);

			if( (g_game_counter & 255) == i)
				g_AI_enemies[i].AI_tick++;

			ret = game_collision_move((t_runner*)&g_AI_enemies[i], 5, -8, 5, 1);

			if(ret == 0)// bad or old move - new dir
			{
				u32 playerX, playerY;
				s32 x, y;

				playerX = g_player.posX;
				playerY = g_player.posY;

				// ret = rand(); // rand state

				// if(g_AI_enemies[i].AI_state & AI_STATE_PLAYER)
				{
					//   20      - 64 // go right
					x = playerX  - g_AI_enemies[i].posX;
					//  64      -   100 // go up
					y = playerY  - g_AI_enemies[i].posY;
					//if(ret & 1 )

					if(g_AI_enemies[i].AI_state == AI_STATE_PLAYER_TOWARD)
					{
						if(x>0) // go right
						{
							g_AI_enemies[i].dpad  =CONTROL_DPAD_R;
							op_dpad =CONTROL_DPAD_L;
						}
						else // go left
						{
							g_AI_enemies[i].dpad  =CONTROL_DPAD_L;
							op_dpad =CONTROL_DPAD_R;
						}

						if(y<0) // go up
						{
							g_AI_enemies[i].dpad  += CONTROL_DPAD_U;
							op_dpad +=CONTROL_DPAD_D;
						}
						else // go down
						{
							g_AI_enemies[i].dpad  += CONTROL_DPAD_D;
							op_dpad +=CONTROL_DPAD_U;
						}
						ret = game_collision_move((t_runner*)&g_AI_enemies[i], 5, -8, 5, 1);
						if(ret) // move ok
						{
							// do nothing g_AI_enemies[i].AI_tick = g_AI_enemies[i].AI_tick >>1; // half it?
						}
						else // move not ok
						{
							// try again later?


							if(g_AI_enemies[i].AI_tick > 126)
							{

								//	g_AI_enemies[i].AI_personal_tolerance--;
								g_AI_enemies[i].AI_state = AI_STATE_RANDOM1 ; // change to evade for a while
								g_AI_enemies[i].AI_tick = 0;

							}

							g_AI_enemies[i].dpad = op_dpad;//~g_AI_enemies[i].dpad ;
							g_AI_enemies[i].AI_tick += i; //clear



						}
					}
					else if(g_AI_enemies[i].AI_state == AI_STATE_PLAYER_EVADE)
					{
						if(x<0) // go right
						{
							g_AI_enemies[i].dpad  =CONTROL_DPAD_R;
							op_dpad =CONTROL_DPAD_L;
						}
						else // go left
						{
							g_AI_enemies[i].dpad  =CONTROL_DPAD_L;
							op_dpad =CONTROL_DPAD_R;
						}
						if(y>0) // go up
						{
							g_AI_enemies[i].dpad  += CONTROL_DPAD_U;
							op_dpad +=CONTROL_DPAD_D;
						}
						else // go down
						{
							g_AI_enemies[i].dpad  += CONTROL_DPAD_D;
							op_dpad +=CONTROL_DPAD_U;
						}
						ret = game_collision_move((t_runner*)&g_AI_enemies[i], 5, -8, 5, 1);

						if(ret) // move ok
						{
							// do nothing g_AI_enemies[i].AI_tick = g_AI_enemies[i].AI_tick >>1; // half it?
						}
						else // move not ok
						{
							// do nothing?


							if(g_AI_enemies[i].AI_tick > 200)
							{
								g_AI_enemies[i].AI_state =  AI_STATE_RANDOM1; // change to evade for a while
								g_AI_enemies[i].AI_tick = 0;

							}

							g_AI_enemies[i].dpad = op_dpad; //~g_AI_enemies[i].dpad ;
							g_AI_enemies[i].AI_tick += i; //clear


						}

					}
					else if(g_AI_enemies[i].AI_state ==  AI_STATE_PLAYER_HIT)
					{
#if 0
						if(g_AI_enemies[i].AI_hits & 1)
							g_AI_enemies[i].AI_state = AI_STATE_PLAYER_TOWARD;
						else
							g_AI_enemies[i].AI_state = AI_STATE_PLAYER_EVADE;
#else
						g_AI_enemies[i].AI_state = AI_STATE_RANDOM1;
						g_AI_enemies[i].AI_tick = 0;
#endif
					}
					else if(g_AI_enemies[i].AI_state ==  AI_STATE_RANDOM1)
					{
						//u32 val;
						//	g_AI_enemies[i].dpad  = 0;
						u8 pos;

#if 0
						// u32 pos = g_AI_enemies[i].AI_tick & 3;
						pos = g_AI_enemies[i].AI_tick >> 4;

						g_AI_enemies[i].dpad = pos;

						if( (pos & 3) == 3)
							g_AI_enemies[i].dpad -=2;

						if( (pos & 12) == 12)
							g_AI_enemies[i].dpad -=8;
#else


						pos = g_stereo_counter_random & 0x3;



						if(pos)
							pos = CONTROL_DPAD_U;
						else if(pos == 3)
							pos = CONTROL_DPAD_D;

						g_AI_enemies[i].dpad = pos;
#endif
						ret = game_collision_move((t_runner*)&g_AI_enemies[i], 5, -8, 5, 1);

						if(ret) // move ok
						{
							// do nothing g_AI_enemies[i].AI_tick = g_AI_enemies[i].AI_tick >>1; // half it?
						}
						else
						{

							//skip
							g_AI_enemies[i].AI_tick+= 25;// try a few more times

						}



						//g_AI_enemies[i].AI_hit_cnt = 255;
						//g_AI_enemies[i].AI_tick++;


						if( g_AI_enemies[i].AI_tick > 200)
						{

							//if( g_AI_enemies[i].speed  & 1)

							if(g_stereo_counter_random&1)
							{
								g_AI_enemies[i].AI_state =  AI_STATE_PLAYER_TOWARD;
								// g_AI_enemies[i].AI_hit_cnt = 64;
								g_AI_enemies[i].AI_tick =0;
								//return 0;
							}
							else //if(g_AI_enemies[i].AI_tick &128)
							{

								g_AI_enemies[i].AI_state =  AI_STATE_PLAYER_EVADE;
								// g_AI_enemies[i].AI_hit_cnt = 64;
								g_AI_enemies[i].AI_tick =0;
								//return 0;
							}



						}

#if 0
						//  do{

						if(g_AI_enemies[i].AI_tick  &1)
						{
							if(i &1)
								op_dpad = CONTROL_DPAD_R;
							else
								op_dpad = CONTROL_DPAD_L;

							if(g_AI_enemies[i].AI_tick &16)
								op_dpad += CONTROL_DPAD_U;
							else
								op_dpad += CONTROL_DPAD_D;
						}
						else
						{
							if(i &1)
								op_dpad += CONTROL_DPAD_L;
							else
								op_dpad += CONTROL_DPAD_R;

							if(g_AI_enemies[i].AI_tick &16)
								op_dpad += CONTROL_DPAD_D;
							else
								op_dpad += CONTROL_DPAD_U;
						}

						//g_game_counter += g_AI_enemies[i].AI_tick++;

						g_AI_enemies[i].dpad = op_dpad;

						ret = game_collision_move((t_runner*)&g_AI_enemies[i], 5, -8, 5, 1);
						g_AI_enemies[i].AI_tick++;
						//}while(!ret);


						if(g_AI_enemies[i].AI_tick > 126)
							if(i & 1)
								g_AI_enemies[i].AI_state = AI_STATE_PLAYER_EVADE ;
							else
								g_AI_enemies[i].AI_state = AI_STATE_PLAYER_TOWARD;

#endif

#if 0

						// if(g_AI_enemies[i].AI_tick > g_AI_enemies[i].AI_personal_tolerance)
						{
								//	g_AI_enemies[i].AI_tick++;
								//	g_AI_enemies[i].AI_personal_tolerance--;




								if( g_AI_enemies[i].AI_tick & 1)
								{
									g_AI_enemies[i].AI_state =  AI_STATE_PLAYER_TOWARD;
									g_AI_enemies[i].AI_tick =0;

									return 0;
								}
								else //if(g_AI_enemies[i].AI_tick &128)
								{

									g_AI_enemies[i].AI_state =  AI_STATE_PLAYER_EVADE;
									g_AI_enemies[i].AI_tick =0;
									return 0;
								}


						}

#endif


#if 0
						{


							if(g_AI_enemies[i].seed &128) // go up
							{
								g_AI_enemies[i].dpad  +=CONTROL_DPAD_U;
							}

							if(g_AI_enemies[i].seed &32)  // go down
							{
								g_AI_enemies[i].dpad  +=CONTROL_DPAD_D;
							}

							if(g_AI_enemies[i].seed &8) // go left
							{
								g_AI_enemies[i].dpad  += CONTROL_DPAD_L;
							}

							if(g_AI_enemies[i].seed &2) // go right
							{
								g_AI_enemies[i].dpad  += CONTROL_DPAD_R;
							}



						}
#endif


						//	g_AI_enemies[i].AI_tick++;
						//	g_AI_enemies[i].AI_personal_tolerance--;




					}
				}

			}
			// else
			//	 g_AI_enemies[i].AI_tick = 0;




			if(g_AI_enemies[i].AI_hit_cnt)
			{

				if(g_game_counter & 8)
					amico_rectangle(255, 255, 255, (g_AI_enemies[i].posX>>6)-16, (g_AI_enemies[i].posY>>6) -16, 16, 32 );
				else
					amico_rectangle(g_AI_enemies[i].AI_hit_cnt, g_AI_enemies[i].AI_hit_cnt, g_AI_enemies[i].AI_hit_cnt, (g_AI_enemies[i].posX>>6)-16, (g_AI_enemies[i].posY>>6) -16, 16, 32 );


				// amico_sprite( 4, 31*8, 3*8, 1*8, 1*8,     8+(g_bullets[b].posX>>6), 8+(g_bullets[b].posY>>6) ,     100, 0, 0);

				g_AI_enemies[i].AI_hit_cnt--;
			}
			else if(g_AI_enemies[i].AI_personal_tolerance<220) // thinking about it;
			{
				g_AI_enemies[i].AI_personal_tolerance+=(g_gamestate.level+1);

			}
			else  // can do shoot!
			{
				if(g_AI_enemies[i].shoot_timer)
				{
					g_AI_enemies[i].shoot_timer--;
				}
				else
				{
					// calc shooting
					s32 x, y;
					u8 dpad;
					//s32 x_start, y_start;



					x = (s32) (g_player.posX>>6)  - (s32) (g_AI_enemies[i].posX>>6);
					y = (s32) (g_player.posY>>6)  - (s32) (g_AI_enemies[i].posY>>6);



					// Y -below
					// Y + above
					// X -right
					// X +left
					//LOG_SHOOT_BULLET("dist X: %d  Y: %d\n", x, y);

					/*
					 *
		#define CONTROL_DPAD_NONE 0
		#define CONTROL_DPAD_R 1 // 0b0001 // right 1
		#define CONTROL_DPAD_L 2 // 0b0010 // left 2
		#define CONTROL_DPAD_U 4  // 0b0100 // up 4
		#define CONTROL_DPAD_D 8  // 0b1000 // down 8
					 *
					 */
					dpad=0;


					if(  (i + g_gamestate.wave) &1)// is saying stupid things = shoot random
					{


						u32 dist;


						//TODO: 000 distance is huge at the start to make game harder, then shrinks smaller
						if(g_gamestate.level<1)
							dist =  g_AI_shoot_dist + (( 36- g_gamestate.wave )>>1);
						else
							dist =  g_AI_shoot_dist - (g_gamestate.level *3) ;


						if( ( (x >= 0 && x < dist)  || (x < 0 && x > -dist ) )  &&  ( (y >= 0 && y < dist)  || (y < 0 && y > -dist )) ) // X -NPC left  of player
						{
							dpad = g_stereo_counter_random & 0x3;

							if(dpad == 0)
								dpad = CONTROL_DPAD_U;
							else if(dpad == 3)
								dpad = CONTROL_DPAD_D;

							LOG_SHOOT_BULLET(" NPC longer distance, saying stupid things dpad %d %d \n",dpad, g_stereo_counter_random );
						}



					}
					else
					{



						// Y -NPC below of player
						// Y +NPC above of player

						// X -NPC right of player
						// X +NPC left of player

						if( y >= 0 && y < g_AI_shoot_dist    ) // Y +NPC above of player
						{
							LOG_SHOOT_BULLET(" Y +NPC above player Shoot down %d %d \n", x, y);



							if( x <= g_AI_shoot_dist  && x >= MAX_SHOOT_ANGLE_TEST  ) // X +NPC right of player
							{
								LOG_SHOOT_BULLET("  X +NPC left of player shoot right %d %d \n", x, y);
								dpad  += CONTROL_DPAD_R;

								if(y >= MAX_SHOOT_ANGLE_TEST )
									dpad  += CONTROL_DPAD_D;

							}
							else if(x > -g_AI_shoot_dist && x < -MAX_SHOOT_ANGLE_TEST  ) // X -NPC left  of player
							{
								LOG_SHOOT_BULLET("X -NPC right of player shoot left %d %d \n", x, y);
								dpad  += CONTROL_DPAD_L;

								if(y >= MAX_SHOOT_ANGLE_TEST )
									dpad  += CONTROL_DPAD_D;

							}

							else if( ( ( x >= 0) && x <= g_AI_shoot_dist)  || ( ( x < 0) && x > -g_AI_shoot_dist) )
							{
								LOG_SHOOT_BULLET(" player Shoot down %d %d \n", x, y);
								dpad  += CONTROL_DPAD_D;

							}
						}

						else if(y < 0 &&  y > -g_AI_shoot_dist)
						{
							LOG_SHOOT_BULLET("Y -NPC below player Shoot up %d %d \n", x, y);



							if( x <= g_AI_shoot_dist  && x >= MAX_SHOOT_ANGLE_TEST  ) // X +NPC right of player
							{
								LOG_SHOOT_BULLET("  X +NPC left of player shoot right %d %d \n", x, y);
								dpad  += CONTROL_DPAD_R;

								if(y < MAX_SHOOT_ANGLE_TEST )
									dpad  += CONTROL_DPAD_U;


							}
							else if(x > -g_AI_shoot_dist && x < -MAX_SHOOT_ANGLE_TEST  ) // X -NPC left  of player
							{
								LOG_SHOOT_BULLET("X -NPC right of player shoot left %d %d \n", x, y);
								dpad  += CONTROL_DPAD_L;

								if(y < MAX_SHOOT_ANGLE_TEST )
									dpad  += CONTROL_DPAD_U;

							}

							else if( ( ( x >= 0) && x < g_AI_shoot_dist)  || ( ( x < 0) && x > -g_AI_shoot_dist) )
							{
								LOG_SHOOT_BULLET(" player Shoot up %d %d \n", x, y);
								dpad  += CONTROL_DPAD_U;

							}




						}

					}


					if(dpad) // got close and dir set, shoot!
					{
						// add_bullet(t_runner * runner, u8 dpad, u32 center_offsetDown_fixed, u32 center_offsetLeft_fixed)
						add_bullet( (t_runner*) &g_AI_enemies[i], dpad, -256 ,16<<6,SIDE_ENEMY);
						g_AI_enemies[i].shoot_timer = 65-g_gamestate.wave; //25;
					}
				}


			}// end shoot



			render_runner( (t_runner*)&g_AI_enemies[i], 2);//.frame, g_player.posX, g_player.posY,	g_player.dir & 1);


		} // active
	}// for loop

	LOG_NPC("game_AI_enemies: FIN g_game_counter %d \n", g_game_counter);
	return 0;

}
u32 game_AI_friends(void)
{


	u32 i;
	u32 playerX, playerY;
	s32 x, y;
	u32 ret;
	playerX = g_player.posX;
	playerY = g_player.posY;


	LOG_NPC("game_AI_enemies:  g_game_counter %d \n", g_game_counter);


	LOG_NPC("game_AI_enemies: playerX %d \n", playerX);
	LOG_NPC("game_AI_enemies: playerY %d \n", playerY);



	for(i=0; i<MAX_SHILLS; i++)
	{
		if(g_AI_friends[i].posX > 0) // active
		{

			//if(g_AI_friends[i].AI_state & AI_STATE_PLAYER_TOWARD)
			{
				//   100      - 64 // go right
				x = playerX  - g_AI_friends[i].posX;
				//  64      -   100 // go up
				y = playerY  - g_AI_friends[i].posY;

				if(g_AI_friends[i].AI_state & AI_STATE_PLAYER_TOWARD)
				{
					if(x>0) // go right
					{
						g_AI_friends[i].dpad  =CONTROL_DPAD_R;
					}
					else // go left
					{
						g_AI_friends[i].dpad  =CONTROL_DPAD_L;
					}
					if(y<0) // go up
					{
						g_AI_friends[i].dpad  += CONTROL_DPAD_U;
					}
					else // go down
					{
						g_AI_friends[i].dpad  += CONTROL_DPAD_D;
					}
					ret = game_collision_move((t_runner*)&g_AI_friends[i], 5, -8, 5, 1);
					if(ret) // move ok
					{
						g_AI_friends[i].AI_tick = 0;
					}
					else // move not ok
					{
						g_AI_friends[i].AI_tick++;
						if(g_AI_friends[i].AI_tick > 150)
							g_AI_friends[i].AI_state = AI_STATE_PLAYER_EVADE ; // change to evade for a while
					}
				}
				else
				{
					if(x<0) // go left
					{
						g_AI_friends[i].dpad  =CONTROL_DPAD_R;
					}
					else // go right
					{
						g_AI_friends[i].dpad  =CONTROL_DPAD_L;
					}
					if(y>0) // go down
					{
						g_AI_friends[i].dpad  += CONTROL_DPAD_U;
					}
					else // go up
					{
						g_AI_friends[i].dpad  += CONTROL_DPAD_D;
					}
					ret = game_collision_move((t_runner*)&g_AI_friends[i], 5, -8, 5, 1);
					if(ret) // move ok
					{
						g_AI_friends[i].AI_tick = 0;
					}
					else // move not ok
					{
						g_AI_friends[i].AI_tick++;
						if(g_AI_friends[i].AI_tick > 150)
							g_AI_friends[i].AI_state =  AI_STATE_PLAYER_TOWARD; // change to evade for a while
					}
				}
			}
			//	else // random
			if(0)
			{
				u32 val;
				g_AI_friends[i].dpad  =CONTROL_DPAD_D;
				do{
					//g_AI_friends[i].dpad = g_AI_friends[i].dpad<< 1;
					val = game_collision_move((t_runner*)&g_AI_friends[i], 5, -8, 5, 1);
				}while(0);//!val);
				g_AI_friends[i].dpad = 0;
			}

			render_runner( (t_runner*)&g_AI_friends[i], 1);//.frame, g_player.posX, g_player.posY,	g_player.dir & 1);

		}

	}// for loop

	LOG_NPC("game_AI_friends: FIN g_game_counter %d \n", g_game_counter);
	return 0;
}



#if 0

// collision based from: https://github.com/gszauer/GamePhysicsCookbook/blob/a0b8ee0c39fed6d4b90bb6d2195004dfcf5a1115/Code/Geometry2D.cpp#L311
// from http://www.realtimerendering.com/intersections.html

bool RectangleRectangle(const Rectangle2D& rect1, const Rectangle2D& rect2) {
	vec2 aMin = GetMin(rect1);
	vec2 aMax = GetMax(rect1);
	vec2 bMin = GetMin(rect2);
	vec2 bMax = GetMax(rect2);

	bool xOverlap = ((bMin.x <= aMax.x) && (aMin.x <= bMax.x));
	bool yOverlap = ((bMin.y <= aMax.y) && (aMin.y <= bMax.y));

	return xOverlap && yOverlap;
}


// https://www.geometrictools.com/Source/Intersection2D.html
// https://www.geometrictools.com/GTE/Mathematics/IntrAlignedBox2AlignedBox2.h

for (int32_t i = 0; i < 2; i++)
{
	if (box0.max[i] < box1.min[i] || box0.min[i] > box1.max[i])
	{
		result.intersect = false;
		return result;
	}
}


#endif

u32 game_bullet_runner_collision(  t_bullet *bullet)
{
	u32 start;
	//u32 posX, posY;
	u32 end = g_gamestate.enemy_next;
	s32 b_x;
	s32 b_y;
	s32 e_x;
	s32 e_y;
	t_AI_youtubers *AI_list;






	AI_list = g_AI_enemies;

	b_x = bullet->posX >> 6;
	b_y = bullet->posY >> 6;


	//first check collision with player
	if(!g_player.AI_hit_cnt) // can player be hit, if zero yes
		if(bullet->owner != (t_runner*) &g_player) //and not players own bullets
		{

			e_x = g_player.posX >> 6;
			e_y = g_player.posY >> 6;

#ifdef LOG_DEBUG_COL
			// bullet
			// amico_rectangle(255, 0, 0, b_x+4, b_y+4 , 8, 8 );


			amico_rectangle(0, 255, 0, e_x-16, e_y -15, 16, 32 );
			amico_rectangle(0, 5, 250, e_x-16, e_y +14, 2, 2 );
#endif
			// amico_rectangle(0, 5, 250,   b_x +4 ,  b_y, 2, 2 );
			// amico_rectangle(0, 5, 250,   b_x+12 ,  b_y, 2, 2 );

			if(
					b_x +4 > e_x - 16 && b_x+12 < e_x + 1
					&& b_y+4 > e_y-15 && b_y-4 < e_y + 14


			)
			{


				g_gamestate.p_health-= GAME_CALCULATE_PLAYER_BULLET_HIT; // assume greater then zero, death check and anim somewhere else

				g_player.AI_hit_cnt = 255;


				amico_play_SFX(SFX_HIT_OOH);

				return 1; //  collision! bullet processed exit
			}
		} // player collision check




	// enemy/friend collision check

	start = 0;// g_gamestate.killed;



	// only player bullets can kill enimies - enemies can't kill enemies
	if(bullet->owner == (t_runner*)&g_player) // is a player bullet
	{

		BULLET_RESTART: //friendlies and bullets, anyone can kill

		for( ; start <= MAX_SHILLS; start++ )
			if( (AI_list+start) !=  (t_AI_youtubers*) bullet->owner) // ignore AI owner bullets
			{
				if(AI_list[start].posX && !AI_list[start].AI_hit_cnt) // hit cnt must be zero
				{


					e_x = AI_list[start].posX >> 6;
					e_y = AI_list[start].posY >> 6;


#if 0


#if 1
					// bullet
					// amico_rectangle(255, 0, 0, b_x+4, b_y+4 , 8, 8 );


					amico_rectangle(0, 255, 0, e_x-16, e_y -16, 16, 32 );
					amico_rectangle(0, 5, 250, e_x-16, e_y +14, 2, 2 );
#endif
					// amico_rectangle(0, 5, 250,   b_x +4 ,  b_y, 2, 2 );
					// amico_rectangle(0, 5, 250,   b_x+12 ,  b_y, 2, 2 );

					if(
							b_x +4 > e_x - 16 && b_x+12 < e_x + 16
							&& b_y+4 > e_y-18 && b_y-4 < e_y + 14


					)
#else


#ifdef LOG_DEBUG_COL
						// bullet
						// amico_rectangle(255, 0, 0, b_x+4, b_y+4 , 8, 8 );


						amico_rectangle(0, 255, 0, e_x-22, e_y -15, 28, 32 );
					amico_rectangle(0, 5, 250, e_x-22, e_y +14, 2, 2 );
#endif
					// amico_rectangle(0, 5, 250,   b_x +4 ,  b_y, 2, 2 );
					// amico_rectangle(0, 5, 250,   b_x+12 ,  b_y, 2, 2 );

					if(
							b_x +4 > e_x - 22 && b_x+4 < e_x + 1
							&& b_y+4 > e_y-15 && b_y-4 < e_y + 1


					)


#endif
					{


						//	LOG_BUL_COL(" b_x %d > e_x %d - b_x %d < e_x %d - ", b_x, e_x,  b_x , e_x );
						//	LOG_BUL_COL(" b_y %d > e_y %d - e_y %d < e_y %d\n", b_y, e_y,  b_y , e_y );



						LOG_BUL_COL(" bullet hit! %d \n", AI_list[start].AI_hits);


						if(AI_list[start].AI_hits) // AI is still alive
						{
							AI_list[start].AI_hits--;
							AI_list[start].AI_hit_cnt= 255;
							AI_list[start].AI_state = AI_STATE_PLAYER_HIT;

						}
						else // AI is dead
						{


							if(bullet->owner == (t_runner*) &g_player) // process player's shot
							{
								g_gamestate.level_bullets_hit++;

								if(AI_list == g_AI_enemies) // hit enemy - add points
								{
									// g_gamestate.p_score +=10*(g_gamestate.level+1);
									g_gamestate.p_score += GAME_CALCULATE_EMEMY_HIT_SCORE;
									g_gamestate.p_bullets += GAME_CALCULATE_EMEMY_HIT_SCORE>>4;
									amico_play_SFX(SFX_HIT_HEH);
									add_runner_hit(&AI_list[start],2);

									if(g_gamestate.enemy_alive)
										g_gamestate.enemy_alive--;

								}
								else // hit a friend - add bullets or health
								{
									if(g_gamestate.p_bullets < g_gamestate.p_health )
										g_gamestate.p_bullets += GAME_CALCULATE_FRIEND_HIT_ADD_BULLETS;
									else
										g_gamestate.p_health += GAME_CALCULATE_FRIEND_HIT_ADD_HEALTH;



									amico_play_SFX(SFX_HIT_HEH);


									add_runner_hit(&AI_list[start],1);

									if(g_gamestate.friend_alive)
										g_gamestate.friend_alive--;

									//g_gamestate.p_score +=10*(g_gamestate.level+1);
									g_gamestate.p_score += GAME_CALCULATE_EMEMY_HIT_SCORE;
									g_gamestate.level_friends_saved++;


								}


							} // process player shot


							else {// process all audio/lives

								if(AI_list == g_AI_friends  )
								{
									g_gamestate.p_health -=GAME_CALCULATE_PLAYER_BULLET_HIT_FRIEND;


									// AI killing friends hurts player
									amico_play_SFX(SFX_HIT_OOH);


									add_runner_hit(&AI_list[start],1);
									if(g_gamestate.friend_alive)
										g_gamestate.friend_alive--;

								}
								else
								{


									add_runner_hit(&AI_list[start],2);
									amico_play_SFX(SFX_HIT_HEH);

									if(g_gamestate.enemy_alive)
										g_gamestate.enemy_alive--;
								}


							}

							AI_list[start].posX = AI_list[start].AI_hits = AI_list[start].AI_hit_cnt= 0;
						}


						LOG_BUL_COL("remove bullet");
						return 1; // remove bullet
					}



				}
			} // not onwer
	}

	if(AI_list != g_AI_friends)
	{
		AI_list = g_AI_friends;
		start =   0;
		//	LOG_BUL_COL("DOING FRIENDS!\n");
		goto BULLET_RESTART;
	}









	return 0; // no collision
}



// #define CLEAR_ANGLE_ON_SLIDE_FOR_AI
u32 game_collision_move(t_runner * runner, s32 center_offsetDown, s32 center_offsetRight, u32 radius, u32 slide)
{
	u8 dpad =runner->dpad;
	u16 full = runner->speed;
	u16 half = full  >> 1;
	u32 posXf, posYf;
	s32 x;
	s32 y;
	posXf = runner->posX;
	posYf = runner->posY;

	LOG_GAME_UPDATE("\n g_player.shoot_dpad %d g_player.dpad %d g_function_loop();  %x   amico: This is %s() from %s, line %d \n", g_player.shoot_dpad ,g_player.dpad, g_function_loop,__FUNCTION__, __FILE__, __LINE__);
	LOG_GAME_UPDATE("\n dpad %d \n", dpad);

	// process dir circle
	switch( dpad )
	{
	case CONTROL_DPAD_NONE:
		return 0;

		// #define CONTROL_DPAD_RR 0b0001 // right right 1
	case CONTROL_DPAD_RR:
		posXf +=full;
		runner->dir = 1; // left is normal, right is reversed
		// if(dir)
		//	headforward=-headforward;// reverse;
		break;
		//#define CONTROL_DPAD_RU 0b0101 // right up 5
	case CONTROL_DPAD_RU:
		posXf +=full;
		posYf -=half;
		//radiusY = radiusY >>1; // half Y
		runner->dir = 1; // 0 left is normal, 1 right is reversed
		break;
		//#define CONTROL_DPAD_UU 0b0100 // up up 4
	case CONTROL_DPAD_UU:
		posYf -=full;
		// UP/DOWN leave old dir - 0 left is normal, 1 right is reversed
		break;
		//#define CONTROL_DPAD_LU 0b0110 // left up 6
	case CONTROL_DPAD_LU:
		posXf -=full;
		posYf -=half;
		runner->dir = 0; // 0 left is normal, 1 right is reversed
		//	radiusY = radiusY >>1; // half Y
		break;
		//#define CONTROL_DPAD_LL 0b0010 // left left 2
	case CONTROL_DPAD_LL:
		posXf -=full;
		runner->dir = 0; // 0 left is normal, 1 right is reversed
		break;
		//#define CONTROL_DPAD_LD 0b1010 // left down 10
	case CONTROL_DPAD_LD:
		posXf -=full;
		posYf +=half;
		runner->dir = 0; // 0 left is normal, 1 right is reversed
		//	radiusY = radiusY >>1; // half Y
		break;

		//#define CONTROL_DPAD_DD 0b1000 // down down 8
	case CONTROL_DPAD_DD:
		posYf +=full;
		// UP/DOWN leave old dir - 0 left is normal, 1 right is reversed
		break;

		// #define CONTROL_DPAD_RD 0b1001 // right down 9
	case CONTROL_DPAD_RD:
		posXf +=full;
		posYf +=half;
		runner->dir = 1; // 0 left is normal, 1 right is reversed
		//	radiusY = radiusY >>1; // half Y
		break;
	default: // failed
#if 0
		//todo - add debuging
		printf("game_collision_move bad dpad %d not a direction \n\n",dpad);
		printf("game_collision_move bad dpad %d not a direction \n\n",dpad);
		printf("game_collision_move bad dpad %d not a direction \n\n",dpad);
#endif
		//exit(0);
		return 0;//android sends these sometimes
		break;
	}

	// bound checking
	x = posXf>>6;
	y = posYf>>6;

#ifdef LOG_DEBUG_COL


	amico_rectangle(255, 110, 110, x+center_offsetRight, y+center_offsetDown, radius, radius );
	LOG_MAP_COL(" x+center_offsetRight  %d, y+center_offsetDown %d, radius %d \n", x+center_offsetRight, y+center_offsetDown, radius);

#endif


	// +-1 for rounding??
	if( x + center_offsetRight - (radius)  <  MAP_BOUNDING_SIDES )
		return 0;
	if(x + center_offsetRight + (radius) > 320 - MAP_BOUNDING_SIDES)
		return 0;
	if(y +  center_offsetDown <  MAP_BOUNDING_TOP+radius)
		return 0;
	if(y +  center_offsetDown + (radius) > 240 - MAP_BOUNDING_BOT)
		return 0;

#if 0
	if(g_gamestate.level > 4  && radius == 2 )// player bullets go throw walls!
	{
		t_bullet* b = (t_bullet*) runner;

		if( b->owner == (t_runner*) &g_player)
		{
			// no collision
			runner->posX = posXf;
			runner->posY = posYf;
			return 1;
		}
	}
#endif
	// map check 4 corners, it's hacky, but hey
	{
		s32 row, col;
		u32 dataTop, dataBot, cellTopLeft, cellBotRight, cellTopRight, cellBotLeft;
		u32 level = g_gamestate.level + g_gamestate.wave;






		level = level % MAX_LEVEL;

		/*
		if(posX<0 || runner->dir == 0)
			radius=-radius;
		if(posY<0)
			radiusY=-radiusY;
		else if(posY == 0)
			radiusY = 0;
		 */
		row = y;
		row += center_offsetDown;// drop pos to center runner point in map and check
		row += radius;
		row = row >>4;
		dataBot =  g_cur_map[level][row];
		row = y;
		row += center_offsetDown;// drop pos to center runner point in map and check

		if( row > radius)
		{
			row -= radius;
			row = row >>4;
		}
		else
			row = 0;

		dataTop =  g_cur_map[level][row];
		col = x;
		col += center_offsetRight; // center of sprite runner point check
		col += radius;
		col = col>>4;
		cellBotRight= dataBot & (1<< col);
		cellTopRight= dataTop & (1<< col);
		col = x;
		col += center_offsetRight; // center of sprite runner point check
		if( col > radius)
		{
			col -= radius;
			col = col>>4;
		}
		else
			col = 0;



		cellBotLeft= dataBot & (1<< col);
		cellTopLeft= dataTop & (1<< col);

		LOG_MAP_COL("posXf %d posYf %d cellTopRight:%d cellBotRight:%d  cellBotLeft:%d cellTopLeft:%d \n", posXf, posYf, cellTopRight,  cellBotRight, cellBotLeft , cellTopLeft );


		if(cellTopLeft + cellTopRight + cellBotRight + cellBotLeft == 0)
		{
			// no collision
			runner->posX = posXf;
			runner->posY = posYf;
			return 1;
		}

#if 1 // PITA works poorly - needs wall collisions needs to be converted to planes and vectors


		col = 0;
		half = half >> 1;// slide slow down

		if(slide)//slide) //do slide move
			switch( dpad )
			{

			case CONTROL_DPAD_RU: // right up
				//safe - CONTROL_DPAD_RU TOP RIGHT cellTopRight:0 cellTopLeft:0 cellBotRight:2048
#ifdef SAFE
				if(cellTopRight+cellTopLeft==0) // can move up
				{
					runner->posY = posYf;
					col++;
				}
				else if(cellTopRight + cellBotRight  == 0) // can move right
				{
					runner->posX = posXf;
					col++;
				}
#else
				//cellTopRight:2048 cellBotRight:2048  cellBotLeft:0 cellTopLeft:0
				if(cellTopLeft==0) // can move up
				{
#ifdef CLEAR_ANGLE_ON_SLIDE_FOR_AI
					runner->dpad = CONTROL_DPAD_U; // clear for AI
#endif
					runner->posY = posYf-half;
					col++;
				}
				else if(cellBotRight  == 0) // can move right
				{
					runner->posX = posXf-half;

#ifdef CLEAR_ANGLE_ON_SLIDE_FOR_AI
					runner->dpad = CONTROL_DPAD_R; // clear for AI
#endif
					col++;
				}

#endif
				break;


			case CONTROL_DPAD_LU:
#ifdef SAFE
				if(cellTopLeft+cellTopRight==0) // can move up
				{
					runner->posY = posYf-half;
					col++;
				}
				else if(cellTopLeft+cellBotLeft  == 0) // can move left
				{
					runner->posX = posXf+half;
					col++;
				}
#else
				if(cellTopRight==0) // can move up
				{
					runner->posY = posYf-half;

#ifdef CLEAR_ANGLE_ON_SLIDE_FOR_AI
					runner->dpad = CONTROL_DPAD_U; // clear for AI
#endif
					col++;
				}
				else if(cellBotLeft  == 0) // can move left
				{
					runner->posX = posXf+half;
#ifdef CLEAR_ANGLE_ON_SLIDE_FOR_AI
					runner->dpad = CONTROL_DPAD_L; // clear for AI
#endif
					col++;
				}
#endif
				break;
			case CONTROL_DPAD_LD:
#ifdef SAFE
				if(cellBotLeft+cellBotRight==0) // can move down
				{
					runner->posY = posYf+half;
					col++;
				}
				else if(cellBotLeft+cellTopLeft == 0) // can move left
				{
					runner->posX = posXf+half;
					col++;
				}
#else
				if(cellBotRight==0) // can move down
				{
					// 	runner->dpad = CONTROL_DPAD_D; // clear for AI
					runner->posY = posYf+half;
					col++;
				}
				else if(cellTopLeft == 0) // can move left
				{
					runner->posX = posXf+half;

#ifdef CLEAR_ANGLE_ON_SLIDE_FOR_AI
					runner->dpad = CONTROL_DPAD_L; // clear for AI
#endif
					col++;
				}
#endif
				break;

				// LL & RR here just in case stuck in the slide
			case CONTROL_DPAD_LL:
#ifdef SAFE
				if(cellBotLeft+cellBotRight==0) // can move down
				{
					runner->posY = posYf+half;
					col++;
				}
				else if(cellBotLeft+cellTopLeft == 0) // can move left
				{
					runner->posX = posXf+half;
					col++;
				}
#else

				if(cellBotLeft + cellTopLeft == 0) // can move left
				{
					runner->posX = posXf+half;

#ifdef CLEAR_ANGLE_ON_SLIDE_FOR_AI
					runner->dpad = CONTROL_DPAD_L; // clear for AI
#endif
					col++;
				}
#endif
				break;




			case CONTROL_DPAD_RR:
#ifdef SAFE
				if(cellBotRight+cellBotLeft==0) // can move down
				{
					runner->posY = posYf+half;
					col++;
				}
				else if(cellBotRight+cellTopRight  == 0) // can move right
				{
					runner->posX = posXf-half;
					col++;
				}
#else
				if(cellBotRight + cellTopRight  == 0) // can move right
				{
					runner->posX = posXf-half;
					runner->dpad = CONTROL_DPAD_R; // clear for AI
					col++;
				}
#endif
				break;


			case CONTROL_DPAD_RD:
#ifdef SAFE
				if(cellBotRight+cellBotLeft==0) // can move down
				{
					runner->posY = posYf+half;
					col++;
				}
				else if(cellBotRight+cellTopRight  == 0) // can move right
				{
					runner->posX = posXf-half;
					col++;
				}
#else
				if(cellBotLeft==0) // can move down
				{
					runner->posY = posYf+half;
					// 					runner->dpad = CONTROL_DPAD_D; // clear for AI
#ifdef CLEAR_ANGLE_ON_SLIDE_FOR_AI
					runner->dpad = CONTROL_DPAD_D; // clear for AI
#endif
					col++;
				}
				else if(cellTopRight  == 0) // can move right
				{
					runner->posX = posXf-half;
					runner->dpad = CONTROL_DPAD_R; // clear for AI
					col++;
				}
#endif
				break;






			default:
				break;
			}
		// slide logic requires more edge (middles) sampling!
		// no move, collision

		return col;

#else
		return 0;
#endif // PITA slide

	}
}

void game_render(void)
{

	render_top();
	render_map();

	render_fires();
	render_runner_hits();
	render_bullets();

	if(g_player.AI_hit_cnt)
	{

		if(g_game_counter & 8)
			amico_rectangle(g_player.AI_hit_cnt, g_player.AI_hit_cnt, g_player.AI_hit_cnt, (g_player.posX>>6)-16, (g_player.posY>>6) -16, 16, 32 );
		else
			amico_rectangle(255,255, 255, (g_player.posX>>6)-16, (g_player.posY>>6) -16, 16, 32 );


		g_player.AI_hit_cnt--;
	}

	render_runner( (t_runner*)&g_player, 3);//.frame, g_player.posX, g_player.posY,	g_player.dir & 1);


}


// data external file youtuber list - clunky
#include "amico.inc"


#ifdef __ANDROID__
// ANDROID uses CPP not C
}
#endif



