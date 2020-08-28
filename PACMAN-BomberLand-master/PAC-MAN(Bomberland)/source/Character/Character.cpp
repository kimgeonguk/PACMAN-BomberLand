#include "Character.h"

Vec2 PLAYER::GetPos() {
	return pos;
}

void PLAYER::SetPos(float x, float y) {
	pos.X = x;
	pos.Y = y;
}

Size PLAYER::GetSize() {
	return size;
}

void PLAYER::SetSize(float width, float height) {
	size.Width = width;
	size.Height = height;
}

float PLAYER::GetSpeed() {
	return speed;
}

PLAYER::PLAYER():is_dead(false) {
	SetPos(50, 50);
	SetSize(75, 75);
}

PLAYER::~PLAYER() {

}