#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	//ホストプロセスに接続
	if (sm.Open(MapName)) {
		return 1;
	}
	//UIクラス初期化
	frames.ui.init();
	//ウィンドウハンドル代入
	sm.smd->Ready = frames.ui.win.hwnd;
	//フレームレート設定
	frames.ui.win.fps.SetFPS(30);
	//フレーム配置
	frames.placement();
	//メインルーチン
	while (true) {
		//UIループ処理
		if (frames.ui.loop()) break;
		//ホスト生存確認
		if (sm.smd->Host == nullptr) break;
	}
	//終了時処理
	frames.ui.exit();
	return 0;
}