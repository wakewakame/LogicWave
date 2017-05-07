#pragma once

#include "define.h"
#include "win_info.h"

//�t���[�����N���X
class Frame {
protected:
//�Ǘ��n�֐�
	//�S�ϐ�������
	void reset();
	//�q�t���[�����玩�t���[����length��lock_length���Z�o(�q�t���[�����ǉ�����邽�т�root�t���[���̂��̊֐����Ă�)
	void get_length();
	//root�t���[���̃|�C���^�擾
	void get_root();
	//���t���[���̃C���f�b�N�X�ԍ��擾
	void get_index();
	//���t���[���̒��ɕ`�悷��֐�
	virtual void main_draw();
	//���t���[���ȉ��̑S�q�t���[����draw�֐����s
	void childs_draw();
	//�t���[���ǉ������s�֐�
	virtual void when_create();

public:
	//�ϐ�
	Frame *root; //root�t���[���̃|�C���^
	Frame *parent; //�e�t���[���̃|�C���^
	std::vector<Frame*> childs; //�S�q�t���[���̃|�C���^�z��
	int index;//���t���[�����̎��t���[���̊����ԍ�(=0,1,2,3,...)
	WindowRect pos; //�t���[�����W
	WindowPoint size; //�t���[���T�C�Y(���[�t���[���̂ݑ��)
	std::string name; //�t���[���̖���
	std::string description; //�t���[������UI�̉��
	bool mode; //�q�t���[�����c����=0,������=1
	double gap; //�q�t���[���ԓ��m�̌���(px�P��)
	WindowPoint length; //�S�t���[���������l�T�C�Y���̎��t���[���̃T�C�Y
	bool lock; //�e�q�t���[���̒���(mode=0�Ȃ�c��,mode=1�Ȃ牡��)�̌Œ�on/off
	WindowPoint lock_length; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
	WINDOW_INFO *win;

	//�֐��錾
	//WINDOW_INFO�|�C���^���
	void set_win_info(WINDOW_INFO *set_win);
	//���t���[���ȉ��̑S�t���[���`��
	void draw();
	//���t���[���̃T�C�Y�ɍ��킹�Ďq�t���[���T�C�Y�X�V
	void resize(WindowRect set_pos = { -1.0, -1.0, -1.0, -1.0 });
	//root�t���[���ȉ��̃t���[���z�u�̐���(�t���[����ǉ����I�������K�����s)
	void orderliness();
	//�q�t���[���ǉ�(�g����:Frame *x = Frame::add<type>();)
	template <class T> T *add(){
		return new T(this);
	}
	//�R���X�g���N�^
	Frame(Frame *set_parent = nullptr);
	//�f�X�g���N�^
	~Frame();
};