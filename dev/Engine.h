#ifndef ENGINE_H
#define	ENGINE_H

#include <string>
#include <sstream>
#include "Timer.h"
#include "Entity.h"

using namespace std;

class TMaterial{
public:
    TMaterial();
    TMaterial(string, SDL_Surface* Top);
    string MaterialName;    
    SDL_Surface* TopTexture;
    SDL_Surface* SideTexture;  
    bool isDecoration;
};

class Engine{
public: 
    int LevelH;
    int LevelW;
    struct TCell{
    TMaterial Material;
    bool isBlock;
    bool isDecorationOn;
    TMaterial Decoration;
    };
    SDL_Surface * screen;
    SDL_Rect camera;
    const static int MapSize = 128;
    TCell Map[MapSize][MapSize];
    TMaterial Materials[256];
    TMaterial Decorations[256];
    string BasePath;    
    SDL_Event GameEvent;
    Entity Player;
    SDL_Surface * dot;
    bool RenderQueryEmpty;
    int MainLoop();
    void LoadLevel();
    void CreateLevel();
    string PrintKeyInfo(SDL_KeyboardEvent *key);
    int FindMaterialID(string Name);
    TMaterial AddNewMaterial(string Name, string FileName);
    void RenderScene();
    void RenderDecorations();
    void Apply_Surface(float x, float y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
    TCell SetCell(string MaterialName, bool Block, int MaterialNumber, bool isDecoration);
    TCell TCellCreate(TMaterial Material, bool Block, bool isDecoration);
    void HandleInput();
    void MovePlayer(Uint32 ticks);
    void Log(string Message);
    void SetCamera(Entity Ent);
    bool IsFileExists(string FileName);
    SDL_Surface* MaterialToRawSurface(TMaterial Material);
};

#endif	/* ENGINE_H */

