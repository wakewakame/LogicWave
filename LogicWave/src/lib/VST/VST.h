#include "define.h"
#include "../SM/ShareMemory.h"
#include "../UI/UILib.h"

//パラメータ変数等管理する
class AllProcess {
public:
	//変数宣言
	//通信クラス
	ShareMem<ShareMemData> sm;
	//UIクラス
	UILib ui;
	//フレーム管理クラス
	FrameData frames;

	//関数宣言
	//全処理を実行する関数
	bool start(LPSTR MapName);
};