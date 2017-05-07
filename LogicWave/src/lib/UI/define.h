#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

//���F���
struct VSTParameteres { //�p�����[�^�[�l�\����
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

//���L�������\����
struct ShareMemData {
	HWND Ready; //GUI�N���C�A���g���N�������TRUE�ɂ���(���d�N������̂���)
	HWND Host; //�`���n���h��
	VSTParameteres para; //VST�̃p�����[�^�[�Q
};

struct Dimension {
	bool on_limit_min; //�p�����[�^�̉���̍ŏ��l���L�����ǂ���
	bool on_limit_max; //�p�����[�^�̉���̍ő�l���L�����ǂ���
	float limit_min; //�p�����[�^�̉���̍ŏ��l
	float limit_max; //�p�����[�^�̉���̍ő�l
	int min_index; //�O���t�̕`���̍ŏ��l�p�����[�^�̃C���f�b�N�X
	int max_index; //�O���t�̕`���̍ő�l�p�����[�^�̃C���f�b�N�X
	std::vector<float> val; //�p�����[�^�̒l�̔z��
};

//���[�e�B���e�B�N���X
class Utility {
public:
	//�����ϊ��֐�(�߂�l:�ϊ���,����1~5:�ϊ��O�̒l,�ϊ��O�̍ŏ��l,�ϊ��O�̍ő�l,�ϊ���̍ŏ��l,�ϊ���̍ő�l)
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

//�O���t��̍��W
struct GraphPos {
	int x;
	float y;
};

//�E�B���h�E��̍��W
struct WindowPoint {
//�ϐ�
	double x;
	double y;

//���Z�q
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

//�E�B���h�E��̃T�C�Y
struct WindowRect {
//�ϐ�
	double left;
	double top;
	double right;
	double bottom;

//���Z�q
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

//�O���t�̃v���p�e�B
class graph {
public:
	float *samples; //�g�`�{��
	int num_sample; //�g�`�̃T���v����
	int start_index; //�`��̈�̎n�߂̔g�`�̃T���v���̃C���f�b�N�X
	int end_index; //�`��̈�̏I���̔g�`�̃T���v���̃C���f�b�N�X
	float zero_index_val; //�g�`�̃T���v����0�̒n�_�̃O���t��̒P�ʂ�x���W
	float last_index_val; //�g�`�̃T���v�����ŏI�n�_�̃O���t��̒P�ʂ�x���W
	float val_min; //�`��̈�̃T���v���l�̍ŏ��l
	float val_max; //�`��̈�̃T���v���l�̍ő�l
	float val_lim_min; //�`��̈�̃T���v���l�̍ŏ��l�̉���̍ŏ��l
	float val_lim_max; //�`��̈�̃T���v���l�̍ő�l�̉���̍ő�l
	graph() {
		//�ϐ�������
		samples = nullptr; //�g�`�{��
		num_sample = 0; //�g�`�̃T���v����
		start_index = 0; //�`��̈�̎n�߂̔g�`�̃T���v���̃C���f�b�N�X
		end_index = 0; //�`��̈�̏I���̔g�`�̃T���v���̃C���f�b�N�X
		zero_index_val = 0.0f; //�g�`�̃T���v����0�̒n�_�̃O���t��̒P�ʂ�x���W
		last_index_val = 1.0f; //�g�`�̃T���v�����ŏI�n�_�̃O���t��̒P�ʂ�x���W
		val_min = -1.0f; //�`��̈�̃T���v���l�̍ŏ��l
		val_max = 1.0f; //�`��̈�̃T���v���l�̍ő�l
		val_lim_min = -1.0f; //�`��̈�̃T���v���l�̍ŏ��l�̉���̍ŏ��l
		val_lim_max = 1.0f; //�`��̈�̃T���v���l�̍ő�l�̉���̍ő�l
	}
};