#include "define.h"
#include "../SM/ShareMemory.h"

//�p�����[�^�ϐ����Ǘ�����
class AllProcess {
	//�ϐ��錾
	//�ʐM�N���X
	ShareMem<ShareMemData> sm;
	//�t���[���Ǘ��N���X
	FrameData frames;

	//�֐��錾
	//�z�X�g�v���Z�X�ɐڑ�����֐�
	bool AccessHost(LPCTSTR MapName){
		return sm.Open(MapName);
	}
};