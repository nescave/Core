#pragma once
struct TextureDeleter {
	void operator() (SDL_Texture* t) {
        //if (!message.empty()) printf((message + " \n").c_str());
		SDL_DestroyTexture(t);
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

