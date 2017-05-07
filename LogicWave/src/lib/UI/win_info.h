#pragma once

#include "define.h"
#include "mouse.h"
#include "fps.h"

//�E�B���h�E���ێ��ϐ�
class WINDOW_INFO {
private:
//�ϐ��錾
	//�O�t���[�����̃E�B���h�E�T�C�Y�ێ�
	WindowPoint b_size;

//�֐��錾
	//�E�B���h�E���T�C�Y�C�x���g�����֐�
	static void resize_event(GLFWwindow *window, int width, int heigh);
	
	//�E�B���h�E���T�C�Y�t���O����
	void resize_flag_event();

public:
//�R���X�g���N�^
	WINDOW_INFO();

//�ϐ��錾
	WindowPoint size; //�E�B���h�E�T�C�Y
	bool resize_flag;//�E�B���h�E�T�C�Y�ύX�t���O(�E�B���h�E���T�C�Y�ύX����̃t���[���̂�1)
	HWND hwnd; //OpenGL�̐����E�B���h�E�̃n���h��
	GLFWwindow *gl_hwnd; //OpenGL�̐���GL�E�B���h�E�̃n���h��
	MOUSE mouse; //�}�E�X�C�x���g�ێ��N���X
	FPS fps; //�t���[�����[�g�Ǘ��N���X
	std::string title; //�E�B���h�E�^�C�g��

//�֐��錾
	//WINDOW_INFO�̃C���X�^���X�擾�֐�
	static WINDOW_INFO *get_instance(GLFWwindow *const window);

	//GL�E�B���h�E�n���h���ݒ�֐�
	void set_GLhwnd(GLFWwindow *set_gl_hwnd);

	//�E�B���h�E�T�C�Y�ύX�֐�
	void set_window_size(int width, int heigh);

	//���[�v�֐�(�`��O�ɒu��)
	void loop();
};