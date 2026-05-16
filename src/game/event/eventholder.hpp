#pragma once
#include <filesystem>
#include "../anm2sprite.hpp"
#include "../common/vector.hpp"
#include <list>

enum EventOpType {
	NOP,
	DEFINE_ACTOR,
	SAY_LINE,
	PLAY_ANIM,
	WAIT
};

struct EventOp {
	std::string tag;
	EventOpType opc=EventOpType::NOP;
	std::vector<std::string> args;
};

struct EventActor {
	ANM2::Sprite spr;
	std::string id;
	std::string name;
	Vector pos=Vector(960,540);	//center
};

struct EventLine {
	std::string name;
	std::string text;
	bool isShown = false;
};

struct EventTimer {
	float maxTime=0.0f;
	float curTime=0.0f;
	bool shouldDelete = false;
};

class EventHolder {
public:
	bool paused = false;
	EventLine cur_line;
	bool showNextLine = false;
	bool loaded = false;
	std::filesystem::path filePath;
	int currentPos = 0;
	std::vector<EventOp> event_ops;
	std::vector<EventTimer> event_blocking_timers;
	std::vector<EventActor> actors;
	size_t event_pos=0;
	static EventOpType DecodeEventOpcode(const std::string& op);
	bool IsEventDone();
	void HandleEventOp(EventOp& op);
	void AdvanceEvent(float delta);
	void ParseScene(const std::filesystem::path& p);
};