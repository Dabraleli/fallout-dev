#include "Engine.h"
#include "iostream"
#include <math.h>

void Engine::RenderScene() {
    float CurrentCellX = Player.x / 32;
    float CurrentCellY = Player.y / 32;
    float LeftTopX = CurrentCellX - (screen->w / 32) / 2;
    float LeftTopY = CurrentCellY - (screen->h / 32) / 2;
    float RightBotX = CurrentCellX + (screen->w / 32) / 2;
    float RightBotY = CurrentCellY + (screen->h / 32) / 2 + 1;
    if(!RenderQueryEmpty){
    for (int i = LeftTopX; i < RightBotX; i++) {
        for (int j = LeftTopY; j < RightBotY; j++) {
            Apply_Surface((0 + Map[i][j].Material.TopTexture->w)*(i - LeftTopX), (0 + Map[i][j].Material.TopTexture->h)*(j - LeftTopY), Map[i][j].Material.TopTexture, screen, NULL);
        }
    }
    SetCamera(Player);  
    Apply_Surface(round(Player.x - camera.x) + 10, round(Player.y - camera.y) + 10, dot, screen, NULL);
    }
}

void Engine::RenderDecorations() {
    float CurrentCellX = Player.x / 32;
    float CurrentCellY = Player.y / 32;
    float LeftTopX = CurrentCellX - (screen->w / 32) / 2;
    float LeftTopY = CurrentCellY - (screen->h / 32) / 2;
    float RightBotX = CurrentCellX + (screen->w / 32) / 2;
    float RightBotY = CurrentCellY + (screen->h / 32) / 2 + 1;
    if(!RenderQueryEmpty){
    for (int i = LeftTopX; i < RightBotX; i++) {
        for (int j = LeftTopY; j < RightBotY; j++) {
        int BaseX = (i * 32 + Map[i][j].Decoration.TopTexture->w) - i * 32;
        int BaseY = (j * 32 + Map[i][j].Decoration.TopTexture->h) - j * 32;
        if(Map[i][j].isDecorationOn){// && Map[i][j+3].isBlock && !Map[i][j].isBlock){
            Apply_Surface((0 + Map[i][j].Material.TopTexture->w)*(i - LeftTopX), (0 + Map[i][j].Material.TopTexture->h)*(j - LeftTopY - 1), Map[i][j].Decoration.TopTexture, screen, NULL);
        }  
        }
    }
}
}
