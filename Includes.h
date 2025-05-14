#pragma once

// 標準ライブラリ
#include <Windows.h>
#include <math.h>
#include <time.h>

// Kinect API
#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSkeleton.h>
#include <NuiSensor.h>

// Dxlib
#include "DxLib.h"

// 自作ヘッダー
#include "Kinect.h"
// マクロ定義
#define MAX_SKELETON 2

// 画面サイズ
#define WINDOW_SIZE_X 640
#define WINDOW_SIZE_Y 480

// フェードスピード
#define FADE_SPEED 2


#include "BackGround.h"
#include "Fade.h"
#include "Sounds.h"
#include "Game.h"
#include "Timer.h"
#include "Ranking.h"


// 3dキャラのボーンナンバー
// 塊のもの

const int LOWER_BODY = 219;

// 左側
const int LEFT_KNEE = 221;
const int LEFT_TOES = 225;
const int LEFT_SHOULDER = 85;
const int LEFT_ELBOW = 88;
const int LEFT_WRIST = 90;
const int LEFT_HAND = 95;

// 右側
const int RIGHT_KNEE = 227;
const int RIGHT_TOES = 229;
const int RIGHT_SHOULDER = 126;
const int RIGHT_ELBOW = 129;
const int RIGHT_WRIST = 131;
const int RIGHT_HAND = 136;
