#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include "Engine.h"

using namespace std;


int main( int argc, char* args[] ){  
    Engine eng; 
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) cout << "SDL OK" << endl; else cout << "SDL init failed" << endl;
    cout << "Ti lalka" << endl;
    //if (eng.Fullscreen) eng.screen = SDL_SetVideoMode(960, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //else eng.screen = SDL_SetVideoMode(960, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    eng.screen = SDL_SetVideoMode(1280, 1024, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF);
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    eng.BasePath = cwd;
    cout << "PATH: " << eng.BasePath << endl;
    cout << "Starting game..." << endl;
    eng.MainLoop();
    return 0;
}
