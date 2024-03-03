#pragma once

#include "Rect.h"

class Window
{
public:
	Window();
	~Window();

	Rect getInnerSize();

	void makeCurrentContext();
	void present(bool vsync);
private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
	Rect m_size = Rect(1024, 768);
};

