#pragma once

#include <map>

#include "Scene.h"
#include "GraphicEntity.h"
#include "Command.h"
#include "Spaceship.h"

class ShootingScene : public Scene
{
public:
   ShootingScene(Graphics* g, Mixer* m);

   ~ShootingScene();

   Scene* GetNextState(bool* deleteMe);

protected:

   bool ProcessEvent(SDL_Event const & ev);

protected:

   GraphicEntity _background;

   std::map<int, Command*> _keyboardDownMappedCommands;

   std::map<int, Command*> _keyboardUpMappedCommands;

   Spaceship _ship;

};

