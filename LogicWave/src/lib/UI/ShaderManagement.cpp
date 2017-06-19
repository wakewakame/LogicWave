#include "ShaderManagement.h"

GLuint ShaderManagement::LoadVertexShader(std::string VertexScript) {
	//バーテックスシェーダファイルの読み込み
	if (VertexScript == "") {
		return NormalVertexShaderID;
	}
	//結果の値を保持する変数宣言
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//バーテックスシェーダコンパイル
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER); //空バーテックスシェーダの生成
	char const * VertexSourcePointer = VertexScript.c_str();
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

GLuint ShaderManagement::LoadFragmentShader(std::string FragmentScript) {
	//フラグメントシェーダファイルの読み込み
	if (FragmentScript == "") {
		return NormalFragmentShaderID;
	}
	//結果の値を保持する変数宣言
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//フラグメントシェーダコンパイル
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); //空フラグメントシェーダの生成
	char const * FragmentSourcePointer = FragmentScript.c_str();
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

	//バーテックスシェーダ読み込み
	GLuint VertexShaderID = LoadVertexShader(VertexScript);
	//フラグメントシェーダ読み込み
	GLuint FragmentShaderID = LoadFragmentShader(FragmentScript);

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