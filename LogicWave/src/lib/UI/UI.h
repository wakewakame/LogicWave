#pragma once

#include "define.h"
#include "Frame.h"
#include "Animation.h"
#include "FBO.h"
#include "GraphPara.h"

//�O���t�`��N���X
class Graph : public Frame {
private:
	void main_draw();
	std::vector<int> wave;
	void glColor(double R, double G, double B, double A = 255.0) {
		glColor4d(R / 255.0, G / 255.0, B / 255.0, A / 255.0);
	}
public:
	Graph(Frame *set_parent = nullptr) : Frame(set_parent) {

	}
	//�g�`���ƕ`��͈�
	graph grp;
	//�g�`��h��Ԃ����ǂ���
	bool fill_wave;
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