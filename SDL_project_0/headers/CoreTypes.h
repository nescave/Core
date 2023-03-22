#pragma once
class Object;
class SceneObject;
class Component;
class RenderableObject;
class Collider;

typedef std::shared_ptr<Object> SharedObject;
typedef std::weak_ptr<Object> WeakObject;

typedef std::shared_ptr<SceneObject> SharedSceneObject;
typedef std::weak_ptr<SceneObject> WeakSceneObject;

typedef std::shared_ptr<Component> SharedComponent;
typedef std::weak_ptr<Component> WeakComponent;

typedef std::shared_ptr<SDL_Texture> SharedTexture;
typedef std::weak_ptr<SDL_Texture> WeakTexture;

typedef std::shared_ptr<TTF_Font> SharedFont;

//typedef std::vector<Collider*> ColliderList_t;
//typedef std::vector<Object*> ObjectList_t;

