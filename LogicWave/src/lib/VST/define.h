#pragma once

#include "../UI/UILib.h"

//���F���
struct ToneData {
	//���F�n
	bool make_auto; //�����ŉ��F�𐶐����邩
	bool use_rawwave; //���g�`�f�[�^�̎g�p�����邩�ǂ���
	bool change_natural; //�����ω������R�ɂ��邩
	float overtones[512]; //�{���O���tor���X�y�N�g���O���t
	int iovertones; //�{���̐�
	//���g�`�f�[�^�h��
	float rawwave[4096]; //���g�`�̎g�p�����g�`(�t�@�C���}�b�s���O�ɂ��邩��(�L�E�ցE�M))
	int nrawwave; //���g�`�̃T���v����
	float base_pitch; //��ʒu(�蓮�ύX��)
	//�����g�`
	float outwave[4096]; //�o�͂����g�`
	int noutwave; //�o�͔g�`�̃T���v����
		//�t�F�[�h�n
	bool use_string_mode; //�����[�h�̎g�p�����邩�ǂ���
	bool use_fade_change; //�Ȃ߂炩�ȉ���,���ʂ̕ω����g�p���邩�ǂ���(2�����ɉ����o���Ȃ�)
	float fadein_vol[6];
	float fadein_pitch[6];
	float fadeout_vol[6];
	float fadeout_pitch[6];
	float fadechange_vol[6];
	float fadechange_pitch[6];
	//�g�`�̐�Βl�̏��
	float wave_limit;
	//��{�g�`�̌`
	char wave_type;
	//�Đ����ύX�ł���ƕ֗��ȃp�����[�^�[
	float vol;
	float pitch; //MIDI�l�ɉ��Z
};

//�t���[�����
class FrameData {
public:
	//UI�Ǘ��N���X�C���X�^���X��
	UILib ui;

	//�ϐ�������
	Frame *window; //�T�uroot�t���[��
	Frame *root; //�p�����[�^�֌W�̃t���[���c���[��root�t���[��
	Frame *tone; //���F�ݒ�t���[��
	Frame *fade; //�t�F�[�h�ݒ�t���[��
	//���F�n
	Button *make_auto; //�����ŉ��F�𐶐����邩
	Frame *raw_wave_para; //���L�C���f���g�𑩂˂�
	//���g�`�f�[�^�h��
	Button *use_rawwave; //���g�`�f�[�^�̎g�p�����邩�ǂ���
	Graph *rawwave; //���g�`�̎g�p�����g�`(�t�@�C���}�b�s���O�ɂ��邩��(�L�E�ցE�M))
	Graph *base_pitch; //��ʒu(�蓮�ύX��)
	Frame *tone_para; //���L�C���f���g�̃t���[���𑩂˂�
	Button *change_natural; //�����ω������R�ɂ��邩
	Graph *overtones; //�{���O���tor���X�y�N�g���O���t
	Figure *iovertones; //�{���̐�
	WaveForm *wave_type; //��{�g�`�̌`
	//�Đ����ύX�ł���ƕ֗��ȃp�����[�^�[
	Frame *hostpar;
	Volume *vol;
	Volume *pitch; //MIDI�l�ɉ��Z
	//�g�`�̐�Βl�̏��
	Graph *wave_limit;
	//�����g�`
	Graph *outwave; //�o�͂����g�`
	//�t�F�[�h�n
	Button *use_string_mode; //�����[�h�̎g�p�����邩�ǂ���
	Button *use_fade_change; //�Ȃ߂炩�ȉ���,���ʂ̕ω����g�p���邩�ǂ���(2�����ɉ����o���Ȃ�)
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

	//�����������z�u
	void placement() {
		//�e�q�֌W�̒�`
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
		//�z�u
		window->mode = 1;
		root->scroll = 0.0;
		hostpar->mode = 1;
		fadein->mode = 1;
		fadeout->mode = 1;
		fadechange->mode = 1;
		scroll->length.x = 20.0;
		scroll->lock = 1;
		//����
		ui.window.orderliness();
	}

	FrameData() {
		
	}
};

//���L�������\����
struct ShareMemData {
	HWND Ready; //GUI�N���C�A���g���N������Ɏ��E�B���h�E�n���h�����(���d�N������̂���)
	HWND Host; //�z�X�g�����������E�B���h�E�̃n���h��
	ToneData para; //VST�̃p�����[�^�[�Q
};