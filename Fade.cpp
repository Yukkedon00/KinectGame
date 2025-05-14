#include "Includes.h"

bool FadeIn(int speed)
{
	// フェードするスピード

	if (speed < 256) {
		speed++;
		return false;
	}

	else {
		return true;
	}

	SetDrawBright(speed, speed, speed);
}

bool FadeOut(int speed)
{
	// フェードするスピード
	if (speed > 0) {
		speed--;
		return false;
	}

	else {
		return true;
	}
	SetDrawBright(speed, speed, speed);
}
