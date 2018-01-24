#include "coreEngine.hpp"
#include "window.hpp"

#include "meshRenderer.hpp"
#include "freeLook.hpp"
#include "freeMove.hpp"
#include "followComponent.hpp"
#include "physicsComponent.hpp"
#include "spawner.hpp"
#include "gameObjectBuilder.hpp"

#include "camera.hpp"
#include "util.hpp"
#include "lighting.hpp"
#include "testing.hpp"
#include "constants.hpp"

#include "boundingSphere.hpp"
#include "boundingBox.hpp"
#include "plane.hpp"
#include "physicsObject.hpp"

#include "debug.hpp"

#include "json/json.h"

#include <iostream>
#include <fstream>

using namespace std;

class TestGame : public Game
{
public:
    TestGame() = default;
    ~TestGame() = default;

    void init() override
    {
	DEBUG("Initializing game");

	GameObjectBuilder gameObjectBuilder;
	gameObjectBuilder.readFile("camera.json");
        addToScene(gameObjectBuilder.get());

	gameObjectBuilder.readFile("scene.json");
	addToScene(gameObjectBuilder.get());
	
	gameObjectBuilder.readFile("monkey.json");
	addToScene(gameObjectBuilder.get());

	GameObject* spot = (new GameObject())
	    ->addComponent(new SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 10000000, Attenuation(0.8f, 0.1f, 0.1f), toRad(1)));
	Transform* spotTransform = new Transform();
	spotTransform->set_pos(glm::vec3(0,5,-5));
	spotTransform->rotate(toRad(60), glm::vec3(1,0,0));
	spot->setTransform(spotTransform);
	addToScene(spot);
	
	// GameObject* pointLight = (new GameObject(glm::vec3(0,1,0)))
	//   ->addComponent(new PointLight(glm::vec3(0.7f, 0.7f, 0.7f), 100000000, Attenuation(0, 0, 1)));

	// addToScene(pointLight);



	// North
	// addToScene((new GameObject())
	// 	       ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 0.1f)));

	// // East
	// GameObject* dirLight2 = (new GameObject())
	//   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 0.1f));
	// addToScene(dirLight2);

	// Transform* transformDirLight2 = new Transform();
	// transformDirLight2->rotate(toRad(60), glm::vec3(0,1,0));
	// dirLight2->setTransform(transformDirLight2);

	// // South
	// GameObject* dirLight3 = (new GameObject())
	//   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
	// addToScene(dirLight3);

	// Transform* transformDirLight3 = new Transform();
	// transformDirLight3->rotate(toRad(150), glm::vec3(0,1,0));
	// dirLight3->setTransform(transformDirLight3);

	// West
	// GameObject* dirLight4 = (new GameObject())
	//   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
	// addToScene(dirLight4);

	// Transform* transformDirLight4 = new Transform();
	// transformDirLight4->rotate(toRad(240), glm::vec3(0,1,0));
	// dirLight4->setTransform(transformDirLight4);


	// // North
	// GameObject* dirLight = (new GameObject())
	//   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
	// //addToScene(dirLight);

	// Transform* transformDirLight = new Transform();
	//  transformDirLight->rotate(toRad(-30), glm::vec3(0,1,0));
	//  dirLight->setTransform(transformDirLight);

	// // East
	// GameObject* dirLight2 = (new GameObject())
	//   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
	// //addToScene(dirLight2);

	// Transform* transformDirLight2 = new Transform();
	//  transformDirLight2->rotate(toRad(60), glm::vec3(1,1,0));
	// dirLight2->setTransform(transformDirLight2);

	// // South
	// GameObject* dirLight3 = (new GameObject())
	//   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
	// //addToScene(dirLight3);

	// Transform* transformDirLight3 = new Transform();
	// transformDirLight3->rotate(toRad(150), glm::vec3(0,1,0));
	// dirLight3->setTransform(transformDirLight3);

	// West
	// GameObject* dirLight4 = (new GameObject())
	//   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
	// //addToScene(dirLight4);

	// Transform* transformDirLight4 = new Transform();
	// transformDirLight4->rotate(toRad(200), glm::vec3(-1,1,0));
	// dirLight4->setTransform(transformDirLight4);

	DEBUG("Game initialized!");
    }
};


int main(int argc, char* argv[])
{
    cout << "Start of 3DEngine program!\n" << endl;

    // Testing::runAllTests();

    TestGame* game = new TestGame;

    CoreEngine engine(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, 100, game, "3D Game Engine");
    engine.setWindowIcon("green_cube.png");
    engine.start();

    delete game;

    cout << "End of program" << endl;
    return 0;
}
