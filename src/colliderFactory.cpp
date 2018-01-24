#include "colliderFactory.hpp"
#include "plane.hpp"
#include "boundingSphere.hpp"

ColliderFactory::ColliderFactory(){
}

ColliderFactory::~ColliderFactory(){
}

Collider*
ColliderFactory::
getCollider(Json::Value json) {
    std::string type = json.get("type", "").asString();

    if (type == "plane") {
	Json::Value jsonNormal = json["normal"];
	glm::vec3 normal;
	if (!jsonNormal.empty())
	    normal = glm::vec3{jsonNormal[0].asFloat(),
			       jsonNormal[1].asFloat(),
			       jsonNormal[2].asFloat()};
	float offset = json.get("offset", 0).asFloat();
	return new Plane(normal, offset);	
    }

    if (type == "sphere") {
	Json::Value jsonPos = json["pos"];
	glm::vec3 pos;
	if (!jsonPos.empty())
	    pos = glm::vec3{jsonPos[0].asFloat(),
			    jsonPos[1].asFloat(),
			    jsonPos[2].asFloat()};
	float radius = json.get("radius", 1).asFloat();
	return new BoundingSphere(pos, radius);
    }

    return nullptr;
}
