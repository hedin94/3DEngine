#include "coreEngine.h"
#include "window.h"

#include "meshRenderer.h"
#include "freeLook.h"
#include "freeMove.h"
#include "followComponent.h"
#include "physicsComponent.h"

#include "camera.h"
#include "util.h"
#include "lighting.h"
#include "testing.h"

#include "boundingSphere.h"
#include "boundingBox.h"
#include "plane.h"
#include "physicsObject.h"

#include "debug.h"

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
      ->addComponent(new FreeMove(0.015f));    
    // ->addComponent(new SpotLight(glm::vec3(0.7f,0,0.7f), 30, Attenuation(0.4f, 0.1f, 0.5f), 0.9f));

    addToScene(cameraObject);

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
    						   new Texture("bricks2_normal.jpg"),
    						   glm::vec3(1,1,1), 1, 0)));

    GameObject* planeObject2 = (new GameObject(glm::vec3(0, 7, 8)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   new Texture("bricks2_normal.jpg"),
    						   glm::vec3(1,1,1), 1, 0)));
    
    GameObject* planeObject3 = (new GameObject(glm::vec3(0, 15, 0)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   new Texture("bricks2_normal.jpg"),
    						   glm::vec3(1,1,1), 1, 0)));
    
    GameObject* planeObject4 = (new GameObject(glm::vec3(-8, 7, 0)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   new Texture("bricks2_normal.jpg"),
    						   glm::vec3(1,1,1), 1, 0)));

    GameObject* planeObject5 = (new GameObject(glm::vec3(8, 7, 0)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   new Texture("bricks2_normal.jpg"),
    						   glm::vec3(1,1,1), 1, 0)));

    GameObject* planeObject6 = (new GameObject(glm::vec3(0, 7, -8)))
      ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    				      new Material(new Texture("bricks2.jpg"),
    						   new Texture("bricks2_normal.jpg"),
    						   glm::vec3(1,1,1), 1, 0)));


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
    transform4->set_pos(glm::vec3(-8, 7, 0));
    planeObject4->setTransform(transform4);

    Transform* transform5 = new Transform();
    transform5->rotate(toRad(90.0f), glm::vec3(0,0,1));
    transform5->set_pos(glm::vec3(8, 7, 0));
    planeObject5->setTransform(transform5);

    Transform* transform6 = new Transform();
    transform6->rotate(toRad(90.0f), glm::vec3(1,0,0));
    transform6->set_pos(glm::vec3(0, 7, -8));
    planeObject6->setTransform(transform6);

    planeObject2->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(0,0,1), 8.0f), false));
    planeObject3->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(0,-1,0), -15.0f), false));
    planeObject4->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(1,0,0), -8.0f), false));
    planeObject5->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(1,0,0), 8.0f), false));
    planeObject6->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 1000000.0f, new Plane(glm::vec3(0,0,1), -8.0f), false));

    //planeObject1->addChild(planeObject2);
    // planeObject1->addChild(planeObject3);
    // planeObject1->addChild(planeObject4);
    // planeObject1->addChild(planeObject5);

    planeObject1->addComponent(new PhysicsComponent(glm::vec3(0,0,0), 100000000000.0f, new Plane(glm::vec3(0,1,0), 0.0f), false));

    addToScene(planeObject2);
    addToScene(planeObject1);
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

    // South
    GameObject* dirLight3 = (new GameObject())
      ->addComponent(new DirectionalLight(glm::vec3(0.4f, 0, 0.4f), 2.5f));
    addToScene(dirLight3);

    Transform* transformDirLight3 = new Transform();
    transformDirLight3->rotate(toRad(150), glm::vec3(0,1,0));
    dirLight3->setTransform(transformDirLight3);

    // West
    GameObject* dirLight4 = (new GameObject())
      ->addComponent(new DirectionalLight(glm::vec3(0, 0.4f, 0.4f), 2.5f));
    addToScene(dirLight4);

    Transform* transformDirLight4 = new Transform();
    transformDirLight4->rotate(toRad(240), glm::vec3(0,1,0));
    dirLight4->setTransform(transformDirLight4);


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

    addToScene((new GameObject(glm::vec3(0, 3, 0)))
    	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    					       new Material(new Texture("bricks3.jpg"), 
    							    new Texture("bricks3_normal.jpg"), 
    							    glm::vec3(1,1,1), 2 , 1)))
    	       ->addComponent(new PhysicsComponent(glm::vec3(0.01f,0, 0), 1.0f, new BoundingSphere(glm::vec3(0,3,0), 1))));

    addToScene((new GameObject(glm::vec3(4, 3, 0)))
    	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    					       new Material(new Texture("bricks3.jpg"), 
    							    new Texture("bricks3_normal.jpg"), 
    							    glm::vec3(1,1,1), 2 , 1)))
    	       ->addComponent(new PhysicsComponent(glm::vec3(-0.01f, 0, 0), 1.0f, new BoundingSphere(glm::vec3(4,3,0), 1))));

    addToScene((new GameObject(glm::vec3(6, 3, 0)))
    	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    					       new Material(new Texture("bricks3.jpg"), 
    							    new Texture("bricks3_normal.jpg"), 
    							    glm::vec3(1,1,1), 2 , 1)))
    	       ->addComponent(new PhysicsComponent(glm::vec3(-0.001f, 0, 0), 1.0f, new BoundingSphere(glm::vec3(6,3,0), 1))));

    addToScene((new GameObject(glm::vec3(-2, 3, 0)))
    	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    					       new Material(new Texture("bricks2.jpg"), 
    							    new Texture("bricks2_normal.jpg"), 
    							    glm::vec3(0.5f,1,1), 7, 10)))
    	       ->addComponent(new PhysicsComponent(glm::vec3(0.001f, 0, 0), 10.0f, new BoundingSphere(glm::vec3(-2,3,0), 1))));

    // addToScene((new GameObject(glm::vec3(-4, 1, 0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
    // 					       new Material(new Texture("184.jpg"), 
    // 							    new Texture("184_norm.jpg"), 
    // 							    glm::vec3(0.5f,0.5f,0.5f), 5, 10)))
    // 	       ->addComponent(new PhysicsComponent(glm::vec3(0, 0.025f, 0), 10.0f, new BoundingSphere(glm::vec3(-4,1,0), 1))));

    // addToScene((new GameObject(glm::vec3(0,-1,0)))
    // 	       ->addComponent(new MeshRenderer(new Mesh("plane3.obj"),
    // 					       new Material(new Texture("bricks2.jpg"),
    // 							    new Texture("bricks2_normal.jpg"),
    // 							    glm::vec3(1,1,1), 1, 0))));
    // 	       ->addComponent(new PhysicsComponent(glm::vec3(1,0,0))));
    
    DEBUG("Game initialized!");
  }
};


int main(int argc, char* argv[])
{
  cout << "Start of 3DEngine program!\n" << endl;

  Testing::runAllTests();

  TestGame* game = new TestGame;

  CoreEngine engine(1200, 650, 60, game, "3D Game Engine");
  engine.start();

  delete game;

  cout << "End of program" << endl;
  return 0;
}
