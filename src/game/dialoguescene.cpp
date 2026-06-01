#include "dialoguescene.hpp"

DialogueScene::DialogueScene(DialogueHolder* d) {
	SDL_Log("New dialogue\n");
	data = d;
}

DialogueScene::~DialogueScene() {}
bool DialogueScene::Update(float delta)
{
	return false;
}
bool DialogueScene::Render(float delta)
{
	g_Renderer.RenderFont(data->header, Vector(960, 540) + Vector(-20, 300));
	g_Renderer.RenderFont(data->text, Vector(960, 540) + Vector(-20, 350));
	return false;
}
bool DialogueScene::HandleEvent(SDL_Event* e)
{
	if (!IsFocused()) return false;
	if (e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		data->isShown = false;
		queueForRemoval = true;
	};
	return false;
}
;