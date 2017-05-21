#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	//ホストプロセスに接続
	if (sm.Open(MapName)) {
		return 1;
	}
	//UIクラス初期化
	frames.ui.init();
	//フレームレート設定
	frames.ui.win.fps.SetFPS(30);
	//フレーム配置
	frames.placement();
	//メインルーチン
	frames.ui.loop();
	//終了時処理
	frames.ui.exit();
	return 0;
}