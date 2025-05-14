#pragma once

const int WinX = 640;
const int WinY = 480;

// エフェクト画像サイズ
const int EffectSizeX = 240;
const int EffectSizeY = 240;

const int ObjMax = 5;

extern bool finish;

extern int breakEffect[5];


namespace Game
{
	enum Mode {
		ModeInit,
		ModeSetUp,
		ModeTitle,
		ModeSelect,
		ModeGame,
		ModeResult,
		ModeFinish,
	};

	enum eBody {
		Error = -1,
		Head = 3,
		Hand_L = 7,
		Hand_R = 11,
		Foot_L = 15,
		Foot_R = 19,
	};

	typedef struct {
		float x;
		float y;
	}POS;


	class cKinectTracking
	{
	private:

		// キネクトハンドル
		HRESULT hrKinect;

		// ユーザーの骨格情報
		NUI_SKELETON_FRAME Skeleton;

		INuiSensor* Sensor;

		HANDLE hSkeletonEvent;

		HANDLE hEvents[1];

		POS fPos[20];

	public:


		void Connect();
		void GetData();
		void ResetColorPoint();
		void DebugPrint();
		void KinectShutdown();
		void DrawPos() {
			for (int i = 0; i < 20; i++) {
				// DrawFormatString(0, i * 20, 0xFFFFFF, "%f,%f", fPos[i].x, fPos[i].y);
			}
		}

		// 変数参照関数
		POS GetPos(eBody b) { return fPos[b]; }
	};

	class CColor {
	private:
		unsigned int iColor[20];
	public:
		CColor() {
			iColor[Head] = 0xFF0000;
			iColor[Hand_L] = 0x00FFFF;
			iColor[Hand_R] = 0x00FF00;
			iColor[Foot_L] = 0x0000FF;
			iColor[Foot_R] = 0x880088;
		}
		unsigned int GetMarkColor(eBody b)
		{
			return iColor[(int)b];
		}
		eBody	GetBody(int num) {
			switch (num) {
			case 0:
				return Head;
				break;
			case 1:
				return Hand_L;
				break;
			case 2:
				return Hand_R;
				break;
			case 3:
				return Foot_L;
				break;
			case 4:
				return Foot_R;
				break;
			default:
				return Error;
				break;
			}
		}

	};

	class CMarker {
	private:
		POS		fPos;
		eBody	Body;
		unsigned int iColor[20];
		float	fSizeR;
		CColor *Col;
		short  shMoveType;

		// 2dエフェクトの配列番号格納
		int iImagePoint;
		
		// クラス削除するかどうか判別する変数
		bool isJudgeEffect;
		bool isJudgeDelete;

	public:
		CMarker(){
			fPos	= { (float)GetRand(WinX), (float)GetRand(WinY / 2) + 100 };
			fSizeR	= 30.f + (float)GetRand(20);
			Col		= new CColor();
			Body	= Col->GetBody(GetRand(4));

			iImagePoint = -1;
			isJudgeDelete = false;
			isJudgeEffect = false;

			// マーカーの色が変わった
			iColor[Head] = 0xFF0000;
			iColor[Hand_L] = 0x00FFFF;
			iColor[Hand_R] = 0x00FF00;
			iColor[Foot_L] = 0x0000FF;
			iColor[Foot_R] = 0xF6F81B;

			// 的の動きの決定
			shMoveType = (short)GetRand(4);
		}
		~CMarker() {
			delete Col;
			Col = nullptr;
		}
		void	DrawMarker() {
				// DrawCircleAA(fPos.x, fPos.y, fSizeR, 20, iColor[Body], true);
				DrawFormatString(fPos.x, fPos.y, 0x000000, "%d", (int)Body);
				DrawBreakMarker();
			if (isJudgeEffect == true)
				DrawBreakEffect();
			// DrawFormatString(fPos.x, fPos.y, 0x000000, "%d", (int)Body);
		}
		void	DrawBreakMarker() {
			if (isJudgeEffect == false)
			for (int i = 0; i < 5; i++) {
				if (i % 2 != 0)DrawCircle((int)fPos.x, (int)fPos.y, 50 - 10 * i, 0xffffff, true);
				else DrawCircle((int)fPos.x, (int)fPos.y, 50 - 10 * i, iColor[Body], true);
			}
		}
		bool	Collision(eBody b, float x, float y) {
			if (fPos.x + fSizeR > x && fPos.x - fSizeR < x &&
				fPos.y + fSizeR > y && fPos.y - fSizeR < y) {
				if (b == Body) {
					isJudgeEffect = true;
					return true;
				}
			}
			/*if (((fPos.x - x) * (fPos.x - x)) + ((fPos.y - y) * (fPos.y - y)) < (fSizeR + 20.f) * (fSizeR + 20.f))
			{
				if (b == Body)
				{
					return true;
				}
			}*/
			return false;
		}
		void MoveMarker() {
			switch (shMoveType) {
			case 0:
				break;
			case 1:
				break;
			default:
				break;
			}
		}

		void	DrawBreakEffect() {
			if (iImagePoint == 5) isJudgeDelete = true;
			if (iImagePoint == -1) PlaySoundMem(GoodSE, DX_PLAYTYPE_BACK, TRUE);
			iImagePoint++;
			DrawGraph(fPos.x - EffectSizeX / 2, fPos.y - EffectSizeY / 2, breakEffect[iImagePoint], TRUE);
			
		}

		bool CheckJudgeDelete() { return isJudgeDelete; }
		bool CheckJudgeEffect() {return isJudgeEffect;}
		POS GetPos() { return fPos; }
	};

	class CGame {
	private:
		int iTurn;
		int iTurnMax;
		int iObjNum;
		int iScore;
		bool isClear;
		CMarker *Marker[ObjMax];
		cKinectTracking *k;

	public:
		CGame(int _iTurnMax)
		: iTurnMax(_iTurnMax)
		{
			iTurn = 0;
			k = new cKinectTracking();
			k->Connect();

			SetMarker(3 + GetRand(ObjMax - 3));
			isClear = false;

			// エフェクトロード
			LoadDivGraph("Image/Effect/BreakMarker.png", 5, 5, 1, 240, 240, breakEffect);
		}
		~CGame() {
			k->KinectShutdown();
			delete k;
			k = nullptr;
			DeleteMarker();

			// エフェクトデリート	
			for (int i = 0; i < 5; i++) {
				DeleteGraph(breakEffect[i]);
			}
		}
		bool	KinectSetUp() {

			for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; i++) {
				if (WinX < k->GetPos((eBody)i).x || 10 > k->GetPos((eBody)i).x ||
					WinY < k->GetPos((eBody)i).y || 10 > k->GetPos((eBody)i).y) {
					return false;
				}
			}
			return true;
		}
		void	KinectInfo() {
			k->GetData();
		}
		void	Update() {

			
			DrawMarker();
			
			int Touch = CollisionMarker();
			if (Touch != -1)
			{
				if (Marker[Touch]->CheckJudgeDelete() == true) {
					delete Marker[Touch];
					Marker[Touch] = nullptr;
					
				}
			}

			if (LiveMarker() == 0) {
				// finish = true;
				iTurn++;
				if (iTurn >= iTurnMax) {
					// kuria
					//isClear = true;
					//mode = ModeFinish;
					finish = true;
				}
				else {
					DeleteMarker();
					SetMarker(GetRand(4));
				}
			}

			/*for (int i = 0; i < ObjMax; i++) {
				if (Marker[i] != nullptr && Marker[i]->CheckJudgeDelete()) Marker[i]->DrawMarker();
				if (Marker[i] != nullptr) DrawFormatString(0, i * 20, 0xFFFFFF, "%f,%f", Marker[i]->GetPos().x, Marker[i]->GetPos().y);
			}*/
			

		}
		void	DeleteMarker() {
			for (int i = 0; i < ObjMax; i++) {
				delete Marker[i];
				Marker[i] = nullptr;
			}
		}
		int LiveMarker() {
			int count = 0;
			for (int i = 0; i < ObjMax; i++) {
				if (Marker[i] != nullptr) {
					count++;
				}
			}
			return count;
		}
		void	SetMarker(int num) {
			for (int i = 0; i < num; i++) {
				if (Marker[i] == nullptr) {
					Marker[i] = new CMarker();
				}
			}
		}
		int	CollisionMarker() {
			CColor c;
			for (int i = 0; i < ObjMax; i++)
			{

				if (Marker[0] != nullptr) {
					bool a = Marker[0]->Collision(c.GetBody(i), k->GetPos(c.GetBody(i)).x, k->GetPos(c.GetBody(i)).y);
					if (Marker[0]->CheckJudgeDelete()) {
						delete Marker[0];
						Marker[0] = nullptr;
						// PlaySoundMem(GoodSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}
				if (Marker[1] != nullptr) {
					bool a = Marker[1]->Collision(c.GetBody(i), k->GetPos(c.GetBody(i)).x, k->GetPos(c.GetBody(i)).y);
					if (Marker[1]->CheckJudgeDelete()) {
						delete Marker[1];
						Marker[1] = nullptr;
						// PlaySoundMem(GoodSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}
				if (Marker[2] != nullptr) {
					bool a = Marker[2]->Collision(c.GetBody(i), k->GetPos(c.GetBody(i)).x, k->GetPos(c.GetBody(i)).y);
					if (Marker[2]->CheckJudgeDelete()) {
						delete Marker[2];
						Marker[2] = nullptr;
						// PlaySoundMem(GoodSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}
				if (Marker[3] != nullptr) {
					bool a = Marker[3]->Collision(c.GetBody(i), k->GetPos(c.GetBody(i)).x, k->GetPos(c.GetBody(i)).y);
					if (Marker[3]->CheckJudgeDelete()) {
						delete Marker[3];
						Marker[3] = nullptr;
						// PlaySoundMem(GoodSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}
				if (Marker[4] != nullptr) {
					bool a = Marker[4]->Collision(c.GetBody(i), k->GetPos(c.GetBody(i)).x, k->GetPos(c.GetBody(i)).y);
					if (Marker[4]->CheckJudgeDelete()) {
						delete Marker[4];
						Marker[4] = nullptr;
						// PlaySoundMem(GoodSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}
			
	
			}
			return -1;
		}
		
		void	DrawMarker() {
			for (int i = 0; i < ObjMax; i++) {
				if (Marker[i] != nullptr) {
					Marker[i]->DrawMarker();
				}
			}
		}

		
	};

	
}

extern void Init();
extern void Updata();