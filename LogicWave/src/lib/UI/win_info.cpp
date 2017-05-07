#include "win_info.h"

WINDOW_INFO::WINDOW_INFO() {
//�ϐ�������
	size = { 640.0, 480.0 }; //�E�B���h�E�T�C�Y
	b_size = size;
	resize_flag = 0;
	hwnd = nullptr; //OpenGL�̐����E�B���h�E�̃n���h��
	gl_hwnd = nullptr;
	fps.SetFPS(30.0); //�t���[�����[�g�ݒ�
	title = "UILib"; //�E�B���h�E�^�C�g���ݒ�
}

void WINDOW_INFO::resize_event(GLFWwindow *window, int width, int heigh) {
	WINDOW_INFO::get_instance(window)->b_size = WINDOW_INFO::get_instance(window)->size;
	WINDOW_INFO::get_instance(window)->size.x = (double)width;
	WINDOW_INFO::get_instance(window)->size.y = (double)heigh;
}

void WINDOW_INFO::resize_flag_event() {
	if (size != b_size) {
		resize_flag = 1;
		b_size = size;
	}
	else {
		if (resize_flag) {
			resize_flag = 0;
		}
	}
}

WINDOW_INFO *WINDOW_INFO::get_instance(GLFWwindow *const window) {
	return (WINDOW_INFO*)glfwGetWindowUserPointer(window);
}

void WINDOW_INFO::set_GLhwnd(GLFWwindow *set_gl_hwnd) {
	//���
	gl_hwnd = set_gl_hwnd;
	hwnd = (HWND)gl_hwnd;

	//�R�[���o�b�N�֐��p���N���X�̃|�C���^�w��
	glfwSetWindowUserPointer(gl_hwnd, this);

	//�E�B���h�E���T�C�Y�C�x���g�̃R�[���o�b�N�֐��o�^
	glfwSetWindowSizeCallback(gl_hwnd, resize_event);

	//���
	mouse.SetGLhwnd(gl_hwnd);
}

void WINDOW_INFO::set_window_size(int width, int heigh) {
	if (gl_hwnd == nullptr) {
		size = { (double)width, (double)heigh };
	}
	else {
		resize_event(gl_hwnd, (double)width, (double)heigh);
	}
}

void WINDOW_INFO::loop() {
	//�`��㏈��
	fps.Wait();

	//�`��O����
	mouse.loop();
	resize_flag_event();
}