#include "Includes.h"

short sMaxDate = sizeof(ranking) / sizeof(*ranking);

void SaveRanking(int num)
{
	int number = num;

	for (int i = 0; i < sMaxDate; i++) {

		if ((ranking[i] > num || ranking[i] == 0) && i + 1 != sMaxDate) {
			int buf = ranking[i];
			ranking[i] = num;
			num = buf;
		}
		if (ranking[i] > num && i + 1 == sMaxDate) {
			ranking[i] = num;
		}
	}
}

void ResetRanking()
{
	for (int i = 0; i < sMaxDate; i++) {
		ranking[i] = 0;
	}
}

void DrawRanking()
{	
	for (int i = 0; i < sMaxDate; i++) {
		DrawFormatString(WINDOW_SIZE_X / 4, (WINDOW_SIZE_Y / 6 * 1)*i, 0xffffff, "%d : %d", i + 1, ranking[i]);
	}
}
