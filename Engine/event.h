#pragma once
#include "id.h"
#include "varient.h"

class Entity;

struct Event
{
	ID eventID;
	Entity* sender;
	Entity * receiver;
	Varient varient;

	Event() {}
};