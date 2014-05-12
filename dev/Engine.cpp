#include "Engine.h"
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "ConfigReader.h"

using namespace std;

const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 20;
const int PLAYER_VEL = 200;

Timer delta;
    
void Engine::Log(string Message) {
    cout << __FILE__ << ":" << __LINE__ << ": " << Message << endl;

}

bool Engine::IsFileExists(string FileName) {
    {
        ifstream infile(FileName.c_str());
        return infile.good();
    }
}

void Engine::HandleInput() {
    if (GameEvent.type == SDL_KEYDOWN) {
        switch (GameEvent.key.keysym.sym) {
            case SDLK_UP: Player.yVel -= PLAYER_VEL;
                break;
            case SDLK_DOWN: Player.yVel += PLAYER_VEL;
                break;
            case SDLK_LEFT: Player.xVel -= PLAYER_VEL;
                break;
            case SDLK_RIGHT: Player.xVel += PLAYER_VEL;
                break;
            case SDLK_SPACE: Player.onGround = false;
        }
    } else if (GameEvent.type == SDL_KEYUP) {
        switch (GameEvent.key.keysym.sym) {
            case SDLK_UP: Player.yVel += PLAYER_VEL;
                break;
            case SDLK_DOWN: Player.yVel -= PLAYER_VEL;
                break;
            case SDLK_LEFT: Player.xVel += PLAYER_VEL;
                break;
            case SDLK_RIGHT: Player.xVel -= PLAYER_VEL;
                break;
        }
    }
}

void Engine::LoadLevel(){
    srand(time(NULL));
    string LevelName;
    string Material;
    int type1;
    LevelName = BasePath + "/resources/levels/level1.lvl";
    LevelH = 32 * MapSize;
    LevelW = 32 * MapSize;
    ifstream MapFile(LevelName.c_str());
    if (MapFile) {
        for (int i = 0; i < MapSize; i++) {
            for (int j = 0; j < MapSize; j++) {
                MapFile >> Material >> type1;
                Map[i][j] = TCellCreate(Materials[FindMaterialID(Material)], type1, false);
            }            
        }
         for (int i = 0; i < MapSize; i++) {
            for (int j = 0; j < MapSize; j++) {
                int DecoChance = (rand() % 100) + 1;
                if(DecoChance > 60 && Map[i][j+2].isBlock && !Map[i][j+1].isBlock){
                    cout << DecoChance << endl;
                    Map[i][j].isDecorationOn = true;
                    Map[i][j].Decoration = Decorations[0];
                }
            }           
        }
    }
}

int Engine::FindMaterialID(std::string Name) {
    for (int i = 0; i < 256; i++) {
        if (Materials[i].MaterialName == Name) return i;
        else continue;
        return -1;
    }
}

Engine::TCell Engine::SetCell(std::string Material1, bool Block, int MaterialNumber = NULL, bool isDecoration = false) {
    if (Material1 != "random") {
        switch (FindMaterialID(Material1)) {
            case -1:
                cout << "Material """ << Material1 << """ doesn't exists" << endl;
            default:
                return TCellCreate(Materials[FindMaterialID(Material1)], Block, isDecoration);
        }
    } else {
        cout << MaterialNumber << endl;
        return TCellCreate(Materials[MaterialNumber], false, isDecoration);
    }

}

TMaterial Engine::AddNewMaterial(string Name, string FileName) {
    SDL_Surface * Texture;
    if (IsFileExists(FileName)) {
        Texture = SDL_DisplayFormatAlpha(IMG_Load(FileName.c_str()));
    } else {
        string DefaultFile = "./resources/textures/empty.bmp";
        Texture = SDL_DisplayFormatAlpha(IMG_Load(DefaultFile.c_str()));
        cerr << "Texture for material \"" << Name << "\" not found. Using default texture" << endl;

    }
    return TMaterial(Name, Texture);

}

void Engine::Apply_Surface(float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}

TMaterial::TMaterial() {
}

TMaterial::TMaterial(string Name, SDL_Surface* Top) {
    MaterialName = Name;
    TopTexture = Top;
    cout << "New material added. Name: " << Name << endl;
}

Engine::TCell Engine::TCellCreate(TMaterial Material, bool Block, bool isDecoration) {
    TCell Cell;
    Cell.Material = Material;
    Cell.isBlock = Block;
    Cell.isDecorationOn = isDecoration;
    return Cell;
}

int Engine::MainLoop() {
    bool playing = true;
    int FPS = 25;
    int frame = 0;
    Timer fps;
    Player = Entity();
    Player.x = 720;
    Player.y = 440;
    Player.xVel = 0;
    Player.yVel = 0;
    Player.JumpSpeed = 200;
    camera.x = 0;
    camera.y = 0;
    camera.w = screen->w;
    camera.h = screen->h;
    dot = SDL_DisplayFormatAlpha(IMG_Load("./resources/textures/playerl.png"));
    if (dot == NULL) cout << "ERR" << endl;
    cout << "Loading textures..." << endl;
    ConfigReader * ConfigRead = new ConfigReader(this);
    ConfigRead->ReadConfigs();
    cout << "Loading base level... ";
    LoadLevel();
    //CreateLevel();
    cout << "OK" << endl << "Size: " << MapSize << endl;
    cout << __FILE__ << ":" << __LINE__ << ": " << __func__ << "() finished OK." << endl;
    delta.start();
    while (playing) {
        fps.start();
        while (SDL_PollEvent(&GameEvent)) {
            HandleInput();

            if (GameEvent.type == SDL_QUIT) {
                playing = false;
                SDL_Quit;
                break;
            }
            if (GameEvent.type == SDL_MOUSEMOTION) {
                int x = GameEvent.motion.x;
                if (x < camera.x) dot = SDL_DisplayFormatAlpha(IMG_Load("./resources/textures/playerl.png"));
                if (x > camera.x) dot = SDL_DisplayFormatAlpha(IMG_Load("./resources/textures/playerr.png"));

            }
            if (GameEvent.type == SDL_KEYDOWN) {
                switch (GameEvent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        playing = false;
                        SDL_Quit();
                        cout << __FILE__ << ":" << __LINE__ << ": Closed by user." << endl;
                        break;
                }
            }
        }
        if (playing) {            
            MovePlayer(delta.get_ticks());    
            delta.stop();
            delta.start();
            SDL_Flip(screen);
            if(Player.onGround) cout << "On gr"; else cout << "Not on gr";
            if (fps.get_ticks() < 1000 / FPS) {
                SDL_Delay((1000 / FPS) - fps.get_ticks());
            }
            SDL_Flip(screen);
        }
    }
}

void Engine::MovePlayer(Uint32 deltaTicks) {
    float CurrentX = Player.x;
    float CurrentY = Player.y;
  
    int CurrentCellX = Player.x / 32;
    int CurrentCellY = Player.y / 32; 
    Player.x = Player.x + Player.xVel * (deltaTicks / 1000.f);
    cout << CurrentCellX << ":" << CurrentCellY << endl;
    if (Map[CurrentCellX][CurrentCellY + 1].isBlock) Player.onGround = true; else Player.onGround = false;
    if(Player.onGround){ 
        if(Map[CurrentCellX][CurrentCellY + 1].isBlock){ 
        Player.onGround = true;
        cout << "123";
        //Player.y += Player.yVel * (deltaTicks / 1000.f); 
        cout << CurrentCellX << ":" << CurrentCellY << endl;
    } else Player.y = CurrentY; 
    } else {
        while(!Player.onGround){
       //     HandleInput();
         //   Player.x = Player.x + Player.xVel * (deltaTicks / 1000.f);
               Player.y = Player.y + 15;
               
               SetCamera(Player);
               Apply_Surface(round(Player.x - camera.x) + 10, round(Player.y - camera.y) + 10, dot, screen, NULL);
               SDL_Flip(screen);
               SDL_Delay(50);
               if (Map[CurrentCellX][CurrentCellX].isBlock) Player.onGround = true; else Player.onGround = false;
           
       } 
       cout << "end" << endl; 
    }
    if(Player.x != CurrentX || Player.y != CurrentY){
    RenderScene();
    RenderDecorations();
    }
}

void Engine::CreateLevel() {
    srand(time(NULL));
    LevelH = 32 * MapSize;
    LevelW = 32 * MapSize;
    for (int i = 0; i < MapSize; i++) {
        for (int j = 0; j < MapSize; j++) {
            int MaterialNumber = rand() % 2;
            Map[i][j] = TCellCreate(Materials[MaterialNumber], false, false);
            int DecoChance = (rand() % 100) + 1;
            if(DecoChance > 95){
                Map[i][j] = TCellCreate(Materials[MaterialNumber], true, true);
                Map[i][j].Decoration = Decorations[0];
            }
        }

    }
}

void Engine::SetCamera(Entity Ent) {
    camera.x = trunc((Ent.x + dot->w / 2) - screen->w / 2);
    camera.y = trunc((Ent.y + dot->h / 2) - screen->h / 2);
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > LevelW - camera.w) {
        camera.x = LevelW - camera.w;
    }
    if (camera.y > LevelH - camera.h) {
        camera.y = LevelH - camera.h;
    }
}
