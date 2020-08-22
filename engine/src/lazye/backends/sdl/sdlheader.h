#pragma once

// This is to ensure SDL_MAIN_HANDLED is define before anyone includes SDL.h
// We're going to manage SDL's lifecycle manually in SDLSystem.h anyway
#define SDL_MAIN_HANDLED
#include <SDL.h>