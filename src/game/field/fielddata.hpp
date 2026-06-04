#pragma once
#include <filesystem>
#include <vector>
#include <string>


enum FieldObjType { /*!Перечисление типов объектов локации*/
	FIELD_NOP,
	EVENT,
	TALK,
	NEXT_FIELD
};


struct FieldObjectData { /*!Данные об объекте на локации*/
	FieldObjType actionType=FieldObjType::FIELD_NOP;
	std::string associated_null;
	std::string text_data;
};

struct FieldData { /*!Данные о локации*/
	std::string anm2name;
	std::filesystem::path anm2path;
	std::filesystem::path path;
	std::vector<FieldObjectData> objects;
	static FieldObjType ResolveObjTypeFromString(const std::string& name);
	void Init(const std::filesystem::path& p);
	void InitFromName(const std::string& name);
};
