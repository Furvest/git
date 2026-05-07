#pragma once
#include "rendermanager.hpp"
#include "anm2data.hpp"
#include "anm2state.hpp"
#include "common/vector.hpp"
#include <SDL3/SDL.h>
#include <array>
namespace ANM2 {
	struct SheetRenderDesc {
		SDL_Texture* tex=nullptr;
		std::string path;
	};
	class Sprite {
		ANM2Data data;
		std::array<SheetRenderDesc,64> textures;
	public:
		AnimationState state;	//public is temp
		Sprite() = default;
		Sprite(const std::filesystem::path& p);
		void Load(const std::filesystem::path& p);
		~Sprite();
		void Render(Vector pos);
		void Update();
	};
}