#ifndef INFORMATION_H_
#define INFORMATION_H_

#include "../Scene.h"

class INFORMATION:public SCENE_BASE {
public:

	INFORMATION();

	~INFORMATION();

	void UpdateScene();

private:

	STEP step = LoadStep;

	void Load();
	void Draw();
	void Control();
	void Release();
};
#endif
