#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	//�z�X�g�v���Z�X�ɐڑ�
	if (sm.Open(MapName)) {
		return 1;
	}
	//UI�N���X������
	ui.init();
	//���C�����[�`��
	ui.loop();
	//�I��������
	ui.exit();
	return 0;
}