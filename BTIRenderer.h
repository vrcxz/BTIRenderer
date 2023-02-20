#ifndef BTIRenderer_h
#define BTIRenderer_h
using namespace std;

namespace BTI
{
//my own renderer
class draw
{
  public:
	SDL_Window *window = SDL_CreateWindow("test", 0, 0, WIDTH, HEIGHT, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
	TTF_Font *font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", 256);

	vector<function<void()>> renderVector;

	void addCopy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst)
	{
		renderVector.push_back([=] { SDL_RenderCopy(renderer, texture, src, dst); });
	}

	void addShape(SDL_Color color, SDL_Rect *rect)
	{
		renderVector.push_back([=] {
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(renderer, rect);
		});
	}

	void swapVector(int index, SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst)
	{
		renderVector.at(index) = [=] { SDL_RenderCopy(renderer, texture, src, dst); };
	}

	void removeVector()
	{
		renderVector.pop_back();
	}

	//store all to buffer
	void render()
	{
		for (auto &looper : renderVector)
		{
			looper();
		}
	}

	void renderOutput()
	{
		SDL_RenderPresent(renderer);
	}

	void clear_render()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}

	void clear_renderVector()
	{
		renderVector.clear();
	}
};

//WIDGETS Classes

//box class
class box
{
  public:
	int x, y, w, h;
	SDL_Rect rect;

	box(SDL_Renderer *renderer, int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
	{
		rect = {x, y, w, h};
	}
};

//text class
class text
{
  public:
	int x, y, w, h, scale = 1;
	SDL_Renderer *renderer;
	SDL_Rect rect;
	SDL_Color color;
	SDL_Texture *texture;
	TTF_Font *font;
	string t;

	text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, std::string t, int x, int y, int scale) : renderer(renderer), font(font), color(color), t(t), x(x), y(y), w(w), h(h), scale(scale)
	{
		SDL_Surface *surface = TTF_RenderText_Solid(font, t.c_str(), color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		w *= 0.1;
		w *= scale;
		h *= 0.1;
		h *= scale;
		rect = {x, y, w, h};
		SDL_FreeSurface(surface);
	}

	void setValue(string new_t)
	{
		t = new_t;
		SDL_Surface *surface = TTF_RenderText_Solid(font, t.c_str(), color);

		//destroy to make another text
		SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		w *= 0.1;
		w *= scale;
		h *= 0.1;
		h *= scale;
		rect.w = w;
		rect.h = h;
		SDL_FreeSurface(surface);
	}
};

//image class
class image
{
  public:
	int x, y, w, h, scale = 1;
	SDL_Renderer *renderer;
	SDL_Rect rect;
	SDL_Texture *texture;
	char *path;

	image(SDL_Renderer *renderer, char *path, int x, int y, int scale) : renderer(renderer), path(path), x(x), y(y), w(w), h(h), scale(scale)
	{
		SDL_Surface *surface = IMG_Load(path);
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		w *= 0.1;
		w *= scale;
		h *= 0.1;
		h *= scale;
		rect = {x, y, w, h};
		SDL_FreeSurface(surface);
	}
};

//end BTI namespace
}

#endif
