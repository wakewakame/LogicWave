#pragma once

#include "define.h"

//�C�x���g�����̊��N���X
class GET_EVENT {
public:
//�ϐ�������
	//GL�E�B���h�E�n���h��
	GLFWwindow *gl_hwnd;

//�֐�������
	//GL�E�B���h�E�n���h���ݒ�֐�
	virtual void SetGLhwnd(GLFWwindow *set_gl_hwnd);

	//�R���X�g���N�^
	GET_EVENT();
};