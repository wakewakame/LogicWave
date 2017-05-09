#pragma once

#include <Windows.h>

//共有メモリアクセスクラス
template <class ShareMemData>
class ShareMem {
public:
	//変数初期化
	HANDLE MapHandle; //マップのハンドル
	ShareMemData *smd; //共有メモリデータポインタ
	int ShareMemSize; //マップのサイズ

	//関数宣言
	//コンストラクタ
	ShareMem() {
		MapHandle = nullptr; //マップのハンドル
		smd = nullptr; //共有メモリデータポインタ
		ShareMemSize = sizeof(ShareMemData); //マップのサイズ
	}
	//デストラクタ
	~ShareMem() {
		UnmapViewOfFile(smd); //共有メモリデータポインタ開放
	}
	//共有メモリアクセス関数
	bool Open(LPCTSTR MapName) {
		if (MapName == nullptr) { //引数がなければエラー
			return 1;
		}
		MapHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, MapName); //ファイル名からマップハンドル取得
		if (MapHandle == NULL) { //マップが存在していなければエラー
			return 1;
		}
		smd = (ShareMemData *)MapViewOfFile(MapHandle, FILE_MAP_ALL_ACCESS, 0, 0, ShareMemSize); //マップ内容同期
		if (smd == NULL) { //マップ内容取得ができていなければエラー
			return 1;
		}
		return 0;
	}
};