//necessary standard libraries to include
#include <string>
#include <vector>
#include <random>

//include SDL library to wrap
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//define macros for the window size
#define HEIGHT 1400
#define WIDTH 720

//include the BTIRenderer wrapper
#include "BTIRenderer.h"

int main()
{
	//Initialize SDL and TTF
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//Add context
	BTI::draw ctx;

	//declare variables for velocity
	int vx1 = 1, vy1 = 1;
	//create the DVD text and add it to the renderer
	BTI::text dvd1(ctx.renderer, ctx.font, {195, 255, 235}, "DVD", 0, 0, 5);
	ctx.addCopy(dvd1.texture, NULL, &dvd1.rect);

	int vx2 = -1, vy2 = -1;
	BTI::text dvd2(ctx.renderer, ctx.font, {255, 195, 235}, "DVD", 100, 500, 5);
	ctx.addCopy(dvd2.texture, NULL, &dvd2.rect);

	while (1)
	{
		//clear the screen
		ctx.clear_render();

		//update position
		dvd1.rect.x += vx1;
		dvd1.rect.y += vy1;

		dvd2.rect.x += vx2;
		dvd2.rect.y += vy2;

		//check collision
		if (dvd1.rect.x <= 0 || dvd1.rect.x + dvd1.rect.w >= WIDTH)
			vx1 = -vx1;
		if (dvd1.rect.y <= 0 || dvd1.rect.y + dvd1.rect.h >= HEIGHT)
			vy1 = -vy1;

		if (dvd2.rect.x <= 0 || dvd2.rect.x + dvd2.rect.w >= WIDTH)
			vx2 = -vx2;
		if (dvd2.rect.y <= 0 || dvd2.rect.y + dvd2.rect.h >= HEIGHT)
			vy2 = -vy2;

		//render it to the buffer
		ctx.render();

		//render it to the screen
		ctx.renderOutput();

		SDL_Delay(5);
	}
}
