#include "Includes.h"

using namespace Game;

void cKinectTracking::Connect()
{
	hrKinect = NuiCreateSensorByIndex(0, &Sensor);

	// 初期化
	hrKinect = NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);

	// ハンドル取得できないなら強制終了
	if (FAILED(hrKinect)) {
		exit(0);
	}

	// Skeletonストリーム
	hSkeletonEvent = INVALID_HANDLE_VALUE;
	hSkeletonEvent = CreateEvent(nullptr, true, false, nullptr);

	// 全身を認識
	Sensor->NuiSkeletonTrackingEnable(hSkeletonEvent, 0);

	// Event配列に代入
	hEvents[0] = hSkeletonEvent;
}

void cKinectTracking::GetData()
{
	// フレームの更新待ち
	ResetEvent(hSkeletonEvent);
	WaitForMultipleObjects(ARRAYSIZE(hEvents), hEvents, true, INFINITE);

	// Skeletonフレームを取得
	NUI_SKELETON_FRAME pSkeletonFrame = { 0 };
	hrKinect = Sensor->NuiSkeletonGetNextFrame(0, &pSkeletonFrame);
	if (FAILED(hrKinect)) {
		MessageBox(NULL, TEXT("エラー"), TEXT("フレーム取得エラー"), MB_OK);
		exit(0);
	}

	float pointx = 0, pointy = 0;

	POS fGetPos[20];

	for (int count = 0; count < NUI_SKELETON_COUNT; count++) {
		NUI_SKELETON_DATA skeleton = pSkeletonFrame.SkeletonData[count];
		if (skeleton.eTrackingState == NUI_SKELETON_TRACKED) {
			for (int position = 0; position < NUI_SKELETON_POSITION_COUNT; position++) {

				//NuiTransformSkeletonToDepthImage(skeleton.SkeletonPositions[position], &fGetPos[position].x, &fGetPos[position].y, NUI_IMAGE_RESOLUTION_640x480);
				NuiTransformSkeletonToDepthImage(skeleton.SkeletonPositions[position], &fPos[position].x, &fPos[position].y, NUI_IMAGE_RESOLUTION_640x480);
				// 頭、手、足なら配列に代入する
				// 3頭 7左手 11右手 15左足 19右足
				// 的と部位の色の違いはここに出ていた
				unsigned int iColor = 0xFFFFFF;
				if (position == Head) iColor = 0xFF0000;
				if (position == Foot_L) iColor = 0x0000FF;
				if (position == Foot_R) iColor = 0xFFFF00;
				if (position == Hand_L) iColor = 0x00FFFF;
				if (position == Hand_R) iColor = 0x00FF00;
				
				DrawCircleAA(fPos[position].x, fPos[position].y, 20.f, 20, iColor, true);
			}
		}
	}
}

void cKinectTracking::ResetColorPoint()
{
	srand((unsigned)time(NULL));
	/*RedPoint = rand() % 5;
	BluePoint = rand() % 5 + 5;
	YellowPoint = rand() % 5 + 10;
	AquaPoint = rand() % 5 + 15;*/
}

void cKinectTracking::DebugPrint()
{
	//DrawFormatString(0, 0, 0xffffff, "Head x: %f,Head y: %f,Head z: %f",partx[0],party[0],0);
}

void cKinectTracking::KinectShutdown()
{
	Sensor->NuiShutdown();
	Sensor->NuiSkeletonTrackingDisable();
	CloseHandle(hSkeletonEvent);

}
