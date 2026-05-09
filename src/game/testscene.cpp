#include "testscene.hpp"
#include "rendermanager.hpp"

#include "anm2sprite.hpp"
#include "fs.hpp"

TestScene::TestScene() {
	test_spr.Load(FSManager::GetAssetPath()+"slop.anm2");
	test_spr.state.anim_name = "Shocked";
}

TestScene::~TestScene(){
};

bool TestScene::Update(float delta)
{
	test_spr.Update(delta);
	return false;
}

bool TestScene::Render(float delta)
{
	Vector screen_size = g_Renderer.GetScreenSize();		//обычно будет 1280x720
    test_spr.Render(Vector(screen_size.x/2.0f, screen_size.y / 2.0f + 40.0f));
    g_Renderer.RenderFont("hello!", Vector(screen_size.x-200, screen_size.y-100));
	return false;
}

bool TestScene::HandleEvent(SDL_Event* e)
{
	return false;
}