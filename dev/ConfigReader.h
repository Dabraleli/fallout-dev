#include "ConfigData.h"
#include "Engine.h"

#ifndef CONFIGREADER_H
#define	CONFIGREADER_H

#define CONFIGS 1
#define TEXTURES 2
#define DECORATIONS 3
#define ANIMATIONS 4

class ConfigReader {
public:
    ConfigReader();
    ConfigReader(Engine * Parent);
    ConfigData ReadConfigs();
    Engine * Parent;
    void ReadTextures(std::string Path);
    void ReadDecorations(std::string Path);
private:

};

#endif	/* CONFIGREADER_H */

