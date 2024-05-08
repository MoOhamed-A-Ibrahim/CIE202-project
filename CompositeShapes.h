#pragma once
#include "Basicshapes.h"


////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
//This class reprsents the composite shape "sign"
//The sign is composed of 2 Recatngles
/*

					 ------------------
					|				   |
					|		 x		   |     x is the reference point of the Sign shape
					|			       |
					 ------------------
						   |   |
						   |   |
						   | . |
						   |   |
						   |   |
							---
*/

//Note: sign reference point is the center point of the top rectangle
class Sign :public shape
{
	Rect* base;
	Rect* top;
	double* SignRotation = ROT_angle;


public:
	Sign(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);

	void rotate();

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class Tree :public shape
{
	Rect* base;
	triangle* Layer_1, * Layer_2, * layer_3;
	circle* apple;
	double* TreeRotation = ROT_angle;
public:
	Tree(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate();

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class Car :public shape
{
	Rect* base;
	circle* frontalWheel, * posteriorWheel;
	double* CarRotation = ROT_angle;
public:
	Car(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate();

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class IceCream :public shape
{
	triangle* base;
	circle* iceCircle;
	double* IceCreamRotation = ROT_angle;
public:
	IceCream(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate();

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class Rocket :public shape
{
	Rect* base;
	triangle* head, * liftbase, * rightbase;
	circle* door;
	double* RocketRotation = ROT_angle;
public:
	Rocket(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate();

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class House :public shape
{
	Rect* base, * door;
	triangle* head;
	double* HouseRotation = ROT_angle;
public:
	House(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate();

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};