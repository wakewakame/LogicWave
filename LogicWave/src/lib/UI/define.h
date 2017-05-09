#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

//ユーティリティクラス
class Utility {
public:
	//割合変換関数(戻り値:変換後,引数1~5:変換前の値,変換前の最小値,変換前の最大値,変換後の最小値,変換後の最大値)
	static double Proportion(double i, double i_mix, double i_max, double j_min, double j_max) {
		double j;
		j = j_min + (i - i_mix) * ((j_max - j_min) / (i_max - i_mix));
		return j;
	}
	static float Proportion(float i, float i_mix, float i_max, float j_min, float j_max) {
		float j;
		j = float(Proportion(double(i), double(i_mix), double(i_max), double(j_min), double(j_max)));
		return j;
	}
	static int Proportion(int i, int i_mix, int i_max, int j_min, int j_max) {
		int j;
		j = int(Proportion(double(i), double(i_mix), double(i_max), double(j_min), double(j_max)));
		return j;
	}
	//LPSTR->LPCTSTR(=LPCWSTR)
	static void LPtoLPCW(LPSTR str, wchar_t wlocal[300]) {
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

//グラフ上の座標
struct GraphPos {
	int x;
	float y;
};

//ウィンドウ上の座標
struct WindowPoint {
//変数
	double x;
	double y;

//演算子
	void operator += (WindowPoint a) {
		this->x += a.x;
		this->y += a.y;
	}
	void operator += (double a) {
		this->x += a;
		this->y += a;
	}
	void operator -= (WindowPoint a) {
		this->x -= a.x;
		this->y -= a.y;
	}
	void operator -= (double a) {
		this->x -= a;
		this->y -= a;
	}
	bool operator == (WindowPoint a) {
		return (
			this->x == a.x &&
			this->y == a.y
		);
	}
	bool operator != (WindowPoint a) {
		return (
			this->x != a.x ||
			this->y != a.y
		);
	}
};

//ウィンドウ上のサイズ
struct WindowRect {
//変数
	double left;
	double top;
	double right;
	double bottom;

//演算子
	void operator += (WindowRect a) {
		this->left += a.left;
		this->top += a.top;
		this->right += a.right;
		this->bottom += a.bottom;
	}
	void operator -= (WindowRect a) {
		this->left -= a.left;
		this->top -= a.top;
		this->right -= a.right;
		this->bottom -= a.bottom;
	}
	bool operator == (WindowRect a){
		return (
			this->left == a.left &&
			this->top == a.top &&
			this->right == a.right &&
			this->bottom == a.bottom
		);
	}
	bool operator != (WindowRect a) {
		return (
			this->left != a.left ||
			this->top != a.top ||
			this->right != a.right ||
			this->bottom != a.bottom
			);
	}
};

//グラフのプロパティ
class graph {
public:
	float *samples; //波形本体
	int num_sample; //波形のサンプル数
	int start_index; //描画領域の始めの波形のサンプルのインデックス
	int end_index; //描画領域の終わりの波形のサンプルのインデックス
	float zero_index_val; //波形のサンプルが0の地点のグラフ上の単位のx座標
	float last_index_val; //波形のサンプルが最終地点のグラフ上の単位のx座標
	float val_min; //描画領域のサンプル値の最小値
	float val_max; //描画領域のサンプル値の最大値
	float val_lim_min; //描画領域のサンプル値の最小値の可動域の最小値
	float val_lim_max; //描画領域のサンプル値の最大値の可動域の最大値
	graph() {
		//変数初期化
		samples = nullptr; //波形本体
		num_sample = 0; //波形のサンプル数
		start_index = 0; //描画領域の始めの波形のサンプルのインデックス
		end_index = 0; //描画領域の終わりの波形のサンプルのインデックス
		zero_index_val = 0.0f; //波形のサンプルが0の地点のグラフ上の単位のx座標
		last_index_val = 1.0f; //波形のサンプルが最終地点のグラフ上の単位のx座標
		val_min = -1.0f; //描画領域のサンプル値の最小値
		val_max = 1.0f; //描画領域のサンプル値の最大値
		val_lim_min = -1.0f; //描画領域のサンプル値の最小値の可動域の最小値
		val_lim_max = 1.0f; //描画領域のサンプル値の最大値の可動域の最大値
	}
};