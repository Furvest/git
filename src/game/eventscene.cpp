#include "eventscene.hpp"
#include "rendermanager.hpp"

#include "anm2sprite.hpp"
#include "fs.hpp"

#include "event/eventholder.hpp"

#include "dialoguescene.hpp"

EventScene::EventScene(const std::filesystem::path& p) {
	eh.ParseScene(p);
}

EventScene::~EventScene(){
	SDL_Log("Event scene is destroyed\n");
};

bool EventScene::Update(float delta)
{
	for (auto& a: eh.actors) {
		a.spr.Update(delta);
	};
	if (IsFocused()) {;
		eh.AdvanceEvent(delta);
		if (eh.showNextLine) {
			auto s = std::make_unique<DialogueScene>(&eh.cur_line);
			s->Focus();
			g_Manager.sceneManager.QueueScene(std::move(s));
			Unfocus();
			eh.showNextLine = false;
			eh.paused = false;
		};
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
/*	if (eh.showNextLine) {
		g_Renderer.RenderFont(eh.cur_line.header,Vector(960,540)+Vector(0,300));
		g_Renderer.RenderFont(eh.cur_line.text, Vector(960, 540) + Vector(0, 350));
	};*/
	return false;
}

bool EventScene::HandleEvent(SDL_Event* e)
{
	if (!IsFocused()) return false;
	if (e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		if (eh.showNextLine) {
			eh.paused = false;
			eh.showNextLine = false;
		};
	};
	return false;
}