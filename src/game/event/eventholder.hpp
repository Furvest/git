/**
 * @file eventholder.hpp
 * @brief Заголовочный файл обработчика событий
 *
 * Нужен для обработки событий игры, декодирования операций из файла
 * и отрисовки диалогов
 *
 */

#pragma once
#include <filesystem>
#include "../anm2sprite.hpp"
#include "../common/vector.hpp"
#include "../dialogueholder.hpp"
#include <list>

/*!Перечисление операций событий*/
enum EventOpType {
	NOP,
	DEFINE_ACTOR,
	SAY_LINE,
	PLAY_ANIM,
	WAIT,
	CHANGE_FIELD,
	WAIT_SPR_FINISH
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
	int priority;
	Vector pos=Vector(960,540);	//center
};

struct EventTimer {
	float maxTime=0.0f;
	float curTime=0.0f;
	bool shouldDelete = false;
};

struct EventBlockActor {
	std::string id;
	bool shouldDelete = false;
};

/**
   * @class EventHolder
   * @brief Обработчик событий
   *
   * Отвечает за обработку событий и взаимодействие NPC с игроком
   * Работает с операциями указанными в перечислении
   * Список диалогов в специальном формате
   *
   */

class EventHolder {
public:
	~EventHolder() { SDL_Log("EventHolder destroyed!\n"); };
	bool paused = false;
	DialogueHolder cur_line;
	bool showNextLine = false;
	bool loaded = false;
	std::filesystem::path filePath;
	int currentPos = 0;
	std::vector<EventOp> event_ops;
	std::vector<EventTimer> event_blocking_timers;
	std::vector<EventBlockActor> event_blocking_actors;
	std::vector<EventActor> actors;
	size_t event_pos=0;
	static EventOpType DecodeEventOpcode(const std::string& op);
	bool IsEventDone();
	void HandleEventOp(EventOp& op);
	void AdvanceEvent(float delta);
	void ParseScene(const std::filesystem::path& p);
};
