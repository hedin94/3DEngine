
CCC=g++
SRC_DIR=src
CFLAGS=-g -c -w -Wl,-subsystem,windows -std=c++11 -Wall -Wpedantic -Wextra -I$(SRC_DIR)
LFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -Llib -lglew32 -lopengl32 -lassimp

all: 3DEngine

debug: CFLAGS += -DUSE_DEBUG
debug: 3DEngine

3DEngine: testing.o main.o 3DphysicsEngine 3DrenderingEngine
	$(CCC) *.o -o 3DEngine $(LFLAGS)

testing.o: $(SRC_DIR)/testing.cc $(SRC_DIR)/testing.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/testing.cc

3DrenderingEngine: ostream_helper.o window.o lighting.o camera.o shader.o material.o obj_loader.o mesh.o stb_image.o texture.o transform.o input.o  meshRenderer.o gameComponent.o gameObject.o game.o renderingEngine.o coreEngine.o freeLook.o freeMove.o followComponent.o spawner.o

main.o: $(SRC_DIR)/main.cc
	$(CCC) $(CFLAGS) $(SRC_DIR)/main.cc

window.o: $(SRC_DIR)/window.cc $(SRC_DIR)/window.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/window.cc

shader.o: $(SRC_DIR)/shader.cc $(SRC_DIR)/shader.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/shader.cc

lighting.o: $(SRC_DIR)/lighting.cc $(SRC_DIR)/lighting.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/lighting.cc

obj_loader.o: $(SRC_DIR)/obj_loader.cc $(SRC_DIR)/obj_loader.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/obj_loader.cc

mesh.o: $(SRC_DIR)/mesh.cc $(SRC_DIR)/mesh.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/mesh.cc

stb_image.o: $(SRC_DIR)/stb_image.c $(SRC_DIR)/stb_image.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/stb_image.c

texture.o: $(SRC_DIR)/texture.cc $(SRC_DIR)/texture.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/texture.cc

transform.o: $(SRC_DIR)/transform.cc $(SRC_DIR)/transform.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/transform.cc

camera.o: $(SRC_DIR)/camera.cc $(SRC_DIR)/camera.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/camera.cc

input.o: $(SRC_DIR)/input.cc $(SRC_DIR)/input.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/input.cc

material.o: $(SRC_DIR)/material.cc $(SRC_DIR)/material.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/material.cc

meshRenderer.o: $(SRC_DIR)/meshRenderer.h $(SRC_DIR)/meshRenderer.cc
	$(CCC) $(CFLAGS) $(SRC_DIR)/meshRenderer.cc

renderingEngine.o: $(SRC_DIR)/renderingEngine.cc $(SRC_DIR)/renderingEngine.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/renderingEngine.cc

coreEngine.o: $(SRC_DIR)/coreEngine.cc $(SRC_DIR)/coreEngine.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/coreEngine.cc

game.o: gameObject.o gameComponent.o renderingEngine.o coreEngine.o $(SRC_DIR)/game.cc $(SRC_DIR)/game.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/game.cc

gameObject.o: $(SRC_DIR)/gameObject.cc $(SRC_DIR)/gameObject.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/gameObject.cc

gameComponent.o: $(SRC_DIR)/gameComponent.cc $(SRC_DIR)/gameComponent.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/gameComponent.cc

freeLook.o: $(SRC_DIR)/freeLook.cc $(SRC_DIR)/freeLook.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/freeLook.cc

freeMove.o: $(SRC_DIR)/freeMove.cc $(SRC_DIR)/freeMove.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/freeMove.cc

followComponent.o: $(SRC_DIR)/followComponent.cc $(SRC_DIR)/followComponent.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/followComponent.cc


3DphysicsEngine: collider.o boundingSphere.o boundingBox.o plane.o physicsObject.o physicsEngine.o physicsComponent.o

collider.o: $(SRC_DIR)/collider.cc $(SRC_DIR)/collider.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/collider.cc

boundingSphere.o: $(SRC_DIR)/boundingSphere.cc $(SRC_DIR)/boundingSphere.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/boundingSphere.cc

boundingBox.o: $(SRC_DIR)/boundingBox.cc $(SRC_DIR)/boundingBox.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/boundingBox.cc

plane.o: $(SRC_DIR)/plane.cc $(SRC_DIR)/plane.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/plane.cc

physicsObject.o: $(SRC_DIR)/physicsObject.cc $(SRC_DIR)/physicsObject.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/physicsObject.cc

physicsEngine.o: $(SRC_DIR)/physicsEngine.cc $(SRC_DIR)/physicsEngine.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/physicsEngine.cc

physicsComponent.o: $(SRC_DIR)/physicsComponent.cc $(SRC_DIR)/physicsComponent.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/physicsComponent.cc

spawner.o: $(SRC_DIR)/spawner.cc $(SRC_DIR)/spawner.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/spawner.cc

ostream_helper.o: $(SRC_DIR)/ostream_helper.cc $(SRC_DIR)/ostream_helper.h
	$(CCC) $(CFLAGS) $(SRC_DIR)/ostream_helper.cc



clean: clean_src clean_ 

clean_src:
	del $(SRC_DIR)\*~

clean_:
	del *~

zap: clean
	del *.o
