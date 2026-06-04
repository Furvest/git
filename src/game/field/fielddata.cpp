#include "fielddata.hpp"
#include <tinyxml2.h>
#include <SDL3/SDL.h>
#include "../fs.hpp"

FieldObjType FieldData::ResolveObjTypeFromString(const std::string& name)
{
	if (name == "talk") return FieldObjType::TALK;
	if (name == "event") return FieldObjType::EVENT;
	if (name == "next_field") return FieldObjType::NEXT_FIELD;
	return FieldObjType(FIELD_NOP);
}

void FieldData::Init(const std::filesystem::path& p) {
	path = "";
	anm2name = "";
	anm2path = "";
	objects.clear();
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

	tinyxml2::XMLDocument d;
	//		auto err = d.LoadFile(p.string().c_str());
	auto err = d.Parse(file_contents.c_str());
	if (err) {
		SDL_Log("xml fail!\n");
		return;		//xml parse fail
	};
	tinyxml2::XMLHandle doc_handle(&d);
	auto root = doc_handle.FirstChildElement("field");
	anm2name = root.ToElement()->FindAttribute("anm2")->Value();
	anm2path = p.parent_path() / anm2name;
	SDL_Log("Recorded ANM2 path for field %s is %s\n", p.string().c_str(), anm2path.string().c_str());
	auto obj = root.FirstChildElement("object");
	while (obj.ToElement()) {
		FieldObjectData field_o;
		field_o.associated_null = obj.ToElement()->FindAttribute("null")->Value();
		field_o.text_data = obj.ToElement()->FindAttribute("text")->Value();
		field_o.actionType = FieldData::ResolveObjTypeFromString(obj.ToElement()->FindAttribute("type")->Value());
		objects.push_back(field_o);
		obj = obj.NextSiblingElement();
	};
	path = p;

}
void FieldData::InitFromName(const std::string& name)
{
	auto p=FSManager::GetAssetFSPath() / "field" / (name + ".xml");
	Init(p);

};