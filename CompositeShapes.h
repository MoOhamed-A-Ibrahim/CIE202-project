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
	virtual void draw() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);

};

class Tree :public shape
{
	Rect* base;
	triangle* Layer_1, * Layer_2, * layer_3;
	double angle = 0;
public:
	Tree(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);

};

class Car :public shape
{
	Rect* base;
	circle* frontalWheel, * posteriorWheel;
	double angle = 0;
public:
	Car(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);
};

class IceCream :public shape
{
	triangle* base;
	circle* iceCircle;
	double angle = 0;
public:
	IceCream(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);
};

class Rocket :public shape
{
	Rect* base;
	triangle* head, * liftbase, * rightbase;
	double angle = 0;
public:
	Rocket(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);
};

class House :public shape
{
	Rect* base, * door;
	triangle* head;
	double angle = 0;
public:
	House(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(double factor);
	virtual void resizeDown(double factor);
	virtual void rotate(double deg);

};