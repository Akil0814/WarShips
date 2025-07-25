#include "Atlas.h"

void Atlas::clear()
{
    texture_list.clear();
}

int Atlas::get_size() const
{
    return static_cast<int>(texture_list.size());
}

bool Atlas::add_Texture(SDL_Texture* new_texture)
{
    texture_list.push_back(new_texture);
}

bool Atlas::add_Textures(std::initializer_list<SDL_Texture*> textures)
{
    if (textures.size() == 0)
        return false;

    for (auto tex : textures) 
    {
        if (tex==nullptr)
            return false;
        texture_list.push_back(tex);
    }

    return true;
}

SDL_Texture* Atlas::get_texture(size_t num)const
{
    if (texture_list.empty())
        return nullptr;

    return texture_list[num % texture_list.size()];
}