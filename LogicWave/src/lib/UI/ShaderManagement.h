#pragma once

#include "define.h"

#include <string.h>
#include <iostream>
#include <fstream>
#include <memory>

//シェーダ管理クラス
class ShaderManagement {
private:
	//デフォルトバーテックスシェーダのID
	GLuint NormalVertexShaderID;
	//デフォルトフラグメントシェーダのID
	GLuint NormalFragmentShaderID;
	//リソースファイルの読み込み
	void *GetResource(std::string Path);
	//バーテックスシェーダ読み込み
	GLuint LoadVertexShader(std::string VertexFilePath);
	//フラグメントシェーダ読み込み
	GLuint LoadFragmentShader(std::string FragmentFilePath);
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
	GLuint Load(std::string VertexFilePath, std::string FragmentFilePath);

	//シェーダ変更
	void Change(GLuint ID);
};