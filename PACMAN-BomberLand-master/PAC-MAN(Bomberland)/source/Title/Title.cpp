#include "../Main.h"
#include "Title.h"

void TITLE::UpdateScene() {
	switch (step) {
	case LoadStep:Load();
		break;
	case MainStep:
		Control();
		Draw();
		break;
	case ReleaseStep:Release();
		break;
	default:Release();
		break;
	}
}

void TITLE::Load() {
	dx.LoadTexture("resource/BackGround/Title_BG.jpg", "Title_BG");
	step = MainStep;
}

void TITLE::Control() {
	if (dx.KeyState[DIK_SPACE] == dx.PUSH) {
		step = ReleaseStep;
	}
}

void TITLE::Draw() {
	dx.Draw(0, 0, window_width, window_height, 0.0f, 1.0f, false, "Title_BG");
}

void TITLE::Release() {
	dx.ReleaseTexture("Title_BG");
	g_scene = Information;
}

TITLE::TITLE() {
	
}

TITLE::~TITLE() {
	
}


