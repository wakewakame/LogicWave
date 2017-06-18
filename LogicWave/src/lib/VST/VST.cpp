#define NUM_TRY 10 //共有メモリにアクセスを試みる回数
#define GAP_TRY 500 //共有メモリにアクセスを試みる区間(ms)

#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	bool req = 0;
	//ホストプロセスに接続
	for (int i = 0; i <= NUM_TRY; i++) {
		if (i == NUM_TRY) return 1;
		if (!sm.Open(MapName)) break;
		Sleep(GAP_TRY);
	}
	//UIクラス初期化
	frames.ui.init();
	//多重起動防止
	if (IsWindow(sm.smd->Ready) != 0) {
		return 1;
	}
	else {
		sm.smd->Ready = frames.ui.win.hwnd;
		frames.ui.win.close = 0;
	}
	//フレームレート設定
	frames.ui.win.fps.SetFPS(30);
	//フレーム配置
	frames.placement();
	//メインルーチン
	while (true) {
		//UIループ処理とホスト生存確認
		if (frames.ui.loop() || sm.smd->message == 1) {
			break;
		}
		//クローズボタンが押されたとき
		if (frames.ui.win.close_flag) {

			frames.ui.win.close_flag = 0;
		}
		//アクティブ化
		if (sm.smd->message == 2) {
			SetActiveWindow(frames.ui.win.hwnd);
		}
	}
	//終了時処理
	frames.ui.exit();
	return req;
}