#include "Includes.h"

int timer;
int ranking[5];

void StartTimer()
{

	timer++;

	DrawFormatString(WINDOW_SIZE_X / 2, 10, 0xffffff, "%02d,%02d", timer / 60, timer % 60);
}

void ResetTimer()
{
	timer = 0;
}

void StopTimer()
{
}
