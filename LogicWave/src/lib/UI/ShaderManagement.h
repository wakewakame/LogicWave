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
	//リソースファイルの読み込み
	std::string GetResource(std::string FileName);
	//バーテックスシェーダ読み込み
	GLuint LoadVertexShader(std::string VertexFileName);
	//フラグメントシェーダ読み込み
	GLuint LoadFragmentShader(std::string FragmentFileName);
	//LPSTR->LPCTSTR(=LPCWSTR)関数
	void LPtoLPCW(LPCSTR str, wchar_t *wlocal) {
		MultiByteToWideChar(
			CP_ACP,
			MB_PRECOMPOSED,
			str,
			strlen(str),
			wlocal,
			strlen(str) + 1
		);
	}
public:
	//デフォルトシェーダのID
	GLuint NormalProgramID;

	//コンストラクタ
	ShaderManagement();

	//デストラクタ
	~ShaderManagement();

	//シェーダ読み込み(どちらか一方をデフォルトのシェーダにしたい場合は引数に""指定)
	GLuint Load(std::string VertexFileName, std::string FragmentFileName);

	//シェーダ変更
	void Change(GLuint ID);
};