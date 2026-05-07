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
		printf("hi!\n");
		for (SpritesheetData& sheet : data.spritesheets) {
			textures[sheet.id].path = sheet.path;
			std::filesystem::path load_path = p;
			auto dir = load_path.parent_path();
			printf("getting tex %s\n", (dir / sheet.path).string().c_str());
			textures[sheet.id].tex = g_TexManager.GetTexture((dir / sheet.path).string());
		};
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
	};
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
			auto& sheet_id = data.layers[layer.layer_id].sheet_id;
			int frame_id = 0;
			int elapsed = 0;
			for (size_t i = 0; i < layer.frames.size(); ++i)
			{
				if (state.cur_frame < elapsed+layer.frames[i].Delay)
				{
					frame_id = i;
					break;
				}
				elapsed += layer.frames[i].Delay;
			};
			auto& frame_data = layer.frames[frame_id];
			int next_frame_id = std::min((size_t)frame_id+1, layer.frames.size() - 1);
			auto& next_frame_data = layer.frames[next_frame_id];
			if (!layer.frames[frame_id].Interpolated) {
				next_frame_data = frame_data;
			};
			double new_ratio = (state.cur_frame-elapsed) / (double)frame_data.Delay;
			double old_ratio = 1.0 - new_ratio;
			g_Renderer.Render(textures[sheet_id].tex, pos + Vector(frame_data.XPosition*old_ratio + next_frame_data.XPosition*new_ratio - frame_data.XPivot,
				frame_data.YPosition*old_ratio + next_frame_data.YPosition*new_ratio - frame_data.YPivot),
				Quad(frame_data.XCrop, frame_data.YCrop, frame_data.Width, frame_data.Height), Vector(frame_data.XPivot, frame_data.YPivot), Vector(frame_data.XScale*old_ratio + next_frame_data.XScale*new_ratio, frame_data.YScale * old_ratio + next_frame_data.YScale * new_ratio), LerpAngleDegrees(frame_data.Rotation,next_frame_data.Rotation,new_ratio));
		};
	}
	void Sprite::Update()
	{
		AnimationData* animdata = nullptr;
		for (AnimationData& anim : data.anims) {
			if (anim.name == state.anim_name) {
				animdata = &anim;
				break;
			};
		};
		if (!animdata) { return; };
		state.cur_frame += 1;
		state.cur_frame %= animdata->framenum;
	}
	;
};