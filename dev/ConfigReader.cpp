/* 
 * File:   ConfigReader.cpp
 * Author: dabraleli
 * 
 * Created on 10 Май 2014 г., 9:34
 */

#include <fstream>
#include <iostream>
#include <string>
#include <SDL/SDL.h>


#include "ConfigReader.h"

using namespace std;

ConfigReader::ConfigReader() {
    
}

ConfigReader::ConfigReader(Engine * Par){
    Parent = Par;
}


ConfigData ConfigReader::ReadConfigs(){
    
    std::ifstream RootConfig("./resources/RootConfig.cfg");
    if(RootConfig){
    cout << "Root config exists. Reading..." << endl; 
    while(!RootConfig.eof()){
      string Name, Path;
      int MagicNumber;
      RootConfig >> Name >> MagicNumber >> Path;
      switch(MagicNumber){
          case 2:
              ReadTextures(Path);
              break;
          case 3:
              ReadDecorations(Path);
              break;
      }
      
    }  
    } else {
        cout << "No config. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    
}


void ConfigReader::ReadTextures(std::string Path){
    std::ifstream TexturesConfig(Path.c_str());
    int Count = 0;
    if(TexturesConfig){
        cout << "Reading textures..." << endl;
        while(!TexturesConfig.eof()){
            string Name, Path;
            TexturesConfig >> Name >> Path;
            Parent->Materials[Count] = Parent->AddNewMaterial(Name, Path);
            Count++;  
        }
        cout << "Added " << Count << " new materials." << endl;
        cout << "Textures loading finished." << endl;
    } else {
        cout << "No textures to read. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    
    
}


void ConfigReader::ReadDecorations(std::string Path){
    std::ifstream DecoConfig(Path.c_str());
    int Count = 0;
    if(DecoConfig){
        cout << "Reading decorations..." << endl;
        while(!DecoConfig.eof()){
            string Name, Path;
            DecoConfig >> Name >> Path;
            Parent->Decorations[0] = Parent->AddNewMaterial(Name, Path);
            Count++;  
        }
        cout << "Added " << Count << " new decorations." << endl;
        cout << "Decorations loading finished" << endl;
    } else {
        cout << "No decoraions to read. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    
    
}