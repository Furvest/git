#pragma once
#include <filesystem>
#include <string>
#include <vector>
struct SpritesheetData { int id=-1; std::string path; };	//path is relative
struct LayerData { int id = -1; int sheet_id = 0; std::string name; };
struct NullData { int id = -1; std::string name; };		//nulls are layers that do not have a backing spritesheet
struct EventData { int id = -1; std::string name; };	

struct FrameData{
	float XPosition;
	float YPosition;

	int XCrop;
	int YCrop;
	int XPivot;
	int YPivot;

	float XScale;
	float YScale;
	float Rotation;

	float r;
	float g;
	float b;
	float alpha;
	float ro;
	float go;
	float bo;

	unsigned int Width;
	unsigned int Height;
	unsigned int Delay;

	bool Visible;
};

struct Trigger { int event_id = -1; int at = 0; };

struct LayerAnimationData { int layer_id = 0; bool visible = false; std::vector<FrameData> frames; };


struct AnimationData {
	std::string name;
	unsigned int framenum=0;
	bool loop=false;
	std::vector<FrameData> root_anim;
	std::vector<LayerAnimationData> layer_anims;
	std::vector<LayerAnimationData> null_anims;
	std::vector<Trigger> triggers;
};

class ANM2Data {
public:
	ANM2Data(const std::filesystem::path& p);
	std::vector<SpritesheetData> spritesheets;
	std::vector<LayerData> layers;
	std::vector<NullData> nulls;
	std::vector<EventData> events;
	std::vector<AnimationData> anims;
	std::string default_anim;
};

class ANM2 {
	ANM2Data data;
public:
	ANM2(const std::filesystem::path& p);
};