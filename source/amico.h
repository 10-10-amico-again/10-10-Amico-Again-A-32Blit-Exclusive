/*
 *
 PUBLIC DOMAIN 2022
 THIS CODE IS A HACKY MESS - READ IT AT YOUR OWN RISK!
 *
 */

#ifndef AMICO_AGAIN
#define AMICO_AGAIN

#include <stdlib.h>
#include <stdio.h>
#define DATE_STRING "2022-OCT-02"

#ifdef __NOT_USED__
 

 
#else



#include <string.h>
#include "build.h" // build def's changed before different builds, easier then setting make param's PITA!
#define BUILD_STRING "                           FINAL BUILD: " DATE_STRING "   AUDIO MADE WITH GOLDWAVE AND AUDACITY, GRAPHICS MADE WITH GIMP AND TILE STUDIO. THANKS GOES TO THE 32BLIT COMMUNITY, ESPECIALLY DAFT_FREAK, TINWHISKER, AHNLAK AND GADGETOID.   "



#ifdef __ANDROID__


//https://stackoverflow.com/questions/10274920/how-to-get-printf-messages-written-in-ndk-application
#include <android/log.h>

extern int android_debugf( const char *format, ...);

#define  LOG_TAG    "amico"

#define  ANDROID_LOG(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  printf ANDROID_LOG 


#endif // #ifdef __ANDROID__



//save location:  ~/.local/share/
#endif





// #define BETA_DEMO
// #define BOSS_TEST


//-------------------------------------------------------------------------------------------------- #define's


#if 1
#define _RELEASE_
#else
#define _DEBUG_
#endif

#if 0
#ifdef UNIT_32BLIT
#undef _DEBUG_
#define _RELEASE_
#endif
#endif


#ifdef _RELEASE_
#undef _DEBUG_
#define LOG_SCROLL_TEXT	//  printf
#define IF_SKIPP_RANDOM   //if(0)
#define MACRO_NO_SAVE_LOADING //return 0;
#else
#define LOG_SCROLL_TEXT	  printf
#define IF_SKIPP_RANDOM  if(0)
#define MACRO_NO_SAVE_LOADING //return 0;
#endif

#ifdef _DEBUG_
#define SCROLL_TEXT_LOCK 0
#else
#define SCROLL_TEXT_LOCK 1
#endif // _DEBUG_

#define INTRO_SCROLL_TEXT_SPEED 2 // 3 SLOW 2 FAST - scrolling tick speed for g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN





// this printf doesn't get removed

// magic number to get intro to correct place!
#define  MACRO_SKIP_TO_INTRO_COUNTER  {g_game_counter = AMICO_NONE_BOSSES+1; 	g_game_counter = g_game_counter<<7;}

extern void intern_randomize_init_lists(void);
#define MACRO_GAME_RESET_AND_RANDOMIZE_LIST  game_reset(); intern_randomize_init_lists();

#if 0

// to easy #define  GAME_CALCULATE_SMART_BOMB_COST (  (10 * (1+g_gamestate.level) ) + (g_gamestate.wave * 5) )
#define  GAME_CALCULATE_SMART_BOMB_COST (   ((20+g_gamestate.level) *  g_gamestate.wave  ) )
#define  GAME_CALCULATE_BONUS 1010
//(GAME_CALCULATE_SMART_BOMB_COST * 10)


#define  GAME_CALCULATE_FRIEND_HIT_ADD_SCORE  (  (10 * (1+g_gamestate.level) ) + ( (51-g_gamestate.wave) * 10) )
#define  GAME_CALCULATE_FRIEND_HIT_ADD_HEALTH   GAME_CALCULATE_FRIEND_HIT_ADD_SCORE
#define  GAME_CALCULATE_FRIEND_HIT_ADD_BULLETS (10 * (g_gamestate.level+10))

#define  GAME_CALCULATE_EMEMY_HIT_SCORE    (  (10 * (1+g_gamestate.level) ) + ((g_gamestate.wave) * 10) ) //(  ( (1+g_gamestate.level) ) + (g_gamestate.wave * 2) )
// #define  GAME_CALCULATE_END_WAVE_BONUS ( ( friends_saved_avg* ( (g_gamestate.level+1)*2) ) + (bulletperc *( (g_gamestate.wave)) ) )
#define  GAME_CALCULATE_PLAYER_BULLET_HIT  (  (100 * (1+g_gamestate.level) )  + ((50-g_gamestate.wave) * 10))  // ( (g_gamestate.level+1)*20 )
#define  GAME_CALCULATE_PLAYER_BULLET_HIT_FRIEND  (  (50 * (1+g_gamestate.level) )  + ((50-g_gamestate.wave) * 5))   //( (g_gamestate.level+1)*10 ) //( (g_gamestate.level+1)*11 + ( (g_gamestate.wave)*10 ) )
// #define  GAME_CALCULATE_END_WAVE_BONUS (( ( ( friends_saved_avg* ( ((1+g_gamestate.level)*10)  ) ) + (bulletperc *( (g_gamestate.wave)) ) ) )+1)// div 4
#define  GAME_CALCULATE_END_WAVE_BONUS  ( (friends_saved_avg* ( ((1+g_gamestate.level)*10)  ) + (bulletperc *( (g_gamestate.wave)) )+8) >> 1)// div 4


#else



// to easy #define  GAME_CALCULATE_SMART_BOMB_COST ((1+g_gamestate.level)*  ((1+g_gamestate.level) * (1+g_gamestate.level) )) + (g_gamestate.wave * 5) )
#define  GAME_CALCULATE_SMART_BOMB_COST (   (( (g_gamestate.wave) * 2)*  ((1+g_gamestate.level) * (1+g_gamestate.level) )) )
#define  GAME_CALCULATE_BONUS 1010
//(GAME_CALCULATE_SMART_BOMB_COST * 10)


#define  GAME_CALCULATE_FRIEND_HIT_ADD_SCORE  (  8 *  1+( (g_gamestate.level) * (g_gamestate.level) ) )
#define  GAME_CALCULATE_FRIEND_HIT_ADD_HEALTH   (  (30 * ( 1+(g_gamestate.level) * (g_gamestate.level)  ) )  )  //  (  50 *  (1+( (g_gamestate.level) * (g_gamestate.level) ) ) )
#define  GAME_CALCULATE_FRIEND_HIT_ADD_BULLETS  ( GAME_CALCULATE_FRIEND_HIT_ADD_HEALTH + g_gamestate.wave +( (g_gamestate.level) * (g_gamestate.level) ))

#define  GAME_CALCULATE_EMEMY_HIT_SCORE    ( GAME_CALCULATE_FRIEND_HIT_ADD_HEALTH  ) //(  ( (1+g_gamestate.level) ) + (g_gamestate.wave * 2) )
// #define  GAME_CALCULATE_END_WAVE_BONUS ( ( friends_saved_avg* ( (g_gamestate.level+1)*2) ) + (bulletperc *( (g_gamestate.wave)) ) )
#define  GAME_CALCULATE_PLAYER_BULLET_HIT  (  (100 * ( (g_gamestate.level) * (g_gamestate.level)  ) )+ (51-g_gamestate.wave)*10 )  // ( (g_gamestate.level+1)*20 )
#define  GAME_CALCULATE_PLAYER_BULLET_HIT_FRIEND (  (50 * ( 1+(g_gamestate.level) * (g_gamestate.level)  ) )  )   //( (g_gamestate.level+1)*10 ) //( (g_gamestate.level+1)*11 + ( (g_gamestate.wave)*10 ) )
// #define  GAME_CALCULATE_END_WAVE_BONUS (( ( ( friends_saved_avg* ( ((1+g_gamestate.level)*10)  ) ) + (bulletperc *( (g_gamestate.wave)) ) ) )+1)// div 4
#define  GAME_CALCULATE_END_WAVE_BONUS  ( ( (  (friends_saved_avg*bulletperc) * ( (g_gamestate.level+1) * g_gamestate.wave )  ) >> 8)+10)>9999?9999:( ( (  (friends_saved_avg*bulletperc) * ( (g_gamestate.level+1) * g_gamestate.wave )  ) >> 8)+10) // div 4



#endif


//#define SPLASH_MAX_CYCLES 1024+512

// #define LOG_DEBUG_COL

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char s8;
// #define s8 signed char
typedef signed short s16;
typedef signed int s32;



#ifdef _DEBUG_


#ifdef __ANDROID__

#define LOG_ZERO  ANDROID_LOG
#define LOG_INTRO     ANDROID_LOG
#define LOG_INTRO2    ANDROID_LOG
#define LOG_SELECT    ANDROID_LOG
#define LOG_PAUSE     ANDROID_LOG
#define LOG_RAND2     ANDROID_LOG
#define LOG_RAND      ANDROID_LOG
#define LOG_BUL_COL   ANDROID_LOG
#define LOG_BULLET    ANDROID_LOG
#define LOG_MAP_COL   ANDROID_LOG
#define LOG_GAME_UPDATE    ANDROID_LOG
#define LOG_GAME_WAVE  //  ANDROID_LOG
#define LOG_GAME_WAVE2 //   ANDROID_LOG
#define LOG_AUDIO 		//  ANDROID_LOG
#define LOG_NPC  // ANDROID_LOG
#define LOG_FLASHING_HEADS  // ANDROID_LOG
#define LOG_FIN  // ANDROID_LOG
#define LOG_TEXT // ANDROID_LOG
#define LOG_FIN_TEXT2 //ANDROID_LOG
#define LOG_DEST //ANDROID_LOG
#define LOG_SHOOT_BULLET //ANDROID_LOG
#define LOG_FIN_TEXT  // ANDROID_LOG



#else //#ifdef __ANDROID__


#define LOG_ZERO // printf
#define LOG_INTRO    // printf
#define LOG_INTRO2  //   printf
#define LOG_SELECT    // printf
#define LOG_PAUSE     // printf
#define LOG_RAND2    //    printf
#define LOG_RAND   //    printf
#define LOG_BUL_COL   // printf
#define LOG_BULLET    // printf
#define LOG_MAP_COL   // printf
#define LOG_GAME_UPDATE // printf
#define LOG_GAME_WAVE     //   printf
#define LOG_GAME_WAVE2   //   printf
#define LOG_AUDIO 		//  printf
#define LOG_NPC //  printf
#define LOG_FLASHING_HEADS  // printf
#define LOG_FIN    //  printf
#define LOG_FIN_TEXT      printf
#define LOG_FIN_TEXT2  //  printf
#define LOG_TEXT // printf
#define LOG_DEST // printf
#define LOG_SHOOT_BULLET // printf
#endif





#else

#define LOG_ZERO // printf
#define LOG_INTRO    // printf
#define LOG_INTRO2    // printf
#define LOG_SELECT    // printf
#define LOG_PAUSE     // printf
#define LOG_RAND2    //  printf
#define LOG_RAND   //    printf
#define LOG_BUL_COL   // printf
#define LOG_BULLET   //  printf
#define LOG_MAP_COL   // printf
#define LOG_GAME_UPDATE   // printf
#define LOG_GAME_WAVE     // printf
#define LOG_GAME_WAVE2   // printf
#define LOG_AUDIO 		//  printf
#define LOG_NPC //  printf
#define LOG_FLASHING_HEADS // printf
#define LOG_FIN // printf
#define LOG_DEST // printf
#define LOG_TEXT // printf
#define LOG_FIN_TEXT // printf
#define LOG_FIN_TEXT2 // printf
#define LOG_SHOOT_BULLET //  printf
#endif



#define INIT_BONUS_INCR 10000

#define NEW_LEVEL_PLAYER_SPEED_INC 3

#define AMICO_BOSSES 16 // count from 0

#define MAX_SHILLS 50 // count from zero
// #define MAX_HATERS 49 // count from zero

#define AMICO_NONE_BOSSES (MAX_SHILLS-AMICO_BOSSES) // count from 0 ( 0-33 none bosses)
//#define SHARED_HEAD_SLOT 4

#define MAX_SHOOT_ANGLE_TEST 25
#define INIT_SHOOT_DIST 40
#define AI_SHOOT_DIST_INC 5
#define PLAYER_INIT_SPEED 35
#define  PLAYER_SHOOT_CENTER_DOWN -(6<<6) //up
#define  PLAYER_SHOOT_CENTER_LEFT 16<<6

//#define CHEATS_PLAYER_BIG_HEAD 1
//#define CHEATS_TEST_MODE 1<<1
/*
#define CHEATS_UNLIMITED_BULLETS 1<<2
#define CHEATS_UNLIMITED_LIVES 1<<3
#define CHEATS_UNLIMITED_HARD 1<< 4
 */
#define BUTTON_PRESS_TIME 20


#define CONTROL_DPAD_NONE 0
#define CONTROL_DPAD_R 1 // 0b0001 // right 1
#define CONTROL_DPAD_L 2 // 0b0010 // left 2
#define CONTROL_DPAD_U 4  // 0b0100 // up 4
#define CONTROL_DPAD_D 8  // 0b1000 // down 8

#define CONTROL_DPAD_ALL_DIR 15
#define CONTROL_DPAD_UP_DOWN 12
#define CONTROL_DPAD_LEFT_RIGHT 3



// circle counter clockwise
#define CONTROL_DPAD_RR 1 // 0b0001 // right right 1
#define CONTROL_DPAD_RU 5 // 0b0101 // right up 5

#define CONTROL_DPAD_UU 4 // 0b0100 // up up 4

#define CONTROL_DPAD_LU 6 // 0b0110 // left up 6
#define CONTROL_DPAD_LL 2 // 0b0010 // left left 2
#define CONTROL_DPAD_LD 10 // 0b1010 // left down 10

#define CONTROL_DPAD_DD 8 // 0b1000 // down down 8
#define CONTROL_DPAD_RD 9 // 0b1001 // right down 9


#define AI_STATE_PLAYER_EVADE 1
#define AI_STATE_PLAYER_TOWARD 2
#define AI_STATE_PLAYER_HIT 3
#define AI_STATE_RANDOM1 4
#define AI_FIRE_TIME_START 230


#ifdef INST_AMICO_TEXTURES
#define INSTANCE
#else
#define INSTANCE extern
#endif


// used with g_gamestate.shell_corners
#define MAP_SHELL_CORNER_TOP_LEFT  0
#define MAP_SHELL_CORNER_TOP_RIGHT 1
#define MAP_SHELL_CORNER_BOT_RIGHT 2
#define MAP_SHELL_CORNER_BOT_LEFT  3




#define CONTROL_BUT_NONE 0
#define CONTROL_BUT_A   1 //  0b0001
#define CONTROL_BUT_B   2 //  0b0010
#define CONTROL_BUT_MENU 4 // 0b0100
#define CONTROL_BUT_HOME 8 // 0b1000
//#define CONTROL_BUT_X    0b0100
//#define CONTROL_BUT_Y    0b1000





#define TOP_PANEL_R 55
#define TOP_PANEL_G 55
#define TOP_PANEL_B 55

/*

#define CLEAR_BG_RED		133
#define CLEAR_BG_GREEN	133
#define CLEAR_BG_BLUE		133
 */


#define MAP_BOUNDING_SIDES 4
#define MAP_BOUNDING_TOP 32
#define MAP_BOUNDING_BOT 1

#define SIDE_SHILL 0
#define SIDE_HATER 1


#define SIDE_FRIEND 0
#define SIDE_ENEMY 1



#define MAP_BRICK_TPAGE 4
#define MAP_BRICK_U     0
#define MAP_BRICK_V     0


#define AMICO_GOOD_SHELL_TPAGE  3
#define AMICO_GOOD_SHELL_TEXTU  1*32
#define AMICO_GOOD_SHELL_TEXTV  7*32


#define AMICO_BAD_SHELL_TPAGE  3
#define AMICO_BAD_SHELL_TEXTU  1*32
#define AMICO_BAD_SHELL_TEXTV  1*32

#define MAP_START_PLAYER_POSX (160+7)<<6;
#define MAP_START_PLAYER_POSY (120+10)<<6;


#define MAP_START_ENEMY_POSX (0+32)<<6;
#define MAP_START_ENEMY_POSY (240-32)<<6;



#define MAX_LEVEL 51










#define BULLET_FIRE_TPAGE 2
#define BULLET_FIRE_U 0
#define BULLET_FIRE_V 248
#define BULLET_SPEED 140
#define MAX_ENTITIES 32


// play voices
#define  CHEAT_VOICE_RIGHT  0,0,0,0, 0,0,0,0

#define  CHEAT_VOICE_LEFT  0,0,0,0, 0,0,0,0


#define  CHEAT_VOICE_UP  0,0,0,0, 0,0,0,0

#define  CHEAT_VOICE_DOWN 0,0,0,0, 0,0,0,0

// testing mode
#define  CHEAT_TESTING 0,0,0,0, 0,0,0,0



//  unlock bosses -
#define  CHEAT_UNLOCK_BOSSES 0,0,0,0, 0,0,0,0


//    big heads 
#define    0,0,0,0, 0,0,0,0


//  bullets and health  
#define   0,0,0,0, 0,0,0,0

//  next level 
#define   0,0,0,0, 0,0,0,0




// CHEAT_ENDING   
#define  0,0,0,0, 0,0,0,0

#define CHEAT_TOTAL 10




//-------------------------------------------------------------------------------------------------- typedef's

typedef struct {
	s8 name[32];
	u8  TPAGE;
	u8 textU, textV;
	// u8 color[3];
}t_data_head32;






typedef struct {
	u16 posX, posY;
	u8 dpad; //8bit control_dpad
	u8 speed;
	// volX/Y ???

	u8 dir;

	// head32
	u8 TPAGE;
	u8 textU, textV;

	//running man 32
	u8 frame; // 8 anim
	u8 frame_cnt; // 8 anim

	u8 AI_hit_cnt;
	// t_runner



}t_runner; //32x64



typedef struct {
	u16 posX, posY;
	u8 dpad; //8bit control_dpad
	u8 speed;
	u8 sprite;
	t_runner* owner;
	// volX/Y ???

}t_bullet; //32x64



typedef struct {
	u16 posX, posY;
	u8 speed;
} t_pos;



// same as runner but with player info
typedef struct {
	u16 posX, posY;
	u8 dpad; //8bit control_dpad
	u8 speed;
	// volX/Y ???

	// volX/Y ???

	u8 dir;

	// head32
	u8 TPAGE;
	u8 textU, textV;

	//running man 32
	u8 frame; // 8 anim
	u8 frame_cnt; // 8 anim

	u8 AI_hit_cnt;
	// runner_t


	u8 shoot_dpad;
	u8 shoot_timer; //8bit control_dpad





	// tail
	//t_tail32 tail[32];

}t_player; //32x64



// same as runner but with player info


// same as runner but with player info
typedef struct {
	u32 p_score;
	s32 p_health;
	u32 p_bullets;
	u8 p_side;


	u8 killed;
	u8 rescuded;

	u8 enemy_next;
	u8 friend_next;

	u8 enemy_alive;
	u8 friend_alive;


	u8 wave;
	u8 level;

	u8 shell_corners;
	u8 shell_corners_ticks;

	u8 BG_SNARTBOMB;
	u8 BG_MAIN;
	//u8 BG_SIDES;


	u8 cheat_big_heads;
	u8 cheat_testing;
	u8 AI_shoot_dist;
	u32 time;
	u32 bullet_acc;
	u16 level_bullets_used;
	u16 level_bullets_hit;
	s8 level_friends_saved;


}t_game_state; //32x64





/*
typedef struct {
	u16 posX, posY;
	u8 dpad; //8bit control_dpad
	u8 speed;
	// volX/Y ???
	// volX/Y ???

	u8 dir;

	// head
	u8 TPAGE;
	u8 textU, textV;

}t_tail32;
 */

typedef struct
{

	u16 posX, posY;
	u8 dpad; //8bit control_dpad
	u8 speed;
	// volX/Y ???

	// volX/Y ???

	u8 dir;

	// head32
	u8 TPAGE;
	u8 textU, textV;

	//running man 32
	u8 frame; // 8 anim
	u8 frame_cnt; // 8 anim

	u8 AI_hit_cnt;
	// t_runner


	u8 shoot_dpad;
	u8 shoot_timer; //8bit control_dpad

	//	u8 seed;
	u8 phase;
	u8 AI_state;
	u8 AI_tick;
	u8 AI_personal_tolerance;
	u8 AI_hits;


}t_AI_youtubers;



typedef struct {
	u16 posX; // no posY, use runner pointer info
	u8 speed;
	u8 side;
	t_AI_youtubers *runner;
} t_runner_hit;





#if 0
delete me!
// same as runner but with player info
typedef struct {

	u32 a;

}t_game_RAM; //32x64

#endif

//-------------------------------------------------------------------------------------------------- GLOBAL's



extern t_data_head32 g_texture_map_haters[];
extern t_data_head32 g_texture_map_shills[];

// char g_tim_header[]; // put here for lolz

//store data
INSTANCE u32 g_total_bullets_used;
INSTANCE u32 g_total_bullets_hit;

INSTANCE u32 g_total_friends_saved;
INSTANCE u32 g_total_friends;
INSTANCE u32 g_shell_bonus;



INSTANCE u32 g_game_CUR_BONUS;
INSTANCE s8 g_unlocked_bosses_level;
INSTANCE t_game_state g_gamestate;
INSTANCE t_player g_player;


#ifdef __NOT_USED__
INSTANCE s8 g_SET_SFX_VOL; //max
INSTANCE s8 g_SET_BGM_VOL; //max

#else
INSTANCE u16 g_SET_SFX_VOL; //max
INSTANCE u16 g_SET_BGM_VOL; //max
#endif



INSTANCE u32 g_game_start_time;
INSTANCE u32 g_game_counter;
INSTANCE u32 g_text_scroll_counter;

INSTANCE void (*g_function_loop)(void);


extern  u32 g_cur_map[MAX_LEVEL+1][15];
extern s8 g_SCROLL_TEXT_YOUTUBER_FLASH_SCREEN[]; //string
extern s8 g_LEVEL_FINISH_CHEAT[];// URL strings

INSTANCE t_bullet *g_bullets;
INSTANCE t_pos *g_fires;
INSTANCE t_runner_hit *g_runner_hits;

INSTANCE t_AI_youtubers *g_AI_friends;
INSTANCE t_AI_youtubers *g_AI_enemies;



INSTANCE u8 g_AI_shoot_dist; // 40
INSTANCE u8 g_no_boss_flashing;


//-------------------------------------------------------------------------------------------------- functions

// game states

void update_select(void);
void update_intro(void);
void update_game(void);
void update_game_AI(void);
void update_pause(void);
void update_new_game_wave(void);
void update_dead(void);
void update_splash(void);
void update_level_zero(void);
void update_final_credits(void);

// render things
#define FONT_TPAGE 2
#define FONT_Y_OFFSET  224 // start Y


void render_text(u32 posx, u32 posy, s32 scale, char *string);

void render_fires(void);
void render_runner(t_runner * runner,  u32 side);
void render_runner_hits(void);
void render_bullets(void);
void render_map(void);
void render_top(void);


//void amico_intro_splash(void);
int amico_save_data(void);
int amico_load_data(void);


//void amico_mainloop(u32 );



// Primitives
void amico_text_continue(void);
//void amico_text_pressA(void);
//void amico_text_init(void);
//void amico_text_top1_line( s8 *name );
//void amico_text_top2_line( s8 *name );
void amico_rectangle(u8 r, u8 g, u8 b, u32 screen_posX, u32 screen_posY, u32 w, u32 h );
void amico_sprite(u8 TPAGE, u32 texture_u, u32 texture_v, u32 texture_w, u32 texture_h, s32 posX, s32 posY, s32 scale , u8 h_flip);
void amico_init(void);
void amico_deinit(void);
u32 amico_play_SFX(u32 id); // 0 = left, 1 = center, 2 = right
u32 amico_stop_SFX(u32 id, u32 voice);
void amico_play_BGM_audio(int side);
void amico_BGM_quiet_time(int quiet_time); // 1 true reduce vol - 0 false increase back to normal BG volume
void amico_stop_all_SFX(void);

void amico_secret_end(void);


u32 game_AI_enemies(void);
u32 game_AI_friends(void);

u32 game_bullet_runner_collision( t_bullet *bullet);
u32 game_bullet_bullet_collision( void );


u32 game_collision_move(t_runner * runner, s32 center_offsetDown, s32 center_offsetRight, u32 radius, u32 slide);
void game_render(void);
void game_reset(void);


u32 add_NPC(u32 shell, u8 AI_state, u8 start, u8 side);

void add_smart_bomb(void);
u32 add_bullet(t_runner * runner, u8 dpad, u32 center_offsetDown_fixed, u32 center_offsetLeft_fixed, u32 side);
void add_fires(u32 posX, u32 posY );
void add_runner_hit(t_AI_youtubers * runner, u8 side);




//convert wav files to 8bit unsigned-integer 22050mhz samples
// in game SFX
#define SFX_HIT_HEH  0 // 00-kill-shill.wav.fast.wav
#define SFX_HIT_OOH  1 // 00-kill-hater.wav
#define SFX_MOO1  2 // 01 hater shoot 1 moo1.wav.fast.wav
#define SFX_MOO2  3 // 01 hater shoot 2 moo2.wav.fast.wav
#define SFX_CHICKEN1  4 // 01 shill shoot 1 chicken bokak1.wav.fast.wav
#define SFX_CHICKEN2  5 // 01 shill shoot 2 chicken bokak2.wav.fast.wav
#define SFX_AMICO_AGAIN  6 // 99-10-10-amicooo-again.wav.fast.wav
#define SFX_TOMMY_TALK 7 // START OF TT TALKING BS GOOD THEN BAD ALTERNATE AND GET WORSE AS YOU GO

INSTANCE u32 g_stereo_counter_random;

#define ADD_TO_SFX 11 // random TT SFX

#ifdef __NOT_USED__


#define  MACRO_PLAY_STEREO_SFX(__ID__)  amico_play_SFX(__ID__); amico_play_SFX(__ID__); // stereo play twice

extern void RenderClear(void);


extern volatile u8 *g_random;



#define MACRO_CLEAR_SCREEN 
#define SPLASH_MAX_CYCLES 1024+990


#define SFX_LAST 47 // last SFX


#define VOL_MAX 127
#define BGM_VOL_DEFAULT 100
#define SFX_VOL_DEFAULT VOL_MAX
#define VOL_CHANGE 10


#define TOMMY_TALK_WHAT_EGO  23
#define TOMMY_TALK_JUST_NEED_THE_MONEY 28
#define TOMMY_TALK_NOT_REAL_FRIENDS 30
#define TOMMY_TALK_HARDCORE_ELITIST 15
#define TOMMY_TALK_SKIP_DEVELOPMENT 38
#define TOMMY_TALK_OUT_OF_BUSINESS 44

#define TOMMY_TALK_PROMOTE_YOUR_CHANNEL 16
#define TOMMY_TALK_SINGLE_NO_FRIENDS 39


#define TOMMY_TALK_GET_YOUR_NAME_IN_CREDITS 41
#define TOMMY_TALK_GAMING_RACIST 43

#define TOMMY_TALK_WHOS_LAUGHING_NOW  23 //ego //27 negative and evil
#define TOMMY_TALK_WHY_DO_YOU_HATE_ME 25





// random noob hacks!!!


u32 bad_random(void);
u32 button_seed_random(void);


#define RANDOM_SEED(__RCNT__) VSync(0); //removed
#define button_seed_random button_seed_random
#define rand bad_random
#define srand (--ERROR-- removed srand not required)




#define   MACRO_SLOW_DOWN  

#endif
 
// length X4 4465�4 = 17860
#define  MACRO_SET_GAME_TO_FINAL_CREDITS 	{g_game_counter=15860;  g_text_scroll_counter=0; g_function_loop = update_final_credits; amico_play_BGM_audio(3);}

#else

#define  MACRO_SET_GAME_TO_FINAL_CREDITS 	{g_game_counter=15000; g_text_scroll_counter=0; g_function_loop = update_final_credits; amico_BGM_quiet_time(1); amico_play_BGM_audio(3);}


// 32blit VOL is 16bit 0-65535
#define  MACRO_PLAY_STEREO_SFX(__ID__)  amico_play_SFX(__ID__); // played once, no stereo!

#define MACRO_CLEAR_SCREEN // 32blit doesn't need this
#define SFX_LAST 73 // 32blit has more Tommy talk
#define BGM_VOL_DEFAULT 37000 //12766
#define SFX_VOL_DEFAULT 40000 //32766
#define VOL_MAX 65535
#define VOL_CHANGE 1023*4

#define TOMMY_TALK_WHAT_EGO  23
#define TOMMY_TALK_JUST_NEED_THE_MONEY 54
#define TOMMY_TALK_NOT_REAL_FRIENDS 36
#define TOMMY_TALK_AMICO_WARS_BATTLING 74
#define TOMMY_TALK_HARDCORE_ELITIST 21
#define TOMMY_TALK_SKIP_DEVELOPMENT 44
#define TOMMY_TALK_OUT_OF_BUSINESS 45

#define TOMMY_TALK_PROMOTE_YOUR_CHANNEL 40
#define TOMMY_TALK_GET_YOUR_NAME_IN_CREDITS 32

#define TOMMY_TALK_SINGLE_NO_FRIENDS 34
#define TOMMY_TALK_GAMING_RACIST 27

#define TOMMY_TALK_NEGATIVE_EVIL 33
#define TOMMY_TALK_IT_DOESNT_MEAN_HELL 11
#define TOMMY_TALK_WHOS_LAUGHING_NOW 23
#define TOMMY_TALK_WHY_DO_YOU_HATE_ME 22


//#define SPLASH_MAX_CYCLES 1024+512-70
#define SPLASH_MAX_CYCLES 1024+990
#define   MACRO_SLOW_DOWN {}
#define RANDOM_SEED(__RCNT__)
 
// #define printf //

// use 32blit's random
extern u32 random_32blit(void);
#define rand() random_32blit()
//#define srand //remove srand calls for 32blit, not required



#endif // 32blit

#endif //#ifndef AMICO_AGAIN


