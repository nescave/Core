#pragma once
class Entity;
class Object;
class Component;
class RenderObject;
class Collider;

typedef std::shared_ptr<Entity> shared_Entity;
typedef std::weak_ptr<Entity> weak_Entity;

typedef std::shared_ptr<Object> shared_Object;
typedef std::weak_ptr<Object> weak_Object;

typedef std::shared_ptr<Component> shared_Component;
typedef std::weak_ptr<Component> weak_Component;

typedef std::shared_ptr<SDL_Texture> shared_Texture;
typedef std::shared_ptr<TTF_Font> shared_Font;

typedef std::weak_ptr<SDL_Texture> weak_Texture;

typedef std::vector<Collider*> ColliderList_t;
typedef std::vector<Object*> ObjectList_t;

