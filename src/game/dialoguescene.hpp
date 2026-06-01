#pragma once
#include "scene.hpp"
#include "dialogueholder.hpp"
#include "anm2sprite.hpp"
#include "manager.hpp"
class DialogueScene : public Scene {
	DialogueHolder* data;
public:
	DialogueScene(DialogueHolder* d);
	~DialogueScene();
	bool Update(float delta) override;
	bool Render(float delta) override;
	bool HandleEvent(SDL_Event* e) override;
	bool Focus() override { Scene::Focus(); return false; };
	bool Unfocus() override { Scene::Unfocus(); return false; }
};