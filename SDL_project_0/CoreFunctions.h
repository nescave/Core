#pragma once
struct TextureDeleter {
	void operator() (SDL_Texture* t) {
		//printf("texture deleted! \n");
		SDL_DestroyTexture(t);
	}
};
struct FontDeleter {
	void operator() (TTF_Font* f) {
		printf("font closed! \n");
		TTF_CloseFont(f);
	}
};

template<typename T>
int GetFirstFreeID(std::unordered_map<int, std::weak_ptr<T>> map) {
    int i = 0;
    while (map.find(i) != map.end()) {
        if (map[i].lock().get() == nullptr)break;
        ++i;
    }
    return i;
}
template<typename T>
int GetFirstFreeID(std::unordered_map<int, std::shared_ptr<T>> map) {
    int i = 0;
    while (map.find(i) != map.end()) {
        if (map[i].get() == nullptr)break;
        ++i;
    }
    return i;
}

