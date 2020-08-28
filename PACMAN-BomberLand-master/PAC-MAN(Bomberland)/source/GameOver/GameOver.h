#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "../Scene.h"

class GAMEOVER:public SCENE_BASE{
public:
	GAMEOVER();
	~GAMEOVER();

	void UpdateScene();

private:
	STEP step = LoadStep;

	void Load();
	void Control();
	void Draw();
	void Release();

};

#endif //GAMEOVER_H_