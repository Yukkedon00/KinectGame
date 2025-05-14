#pragma once

extern int ranking[5];
extern int hit_counter;

void SaveRanking(int num);	// ランキング書き込み
void ResetRanking();// ランキングリセット
void DrawRanking();