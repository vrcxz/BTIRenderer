//necessary standard libraries to include
#include <string>
#include <vector>

//include SDL library to wrap
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//define macros for the window size
#define HEIGHT 600
#define WIDTH 600

//include the BTIRenderer wrapper
#include "BTIRenderer.h"

int main()
{
	//Initialize SDL and TTF
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	//Add context
	BTI::draw ctx;
	
	//create a text and add it to the renderer
	BTI::text hello_text(ctx.renderer,ctx.font,{255,255,255},"Hello World!",0,0,5);
	ctx.addCopy(hello_text.texture,NULL,&hello_text.rect);
	
	//clear the screen
	ctx.clear_render();
	
	//render it to the buffer
	ctx.render();
	
	//render it to the screen
	ctx.renderOutput();
	
	//delay 1 second to view the program
	SDL_Delay(1000);
}