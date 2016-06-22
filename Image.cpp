/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file Image.cpp
* \brief Method to read a Image object from a file and store the data
*/
#include "Image.h"
#include <fstream>
#include <string>

void Image::readPPM(const char *filename)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
	try {
		if (ifs.fail()) { throw("Can't open input file"); }
		std::string header;
		int w, h, b;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
		ifs >> w >> h >> b;
		this->w = w; this->h = h;
		this->pixels.reset(new Color[this->w * this->h], [](Color* p) { delete[] p; });	// we reset the array and recreate one with the right data
		ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
		unsigned char pix[3];
		// read each pixel one by one and convert bytes to floats
		for (int i = 0; i < w * h; ++i) {
			ifs.read(reinterpret_cast<char *>(pix), 3);
			this->pixels.get()[i] = Color(pix[0] / 255.f, pix[1] / 255.f, pix[2] / 255.f);
		}
		ifs.close();
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}
}