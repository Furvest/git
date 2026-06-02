#include "eventholder.hpp"
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <charconv>

#include "../gamestate.hpp"

EventOpType EventHolder::DecodeEventOpcode(const std::string& op)
{
	if (op == "define_actor") return EventOpType::DEFINE_ACTOR;
	if (op == "say_line") return EventOpType::SAY_LINE;
	if (op == "play_anim") return EventOpType::PLAY_ANIM;
	if (op == "wait") return EventOpType::WAIT;
	if (op == "change_field") return EventOpType::CHANGE_FIELD;
	if (op == "wait_spr_finish") return EventOpType::WAIT_SPR_FINISH;
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
		SDL_Log("adding actor %s with name %s and sprite path %s\n",op.args[0].c_str(), op.args[1].c_str(), (filePath.parent_path() / op.args[2]).string().c_str());
		EventActor actor;
		actor.id = op.args[0];
		actor.name = op.args[1];
		auto r=std::from_chars(op.args[3].data(), op.args[3].data()+op.args[3].size(), actor.priority);
		if (r.ec == std::errc()) {
			actor.priority = 0;
		};
		actor.spr.Load(filePath.parent_path() / op.args[2]);
		
		actors.emplace_back(std::move(actor));
		std::sort(actors.begin(), actors.end(), [](auto& a, auto& b) { return a.priority < b.priority; });
	};

	if (op.opc == EventOpType::SAY_LINE) {
		EventActor* actor = nullptr;
		for (size_t i = 0; i < actors.size(); i++) {
			if (actors[i].id == op.args[0]) {
				actor = &actors[i];
			};
		};
		if (!actor) { return; };
		cur_line.isShown = false;
		cur_line.header = actor->name;
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
		std::from_chars(op.args[0].data(), op.args[0].data()+op.args[0].size(), t.maxTime, std::chars_format::general);
		event_blocking_timers.push_back(t);
	};

	if (op.opc == EventOpType::CHANGE_FIELD) {
		g_GameState.cur_field = op.args[0];
	};


	if (op.opc == EventOpType::WAIT_SPR_FINISH) {
		EventActor* actor = nullptr;
		for (size_t i = 0; i < actors.size(); i++) {
			if (actors[i].id == op.args[0]) {
				actor = &actors[i];
			};
		};
		if (!actor) { return; };
		EventBlockActor block;
		block.id = actor->id;
		event_blocking_actors.push_back(block);
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
		for (auto& actor_block : event_blocking_actors) {
			EventActor* actor = nullptr;
			for (size_t i = 0; i < actors.size(); i++) {
				if (actors[i].id == actor_block.id) {
					actor = &actors[i];
				};
			};
			if (!actor) { actor_block.shouldDelete = true; continue; };
			if (actor->spr.state.is_finished) {
				actor_block.shouldDelete = true;
			};
		};
		event_blocking_actors.erase(std::remove_if(event_blocking_actors.begin(), event_blocking_actors.end(), [](EventBlockActor& a) { return a.shouldDelete; }), event_blocking_actors.end());
		if (event_blocking_actors.size() != 0) {
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
//	std::ifstream input(p);
	SDL_IOStream* io = SDL_IOFromFile(p.string().c_str(), "rb");
	if (!io) return;
	size_t size = 0;

	SDL_SeekIO(io, 0, SDL_IO_SEEK_END);   // go to end
	size = SDL_TellIO(io);                // get position = file size
	SDL_SeekIO(io, 0, SDL_IO_SEEK_SET);   // go back to start

	std::string file_contents;
	file_contents.resize(size);

	SDL_ReadIO(io, file_contents.data(), size);

	SDL_CloseIO(io);
	std::stringstream input(file_contents);
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
		SDL_Log("parsing event operator\n");
	};
	return;
}
