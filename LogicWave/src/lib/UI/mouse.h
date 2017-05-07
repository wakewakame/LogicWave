#pragma once

#include "get_event.h"

class MOUSE : public GET_EVENT {
public:
//�\���̒�`
	struct Click {
		bool l; //l�N���b�N
		bool r; //r�N���b�N
		bool wheel; //�z�C�[��
	};

//�ϐ��錾
	WindowPoint mouse; //�}�E�X���W
	WindowPoint b_mouse; //�O�t���[���̃}�E�X���W
	Click push; //������Ă��炸����1
	Click b_push; //�O�t���[����push
	Click click; //�����ꂽ�t���[���̂�1
	double wheel; //�z�C�[���̑����
	bool wheel_flag; //�z�C�[���C�x���g�����������Ƃ��p�t���O

//�֐��錾
	//GL�E�B���h�E�n���h���ݒ�֐�
	void SetGLhwnd(GLFWwindow *set_gl_hwnd);

	//�w��RECT���ɑ��݂��邩�ǂ���
	bool hit(WindowRect area);
	bool hit(WindowPoint pos, double size);

	//���[�v�֐�
	void loop();

	//�R���X�g���N�^
	MOUSE();

private:
//�֐��錾
	//�}�E�X�C�x���g�擾�֐�
	void get_event();

	//�}�E�X�z�C�[���C�x���g�擾�p�R�[���o�b�N�֐�
	static void get_wheel(GLFWwindow *const window, double x, double y);

	//�N���b�N����
	void judge_click();
};