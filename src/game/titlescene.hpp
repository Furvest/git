#include "scene.hpp"
#include "anm2sprite.hpp"
#include "manager.hpp"
class TitleScene : public Scene {
	ANM2::Sprite title;
	ANM2::Sprite begin_button;
	ANM2::Sprite quit_button;
public:
	TitleScene();
	~TitleScene();
	bool Update(float delta) override;
	bool Render(float delta) override;
	bool HandleEvent(SDL_Event* e) override;
	bool Focus() override { Scene::Focus(); return false; };
	bool Unfocus() override { Scene::Unfocus(); return false; }
}; 