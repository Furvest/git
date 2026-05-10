#include "scenemanager.hpp"

bool SceneManager::RemoveQueued()
{
	for (auto it = SceneList.begin(); it != SceneList.end(); ) {
		if ((*it)->queueForRemoval) {
			it=SceneList.erase(it);
		}
		else {
			++it;
		}
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
