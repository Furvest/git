#include "scene.hpp"
#include "anm2sprite.hpp"
class TestScene : public Scene {
public:
	TestScene();
	~TestScene();
	bool Update(float delta) override;
	bool Render(float delta) override;
	bool HandleEvent(SDL_Event* e) override;
	bool Focus() override { return false; };
	bool Unfocus() override { return false; }
	ANM2::Sprite test_spr;
};