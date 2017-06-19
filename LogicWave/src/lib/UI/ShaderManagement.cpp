#include "ShaderManagement.h"

GLuint ShaderManagement::LoadVertexShader(std::string VertexScript) {
	//�o�[�e�b�N�X�V�F�[�_�t�@�C���̓ǂݍ���
	if (VertexScript == "") {
		return NormalVertexShaderID;
	}
	//���ʂ̒l��ێ�����ϐ��錾
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//�o�[�e�b�N�X�V�F�[�_�R���p�C��
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER); //��o�[�e�b�N�X�V�F�[�_�̐���
	char const * VertexSourcePointer = VertexScript.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);
	//�o�[�e�b�N�X�V�F�[�_������ɃR���p�C�����ꂽ���ǂ���
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << VertexShaderErrorMessage.data() << std::endl;
	}
	return VertexShaderID;
}

GLuint ShaderManagement::LoadFragmentShader(std::string FragmentScript) {
	//�t���O�����g�V�F�[�_�t�@�C���̓ǂݍ���
	if (FragmentScript == "") {
		return NormalFragmentShaderID;
	}
	//���ʂ̒l��ێ�����ϐ��錾
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//�t���O�����g�V�F�[�_�R���p�C��
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); //��t���O�����g�V�F�[�_�̐���
	char const * FragmentSourcePointer = FragmentScript.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);
	//�t���O�����g�V�F�[�_������ɃR���p�C�����ꂽ���ǂ���
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << FragmentShaderErrorMessage.data() << std::endl;
	}
	return FragmentShaderID;
}

ShaderManagement::ShaderManagement() {
	NormalVertexShaderID = GL_FALSE;
	NormalFragmentShaderID = GL_FALSE;
	NormalProgramID = GL_FALSE;
	NormalVertexShaderID = LoadVertexShader
(R"(
a
)");
	NormalFragmentShaderID = LoadFragmentShader
(R"(
a
)");
	NormalProgramID = Load("", "");
}

ShaderManagement::~ShaderManagement() {
	glDeleteShader(NormalVertexShaderID);
	glDeleteShader(NormalFragmentShaderID);
}

GLuint ShaderManagement::Load(std::string VertexScript, std::string FragmentScript) {
	if ((VertexScript == "") && (FragmentScript == "") && (NormalProgramID != GL_FALSE)) return NormalProgramID;

	//�o�[�e�b�N�X�V�F�[�_�ǂݍ���
	GLuint VertexShaderID = LoadVertexShader(VertexScript);
	//�t���O�����g�V�F�[�_�ǂݍ���
	GLuint FragmentShaderID = LoadFragmentShader(FragmentScript);

	//�V�F�[�_�̃����N
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	//���ʂ̒l��ێ�����ϐ��錾
	GLint Result = GL_FALSE;
	int InfoLogLength;

	//�G���[�m�F
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << ProgramErrorMessage.data() << std::endl;
	}

	//�V�F�[�_���o��
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	//�V�F�[�_���
	if (VertexShaderID != NormalVertexShaderID) glDeleteShader(VertexShaderID);
	if (FragmentShaderID != NormalFragmentShaderID) glDeleteShader(FragmentShaderID);

	return ProgramID;
}



void ShaderManagement::Change(GLuint programID) {
	glUseProgram(programID);
}