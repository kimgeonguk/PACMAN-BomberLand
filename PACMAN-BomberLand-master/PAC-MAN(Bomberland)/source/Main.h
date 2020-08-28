#ifndef MAIN_H_
#define MAIN_H_

#include <windows.h>
#include <tchar.h>

#include "../source/DirectX/DirectX.h"
#include "../source/Scene.h"

using DX::DirectX;

extern DirectX dx;

//!ウィンドウの横幅
const INT window_width = 1920;

//!ウィンドウの縦幅
const INT window_height = 1080;

extern SCENE_BASE::SCENE g_scene;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

/*
*@brief ウィンドウ生成
*@param ハンドルインスタンスのポインタ変数
*@param アプリケーションの名前
*@return ウィンドウハンドル
*/
HWND GenerateWindow(HINSTANCE* hInstance,const TCHAR* API_NAME);

#endif //MAIN_H_
