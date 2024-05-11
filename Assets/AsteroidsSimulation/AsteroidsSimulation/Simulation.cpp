#include "Simulation.h"
#include "engine/Random.hpp"

void* instantiate(SimulationSettings settings)
{
    try
    {
        const auto simulation = new Simulation();
        simulation->dt = 1.0f/60;
        simulation->settings = settings;
    
        Random::setSeed(666);
    
        simulation->spawnInitialAsteroids(settings);
        simulation->spawnShip(settings);

        return simulation;
    }
    catch (const std::exception& e)
    {
        logError(const_cast<char*>(e.what()));
    }
}

void update(void* ptr)
{
    try
    {
        const auto simulation = static_cast<Simulation*>(ptr);
        simulation->updateShip(simulation->dt);
        simulation->moveBodies(simulation->dt);
    }
    catch (const std::exception& e)
    {
        logError(const_cast<char*>(e.what()));
    }
}

void dispose(void* ptr)
{
    try
    {
        const auto simulation = static_cast<Simulation*>(ptr);
        
        //???
    
        delete simulation;
    }
    catch (const std::exception& e)
    {
        logError(const_cast<char*>(e.what()));
    }
}


void sendCommand(void* ptr, UserInputCommand cmd)
{
    try
    {
        const auto simulation = static_cast<Simulation*>(ptr);
        const auto view = simulation->registry.view<Ship>();
        
        for (auto entity : view)
        {
            auto& steer = view.get<Ship>(entity);
            steer.steer = cmd.steer;
        }
    }
    catch (const std::exception& e)
    {
        logError(const_cast<char*>(e.what()));
    }
}

UnmanagedArray getBodyEntities(void* ptr)
{
    try
    {
        const auto simulation = static_cast<Simulation*>(ptr);
        const auto group = simulation->registry.group<Body>();
    
        const auto entities = (void*)group.storage<Body>()->data();
        const auto length = group.size();

        const auto sizeOf = sizeof(entt::entity);
        const auto alignOf = alignof(entt::entity);

        return UnmanagedArray{entities, length, sizeOf, alignOf};
    }
    catch (const std::exception& e)
    {
        logError(const_cast<char*>(e.what()));
    }
}

Body getBody(void* ptr, entt::entity entity)
{
    try
    {
        const auto simulation = static_cast<Simulation*>(ptr);
        return simulation->registry.get<Body>(entity);
    }
    catch (const std::exception& e)
    {
        logError(const_cast<char*>(e.what()));
    }
}

entt::entity Simulation::spawnBody(float radius, Math::float2 position, Math::float2 velocity)
{
    auto entity = registry.create();
    
    Body b{};
    b.radius = radius;
    b.position = position;
    b.velocity = velocity;
    
    registry.emplace<Body>(entity, b);

    return entity;
}

void Simulation::spawnRandomAsteroid(SimulationSettings settings)
{
    auto x = Random::range(settings.mapSize.x);
    auto y = Random::range(settings.mapSize.y);
    auto position = Math::float2{x, y};

    auto angle = Random::range(2 * 3.1416f);
    auto speed = Random::range(settings.asteroidSpeedRange.x, settings.asteroidSpeedRange.y);
    auto velocity = Math::float2{cos(angle), sin(angle)} * speed;

    auto radius = Random::range(settings.asteroidSizeRange.x, settings.asteroidSizeRange.y);
        
    spawnBody(radius, position, velocity);
}

void Simulation::spawnInitialAsteroids(SimulationSettings settings)
{
    for (int i = 0; i < settings.initialAsteroidCount; ++i)
    {
        spawnRandomAsteroid(settings);
    }
}

void Simulation::spawnShip(SimulationSettings settings)
{
    auto radius = 0.25f;
    auto position = settings.mapSize / 2.0f;
    auto velocity = Math::float2{};
    
    auto entity = spawnBody(radius, position, velocity);
    
    this->registry.emplace<Ship>(entity);
}

void Simulation::moveBodies(const float dt)
{
    const auto group = registry.group<Body>();    
    for (const auto entity : group)
    {
        auto& b = group.get<Body>(entity);
    
        b.position = b.position + b.velocity * dt;
        b.position += b.velocity * dt;
    
        if(b.position.x < 0) b.position.x += settings.mapSize.x;
        if(b.position.x >= settings.mapSize.x) b.position.x -= settings.mapSize.x;
    
        if(b.position.y < 0) b.position.y += settings.mapSize.y;
        if(b.position.y >= settings.mapSize.y) b.position.y -= settings.mapSize.y;
    }
}

void Simulation::updateShip(float dt)
{
    const auto group = registry.group<Ship>(entt::get<Body>);
    for (auto entity : group)
    {
        auto& ship = group.get<Ship>(entity);
        auto& body = group.get<Body>(entity);
        body.rotation += settings.shipRotationSpeed * 2 * 3.1416f * -ship.steer.x * dt;

        auto direction = Math::float2{cos(body.rotation), sin(body.rotation)} ;
        body.velocity += direction * settings.shipAcceleration * ship.steer.y * dt;
    }
}