/*
Win32 compile:  mingw-g++ *.cpp *.h -lmingw32 -lSDLmain -lSDL -lSDL_image -mwindows 
Linux compile   g++ *.cpp *.h -lSDL -lSDL_image
 */


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include "Engine.h"


#ifdef _WIN32
#include <windows.h>
#include <direct.h>
int main( int argc, char *argv[] ){
#else
int main( int argc, char* args[] ){  
#endif
    using namespace std;
    Engine eng; 
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) cout << "SDL OK" << endl; else cout << "SDL init failed" << endl;
    cout << "Ti lalka" << endl;
    //if (eng.Fullscreen) eng.screen = SDL_SetVideoMode(960, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //else eng.screen = SDL_SetVideoMode(960, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    eng.screen = SDL_SetVideoMode(1280, 1024, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF);
    
    #ifdef _WIN32 
    char * cwd;
    cwd = _getcwd( NULL, 0 );
    #else
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    #endif    
        
    eng.BasePath = cwd;
    cout << "PATH: " << eng.BasePath << endl;
    cout << "Starting game..." << endl;
    eng.MainLoop();
    return 0;
}
