#include "Main.h"
#include "../source/Title/Title.h"
#include "../source/Infomation/Information.h"
#include "../source/Game/Game.h"
#include "../source/GameClear/GameClear.h"
#include "../source/GameOver/GameOver.h"

#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/DirectX.lib")
#else
#pragma comment (lib, "../x64/Release/DirectX.lib")
#endif

DirectX dx;
SCENE_BASE::SCENE g_scene = SCENE_BASE::SCENE::Title;

/*
*@brief メインループ
*@param MSGのポインタ変数
*/
VOID Mainloop(MSG*, TITLE*,INFORMATION*, GAME*, GAMECLEAR*, GAMEOVER*);

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdline, _In_ INT nCmdShow) {
	const TCHAR API_NAME[] = _T("PAC-MAN ボンバーランド");
	MSG msg;

	TITLE title;
	INFORMATION information;
	GAME game;
	GAMECLEAR gameclear;
	GAMEOVER gameover;

	HWND hWnd = GenerateWindow(&hInstance, API_NAME);

	dx.InitDirectX(hWnd);

	Mainloop(&msg, &title, &information, &game, &gameclear, &gameover);

	dx.AllRelease();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		
	case WM_SYSKEYDOWN:
		switch (wp){
		case VK_RETURN:
			return 0;
		case VK_F4:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		default:
			return 0;
		}
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

HWND GenerateWindow(HINSTANCE* hInstance, const TCHAR* API_NAME) {

	WNDCLASS Wndclass;
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = *hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDC_ICON);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = API_NAME;

	RegisterClass(&Wndclass);

	return CreateWindow(
		API_NAME,
		API_NAME,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0,
		0,
		window_width,
		window_height,
		NULL,
		NULL,
		*hInstance,
		NULL
	);
}

VOID Mainloop(MSG* msg,TITLE* title,INFORMATION* information, GAME* game,GAMECLEAR* gameclear, GAMEOVER* gameover) {
	DWORD Prev = timeGetTime();
	DWORD Curr;

	timeBeginPeriod(1);
	ZeroMemory(msg, sizeof(msg));
	while (msg->message != WM_QUIT){
		if (PeekMessage(msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(msg);
			DispatchMessage(msg);
		}
		else {
			Curr = timeGetTime();
			if (Curr - Prev >= 1000 / 60) {
				dx.pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0f, 0);
				dx.pD3Device->BeginScene();

				dx.UpdateKeyState();

				switch (g_scene)
				{
				case SCENE_BASE::SCENE::Title:title->UpdateScene();
					break;
				case SCENE_BASE::SCENE::Information:information->UpdateScene();
					break;
				case SCENE_BASE::SCENE::Game:game->UpdateScene();
					break;
				case SCENE_BASE::SCENE::GameClear:gameclear->UpdateScene();
					break;
				case SCENE_BASE::SCENE::GameOver:gameover->UpdateScene();
					break;
				default:MessageBox(0, "シーン設定がされていません", "", MB_OK);
					break;
				}

				dx.pD3Device->EndScene();
				dx.pD3Device->Present(NULL, NULL, NULL, NULL);
				Prev = Curr;
			}
		}
		Sleep(1);
	}
	timeEndPeriod(1);
}
