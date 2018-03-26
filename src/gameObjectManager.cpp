#include "gameObjectManager.hpp"
#include "gameObject.hpp"
#include "gameComponentFactory.hpp"

std::map<std::string, GameObject*> GameObjectManager::m_objects;
std::vector<pendingComponent> GameObjectManager::m_pending;

GameObjectManager::GameObjectManager(){
}

GameObjectManager::~GameObjectManager(){
}


bool
GameObjectManager::
addObject(std::string id, GameObject* object) {
    return m_objects.emplace(id, object).second;
}

bool
GameObjectManager::
contains(std::string id) {
    return m_objects.count(id);
}

GameObject*
GameObjectManager::
getObject(std::string id) {
    auto it = m_objects.find(id);
    if (it != m_objects.end()) return it->second;
    return nullptr;
}

std::map<std::string, GameObject*>
GameObjectManager::
getObjects() {
    return m_objects;
}

void
GameObjectManager::
addPendingComponent(GameObject* object, Json::Value json) {
    m_pending.push_back(pendingComponent(object, json));
}

void
GameObjectManager::
resolvePendingComponents() {
    for (auto it = m_pending.rbegin(); it != m_pending.rend(); it++) {
	GameObject* object = it->first;
	Json::Value c = it->second;
	
	bool pending=false;
	GameComponent* component = GameComponentFactory::getComponent(c, pending);
	if (pending || !component) continue;

	object->addComponent(component);
	m_pending.erase(std::next(it).base());
    }
}
