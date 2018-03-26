#include "gameObjectBuilder.hpp"
#include "json/json.h"
#include <fstream>
#include <glm/glm.hpp>

#include "gameComponentFactory.hpp"
#include "gameObjectManager.hpp"
#include "util.hpp"
#include <glm/gtx/rotate_vector.hpp>

GameObjectBuilder::GameObjectBuilder(){
}

GameObjectBuilder::~GameObjectBuilder(){
}

void
GameObjectBuilder::
readFile(const std::string& filename){
    std::fstream file(PATH + filename);
  
    Json::Value jsonRoot;
    file >> jsonRoot;
    file.close();

    readJSON(jsonRoot);
}

void
GameObjectBuilder::
readJSON(Json::Value json) {
    root = new GameObject();

    std::string id{};
    if (json.isMember("id")) {
	id = json["id"].asString();
	GameObjectManager::addObject(id, root);
    }

    if (json.isMember("ref")) {
	std::string refName = json["ref"].asString();
	GameObject* ref = GameObjectManager::getObject(refName);
	if (ref) {
	    std::cout << id << " referencing " << refName << std::endl;
	}
    }
    
    Json::Value transform = json["transform"];
    if (!transform.empty())
	root->setTransform(buildTransform(transform));

    Json::Value components = json["components"];
    for (auto c : components) {
	bool pending = false;
	GameComponent* component = GameComponentFactory::getComponent(c, pending);
	if (component) addComponent(component);
	if (pending) GameObjectManager::addPendingComponent(root, c);
    }

    Json::Value children = json["children"];
    for (Json::Value child : children) {
	GameObjectBuilder builder;
	builder.readJSON(child);
	root->addChild(builder.get());
    }

    GameObjectManager::resolvePendingComponents();

}

Transform*
GameObjectBuilder::
buildTransform(Json::Value transform) {
    Json::Value jsonPos = transform["pos"];
    Json::Value jsonAxis = transform["axis"];
    Json::Value jsonAngle = transform["angle"];
    Json::Value jsonScale = transform["scale"];

    Transform* t = new Transform();
    
    if (!jsonPos.empty()) {
	glm::vec3 pos = glm::vec3{jsonPos[0].asFloat(),
				  jsonPos[1].asFloat(),
				  jsonPos[2].asFloat()};
	t->setPos(pos);
    }
    
    if (!jsonAxis.empty() && !jsonAngle.empty()) {
	glm::vec3 axis = glm::vec3{jsonAxis[0].asFloat(),
				   jsonAxis[1].asFloat(),
				   jsonAxis[2].asFloat()};
	t->rotate(toRad(jsonAngle.asFloat()), axis);
    }

    if (!jsonScale.empty()) {
	glm::vec3 scale = glm::vec3{jsonScale[0].asFloat(),
				    jsonScale[1].asFloat(),
				    jsonScale[2].asFloat()};
	t->setScale(scale);
    }
    
    return t;
}

GameObjectBuilder*
GameObjectBuilder::
addComponent(GameComponent* component){
    root->addComponent(component);
}

GameObject*
GameObjectBuilder::
get(){
    return root;
}
