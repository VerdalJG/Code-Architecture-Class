#pragma once
#include "Message.h"

class MovementMessage : public Message
{
public:
	MovementMessage(vec2 newPosition);
	vec2 newPosition;
};

