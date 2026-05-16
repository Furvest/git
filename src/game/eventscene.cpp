#include "EventScene.hpp"
#include "rendermanager.hpp"

#include "anm2sprite.hpp"
#include "fs.hpp"

#include "event/eventholder.hpp"

EventScene::EventScene() {
	eh.ParseScene(FSManager::GetAssetPath()+"event/event1.tsv");
}

EventScene::EventScene(const std::filesystem::path& p) {
	eh.ParseScene(p);
}

EventScene::~EventScene(){
};

bool EventScene::Update(float delta)
{
	for (auto& a: eh.actors) {
		a.spr.Update(delta);
	};
	eh.AdvanceEvent(delta);
	if (eh.showNextLine) {

	};
	if (eh.IsEventDone()) {
		queueForRemoval = true;
	};
	return false;
}

bool EventScene::Render(float delta)
{
	Vector screen_size = g_Renderer.GetScreenSize();		//обычно будет 1920x1080
	for (auto& a : eh.actors) {
		a.spr.Render(a.pos);
	};
	if (eh.showNextLine) {
		g_Renderer.RenderFont(eh.cur_line.name,Vector(960,540)+Vector(0,300));
		g_Renderer.RenderFont(eh.cur_line.text, Vector(960, 540) + Vector(0, 350));
	};
	return false;
}

bool EventScene::HandleEvent(SDL_Event* e)
{
	if (e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		if (eh.showNextLine) {
			eh.paused = false;
			eh.showNextLine = false;
		};
	};
	return false;
}