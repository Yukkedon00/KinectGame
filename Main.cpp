#include "Includes.h"

// 色はオレンジ・青
// 黄緑・ピンク
// 時間があれば両方実装する



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	Init();
	// サウンド関係をすべてロード
	LoadMusicSE();

	SetMainWindowText("ObjectChach"); //ウインドウのタイトルを設定
								  
									  // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		
		Updata();
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}