#ifndef _GAME_OBJECT_BUILDER_H_
#define _GAME_OBJECT_BUILDER_H_

#include "gameObject.hpp"
#include "gameComponent.hpp"
#include "transform.hpp"
#include "json/json.h"

#include <vector>
#include <set>
#include <glm/glm.hpp>

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



class SupportedGameComponents {
public:
    static SupportedGameComponents& getInstance(){
	static SupportedGameComponents instance;
	return instance;
    }

    SupportedGameComponents(SupportedGameComponents const&) = delete;
    void operator=(SupportedGameComponents const&) = delete;

    static bool isSupported(const std::string& compName);

private:
    static std::set<std::string> components;
    static const std::string PATH;

    SupportedGameComponents();
    virtual ~SupportedGameComponents();
};
#endif // _GAME_OBJECT_BUILDER_H_
