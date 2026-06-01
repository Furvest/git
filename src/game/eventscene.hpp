#include "scene.hpp"
#include "anm2sprite.hpp"
#include "event/eventholder.hpp"
#include <filesystem>
class EventScene : public Scene {
public:
	EventScene(const std::filesystem::path& p);
	~EventScene();
	bool Update(float delta) override;
	bool Render(float delta) override;
	bool HandleEvent(SDL_Event* e) override;
	ANM2::Sprite test_spr;
	EventHolder eh;
};