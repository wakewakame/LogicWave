//�f�o�b�O���[�h�̎��͉��̃R�����g�A�E�g���O��
#define DEBUG

//�R���\�[����\����
#ifndef DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include "lib/VST/VST.h"

int main(int argc, LPSTR argv[]) {
	//�N���X�C���X�^���X��
	AllProcess ap;

	//�S�Ă̏��������s
	//ap.start("VSTGUIMEM0");
	if (argc == 2) {
		return ap.start(argv[1]);
	}
	else {
		return 1;
	}
}