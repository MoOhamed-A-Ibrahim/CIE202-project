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
	double angle = 0;


public:
	Sign(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);

	void rotate(double deg);

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class Tree :public shape
{
	Rect* base;
	triangle* Layer_1, * Layer_2, * layer_3;
	double angle = 0;
public:
	Tree(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate(double deg);

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class Car :public shape
{
	Rect* base;
	circle* frontalWheel, * posteriorWheel;
	double angle = 0;
public:
	Car(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate(double deg);

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class IceCream :public shape
{
	triangle* base;
	circle* iceCircle;
	double angle = 0;
public:
	IceCream(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate(double deg);

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class Rocket :public shape
{
	Rect* base;
	triangle* head, * liftbase, * rightbase;
	double angle = 0;
public:
	Rocket(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate(double deg);

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};

class House :public shape
{
	Rect* base, * door;
	triangle* head;
	double angle = 0;
public:
	House(game* r_pGame, point ref);
	void draw() const;

	void resizeUp(double factor);
	void resizeDown(double factor);
	void rotate(double deg);

	void moveUp(double dist);
	void moveDown(double dist);
	void moveRight(double dist);
	void moveLeft(double dist);
};