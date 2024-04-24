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
public:
	Sign(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(int factor) override;
	virtual void resizeDown(int factor) ;
};

class Tree :public shape
{
	Rect* base;
	triangle* Layer_1, * Layer_2, * layer_3;
public:
	Tree(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(int factor);
	virtual void resizeDown(int factor);

};

class Car :public shape
{
	Rect* base;
	circle* frontalWheel, * posteriorWheel;
public:
	Car(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(int factor);
	virtual void resizeDown(int factor);
};

class IceCream :public shape
{
	triangle* base;
	circle* iceCircle;
public:
	IceCream(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(int factor);
	virtual void resizeDown(int factor);
};

class Rocket :public shape
{
	Rect* base;
	triangle* head, * liftbase, * rightbase;
public:
	Rocket(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(int factor);
	virtual void resizeDown(int factor);
};

class House :public shape
{
	Rect* base, * door;
	triangle* head;
public:
	House(game* r_pGame, point ref);
	virtual void draw() const;
	virtual void resizeUp(int factor);
	virtual void resizeDown(int factor);
};