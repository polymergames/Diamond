/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Time.h"

#include <memory>

#include "D_Timer.h"

namespace Diamond {
	namespace Time {
		float fps;
		
		static std::unique_ptr<Timer> timer = nullptr;
	}
}

uint32_t Diamond::Time::msElapsed() {
	return timer->msElapsed();
}

void Diamond::Time::setTimer(Timer *timer) {
	if (Time::timer == nullptr && timer != nullptr)
		Time::timer = std::unique_ptr<Timer>(timer);
}
