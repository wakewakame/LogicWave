#pragma once

#include "define.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

//�V�F�[�_�Ǘ��N���X
class ShaderManagement {
private:
	//�f�t�H���g�o�[�e�b�N�X�V�F�[�_��ID
	GLuint NormalVertexShaderID;
	//�f�t�H���g�t���O�����g�V�F�[�_��ID
	GLuint NormalFragmentShaderID;
	//�f�t�H���g�V�F�[�_��ID
	GLuint NormalProgramID;
	//�o�[�e�b�N�X�V�F�[�_�ǂݍ���
	GLuint LoadVertexShader(std::string VertexScript);
	//�t���O�����g�V�F�[�_�ǂݍ���
	GLuint LoadFragmentShader(std::string FragmentScript);
public:
	//�R���X�g���N�^
	ShaderManagement();

	//�f�X�g���N�^
	~ShaderManagement();

	//�V�F�[�_�ǂݍ���(�ǂ��炩������f�t�H���g�̃V�F�[�_�ɂ������ꍇ�͈�����""�w��)
	GLuint Load(std::string VertexScript, std::string FragmentScript);

	//�V�F�[�_�ύX
	void Change(GLuint ID);
};