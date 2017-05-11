#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//�X�N���[���\�t���[���N���X
class Scroll : public Frame {
private:
	void event() {
		if (win->mouse.wheel != 0.0 || parent->mode?size.y:size.x != parent->mode?length.y:length.x) {
			//�X�N���[���ɍ��킹�ăt���[�����W�Z�o
			scroll -= 0.02*(double)(win->mouse.wheel);
			if (scroll < 0.0) scroll = 0.0;
			if (scroll > 1.0) scroll = 1.0;
			if (parent->mode) {
				pos.top = parent->pos.top + parent->gap - scroll*(length.y - (parent->size.y - parent->gap*2.0));
				pos.bottom = pos.top + length.y;
			}else{
				pos.left = parent->pos.left + parent->gap - scroll*(length.x - (parent->size.x - parent->gap*2.0));
				pos.right = pos.left + length.x;
			}
			resize(pos);
		}
	}
	void main_draw() {
		glColor4d(1.0, 1.0, 1.0, 0.5);
		glDisable(GL_POLYGON_SMOOTH);
		glBegin(GL_QUADS);
		glVertex2d(bar->pos.left, bar->pos.top);
		glVertex2d(bar->pos.left, bar->pos.bottom);
		glVertex2d(bar->pos.right, bar->pos.bottom);
		glVertex2d(bar->pos.right, bar->pos.top);
		glEnd();
	}

public:
	//�ϐ��錾
	//�X�N���[���p�[�Z���e�[�W
	double scroll;
	//�X�N���[���o�[
	Frame *bar;


	//�R���X�g���N�^
	//�X�N���[���t���[���͐e�t���[���K�{�̂��߁A�f�t�H���g�����Ȃ�
	Scroll(Frame *set_parent) : Frame(set_parent) {
		scroll = 0.0;
		bar = parent->add<Frame>();
		bar->length = {20.0,20.0};
		bar->lock = 1;
	}
};

//�O���t�`��N���X
class Graph : public Frame {
private:
	void main_draw();
	std::vector<int> wave;
public:
	//�ϐ��錾
	//�g�`���ƕ`��͈�
	graph grp;
	//�g�`��h��Ԃ����ǂ���
	bool fill_wave;

	//�R���X�g���N�^
	Graph(Frame *set_parent = nullptr) : Frame(set_parent) {
		fill_wave = 0;
	}
};

//�J�[�\���t���O���t�`��N���X
class CursorGraph : public Graph {
private:

public:
	CursorGraph(Frame *set_parent = nullptr) : Graph(set_parent) {

	}
};

//�t�F�[�h�O���t�`��N���X
class Fade : public Frame {
public:
	Fade(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};


//�{�^���`��N���X
class Button : public Frame {
public:
	Button(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};

//�{�����[���`��N���X
class Volume : public Frame {
public:
	Volume(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};

//���I��`��N���X
class Figure : public Frame {
public:
	Figure(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};

//�g�`�̌`�I��`��N���X
class WaveForm : public Frame {
public:
	WaveForm(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
};