#include "scene.hpp"
#include "anm2sprite.hpp"
class TestScene2 : public Scene {
public:
	TestScene2();
	~TestScene2();
	bool Update(float delta) override;
	bool Render(float delta) override;
	bool HandleEvent(SDL_Event* e) override;
	bool Focus() override { return false; };
	bool Unfocus() override { return false; }
};