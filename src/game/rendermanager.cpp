#include "rendermanager.hpp"
#include "fs.hpp"

Vector Renderer::GetScreenSize()
{
    int w, h;
    SDL_GetRenderLogicalPresentation(r, &w, &h, nullptr);
    return Vector((float)w,(float)h);
}

Renderer::Renderer() {};
void Renderer::Render(SDL_Texture* tex, Vector pos, Quad crop_region, Vector pivot, Vector scale, double rotation, ColorDesc color) {
    Vector final_scale{
        scale.x * globalScale,
        scale.y * globalScale
    };

    SDL_FRect src_rect{
        .x = (float)crop_region.topleft.x,
        .y = (float)crop_region.topleft.y,
        .w = (float)crop_region.widthheight.x,
        .h = (float)crop_region.widthheight.y
    };

    Vector crop_rel = crop_region.widthheight;

    SDL_FPoint render_pivot{
        .x = pivot.x * final_scale.x,
        .y = pivot.y * final_scale.y
    };

    SDL_FRect dst_rect{
        .w = crop_rel.x * final_scale.x,
        .h = crop_rel.y * final_scale.y
    };

    dst_rect.x =
        pos.x * globalScale
        - pivot.x * (final_scale.x - globalScale);

    dst_rect.y =
        pos.y * globalScale
        - pivot.y * (final_scale.y - globalScale);

    SDL_SetTextureColorModFloat(tex, (float)color.R, (float)color.G, (float)color.B);
    SDL_SetTextureAlphaModFloat(tex, (float)color.A);
    SDL_RenderTextureRotated(
        r,
        tex,
        &src_rect,
        &dst_rect,
        rotation,
        &render_pivot,
        SDL_FLIP_NONE
    );
}
void Renderer::RenderFont(const std::string& text, Vector pos) //функция дорогая! надо будет придумать способ рисовать получше
{
    SDL_Color c;
    c.r = 0;
    c.g = 0;
    c.b = 0;
    c.a = 255;
    TTF_Text* drawn_text=TTF_CreateText(text_engine, main_font, text.c_str(), text.size());
    TTF_SetTextColor(drawn_text, c.r, c.g, c.b, c.a);
    TTF_DrawRendererText(drawn_text, pos.x, pos.y);
    TTF_DestroyText(drawn_text);
};

void Renderer::Init(SDL_Renderer* renderer) {
	r = renderer;
    TTF_Init();
    text_engine=TTF_CreateRendererTextEngine(r);
    main_font = TTF_OpenFont( (FSManager::GetAssetPath() + "font.ttf").c_str(),36.0f);
};

Renderer g_Renderer;