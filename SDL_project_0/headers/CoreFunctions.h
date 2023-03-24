#pragma once
struct TextureDeleter {
	void operator() (SDL_Texture* t) {
		SDL_DestroyTexture(t);
	}
};
struct SurfaceDeleter {
    void operator() (SDL_Surface* s) {
        SDL_FreeSurface(s);
    }
};
struct FontDeleter {
	void operator() (TTF_Font* f) {
		printf("font closed! \n");
		TTF_CloseFont(f);
	}
};

template<typename T1,typename T2>
uint32_t GetFirstFreeID(std::unordered_map<T1, std::weak_ptr<T2>> map) {
    uint32_t i = 0;
    while (map.find(i) != map.end()) {
        if (map[i].lock() == nullptr)break;
        ++i;
    }
    return i;
}
template<typename T1, typename T2>
uint32_t GetFirstFreeID(std::unordered_map<T1, std::shared_ptr<T2>> map) {
    uint32_t i = 0;
    while (map.find(i) != map.end()) {
        if (map[i] == nullptr)break;
        ++i;
    }
    return i;
}

