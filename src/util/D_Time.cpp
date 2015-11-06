/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Time.h"

#include <memory>

#include "D_Timer.h"

namespace Diamond {
	namespace Time {
		std::unique_ptr<Timer> timer = nullptr;
	}
}

void Diamond::Time::set_timer(Timer *timer) {
	if (Time::timer == nullptr && timer != nullptr)
		Time::timer = std::unique_ptr<Timer>(timer);
}
