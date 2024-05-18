/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Rect.h
Description : a rectangle container class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once

class Rect
{
public:
	Rect() {}
	Rect(int width, int height):width(width), height(height) {}
	Rect(int left, int top, int width, int height):left(left), top(top), width(width), height(height) {}
	Rect(const Rect& rect):left(rect.left), top(rect.top), width(rect.width), height(rect.height) {}

public:
	int width = 0, height = 0, left = 0, top = 0;
};
