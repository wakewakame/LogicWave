#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	//�z�X�g�v���Z�X�ɐڑ�
	if (sm.Open(MapName)) {
		return 1;
	}
	//UI�N���X������
	frames.ui.init();
	//�E�B���h�E�n���h�����
	sm.smd->Ready = frames.ui.win.hwnd;
	//�t���[�����[�g�ݒ�
	frames.ui.win.fps.SetFPS(30);
	//�t���[���z�u
	frames.placement();
	//���C�����[�`��
	while (true) {
		//UI���[�v����
		if (frames.ui.loop()) break;
		//�z�X�g�����m�F
		if (sm.smd->Host == nullptr) break;
	}
	//�I��������
	frames.ui.exit();
	return 0;
}