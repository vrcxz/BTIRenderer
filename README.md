# BTIRenderer
BTIRenderer (or Box, Text, and Image Renderer) is a single header, bare-bones SDL2 wrapper to ease the implementation of boxes, texts, images and rendering shapes and copies in SDL2, specifically made to be used in Cxxdroid.
## Setup
Download the header, add it to the same directory of your program and include the following libraries:
```cpp
//necessary standard libraries to include
#include <string>
#include <vector>

//include SDL library GUI
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//define macros for the window size
#define WIDTH 600
#define HEIGHT 600

//include the BTIRenderer wrapper
#include "BTIRenderer.h"
```
## Example
### Hello World!
To print a `Hello World!` text, do the following:
```cpp
//Initialize SDL and TTF
SDL_Init(SDL_INIT_EVERYTHING);
TTF_Init();
	
//Add context
BTI::draw ctx;
	
//create a text and add it to the renderer
BTI::text hello_text(ctx.renderer,ctx.font,{255,255,255},"Hello World!",0,0,3);
ctx.addCopy(hello_text.texture,NULL,&hello_text.rect);

//clear the screen
ctx.clear_render();
	
//render it to the buffer
ctx.render();
	
//render it to the screen
ctx.renderOutput();
	
//delay 1 second to view the program
SDL_Delay(1000);

```
![ss0](https://github.com/vonnogadas/BTIRenderer/raw/main/Untitled131_20230220223512.png)
---
### Bouncing DVD
```cpp
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
```
![ss1](https://github.com/vonnogadas/BTIRenderer/raw/main/ezgif.com-gif-to-mp4.gif)

#### Credits
[Von Ryan Nogadas](https://github.com/vonnogadas)
