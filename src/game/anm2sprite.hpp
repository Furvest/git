#pragma once
#include "rendermanager.hpp"
#include "anm2data.hpp"
#include "anm2state.hpp"
#include "common/vector.hpp"
#include <SDL3/SDL.h>
#include <array>
#include "texmanager.hpp"
namespace ANM2 {
	struct SheetRenderDesc {
		SDL_Texture* tex=nullptr;
		std::string path="";
	};
	class Sprite {
		ANM2Data data;
		std::array<SheetRenderDesc,64> textures;
	public:
		AnimationState state;	//public is temp
		std::string path;
		Sprite() = default;
		Sprite(const std::filesystem::path& p);
		Sprite(const Sprite& other);
		void Load(const std::filesystem::path& p);
		Vector GetNullLayerPos(const std::string& layer_name, Vector render_offset);
		bool IsPosInNullRect(const std::string& layer_name, Vector pos, Vector render_offset);
		~Sprite();
		bool Play(const std::string& name, bool force);
		void Render(Vector pos);
		void Update(float delta);
	};
}