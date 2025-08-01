#include"txt_texture_manager.h"

SDL_Texture* TxtTextureManager::get_txt_texture(SDL_Renderer* renderer,TTF_Font* font,const std::string& text,
												bool is_bold, const SDL_Color& color)
{
	if (is_nullptr(renderer, font, text))
		return nullptr;

	int style = TTF_GetFontStyle(font);

	if(is_bold)
		style |= TTF_STYLE_BOLD;

	std::string key = make_text_key(text, style, color);
	
	auto it = text_texture_pool.find(key);
	if (it != text_texture_pool.end())
		return it->second;

	TTF_SetFontStyle(font, style);

	SDL_Surface* suf_text = TTF_RenderUTF8_Blended(font, text.c_str(), color);

	if (!suf_text) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"TTF_RenderUTF8_Blended failed for text \"%s\": %s",
			text.c_str(), TTF_GetError());
		return nullptr;
	}

	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);

	if (!tex_text) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"SDL_CreateTextureFromSurface failed for text \"%s\": %s",
			text.c_str(), SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(suf_text);

	text_texture_pool[key] = tex_text;

	return tex_text;
}

TxtTextureManager::~TxtTextureManager()
{
	for (auto& kv : text_texture_pool)
		SDL_DestroyTexture(kv.second);
}

bool TxtTextureManager::is_nullptr(SDL_Renderer* renderer, TTF_Font* font, const std::string& text)const
{
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderer is null for text \"%s\"", text.c_str());
		return true;
	}

	if (!font) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font is null for text \"%s\"", text.c_str());
		return true;
	}

	return false;
}

std::string TxtTextureManager::make_text_key(const std::string& text, int style, const SDL_Color& color)const
{
	return text
		+ "|" + std::to_string(style)
		+ "|" + std::to_string(color.r)
		+ "," + std::to_string(color.g)
		+ "," + std::to_string(color.b)
		+ "," + std::to_string(color.a);
}

