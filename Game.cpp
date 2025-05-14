#include "Includes.h"

using namespace Game;

Mode mode;
const	int iTurnMax = 5;
CGame *game;

bool finish = false;

int breakEffect[5];

void Init() 
{
	finish = false;

	// mode = ModeGame;
	game = new CGame(iTurnMax);
	
	// 時間リセット
	ResetTimer();

	mode = ModeInit;
}

void Updata() 
{
	switch (mode)
	{
	case ModeInit:
		DrawFormatString(30, 240, 0xffffff, "画面の中に体全体が入るようにしてください");
		if (game->KinectSetUp()) {
			mode = ModeTitle;
			ResetRanking();
		}
		break;
	case ModeSetUp:
		break;


	case ModeTitle:
		mode = ModeGame;
		break;

	case ModeSelect:
		break;
	case ModeGame:

		nBackGround::Draw();

		game->Update();

		if (CheckSoundMem(MusicLoop) == false)
		PlaySoundMem(MusicLoop, DX_PLAYTYPE_BACK, TRUE);



		StartTimer();

		if (finish == true) {

			SaveRanking(timer);
			mode = ModeFinish;
		}
		break;
	case ModeResult:
		break;
	case ModeFinish:
		DrawRanking();


		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			Init();
			mode = ModeGame;
		}

		break;
	default:
		break;
	}
	game->KinectInfo();
}

