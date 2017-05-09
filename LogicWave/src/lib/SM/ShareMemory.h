#pragma once

#include <Windows.h>

//���L�������A�N�Z�X�N���X
template <class ShareMemData>
class ShareMem {
public:
	//�ϐ�������
	HANDLE MapHandle; //�}�b�v�̃n���h��
	ShareMemData *smd; //���L�������f�[�^�|�C���^
	int ShareMemSize; //�}�b�v�̃T�C�Y

	//�֐��錾
	//�R���X�g���N�^
	ShareMem() {
		MapHandle = nullptr; //�}�b�v�̃n���h��
		smd = nullptr; //���L�������f�[�^�|�C���^
		ShareMemSize = sizeof(ShareMemData); //�}�b�v�̃T�C�Y
	}
	//�f�X�g���N�^
	~ShareMem() {
		UnmapViewOfFile(smd); //���L�������f�[�^�|�C���^�J��
	}
	//���L�������A�N�Z�X�֐�
	bool Open(LPCTSTR MapName) {
		if (MapName == nullptr) { //�������Ȃ���΃G���[
			return 1;
		}
		MapHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, MapName); //�t�@�C��������}�b�v�n���h���擾
		if (MapHandle == NULL) { //�}�b�v�����݂��Ă��Ȃ���΃G���[
			return 1;
		}
		smd = (ShareMemData *)MapViewOfFile(MapHandle, FILE_MAP_ALL_ACCESS, 0, 0, ShareMemSize); //�}�b�v���e����
		if (smd == NULL) { //�}�b�v���e�擾���ł��Ă��Ȃ���΃G���[
			return 1;
		}
		return 0;
	}
};