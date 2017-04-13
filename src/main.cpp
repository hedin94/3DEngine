#include "coreEngine.hpp"
#include "window.hpp"

#include "meshRenderer.hpp"
#include "freeLook.hpp"
#include "freeMove.hpp"
#include "followComponent.hpp"
#include "physicsComponent.hpp"
#include "spawner.hpp"

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

#include <iostream>

using namespace std;

class TestGame : public Game
{
public:
  TestGame() = default;
  ~TestGame() = default;

  void init() override
  {
    DEBUG("Initializing game");

    GameObject* cameraObject = (new GameObject(glm::vec3(0,7,-15)))
      ->addComponent(new CameraComponent(glm::perspective(70.0f, Window::getAspect(), 1.0f, 1000.0f)))
      ->addComponent(new FreeLook(0.01f))
      ->addComponent(new FreeMove(0.015f))
      ->addComponent(new PointLight(glm::vec3(0.7f, 0.7f, 0.7f), 1000, Attenuation(1.0f, 2.0f, 1.0f)))
      ->addComponent(new Spawner(this));

    addToScene(cameraObject);
  
    //GameObject* spot = (new GameObject())
    //  ->addComponent(new PointLight(glm::vec3(0.7f, 0.7f, 0.7f), 10000, Attenuation(0.8f, 0.1f, 0.1f)));
    //addToScene(spot);

    // GameObject* followObject = (new GameObject(glm::vec3(0, 5, 0)))
    //   ->addComponent(new MeshRenderer(new Mesh("monkey3.obj"),
    // 				      new Material(new Texture("184.jpg"),
    // 						   new Texture("184_norm.jpg"), 
    // 						   glm::vec3(1,1,1), 1, 10)))
    //   ->addComponent(new FollowComponent(10, cameraObject));
    
    //followObject->getTransform()->rotate(toRad(180), glm::vec3(0,1,0));
    // addToScene(followObject);

    // addToScene((new GameObject(glm::vec3(0,1,0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("monkey3.obj"),
    // 					       new Material(new Texture("bricks3.jpg"),
    // 							    new Texture("bricks3_normal.jpg"), 
    // 							    glm::vec3(1,1,1), 1, 0))));
    // 	       //->addComponent((new FreeLook(0.025f))));

    // addToScene((new GameObject(glm::vec3(-3, 1, 0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("monkey3.obj"), 
    // 					       new Material(new Texture("bricks3.jpg"), 
    // 							    new Texture("default_normal.jpg"), 
    // 							    glm::vec3(1,1,1), 10 , 2))));


    // addToScene((new GameObject(glm::vec3(0,-1,0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    // 					       new Material(new Texture("12_DIFFUSE.jpg"),
    // 							    new Texture("12_NORMAL.jpg"),
    // 							    glm::vec3(1,1,1), 1, 0))));

    GameObject* planeObject1 = (new GameObject(glm::vec3(0, 0, 0)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   glm::vec3(1,1,1), 1, 0,
    						   new Texture("bricks2_normal.jpg"))));

    GameObject* planeObject2 = (new GameObject(glm::vec3(0, 7, 8)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   glm::vec3(1,1,1), 1, 0,
    						   new Texture("bricks2_normal.jpg"),
    						   new Texture("bricks2_disp.jpg"),
    						   0.04f, -0.6f)));
    
    GameObject* planeObject3 = (new GameObject(glm::vec3(0, 15, 0)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   glm::vec3(1,1,1), 1, 0,
    						   new Texture("bricks2_normal.jpg"),
    						   new Texture("bricks2_disp.jpg"),
    						   0.04f, -0.6f)));
    
    GameObject* planeObject4 = (new GameObject(glm::vec3(-8, 7, 0)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   glm::vec3(1,1,1), 1, 0,
    						   new Texture("bricks2_normal.jpg"),
    						   new Texture("bricks2_disp.jpg"),
    						   0.04f, -0.6f)));

    GameObject* planeObject5 = (new GameObject(glm::vec3(8, 7, 0)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   glm::vec3(1,1,1), 1, 0,
    						   new Texture("bricks2_normal.jpg"),
    						   new Texture("bricks2_disp.jpg"),
    						   0.04f, -0.6f)));

    GameObject* planeObject6 = (new GameObject(glm::vec3(0, 7, -8)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   glm::vec3(1,1,1), 1, 0,
    						   new Texture("bricks2_normal.jpg"),
    						   new Texture("bricks2_disp.jpg"),
    						   0.04f, -0.6f)));


    Transform* transform1 = new Transform();
    transform1->set_scale(glm::vec3(1));
    transform1->set_pos(glm::vec3());
    planeObject1->setTransform(transform1);

    Transform* transform2 = new Transform();
    transform2->rotate(toRad(-90.0f), glm::vec3(1,0,0));
    transform2->set_pos(glm::vec3(0, 7, 8));
    planeObject2->setTransform(transform2);

    Transform* transform3 = new Transform();
    transform3->rotate(toRad(180.0f), glm::vec3(0,0,1));
    transform3->set_pos(glm::vec3(0, 15, 0));
    planeObject3->setTransform(transform3);

    Transform* transform4 = new Transform();
    transform4->rotate(toRad(270.0f), glm::vec3(0,0,1));
    transform4->rotate(toRad(90.0f), glm::vec3(1,0,0));
    transform4->set_pos(glm::vec3(-8, 7, 0));
    planeObject4->setTransform(transform4);

    Transform* transform5 = new Transform();
    transform5->rotate(toRad(90.0f), glm::vec3(0,0,1));
    transform5->rotate(toRad(90.0f), glm::vec3(1,0,0));
    transform5->set_pos(glm::vec3(8, 7, 0));
    planeObject5->setTransform(transform5);

    Transform* transform6 = new Transform();
    transform6->rotate(toRad(90.0f), glm::vec3(1,0,0));
    transform6->set_pos(glm::vec3(0, 7, -8));
    planeObject6->setTransform(transform6);

    planeObject1->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 100000000000.0f, new Plane(glm::vec3(0,1,0), 1.0f), false));
    planeObject2->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(0,0,1), 8.0f), false));
    planeObject3->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(0,-1,0), -12.0f), false));
    planeObject4->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(-1,0,0), 8.0f), false));
    planeObject5->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(1,0,0), 8.0f), false));
    planeObject6->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(0,0,1), -8.0f), false));

    addToScene(planeObject1);
    addToScene(planeObject2);
    addToScene(planeObject3);
    addToScene(planeObject4);
    addToScene(planeObject5);
    //addToScene(planeObject6);


    // North
    addToScene((new GameObject())
    	       ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f)));

    // East
    GameObject* dirLight2 = (new GameObject())
      ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
     addToScene(dirLight2);

    Transform* transformDirLight2 = new Transform();
     transformDirLight2->rotate(toRad(60), glm::vec3(0,1,0));
    dirLight2->setTransform(transformDirLight2);

    // // South
    // GameObject* dirLight3 = (new GameObject())
    //   ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 2.5f));
    // addToScene(dirLight3);

    // Transform* transformDirLight3 = new Transform();
    // transformDirLight3->rotate(toRad(150), glm::vec3(0,1,0));
    // dirLight3->setTransform(transformDirLight3);

    // // West
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


    //   GameObject* testPlane1 = (new GameObject(glm::vec3(3, 2, 0)))
    //     ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    // 				      new Material(new Texture("bricks2.jpg"),
    // 						   new Texture("bricks2_normal.jpg"),
    // 						   glm::vec3(1,1,1), 1, 0)));

    //   GameObject* testPlane2 = (new GameObject(glm::vec3(25, 0, 0)))
    //     ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    // 				      new Material(new Texture("bricks2.jpg"),
    // 						   new Texture("bricks2_normal.jpg"),
    // 						   glm::vec3(1,1,1), 1, 0)));


    // testPlane1->getTransform()->get_scale() = glm::vec3(0.1f, 0.1f, 0.1f);
    // testPlane1->getTransform()->rotate(toRad(20), glm::vec3(0,1,0));
    // testPlane2->getTransform()->rotate(toRad(20), glm::vec3(0,1,0));
 
    // testPlane1->addChild(testPlane2);
    // testPlane1->addChild(testCamera);
    
    // addToScene(testPlane1);

    // addToScene((new GameObject(glm::vec3(-3, 6, 0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    // 					       new Material(new Texture("bricks3.jpg"), 
    // 							    glm::vec3(1,1,1), 2 , 1, 
    // 							    new Texture("bricks3_normal.jpg"),
    // 							    new Texture("bricks3_disp.png"),
    // 							    0.03f, -0.4f)))
    // 	       ->addComponent(new PhysicsComponent(glm::vec3(0,0, 0), 1.0f, new BoundingSphere(glm::vec3(-3,0,0), 1))));

    // addToScene((new GameObject(glm::vec3(3, 8, 0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    // 					       new Material(new Texture("184.jpg"), 
    // 							    glm::vec3(1,1,1), 2 , 1, 
    // 							    new Texture("184_norm.jpg"))))
    // 	       ->addComponent(new PhysicsComponent(glm::vec3(-1.5f, 0, 0), 1.0f, new BoundingSphere(glm::vec3(3,0,0), 1))));

    
    	       

    //   GameObject* sphere = new GameObject(glm::vec3(0, 7, 0));
    // sphere->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    // 					  new Material(new Texture("bricks3.jpg"), 
    // 						       glm::vec3(1,1,1), 2 , 1, 
    // 						       new Texture("bricks3_normal.jpg"))))
    //   ->addComponent(new PhysicsComponent(glm::vec3(0, 0, 0), 10.0f, new BoundingSphere(glm::vec3(0,3,0), 1)));

    //Transform* transform7 = new Transform();
    //transform7->set_scale(glm::vec3(2,2,2));
    //sphere->setTransform(transform7);

    //addToScene(sphere);

    // addToScene((new GameObject(glm::vec3(-2, 3, 0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    // 					       new Material(new Texture("bricks2.jpg"), 
    // 							    new Texture("bricks2_normal.jpg"), 
    // 							    glm::vec3(0.5f,1,1), 7, 10)))
    // 	       ->addComponent(new PhysicsComponent(glm::vec3(0.001f, 0, 0), 10.0f, new BoundingSphere(glm::vec3(-2,3,0), 1))));

    // addToScene((new GameObject(glm::vec3(-4, 3, 0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    // 					       new Material(new Texture("184.jpg"), 
    // 							    new Texture("184_norm.jpg"), 
    // 							    glm::vec3(0.5f,0.5f,0.5f), 5, 10)))
    // 	       ->addComponent(new PhysicsComponent(glm::vec3(0, 0.025f, 0), 10.0f, new BoundingSphere(glm::vec3(-4,3,0), 1))));

    // addToScene((new GameObject(glm::vec3(0,-1,0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    // 					       new Material(new Texture("bricks2.jpg"),
    // 							    new Texture("bricks2_normal.jpg"),
    // 							    glm::vec3(1,1,1), 1, 0)))
    // 	       ->addComponent(new PhysicsComponent(glm::vec3(1,0,0))));
    


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
