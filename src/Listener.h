#pragma once

template<typename T>
struct Listener
{
	Listener();
	virtual ~Listener();
	virtual void handle(const T& event) = 0;

	void activate();
	void deactivate();
};