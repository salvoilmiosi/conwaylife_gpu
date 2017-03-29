#include "sources.h"

/// VERTEX SHADER ///

const char *const SOURCE_VERTEX =
R"SOURCE_VERTEX(#version 100

precision highp float;

attribute vec2 position;

varying vec2 tex_coords;

void main() {
	gl_Position = vec4(position, 0.0, 1.0);

	tex_coords = position * 0.5 + 0.5;
}
)SOURCE_VERTEX";

/// INIT FRAGMENT SHADER ///

const char *const SOURCE_INIT =
R"SOURCE_INIT(#version 100

precision highp float;

varying vec2 tex_coords;

uniform sampler2D start_pattern;

void main() {
	gl_FragColor = texture2D(start_pattern, tex_coords);
}
)SOURCE_INIT";

/// STEP FRAGMENT SHADER ///

const char *const SOURCE_STEP =
R"SOURCE_STEP(#version 100

precision highp float;

uniform sampler2D in_texture;

uniform vec2 texel_size;

varying vec2 tex_coords;

void main() {
	int num_alive = 0;
	bool cell_alive = false;
	for (int x=-1; x<=1; ++x) {
		for (int y=-1; y<=1; ++y) {
			bool b = texture2D(in_texture, tex_coords + vec2(float(x) * texel_size.x, float(y) * texel_size)).r > 0.0;
			if (x==0 && y==0) {
				cell_alive = b;
			} else {
				num_alive += int(b);
			}
		}
	}
	if (cell_alive) {
		if (num_alive <= 2 || num_alive >=4) {
			gl_FragColor = vec4(0.0);
		} else {
			gl_FragColor = vec4(1.0);
		}
	} else if (num_alive == 3) {
		gl_FragColor = vec4(1.0);
	} else {
		gl_FragColor = vec4(0.0);
	}
}
)SOURCE_STEP";

/// DRAW FRAGMENT SHADER ///

const char *const SOURCE_DRAW =
R"SOURCE_DRAW(#version 100

precision highp float;

uniform sampler2D in_texture;
varying vec2 tex_coords;

const vec4 color_alive = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 color_dead  = vec4(0.0, 0.0, 0.0, 1.0);

void main() {
	bool alive = texture2D(in_texture, tex_coords).r > 0.0;
	gl_FragColor = alive ? color_alive : color_dead;
}
)SOURCE_DRAW";


