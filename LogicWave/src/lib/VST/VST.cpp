#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	//�z�X�g�v���Z�X�ɐڑ�
	if (sm.Open(MapName)) {
		return 1;
	}
	//UI�N���X������
	frames.ui.init();
	//�t���[�����[�g�ݒ�
	frames.ui.win.fps.SetFPS(30);
	//�t���[���z�u
	frames.placement();
	//���C�����[�`��
	frames.ui.loop();
	//�I��������
	frames.ui.exit();
	return 0;
}