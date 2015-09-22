/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <memory>

class Graphics {
	public:
	static void setGraphics(std::unique_ptr<Graphics> graphics);
	virtual ~Graphics();

	private:
	static std::unique_ptr<Graphics> graphics;
};

#endif // GRAPHICS_H
