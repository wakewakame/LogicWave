#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	//ホストプロセスに接続
	if (sm.Open(MapName)) {
		return 1;
	}
	//UIクラス初期化
	ui.init();
	//メインルーチン
	ui.loop();
	//終了時処理
	ui.exit();
	return 0;
}