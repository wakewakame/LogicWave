#pragma once
#include "define.h"

//�����_�[�o�b�t�@�ƃt���[���o�b�t�@�ێ��\����
struct Buffer {
	GLuint color; //�J���[FBO
	GLuint alpha; //�A���t�@FBO
	GLuint color_render; //�J���[�e�N�X�`��
	GLuint alpha_render; //�A���t�@�e�N�X�`��
	WindowPoint size; //�o�b�t�@�Ǝ�
};

//�t���[���o�b�t�@�N���X
class FBO {
private:
	//�ϐ�������
	//�o�b�t�@�̔z��
	std::vector<Buffer> buffer;
	//���ݎg�p���Ă���o�b�t�@�̃C���f�b�N�X(-1�Ȃ烌���_�[�o�b�t�@)
	int now_index;
	//�t���[���o�b�t�@����
	void createFBO(GLuint *FBO, GLuint *Tex, WindowPoint size);
	//�A���t�@�o�b�t�@���J���[�o�b�t�@�ɓK��
	void set_alpha();

public:
	//�R���X�g���N�^
	FBO();
	//�f�X�g���N�^
	~FBO();
	//�t���[���o�b�t�@�̒ǉ�
	int add(WindowPoint size);
	//�J���[�t���[���o�b�t�@�̐؂�ւ�
	void change_c(int index);
	//�A���t�@�t���[���o�b�t�@�̐؂�ւ�
	void change_a(int index);
	//�X�N���[���ɐؑ�
	void change_r();
	//�w��J���[�o�b�t�@�`��
	void draw(int index, WindowPoint pos, WindowPoint size = {-1.0,-1.0});
	//�t���[���T�C�Y�擾�֐�
	WindowPoint get_size(int index);
};