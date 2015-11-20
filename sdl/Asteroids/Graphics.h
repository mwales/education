#pragma once

#include <stdint.h>
#include <string>

#include <SDL2/SDL.h>

#include "GameMath.h"

class Graphics
{
public:
   Graphics(uint32_t initFlags = SDL_INIT_EVERYTHING);

   ~Graphics();

   void CreateWindow(char const * title, int width, int height, uint32_t flags = SDL_WINDOW_OPENGL);

   void Clear();

   void Render() { SDL_RenderPresent(_renderer); }

   inline SDL_Renderer* GetRenderer() { return _renderer; }

   inline SDL_Window* GetWindow() { return _window; }

   XYPair GetWindowSize();

protected:
   SDL_Window* _window;

   SDL_Renderer* _renderer;

   XYPair _windowSize;


};
