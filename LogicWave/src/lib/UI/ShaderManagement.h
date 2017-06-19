#pragma once

#include "define.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

//シェーダ管理クラス
class ShaderManagement {
private:
	//デフォルトバーテックスシェーダのID
	GLuint NormalVertexShaderID;
	//デフォルトフラグメントシェーダのID
	GLuint NormalFragmentShaderID;
	//デフォルトシェーダのID
	GLuint NormalProgramID;
	//バーテックスシェーダ読み込み
	GLuint LoadVertexShader(std::string VertexScript);
	//フラグメントシェーダ読み込み
	GLuint LoadFragmentShader(std::string FragmentScript);
public:
	//コンストラクタ
	ShaderManagement();

	//デストラクタ
	~ShaderManagement();

	//シェーダ読み込み(どちらか一方をデフォルトのシェーダにしたい場合は引数に""指定)
	GLuint Load(std::string VertexScript, std::string FragmentScript);

	//シェーダ変更
	void Change(GLuint ID);
};