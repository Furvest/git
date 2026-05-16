#include "eventholder.hpp"
#include <fstream>
#include <string>
#include <algorithm>

EventOpType EventHolder::DecodeEventOpcode(const std::string& op)
{
	if (op == "define_actor") return EventOpType::DEFINE_ACTOR;
	if (op == "say_line") return EventOpType::SAY_LINE;
	if (op == "play_anim") return EventOpType::PLAY_ANIM;
	if (op == "wait") return EventOpType::WAIT;
	return EventOpType::NOP;
}

bool EventHolder::IsEventDone()
{
	return currentPos >= event_ops.size();
}

std::string _DequoteString(std::string& in) {
	if (in.find(',') != std::string::npos ) {
		return std::string(in.cbegin() + 1, in.cend() - 1);
	};
	return in;
};

void EventHolder::HandleEventOp(EventOp& op)
{
	if (op.opc == EventOpType::DEFINE_ACTOR) {
		EventActor actor;
		actor.id = op.args[0];
		actor.name = op.args[1];
		actor.spr.Load(filePath.parent_path() / op.args[2]);
		printf("adding actor %s with name %s and sprite path %s\n",op.args[0].c_str(), op.args[1].c_str(), (filePath.parent_path() / op.args[2]).string().c_str());
		actors.push_back(actor);
	};

	if (op.opc == EventOpType::SAY_LINE) {
		EventActor* actor=nullptr;
		for (size_t i = 0; i < actors.size(); i++) {
			if (actors[i].id == op.args[0]) {
				actor = &actors[i];
			};
		};
		if (!actor) { return; };
		cur_line.isShown = false;
		cur_line.name = actor->name;
		cur_line.text = op.args[1];
		showNextLine = true;
		paused = true;
	};

	if (op.opc == EventOpType::PLAY_ANIM) {
		EventActor* actor = nullptr;
		for (size_t i = 0; i < actors.size(); i++) {
			if (actors[i].id == op.args[0]) {
				actor = &actors[i];
			};
		};
		if (!actor) { return; };
		actor->spr.Play(op.args[1], op.args[2] == "true");
	};

	if (op.opc == EventOpType::WAIT) {
		EventTimer t;
		t.maxTime=std::stof(op.args[0]);
		event_blocking_timers.push_back(t);
	};

};

void EventHolder::AdvanceEvent(float delta)
{
	while (!paused) {
		for (auto& t : event_blocking_timers) {
			t.curTime += delta;
			if (t.curTime >= t.maxTime) {
				t.shouldDelete = true;
			};
		};
		event_blocking_timers.erase(std::remove_if(event_blocking_timers.begin(), event_blocking_timers.end(), [](EventTimer& a) { return a.shouldDelete; }), event_blocking_timers.end());
		if (event_blocking_timers.size() != 0) {
			return;
		};
		if (currentPos < event_ops.size()) {
			HandleEventOp(event_ops[currentPos]);
			currentPos += 1;
		}
		else {
			paused = true;
		};
	};
};

void EventHolder::ParseScene(const std::filesystem::path& p)
{
	std::ifstream input(p);
	std::string buffer;
	std::getline(input, buffer);	
	std::string field;
	std::vector<std::string> linestrings;
	filePath = p;
	while (std::getline(input, buffer)) {
		EventOp op;
		linestrings.clear();
		std::stringstream ss(buffer);
		while (std::getline(ss, field, '\t')) {
//			field = _DequoteString(field);
			linestrings.push_back(field);
		};

		op.tag = linestrings[0];
		op.opc = DecodeEventOpcode(linestrings[1]);
		for (auto it = linestrings.cbegin() + 2; it != linestrings.cend(); it++) {
			op.args.push_back(*it);
		};
		if (op.args.size() < 5) {
			op.args.resize(std::max((size_t)5,op.args.size()));
		};
		event_ops.push_back(op);
		printf("parsing event operator\n");
	};
	return;
}
