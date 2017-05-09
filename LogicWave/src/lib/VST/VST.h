#include "define.h"
#include "../SM/ShareMemory.h"

//パラメータ変数等管理する
class AllProcess {
	//変数宣言
	//通信クラス
	ShareMem<ShareMemData> sm;
	//フレーム管理クラス
	FrameData frames;

	//関数宣言
	//ホストプロセスに接続する関数
	bool AccessHost(LPCTSTR MapName){
		return sm.Open(MapName);
	}
};