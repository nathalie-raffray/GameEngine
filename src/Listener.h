#pragma once

template<typename T>
struct Listener
{
	Listener();
	virtual ~Listener();
	virtual void handle(const T& event) {}

	void activate();
	void deactivate();
};