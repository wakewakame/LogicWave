//デバッグモードの時は下のコメントアウトを外す
#define DEBUG

//コンソール非表示化
#ifndef DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include "lib/VST/VST.h"

int main(int argc, LPSTR argv[]) {
	//クラスインスタンス化
	AllProcess ap;

	//全ての処理を実行
	//ap.start("VSTGUIMEM0");
	if (argc == 2) {
		return ap.start(argv[1]);
	}
	else {
		return 1;
	}
}