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
	//バーテックスシェーダファイルの読み込み
	std::string VertexShaderCode;
	if (VertexFilePath != "") {
		std::ifstream VertexShaderStream(VertexFilePath, std::ios::in);
		//シェーダファイルが存在するかどうか
		if (VertexShaderStream.is_open()) {
			//ソースコード文字列取得
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

GLuint ShaderManagement::LoadFragmentShader(std::string FragmentFilePath) {
	//フラグメントシェーダファイルの読み込み
	std::string FragmentShaderCode;
	if (FragmentFilePath != "") {
		std::ifstream FragmentShaderStream(FragmentFilePath, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			//ソースコード文字列取得
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

GLuint ShaderManagement::Load(std::string VertexFilePath, std::string FragmentFilePath) {
	//バーテックスシェーダ読み込み
	GLuint VertexShaderID = LoadVertexShader(VertexFilePath);
	//フラグメントシェーダ読み込み
	GLuint FragmentShaderID = LoadFragmentShader(FragmentFilePath);

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