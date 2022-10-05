#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Updates the display.
//
// renderer: Renderer to draw on.
// texture: Texture that contains the image.
void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
}

// Event loop that calls the relevant event handler.
//
// renderer: Renderer to draw on.
// colored: Texture that contains the colored image.
// grayscale: Texture that contains the grayscale image.
void event_loop(SDL_Renderer* renderer, SDL_Texture* colored, SDL_Texture* grayscale)
{
    SDL_Event event;
    SDL_Texture* t = colored;

    while (1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
	    	return;
	    case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                	{
                    		draw(renderer, t);
			}
			break;
	    case SDL_KEYDOWN:
	    	draw(renderer,t);
		if (t == colored)
		{
			t = grayscale;
		}
		else{
			t = colored;
		}
	    	break;
        }
    }
}

// Loads an image in a surface.
// The format of the surface is SDL_PIXELFORMAT_RGB888.
//
// path: Path of the image.
SDL_Surface* load_image(const char* path)
{
    SDL_Surface * source = IMG_Load(path);
    return SDL_ConvertSurfaceFormat(source,SDL_PIXELFORMAT_RGB888,0);

}

// Converts a colored pixel into grayscale.
//
// pixel_color: Color of the pixel to convert in the RGB format.
// format: Format of the pixel used by the surface.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);

    //Uint32 color = SDL_MapRGB(format, r, g, b);

    Uint32 average = 0.3*r + 0.59*g + 0.11*b;

    r = g = b = average;
    return SDL_MapRGB(format, r, g, b);
}

void surface_to_grayscale(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;

    int len = surface->w * surface->h;

    SDL_PixelFormat* format = surface->format;

    SDL_LockSurface(surface);

    for (int i = 0; i < len; i++)
    {
    	pixels[i] = pixel_to_grayscale(pixels[i],format);
    }

    SDL_UnlockSurface(surface);
}

int main(int argc, char** argv)
{
    // Checks the number of arguments.
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    // TODO:
    // - Initialize the SDL.
    // - Create a window.
    // - Create a renderer.
    // - Create a surface from the colored image.
    // - Resize the window according to the size of the image.
    // - Create a texture from the colored surface.
    // - Convert the surface into grayscale.
    // - Create a new texture from the grayscale surface.
    // - Free the surface.
    // - Dispatch the events.
    // - Destroy the objects.
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a window.
    SDL_Window* window = SDL_CreateWindow("Image", 0, 0, 0, 0,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    // Creates a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface * surface = load_image(argv[1]);

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);

    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_SetWindowSize(window,w,h);


    surface_to_grayscale(surface);

    SDL_Texture * graytexture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface);

    event_loop(renderer,texture,graytexture);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();




    return EXIT_SUCCESS;
}
