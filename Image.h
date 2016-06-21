/*
	Class used to manipulate an image (like the bump map)
*/
#pragma once
#include "Color.h"
#include <memory>

class Image
{
public:

	// Constructors
	Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }
	Image(const unsigned int _w, const unsigned int _h, const Color &c = Color(0.0f, 0.0f, 0.0f)) : w(_w), h(_h), pixels(nullptr)
	{
		this->pixels = shared_ptr<Color>(new Color[this->w * this->h], [](Color* p) { delete[] p; });
		for (unsigned int i = 0; i < this->w * this->h; ++i) this->pixels.get()[i] = c;
	}

	// Operators
	inline const Color& operator [] (const unsigned int i) const { return this->pixels.get()[i]; }	// reading only
	inline Color& operator [] (const unsigned int i) { return this->pixels.get()[i]; } // reading and writting

	// Manipulations on images
	inline unsigned int getWidth() const { return this->w; }
	inline unsigned int getHeight() const { return this->h; }
	void readPPM(const char* file);
	bool isDefined() const { return pixels ? true : false; }	// return true if the pointer pixels is defined

private:
	unsigned int w, h; // image resolution
	shared_ptr<Color> pixels; // 1D array of pixels (shared because one or several Material can use it)
};