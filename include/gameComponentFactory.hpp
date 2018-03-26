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
    
    GameComponentFactory(const GameComponentFactory &) = delete;
    void operator=(const GameComponentFactory &) = delete;


    static GameComponent* getComponent(Json::Value, bool&);

private:
    GameComponentFactory();
    virtual ~GameComponentFactory();
};

#endif // _GAME_COMPONENT_FACTORY_H_
