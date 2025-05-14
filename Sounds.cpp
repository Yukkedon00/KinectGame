#include "Includes.h"

int MusicLoop;
int GoodSE;
int ButSE;
int EndSE;
int StartVoice;

void LoadMusicSE()
{
	MusicLoop = LoadSoundMem("Music/EdenAndHell.wav");
	EndSE = LoadSoundMem("Music/MusicEnd.wav");
	GoodSE = LoadSoundMem("SE/Good.wav");
	ButSE = LoadSoundMem("SE/But.wav");
	StartVoice = LoadSoundMem("SE/yoidon.mp3");
}
