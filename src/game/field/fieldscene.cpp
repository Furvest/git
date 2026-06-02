#include "fieldscene.hpp"
#include "../gamestate.hpp"
#include "../dialoguescene.hpp"
#include "../eventscene.hpp"
#include "../fs.hpp"

FieldScene::FieldScene()
{
	LoadField(g_GameState.cur_field);
}

FieldScene::~FieldScene()
{}

void FieldScene::LoadField(const std::string& name)
{
	d.InitFromName(name);
};

bool FieldScene::Update(float delta)
{
	field_spr.Update(delta);
	if (last_name != g_GameState.cur_field) {
		SDL_Log("trying to load field! %s\n", g_GameState.cur_field.c_str());
		LoadField(g_GameState.cur_field);
		field_spr.Load(d.anm2path);
		last_name = g_GameState.cur_field;
	};
	return false;
}

bool FieldScene::Render(float delta)
{
	field_spr.Render(Vector(960, 540));
	return false;
}

bool FieldScene::HandleEvent(SDL_Event* e)
{
	if (!IsFocused()) return false;
	if (e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		SDL_Log("Hi!\n");
		Vector pos = Vector(e->motion.x, e->motion.y);
		for (auto& obj : d.objects) {
			bool is_in_rect=field_spr.IsPosInNullRect(obj.associated_null, pos, Vector(960,544));
			if (is_in_rect) {
				if (obj.actionType == FieldObjType::TALK) {
					talk_data.header = "";
					talk_data.isShown = "true";
					talk_data.text = obj.text_data;
					g_Manager.sceneManager.QueueScene(std::move(std::make_unique<DialogueScene>(&talk_data)));
					Unfocus();
				};
				if (obj.actionType == FieldObjType::NEXT_FIELD) {
					g_GameState.cur_field = obj.text_data;
				};
				if (obj.actionType == FieldObjType::EVENT) {
					g_Manager.sceneManager.QueueScene(std::move(std::make_unique<EventScene>( (FSManager::GetAssetFSPath() / "event" / (obj.text_data+".tsv")))) );
					Unfocus();
				};
			};
		};
	};
	return false;
}
