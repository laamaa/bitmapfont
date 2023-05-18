#include "SDL_render.h"
#include "SDL_surface.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

//configure stuff here
const int bitmap_width = 128+8;
const int bitmap_height = 64+4;
const int spacing_x = 8;
const int spacing_y = 9;
const int pointsize= 12;
const char* fontfile = "m8stealth89.ttf";

int main(int argc, char **argv) {
  // Initialize SDL2
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  // Create an SDL window
  SDL_Window *window =
      SDL_CreateWindow("check out this font", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, bitmap_width*4, bitmap_height*4, 0);

  // Create a renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_RenderSetLogicalSize(renderer, bitmap_width, bitmap_height);

  // Open a font style and set its size
  TTF_Font *font = TTF_OpenFont(fontfile, pointsize);

  // Set the color of the text (white)
  SDL_Color White = {255, 255, 255};

  int column = 0;
  int row = 0;
  SDL_Surface *surfaceMessage;
  SDL_Texture *Message;
  SDL_Texture *maintex;
  maintex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET, bitmap_width, bitmap_height);
  SDL_SetRenderTarget(renderer, maintex);

  for (int i = 33; i < 127; i++) {
    char ascii[2];
    sprintf(ascii, "%c", i);
    //printf("%c", i);

    // Create a surface with the text
    surfaceMessage = TTF_RenderText_Solid(font, ascii, White);
    // Convert the surface into a texture
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    // Create a rect for the text
    SDL_Rect Message_rect;
    Message_rect.x = column * spacing_x;
    Message_rect.y = row * spacing_y;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;
    // Render the texture in the game loop
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    column++;
    if (column > 16) {
      column = 0;
      row++;
    }
  }

  SDL_Surface *bitmap = SDL_CreateRGBSurface(0, bitmap_width, bitmap_height, 32, 0, 0, 0, 0);
  SDL_RenderReadPixels(renderer, NULL, bitmap->format->format, bitmap->pixels, bitmap->pitch);
  SDL_SaveBMP(bitmap, "font.bmp");
  SDL_FreeSurface(bitmap);

  SDL_SetRenderTarget(renderer, NULL);
  SDL_Rect bitmap_rect = {0, 0, bitmap_width, bitmap_height};
  SDL_RenderCopy(renderer, maintex, NULL, &bitmap_rect);

  SDL_RenderPresent(renderer);
  int quit = 0;
  SDL_Event event;
  while (!quit) {
    if (SDL_WaitEvent(&event)) {
      if (event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN) {
        quit = 1;
      } 
    }
  }

  // Free the surface and texture
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
  SDL_DestroyTexture(maintex);
  TTF_CloseFont(font);

  // Quit SDL2
  TTF_Quit();
  SDL_Quit();
}