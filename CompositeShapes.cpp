#include "CompositeShapes.h"
#include "gameConfig.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref):shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
}

void Sign::draw() const
{
	base->draw();
	top->draw();
}

void Sign::resizeDown(int factor) const {
	int newHeight = (base->getHeight()) - factor;
	int newWidth = (base->getWidth()) - factor;
	base->setHeight(newHeight);
	base->setWidth(newWidth);
}

void Sign::resizeUp(int factor) const {
	int newHeight = (base->getHeight()) + factor;
	int newWidth = (base->getWidth()) + factor;
	base->setHeight(newHeight);
	base->setWidth(newWidth);
}


Tree::Tree(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point layer_1_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - config.tree.baseWdth };
	point layer_2_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 2 * config.tree.baseWdth };
	point layer_3_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 2 * config.tree.baseWdth };

	base = new Rect(pGame, baseRef, config.tree.baseHeight, config.tree.baseWdth);
	base = new Rect(pGame, layer_1_ref, config.tree.baseHeight, config.tree.baseWdth);
}

void Tree::draw() const
{
	base->draw();
	Layer_1->draw();
	Layer_2->draw();
	layer_3->draw();
}

Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point fWRef = { ref.x + (0.4 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };
	point PWRef = { ref.x + (0.4 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };

	base = new Rect(pGame, baseRef, config.car.baseHeight, config.car.baseWdth);
	frontalWheel = new circle(pGame, fWRef, config.car.wheelRadius);
	posteriorWheel = new circle(pGame, PWRef, config.car.wheelRadius);
}

void Car::draw() const
{
	base->draw();
	frontalWheel->draw();
	posteriorWheel->draw();
}

IceCream::IceCream(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point circleRef = { ref.x, ref.y + config.icecream.baseWdth / 2 };

	base = new triangle(pGame, baseRef, config.icecream.baseWdth);
	iceCircle = new circle(pGame, circleRef, config.icecream.baseWdth);
}

void IceCream::draw() const
{
	iceCircle->draw();
	base->draw();
}

Rocket::Rocket(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point headref = { ref.x, ref.y - config.rocket.baseHeight / 2 - config.rocket.headwdth / 2 };
	point leftbaseRef = { ref.x - config.rocket.baseWdth / 2 , ref.y + config.rocket.baseHeight / 2 };
	point rightbaseRef = { ref.x + config.rocket.baseWdth / 2 , ref.y + config.rocket.baseHeight / 2 };

	base = new Rect(pGame, baseRef, config.rocket.baseHeight, config.rocket.baseWdth);
	head = new triangle(pGame, headref, config.rocket.headwdth);
	liftbase = new triangle(pGame, leftbaseRef, config.rocket.smallbaseWdth);
	rightbase = new triangle(pGame, rightbaseRef, config.rocket.smallbaseWdth);
}

void Rocket::draw() const
{
	liftbase->draw();
	rightbase->draw();
	base->draw();
	head->draw();
}

House::House(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point headRef = { ref.x, ref.y - config.house.baseHeight / 2 - config.house.headwdth / 2 };
	point doorRef = { ref.x + config.house.baseWdth / 3 , ref.y + config.house.baseHeight / 2 - config.house.doorhight / 2 };

	base = new Rect(pGame, baseRef, config.house.baseHeight, config.house.baseWdth);
	door = new Rect(pGame, doorRef, config.house.doorhight, config.house.doorwdth);
	head = new triangle(pGame, headRef, config.house.headwdth);
}

void House::draw() const
{
	base->draw();
	door->draw();
	head->draw();
}


