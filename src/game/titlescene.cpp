#include "titlescene.hpp"
#include "rendermanager.hpp"

#include "anm2sprite.hpp"
#include "fs.hpp"
#include "eventscene.hpp"


TitleScene::TitleScene() {
	SDL_Log("We are in titlescene\n");
	SDL_Log("Path to load is %s\n", (FSManager::GetAssetPath() + "title.anm2").c_str());
	title.Load(FSManager::GetAssetPath() + "title.anm2");
	begin_button.Load(FSManager::GetAssetPath() + "title_begin.anm2");
	quit_button.Load(FSManager::GetAssetPath() + "title_quit.anm2");
}

TitleScene::~TitleScene() {};

bool TitleScene::Update(float delta)
{
	if (!IsFocused()) {
		return false;
	};
	title.Update(delta);
	begin_button.Update(delta);
	quit_button.Update(delta);
	return false;
}

bool TitleScene::Render(float delta)
{
	if (!IsFocused()) {
		return false;
	};
	title.Render(Vector(0, 0));
	begin_button.Render(title.GetNullLayerPos("Begin",Vector(0,0)));
	quit_button.Render(title.GetNullLayerPos("Quit", Vector(0, 0)));
	return false;
}

bool TitleScene::HandleEvent(SDL_Event* e)
{
	if (!IsFocused()) {
		return false;
	};
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

		bool is_begin_hover = quit_button.IsPosInNullRect("ButtonRect", pos, title.GetNullLayerPos("Begin", Vector(0, 0)));
		if (is_begin_hover) {
			g_Manager.sceneManager.QueueScene(std::move(std::make_unique<EventScene>(FSManager::GetAssetFSPath() / "event/event1.tsv")));
			Unfocus();
		};
	};
	return false;
}