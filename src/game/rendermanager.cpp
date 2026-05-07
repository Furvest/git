#include "rendermanager.hpp"

Renderer::Renderer() {};
void Renderer::Render(SDL_Texture* tex, Vector pos, Quad crop_region, Vector pivot, Vector scale, double rotation) {
	SDL_FRect src_rect{ .x = (float)crop_region.topleft.x,.y=(float)crop_region.topleft.y,.w=(float)crop_region.widthheight.x,.h=(float)crop_region.widthheight.y };
	Vector crop_rel=crop_region.widthheight;
	SDL_FPoint render_pivot{ .x = (float)pivot.x,.y = (float)pivot.y };
	SDL_FRect dst_rect{ .x = (float)pos.x,.y = (float)pos.y,.w = (float)crop_rel.x*(float)scale.x,.h = (float)crop_rel.y * (float)scale.y };	//todo: adjust scale for pivot
	dst_rect.x = pos.x - pivot.x * (scale.x - 1.0);
	dst_rect.y = pos.y - pivot.y * (scale.y - 1.0);
	pivot.x = pivot.x * scale.x;
	pivot.y = pivot.y * scale.y;
	SDL_RenderTextureRotated(r,tex,&src_rect,&dst_rect,rotation,&render_pivot,SDL_FLIP_NONE);
};

void Renderer::Init(SDL_Renderer* renderer) {
	r = renderer;
};

Renderer g_Renderer;