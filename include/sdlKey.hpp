/* Character to SDL_Keycode */

#include <SDL.h>
#include <cctype>

using std::tolower;

Uint8 getSDLKey(const std::string name) {
    if (name.length() == 1) {
	char c = name[0];
	if (tolower(c) == 'a') return SDLK_a;
	if (tolower(c) == 'b') return SDLK_b;
	if (tolower(c) == 'c') return SDLK_c;
	if (tolower(c) == 'd') return SDLK_d;
	if (tolower(c) == 'e') return SDLK_e;
	if (tolower(c) == 'f') return SDLK_f;
	if (tolower(c) == 'g') return SDLK_g;
	if (tolower(c) == 'h') return SDLK_h;
	if (tolower(c) == 'i') return SDLK_i;
	if (tolower(c) == 'j') return SDLK_j;
	if (tolower(c) == 'k') return SDLK_k;
	if (tolower(c) == 'l') return SDLK_l;
	if (tolower(c) == 'm') return SDLK_m;
	if (tolower(c) == 'n') return SDLK_n;
	if (tolower(c) == 'o') return SDLK_o;
	if (tolower(c) == 'p') return SDLK_p;
	if (tolower(c) == 'q') return SDLK_q;
	if (tolower(c) == 'r') return SDLK_r;
	if (tolower(c) == 's') return SDLK_s;
	if (tolower(c) == 't') return SDLK_t;
	if (tolower(c) == 'u') return SDLK_u;
	if (tolower(c) == 'v') return SDLK_v;
	if (tolower(c) == 'w') return SDLK_w;
	if (tolower(c) == 'x') return SDLK_x;
	if (tolower(c) == 'y') return SDLK_y;
	if (tolower(c) == 'z') return SDLK_z;
    }
    return 0;
}
