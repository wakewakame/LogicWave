#include "define.h"
#include "../SM/ShareMemory.h"
#include "../UI/UILib.h"

//�p�����[�^�ϐ����Ǘ�����
class AllProcess {
public:
	//�ϐ��錾
	//�ʐM�N���X
	ShareMem<ShareMemData> sm;
	//UI�N���X
	UILib ui;
	//�t���[���Ǘ��N���X
	FrameData frames;

	//�֐��錾
	//�S���������s����֐�
	bool start(LPSTR MapName);
};