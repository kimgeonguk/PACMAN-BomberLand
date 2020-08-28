#include "../Main.h"
#include "Game.h"

void GAME::UpdateScene() {
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

void GAME::Load() {
	dx.LoadTexture("resource/Map/map.png", "map_BG");
	dx.LoadTexture("resource/Character/Player/Player2.png", "Player");
	step = MainStep;
}

void GAME::Control() {
	Move();

#ifdef _DEBUG
	if (dx.KeyState[DIK_SPACE] == dx.PUSH) {
		step = ReleaseStep;
	}
#endif
}

void GAME::Draw() {
	MAP map[16][9];
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 16; col++) {
			dx.Draw(map_width * col, map_height * row, map_width, map_height, 0.0f, 1.0f, false, "map_BG");
		}
	}
	dx.Draw(player.GetPos().X, player.GetPos().Y, player.GetSize().Width, player.GetSize().Height, 0.0f, 1.0f, false, "Player");
}

void GAME::Release() {
	dx.ReleaseTexture("map_BG");
	dx.ReleaseTexture("Player");
}

void GAME::Move() {
	if (dx.KeyState[DIK_UP] == dx.ON) {
		player.SetPos(player.GetPos().X, player.GetPos().Y - player.GetSpeed());
	}
	if (dx.KeyState[DIK_DOWN] == dx.ON) {
		player.SetPos(player.GetPos().X, player.GetPos().Y + player.GetSpeed());
	}
	if (dx.KeyState[DIK_RIGHT] == dx.ON) {
		player.SetPos(player.GetPos().X + player.GetSpeed(), player.GetPos().Y);
	}
	if (dx.KeyState[DIK_LEFT] == dx.ON) {
		player.SetPos(player.GetPos().X - player.GetSpeed(), player.GetPos().Y);
	}
}

GAME::GAME():map_width(120),map_height(120){

}

GAME::~GAME() {

}