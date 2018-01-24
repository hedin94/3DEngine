#ifndef _COLLIDER_FACTORY_H_
#define _COLLIDER_FACTORY_H_

#include "collider.hpp"
#include "json/json.h"

class ColliderFactory {
public:
    static ColliderFactory& getInstance() {
	static ColliderFactory instance;
	return instance;
    }
    
    ColliderFactory(ColliderFactory const&) = delete;
    void operator=(ColliderFactory const&) = delete;

    static Collider* getCollider(Json::Value);

private:
    ColliderFactory();
    virtual ~ColliderFactory();

};

#endif // _COLLIDER_FACTORY_H_
