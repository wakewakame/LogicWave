#include "UILib.h"

void UILib::viewport_resize() {
	if (f_exit) return;
	//�E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport(0, 0, win.size.x, win.size.y);

	//�ϊ��s��̏�����
	glLoadIdentity();

	//�X�N���[����̕\���̈���r���[�|�[�g�̑傫���ɔ�Ⴓ����
	glOrtho(0.0, (double)win.size.x, (double)win.size.y, 0.0, -1.0, 1.0);
}

bool UILib::error(bool val) {
	if (val) {
		exit();
		f_exit = 1;
	}
	return val;
}

void UILib::init() {
	//�ϐ�������
	f_exit = 0;

	//GLFW������
	if (error(glfwInit() == GL_FALSE)) return;

	//OpenGL Version 4.3���w��
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//�E�B���h�E����
	win.set_GLhwnd(
		glfwCreateWindow
			(
				win.size.x,
				win.size.y,
				win.title.c_str(),
				NULL,
				NULL
			)
	);
	
	//�E�B���h�E����������Ă��Ȃ���ΏI��
	if (error(win.hwnd == NULL)) return;
	
	//���������E�B���h�E��OpenGL�̏����Ώۂɂ���
	glfwMakeContextCurrent(win.gl_hwnd);

	//GLEW������
	glewExperimental = GL_TRUE;
	if (error(glewInit() != GLEW_OK)) return;
	
	//�f�t�H���g�Ńu�����h���[�h�L����
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //�A���t�@�u�����h�K�p

	//�f�t�H���g�ŃA���`�G�C���A�X�K��
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); //�_�̃A���`�G�C���A�X���x�ő剻
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); //���̃A���`�G�C���A�X���x�ő剻
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); //�ʂ̃A���`�G�C���A�X���x�ő剻
	glEnable(GL_POINT_SMOOTH); //�_
	glEnable(GL_LINE_SMOOTH); //��
	glEnable(GL_POLYGON_SMOOTH); //��

	//�E�B���h�E�ƃr���[�|�[�g�̍��W�P�ʓ���
	viewport_resize();

	//���������̃^�C�~���O��҂�
	glfwSwapInterval(1);

	//�t���[�����[�g�ݒ�
	win.fps.SetFPS(30);

	//window�t���[��������
	window.win = &win;
	window_resize(1);

	return;
}

void UILib::loop() {
	//�G���[�m�F
	if (f_exit) return;

	//�E�B���h�E���J���Ă���ԌJ��Ԃ�
	while (glfwWindowShouldClose(win.gl_hwnd) == GL_FALSE)
	{
		//�C�x���g����������܂őҋ@
		glfwPollEvents();

		//�C�x���g������
		win.loop();

		//��ʏ�����
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//�`��
		render();

		//���T�C�Y����
		window_resize();

		//�o�b�t�@�ɕ`��
		glFlush();

		//�J���[�o�b�t�@�����ւ���
		glfwSwapBuffers(win.gl_hwnd);
	}

}

void UILib::render() {
	window.draw();
	return;
}

void UILib::window_resize(bool init) {
	if(win.resize_flag || init){
		//window�t���[���T�C�Y����
		window.resize({ 0.0, 0.0, (double)win.size.x, (double)win.size.y });
		//�E�B���h�E�ƃr���[�|�[�g�̍��W�P�ʓ���
		viewport_resize();
	}
}

void UILib::exit() {
	if (f_exit) return;
	//GLFW�̏I��
	glfwTerminate();

	return;
}