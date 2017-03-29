#ifndef __COLOR_H__
#define __COLOR_H__

struct color {
	int value;

	color() {}

	color(int r, int g, int b, int a = 0xff) {
		value = ((r & 0xff) |
				((g & 0xff) << 8) |
				((b & 0xff) << 16) |
				((a & 0xff) << 24));
	}

	color(int rgb) : value(rgb) {}
};

#endif // __COLOR_H__
