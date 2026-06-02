#include "dialoguescene.hpp"
#include "fs.hpp"

DialogueScene::DialogueScene(DialogueHolder* d) {
	SDL_Log("New dialogue\n");
	box.Load(FSManager::GetAssetPath() + "dialogue_box.anm2");
	data = d;
}

DialogueScene::~DialogueScene() {}
bool DialogueScene::Update(float delta)
{
	return false;
}
bool DialogueScene::Render(float delta)
{
	box.Render(Vector(0, 0));
	Vector title_pos=box.GetNullLayerPos("Title", Vector(0, 0));
	Vector text_pos = box.GetNullLayerPos("Text", Vector(0, 0));
	g_Renderer.RenderFontCentered(data->header, title_pos);
	g_Renderer.RenderFontCentered(data->text, text_pos);
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