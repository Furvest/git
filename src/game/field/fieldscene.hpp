#pragma once
#include "../scene.hpp"
#include "../dialogueholder.hpp"

#include "../anm2sprite.hpp"
#include "../manager.hpp"
#include "fielddata.hpp"
class FieldScene : public Scene {
	FieldData d;
	std::string last_name;
	ANM2::Sprite field_spr;
	DialogueHolder talk_data;
public:
	FieldScene();
	~FieldScene();
	void LoadField(const std::string& name);
	bool Update(float delta) override;
	bool Render(float delta) override;
	bool HandleEvent(SDL_Event* e) override;
};