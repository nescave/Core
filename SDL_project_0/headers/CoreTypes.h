#pragma once
class Object;
class SceneObject;
class Component;
class RenderableObject;
class Collider;

typedef std::shared_ptr<Object> shared_Entity;
typedef std::weak_ptr<Object> weak_Entity;

typedef std::shared_ptr<SceneObject> shared_Object;
typedef std::weak_ptr<SceneObject> weak_Object;

typedef std::shared_ptr<Component> shared_Component;
typedef std::weak_ptr<Component> weak_Component;

typedef std::shared_ptr<SDL_Texture> shared_Texture;
typedef std::shared_ptr<TTF_Font> shared_Font;

typedef std::weak_ptr<SDL_Texture> weak_Texture;

//typedef std::vector<Collider*> ColliderList_t;
//typedef std::vector<Object*> ObjectList_t;

