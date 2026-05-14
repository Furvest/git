#include "eventholder.hpp"
#include <fstream>
#include <string>

EventOpType EventHolder::DecodeEventOpcode(const std::string& op)
{
	if (op == "define_actor") return EventOpType::DEFINE_ACTOR;
	if (op == "say_line") return EventOpType::SAY_LINE;
	return EventOpType::NOP;
}

void EventHolder::AdvanceEvent()
{
}

void EventHolder::ParseScene(const std::filesystem::path& p)
{
	std::ifstream input(p);
	std::string buffer;
	std::getline(input, buffer);	// пропуск линии заголовка
	std::string field;
	std::vector<std::string> linestrings;
	while (std::getline(input, buffer)) {
		EventOp op;
		linestrings.clear();
		std::stringstream ss(buffer);
		while (std::getline(ss, field, '\t')) {
			linestrings.push_back(field);
		};

		op.tag = linestrings[0];
		op.opc = DecodeEventOpcode(linestrings[1]);
		for (auto it = linestrings.cbegin() + 2; it != linestrings.cend(); it++) {
			op.args.push_back(*it);
		};
		event_ops.push_back(op);
	};
	return;
}
