#include "gameObjectBuilder.hpp"
#include "json/json.h"
#include <fstream>
#include <glm/glm.hpp>

#include "gameComponentFactory.hpp"
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
    
    Json::Value transform = json["transform"];
    if (!transform.empty())
	root->setTransform(buildTransform(transform));

    Json::Value components = json["components"];
    for (auto c : components) {
	GameComponent* component = GameComponentFactory::getComponent(c);
	if (component) addComponent(component);
    }

    Json::Value children = json["children"];
    for (Json::Value child : children) {
	GameObjectBuilder builder;
	builder.readJSON(child);
	root->addChild(builder.get());
    }

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
	t->set_pos(pos);
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
	t->set_scale(scale);
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


std::set<std::string> SupportedGameComponents::components;
const std::string SupportedGameComponents::PATH = "./res/components.txt";

SupportedGameComponents::
SupportedGameComponents(){
    std::fstream file(PATH);
    if(!file){
	std::cerr << "ERROR: could not read " << PATH  << std::endl;
	return;
    }

    std::string compName;
    while(getline(file, compName)){
	components.emplace(compName);
    }

    file.close();
}

SupportedGameComponents::
~SupportedGameComponents() {
}

bool
SupportedGameComponents::
isSupported(const std::string& compName){
    return components.find(compName) != components.end();
}
