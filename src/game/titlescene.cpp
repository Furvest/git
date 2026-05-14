#include "titlescene.hpp"
#include "rendermanager.hpp"

#include "anm2sprite.hpp"
#include "fs.hpp"


TitleScene::TitleScene() {
	title.Load(FSManager::GetAssetPath() + "title.anm2");
	begin_button.Load(FSManager::GetAssetPath() + "title_begin.anm2");
	quit_button.Load(FSManager::GetAssetPath() + "title_quit.anm2");
}

TitleScene::~TitleScene() {};

bool TitleScene::Update(float delta)
{
	title.Update(delta);
	begin_button.Update(delta);
	quit_button.Update(delta);
	return false;
}

bool TitleScene::Render(float delta)
{
	title.Render(Vector(0, 0));
	begin_button.Render(title.GetNullLayerPos("Begin",Vector(0,0)));
	quit_button.Render(title.GetNullLayerPos("Quit", Vector(0, 0)));
//	g_Renderer.RenderFont("test scene 2 говорит привет!", Vector(200, 100));
	return false;
}

bool TitleScene::HandleEvent(SDL_Event* e)
{
	if (e->type == SDL_EVENT_MOUSE_MOTION) {
		Vector pos = Vector(e->motion.x, e->motion.y);
		bool is_begin_hover = begin_button.IsPosInNullRect("ButtonRect", pos, title.GetNullLayerPos("Begin", Vector(0, 0)));
		bool is_quit_hover = quit_button.IsPosInNullRect("ButtonRect", pos, title.GetNullLayerPos("Quit", Vector(0, 0)));
		if (begin_button.state.is_finished) {
			if (is_begin_hover) {
				begin_button.Play("Selected", false);
			}
			else {
				begin_button.Play("Unselected", false);
			};
		}
		if (quit_button.state.is_finished) {
			if (is_quit_hover) {
				quit_button.Play("Selected", false);
			}
			else {
				quit_button.Play("Unselected", false);
			};
		};
	};
	if (e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		Vector pos = Vector(e->motion.x, e->motion.y);
		bool is_quit_hover = quit_button.IsPosInNullRect("ButtonRect", pos, title.GetNullLayerPos("Quit", Vector(0, 0)));
		if (is_quit_hover) {
			queueForRemoval = true;
		};
	};
	return false;
}