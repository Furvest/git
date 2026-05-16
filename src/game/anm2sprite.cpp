#include "anm2sprite.hpp"
#include "texmanager.hpp"
#include "fs.hpp"

inline float NormalizeDegrees(float angle)
{
	angle = fmodf(angle, 360.0f);

	if (angle < 0)
		angle += 360.0f;

	return angle;
};

inline float LerpAngleDegrees(float a, float b, float t)
{
	float diff = fmodf(b - a + 180.0f, 360.0f);

	if (diff < 0)
		diff += 360.0f;

	diff -= 180.0f;

	return NormalizeDegrees(a + diff * t);
};

namespace ANM2 {
	void Sprite::Load(const std::filesystem::path& p) {
		data.Init(p);
		state.anim_name = data.default_anim;
		SDL_Log("hi!\n");
		for (SpritesheetData& sheet : data.spritesheets) {
			textures[sheet.id].path = sheet.path;
			std::filesystem::path load_path = p;
			auto dir = load_path.parent_path();
			SDL_Log("getting tex %s\n", (dir / sheet.path).string().c_str());
			textures[sheet.id].tex = g_TexManager.GetTexture((dir / sheet.path).string());
		};
	}
	Vector Sprite::GetNullLayerPos(const std::string& layer_name, Vector render_offset)
	{
		Vector out(0.0f, 0.0f);
		AnimationData* animdata = nullptr;
		for (AnimationData& anim : data.anims) {
			if (anim.name == state.anim_name) {
				animdata = &anim;
				break;
			};
		};
		if (!animdata) { return out; };
		for (LayerAnimationData layer : animdata->null_anims) {
			if (data.nulls[layer.layer_id].name != layer_name) { continue; };
			if (layer.visible != true) { continue; }
			if (layer.frames.size() == 0) { continue; };
			int frame_id = (layer.frames.size() - 1);
			int frame_begin_time = 0;
			for (int i = 0; i < (int)layer.frames.size(); ++i)
			{
				if (state.cur_frame < frame_begin_time + (int)layer.frames[i].Delay)
				{
					frame_id = i;
					break;
				}
				frame_begin_time += layer.frames[i].Delay;
			};
			auto& frame_data = layer.frames[frame_id];
			int next_frame_id = (int)std::min((size_t)frame_id + 1, layer.frames.size() - 1);


			auto& next_frame_data = layer.frames[next_frame_id];
			if (!layer.frames[frame_id].Interpolated) {
				next_frame_data = frame_data;
			};
			if (frame_data.Visible == false) { continue; };
			double new_ratio = (double)(state.cur_frame - frame_begin_time + (double)state.cur_frame_accumulator) / (double)frame_data.Delay;
			double old_ratio = 1.0 - new_ratio;

			Vector pos = Vector(frame_data.XPosition * old_ratio + next_frame_data.XPosition * new_ratio,
				frame_data.YPosition * old_ratio + next_frame_data.YPosition * new_ratio);

			return render_offset + pos;
		};
		return out;
	};

	bool Sprite::IsPosInNullRect(const std::string& layer_name, Vector pos, Vector render_offset) {
		AnimationData* animdata = nullptr;
		for (AnimationData& anim : data.anims) {
			if (anim.name == state.anim_name) {
				animdata = &anim;
				break;
			};
		};
		if (!animdata) { return false; };
		for (LayerAnimationData layer : animdata->null_anims) {
			if (data.nulls[layer.layer_id].name != layer_name) { continue; };
			if (layer.visible != true) { continue; }
			if (layer.frames.size() == 0) { continue; };
			int frame_id = (layer.frames.size() - 1);
			int frame_begin_time = 0;
			for (int i = 0; i < (int)layer.frames.size(); ++i)
			{
				if (state.cur_frame < frame_begin_time + (int)layer.frames[i].Delay)
				{
					frame_id = i;
					break;
				}
				frame_begin_time += layer.frames[i].Delay;
			};
			auto& frame_data = layer.frames[frame_id];
			int next_frame_id = (int)std::min((size_t)frame_id + 1, layer.frames.size() - 1);


			auto& next_frame_data = layer.frames[next_frame_id];
			if (!layer.frames[frame_id].Interpolated) {
				next_frame_data = frame_data;
			};
			if (frame_data.Visible == false) { continue; };
			double new_ratio = (double)(state.cur_frame - frame_begin_time + (double)state.cur_frame_accumulator) / (double)frame_data.Delay;
			double old_ratio = 1.0 - new_ratio;

			Vector center = Vector(frame_data.XPosition * old_ratio + next_frame_data.XPosition * new_ratio,
				frame_data.YPosition * old_ratio + next_frame_data.YPosition * new_ratio);
			Vector half_scale_xy = Vector( 100.0f*0.5f*(frame_data.XScale * old_ratio + next_frame_data.XScale * new_ratio), 100.0f*0.5f*(frame_data.YScale * old_ratio + next_frame_data.YScale * new_ratio));
			Vector topleft = center - half_scale_xy + render_offset;
			Vector bottomright = center + half_scale_xy + render_offset;
			return (pos.x >= topleft.x && pos.x <= bottomright.x && pos.y >= topleft.y && pos.y <= bottomright.y);
		};
		return false;
	};

	Sprite::Sprite(const std::filesystem::path& p) : data(p) {
		Load(p);
	};
	Sprite::~Sprite() {
		for (SheetRenderDesc sheet : textures) {
			if (sheet.tex) {
				g_TexManager.FreeTexture(sheet.path);
			};
		};
	}
	bool Sprite::Play(const std::string& name, bool force)
	{
		if (!force && state.anim_name == name) {
			return false;
		};
		AnimationData* animdata = nullptr;
		for (AnimationData& anim : data.anims) {
			if (anim.name == name) {
				animdata = &anim;
				break;
			};
		};
		if (!animdata) { return false; };
		state.cur_frame = 0;
		state.cur_frame_accumulator = 0.0f;
		state.is_finished = false;
		state.anim_name = name;
		return true;
	}
	;
	void Sprite::Render(Vector pos) {
		AnimationData* animdata = nullptr;
		for (AnimationData& anim : data.anims) {
			if (anim.name == state.anim_name) {
				animdata = &anim;
				break;
			};
		};
		if (!animdata) { return; };
		for (LayerAnimationData layer : animdata->layer_anims) {
			if (layer.frames.size() == 0) { continue; };
			if (layer.visible == false) { continue; };
			auto& sheet_id = data.layers[layer.layer_id].sheet_id;

			int frame_id = (layer.frames.size() - 1);
			int frame_begin_time = 0;
			for (int i = 0; i < (int)layer.frames.size(); ++i)
			{
				if (state.cur_frame < frame_begin_time+(int)layer.frames[i].Delay)
				{
					frame_id = i;
					break;
				}
				frame_begin_time += layer.frames[i].Delay;
			};
			auto& frame_data = layer.frames[frame_id];
			int next_frame_id = (int)std::min((size_t)frame_id+1, layer.frames.size() - 1);


			auto& next_frame_data = layer.frames[next_frame_id];
			if (!layer.frames[frame_id].Interpolated) {
				next_frame_data = frame_data;
			};
			if (frame_data.Visible == false) { continue; };
			double new_ratio = (double)(state.cur_frame-frame_begin_time + (double)state.cur_frame_accumulator) / (double)frame_data.Delay;
			double old_ratio = 1.0 - new_ratio;
			
			ColorDesc col{ .R = frame_data.r*old_ratio + next_frame_data.r*new_ratio, .A=frame_data.alpha*old_ratio + next_frame_data.alpha*new_ratio };

			g_Renderer.Render(textures[sheet_id].tex, pos + Vector(frame_data.XPosition*old_ratio + next_frame_data.XPosition*new_ratio - frame_data.XPivot,
				frame_data.YPosition*old_ratio + next_frame_data.YPosition*new_ratio - frame_data.YPivot),
				Quad(frame_data.XCrop, frame_data.YCrop, frame_data.Width, frame_data.Height), Vector(frame_data.XPivot, frame_data.YPivot), Vector(frame_data.XScale*old_ratio + next_frame_data.XScale*new_ratio, frame_data.YScale * old_ratio + next_frame_data.YScale * new_ratio), LerpAngleDegrees(frame_data.Rotation,next_frame_data.Rotation,new_ratio),col);
		};
	}
	void Sprite::Update(float delta)
	{
		AnimationData* animdata = nullptr;
		for (AnimationData& anim : data.anims) {
			if (anim.name == state.anim_name) {
				animdata = &anim;
				break;
			};
		};
		if (!animdata) { return; };
		delta = delta/data.information.time;
		state.cur_frame_accumulator += delta;
		while (state.cur_frame_accumulator >= 1.0f) {
			state.cur_frame += 1;
			state.cur_frame_accumulator -= 1.0f;
		};
		if (animdata->loop) {
			state.cur_frame %= animdata->framenum;
		}
		else {
			int prev_frame = state.cur_frame;
			state.cur_frame = std::min((int)animdata->framenum - 1, state.cur_frame);
			if (!state.is_finished && prev_frame != state.cur_frame) {
				state.is_finished = true;
			};
		};
	}
	;
};