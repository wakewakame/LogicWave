#pragma once

#include "define.h"
#include "win_info.h"

//フレーム基底クラス
class Frame {
protected:
//管理系関数
	//全変数初期化
	void reset();
	//子フレームから自フレームのlengthとlock_lengthを算出(子フレームが追加されるたびにrootフレームのこの関数を呼ぶ)
	void get_length();
	//rootフレームのポインタ取得
	void get_root();
	//自フレームのインデックス番号取得
	void get_index();
	//イベント処理
	virtual void event();
	//自フレームの中に描画する関数
	virtual void main_draw();
	//自フレーム以下の全子フレームのdraw関数実行
	void childs_draw();
	//フレーム追加時実行関数
	virtual void when_create();

public:
	//変数
	Frame *root; //rootフレームのポインタ
	Frame *parent; //親フレームのポインタ
	std::vector<Frame*> childs; //全子フレームのポインタ配列
	int index;//同フレーム内の自フレームの割当番号(=0,1,2,3,...)
	WindowRect pos; //フレーム座標
	WindowPoint size; //フレームサイズ(末端フレームのみ代入)
	std::string name; //フレームの名称
	std::string description; //フレーム内のUIの解説
	bool mode; //子フレームが縦並び=0,横並び=1
	double gap; //子フレーム間同士の隙間(px単位)
	WindowPoint length; //全フレームが初期値サイズ時の自フレームのサイズ
	bool lock; //各子フレームの長さ(mode=0なら縦幅,mode=1なら横幅)の固定on/off
	WindowPoint lock_length; //固定サイズの全子フレームと全gapの和(末端フレームは0を代入)
	WINDOW_INFO *win;

	//関数宣言
	//WINDOW_INFOポインタ代入
	void set_win_info(WINDOW_INFO *set_win);
	//自フレーム以下の全フレーム描画
	void draw();
	//自フレームのサイズに合わせて子フレームサイズ更新
	void resize(WindowRect set_pos = { -1.0, -1.0, -1.0, -1.0 });
	//rootフレーム以下のフレーム配置の整頓(フレームを追加し終わったら必ず実行)
	void orderliness();
	//子フレーム追加(使い方:Frame *x = Frame::add<type>();)
	template <class T> T *add(){
		return new T(this);
	}
	//コンストラクタ
	Frame(Frame *set_parent = nullptr);
	//デストラクタ
	~Frame();
};