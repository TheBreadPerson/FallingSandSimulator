#include <util.h>

Color color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	Color temp_color;
	temp_color.r = r;
	temp_color.g = g;
	temp_color.b = b;
	temp_color.a = a;
	return temp_color;
}