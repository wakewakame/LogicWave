#include "ShaderManagement.h"

void *ShaderManagement::GetResource(std::string FileName) {
	std::unique_ptr<wchar_t[]> FileName_{ new wchar_t[FileName.size() + 1] };

	LPtoLPCW(FileName.c_str(), FileName_.get());
	LoadResource(
		GetModuleHandle(NULL),
		FindResource(
			GetModuleHandle(NULL),
			FileName_.get(),
			RT_RCDATA
		)
	);
}

GLuint ShaderManagement::LoadVertexShader(std::string VertexFilePath) {
	//�o�[�e�b�N�X�V�F�[�_�t�@�C���̓ǂݍ���
	std::string VertexShaderCode;
	if (VertexFilePath != "") {
		std::ifstream VertexShaderStream(VertexFilePath, std::ios::in);
		//�V�F�[�_�t�@�C�������݂��邩�ǂ���
		if (VertexShaderStream.is_open()) {
			//�\�[�X�R�[�h������擾
			std::string Line = "";
			while (getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		else {
			std::cout << "Vertex Shader is not found." << std::endl;
			return NormalVertexShaderID;
		}
	}
	else {
		return NormalVertexShaderID;
	}
	//���ʂ̒l��ێ�����ϐ��錾
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//�o�[�e�b�N�X�V�F�[�_�R���p�C��
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER); //��o�[�e�b�N�X�V�F�[�_�̐���
	char const * VertexSourcePointer = VertexShaderCode.c_str();
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

GLuint ShaderManagement::LoadFragmentShader(std::string FragmentFilePath) {
	//�t���O�����g�V�F�[�_�t�@�C���̓ǂݍ���
	std::string FragmentShaderCode;
	if (FragmentFilePath != "") {
		std::ifstream FragmentShaderStream(FragmentFilePath, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			//�\�[�X�R�[�h������擾
			std::string Line = "";
			while (getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		else {
			std::cout << "Fragment Shader is not found." << std::endl;
			return NormalFragmentShaderID;
		}
	}
	else {
		return NormalFragmentShaderID;
	}
	//���ʂ̒l��ێ�����ϐ��錾
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//�t���O�����g�V�F�[�_�R���p�C��
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); //��t���O�����g�V�F�[�_�̐���
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
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
	NormalVertexShaderID = LoadVertexShader("default.vs");
	NormalFragmentShaderID = LoadFragmentShader("default.fs");
	NormalProgramID = Load("", "");
}

ShaderManagement::~ShaderManagement() {
	glDeleteShader(NormalVertexShaderID);
	glDeleteShader(NormalFragmentShaderID);
}

GLuint ShaderManagement::Load(std::string VertexFilePath, std::string FragmentFilePath) {
	//�o�[�e�b�N�X�V�F�[�_�ǂݍ���
	GLuint VertexShaderID = LoadVertexShader(VertexFilePath);
	//�t���O�����g�V�F�[�_�ǂݍ���
	GLuint FragmentShaderID = LoadFragmentShader(FragmentFilePath);

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