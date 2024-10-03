# Asteroids #

A clone of Asteroids using C++ and SDL.

## Build instructions ##

### Linux ###

You need: 
* git
* CMake (3.27+)
* GCC 10.1+ (must support C++20 for \<numbers>)

```
git clone --recursive https://github.com/danelbro/asteroids-sdl.git asteroids
cd asteroids
./config.sh
./build.sh
./run.sh
```

### Windows ###

To play, you can grab a release for the binary - just unzip and run asteroids.exe, ensuring that the .exe is in the same folder as the 'data' directory.

Otherwise:

```
git clone --recursive https://github.com/danelbro/asteroids-sdl.git asteroids
```

If you use Visual Studio with CMake support, you should then be able to open the folder to build and run it.

I recommend the following CMake options (these are baked into the .config.sh script):

```
BUILD_SHARED_LIBS=OFF
SDLTTF_VENDORED=ON	// requires that the repository is cloned recursively - otherwise you'll need SDL_ttf installed on your system
SDL_TEST_LIBRARY=OFF
```

Using MinGW you should be able to build by following the Linux instructions. It won't build with Cygwin as it is no longer supported by SDL. 
