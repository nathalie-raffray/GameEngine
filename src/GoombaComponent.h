#pragma once
#include <SFML/System/Vector2.hpp>

template<typename T>
using Vector2 = sf::Vector2<T>;

struct GoombaComponent
{
	
};

struct RigidBody
{
	bool direction; //is it moving left or right in this frame 
	//(can be used as starting direction for ai, or which way mario faces).
	//note: even a paragoomba or koopa paratroopa which hops, moves only left or right essentially.
	float speed;
	enum FallType
	{
		discrete, continuous, disabled //goombas fall discretely, red shells fall with physics as does mario
	};
	FallType fall_type;
};

//koopa paratroopa can jump off platforms
struct HopComponent
{

};

struct DynamicSpawnComponent
{
	unsigned int rightThreshold = ~0; //relative to camera screencoord0
	unsigned int leftThreshold = ~0;
	
	Vector2<int> spawnPos_fromRight; //relative to player
	Vector2<int> spawnPos_fromLeft;

	//once out of screen by a set amount, dynamicenemy is inactive
	//now we listen for leftthreshold and rightthreshold for all inactive entities w/dynamicenemy component
	//if the entity is killed (health = 0) then we automatically wont listen for leftthreshold and right
};

struct HealthComponent
{
	unsigned int health;
	unsigned int maxHealth;
};

struct EnemyAreaComponent
{
	unsigned int rightThreshold;
	unsigned int leftThreshold;

	unsigned int numEnemies;

};

struct EnemyRightAreaComponent
{
	unsigned int numGoombas;
};

struct EnemyLeftAreaComponent
{

};