#include "../Main.h"
#include "Information.h"

void INFORMATION::UpdateScene() {
	switch (step) {
	case LoadStep:Load();
		break;
	case MainStep:
		Control();
		Draw();
		break;
	case ReleaseStep:Release();
		break;
	}
}

void INFORMATION::Load() {
	dx.LoadTexture("resource/BackGround/Information.png", "Info_BG");
	step = MainStep;
}

void INFORMATION::Draw() {
	dx.Draw(0, 0, window_width, window_height, 0.0f, 1.0f, false, "Info_BG");
}

void INFORMATION::Control() {
	if (dx.KeyState[DIK_SPACE] == dx.ON) {
		step = ReleaseStep;
	}
}

void INFORMATION::Release() {
	dx.ReleaseTexture("Info_BG");
	g_scene = Game;
}

INFORMATION::INFORMATION() {

}

INFORMATION::~INFORMATION() {

}