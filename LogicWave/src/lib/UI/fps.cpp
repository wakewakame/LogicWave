#include "fps.h"

void FPS::SetFPS(double f) {
	if (f <= 0.0) {
		f = 30.0;
	}
	fps = f;
	bef = timeGetTime();
	gap = 1.0;
	speed = speed = 60.0 / fps;
}

void FPS::Wait() {
	//�t���[���Ԃ̎����擾
	gap = timeGetTime() - bef;

	//�t���[�����[�g����
	if ((1000.0 / fps) > (double)gap) {
		Sleep(
			(DWORD)(
				(1000.0 / fps) - (double)gap
			)
		);
	}

	//GPU���׎Z�o
	load = 100.0 * (double)gap / (1000.0 / fps);

	//���݂̃t���[�����[�g�擾
	r_fps = 1000.0 / (double)(timeGetTime() - bef);

	//60fps����Ƃ����A�j���[�V�����̃t���[���Ԃ̈ړ����x�̔{���Z�o
	speed = speed = 60.0 / r_fps;

	//���ݎ����ꎞ�ۑ�
	bef = timeGetTime();
	return;
}

double FPS::GetFPS() {
	return r_fps;
}

double FPS::GetSpeed() {
	return speed;
}

double FPS::GetLoad() {
	return load;
}