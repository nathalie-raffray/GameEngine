#pragma once

template<typename T>
using Vector2 = sf::Vector2<T>;

struct CameraComponent
{
	Vector2<int> aspectRatio;
	Vector2<int> screenCoord0; //top lefthand coords
	Vector2<int> screenCoord1; //bottom righthand coords
};