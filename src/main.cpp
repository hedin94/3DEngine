#include "coreEngine.hpp"
#include "window.hpp"

#include "gameObjectBuilder.hpp"
#include "gameObjectManager.hpp"

#include "util.hpp"
#include "testing.hpp"
#include "constants.hpp"

#include "debug.hpp"

#include <iostream>
#include <fstream>
#include <map>

#include "spawner.hpp"

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
	gameObjectBuilder.readFile("follower.json");
	addToScene(gameObjectBuilder.get());

	gameObjectBuilder.readFile("camera.json");
        addToScene(gameObjectBuilder.get());

	gameObjectBuilder.readFile("scene.json");
	addToScene(gameObjectBuilder.get());
	
	gameObjectBuilder.readFile("monkey.json");
	addToScene(gameObjectBuilder.get());

	gameObjectBuilder.readFile("lights.json");
	addToScene(gameObjectBuilder.get());
	
	std::map<std::string, GameObject*> refObjects = GameObjectManager::getObjects();

	std::cout << "Referenced objects:" << std::endl;
	for (auto val : refObjects) {
	    std::cout << val.first << ": " << std::endl;
	    val.second->dumpComponents();
	}
	
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
