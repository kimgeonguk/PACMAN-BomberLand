#ifndef SCENE_H_
#define SCENE_H_

class SCENE_BASE {
public:

	enum SCENE {
		Title,
		Information,
		Game,
		GameClear,
		GameOver
	};

	SCENE_BASE();

	virtual ~SCENE_BASE();

protected:
	enum STEP {
		LoadStep,
		MainStep,
		ReleaseStep
	};

	virtual void UpdateScene() = 0;
	virtual void Load() = 0;
	virtual void Draw() = 0;
	virtual void Control() = 0;
	virtual void Release() = 0;

};

#endif
