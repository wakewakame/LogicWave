#pragma once

#include "define.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <memory>

//�V�F�[�_�Ǘ��N���X
class ShaderManagement {
private:
	//�f�t�H���g�o�[�e�b�N�X�V�F�[�_��ID
	GLuint NormalVertexShaderID;
	//�f�t�H���g�t���O�����g�V�F�[�_��ID
	GLuint NormalFragmentShaderID;
	//���\�[�X�t�@�C���̓ǂݍ���
	void *GetResource(std::string Path);
	//�o�[�e�b�N�X�V�F�[�_�ǂݍ���
	GLuint LoadVertexShader(std::string VertexFilePath);
	//�t���O�����g�V�F�[�_�ǂݍ���
	GLuint LoadFragmentShader(std::string FragmentFilePath);
	//LPSTR->LPCTSTR(=LPCWSTR)�֐�
	void LPtoLPCW(LPCSTR str, wchar_t *wlocal) {
		MultiByteToWideChar(
			CP_ACP,
			MB_PRECOMPOSED,
			str,
			strlen(str),
			wlocal,
			strlen(str) + 1
		);
	}
public:
	//�f�t�H���g�V�F�[�_��ID
	GLuint NormalProgramID;

	//�R���X�g���N�^
	ShaderManagement();

	//�f�X�g���N�^
	~ShaderManagement();

	//�V�F�[�_�ǂݍ���(�ǂ��炩������f�t�H���g�̃V�F�[�_�ɂ������ꍇ�͈�����""�w��)
	GLuint Load(std::string VertexFilePath, std::string FragmentFilePath);

	//�V�F�[�_�ύX
	void Change(GLuint ID);
};