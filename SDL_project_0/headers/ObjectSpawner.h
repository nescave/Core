#pragma once
#include "CoreFonts.h"
#include "ObjectManager.h"
#include <optional>

// class Object;
// class SceneObject;
// class Actor;
// class Text;

class ObjectSpawner
{
private:
    
    static ObjectManager& GetObjectManager();
public:

    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnObject(Transform& t, SharedTexture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "") 
    {
        std::shared_ptr<T> object = std::make_shared<T>();
        GetObjectManager().AddObject(object);
        object->SetTransform(t);
        object->SetSize(s);
        object->SetTexture(tex);
        object->name = n;
        object->OnSpawn();
        return object;
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnObject(Transform&& t = Transform(), SharedTexture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "") 
    {
        return SpawnObject<T>(t, tex, s, n);
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnObject(const Vector2d& p, SharedTexture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "")
    {
        return SpawnObject<T>(Transform(p), tex, s, n);
    }
    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Object, T>>,
        class = std::enable_if_t<!std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnObject(std::string n = "") 
    {
        std::shared_ptr<T> obj = std::make_shared<T>();
        GetObjectManager().AddObject(obj);
        obj->name = n;
        return obj;
    }
};

