#include "ShaderManagement.h"

std::string ShaderManagement::GetResource(std::string FileName) {
	std::unique_ptr<wchar_t[]> FileName_{ new wchar_t[FileName.size() + 1] };

	LPtoLPCW(FileName.c_str(), FileName_.get());
	HRSRC resInfo = FindResource(
		GetModuleHandle(NULL),
		FileName_.get(),
		RT_RCDATA
	);
	if (resInfo == NULL) return "";
	return std::string(
		(char*)LockResource(
			LoadResource(
				GetModuleHandle(NULL),
				resInfo
			)
		),
		SizeofResource(
			GetModuleHandle(NULL),
			resInfo
		)
	);
}

GLuint ShaderManagement::LoadVertexShader(std::string VertexFileName) {
	//バーテックスシェーダファイルの読み込み
	std::string VertexShaderCode;
	if (VertexFileName != "") {
		VertexShaderCode = GetResource(VertexFileName);
		std::cout << VertexShaderCode << std::endl;
		if(VertexShaderCode == "") {
			std::cout << "Vertex Shader is not found." << std::endl;
			return NormalVertexShaderID;
		}
	}
	else {
		return NormalVertexShaderID;
	}
	//結果の値を保持する変数宣言
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//バーテックスシェーダコンパイル
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER); //空バーテックスシェーダの生成
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);
	//バーテックスシェーダが正常にコンパイルされたかどうか
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << VertexShaderErrorMessage.data() << std::endl;
	}
	return VertexShaderID;
}

GLuint ShaderManagement::LoadFragmentShader(std::string FragmentFileName) {
	//フラグメントシェーダファイルの読み込み
	std::string FragmentShaderCode;
	std::cout << FragmentShaderCode << std::endl;
	if (FragmentFileName != "") {
		FragmentShaderCode = GetResource(FragmentFileName);
		if (FragmentShaderCode == "") {
			std::cout << "Fragment Shader is not found." << std::endl;
			return NormalFragmentShaderID;
		}
	}
	else {
		return NormalFragmentShaderID;
	}
	//結果の値を保持する変数宣言
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//フラグメントシェーダコンパイル
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); //空フラグメントシェーダの生成
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);
	//フラグメントシェーダが正常にコンパイルされたかどうか
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

GLuint ShaderManagement::Load(std::string VertexFileName, std::string FragmentFileName) {
	//バーテックスシェーダ読み込み
	GLuint VertexShaderID = LoadVertexShader(VertexFileName);
	//フラグメントシェーダ読み込み
	GLuint FragmentShaderID = LoadFragmentShader(FragmentFileName);

	//シェーダのリンク
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	//結果の値を保持する変数宣言
	GLint Result = GL_FALSE;
	int InfoLogLength;

	//エラー確認
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << ProgramErrorMessage.data() << std::endl;
	}

	//シェーダ取り出し
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	//シェーダ解放
	if (VertexShaderID != NormalVertexShaderID) glDeleteShader(VertexShaderID);
	if (FragmentShaderID != NormalFragmentShaderID) glDeleteShader(FragmentShaderID);

	return ProgramID;
}



void ShaderManagement::Change(GLuint programID) {
	glUseProgram(programID);
}