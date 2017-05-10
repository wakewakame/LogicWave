#pragma once

#include "../UI/UILib.h"

//音色情報
struct ToneData {
	//音色系
	bool make_auto; //自動で音色を生成するか
	bool use_rawwave; //生波形データの使用をするかどうか
	bool change_natural; //音程変化を自然にするか
	float overtones[512]; //倍音グラフor共鳴スペクトルグラフ
	int iovertones; //倍音の数
	//生波形データ派生
	float rawwave[4096]; //生波形の使用部分波形(ファイルマッピングにするかも(´・ω・｀))
	int nrawwave; //生波形のサンプル数
	float base_pitch; //基音位置(手動変更可)
	//生成波形
	float outwave[4096]; //出力される波形
	int noutwave; //出力波形のサンプル数
		//フェード系
	bool use_string_mode; //弦モードの使用をするかどうか
	bool use_fade_change; //なめらかな音程,音量の変化を使用するかどうか(2つ同時に音を出せない)
	float fadein_vol[6];
	float fadein_pitch[6];
	float fadeout_vol[6];
	float fadeout_pitch[6];
	float fadechange_vol[6];
	float fadechange_pitch[6];
	//波形の絶対値の上限
	float wave_limit;
	//基本波形の形
	char wave_type;
	//再生中変更できると便利なパラメーター
	float vol;
	float pitch; //MIDI値に加算
};

//フレーム情報
class FrameData {
public:
	//UI管理クラスインスタンス化
	UILib ui;

	//変数初期化
	Frame *window; //サブrootフレーム
	Frame *root; //パラメータ関係のフレームツリーのrootフレーム
	Frame *tone; //音色設定フレーム
	Frame *fade; //フェード設定フレーム
	//音色系
	Button *make_auto; //自動で音色を生成するか
	Frame *raw_wave_para; //下記インデントを束ねる
	//生波形データ派生
	Button *use_rawwave; //生波形データの使用をするかどうか
	Graph *rawwave; //生波形の使用部分波形(ファイルマッピングにするかも(´・ω・｀))
	Graph *base_pitch; //基音位置(手動変更可)
	Frame *tone_para; //下記インデントのフレームを束ねる
	Button *change_natural; //音程変化を自然にするか
	Graph *overtones; //倍音グラフor共鳴スペクトルグラフ
	Figure *iovertones; //倍音の数
	WaveForm *wave_type; //基本波形の形
	//再生中変更できると便利なパラメーター
	Frame *hostpar;
	Volume *vol;
	Volume *pitch; //MIDI値に加算
	//波形の絶対値の上限
	Graph *wave_limit;
	//生成波形
	Graph *outwave; //出力される波形
	//フェード系
	Button *use_string_mode; //弦モードの使用をするかどうか
	Button *use_fade_change; //なめらかな音程,音量の変化を使用するかどうか(2つ同時に音を出せない)
	Frame *fadein;
	Fade *fadein_vol;
	Fade *fadein_pitch;
	Frame *fadeout;
	Fade *fadeout_vol;
	Fade *fadeout_pitch;
	Frame *fadechange;
	Fade *fadechange_vol;
	Fade *fadechange_pitch;
	Volume *scroll;

	//生成時自動配置
	void placement() {
		//親子関係の定義
		window = ui.window.add<Frame>();
		root = window->add<Frame>();
		tone = root->add<Frame>();
		make_auto = tone->add<Button>();
		raw_wave_para = tone->add<Frame>();
		use_rawwave = raw_wave_para->add<Button>();
		rawwave = raw_wave_para->add<Graph>();
		base_pitch = raw_wave_para->add<Graph>();
		tone_para = tone->add<Frame>();
		change_natural = tone_para->add<Button>();
		overtones = tone_para->add<Graph>();
		iovertones = tone_para->add<Figure>();
		wave_type = tone_para->add<WaveForm>();
		hostpar = tone_para->add<Frame>();
		vol = hostpar->add<Volume>();
		pitch = hostpar->add<Volume>();
		wave_limit = tone->add<Graph>();
		outwave = tone->add<Graph>();
		fade = root->add<Frame>();
		use_string_mode = fade->add<Button>();
		use_fade_change = fade->add<Button>();
		fadein = fade->add<Frame>();
		fadein_vol = fadein->add<Fade>();
		fadein_pitch = fadein->add<Fade>();
		fadeout = fade->add<Frame>();
		fadeout_vol = fadeout->add<Fade>();
		fadeout_pitch = fadeout->add<Fade>();
		fadechange = fade->add<Frame>();
		fadechange_vol = fadechange->add<Fade>();
		fadechange_pitch = fadechange->add<Fade>();
		scroll = window->add<Volume>();
		//配置
		window->mode = 1;
		root->scroll = 0.0;
		hostpar->mode = 1;
		fadein->mode = 1;
		fadeout->mode = 1;
		fadechange->mode = 1;
		scroll->length.x = 20.0;
		scroll->lock = 1;
		//整列
		ui.window.orderliness();
	}

	FrameData() {
		
	}
};

//共有メモリ構造体
struct ShareMemData {
	HWND Ready; //GUIクライアントが起動直後に自ウィンドウハンドル代入(多重起動回避のため)
	HWND Host; //ホストが生成したウィンドウのハンドル
	ToneData para; //VSTのパラメーター群
};