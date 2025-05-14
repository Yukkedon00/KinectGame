#pragma once

// 判定する場所の数
#define LANE_SIZE 4
// ノーツの最大数
#define MAX_NOTES 40
// BPM
#define BPM 120
// ノーツの縦幅
#define NOTES_H 10
class cNotes {

	// 0,1,2,3 左上、右上、右下、左下
	short notes_posCenter[MAX_NOTES];
	float notes_ULposX[MAX_NOTES];
	float notes_ULposY[MAX_NOTES];
	float notes_BMposX[MAX_NOTES];
	float notes_BMposY[MAX_NOTES];
	int   notes_time[MAX_NOTES];
	bool  notes_flag[MAX_NOTES];

	short play_level;

	// 時間関係
	LONGLONG start_time;
	LONGLONG now_time;
	int		 current_time;		// 経過時間
	int		 counter;			

	const int offset = 4000;

	// ノーツ設定
	const float notes_speed = 0.5f;

	// 拍設定
	int beat;

public:

	cNotes(){
		play_level = 0;
	}
	void SetNotes();
	bool bFallandPlayNotes(int life);

};
