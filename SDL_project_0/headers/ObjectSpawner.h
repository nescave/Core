#pragma once
#include "CoreFonts.h"
#include "ObjectManager.h"
#include <optional>

class Object;
class SceneObject;
class Actor;
class Text;

class EntitySpawner
{
private:
    
    static EntityManager& GetEntityManager();
public:

    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnObject(Transform& t, shared_Texture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "") 
    {
        std::shared_ptr<T> actor = std::make_shared<T>();
        GetEntityManager().AddEntity(actor);
        actor->SetTransform(t);
        actor->SetSize(s);
        actor->SetTexture(tex);
        actor->name = n;
        actor->OnSpawn();
        return actor;
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnObject(Transform&& t = Transform(), shared_Texture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "") 
    {
        return SpawnObject<T>(t, tex, s, n);
    }
    
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnObject(const Vector2d& p, shared_Texture tex = nullptr, const Vector2d& s = Vector2d::zero, std::string n = "")
    {
        return SpawnObject<T>(Transform(p), tex, s, n);
    }
    //ActorSpawners----------------------------------------------------
    template<
        typename T,
        class = std::enable_if_t<std::is_base_of_v<Object, T>>,
        class = std::enable_if_t<!std::is_base_of_v<SceneObject, T>>
    >
    static std::weak_ptr<T> SpawnEntity(std::string n = "") 
    {
        std::shared_ptr<T> entity = std::make_shared<T>();
        GetEntityManager().AddEntity(entity);
        entity->name = n;
        return entity;
    }
};

