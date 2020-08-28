#ifndef DIRECTX_H
#define DIRECTX_H

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <d3dx9tex.h>
#include <unordered_map>
#include <tchar.h>

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

namespace DX {

	using namespace std;

	class DirectX {

	private:
		/*
		*@brief カスタムバーテックス
		*/
		struct CUSTOMVERTEX {
			//! 座標と除算数
			FLOAT x, y, z, rhw;
			//! 色情報
			DWORD color;
			//! テクスチャのUV座標
			FLOAT tu, tv;
		};

		//! キー情報の最大値
		static const INT MAX_KEY = 256;

		//! マスク値
		const INT MASK_NUM = 0x80;

		/*
		*@brief D3Deviceの初期化
		*@param hWnd ウィンドウハンドル
		*@return 成功したかどうか
		*/
		HRESULT InitD3Device(HWND hWnd);

		/*
		*@brief Dinputの初期化
		*@param hWnd ウィンドウハンドル
		*@return 成功したかどうか
		*/
		HRESULT InitDinput(HWND hWnd);

		VOID SetRenderState();

		VOID SetTextureStage();

		VOID SetSampler();

		/*
		*@brief PresentParametersの初期化
		*@param hWnd ウィンドウハンドル
		*/
		VOID InitPresentParameters(HWND hWnd);

		/*
		*@brief テクスチャの初期化
		*/
		VOID AllTextureRelease();

		/*
		*@brief フォントの初期化
		*/
		VOID AllFontRelease();

		/*
		*@brief 回転
		*@param [in] 回転前の頂点情報
		*@param [out] 回転後の頂点情報
		*@param [in] 回転角度(初期値が0)
		*/
		VOID Rotate(CUSTOMVERTEX original[], CUSTOMVERTEX ret[], FLOAT degree);

		/*
		*@brief 拡大・縮小
		*@param [in] 元の頂点情報のx座標
		*@param [in] 元の頂点情報のy座標
		*@param [in] 元の頂点情報の横幅
		*@param [in] 元の頂点情報の高さ
		*@param [in] 座標がセンターかどうか
		*@param [out] 拡縮後の頂点情報
		*/
		VOID Scaling(FLOAT x, FLOAT y, FLOAT dw, FLOAT dh, BOOL is_Center, CUSTOMVERTEX result[]);

		/*
		*@brief オブジェクトの生成
		*@param テクスチャ情報の名前
		*@param 頂点情報
		*@param 回転角度
		*/
		VOID DrawObject(std::string TextureName, CUSTOMVERTEX customvertex[], FLOAT degree);

		/*
		*@brief 頂点情報の設定
		*@param 左上のx座標
		*@param 左上のy座標
		*@param 横幅
		*@param 高さ
		*@param 拡大率
		*@param 反転するかどうか(trueで反転、falseで通常)
		*@param 座標がセンターかどうか
		*@param テクスチャUVの左上のx座標
		*@param テクスチャUVの左上のy座標
		*@param テクスチャUVの横幅
		*@param テクスチャUVの高さ
		*/
		CUSTOMVERTEX* SetVertex(FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT zoom, BOOL is_Reverse, BOOL is_Center, FLOAT tu, FLOAT tv, FLOAT tw, FLOAT th);

		/*
		*@brief 頂点情報の生成
		*@param 横幅
		*@param 高さ
		*@param テクスチャUVの左上のx座標
		*@param テクスチャUVの左上のy座標
		*@param テクスチャUVの横幅
		*@param テクスチャUVの高さ
		*@param 反転するかどうか(trueで反転、falseで通常)
		*/
		VOID MakeVertex(CUSTOMVERTEX customvertex[],FLOAT width,FLOAT height,FLOAT tu,FLOAT tv,FLOAT tw, FLOAT th, BOOL is_Reverse);

	public:

		//! Direct3Dのインターフェイス
		LPDIRECT3D9 pDirect3D;

		//! Direct3Dのデバイス
		IDirect3DDevice9* pD3Device;

		//! ウィンドウの設定
		D3DPRESENT_PARAMETERS D3dPresentParameters;

		//! DirectInputのキーボードデバイス
		LPDIRECTINPUTDEVICE8 pDxIKeyDevice;

		//! DirectInputのインターフェイス
		LPDIRECTINPUT8 pDinput;

		//! テクスチャ
		std::unordered_map<std::string, LPDIRECT3DTEXTURE9> pTexture;

		//! フォント
		std::unordered_map<std::string, LPD3DXFONT> pFont;

		//! キーの状態
		enum KEY_STATE {
			PUSH,
			RELEASE,
			ON,
			OFF
		};

		//! キーの保存変数
		KEY_STATE KeyState[256];

		/*
		*@brief Constractor
		*/
		DirectX();

		/*
		*@brief Destractor
		*/
		~DirectX();

		/*
		*@brief DirectXの初期化
		*@param hWnd ウィンドウハンドル
		*/
		HRESULT InitDirectX(HWND hWnd);

		/*
		*@brief キーの状態の更新
		*/
		VOID UpdateKeyState();

		/*
		*@brief キーの状態の取得
		*@param キーの情報
		*/
		KEY_STATE GetKeyState(INT diks);

		/*
		*@brief 全て解放する
		*/
		VOID AllRelease();

		/*
		*@brief 一つのテクスチャを解放する
		*@param テクスチャ名
		*/
		VOID ReleaseTexture(std::string TextureName);

		/*
		*@brief テクスチャの読み込み
		*@param [in] ファイルの名前(char)
		*@param [out] pTextureに入る配列の名前(char)
		*/
		VOID LoadTexture(const CHAR* FileName, std::string TextureName);

		/*
		*@brief 描画する
		*@param x座標
		*@param y座標
		*@param 横幅
		*@param 高さ
		*@param 角度
		*@param 拡縮
		*@param 反転
		*@param テクスチャ情報の名前
		*/
		VOID Draw(FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT degree, FLOAT zoom, BOOL is_Reverse, std::string TextureName);

		/*
		*@brief 描画する(座標は中央)
		*@param x座標
		*@param y座標
		*@param 横幅
		*@param 高さ
		*@param 角度
		*@param 拡縮
		*@param 反転
		*@param テクスチャ情報の名前
		*/
		VOID DrawCenter(FLOAT CenterX, FLOAT CenterY, FLOAT width, FLOAT height, FLOAT degree, FLOAT zoom, BOOL is_Reverse, std::string TextureName);

		/*
		*@brief 描画する(EX)
		*@param x座標
		*@param y座標
		*@param z座標
		*@param 横幅
		*@param 高さ
		*@param 角度
		*@param 拡縮
		*@param 反転
		*@param pTextureに保存されているテクスチャ情報の名前
		*@param テクスチャの左上のx座標
		*@param テクスチャの左上のy座標
		*@param テクスチャの横幅
		*@param テクスチャの高さ
		*@param 除算数
		*@param 色
		*/
		VOID DrawEx(
			FLOAT x,
			FLOAT y,
			FLOAT z,
			FLOAT width,
			FLOAT height,
			FLOAT degree,
			FLOAT zoom,
			BOOL is_Reverse,
			std::string TextureName,
			FLOAT tu,
			FLOAT tv,
			FLOAT tu_width,
			FLOAT tv_height,
			FLOAT rhw = 0.0f,
			DWORD color = 0xFFFFFFFF);

		/*
		*@brief 描画する(EX)
		*@param x座標
		*@param y座標
		*@param z座標
		*@param 横幅
		*@param 高さ
		*@param 角度
		*@param 拡縮
		*@param 反転
		*@param pTextureに保存されているテクスチャ情報の名前
		*@param テクスチャの左上のx座標
		*@param テクスチャの左上のy座標
		*@param テクスチャの横幅
		*@param テクスチャの高さ
		*@param 除算数
		*@param 色
		*/
		VOID DrawCenterEx(
			FLOAT CenterX,
			FLOAT CenterY,
			FLOAT z,
			FLOAT width,
			FLOAT height,
			FLOAT degree,
			FLOAT zoom,
			BOOL is_Revese,
			std::string TextureName,
			FLOAT tu,
			FLOAT tv,
			FLOAT tu_width,
			FLOAT tv_height,
			FLOAT rhw = 0.0f,
			DWORD color = 0xFFFFFFFF);
	};
}

#endif
