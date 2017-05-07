#include "UI.h"

void Graph::main_draw() {
	//�`��������̂��߁A�s�N�Z���̐��ɍ��킹�ĕ`��
	int index = 0; //�z�񂩂�l���Q�Ƃ���Ƃ��̃C���f�b�N�X
	float percentage = 0.0f;
	float height; //���`�悷��g�̍���
	float zero = Utility::Proportion(0.0f, grp.val_min, grp.val_max, (float)(pos.bottom), (float)(pos.top)); //�O���ty���W��0�̂Ƃ��̃t���[��y���W
	if (wave.size() != size.x) {
		wave.resize(size.x);
	}
	//�g�`�̕`��ʒu�Z�o
	for (int i = 0; i < size.x; i++) {
		percentage = Utility::Proportion((float)i, 0.0f, (float)size.x, (float)grp.start_index, (float)grp.end_index); //�ꎞ���
		index = (int)percentage; //�g�`�z��̃C���f�b�N�X�Z�o
		percentage = percentage - (float)index; //int,float�̐�����K�����̐��ɂȂ�
		//(�O�̈�)index+1>=num_sample�ɂȂ����烋�[�v�E�o
		if (index + 1 >= grp.num_sample) {
			break;
		}
		//���`�悷��g�̍���
		height =
			Utility::Proportion(grp.samples[index], grp.val_min, grp.val_max, (float)(pos.bottom), (float)(pos.top)) * (1.0f - percentage) +
			Utility::Proportion(grp.samples[index + 1], grp.val_min, grp.val_max, (float)(pos.bottom), (float)(pos.top)) * (percentage);
		wave[i] = height;
	}
	//x���`��
	glLineWidth(1.0f);
	glColor(255, 255, 255, 128);
	glBegin(GL_LINES);
	glVertex2d(pos.left, zero);
	glVertex2d(pos.right, zero);
	glEnd();
	//�h��Ԃ�
	if (fill_wave) {
		glLineWidth(1.0f);
		glColor(0, 128, 198, 50);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < size.x; i++) {
			glVertex2d(pos.left + i, zero);
			glVertex2d(pos.left + i, wave[i]);
			glVertex2d(pos.left + i, zero);
		}
		glEnd();
	}
	//�g�`�`��
	glDisable(GL_POLYGON_SMOOTH);
	glLineWidth(1.5f);
	glColor(0, 128, 198, 255);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < size.x; i++) {
		glVertex2d(pos.left + i, wave[i]);
	}
	glEnd();
}