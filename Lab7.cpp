#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(0, .5));

	// Floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

		// Wall Left
	PhysicsRectangle Lwall;
	Lwall.setSize(Vector2f(20, 560));
	Lwall.setCenter(Vector2f(0, 300));
	Lwall.setStatic(true);
	world.AddPhysicsBody(Lwall);
	Lwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	// Wall Right
	PhysicsRectangle Rwall;
	Rwall.setSize(Vector2f(20, 560));
	Rwall.setCenter(Vector2f(800, 300));
	Rwall.setStatic(true);
	world.AddPhysicsBody(Rwall);
	Rwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	// Wall Right
	PhysicsRectangle Roof;
	Roof.setSize(Vector2f(800, 20));
	Roof.setCenter(Vector2f(400, 10));
	Roof.setStatic(true);
	world.AddPhysicsBody(Roof);
	Roof.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	// Mid
	PhysicsRectangle Mid;
	Mid.setSize(Vector2f(100, 100));
	Mid.setCenter(Vector2f(400, 150));
	Mid.setStatic(true);
	world.AddPhysicsBody(Mid);
	int bangCount(0);
	Mid.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(Lwall);
		window.draw(Rwall);
		window.draw(Roof);
		window.draw(Mid);
		window.display();

		if (bangCount == 3) {
			exit(0);
		}
	}
}
