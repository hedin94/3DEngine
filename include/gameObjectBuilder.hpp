#ifndef _GAME_OBJECT_BUILDER_H_
#define _GAME_OBJECT_BUILDER_H_

#include "gameObject.hpp"
#include "gameComponent.hpp"
#include "transform.hpp"
#include "json/json.h"

class GameObjectBuilder {
public:
    GameObjectBuilder();
    virtual ~GameObjectBuilder();

    void readFile(const std::string& filename);
    void readJSON(Json::Value);
    GameObjectBuilder* addComponent(GameComponent*);
    GameObject* get();

private:
    Transform* buildTransform(Json::Value);

    GameObject* root = nullptr;
    const std::string PATH = "./res/";
};

#endif // _GAME_OBJECT_BUILDER_H_
