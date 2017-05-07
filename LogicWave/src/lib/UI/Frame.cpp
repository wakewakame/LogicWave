#include "Frame.h"

void Frame::reset() {
	//�ϐ��̏�����
	root = nullptr; //root�t���[���̃|�C���^
	parent = nullptr; //�e�t���[���̃|�C���^
	childs = {};
	index = 0;//���t���[�����̎��t���[���̊����ԍ�(=0,1,2,3,...)
	pos = { 0.0,0.0,0.0,0.0 }; //�t���[�����W
	size = { 0.0, 0.0 }; //�t���[���T�C�Y(���[�t���[���̂ݑ��)
	name = ""; //�t���[���̖���
	description = ""; //�t���[������UI�̉��
	mode = 0; //�q�t���[�����c����=0,������=1
	gap = 3.0; //�q�t���[���ԓ��m�̌���(px�P��)
	length = { 100.0, 100.0 }; //�S�t���[���������l�T�C�Y���̎��t���[���̃T�C�Y
	lock = 0; //�e�q�t���[���̒���(mode=0�Ȃ�c��,mode=1�Ȃ牡��)�̌Œ�on/off
	lock_length = { 0.0, 0.0 }; //�Œ�T�C�Y�̑S�q�t���[���ƑSgap�̘a(���[�t���[����0����)
	return;
}

void Frame::main_draw() {
	///debug///
	//�t���[���̘g�̕`��
	glLineWidth(1.0f);
	glColor4d(1.0, 1.0, 1.0, 0.5);
	glDisable(GL_POLYGON_SMOOTH);
	glBegin(GL_LINE_LOOP);
	glVertex2d(pos.left, pos.top);
	glVertex2d(pos.left, pos.bottom);
	glVertex2d(pos.right, pos.bottom);
	glVertex2d(pos.right, pos.top);
	glEnd();
	///debug///
	return;
}

void Frame::childs_draw() {
	for (int i = 0; i < childs.size(); i++) {
		childs[i]->draw();
	}
	return;
}

void Frame::when_create() {
	//�e�t���[�������݂�����
	if (parent != nullptr) {
		//�e�t���[���̎q�t���[���z��Ɏ��t���[���ǉ�
		parent->childs.push_back(this);
		//WINDOW_INFO��e�t���[���Ɠ���̂��̂ɂ���
		win = parent->win;
	}
	//���t���[���̃C���f�b�N�X�ԍ��擾
	get_index();
	//���t���[���̃c���[��root�t���[���擾
	get_root();
}

void Frame::set_win_info(WINDOW_INFO *set_win) {
	if ((root->win != set_win) && (this != root)) {
		root->set_win_info(set_win);
	}
	else {
		win = set_win;
		for (int i = 0; i < childs.size(); i++) {
			childs[i]->set_win_info(set_win);
		}
	}
}

void Frame::resize(WindowRect set_pos){
	if (
		set_pos.left >= 0.0 &&
		set_pos.top >= 0.0 &&
		set_pos.right >= 0.0 &&
		set_pos.bottom >= 0.0
	) {
		pos = set_pos;
	}
	size.x = pos.right - pos.left;
	size.y = pos.bottom - pos.top;
	if (childs.size() != 0) {
		if (mode) {
			//�����т̏ꍇ
			//�q�t���[�������[�v
			for (int i = 0; i < childs.size(); i++) {
				//i�ڂ̎q�t���[���ʒu�Z�o
				//�㉺�ʒu
				childs[i]->pos.top = pos.top + gap;
				childs[i]->pos.bottom = pos.bottom - gap;
				//���ʒu
				if (i == 0) {
					childs[i]->pos.left = pos.left + gap;
				}
				else {
					childs[i]->pos.left = childs[i - 1]->pos.right + gap;
				}
				//�E�ʒu
				if (childs[i]->lock) {
					//�Œ�T�C�Y�t���[��or�X�N���[���t���[���̏ꍇ�͊����ϊ��s�v
					childs[i]->pos.right =
						childs[i]->pos.left +
						childs[i]->length.x;
				}
				else {
					//��Œ�T�C�Y�t���[���̏ꍇ�͊����v�Z
					childs[i]->pos.right =
						childs[i]->pos.left +
						Utility::Proportion(
							childs[i]->length.x,
							0.0,
							length.x - lock_length.x,
							0.0,
							size.x - lock_length.x
						);
				}
				//�q�t���[���ʒu�ݒ�
				childs[i]->resize();
			}
		}
		else {
			//�c���т̏ꍇ
			//�q�t���[�������[�v
			for (int i = 0; i < childs.size(); i++) {
				//i�ڂ̎q�t���[���ʒu�Z�o
				//���E�ʒu
				childs[i]->pos.left = pos.left + gap;
				childs[i]->pos.right = pos.right - gap;
				//��ʒu
				if (i == 0) {
					childs[i]->pos.top = pos.top + gap;
				}
				else {
					childs[i]->pos.top = childs[i - 1]->pos.bottom + gap;
				}
				//���ʒu
				if (childs[i]->lock) {
					//�Œ�T�C�Y�t���[��or�X�N���[���t���[���̏ꍇ�͊����ϊ��s�v
					childs[i]->pos.bottom =
						childs[i]->pos.top +
						childs[i]->length.y;
				}
				else {
					//��Œ�T�C�Y�t���[���̏ꍇ�͊����v�Z
					childs[i]->pos.bottom =
						childs[i]->pos.top +
						Utility::Proportion(
							childs[i]->length.y,
							0.0,
							length.y - lock_length.y,
							0.0,
							size.y - lock_length.y
						);
				}
				//�q�t���[���ʒu�ݒ�
				childs[i]->resize();
			}
		}
	}
	return;
}

void Frame::orderliness() {
	//root�t���[���ȉ���length���ĎZ�o
	root->get_length();
	//root�t���[���ȉ��̃t���[���Ĕz�u
	root->resize(root->pos);
	return;
}

void Frame::draw() {
	main_draw();
	childs_draw();
	return;
}

void Frame::get_length() {
	if (mode) {
		length.x = 0.0;
		lock_length.x = 0.0;
		for (int i = 0; i < childs.size(); i++) {
			//�q�t���[�����q�t���[���������Ă����ꍇ�A�ċA
			if (childs[i]->childs.size() != 0) {
				childs[i]->get_length();
			}
			//�e�t���[���̒����Ɏq�t���[���̒����𑫂��Ă���
			length.x += childs[i]->length.x;
			//�����q�t���[�����Œ�T�C�Y�t���[���̏ꍇ
			if (childs[i]->lock) {
				lock_length.x += childs[i]->length.x;
			}
		}
		//�Sgap�𑫂�
		length.x += gap * (double)(childs.size() + 1);
		lock_length.x += gap * (double)(childs.size() + 1);
	}
	else {
		length.y = 0.0;
		lock_length.y = 0.0;
		for (int i = 0; i < childs.size(); i++) {
			//�q�t���[�����q�t���[���������Ă����ꍇ�A�ċA
			if (childs[i]->childs.size() != 0) {
				childs[i]->get_length();
			}
			//�e�t���[���̒����Ɏq�t���[���̒����𑫂��Ă���
			length.y += childs[i]->length.y;
			//�����q�t���[�����Œ�T�C�Y�t���[���̏ꍇ
			if (childs[i]->lock) {
				lock_length.y += childs[i]->length.y;
			}
		}
		//�Sgap�𑫂�
		length.y += gap * (double)(childs.size() + 1);
		lock_length.y += gap * (double)(childs.size() + 1);
	}
	return;
}

void Frame::get_root() {
	if (parent != nullptr) {
		parent->get_root();
		root = parent->root;
	}
	else {
		root = this;
	}
return;
}

void Frame::get_index() {
	if (parent != nullptr) {
		index = parent->childs.size() - 1;
	}
	else {
		index = 0;
	}
}

Frame::Frame(Frame *set_parent) {
	reset();
	parent = set_parent;
	when_create();
}

Frame::~Frame() {
	for (int i = 0; i < childs.size(); i++) {
		delete childs[i];
	}
}