#include "../Main.h"
#include "GameOver.h"

void GAMEOVER::UpdateScene() {
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

void GAMEOVER::Load() {

}

void GAMEOVER::Control(){
	if (dx.KeyState[DIK_SPACE] == dx.PUSH) {
		step = ReleaseStep;
	}
}

void GAMEOVER::Draw() {

}

void GAMEOVER::Release() {
	
}

GAMEOVER::GAMEOVER() {

}

GAMEOVER::~GAMEOVER() {

}
