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
	bool Open(LPSTR set_MapName) {
		std::cout << "MapName:" << set_MapName << std::endl;
		//文字列が存在しているか確認
		if (set_MapName == nullptr) { //引数がなければエラー
			std::cout << "MapName is not found" << std::endl;
			return 1;
		}
		std::cout << "MapName is exist" << std::endl;
		//文字列型変換処理
		wchar_t *MapName = new wchar_t[strlen(set_MapName) + 1];
		LPtoLPCW(set_MapName, MapName);
		//共有メモリの検索
		MapHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, (LPCTSTR)MapName); //ファイル名からマップハンドル取得
		if (MapHandle == NULL) { //マップが存在していなければエラー
			std::cout << "Map is not found" << std::endl;
			return 1;
		}
		//newした変数を解放
		delete MapName;
		std::cout << "Map is exist" << std::endl;
		//共有メモリのポインタ取得
		smd = (ShareMemData *)MapViewOfFile(MapHandle, FILE_MAP_ALL_ACCESS, 0, 0, ShareMemSize); //マップ内容同期
		std::cout << "To access Map is failed" << std::endl;
		if (smd == NULL) { //マップ内容取得ができていなければエラー
			return 1;
		}
		std::cout << "To access Map is success" << std::endl;
		return 0;
	}
	//LPSTR->LPCTSTR(=LPCWSTR)関数
	void LPtoLPCW(LPSTR str, wchar_t *wlocal) {
		MultiByteToWideChar(
			CP_ACP,
			MB_PRECOMPOSED,
			str,
			strlen(str),
			wlocal,
			strlen(str) + 1
		);
	}
};