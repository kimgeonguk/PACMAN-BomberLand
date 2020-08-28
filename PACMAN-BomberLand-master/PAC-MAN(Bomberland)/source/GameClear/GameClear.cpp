#include "../Main.h"
#include "GameClear.h"

void GAMECLEAR::UpdateScene() {
	switch (step)
	{
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

void GAMECLEAR::Load() {

}

void GAMECLEAR::Control() {
	if (dx.KeyState[DIK_SPACE] == dx.PUSH) {
		step = ReleaseStep;
	}
}

void GAMECLEAR::Draw() {

}

void GAMECLEAR::Release() {

}

GAMECLEAR::GAMECLEAR() {

}

GAMECLEAR::~GAMECLEAR() {

}
