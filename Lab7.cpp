// Lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 100));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(-.8,-.3));
	world.AddPhysicsBody(ball);
	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	// Create Left wall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 800));
	leftWall.setCenter(Vector2f(10, 400));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);
	// Create Right wall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 800));
	rightWall.setCenter(Vector2f(790, 400));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);
	// Create ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	// Create Center rectangle
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(100, 100));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);
	// Thud Counter
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
		};
	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
		};
	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
		};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		thudCount++;
		cout << "thud " << thudCount << endl;
		};
	// Bang Counter
	int bangCount(1);
	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		if (bangCount == 4) {
			exit(0);
		}
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
		window.draw(rightWall);
		window.draw(leftWall);
		window.draw(ceiling);
		window.draw(obstacle);
		window.display();
	}
}
