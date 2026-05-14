#include <filesystem>

enum EventOpType {
	NOP,
	DEFINE_ACTOR,
	SAY_LINE,
};

struct EventOp {
	std::string tag;
	EventOpType opc=EventOpType::NOP;
	std::vector<std::string> args;
};

struct EventActor {

};

class EventHolder {
public:
	bool loaded = false;
	std::vector<EventOp> event_ops;
	size_t event_pos;
	static EventOpType DecodeEventOpcode(const std::string& op);
	void AdvanceEvent();
	void ParseScene(const std::filesystem::path& p);
};