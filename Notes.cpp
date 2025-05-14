#include "Includes.h"

void cNotes::SetNotes()
{
	counter = -1;
	beat = 240000;
	for (int i = 0; i < MAX_NOTES; i++) {
		notes_flag[i] = false;
	}
	int set_notes_num = play_level * 10 + 10;
	for (int notes = 0; notes < set_notes_num; notes++) {
		notes_flag[notes] = true;
		notes_posCenter[notes] = 0;
		notes_ULposX[notes] = 0;
		notes_BMposX[notes] = 100;
	}
}

bool cNotes::bFallandPlayNotes(int life)
{
	if (counter == -1) {
		// PlaySoundMem(MusicLoop, DX_PLAYTYPE_LOOP, TRUE);
		PlaySoundMem(MusicLoop, DX_PLAYTYPE_LOOP,TRUE);
		start_time = GetNowHiPerformanceCount();
		counter = 0;
	}
	now_time = GetNowHiPerformanceCount();
	current_time = (int)((now_time - start_time) / 1000) - offset;

	while (current_time >= (60000 / BPM * counter) - 3000) {
		for (int i = 0; i < LANE_SIZE; i++) {
			// 拍 / テンポ * カウンター
			notes_time[counter % MAX_NOTES] = beat / BPM * counter;
		}
		counter++;
	}

	// 座標更新
	for (int i = 0; i < MAX_NOTES; i++) {
		if (notes_flag[i]) {
			if (notes_posCenter[i] == 0) {
				notes_ULposY[i] = (current_time - notes_time[i]) / 5 * notes_speed + WINDOW_SIZE_Y / 5 * 4 - NOTES_H;
				notes_BMposY[i] = (current_time - notes_time[i]) / 5 * notes_speed + WINDOW_SIZE_Y / 5 * 4 + NOTES_H;
				if (notes_BMposY[i] > WINDOW_SIZE_Y + 10) {
					notes_flag[i] = false; //画面外に出たらfalse
				}
			}

			
		}
	}

	// 描画
	for (int i = 0; i < MAX_NOTES; i++) {
		if (notes_flag[i]) {
			DrawCircle(notes_ULposX[i], notes_ULposY[i], 50, 0xffffff, true);
		}
	}

	// 判定ライン
	DrawLine(0, WINDOW_SIZE_Y / 5 * 4, WINDOW_SIZE_X, WINDOW_SIZE_Y / 5 * 4, GetColor(255, 255, 255));

	if (life == 0)
		return false;
	else
		return true;
}
