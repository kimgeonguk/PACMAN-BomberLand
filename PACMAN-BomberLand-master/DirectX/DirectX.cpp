#include "DirectX.h"

#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"dinput8.lib")

namespace DX {

	DirectX::DirectX() {

	}

	DirectX::~DirectX() {
		AllRelease();
	}

	HRESULT DirectX::InitDirectX(HWND hWnd)
	{
		if (FAILED(InitD3Device(hWnd))) {
			return E_FAIL;
		}

		if (FAILED(InitDinput(hWnd))) {
			return E_FAIL;
		}

		pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

		if (pDirect3D == NULL) {
			MessageBox(0, _T("Direct3Dの作成に失敗しました"), NULL, MB_OK);
			return E_FAIL;
		}

		SetRenderState();
		SetTextureStage();
		SetSampler();

		pD3Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1);

		return S_OK;
	}

	VOID DirectX::SetSampler() {
		pD3Device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_MIRROR);
	}

	VOID DirectX::SetRenderState() {
		pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	}

	VOID DirectX::SetTextureStage() {
		pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}

	HRESULT DirectX::InitD3Device(HWND hWnd) {
		if (NULL == (pDirect3D = Direct3DCreate9(D3D_SDK_VERSION))) {
			MessageBox(0, _T("Direct3Dの作成に失敗しました"), _T(""), MB_OK);
			return E_FAIL;
		}

		InitPresentParameters(hWnd);

		if (FAILED(pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING,
			&D3dPresentParameters, &pD3Device))) {

			MessageBox(0, _T("HALモードでDIRECT3Dデバイスの作成に失敗しました。\nREFモードで再試行します。"), NULL, MB_OK);
			if (FAILED(pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_MIXED_VERTEXPROCESSING,
				&D3dPresentParameters, &pD3Device))) {
				MessageBox(0, _T("REFモードでDIRECT3Dデバイスの作成に失敗しました。"), NULL, MB_OK);
				return E_FAIL;
			}
		}
		return S_OK;
	}

	HRESULT DirectX::InitDinput(HWND hWnd)
	{
		HRESULT hr;

		if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID * *)& pDinput, NULL)))
		{
			MessageBox(0, _T("DirectInputの作成に失敗しました"), NULL, MB_OK);
			return hr;
		}

		if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard, &pDxIKeyDevice, NULL)))
		{
			MessageBox(0, _T("DirectInputの作成に失敗しました"), NULL, MB_OK);
			return hr;
		}

		if (FAILED(hr = pDxIKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
		{
			MessageBox(0, _T("キーデバイスのフォーマットの設定に失敗しました。"), NULL, MB_OK);
			return hr;
		}

		if (FAILED(hr = pDxIKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		{
			MessageBox(0, _T("キーデバイスの協調レベルの設定に失敗しました。"), NULL, MB_OK);
			return hr;
		}

		pDxIKeyDevice->Acquire();
		return S_OK;
	}

	VOID DirectX::InitPresentParameters(HWND hWnd)
	{
		ZeroMemory(&D3dPresentParameters, sizeof(D3dPresentParameters));

		D3dPresentParameters.BackBufferWidth = 0;
		D3dPresentParameters.BackBufferHeight = 0;
		D3dPresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
		D3dPresentParameters.BackBufferCount = 1;
		D3dPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
		D3dPresentParameters.MultiSampleQuality = 0;
		D3dPresentParameters.hDeviceWindow = hWnd;
		D3dPresentParameters.EnableAutoDepthStencil = FALSE;
		D3dPresentParameters.AutoDepthStencilFormat = D3DFMT_A1R5G5B5;
		D3dPresentParameters.Flags = 0;
		D3dPresentParameters.FullScreen_RefreshRateInHz = 0;
		D3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		D3dPresentParameters.Windowed = TRUE;
	}

	VOID DirectX::UpdateKeyState() {

		BYTE curr_diks[MAX_KEY];

		static BYTE prev_diks[MAX_KEY] = { OFF };

		HRESULT hr = pDxIKeyDevice->Acquire();

		if ((hr == DI_OK) || (hr == S_FALSE)) {
			pDxIKeyDevice->GetDeviceState(sizeof(curr_diks), &curr_diks);
			for (int i = 0; i < MAX_KEY; i++) {
				if (curr_diks[i] & MASK_NUM) {
					if (prev_diks[i] == OFF) {
						KeyState[i] = PUSH;
					}
					else {
						KeyState[i] = ON;
					}

					prev_diks[i] = ON;
				}
				else {
					if (prev_diks[i] == ON) {
						KeyState[i] = RELEASE;
					}
					else {
						KeyState[i] = OFF;
					}
					prev_diks[i] = OFF;
				}

			}
		}
	}

	DirectX::KEY_STATE DirectX::GetKeyState(INT diks) {
		return KeyState[diks];
	}

	VOID DirectX::AllRelease() {
		AllTextureRelease();
		AllFontRelease();
		if (pDxIKeyDevice)
		{
			pDxIKeyDevice->Unacquire();
		}
		if (pDxIKeyDevice != nullptr) {
			pDxIKeyDevice->Release();
			pDxIKeyDevice = nullptr;
		}
		if (pDinput != nullptr) {
			pDinput->Release();
			pDinput = nullptr;
		}
		if (pD3Device != nullptr) {
			pD3Device->Release();
			pD3Device = nullptr;
		}
		if (pDirect3D != nullptr) {
			pDirect3D->Release();
			pDirect3D = nullptr;
		}
	}

	VOID DirectX::ReleaseTexture(std::string TextureName) {
		if (pTexture[TextureName] != nullptr) {
			pTexture[TextureName]->Release();
		}
	}

	VOID DirectX::AllTextureRelease() {
		if (!pTexture.size()) {
			return;
		}
		for (auto i : pTexture) {
			if (!i.second) {
				continue;
			}
			(i.second)->Release();
		}
		pTexture.clear();
		std::unordered_map<std::string, LPDIRECT3DTEXTURE9>().swap(pTexture);
	}

	VOID DirectX::AllFontRelease() {
		if (!pFont.size()) {
			return;
		}
		for (auto i : pFont) {
			if (!i.second) {
				continue;
			}
			(i.second)->Release();
		}
		pFont.clear();
		std::unordered_map<std::string, LPD3DXFONT>().swap(pFont);
	}

	VOID DirectX::LoadTexture(const CHAR* FilePath, std::string TextureName) {
		D3DXCreateTextureFromFile
		(pD3Device,
			FilePath,
			&pTexture[TextureName]);
	}

	VOID DirectX::Draw(FLOAT x, FLOAT y, FLOAT width, FLOAT height,FLOAT degree,FLOAT zoom, BOOL is_Reverse, std::string TextureName) {
		DrawObject(TextureName, SetVertex(x, y, width, height, zoom, is_Reverse, false, 0.0f, 0.0f, 1.0f, 1.0f), degree);
	}

	VOID DirectX::DrawEx(FLOAT x,
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
		FLOAT rhw,
		DWORD color){
		DrawObject(TextureName, SetVertex(x, y, width, height, zoom, is_Reverse, false, tu, tv, tu_width, tv_height), degree);
	}

	VOID DirectX::DrawCenter(FLOAT CenterX, FLOAT CenterY, FLOAT width, FLOAT height, FLOAT degree, FLOAT zoom, BOOL is_Reverse, std::string TextureName) {
		FLOAT TopLeftX = CenterX - width / 2;
		FLOAT TopLeftY = CenterY - height / 2;

		DrawObject(TextureName, SetVertex(TopLeftX, TopLeftY, width, height, zoom, is_Reverse, true, 0.0f, 0.0f, 1.0f, 1.0f), degree);
	}

	VOID DirectX::DrawCenterEx(
		FLOAT CenterX,
		FLOAT CenterY,
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
		FLOAT rhw,
		DWORD color){
		FLOAT TopLeftX = CenterX - width / 2;
		FLOAT TopLeftY = CenterY - height / 2;
		DrawObject(TextureName, SetVertex(TopLeftX, TopLeftY, width, height, zoom, is_Reverse, true, tu, tv, tu_width, tv_height), degree);
	}

	VOID DirectX::DrawObject(std::string TextureName, CUSTOMVERTEX customvertex[], FLOAT degree) {
		CUSTOMVERTEX vertex[4];
		Rotate(customvertex,vertex,degree);

		pD3Device->SetTexture(0, pTexture[TextureName]);
		pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(CUSTOMVERTEX));
	}

	VOID DirectX::Rotate(CUSTOMVERTEX original[],CUSTOMVERTEX ret[], FLOAT degree = 0.0f) {
		FLOAT centerX = (original[0].x + original[1].x) / 2.0f;
		FLOAT centerY = (original[0].y + original[3].y) / 2.0f;
		DOUBLE radian = (DOUBLE)(degree * D3DX_PI / 180.0f);

		for (int i = 0; i < 4; i++) {
			original[i].x -= centerX;
			original[i].y -= centerY;

			ret[i] = original[i];

			ret[i].x = (FLOAT)(original[i].x * cos(radian) - original[i].y * sin(radian));
			ret[i].y = (FLOAT)(original[i].x * sin(radian) + original[i].y * cos(radian));

			original[i].x += centerX;
			original[i].y += centerY;

			ret[i].x += centerX;
			ret[i].y += centerY;
			ret[i].z = 0.0f;
		}
	}

	VOID DirectX::Scaling(FLOAT x, FLOAT y, FLOAT dw, FLOAT dh,BOOL is_Center, CUSTOMVERTEX result[]) {
		if (is_Center) {
			FLOAT CenterX = x + dw / 2;
			FLOAT CenterY = y + dh / 2;
			result[0].x = CenterX - dw / 2;
			result[1].x = CenterX + dw / 2;
			result[2].x = CenterX + dw / 2;
			result[3].x = CenterX - dw / 2;
			result[0].y = CenterY - dh / 2;
			result[1].y = CenterY - dh / 2;
			result[2].y = CenterY + dh / 2;
			result[3].y = CenterY + dh / 2;
		}
		else {
			result[0].x = x;
			result[1].x = x + dw;
			result[2].x = x + dw;
			result[3].x = x;
			result[0].y = y;
			result[1].y = y;
			result[2].y = y + dh;
			result[3].y = y + dh;
		}
	}

	DirectX::CUSTOMVERTEX* DirectX::SetVertex(FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT zoom, BOOL is_Reverse, BOOL is_Center, FLOAT tu = 0.0f, FLOAT tv = 0.0f, FLOAT tw = 1.0f, FLOAT th = 1.0f) {
		static CUSTOMVERTEX customvertex[4];
		FLOAT zw, zh;
		MakeVertex(customvertex, width, height, tu, tv, tw, th, is_Reverse);
		zw = width;
		zh = height;
		zw *= zoom;
		zh *= zoom;

		Scaling(x, y, zw, zh, is_Center, customvertex);
		return customvertex;
	}

	VOID DirectX::MakeVertex(CUSTOMVERTEX customvertex[], FLOAT width, FLOAT height, FLOAT tu, FLOAT tv, FLOAT tw, FLOAT th, BOOL is_Reverse) {
		customvertex[0].x = 0.0f;
		customvertex[3].x = 0.0f;
		customvertex[1].x = width;
		customvertex[2].x = width;
		customvertex[0].y = 0.0f;
		customvertex[1].y = 0.0f;
		customvertex[2].y = height;
		customvertex[3].y = height;

		for (int i = 0; i < 4; i++) {
			customvertex[i].z = 0.0f;
			customvertex[i].rhw = 1.0f;
			customvertex[i].color = 0xFFFFFFFF;
		}

		customvertex[0].tu = is_Reverse ? tu + tw : tu;
		customvertex[1].tu = is_Reverse ? tu : tu + tw;
		customvertex[2].tu = is_Reverse ? tu : tu + tw;
		customvertex[3].tu = is_Reverse ? tu + tw : tu;
		customvertex[0].tv = tv;
		customvertex[1].tv = tv;
		customvertex[2].tv = tv + th;
		customvertex[3].tv = tv + th;
	}
}
