#define NUM_TRY 10 //���L�������ɃA�N�Z�X�����݂��
#define GAP_TRY 500 //���L�������ɃA�N�Z�X�����݂���(ms)

#include "VST.h"

bool AllProcess::start(LPSTR MapName) {
	bool req = 0;
	//�z�X�g�v���Z�X�ɐڑ�
	for (int i = 0; i <= NUM_TRY; i++) {
		if (i == NUM_TRY) return 1;
		if (!sm.Open(MapName)) break;
		Sleep(GAP_TRY);
	}
	//UI�N���X������
	frames.ui.init();
	//���d�N���h�~
	if (IsWindow(sm.smd->Ready) != 0) {
		return 1;
	}
	else {
		sm.smd->Ready = frames.ui.win.hwnd;
	}
	//�t���[�����[�g�ݒ�
	frames.ui.win.fps.SetFPS(30);
	//�t���[���z�u
	frames.placement();
	//���C�����[�`��
	while (true) {
		//UI���[�v�����ƃz�X�g�����m�F
		if (frames.ui.loop() || sm.smd->exit) {
			req = 1;
			break;
		}
	}
	//�I��������
	frames.ui.exit();
	return req;
}