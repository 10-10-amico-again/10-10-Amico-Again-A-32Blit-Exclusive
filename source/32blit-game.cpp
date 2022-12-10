/*
 *
 PUBLIC DOMAIN 2022
 THIS CODE IS A HACKY MESS - READ IT AT YOUR OWN RISK!
 *
 */

#include "32blit.hpp"
#include "build.h" // build defines changed before diferent builds


//created via assets.yml
#include "assets-images.hpp"
#include "assets-SFX.hpp"
#include "assets-BGM-intro.hpp"
#include "assets-BGM-haters.hpp"
#include "assets-BGM-shills.hpp"


// 32blit image --input_file y3-256.png  --output_file y3.cpp  --output_format c_source --symbol_name TEXT  --packed yes
using namespace blit;


#define SAVE_CHECK_STRING_START "Amico-Again-BUILD: 2022 JUNE 16" //32 chars
#define SAVE_CHECK_STRING_END "aMICO-aGAIN-build: 2022 june 16" //32 chars

// #define TESTING // auto smartbomb




#if 1 //def _RELEASE_


#define LOG_DATA  // blit::debugf
#define LOG_EXIT  //  blit::debugf
#define LOG_SND   //  blit::debugf
#define LOG_DEL  //  blit::debugf
#define LOG_PAD  //  blit::debugf

#else



			#ifdef __ANDROID__
			#include <android/log.h>
			#define  LOG_TAG    "amico"
			#define  LOG_DATA(...) // __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
			#define  LOG_EXIT(...) // __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
			#define  LOG_SND(...)  // __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
			#define  LOG_DEL(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
			#define  LOG_PAD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)



			#else // #ifdef __ANDROID__

			#define LOG_DATA   blit::debugf
			#define LOG_EXIT    blit::debugf
			#define LOG_SND     blit::debugf
			#define LOG_DEL    blit::debugf
			#define LOG_PAD    blit::debugf
			#endif

#endif

#ifdef __ANDROID__
#define LOG_ERR(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#else
#define LOG_ERR blit::debugf
#endif



#define SOUND_ADD_DATA_POINTER 512
#define SOUND_MINUS_LEN 512

// audio implementation based from 32blitDoom -  https://github.com/Daft-Freak/32BlitDoom
struct active_sound
{
	short rate;
	unsigned char *data;
	uint32_t length;
	uint32_t offset;
};





#ifndef NO_BGM

// CHANNEL_COUNT depends on target 32blit device is 8channels, everything else SDL based is configured to 16
#define SOUND_ALL_CHANNELS (CHANNEL_COUNT - 1)

#define SOUND_BGM_CHANNEL  (SOUND_ALL_CHANNELS-1) // last
#define SOUND_ALL_FX_CHANNELS (SOUND_BGM_CHANNEL -1)

#else // no BGM
// CHANNEL_COUNT depends on target 32blit device is 8channels, everything else is 16
#define SOUND_ALL_CHANNELS (CHANNEL_COUNT )

#define SOUND_BGM_CHANNEL  !ERROR-NO-BGM-USED!
#define SOUND_ALL_FX_CHANNELS (SOUND_ALL_CHANNELS)

#endif




//samples/HW 8000 11025 22050, no 44100 support;

//TODO AUDIO IS HARDCODED :/
#ifdef __EMSCRIPTEN__
/*


add -s TOTAL_MEMORY=67108864 to the LINKFLAGS

//Flags used by the linker during all build types.\\
CMAKE_EXE_LINKER_FLAGS:STRING= -s TOTAL_MEMORY=67108864


It should automatically update the linker settings: CMakeFiles/game.dir/link.txt \\
If not, add it to the line after em++
 */


#define AUDIO_SAMPLE_RATE_BGM 11025
#define AUDIO_SAMPLE_RATE_SFX 22050


#elif  __arm__

#define AUDIO_SAMPLE_RATE_BGM 8000
#define AUDIO_SAMPLE_RATE_SFX 11025


#else
// PC windows/linux
#define AUDIO_SAMPLE_RATE_BGM 22050 //22050
#define AUDIO_SAMPLE_RATE_SFX 22050 //22050

#endif






#ifdef __ANDROID__
// ouya use hi-def audio
#undef AUDIO_SAMPLE_RATE_BGM  
#undef AUDIO_SAMPLE_RATE_SFX  

#define AUDIO_SAMPLE_RATE_BGM 22050 //22050
#define AUDIO_SAMPLE_RATE_SFX 22050 //22050


#endif


#define MAX_BGM_TRACKS  2
static active_sound g_channel_sounds[SOUND_ALL_CHANNELS];
char g_last_channel;
char g_BGM_TRACK;
unsigned int g_ms_start;

#if 0
// wave audio demo
// Called everytime audio buffer ends
void buff_callback(AudioChannel &channel) {

	// Copy 64 bytes to the channel audio buffer
	for (int x = 0; x < 64; x++) {
		// If current sample position is greater than the sample length, fill the rest of the buffer with zeros.
		// Note: The sample used here has an offset, so we adjust by 0x7f.
		channel.wave_buffer[x] = (wav_pos < wav_size) ? (wav_sample[wav_pos] << 8) - 0x7f00 : 0;

		// As the engine is 22050Hz, we can timestretch to match by incrementing our sample every other step (every even 'x')
		if (wav_sample_rate == 11025) {
			if (x % 2) wav_pos++;
		} else {
			wav_pos++;
		}
	}

	// For this example, clear the values
	if (wav_pos >= wav_size) {
		channel.off();        // Stop playback of this channel.
		//Clear buffer
		wav_sample = nullptr;
		wav_size = 0;
		wav_pos = 0;
		wav_sample_rate = 0;
	}
}
#endif


extern "C" void amico_play_BGM_audio(int side);

void RefillBuffer(blit::AudioChannel &channel)
{



	auto sound = (active_sound *)(channel.user_data);

	LOG_SND("RefillBuffer start -sound->rate %d sound->offset %d  sound->length %d  \n",sound->rate, sound->offset, sound->length );

	if(sound->offset >= sound->length)
	{
#ifndef NO_BGM
		if((void *)sound == (void *)(&g_channel_sounds[SOUND_BGM_CHANNEL])) // BGM stopped!
		{
			//sound->offset =0; // restart it?

			if(g_BGM_TRACK == MAX_BGM_TRACKS)
				g_BGM_TRACK =0;
			else
				g_BGM_TRACK++;

			amico_play_BGM_audio(g_BGM_TRACK);
			return; // exit out, nothing to play here!
		}
		else
#endif
		{
			sound->offset = sound->length = 0;
			sound->data = NULL;
			channel.off();
		}
		// LOG_SND("RefillBuffer ended and off \n");
		return;
	}

	int i = 0;

	// 32blit default
	if(sound->rate == 22050) //22050 )
	{

		/*
		 *
		 *
 #speed up
  ffmpeg -i $f  -filter:a "atempo=1.5" -vn -y $f-1.wav
  # cp  $f  $f-1.wav

  #pitch up
  ffmpeg -i $f-1.wav -af asetrate=44100*1.1,aresample=44100 -filter:a "volume=0.75" -y  $f-2.wav
		 *
		 */

#ifdef __EMSCRIPTEN__ // it clips alot! I don't know why
		for(i = 0; i < 64 && sound->offset < sound->length; i++, sound->offset++)
			channel.wave_buffer[i] = (sound->data[sound->offset] - 127) * 128;
#else

		for(i = 0; i < 64 && sound->offset < sound->length; i++, sound->offset++)
			channel.wave_buffer[i] = (sound->data[sound->offset] - 127) * 256;
#endif



	}
	// next common here and easy to encode
	else if(sound->rate == 11025)
	{

		/*
		 *
		 *
	 #speed up
	  ffmpeg -i $f  -filter:a "atempo=1.5" -vn -y $f-1.wav
	  # cp  $f  $f-1.wav

	  #pitch up
	  ffmpeg -i $f-1.wav -af asetrate=44100*1.1,aresample=44100 -filter:a "volume=0.75" -y  $f-2.wav
		 *
		 */

#ifdef __EMSCRIPTEN__ // it clips alot! I don't know why
		for(i = 0; i < 64 && sound->offset < sound->length; i+=2,sound->offset++)
		{
			channel.wave_buffer[i + 1] = (sound->data[sound->offset]  - 127 ) * 128;
		}
#else

		for(i = 0; i < 64 && sound->offset < sound->length; i+=2,sound->offset++)
		{
			channel.wave_buffer[i] =   	channel.wave_buffer[i + 1] = (sound->data[sound->offset]  - 127 ) * 256;
		}

#endif
	}
	// really desperate for space and cycles, hacky, sounds bad but works fine!
	else if(sound->rate == 8000)
	{


		/*
		 *

	ffmpeg -i $f  -ac 1  -filter:a "volume=0.70"  -vn    -y  1.wav
	ffmpeg -i 1.wav -filter:a "atempo=1.50"  -vn    -y  2.wav
	ffmpeg -i  2.wav -af asetrate=44100*1.50,aresample=44100  -y  3.wav

	BGM created in audacity -


	sox works BUT encoding ads alot of hiss!
	using audacity batch PITA but better sounds
	convert audio to mono wav (MS) 44100 u16bit first (tracks - Mix - Mix stereo down to mono)
	load all wav files in audacity
	set project rate (bottom left screen) to 8k, 11k or 22k
	file -> export -> export multiple
	enter new folder ie: 8000 11025 or 22050
	export as wav (MS) u8bit PCM first - test
	reimport and export multiple
	select all
	change speed to 30-50% faster - I can't remember exactly... 40%??
	format: other uncompressed files
	header: RAW hearder-less
	endcoding: unsigned 8bit PCM
	copy into include folder and rebuild app
		 */



		// __EMSCRIPTEN__   // it clips alot! I don't know why


#ifdef __EMSCRIPTEN__ // it clips alot! I don't know why
		for(i = 0; i < 64 && sound->offset < sound->length; i += 2,sound->offset++)
		{
			channel.wave_buffer[i] =  	channel.wave_buffer[i+1] =  channel.wave_buffer[i+2] =		channel.wave_buffer[i+3] =   ( sound->data[sound->offset] - 127 ) * 128;
		}
#else
		for(i = 0; i < 64 && sound->offset < sound->length; i +=4, sound->offset++)
		{
			channel.wave_buffer[i] =  	channel.wave_buffer[i+1] =  channel.wave_buffer[i+2] =		channel.wave_buffer[i+3] =   ( sound->data[sound->offset] - 127 ) * 256;

		}
#endif





	}
#if 0 // not used really crappy!
	else if(sound->rate == 4000) //4k is 8k sped up ie extra extra compressed!
	{


		/*
		 *
		 * must be sped up tempo and pitched

ffmpeg -i $f  -ac 1  -filter:a "volume=0.85"  -vn    -y  1.wav
ffmpeg -i 1.wav -filter:a "atempo=2.0"  -vn    -y  2.wav
ffmpeg -i  2.wav -af asetrate=44100*2.75,aresample=44100  -y  3.wav
		 */




		for(i = 0; i < 64 && sound->offset < sound->length; i +=8, sound->offset++)
		{
			channel.wave_buffer[i] =  	channel.wave_buffer[i+1] =  channel.wave_buffer[i+2] =		channel.wave_buffer[i+3] =  
					channel.wave_buffer[i+4] =  	channel.wave_buffer[i+5] =  channel.wave_buffer[i+6] =		channel.wave_buffer[i+7] =   ( sound->data[sound->offset] - 127 ) * 256;

		}





	}

#endif// 4k audio, really crappy!


	LOG_SND("RefillBuffer finished -  found  %d sound->offset %d  sound->length %d  \n", i, sound->offset, sound->length );

	// pad end
	for(;i < 64; i++)
		channel.wave_buffer[i] = 0;



}



void sound_stop_all_SFX(void)
{

	for(int i = 0; i < SOUND_ALL_FX_CHANNELS; i++)
	{
		LOG_SND("amico_stop_all_SFX  blit::channels[%d] \n", i);
		blit::channels[i].off();
	}


}



static unsigned char play_SFX(int id, int channel, int vol)
{
	unsigned int lumplen;
	unsigned char *data;

	// need to load the sound

	LOG_SND("play_SFX id:%d chan:%d vol:%d \n", id , channel, vol);


	// lumpnum = sfxinfo->lumpnum;
	switch(id)
	{

	case 0:
		data = (unsigned char *) asset_sound_00; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_00_length; //W_LumpLength(lumpnum);
		break;

	case 1:
		data = (unsigned char *) asset_sound_01; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_01_length; //W_LumpLength(lumpnum);
		break;
	case 2:
		data = (unsigned char *) asset_sound_02; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_02_length; //W_LumpLength(lumpnum);
		break;
	case 3:
		data = (unsigned char *) asset_sound_03; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_03_length; //W_LumpLength(lumpnum);
		break;
	case 4:
		data = (unsigned char *) asset_sound_04; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_04_length; //W_LumpLength(lumpnum);
		break;
	case 5:
		data = (unsigned char *) asset_sound_05; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_05_length; //W_LumpLength(lumpnum);
		break;
	case 6:
		data = (unsigned char *) asset_sound_06; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_06_length; //W_LumpLength(lumpnum);
		break;
	case 7:
		data = (unsigned char *) asset_sound_07; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_07_length; //W_LumpLength(lumpnum);
		break;
	case 8:
		data = (unsigned char *) asset_sound_08; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_08_length; //W_LumpLength(lumpnum);
		break;
	case 9:
		data = (unsigned char *) asset_sound_09; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_09_length; //W_LumpLength(lumpnum);
		break;
	case 10:
		data = (unsigned char *) asset_sound_10; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_10_length; //W_LumpLength(lumpnum);
		break;

	case 11:
		data = (unsigned char *) asset_sound_11; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_11_length; //W_LumpLength(lumpnum);
		break;
	case 12:
		data = (unsigned char *) asset_sound_12; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_12_length; //W_LumpLength(lumpnum);
		break;
	case 13:
		data = (unsigned char *) asset_sound_13; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_13_length; //W_LumpLength(lumpnum);
		break;
	case 14:
		data = (unsigned char *) asset_sound_14; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_14_length; //W_LumpLength(lumpnum);
		break;
	case 15:
		data = (unsigned char *) asset_sound_15; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_15_length; //W_LumpLength(lumpnum);
		break;
	case 16:
		data = (unsigned char *) asset_sound_16; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_16_length; //W_LumpLength(lumpnum);
		break;
	case 17:
		data = (unsigned char *) asset_sound_17; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_17_length; //W_LumpLength(lumpnum);
		break;
	case 18:
		data = (unsigned char *) asset_sound_18; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_18_length; //W_LumpLength(lumpnum);
		break;
	case 19:
		data = (unsigned char *) asset_sound_19; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_19_length; //W_LumpLength(lumpnum);
		break;
	case 20:
		data = (unsigned char *) asset_sound_20; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_20_length; //W_LumpLength(lumpnum);
		break;
	case 21:
		data = (unsigned char *) asset_sound_21; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_21_length; //W_LumpLength(lumpnum);
		break;
	case 22:
		data = (unsigned char *) asset_sound_22; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_22_length; //W_LumpLength(lumpnum);
		break;
	case 23:
		data = (unsigned char *) asset_sound_23; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_23_length; //W_LumpLength(lumpnum);
		break;
	case 24:
		data = (unsigned char *) asset_sound_24; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_24_length; //W_LumpLength(lumpnum);
		break;
	case 25:
		data = (unsigned char *) asset_sound_25; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_25_length; //W_LumpLength(lumpnum);
		break;

	case 26:
		data = (unsigned char *) asset_sound_26; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_26_length; //W_LumpLength(lumpnum);
		break;

	case 27:
		data = (unsigned char *) asset_sound_27; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_27_length; //W_LumpLength(lumpnum);
		break;


	case 28:
		data = (unsigned char *) asset_sound_28; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_28_length; //W_LumpLength(lumpnum);
		break;

	case 29:
		data = (unsigned char *) asset_sound_29; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_29_length; //W_LumpLength(lumpnum);
		break;

	case 30:
		data = (unsigned char *) asset_sound_30; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_30_length; //W_LumpLength(lumpnum);
		break;

	case 31:
		data = (unsigned char *) asset_sound_31; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_31_length; //W_LumpLength(lumpnum);
		break;

	case 32:
		data = (unsigned char *) asset_sound_32; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_32_length; //W_LumpLength(lumpnum);
		break;

	case 33:
		data = (unsigned char *) asset_sound_33; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_33_length; //W_LumpLength(lumpnum);
		break;

	case 34:
		data = (unsigned char *) asset_sound_34; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_34_length; //W_LumpLength(lumpnum);
		break;

	case 35:
		data = (unsigned char *) asset_sound_35; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_35_length; //W_LumpLength(lumpnum);
		break;

	case 36:
		data = (unsigned char *) asset_sound_36; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_36_length; //W_LumpLength(lumpnum);
		break;

	case 37:
		data = (unsigned char *) asset_sound_37; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_37_length; //W_LumpLength(lumpnum);
		break;

	case 38:
		data = (unsigned char *) asset_sound_38; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_38_length; //W_LumpLength(lumpnum);
		break;

	case 39:
		data = (unsigned char *) asset_sound_39; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_39_length; //W_LumpLength(lumpnum);
		break;

	case 40:
		data = (unsigned char *) asset_sound_40; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_40_length; //W_LumpLength(lumpnum);
		break;

	case 41:
		data = (unsigned char *) asset_sound_41; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_41_length; //W_LumpLength(lumpnum);
		break;

	case 42:
		data = (unsigned char *) asset_sound_42; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_42_length; //W_LumpLength(lumpnum);
		break;

	case 43:
		data = (unsigned char *) asset_sound_43; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_43_length; //W_LumpLength(lumpnum);
		break;

	case 44:
		data = (unsigned char *) asset_sound_44; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_44_length; //W_LumpLength(lumpnum);
		break;

	case 45:
		data = (unsigned char *) asset_sound_45; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_45_length; //W_LumpLength(lumpnum);
		break;

	case 46:
		data = (unsigned char *) asset_sound_46; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_46_length; //W_LumpLength(lumpnum);
		break;

	case 47:
		data = (unsigned char *) asset_sound_47; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_47_length; //W_LumpLength(lumpnum);
		break;

	case 48:
		data = (unsigned char *) asset_sound_48; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_48_length; //W_LumpLength(lumpnum);
		break;

	case 49:
		data = (unsigned char *) asset_sound_49; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_49_length; //W_LumpLength(lumpnum);
		break;

	case 50:
		data = (unsigned char *) asset_sound_50; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_sound_50_length; //W_LumpLength(lumpnum);
		break;



	case 51:
		data = (unsigned char *) asset_sound_51 ;
		lumplen =  asset_sound_51_length;
		break;


	case 52:
		data = (unsigned char *) asset_sound_52 ;
		lumplen =  asset_sound_52_length;
		break;

	case 53:
		data = (unsigned char *) asset_sound_53 ;
		lumplen =  asset_sound_53_length;
		break;

	case 54:
		data = (unsigned char *) asset_sound_54 ;
		lumplen =  asset_sound_54_length;
		break;

	case 55:
		data = (unsigned char *) asset_sound_55 ;
		lumplen =  asset_sound_55_length;
		break;

	case 56:
		data = (unsigned char *) asset_sound_56 ;
		lumplen =  asset_sound_56_length;
		break;

	case 57:
		data = (unsigned char *) asset_sound_57 ;
		lumplen =  asset_sound_57_length;
		break;

	case 58:
		data = (unsigned char *) asset_sound_58 ;
		lumplen =  asset_sound_58_length;
		break;

	case 59:
		data = (unsigned char *) asset_sound_59 ;
		lumplen =  asset_sound_59_length;
		break;

	case 60:
		data = (unsigned char *) asset_sound_60 ;
		lumplen =  asset_sound_60_length;
		break;

	case 61:
		data = (unsigned char *) asset_sound_61 ;
		lumplen =  asset_sound_61_length;
		break;

	case 62:
		data = (unsigned char *) asset_sound_62 ;
		lumplen =  asset_sound_62_length;
		break;

	case 63:
		data = (unsigned char *) asset_sound_63 ;
		lumplen =  asset_sound_63_length;
		break;

	case 64:
		data = (unsigned char *) asset_sound_64 ;
		lumplen =  asset_sound_64_length;
		break;

	case 65:
		data = (unsigned char *) asset_sound_65 ;
		lumplen =  asset_sound_65_length;
		break;

	case 66:
		data = (unsigned char *) asset_sound_66 ;
		lumplen =  asset_sound_66_length;
		break;

	case 67:
		data = (unsigned char *) asset_sound_67 ;
		lumplen =  asset_sound_67_length;
		break;

	case 68:
		data = (unsigned char *) asset_sound_68 ;
		lumplen =  asset_sound_68_length;
		break;

	case 69:
		data = (unsigned char *) asset_sound_69 ;
		lumplen =  asset_sound_69_length;
		break;

	case 70:
		data = (unsigned char *) asset_sound_70 ;
		lumplen =  asset_sound_70_length;
		break;

	case 71:
		data = (unsigned char *) asset_sound_71 ;
		lumplen =  asset_sound_71_length;
		break;

	case 72:
		data = (unsigned char *) asset_sound_72 ;
		lumplen =  asset_sound_72_length;
		break;

	case 73:
		data = (unsigned char *) asset_sound_73 ;
		lumplen =  asset_sound_73_length;
		break;




	}


#if 0
	// Check the header, and ensure this is a valid sound
	/*
    if (lumplen < 8
     || data[0] != 0x03 || data[1] != 0x00)
    {
        // Invalid sound

        return false;
    }
	 */
	// 16 bit sample rate field, 32 bit length field

	samplerate = (data[3] << 8) | data[2];
	length = (data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4];

	// If the header specifies that the length of the sound is greater than
	// the length of the lump itself, this is an invalid sound lump

	// We also discard sound lumps that are less than 49 samples long,
	// as this is how DMX behaves - although the actual cut-off length
	// seems to vary slightly depending on the sample rate.  This needs
	// further investigation to better understand the correct
	// behavior.

	if (length > lumplen - 8 || length <= 48)
	{
		// return false;
	}

	// The DMX sound library seems to skip the first 16 and last 16
	// unsigned chars of the lump - reason unknown.

	data += 16;
	length -= 32;

	if(samplerate != 11025 && samplerate != 22050)
	{
		printf("unhandled rate %i\n", samplerate);
		return false;
	}
#endif

	//originally
	//16
	//32
	data += SOUND_ADD_DATA_POINTER; // 512;
	lumplen -=  SOUND_MINUS_LEN; // 512;


	LOG_SND("play_SFX length %d \n",  lumplen);


	g_channel_sounds[channel].rate = AUDIO_SAMPLE_RATE_SFX;//11025; //8000; // 22050 ;
	g_channel_sounds[channel].data = data;
	g_channel_sounds[channel].length = lumplen;
	g_channel_sounds[channel].offset = 0;


#ifdef __EMSCRIPTEN__
	blit::channels[channel].volume = vol; //0xffff; //vol * 111;
#else
	blit::channels[channel].volume = vol; //0xffff; //vol * 111;
#endif


	blit::channels[channel].adsr = 0xFFFF00;
	blit::channels[channel].trigger_sustain();

	//re init?
	blit::channels[channel].waveforms = blit::Waveform::WAVE;
	blit::channels[channel].user_data = (void *)(&g_channel_sounds[channel]);
	blit::channels[channel].wave_buffer_callback =  &RefillBuffer;

	// don't need the original lump any more

	//  W_ReleaseLumpNum(lumpnum);


	LOG_SND("play_SFX finished %d %d \n", id , channel);
	return true;
}



static unsigned char Init32blit_audio(void)
{
	LOG_SND("Init32blit_audio %d \n", 0x0);

LOG_SND("Init32blit_22222audio %d \n", 0x0);
LOG_SND("Init32blit_22222audio %d \n", 0x01);
LOG_SND("Init32blit_22222audio %d \n", 0x03);
LOG_SND("Init32blit_22222audio %d \n", 0xFF);
LOG_SND("Init32blit_audio %l \n", 0x0);

	for(unsigned int i = 0x0; i < SOUND_ALL_CHANNELS; i++)
	{
		LOG_SND("Init32blit_audio blit::channels[%d] \n", i);
		blit::channels[i].off();
		blit::channels[i].waveforms = blit::Waveform::WAVE;
		blit::channels[i].user_data = (void *)(&g_channel_sounds[i]);
		blit::channels[i].wave_buffer_callback = RefillBuffer;
	}



	LOG_SND("Init32blit_audio finished \n\n");
	return true;
}


// audio implementation based from 32blitDoom -  https://github.com/Daft-Freak/32BlitDoom




#if 0 //OG 32blit doom
static int I_Blit_StartSound(void *sfxinfo, int channel, int vol, int sep)
{
	if(channel >= SOUND_ALL_CHANNELS)
		return -1;

	//  blit::channels[channel].off();


	if(!play_SFX(0, channel))
		return -1;

	blit::channels[channel].adsr = 0xFFFF00;
	blit::channels[channel].trigger_sustain();

	blit::channels[channel].volume = vol * 111;
	// I_Blit_UpdateSoundParams(channel, vol, sep);

	return channel;
}

static void I_Blit_StopSound(int handle)
{
	if (handle >= SOUND_ALL_CHANNELS)
		return;

	blit::channels[handle].off();
}

static unsigned char I_Blit_SoundIsPlaying(int handle)
{
	if(handle > SOUND_CHANNELS)
		return false;

	return blit::channels[handle].adsr_phase != blit::ADSRPhase::OFF;
}

#endif




Surface* TPAGE01 = NULL;
Surface* TPAGE02 = NULL;
Surface* TPAGE03 = NULL;
Surface* TPAGE04 = NULL;
Surface* TPAGE05 = NULL;



extern "C" {
#include "amico.h"



#if 0 // turned to macro -> #define  LOG_PAD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#ifdef __ANDROID__

	#include <stdarg.h>

	int android_debugf( const char *format, ...)
	{
		int result;
		va_list args;

		va_start(args, format);
		 __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, format, args );
		va_end(args);

__android_log_print(ANDROID_LOG_DEBUG,    LOG_TAG, "\nThe value of 0 is %d", 0);
		return result;
	}

#endif //#ifdef __ANDROID__

#endif


#if 0
/*
 *
 *
 *

extern "C" 	int android_debugf( const char *format, ...);


#define LOG_DATA   android_debugf
#define LOG_EXIT    android_debugf
#define LOG_SND     android_debugf
#define LOG_DEL    android_debugf
#define LOG_PAD    android_debugf

 *
 *
 *
 *
 *
 *
 *
 *



// REMOVE MOUSE HANDLING
//around line 55 in 32blit-sdl/main.cpp
		case SDL_MOUSEBUTTONDOWN:
//			blit_input->handle_mouse(event.button.button, event.type == SDL_MOUSEBUTTONDOWN, event.button.x, event.button.y);
			break;

		case SDL_MOUSEMOTION:
			if (event.motion.state & SDL_BUTTON_LMASK) {
//				blit_input->handle_mouse(SDL_BUTTON_LEFT, event.motion.state & SDL_MOUSEBUTTONDOWN, event.motion.x, event.motion.y);
			}
			break;



// line 69 in the if statement	if (!blit_input->handle_keyboard(event.key.keysym.sym, event.type == SDL_KEYDOWN)){
 // fullscreen
				 if (event.key.keysym.sym == SDLK_b && event.type == SDL_KEYDOWN)
				 {
					SDL_ShowCursor(is_fullscreen);
					is_fullscreen = !is_fullscreen;
					SDL_SetWindowFullscreen(window, is_fullscreen );
					return;
				}
// fullscreen


// put around line 28
 unsigned int is_fullscreen = 0; //


 /home/dev/32blit-sdk/32blit-sdl/Input.cpp

  remapped
//
	{SDLK_j,       blit::Button::Y}, // left
	{SDLK_l,       blit::Button::A}, // right

	{SDLK_i,       blit::Button::X}, // up
	{SDLK_k,       blit::Button::B}, // down
//


changed WASD to:
	{SDLK_e,       blit::Button::DPAD_UP},
	{SDLK_s,       blit::Button::DPAD_LEFT},
	{SDLK_d,       blit::Button::DPAD_DOWN},
	{SDLK_f,       blit::Button::DPAD_RIGHT},


	// removed 1 and 2 buttons
	//  {SDLK_1,       blit::Button::HOME},
	//  {SDLK_2,       blit::Button::MENU},
	{SDLK_SPACE,       blit::Button::HOME}, // - made space as pause/back
	{SDLK_3,       blit::Button::JOYSTICK},

  {SDLK_ESCAPE,  blit::Button::MENU},






// my action buttons, around line 66


	// action buttons
#if 0 // ORIG
	{SDL_CONTROLLER_BUTTON_A,           blit::Button::A},
	{SDL_CONTROLLER_BUTTON_B,           blit::Button::B},
	{SDL_CONTROLLER_BUTTON_X,           blit::Button::X},
	{SDL_CONTROLLER_BUTTON_Y,           blit::Button::Y},

#else //  mapped using https://generalarcade.com/gamepadtool/

	{SDL_CONTROLLER_BUTTON_X,           blit::Button::Y}, // left
	{SDL_CONTROLLER_BUTTON_B,           blit::Button::A}, //  right



	{SDL_CONTROLLER_BUTTON_Y,           blit::Button::X}, // up
	{SDL_CONTROLLER_BUTTON_A,           blit::Button::B}, // down
#endif

 *

// Adding more channels for PC's
FILE: 32blit-sdk/32blit/audio/audio.hpp

 // default  #define CHANNEL_COUNT 8


#ifdef __EMSCRIPTEN__
#define CHANNEL_COUNT 8


#elif  __arm__
#define CHANNEL_COUNT 8


#else
 // PC windows/linux
#define CHANNEL_COUNT 16

#endif



OPTIONAL remove 32BLIT timeout!
~/32blit-sdk/32blit-stm32/Src/power.cpp
Replaced these functions with:

 void update() {
      return;
  }

  void update_active() {
	  return;
  }

cd  ~/32blit-sdk/build.stm32
run:
make firmware-update
make firmware-update.flash

I had random linker issues... remove " quotes from link file: /home/dev/32blit-sdk/build.stm32/firmware-update/CMakeFiles/firmware-update.dir/link.txt




 */
#endif





void SoundInit(void)
{
	LOG_SND("SoundInit  \n");

	Init32blit_audio();
	g_last_channel =0x0;

	LOG_SND("SoundInit fin  \n");

}



void amico_stop_all_SFX(void)
{
	sound_stop_all_SFX();
}




void amico_BGM_quiet_time(int quiet_time) // 1 true reduce vol - 0 false increase back to normal BG volume
{

#ifndef NO_BGM


	if(g_SET_BGM_VOL)
	{
		if(quiet_time)
		{
			blit::channels[SOUND_BGM_CHANNEL].volume = g_SET_BGM_VOL >>2; //vol * 111;
		}
		else
		{
			blit::channels[SOUND_BGM_CHANNEL].volume = g_SET_BGM_VOL; //vol * 111;
		}
	}

#endif

}



void amico_play_BGM_audio(int side)
{
	unsigned int lumplen;
	unsigned char *data;

#ifndef NO_BGM

	// return;

	// need to load the sound

	LOG_SND("amico_play_BG_audio %d \n", side);



	if(g_SET_BGM_VOL < 10)
		return;

	g_BGM_TRACK = side;

	if(side == SIDE_SHILL)
	{
		data = (unsigned char *) asset_bgm_shills; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_bgm_shills_length; //W_LumpLength(lumpnum);
	}
	else if(side == SIDE_HATER)
	{
		data = (unsigned char *) asset_bgm_haters; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_bgm_haters_length; //W_LumpLength(lumpnum);
	}

#ifndef UNIT_32BLIT

	else // play intro
	{
		data = (unsigned char *) asset_bgm_intro; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_bgm_intro_length; //W_LumpLength(lumpnum);
		g_BGM_TRACK = MAX_BGM_TRACKS;
	}
#else
		/*
		 * intro too big for 32blit play shill instead
		 */
	else // play shill not intro
	{
		data = (unsigned char *) asset_bgm_shills; //(unsigned char *)W_CacheLumpNum(lumpnum, PU_STATIC);
		lumplen =  asset_bgm_shills_length; //W_LumpLength(lumpnum);

		g_BGM_TRACK = SIDE_SHILL;

	}
#endif




	LOG_SND("amico_play_BG_audio length %d \n",  lumplen);



	g_channel_sounds[SOUND_BGM_CHANNEL].rate = AUDIO_SAMPLE_RATE_BGM;
	g_channel_sounds[SOUND_BGM_CHANNEL].data = data;
	g_channel_sounds[SOUND_BGM_CHANNEL].length = lumplen;
	g_channel_sounds[SOUND_BGM_CHANNEL].offset = 0;

#ifdef __EMSCRIPTEN__
	blit::channels[SOUND_BGM_CHANNEL].volume = g_SET_BGM_VOL; // 0x5fff; //vol * 111;
#else
	blit::channels[SOUND_BGM_CHANNEL].volume = g_SET_BGM_VOL; //0xffff; //vol * 111;
#endif

	blit::channels[SOUND_BGM_CHANNEL].adsr = 0xFFFF00;
	blit::channels[SOUND_BGM_CHANNEL].trigger_sustain();

	//re init?
	blit::channels[SOUND_BGM_CHANNEL].waveforms = blit::Waveform::WAVE;
	blit::channels[SOUND_BGM_CHANNEL].user_data = (void *)(&g_channel_sounds[SOUND_BGM_CHANNEL]);
	blit::channels[SOUND_BGM_CHANNEL].wave_buffer_callback =  &RefillBuffer;

	// don't need the original lump any more

	//  W_ReleaseLumpNum(lumpnum);


	LOG_SND("amico_play_BG_audio finished %d channel  %d \n", side, SOUND_BGM_CHANNEL);
#endif // NO_BGM

	return;



}




void amico_clear_SFX(void)
{
	LOG_SND("amico_clear_SFX  \n");


	for(int i=0; i< SOUND_ALL_CHANNELS; i++)
		blit::channels[i].off();
}


u32 amico_stop_SFX(u32 id, u32 voice)
{
	LOG_SND("amico_play_SFX %d \n", id);

	g_last_channel =0x0;


}

u32 amico_play_SFX(u32 id)  //, u8 vol) //returns voice number for that prog
{



	g_stereo_counter_random++;
	LOG_SND("amico_play_SFX  %d %d \n", id , g_SET_SFX_VOL);
#if 0 // sound

	for(int i=0; i< SOUND_ALL_FX_CHANNELS; i++)
	{
		LOG_SND("setup_start_Sound  %d blit::channels[i].adsr_phase %d \n", i, blit::channels[i].adsr_phase);

		if(blit::channels[i].adsr_phase == ADSRPhase::OFF)
		{
			g_last_channel = i;
			play_SFX(id, i, vol);
			LOG_SND("setup_start_Sound  done returning %d blit::channels[i].adsr_phase %d \n", i, blit::channels[i].adsr_phase);


			// blit::channels[i].volume = vol * 111; //0xffff; //vol * 111;
			return 0;

		}
	}



#if 0
	// use last -1 channel
	g_last_channel--;

	if( g_last_channel<0 )
		g_last_channel = SOUND_CHANNELS;


	play_SFX(id, g_last_channel);
#endif


#else



	LOG_SND("setup_start_Sound  %d blit::channels[i].adsr_phase %d \n", g_last_channel, blit::channels[g_last_channel].adsr_phase);


	// hack to stop audio popping in zero level
	if(g_function_loop == update_level_zero)
		return 0;

	//if(blit::channels[g_last_channel].adsr_phase == ADSRPhase::OFF)
	{

	LOG_SND("setup_start_Sound  	play_SFX(id, g_last_channel, g_SET_SFX_VOL);  returning %d blit::channels[i].adsr_phase %d \n", g_last_channel, blit::channels[g_last_channel].adsr_phase);
		play_SFX(id, g_last_channel, g_SET_SFX_VOL);
		LOG_SND("setup_start_Sound  done returning %d blit::channels[i].adsr_phase %d \n", g_last_channel, blit::channels[g_last_channel].adsr_phase);

		// blit::channels[i].volume = vol * 111; //0xffff; //vol * 111;


	}


	g_last_channel++;

	if(g_last_channel >=  SOUND_ALL_FX_CHANNELS)
		g_last_channel =0;


#endif


	LOG_SND("amico_play_SFX fin  %d %d \n", id , g_SET_SFX_VOL);

	return 0;

}

/* Sound playback termination */

void SoundClose(void)
{



	return;

}



void amico_text_init(void)
{

	//does nothing
}



void amico_text_top1_line( char *name )
{

	screen.pen = Pen(255, 255, 255);
	screen.text(name, minimal_font,  Point(4, 4 ) ,  false, TextAlign::left);

}


void amico_text_top2_line( char *name )
{

	screen.pen = Pen(255, 255, 255);
	screen.text(name, minimal_font,  Point(4, 4+16 ) ,  false, TextAlign::left);

}




void amico_text_right_screen( char *name )
{

	screen.pen = Pen(255, 255, 255);
	screen.text(name, minimal_font,  Rect(140, 32, 180,240 ) ,  false, TextAlign::left);


}



void amico_text_continue(void)
{
	screen.alpha = 255;
	screen.pen = Pen(0, 255, 0);
	screen.text("-- PAUSED --", minimal_font,  Point(320/2, 124 ) ,  false, TextAlign::center_center);
	screen.text("PRESS A TO CONTINUE OR ESC TO EXIT", minimal_font,  Point(320/2, 134 ) ,  false, TextAlign::center_center);
}




void amico_text_pressA(void)
{
	screen.alpha = 255;
	screen.pen = Pen(0, 255, 0);
	screen.text("PRESS A ", minimal_font,  Point(150-28, 132 ) ,  false, TextAlign::left);
}





void amico_intro_splash(void )
{
	screen.alpha = 255;
	screen.pen = Pen(0, 255, 0);
	screen.text("splash ", minimal_font,  Point(150-28, 132 ) ,  false, TextAlign::left);
}

void amico_rectangle(u8 r, u8 g, u8 b, u32 screen_posX, u32 screen_posY, u32 w, u32 h )
{
	screen.alpha = 255;
	screen.pen = Pen(r, g, b);
	screen.rectangle( Rect(screen_posX, screen_posY, w, h)  );
}



u8 g_r;
u8 g_g;
u8 g_b;



void amico_sprite(u8 TPAGE, u32 texture_u, u32 texture_v, u32 texture_w, u32 texture_h, s32 posX, s32 posY, s32 scale , u8 h_flip)
{
	float fscale;


	switch(TPAGE)
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
	case 5:
		screen.sprites = TPAGE05;
		break;

	}

	//screen.alpha = alpha; not used

	if(scale)
		fscale = scale/100.f;

	// //screen.sprite(Rect(0, 0, 32/8, 64/8), Point(64,  -100) ,  Point(0, 0), 6.f);
	if(h_flip)
		h_flip = SpriteTransform::HORIZONTAL;
	else
		h_flip = SpriteTransform::NONE;

	//type = 1;
#if 0 // old
	if(side)
	{

		if(side==1) // SHILL
		{
			if(g_game_counter&1)
			{
				screen.sprites->palette[1].r = (u8) 71;
				screen.sprites->palette[1].g = (u8) 213;
				screen.sprites->palette[1].b = (u8) 211;
			}
			else
			{
				screen.sprites->palette[1].r = (u8) 0;
				screen.sprites->palette[1].g = (u8) 93;
				screen.sprites->palette[1].b = (u8) 91;

			}
		}
		else if(side==2) // haters
		{
			if(g_game_counter&1)
			{
				screen.sprites->palette[1].r = (u8) 198;
				screen.sprites->palette[1].g = (u8) 165;
				screen.sprites->palette[1].b = (u8) 107;
			}
			else
			{
				screen.sprites->palette[1].r = (u8) 148;
				screen.sprites->palette[1].g = (u8) 115;
				screen.sprites->palette[1].b = (u8) 067;
			}
		}
		else // 3 player
		{
			screen.sprites->palette[1].r = (u8) 0;
			screen.sprites->palette[1].g = (u8) 0;
			screen.sprites->palette[1].b = (u8) 0;
		}

		screen.sprite( Rect(texture_u/8, texture_v/8, texture_w/8, texture_h/8), Point(posX, posY) ,  Point(texture_w/2, texture_h/2), fscale, h_flip);

		screen.sprites->palette[1].r = (u8) g_r;
		screen.sprites->palette[1].g = (u8) g_g;
		screen.sprites->palette[1].b = (u8) g_b;

	}
	else
#endif
		screen.sprite( Rect(texture_u/8, texture_v/8, texture_w/8, texture_h/8), Point(posX, posY) ,  Point(texture_w/2, texture_h/2), fscale, h_flip);

	// posX += texture_w/2;
	// posY += texture_h/2;



}


} // extern "C" --- the rest is 32blit C++ !!!




typedef struct {
	t_game_state state;
	t_player player;
	u32 total_bullets_used;
	u32 total_bullets_hit;
	u32 game_CUR_BONUS;
	s32 unlocked_bosses_level;
	u32 SET_SFX_VOL; //max
	u32 SET_BGM_VOL; //max
} t_save_data_old;



typedef struct {
	char check_start[32];
	t_game_state state;
	t_player player;
	u32 total_bullets_used;
	u32 total_bullets_hit;
	u32 game_CUR_BONUS;
	s8 unlocked_bosses_level;
	u16 SET_SFX_VOL; //max
	u16 SET_BGM_VOL; //max
	u32 total_friends_saved;
	u32 total_friends;
	u8 AI_shoot_dist;
	u8 g_no_boss_flashing;
	u32 data3;
	u32 data4;
	u32 data5;
	u32 data6;
	u32 data7;
	u32 data8;
	char check_end[32];
} t_save_data;



t_save_data g_saved_data = {0};
// save to:
// linux:   ~/.local/share/

int amico_save_data(void)
{
	LOG_DATA(" amico_save_data(), sizeof(t_save_data) %d \n",  sizeof(t_save_data));


MACRO_NO_SAVE_LOADING
#ifdef BETA_DEMO
//	return 0; // start game demo instead of loop
#endif

	if(  g_gamestate.level==0 && g_gamestate.wave < 2)
	{
		LOG_DATA("amico_save_data   amico_save_data no game played \n");
		return 0; // no saving required
	}

	if( g_saved_data.state.wave == g_gamestate.wave &&
			g_saved_data.state.level == g_gamestate.level  )
	{
		LOG_DATA("amico_save_data   amico_save_data no change from last save \n");
		return 0; // no saving required
	}



	sprintf(g_saved_data.check_start, "%s", SAVE_CHECK_STRING_START);


	g_saved_data.state = g_gamestate;
	g_saved_data.player = g_player;
	g_saved_data.total_bullets_used = g_total_bullets_used;
	g_saved_data.total_bullets_hit = g_total_bullets_hit;
	g_saved_data.game_CUR_BONUS = g_game_CUR_BONUS;
	g_saved_data.unlocked_bosses_level =   g_unlocked_bosses_level;
	g_saved_data.SET_SFX_VOL =  g_SET_SFX_VOL;
	g_saved_data.SET_BGM_VOL =  g_SET_BGM_VOL;
	g_saved_data.AI_shoot_dist = g_AI_shoot_dist;
	g_saved_data.g_no_boss_flashing = g_no_boss_flashing;
	g_saved_data.total_friends_saved = g_total_friends_saved;
	g_saved_data.total_friends = g_total_friends;

	sprintf(g_saved_data.check_end, "%s", SAVE_CHECK_STRING_END);


	// Save all those points we gave away
	write_save(g_saved_data); // returns void :/

	LOG_DATA("amico_save_data  completed write_save(data); finished amico_save_data() \n");
	return 1;

}

int amico_load_data(void)
{
	int loaded_save_file = 0;
	t_save_data_old  saved_data_old;


	LOG_DATA("int amico_load_data(void)  sizeof(t_save_data) %d   sizeof(t_save_data_old) %d \n",  sizeof(t_save_data) , sizeof(t_save_data_old));

	MACRO_NO_SAVE_LOADING
#ifdef _DEBUG_ // BETA_DEMO
//	return 0; // start game demo instead of loop
#endif




	if(g_saved_data.state.enemy_next > 0)
		{
			LOG_DATA(" amico_load_data() returning , data already loaded... \n\n");
			return 0;
		}

	// try to read new bigger new format first, it will fail if it's the old smaller format
	if(read_save(g_saved_data))
	{
		// Loaded successfully!
		if(strcmp(SAVE_CHECK_STRING_END, g_saved_data.check_end ))
			loaded_save_file = 0;
		else if(strcmp(SAVE_CHECK_STRING_START, g_saved_data.check_start ))
			loaded_save_file = 0;
		else
			loaded_save_file = 1;

		LOG_DATA(" amico_load_data:  check loaded_save_file %d \n",loaded_save_file);


	}
#if 0
	else if(read_save(saved_data_old))// Attempt to load old beta format the first save slot.
	{
		// Loaded successfully!
		LOG_DATA(" amico_load_data:  read_save OLD DATA  OK SET_BGM_VOL %d \n",g_saved_data.SET_BGM_VOL);


		//		srand( (g_saved_data.total_bullets_used  + g_saved_data.total_bullets_hit) * rand() & 0xF);
		//		srand( (g_saved_data.state.level + g_saved_data.state.wave) *  g_saved_data.state.time );



		g_saved_data.state = saved_data_old.state;
		g_saved_data.player  = saved_data_old.player;
		g_saved_data.total_bullets_used = saved_data_old.total_bullets_used;
		g_saved_data.total_bullets_hit = saved_data_old.total_bullets_hit;
		g_saved_data.game_CUR_BONUS = saved_data_old.game_CUR_BONUS;
		g_saved_data.unlocked_bosses_level = saved_data_old.unlocked_bosses_level;
		g_saved_data.SET_SFX_VOL = saved_data_old.SET_SFX_VOL;
		g_saved_data.SET_BGM_VOL = saved_data_old.SET_BGM_VOL;


		g_saved_data.AI_shoot_dist = g_AI_shoot_dist;



		loaded_save_file = 1;

		LOG_DATA(" amico_load_data: g_saved_data.version = 0 loaded \n");


	}
#endif


	if(loaded_save_file) // restore saved data
	{





		// already done!
		//g_gamestate.enemy_next = 0xAA;
		// update_splash(); // run once - decode text


		if(g_player.textU ==  g_saved_data.player.textU &&
				g_player.textV ==  g_saved_data.player.textV &&
				g_player.TPAGE ==  g_saved_data.player.TPAGE
				)
		{
			// already loaded
		}
		else
			 amico_play_BGM_audio(g_saved_data.state.p_side);


		g_gamestate = g_saved_data.state;
		g_player = g_saved_data.player;
		g_total_bullets_used = g_saved_data.total_bullets_used;
		g_total_bullets_hit =	 g_saved_data.total_bullets_hit;
		g_game_CUR_BONUS = g_saved_data.game_CUR_BONUS;
		g_unlocked_bosses_level =   g_saved_data.unlocked_bosses_level;
	//	g_SET_SFX_VOL	=  g_saved_data.SET_SFX_VOL;
	//	g_SET_BGM_VOL =    g_saved_data.SET_BGM_VOL;
		g_total_friends_saved = g_saved_data.total_friends_saved;
		g_total_friends =			g_saved_data.total_friends;
		g_AI_shoot_dist = g_saved_data.AI_shoot_dist;
		g_no_boss_flashing = g_saved_data.g_no_boss_flashing;


		g_gamestate.enemy_alive =  g_gamestate.friend_alive = 0;


		g_player.dpad =	g_player.shoot_dpad =0;
		g_player.shoot_timer=BUTTON_PRESS_TIME*2;
		g_player.dir = 1;
		g_player.posX = MAP_START_PLAYER_POSX;
		g_player.posY = MAP_START_PLAYER_POSY;
		g_game_counter =0;


		g_player.dpad = g_player.shoot_dpad =0;
		g_player.shoot_timer=BUTTON_PRESS_TIME*2;
		g_function_loop = update_new_game_wave;
		// moved amico_BGM_quiet_time(1); // wave intro
		// moved to
		MACRO_CLEAR_SCREEN



		LOG_DATA(" amico_load_data:  read_save finished OK return 1\n");

		return 1;

	} else {
		// No save file or it failed to load, set up some defaults.
		LOG_DATA(" amico_load_data: no save fount, ret 0\n");

		// continue as normal
		return 0;

	}

}


#if 0
void on_exit() {
	LOG_EXIT(" on_exit() \n");

	if(g_total_bullets_used)
	{



		amico_save_data();

		SAVE_RETRY:
		LOG_EXIT(" on_exit() going to amico_save_data \n");


		LOG_EXIT(" on_exit() amico_save_data finished going to reload it \n");
		if(amico_load_data() == 1)
		{
			LOG_EXIT(" on_exit()  doign exit\n");
			exit(0);
		}
		else
		{
			LOG_EXIT(" NO exit- load back failed\n");
			game_reset();
			goto SAVE_RETRY;
		}
	}



}
#else

void on_exit()
{

	amico_deinit();
	exit(0);

}
#endif

u32 random_32blit(void)
{

	// 32blit seeded random function
	return blit::random();
}



#ifndef UNIT_32BLIT // SDL2 stuff only



#include "gamecontrollerdb.hpp" // serialized gamecontrollerdb.txt string and size
/*
 assets.yml
 gamecontrollerdb.hpp:
 gamecontrollerdb.txt:
    name: gamecontrollerdb
 */

#include "load_gamecontrollerdb.hpp"
#if 0
extern "C" int  load_gamecontrollerdb(const char *db_str, const uint32_t db_size) ;
 // extern function from Input.cpp, used in Init function to make controllers work
// ANDROID for whatever reason, doesn't link to this function in Input.cpp, put it in the gamecontrollerdb.hpp or cpp
// call example:
// load_gamecontrollerdb((const char *) gamecontrollerdb, gamecontrollerdb_length );


//
//defines private from: https://github.com/libsdl-org/SDL/blob/396411c09093660fead7999827e9f0db5ea2bc0e/src/joystick/SDL_gamecontroller.c#L47
#define SDL_CONTROLLER_PLATFORM_FIELD       "platform:"
#define SDL_CONTROLLER_PLATFORM_FIELD_SIZE  strlen(SDL_CONTROLLER_PLATFORM_FIELD)
#define SDL_CONTROLLER_HINT_FIELD           "hint:"
#define SDL_CONTROLLER_HINT_FIELD_SIZE      strlen(SDL_CONTROLLER_HINT_FIELD)

// loads embedded gamecontrollerdb.txt, then trys to load  gamecontrollerdb.txt in the current directory, then trys to opens connected controllers
// returns number of opened controllers

int  load_gamecontrollerdb(const char *db_str, const uint32_t db_size)
{

	 const char *platform = SDL_GetPlatform();
    int controllers = 0;
    char *buf, *line, *line_end, *tmp, *comma, line_platform[64];
    size_t platform_len;


    buf = (char *)SDL_calloc(1, db_size + 1);
    if (buf == NULL) {
             return SDL_SetError("Could not allocate space to read DB into memory");
    }


    memcpy(buf, db_str, db_size );

    line = buf;

    while (line < buf + db_size) {
        line_end = SDL_strchr(line, '\n');
        if (line_end != NULL) {
            *line_end = '\0';
        } else {
            line_end = buf + db_size;
        }

        /* Extract and verify the platform */
        tmp = SDL_strstr(line, SDL_CONTROLLER_PLATFORM_FIELD);
        if (tmp != NULL) {
            tmp += SDL_CONTROLLER_PLATFORM_FIELD_SIZE;
            comma = SDL_strchr(tmp, ',');
            if (comma != NULL) {
                platform_len = comma - tmp + 1;
                if (platform_len + 1 < SDL_arraysize(line_platform)) {
                    SDL_strlcpy(line_platform, tmp, platform_len);
                    if (SDL_strncasecmp(line_platform, platform, platform_len) == 0 &&
                        SDL_GameControllerAddMapping(line) > 0) {
                        controllers++;
                    }
                }
            }
        }

        line = line_end + 1;
    }

    SDL_free(buf);



	// check for actual gamecontrollerdb.txt
   SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
   controllers =0;

 	// Open all joysticks as game controllers
	for(int n=0; n<SDL_NumJoysticks(); n++) {
		if(SDL_GameControllerOpen(n))
			controllers++;		// open correctly
	}


    return controllers;
} //

#endif //#ifndef UNIT_32BLIT // SDL2 stuff only


#endif


void init() {

	LOG_SND(" void init(void)  \n");

#ifndef UNIT_32BLIT // SDL2 stuff only



	//only load gamecontroller db for new android - not OUYA
#ifdef __ANDROID__
#ifdef NEW_ANDROID //new android - not ouya -SDL2 swaps these on pads tested??
	load_gamecontrollerdb( (const char *) gamecontrollerdb, gamecontrollerdb_length );
#endif

#else //#ifdef __ANDROID__
	load_gamecontrollerdb( (const char *) gamecontrollerdb, gamecontrollerdb_length );
#endif// #ifdef __ANDROID__


#endif //#ifndef UNIT_32BLIT

	set_screen_mode(ScreenMode::hires);

	joystick.x = joystick.y = tilt.x = tilt.y = tilt.z = 0;

	g_stereo_counter_random = 0;

	if( TPAGE01 == NULL)
	{


		TPAGE01 = Surface::load(tpage01);
		TPAGE02 = Surface::load(tpage02);
		TPAGE03 = Surface::load(tpage03);
		TPAGE04 = Surface::load(tpage04);
		TPAGE05 = Surface::load(tpage05);



		SoundInit();

		LOG_SND("SoundInit fin - amico_init  \n");

		amico_init();

		LOG_SND("amico_init fin  \n");



		screen.sprites = TPAGE03;

		g_r = (u8) screen.sprites->palette[1].r;
		g_g = (u8) screen.sprites->palette[1].g;
		g_b = (u8) screen.sprites->palette[1].b;


	//moved to amico init	amico_load_data();
	}
	else
		{
			LOG_ERR(" void init(void)  SERIOUS FAILED \n");
			exit(1);// error!
		}
		
		

// do again, to make sure - especially for android??!
		joystick.x = joystick.y = tilt.x = tilt.z = tilt.y = 0.0f;



} 



void update(uint32_t time) {
	// this is called many times a loop, i don't get why?

	g_ms_start =  time;

	//RefillBuffer(blit::channels[0]);
}



#define AMICO_MAIN_CONTROLLER_BUTTONS blit::buttons
// buttons.state

#define AMICO_MAIN_CONTROLLER_START Button::MENU




/*
    bool button_a = blit::buttons & blit::Button::A; // O
    bool button_b = blit::buttons & blit::Button::B; // X
    bool button_x = blit::buttons & blit::Button::X; // /\
    bool button_y = blit::buttons & blit::Button::Y; // []
 */

//OUYA_ANDROID android API-16 Android devices >= 4.1.2
//NEW_ANDROID = android API-23 Android devices >= 6.0

#define AMICO_MAIN_CONTROLLER_TRIANGLE  Button::X //PADLtriangle) //AMICO_MAIN_CONTROLLER_BUTTONS & Button::X) // up
#define AMICO_MAIN_CONTROLLER_CROSS  Button::B //PADLcross) //AMICO_MAIN_CONTROLLER_BUTTONS & Button::B) // down

#define AMICO_MAIN_CONTROLLER_CIRCLE  Button::A //PADLcircle) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::A) // right
#define AMICO_MAIN_CONTROLLER_SQUARE  Button::Y // PADLsquare) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::Y) // left



#define AMICO_MAIN_CONTROLLER_DPAD_UP  Button::DPAD_UP // PADLup) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_UP)
#define AMICO_MAIN_CONTROLLER_DPAD_DOWN  Button::DPAD_DOWN // PADLdown) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_DOWN)
#define AMICO_MAIN_CONTROLLER_DPAD_RIGHT  Button::DPAD_RIGHT //  PADLright) // buttonsAMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_RIGHT)
#define AMICO_MAIN_CONTROLLER_DPAD_LEFT  Button::DPAD_LEFT // PADLleft) // buttonsAMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_LEFT)




//#define AMICO_MAIN_DO_EXIT exit(0); 




void render(uint32_t time)
{
	{

		u8 dpad, buts;

		dpad =	buts =  0;

		LOG_DEL("\n void render(uint32_t time)  ReadPad3 g_player.shoot_timer %d \n", g_player.shoot_timer);
		g_player.shoot_dpad = 0;


	//	if(dpad == 0)
		{


			#define JOYSTICK_TOL 0.25f

			if (joystick.y > JOYSTICK_TOL)
			{
				LOG_PAD("\n PADLdown %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				dpad = dpad | CONTROL_DPAD_D;
				//player.dir = 1;


			}
			else if (joystick.y < -JOYSTICK_TOL)
			{

				LOG_PAD("\n PADLup %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				dpad = dpad | CONTROL_DPAD_U;
				//g_player.dir = 1;
			}


			if (joystick.x > JOYSTICK_TOL)
			{
				LOG_PAD("\n PADLright %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				dpad = dpad | CONTROL_DPAD_R;
				g_player.dir = 1;
			}
			else if (joystick.x < -JOYSTICK_TOL)
			{
				LOG_PAD("\n PADLleft %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				dpad = dpad | CONTROL_DPAD_L;
				g_player.dir = 0;
			}



		}


#ifndef UNIT_32BLIT // all controllers use second stick as shoot - twin stick


#define JOYSTICK2_TOL 0.50f

		if(g_player.shoot_timer == 0)
		{




#ifdef NEW_ANDROID //new android - not ouya





				if (tilt.y > JOYSTICK2_TOL) // up
				{
					LOG_PAD("\n if (tilt.x > JOYSTICK_TOL)  tilt.x  %f \n", tilt.x);
					g_player.shoot_dpad  =  CONTROL_DPAD_DD;
					g_player.shoot_timer=BUTTON_PRESS_TIME;


				}
				else if (tilt.y <  -(0.00025f)) //down   -JOYSTICK_TOL)//
				{

					LOG_PAD("\n else if (tilt.x < -JOYSTICK_TOL)  tilt.x %f \n", tilt.x);
					g_player.shoot_dpad  =  CONTROL_DPAD_UU;
					g_player.shoot_timer=BUTTON_PRESS_TIME;
				}


				if (tilt.x > JOYSTICK2_TOL) // right
				{
					LOG_PAD("\n else if (tilt.y < JOYSTICK_TOL)  tilt.y %f \n", tilt.y);
					g_player.shoot_dpad |= CONTROL_DPAD_RR;
					g_player.shoot_timer=BUTTON_PRESS_TIME;
				}
				else if (tilt.x < -(0.0001f)) // left  -JOYSTICK_TOL) //
				{
					LOG_PAD("\n else if (tilt.y < -JOYSTICK_TOL)  tilt.y %f \n", tilt.y);
					g_player.shoot_dpad |= CONTROL_DPAD_LL;
					g_player.shoot_timer=BUTTON_PRESS_TIME;
				}



#else  //new android - not ouya


#ifndef	OUYA_ANDROID // no right stick shooting for OUYA - my 2nd controller (same model) that works fine on other games, gets locked to left

				if (tilt.x > JOYSTICK2_TOL) // up
				{
					LOG_PAD("\n if (tilt.x > JOYSTICK_TOL)  tilt.x  %f \n", tilt.x);
					g_player.shoot_dpad  =  CONTROL_DPAD_DD;
					g_player.shoot_timer=BUTTON_PRESS_TIME;


				}
				else if (tilt.x <  -(0.00025f)) //down   -JOYSTICK_TOL)//
				{

					LOG_PAD("\n else if (tilt.x < -JOYSTICK_TOL)  tilt.x %f \n", tilt.x);
					g_player.shoot_dpad  =  CONTROL_DPAD_UU;
					g_player.shoot_timer=BUTTON_PRESS_TIME;
				}


				if (tilt.y > JOYSTICK2_TOL) // right
				{
					LOG_PAD("\n else if (tilt.y < JOYSTICK_TOL)  tilt.y %f \n", tilt.y);
					g_player.shoot_dpad |= CONTROL_DPAD_RR;
					g_player.shoot_timer=BUTTON_PRESS_TIME;
				}
				else if (tilt.y < -(0.0001f)) // left  -JOYSTICK_TOL) //
				{
					LOG_PAD("\n else if (tilt.y < -JOYSTICK_TOL)  tilt.y %f \n", tilt.y);
					g_player.shoot_dpad |= CONTROL_DPAD_LL;
					g_player.shoot_timer=BUTTON_PRESS_TIME;
				}

#endif // #ifndef	OUYA_ANDROID

#endif


#if 0
				if (tilt.z > JOYSTICK2_TOL)
				{
					LOG_PAD("\nelse if (tilt.z < -JOYSTICK_TOL)  tilt.z %f \n", tilt.z);
				}
				else if (tilt.z < -JOYSTICK2_TOL)
				{
					LOG_PAD("\nelse if (tilt.z < -JOYSTICK_TOL)  tilt.z %f \n", tilt.z);
				}
#endif
		}


// LOG_PAD("\n else if (tilt.y < -JOYSTICK_TOL)  tilt.y %f \n", tilt.y);




#endif




		if(g_player.shoot_timer)
			g_player.shoot_timer--;
		else
		{



			if (buttons.state & Button::JOYSTICK  )
			{
				LOG_PAD("\n buttons.state & Button::JOYSTICK %d \n", Button::JOYSTICK);
				g_player.shoot_dpad = CONTROL_DPAD_LEFT_RIGHT;
				g_player.shoot_timer = BUTTON_PRESS_TIME*2;
			}

			LOG_DEL("\n AMICO_MAIN_CONTROLLER_BUTTONS %d \n",AMICO_MAIN_CONTROLLER_BUTTONS);
			// needs to be processed out side of game state

			if(AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_START) // START is ESC
						{

							LOG_PAD("\n 1 start %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
			#if 0
							if(AMICO_MAIN_CONTROLLER_BUTTONS & PADLselect)//(AMICO_MAIN_CONTROLLER_BUTTONS & Button::MENU)
							{
								LOG_PAD("\n exit start and select %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);; //goto EXIT;//exit(0);
								AMICO_DO_EXIT; // goto EXIT;//exit(0);
							}
			#endif

							g_player.shoot_dpad =0;
							g_player.shoot_timer =BUTTON_PRESS_TIME;
							LOG_PAD("\n 2 start %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);

							if(g_function_loop == update_select)
							{
								LOG_PAD("\n g_function_loop =update_intro; %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
								g_game_counter = g_player.frame = 0;
								g_function_loop =update_intro;
							}
							else if( g_function_loop == update_game)
							{
								LOG_PAD("\n g_function_loop =update_pause; %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
								g_function_loop =update_pause;
								g_player.shoot_timer = BUTTON_PRESS_TIME*10;//TODO long lag
								g_game_counter =0;
								amico_stop_all_SFX();
								amico_BGM_quiet_time(1);
							}
							else if( g_function_loop == update_pause  && g_game_counter > 128)
							{
								LOG_PAD("\n g_function_loop =update_intro; %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
								// MACRO_GAME_RESET_AND_RANDOMIZE_LIST
								g_function_loop =update_dead; //update_intro;
								g_game_counter = g_player.frame = 0;
							}
							else if( g_function_loop == update_dead && g_game_counter > 128)
							{
								LOG_PAD("\n g_function_loop =update_dead; %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
								MACRO_GAME_RESET_AND_RANDOMIZE_LIST
								g_function_loop = update_intro;
								g_game_counter = g_player.frame = 0;
							}

							else if( g_function_loop == update_intro && g_game_counter > 128)
							{
								MACRO_GAME_RESET_AND_RANDOMIZE_LIST
								LOG_PAD("\n g_function_loop =update_dead; %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
								MACRO_GAME_RESET_AND_RANDOMIZE_LIST
								g_function_loop = update_splash;
								g_game_counter = g_player.frame = 0;
							}
							else if( g_function_loop == update_splash)
							{
								if(g_game_counter>>1 > 180)
								{
									g_game_counter =0;
									MACRO_GAME_RESET_AND_RANDOMIZE_LIST
								}
								else
								{
									LOG_PAD("\n g_function_loop is in early update_intro - goto exit\n");									
								}

							}
							//return;
							// continue;
						}

			/*
			 *
	{SDLK_j,       blit::Button::Y}, // left
	{SDLK_l,       blit::Button::A}, // right
	{SDLK_i,       blit::Button::X}, // up
	{SDLK_k,       blit::Button::B}, // down
			 *
			 */
			if(AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_TRIANGLE) //PADLtriangle) //AMICO_MAIN_CONTROLLER_BUTTONS & Button::X) // up
			{
				LOG_PAD("\n PADLtriangle %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				g_player.shoot_dpad |= CONTROL_DPAD_UU;
				g_player.shoot_timer=BUTTON_PRESS_TIME;
			}
			if(AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_CROSS) //AMICO_MAIN_CONTROLLER_BUTTONS & Button::B) // down
			{
				LOG_PAD("\n PADLcross %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				g_player.shoot_dpad |= CONTROL_DPAD_DD;
				g_player.shoot_timer=BUTTON_PRESS_TIME;
			}


			if(AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_CIRCLE) //PADLcircle) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::A) // right
			{
				LOG_PAD("\n PADLcircle %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				g_player.shoot_dpad |= CONTROL_DPAD_RR;
				g_player.shoot_timer=BUTTON_PRESS_TIME;
			}
			if(AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_SQUARE) // PADLsquare) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::Y) // left
			{
				LOG_PAD("\n PADLsquare %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
				g_player.shoot_dpad |= CONTROL_DPAD_LL;
				g_player.shoot_timer=BUTTON_PRESS_TIME;
			}



			if(g_gamestate.cheat_testing)
			{

				if(g_player.shoot_dpad)
				{
					g_gamestate.cheat_testing = 0;
				}
				else
				{

					g_player.shoot_dpad = CONTROL_DPAD_LEFT_RIGHT;					
					g_player.shoot_timer = BUTTON_PRESS_TIME*2;
					g_gamestate.p_health++;
					g_gamestate.level_bullets_used++; //to get stats
				}

			}



		}


		if (AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_DPAD_UP) // PADLup) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_UP)
		{
			LOG_PAD("\n PADLup %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
			dpad = dpad | CONTROL_DPAD_U;
		}
		else if (AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_DPAD_DOWN) // PADLdown) // AMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_DOWN)
		{
			LOG_PAD("\n PADLdown %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
			dpad = dpad | CONTROL_DPAD_D;
		}
		if (AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_DPAD_RIGHT) //  PADLright) // buttonsAMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_RIGHT)
		{
			LOG_PAD("\n PADLright %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
			dpad = dpad | CONTROL_DPAD_R;
			g_player.dir = 1;
		}
		else if (AMICO_MAIN_CONTROLLER_BUTTONS & AMICO_MAIN_CONTROLLER_DPAD_LEFT) // PADLleft) // buttonsAMICO_MAIN_CONTROLLER_BUTTONS & Button::DPAD_LEFT)
		{
			LOG_PAD("\n PADLleft %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);
			dpad = dpad | CONTROL_DPAD_L;
			g_player.dir = 0;
		}

		LOG_PAD("\n dpad %d \n", dpad);
		g_player.dpad = dpad;

		//clear screen NOT on pause screen






			u8 r, g, b;

			//LOG_PAD("\n 1 RenderPrepare dpad %d \n", AMICO_MAIN_CONTROLLER_BUTTONS);


			r = g_gamestate.BG_MAIN;
			g = 127;
			b = 127;


			//LOG_PAD("\n 2 RenderPrepare dpad r %d g %d b%d \n", r, g, b);


			if(g_gamestate.BG_SNARTBOMB)
			{
				LOG_PAD("\n if(g_gamestate.BG_SNARTBOMB) r %d g %d b%d g_gamestate.BG_SNARTBOMB %d\n", r, g, b, g_gamestate.BG_SNARTBOMB);

				if(g_gamestate.BG_SNARTBOMB&2)
					r = g= b=0;
				else
					r = g= b=127;

				g_gamestate.BG_SNARTBOMB--;
			}

			//LOG_PAD("\n 3 RenderPrepare dpad r %d g %d b%d \n", r, g, b);

			amico_rectangle(r, g, b, 0, 0, 320, 240 );




	 LOG_GAME_UPDATE("\n g_function_loop(); g_player.shoot_dpad %d g_player.dpad %d g_function_loop();  %x   amico: This is %s() from %s, line %d \n", g_player.shoot_dpad ,g_player.dpad, g_function_loop,__FUNCTION__, __FILE__, __LINE__);
		g_function_loop();



#ifdef TESTING
		g_gamestate.cheat_testing =1;
		//g_gamestate.enemy_next = g_gamestate.friend_next = 36;
#endif
		LOG_DEL("\n");

		// -------------------------------------------------------






		//printf("\n");



	}


#if 0
	if(0)
	{
		// draw FPS meter
		screen.alpha = 255;
		screen.pen = Pen(0, 0, 0);
		screen.rectangle(Rect(0, 240 - 8, 18, 8));
		screen.pen = Pen(255, 255, 255, 200);
		std::string fms = std::to_string(time - g_ms_start);
		screen.text(fms, minimal_font, Rect(1, 240 - 8, 10, 8));

		int block_size = 4;
		for (uint32_t i = 0; i < (time - g_ms_start); i++) {
			screen.pen = Pen(i * 5, 255 - (i * 5), 0);
			screen.rectangle(Rect(i * (block_size + 1) + 1 + 13, screen.bounds.h - block_size - 1, block_size, block_size));
		}

	}
	if(0)
	{
		//uint32_t ms_end =  - time;

		screen.pen = Pen(255, 100, 100);

		screen.text(std::to_string(g_game_counter), minimal_font, Point(5, 200));
		screen.text(std::to_string(g_player.dir), minimal_font, Point(5, 210));
		screen.text(std::to_string(g_player.speed), minimal_font, Point(5, 220));
		screen.text(std::to_string(time - g_ms_start), minimal_font, Point(5, 230));
	}

	// see 	render_32blit(); this is run from update not here, it's faster

#endif


}




