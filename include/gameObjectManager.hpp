#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

#include <map>
#include "json/json.h"
#include <vector>
#include <utility>

class GameObject;
typedef std::pair<GameObject*, Json::Value> pendingComponent;

class GameObjectManager {
public:
    static GameObjectManager& getInstance() {
	static GameObjectManager instance;
	return instance;
    }
    
    GameObjectManager(GameObjectManager const&) = delete;
    void operator=(GameObjectManager const&) = delete;

    static bool addObject(std::string id, GameObject* object);
    static bool contains(std::string id);
    static GameObject* getObject(std::string id);
    static std::map<std::string, GameObject*> getObjects();

    static void addPendingComponent(GameObject* object, Json::Value json);
    static void resolvePendingComponents();

private:
    static std::map<std::string, GameObject*> m_objects;
    static std::vector<pendingComponent> m_pending;
    
    GameObjectManager();
    virtual ~GameObjectManager();

};

#endif // _GAME_OBJECT_MANAGER_H_
