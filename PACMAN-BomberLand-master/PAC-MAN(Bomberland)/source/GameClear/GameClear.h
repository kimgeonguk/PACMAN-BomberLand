#ifndef GAMECLEAR_H_
#define GAMECLEAR_H_

#include "../Scene.h"

class GAMECLEAR:public SCENE_BASE {
public:
	GAMECLEAR();

	~GAMECLEAR();

	void UpdateScene();
private:
	STEP step = LoadStep;

	void Load();
	void Control();
	void Draw();
	void Release();

};

#endif //GAMECLEAR_H_
