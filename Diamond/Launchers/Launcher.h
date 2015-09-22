/*
 Copyright (c) 2015 Polymer Games
 */

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <memory>

class Launcher {
	public:
	static void launch();
	virtual ~Launcher();

	private:
	static std::unique_ptr<Launcher> launcher;
};

#endif // LAUNCHER_H
