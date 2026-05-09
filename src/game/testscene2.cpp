#include "testscene2.hpp"
#include "rendermanager.hpp"

#include "anm2sprite.hpp"
#include "fs.hpp"

TestScene2::TestScene2() {
}

TestScene2::~TestScene2() {};

bool TestScene2::Update(float delta)
{
	return false;
}

bool TestScene2::Render(float delta)
{
	g_Renderer.RenderFont("test scene 2 говорит привет!", Vector(200, 100));
	return false;
}

bool TestScene2::HandleEvent(SDL_Event* e)
{
	return false;
}