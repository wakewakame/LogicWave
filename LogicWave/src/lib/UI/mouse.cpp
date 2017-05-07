#include "mouse.h"
#include "win_info.h"

MOUSE::MOUSE() {
//�ϐ�������
	push.l = 0;
	push.r = 0;
	push.wheel = 0;
	b_push.l = 0;
	b_push.r = 0;
	b_push.wheel = 0;
	click.l = 0;
	click.r = 0;
	click.wheel = 0;
	mouse.x = 0.0;
	mouse.y = 0.0;
	b_mouse.x = 0.0;
	b_mouse.y = 0.0;
	wheel = 0.0;
	wheel_flag = 0;
}

void MOUSE::SetGLhwnd(GLFWwindow *set_gl_hwnd) {
	//���
	gl_hwnd = set_gl_hwnd;

	//�}�E�X�z�C�[���C�x���g�擾
	glfwSetScrollCallback(gl_hwnd, get_wheel);
}

bool MOUSE::hit(WindowRect area) {
	if (
		(area.left <= mouse.x) &&
		(area.top <= mouse.y) &&
		(area.right >= mouse.x) &&
		(area.bottom >= mouse.y)
		) {
		return 1;
	}
	return 0;
}

bool MOUSE::hit(WindowPoint pos, double size) {
	return hit({
		pos.x - size / 2.0,
		pos.y - size / 2.0,
		pos.x + size / 2.0,
		pos.y + size / 2.0
	});
}

void MOUSE::judge_click() {
	if ((push.l == 1) && (b_push.l == 0)) {
		click.l = 1;
	}
	else {
		click.l = 0;
	}
	if ((push.r == 1) && (b_push.r == 0)) {
		click.r = 1;
	}
	else {
		click.r = 0;
	}
	if ((push.wheel == 1) && (b_push.wheel == 0)) {
		click.wheel = 1;
	}
	else {
		click.wheel = 0;
	}
}

void MOUSE::loop() {
	get_event();
}

void MOUSE::get_event() {
	//�ꎞ���
	b_mouse = mouse;
	b_push = push;

	//�}�E�X�J�[�\�����W�̎擾
	glfwGetCursorPos(gl_hwnd, &mouse.x, &mouse.y);

	//�}�E�X�N���b�N�C�x���g�擾
	push.l = (glfwGetMouseButton(gl_hwnd, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS); //���N���b�N
	push.r = (glfwGetMouseButton(gl_hwnd, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS); //�E�N���b�N
	push.wheel = (glfwGetMouseButton(gl_hwnd, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS); //�z�C�[���N���b�N

	//�z�C�[���擾�t���O���Z�b�g
	if (wheel_flag == 1) {
		wheel_flag = 0;
	}else {
		wheel = 0.0;
	}

	//�N���b�N����
	judge_click();
}

void MOUSE::get_wheel(GLFWwindow *const window, double x, double y) {
	WINDOW_INFO::get_instance(window)->mouse.wheel_flag = 1;
	WINDOW_INFO::get_instance(window)->mouse.wheel += y;
}