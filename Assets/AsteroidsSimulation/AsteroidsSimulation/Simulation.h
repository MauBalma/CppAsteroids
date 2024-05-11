#pragma once

#include "engine/Bindings.h"
#include "engine/Math.hpp"
#include "engine/UnmanagedArray.h"
#include "entt/entity/registry.hpp"

//[[EXPORT]]
struct SimulationSettings
{
    Math::float2 mapSize;
    Math::float2 asteroidSizeRange;
    Math::float2 asteroidSpeedRange;
    float initialAsteroidCount;

    float shipRotationSpeed;
    float shipAcceleration;
};

//[[EXPORT]]
struct UserInputCommand
{
    Math::float2 steer;
};

//[[EXPORT]]
struct Body
{
    float radius;
    float rotation;
    Math::float2 position;
    Math::float2 velocity;
    Math::float2 acceleration;
};

struct Ship
{
    Math::float2 steer;
};

struct Simulation
{
    float dt;
    SimulationSettings settings;
    
    entt::registry registry;

    entt::entity spawnBody(float radius, Math::float2 position, Math::float2 velocity);
    
    void spawnRandomAsteroid(SimulationSettings settings);
    void spawnInitialAsteroids(SimulationSettings settings);

    void spawnShip(SimulationSettings settings);
    
    void moveBodies(float dt);
    void updateShip(float dt);
};

/*[[EXPORT]]*/ DLL void* instantiate(SimulationSettings settings);
/*[[EXPORT]]*/ DLL void update(void* ptr);
/*[[EXPORT]]*/ DLL void dispose(void* ptr);
/*[[EXPORT]]*/ DLL void sendCommand(void* ptr, UserInputCommand cmd);
/*[[EXPORT]]*/ DLL UnmanagedArray getBodyEntities(void* ptr);
/*[[EXPORT]]*/ DLL Body getBody(void* ptr, entt::entity entity);
