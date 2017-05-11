#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//スクロール可能フレームクラス
class Scroll : public Frame {
private:
	void event() {
		if (win->mouse.wheel != 0.0 || parent->mode?size.y:size.x != parent->mode?length.y:length.x) {
			scroll -= 0.02*(double)(win->mouse.wheel);
			if (scroll < 0.0) scroll = 0.0;
			if (scroll > 1.0) scroll = 1.0;
			if (parent->mode) {
				pos.top = parent->pos.top + parent->gap - scroll*(length.y - (parent->size.y - parent->gap*2.0));
				pos.bottom = pos.top + length.y;
			}else{
				pos.left = parent->pos.left + parent->gap - scroll*(length.x - (parent->size.x - parent->gap*2.0));
				pos.right = pos.left + length.x;
			}
			resize(pos);
		}
	}

public:
	//変数宣言
	double scroll;

	//コンストラクタ
	//スクロールフレームは親フレーム必須のため、デフォルト引数なし
	Scroll(Frame *set_parent) : Frame(set_parent) {
		scroll = 0.0;
	}
};

//グラフ描画クラス
class Graph : public Frame {
private:
	void main_draw();
	std::vector<int> wave;
public:
	//変数宣言
	//波形情報と描画範囲
	graph grp;
	//波形を塗りつぶすかどうか
	bool fill_wave;

	//コンストラクタ
	Graph(Frame *set_parent = nullptr) : Frame(set_parent) {
		fill_wave = 0;
	}
};

//カーソル付きグラフ描画クラス
class CursorGraph : public Graph {
private:

public:
	CursorGraph(Frame *set_parent = nullptr) : Graph(set_parent) {

	}
};

//フェードグラフ描画クラス
class Fade : public Frame {
public:
	Fade(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};


//ボタン描画クラス
class Button : public Frame {
public:
	Button(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};

//ボリューム描画クラス
class Volume : public Frame {
public:
	Volume(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};

//個数選択描画クラス
class Figure : public Frame {
public:
	Figure(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};

//波形の形選択描画クラス
class WaveForm : public Frame {
public:
	WaveForm(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};