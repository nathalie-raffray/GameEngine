#pragma once
#include <string>
#include <vector>

using SpriteId = std::string;

struct Component
{
    bool isEnabled() const
    {
#if _DEBUG
        return isEnabled_;
#else
        return true;
#endif
    }

#if _DEBUG
    bool isEnabled_;
#endif
};

struct SpriteComponent : Component
{
	// Serializable attribute
	SpriteId spriteId;
#if _DEBUG
	bool isEnabled;
#endif
	// Transient attributes
};

enum ComponentType
{
    AIComponent_Type
};

struct Entity
{
    void attach(SpriteComponent *comp) { comps.emplace_back(comp); }

    bool isAttached(ComponentType ct) { return false; }

    std::vector<Component*> comps;
};

struct EntityHandle
{
    Entity* operator ->()
    {
        return &registry.entities[index];
    }

    int index;
};

struct EntityRegistry
{
    Entity* createEntity(const char*)
    {
        entities.emplace_back();
        return &entities.back();
    }

    std::vector<Entity> entities;

} registry;

struct System
{
    void add(EntityHandle e)
    {
        entities.emplace_back(e);
    }

    void update(float dt)
    {
        for (auto e : entities)
        {
            updateEntity(e, dt);
        }
    }

    virtual bool isValid(EntityHandle e) const = 0;
    virtual void updateEntity(EntityHandle e, float dt) = 0;

    std::vector<EntityHandle> entities;
};


struct AISystem : System
{
    virtual bool isValid(EntityHandle e) const override
    {
        return e->isAttached(AIComponent_Type);
    }

    virtual void updateEntity(EntityHandle e, float dt) override
    {
        // update AI
        if (e->SpriteComponent.isEnabled())
        {
            //...
        }
    }
};

struct SystemRegistry
{
    void add(EntityHandle e)
    {
        for (auto pSystem : systems)
        {
            pSystem->add(e);
        }
    }

    void remove(EntityHandle e)
    {
        for (auto pSystem : systems)
        {
            pSystem->remove(e);
        }
    }

    std::vector<System*> systems;
};

struct AIDirector
{
    void SpwanGoobas()
    {
        EntityHandle goombaEntity = registry.createEntity("goomba");
        goombaEntity->attach(new SpriteComponent{ "goomba-spite", ... });

        SystemRegistry::add(goombaEntity);
        RenderingSystem::add(goombaEntity);
        RenderingSystem::remove(goombaEntity);
    }
};

