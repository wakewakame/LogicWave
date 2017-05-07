#pragma once

#include "define.h"
#include "Frame.h"

//�O���t�p�����[�^�ێ�
/*
�g����
�p�����[�^��K�v�ȕ�����create�֐��Ő���
�����͎����Ŋm�ۂ��Ă����
�p�����[�^�̉���͕K�v������ΐݒ�
�E�B���h�E��x,y���W�ɑΉ����鎟���̐ݒ�
*/
class GraphPara {
private:
	std::vector<Dimension> param; //�e�����̃p�����[�^�z��
	int active; //���݃A�N�e�B�u�ȃp�����[�^�̃C���f�b�N�X
	WindowPoint mouse; //���݂̃}�E�X���W
	Frame *f; //�g�p����t���[���̃|�C���^
	int x_dim; //�E�B���h�Ex���W�ɑΉ����鎟���ԍ�
	int y_dim; //�E�B���h�Ey���W�ɑΉ����鎟���ԍ�
	std::vector<float> length_min;
	int height; //1�����݂̂̏ꍇ�̃p�����[�^��XorY���W
public:
	//�R���X�g���N�g
	GraphPara();
	//�P�ʕϊ��֐�
	float percent(float a, float a_min, float a_max, float b_min, float b_max);
	int percent(int a, int a_min, int a_max, int b_min, int b_max);
	//�t���[���ݒ�
	void set_frame(Frame *set_f);
	//�V�K�p�����[�^�ǉ��֐�(�ŏ��l�ƍő�l�̃p�����[�^�͕K������)
	void create(int argnum, ...);
	//�O���t�̕`���̍ŏ��l�p�����[�^�̃C���f�b�N�X�ݒ�
	void set_min(int dim, int index);
	//�O���t�̕`���̍ő�l�p�����[�^�̃C���f�b�N�X
	void set_max(int dim, int index);
	//�ő�l�ŏ��l�p�����[�^�Ԃ̍ŏ��̋����ݒ�
	void set_length_min(int dim, float min);
	//�p�����[�^�擾�֐�
	const float get_param(int dim, int index);
	//�p�����[�^�̉���̍ŏ��l�ݒ�
	void limit_min(float min, int dim);
	//�p�����[�^�̉���̍ő�l�ݒ�
	void limit_max(float max, int dim);
	//�p�����[�^�̉���̍ŏ��l�擾
	const float get_lim_min(int dim);
	//�p�����[�^�̉���̍ő�l�擾
	const float get_lim_max(int dim);
	//�ŏ��l�p�����[�^�擾�֐�
	const float get_min(int dim);
	//�ő�l�p�����[�^�擾�֐�
	const float get_max(int dim);
	//�ŏ��l�C���f�b�N�X�擾�֐�
	const int get_imin(int dim);
	//�ő�l�C���f�b�N�X�擾�֐�
	const int get_imax(int dim);
	//���݃A�N�e�B�u�ȃp�����[�^�̃C���f�b�N�X�ݒ�(�Ȃ��ꍇ��index=-1)
	void set_active(int index);
	//���݃A�N�e�B�u�ȃp�����[�^�̃C���f�b�N�X�擾
	const int get_active();
	//�E�B���h�E��x,y���W�ɑΉ����鎟�����̐ݒ�
	void set_window_dim(int set_x_dim, int set_y_dim);
	//�E�B���h�E��x���W�ɑΉ����鎟�����̎擾
	const int get_x_dim();
	//�E�B���h�E��y���W�ɑΉ����鎟�����̎擾
	const int get_y_dim();
	//�t���[�����W�ϊ��֐�
	const WindowPoint get_pos(int index);
	//�p�����[�^���W�ϊ��֐�
	void set_pos(WindowPoint pos, int index);
	//�w��͈͓��Ɏw��n�����݂��邩�ǂ����𔻒肷��֐�
	const bool hit(WindowRect area, WindowPoint pos);
	const bool hit(WindowPoint center, WindowPoint size, WindowPoint pos);
	//�h���b�O���}�E�X�Ǐ]�֐�
	void seek(int index, WindowPoint n_mouse, bool l_click, bool b_l_click, WindowPoint size);
	//�p�����[�^�ύX���֐��֐�
	void limiter(int index);
};