#pragma once
#include "ObjectManager.h"
#include <optional>

class ObjectSpawner
{
private:
    
    static ObjectManager& GetObjectManager();
public:

    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<RenderableObject, T>>
    >
    static std::shared_ptr<T> SpawnObject(Transform& t, SharedTexture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "") 
    {
        std::shared_ptr<T> object = std::make_shared<T>();
        GetObjectManager().AddObject(object);
        if (n.empty())
            n = ((std::string)typeid(T).name()).erase(0,6).append("_" + std::to_string(object->id));
        object->name = n;
        object->SetTransform(t);
        object->SetTexture(tex);
        object->SetSize(s);
        object->OnSpawn();
        return object;
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<RenderableObject, T>>
    >
    static std::shared_ptr<T> SpawnObject(Transform&& t = Transform(), SharedTexture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "") 
    {
        return SpawnObject<T>(t, tex, s, n);
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<RenderableObject, T>>
    >
    static std::shared_ptr<T> SpawnObject(const Vector2d& p, SharedTexture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "")
    {
        return SpawnObject<T>(Transform(p), tex, s, n);
    }
    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>,
        class = std::enable_if_t<!std::is_base_of_v<RenderableObject, T>>
    >
    static std::shared_ptr<T> SpawnObject(Transform& t, std::string n = "") 
    {
        std::shared_ptr<T> object = std::make_shared<T>();
        GetObjectManager().AddObject(object);
        object->SetTransform(t);
        if (n == "")
            n = ((std::string)typeid(T).name()).erase(0,6).append("_" + std::to_string(object->id));
        object->name = n;
        return object;
    }
    template<
    typename T,
    class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>,
    class = std::enable_if_t<!std::is_base_of_v<RenderableObject, T>>
    >
    static std::shared_ptr<T> SpawnObject(Transform&& t = Transform(), std::string n = "") 
    {
        return SpawnObject<T>(t, n);
    }
    template<
    typename T,
    class = std::enable_if_t<std::is_base_of_v<Object, T>>,
    class = std::enable_if_t<!std::is_base_of_v<SceneObject, T>>
    >
    static std::shared_ptr<T> SpawnObject(std::string n = "") 
    {
        std::shared_ptr<T> object = std::make_shared<T>();
        GetObjectManager().AddObject(object);
        if (n == "")
            n = ((std::string)typeid(T).name()).erase(0,6).append("_" + std::to_string(object->id));
        object->name = n;
        return object;
    }
};

