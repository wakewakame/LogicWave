#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//グラフ描画クラス
class Graph : public Frame {
private:
	void main_draw();
	std::vector<int> wave;
	void glColor(double R, double G, double B, double A = 255.0) {
		glColor4d(R / 255.0, G / 255.0, B / 255.0, A / 255.0);
	}
public:
	Graph(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
	//波形情報と描画範囲
	graph grp;
	//波形を塗りつぶすかどうか
	bool fill_wave;
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