#include "anm2data.hpp"
#include "tinyxml2.h"
#include <SDL3/SDL.h>

namespace ANM2 {
	FrameData _parse_frame(tinyxml2::XMLHandle& h) {
		if (!h.ToElement()) {
			return FrameData{};	//invalid frame
		};
		FrameData out;
		auto e = h.ToElement();
		out.XPosition = e->FloatAttribute("XPosition");
		out.YPosition = e->FloatAttribute("YPosition");
		out.XCrop = e->IntAttribute("XCrop", 0);
		out.YCrop = e->IntAttribute("YCrop", 0);
		out.Width = e->IntAttribute("Width", 0);
		out.Height = e->IntAttribute("Height", 0);
		out.XPivot = e->IntAttribute("XPivot", 0);
		out.YPivot = e->IntAttribute("YPivot", 0);
		out.XScale = e->FloatAttribute("XScale", 100.0f) / 100.0f;
		out.YScale = e->FloatAttribute("YScale", 100.0f) / 100.0f;
		out.Rotation = e->FloatAttribute("Rotation", 0.0f);
		out.Visible = e->BoolAttribute("Visible", false);
		out.Interpolated = e->BoolAttribute("Interpolated", false);
		out.r = e->FloatAttribute("RedTint", 255.0f) / 255.0f;
		out.g = e->FloatAttribute("GreenTint", 255.0f) / 255.0f;
		out.b = e->FloatAttribute("BlueTint", 255.0f) / 255.0f;
		out.alpha = e->FloatAttribute("AlphaTint", 255.0f) / 255.0f;
		out.Delay = e->IntAttribute("Delay");
		return out;
	};

	void ANM2Data::Init(const std::filesystem::path& p)
	{
		SDL_IOStream* io=SDL_IOFromFile(p.string().c_str(), "rb");
		if (!io) return;
		size_t size = 0;

		SDL_SeekIO(io, 0, SDL_IO_SEEK_END);   // go to end
		size = SDL_TellIO(io);                // get position = file size
		SDL_SeekIO(io, 0, SDL_IO_SEEK_SET);   // go back to start

		std::string file_contents;
		file_contents.resize(size);

		SDL_ReadIO(io, file_contents.data(), size);

		SDL_CloseIO(io);
		
		tinyxml2::XMLDocument d;
//		auto err = d.LoadFile(p.string().c_str());
		auto err = d.Parse(file_contents.c_str());
		if (err) {
			SDL_Log("xml fail!\n");
			return;		//xml parse fail
		};
		tinyxml2::XMLHandle doc_handle(&d);
		auto root = doc_handle.FirstChildElement("AnimatedActor");
		auto info = root.FirstChildElement("Info");
		{
			information.fps=info.ToElement()->FloatAttribute("Fps");
			information.time = 1.0f / information.fps;
		}
		auto content = root.FirstChildElement("Content");

		{
			auto sheet = content.FirstChildElement("Spritesheets").FirstChildElement("Spritesheet");
			while (sheet.ToElement()) {
				SpritesheetData spr;
				spr.id = sheet.ToElement()->IntAttribute("Id", -1);
				spr.path = sheet.ToElement()->Attribute("Path");
				spritesheets.push_back(spr);
				sheet = sheet.NextSiblingElement();
			};
		};

		{
			auto layer = content.FirstChildElement("Layers").FirstChildElement("Layer");
			while (layer.ToElement()) {
				LayerData l;
				l.id = layer.ToElement()->IntAttribute("Id", -1);
				l.sheet_id = layer.ToElement()->IntAttribute("SpritesheetId", 0);
				l.name = layer.ToElement()->Attribute("Name");
				layers.push_back(l);
				layer = layer.NextSiblingElement();
			};
		};

		{
			auto null = content.FirstChildElement("Nulls").FirstChildElement("Null");
			while (null.ToElement()) {
				NullData n;
				n.id = null.ToElement()->IntAttribute("Id", -1);
				n.name = null.ToElement()->Attribute("Name");
				nulls.push_back(n);
				null = null.NextSiblingElement();
			};
		};
		{
			auto event = content.FirstChildElement("Events").FirstChildElement("Event");
			while (event.ToElement()) {
				EventData e;
				e.id = event.ToElement()->IntAttribute("Id", -1);
				e.name = event.ToElement()->Attribute("Name");
				events.push_back(e);
				event = event.NextSiblingElement();
			};
		};
		auto animations = root.FirstChildElement("Animations");
		if (!animations.ToElement()) {
			return;
		};
		default_anim = animations.ToElement()->Attribute("DefaultAnimation");
		{
			auto anim = animations.FirstChildElement("Animation");
			while (anim.ToElement()) {
				AnimationData adata;
				adata.name = anim.ToElement()->Attribute("Name");
				adata.framenum = anim.ToElement()->IntAttribute("FrameNum", 0);
				adata.loop = anim.ToElement()->BoolAttribute("Loop", false);

				{
					auto rootanim = anim.FirstChildElement("RootAnimation");
					if (rootanim.ToElement()) {
						auto frame = rootanim.FirstChildElement("Frame");
						while (frame.ToElement()) {
							adata.root_anim.push_back(_parse_frame(frame));
							frame = frame.NextSiblingElement();
						};
					};
				};

				{
					auto layeranim = anim.FirstChildElement("LayerAnimations").FirstChildElement("LayerAnimation");
					while (layeranim.ToElement()) {
						LayerAnimationData lad;
						lad.layer_id = layeranim.ToElement()->IntAttribute("LayerId");
						lad.visible = layeranim.ToElement()->BoolAttribute("Visible");
						auto frame = layeranim.FirstChildElement("Frame");
						while (frame.ToElement()) {
							lad.frames.push_back(_parse_frame(frame));
							frame = frame.NextSiblingElement();
						};
						adata.layer_anims.push_back(lad);
						layeranim = layeranim.NextSiblingElement();
					};
				};

				{
					auto layeranim = anim.FirstChildElement("NullAnimations").FirstChildElement("NullAnimation");
					while (layeranim.ToElement()) {
						LayerAnimationData lad;
						lad.layer_id = layeranim.ToElement()->IntAttribute("NullId");
						lad.visible = layeranim.ToElement()->BoolAttribute("Visible");
						auto frame = layeranim.FirstChildElement("Frame");
						while (frame.ToElement()) {
							lad.frames.push_back(_parse_frame(frame));
							frame = frame.NextSiblingElement();
						};
						adata.null_anims.push_back(lad);
						layeranim = layeranim.NextSiblingElement();
					};
				};

				anims.push_back(adata);
				anim = anim.NextSiblingElement();
			};
		};
		_init = true;
	};
	ANM2Data::ANM2Data(const std::filesystem::path& p) {
		Init(p);
	};
};

