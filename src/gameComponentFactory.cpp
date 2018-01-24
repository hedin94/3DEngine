#include "gameComponentFactory.hpp"
#include "camera.hpp"
#include "freeLook.hpp"
#include "freeMove.hpp"
#include "meshRenderer.hpp"
#include "lighting.hpp"
#include "physicsComponent.hpp"
#include "colliderFactory.hpp"

#include <iostream>

GameComponentFactory::GameComponentFactory(){
}

GameComponentFactory::~GameComponentFactory(){
}

GameComponent*
GameComponentFactory::
getComponent(Json::Value json) {
    std::string type = json["type"].asString();
    if (type == "CameraComponent") {
	float fieldOfView = json.get("fieldOfView", 90).asFloat();
	float near = json.get("near", 1.0).asFloat();
	float far = json.get("far", 1000).asFloat();
	return new CameraComponent(glm::perspective(fieldOfView, Window::getAspect(), near, far));
    }
    
    if (type == "FreeLook") {
	float sensitivity = json.get("sensitivity", 1.0).asFloat();
	return new FreeLook(sensitivity);
    }
    
    if (type == "FreeMove") {
	float speed = json.get("speed", 1.0).asFloat();
	float speedMod = json.get("speedMod", 1.0).asFloat();
	return new FreeMove(speed, speedMod);
    }

    if (type == "MeshRenderer") {
	std::string filename = json.get("filename", "").asString();
	std::cout << "GameComponentFactory::getComponent(MeshRenderer): " << filename << std::endl;
	Json::Value jsonMaterial = json["material"];
	std::string diffuse = jsonMaterial.get("diffuse", "").asString();
	Json::Value jsonColor = jsonMaterial["color"];
	glm::vec3 color;
	if (!jsonColor.empty())
	    color = glm::vec3{jsonColor[0].asFloat(),
			      jsonColor[1].asFloat(),
			      jsonColor[2].asFloat()};
	float specularIntensity = jsonMaterial.get("specularIntensity", 1.0).asFloat();
	float specularPower =  jsonMaterial.get("specularPower", 0).asFloat();
	std::string normalMap = jsonMaterial.get("normalMap", "default_normal.jpg").asString();
	std::string dispMap = jsonMaterial.get("dispMap", "default_disp.png").asString();
	float dispMapScale = jsonMaterial.get("dispMapScale", 0).asFloat();
	float dispMapOffset = jsonMaterial.get("dispMapOffset", 0).asFloat();

	return new MeshRenderer(new Mesh(filename),
				new Material(new Texture(diffuse),
					     color, specularIntensity, specularPower,
					     new Texture(normalMap), new Texture(dispMap),
					     dispMapScale, dispMapOffset));
    }

    if (type == "BaseLight") {
	return nullptr;
    }

    if (type == "DirectionalLight") {
	Json::Value jsonColor = json["color"];
	glm::vec3 color{0, 0, 0};
	if (!jsonColor.empty())
	    color = glm::vec3{jsonColor[0].asFloat(),
			      jsonColor[1].asFloat(),
			      jsonColor[2].asFloat()};
	float intensity = json.get("intensity", 0).asFloat();
	return new DirectionalLight(color, intensity);
    }

    if (type == "PointLight") {
	Json::Value jsonColor = json["color"];
	glm::vec3 color{0, 0, 0};
	if (!jsonColor.empty())
	    color = glm::vec3{jsonColor[0].asFloat(),
			      jsonColor[1].asFloat(),
			      jsonColor[2].asFloat()};
	float intensity = json.get("intensity", 0).asFloat();
	Json::Value jsonAttenuation = json["attenuation"];
	Attenuation attenuation;
	if (!jsonAttenuation.empty()) {
	    attenuation.constant = jsonAttenuation.get("constant", 0).asFloat();
	    attenuation.linear = jsonAttenuation.get("linear", 0).asFloat();
	    attenuation.exponent = jsonAttenuation.get("exponent", 0).asFloat();
	}

	return new PointLight(color, intensity, attenuation);
    }

    if (type == "SpotLight") {	
	Json::Value jsonColor = json["color"];
	glm::vec3 color{0, 0, 0};
	if (!jsonColor.empty())
	    color = glm::vec3{jsonColor[0].asFloat(),
			      jsonColor[1].asFloat(),
			      jsonColor[2].asFloat()};
	float intensity = json.get("intensity", 0).asFloat();
	Json::Value jsonAttenuation = json["attenuation"];
	Attenuation attenuation;
	if (!jsonAttenuation.empty()) {
	    attenuation.constant = jsonAttenuation.get("constant", 0).asFloat();
	    attenuation.linear = jsonAttenuation.get("linear", 0).asFloat();
	    attenuation.exponent = jsonAttenuation.get("exponent", 0).asFloat();
	}
	float cutoff = json.get("cutoff", 0).asFloat();

	return new SpotLight(color, intensity, attenuation, cutoff);
    }

    if (type == "PhysicsComponent") {
	Json::Value jsonVel = json["vel"];
	glm::vec3 vel;
	if (!jsonVel.empty())
	    vel = glm::vec3{jsonVel[0].asFloat(),
			    jsonVel[1].asFloat(),
			    jsonVel[2].asFloat()};
	float mass = json.get("mass", 1).asFloat();
	Collider* collider = ColliderFactory::getCollider(json["collider"]);
	bool movable = json.get("movable", true).asBool();
	return new PhysicsComponent(vel, mass, collider, movable);
    }

    return nullptr;
}
