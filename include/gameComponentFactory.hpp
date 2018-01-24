#ifndef _GAME_COMPONENT_FACTORY_H_
#define _GAME_COMPONENT_FACTORY_H_

#include "json/json.h"
#include "gameComponent.hpp"

class GameComponentFactory {
public:
    static GameComponentFactory& getInstance() {
	static GameComponentFactory instance;
	return instance;
    }
    
    GameComponentFactory(GameComponentFactory const&) = delete;
    void operator=(GameComponentFactory const&) = delete;


    static GameComponent* getComponent(Json::Value);

private:
    GameComponentFactory();
    virtual ~GameComponentFactory();
};

#endif // _GAME_COMPONENT_FACTORY_H_
