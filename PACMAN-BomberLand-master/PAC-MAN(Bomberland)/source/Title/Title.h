#ifndef TITLE_H_
#define TITLE_H_

#include "../Scene.h"

class TITLE :public SCENE_BASE {
public:

	TITLE();

	~TITLE();

	void UpdateScene();


private:

	STEP step = LoadStep;

	void Load();
	void Control();
	void Draw();
	void Release();

};


#endif //TITLE_H_
