#ifndef SDL_EXCEPTION_H
#define SDL_EXCEPTION_H

#include <exception>

#include <SDL.h>

class SDL_Exception : public std::exception
{
    const char* what() const throw() { return SDL_GetError(); }
};
#endif
