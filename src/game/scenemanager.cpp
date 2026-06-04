#include "scenemanager.hpp"
#include <algorithm>
#include <execution>
#include "texmanager.hpp"

void SceneManager::QueueScene(std::unique_ptr<Scene> s)
{
	ScenesToAdd.push_back(std::move(s));
	orderChanged = true;
}

bool SceneManager::UpdateQueue()
{
	for (auto it = SceneList.begin(); it != SceneList.end(); ) {
		if ((*it)->queueForRemoval) {
			it=SceneList.erase(it);
			orderChanged = true;
		}
		else {
			++it;
		}
	};
	for (auto it = ScenesToAdd.begin(); it != ScenesToAdd.end(); ) {
		SceneList.push_back(std::move(*it));
		it = ScenesToAdd.erase(it);
	};
	if (orderChanged){	//todo: если захочется на ходу менять порядок отрисовки сцен то надо обновлять эту переменную либо убрать её
		g_TexManager.TrimTextures();
		SceneList.sort([](const auto& a, const auto& b) { return a->sortPriority < b->sortPriority; });
		orderChanged = false;
		if (SceneList.size() != 0) {
			auto& end_scene=*(SceneList.back());
			end_scene.Focus();
		};
	};
	return SceneList.size()==0;
}

bool SceneManager::Update(float delta)
{
	for (auto& s : SceneList) {
		s->Update(delta);
	};
	return false;
}

bool SceneManager::Render(float delta)
{
	for (auto& s : SceneList) {
		s->Render(delta);
	};
	return false;
}

bool SceneManager::HandleEvent(SDL_Event* e)
{
	for (auto& s : SceneList) {
		s->HandleEvent(e);
	};
	return false;
}
