#include "CompositeShapes.h"
#include "gameConfig.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	//calc the ref point of the Sign base and top rectangles relative to the Sign shape
	point topRef = ref;	//top rect ref is the same as the sign
	point baseRef = { ref.x, ref.y + config.signShape.topHeight / 2 + config.signShape.baseHeight / 2 };


	top = new Rect(pGame, topRef, config.signShape.topHeight, config.signShape.topWdth);
	base = new Rect(pGame, baseRef, config.signShape.baseHeight, config.signShape.baseWdth);


}
void Sign::draw() const
{
	base->draw();
	top->draw();
}
void Sign::rotate(double deg)
{
	point topRef = RefPoint;
	//point baseRef = { RefPoint.x - config.signShape.topHeight / 2 - config.signShape.baseWdth / 2 + config.signShape.baseWdth , RefPoint.y - config.signShape.topHeight- config.signShape.baseWdth };
	point baseRef = { RefPoint.x - config.signShape.topWdth / 2 - config.signShape.baseWdth / 2 + config.signShape.topWdth / 2 - config.signShape.baseWdth ,RefPoint.y + config.signShape.topWdth / 2 + config.signShape.baseWdth / 2 };

	top->setRefPoint(topRef);
	base->setRefPoint(baseRef);
	top->rotate(deg);
	base->rotate(deg);


}


void Sign::resizeUp(int factor) {
	point oldRefBottom = base->getRefPoint();
	point newRefBottom;
	newRefBottom.y = base->getHeight() + top->getRefPoint().y + top->getHeight();
	newRefBottom.x = oldRefBottom.x;
	base->setRefPoint(newRefBottom);

	top->resizeUp(factor);
	base->resizeUp(factor);

}

void Sign::resizeDown(int factor) {
	// Retrieve the old reference point of the base
	point oldBaseRef = base->getRefPoint();

	// Calculate the new reference point for the base after resizing down
	point newBaseRef;
	// Subtract half of the scaled-down height of the base and half of the scaled-down height of the top part from the old reference point's y-coordinate
	newBaseRef.y = oldBaseRef.y - (base->getHeight() / factor) / 2 - (top->getHeight() / 2) / factor;
	newBaseRef.x = oldBaseRef.x; 
	base->setRefPoint(newBaseRef);
	top->resizeDown(factor);
	base->resizeDown(factor);
}



////////////////////////////////////////////////////////////////

Tree::Tree(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point layer_1_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - config.tree.baseWdth };
	point layer_2_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 2 * config.tree.baseWdth };
	point layer_3_ref = { ref.x, ref.y - config.tree.baseHeight / 2 - 3 * config.tree.baseWdth };

	base = new Rect(pGame, baseRef, config.tree.baseHeight, config.tree.baseWdth);
	Layer_1 = new triangle(pGame, layer_1_ref, config.tree.triwdth);
	Layer_2 = new triangle(pGame, layer_1_ref, config.tree.triwdth);
	layer_3 = new triangle(pGame, layer_3_ref, config.tree.triwdth);
}

void Tree::draw() const
{
	base->draw();
	Layer_1->draw();
	Layer_2->draw();
	layer_3->draw();
}

void Tree::resizeUp(int factor) {
	point newReference1 = { base->getRefPoint().x,base->getRefPoint().y - (config.tree.baseHeight / 2 - config.tree.baseWdth) * factor };
	point newReference2 = { base->getRefPoint().x,base->getRefPoint().y - (config.tree.baseHeight / 2 - 2 * config.tree.baseWdth) * factor };
	point newReference3 = { base->getRefPoint().x,base->getRefPoint().y - (config.tree.baseHeight / 2 - 3 * config.tree.baseWdth) * factor };

	Layer_1->setRefPoint(newReference1);
	Layer_2->setRefPoint(newReference2);
	layer_3->setRefPoint(newReference3);

	base->resizeUp(factor);
	Layer_1->resizeUp(factor);
	Layer_2->resizeUp(factor);
	layer_3->resizeUp(factor);


}
void Tree::resizeDown(int factor) {
	point newReference1 = { base->getRefPoint().x,base->getRefPoint().y - (config.tree.baseHeight / 2 - config.tree.baseWdth) / factor };
	point newReference2 = { base->getRefPoint().x,base->getRefPoint().y - (config.tree.baseHeight / 2 - 2 * config.tree.baseWdth) / factor };
	point newReference3 = { base->getRefPoint().x,base->getRefPoint().y - (config.tree.baseHeight / 2 - 3 * config.tree.baseWdth) / factor };

	Layer_1->setRefPoint(newReference1);
	Layer_2->setRefPoint(newReference2);
	layer_3->setRefPoint(newReference3);

	base->resizeDown(factor);
	Layer_1->resizeDown(factor);
	Layer_2->resizeDown(factor);
	layer_3->resizeDown(factor);

}
void Tree::rotate(double deg)
{
	Layer_1->rotate(deg);
	Layer_2->rotate(deg);
	layer_3->rotate(deg);
	base->rotate(deg);
}

//////////////////////////////////////////////////////////////////////
Car::Car(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point fWRef = { ref.x + (0.3 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };
	point PWRef = { ref.x - (0.3 * config.car.baseWdth), ref.y + config.car.baseHeight / 2 };

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
 
void Car::resizeUp(int factor) {
	point oldRefPoint = base->getRefPoint();
	point newfwRef;
	point newpwRef;

	newfwRef.x = oldRefPoint.x + (0.3 * config.car.baseWdth)*factor;
	newfwRef.y = oldRefPoint.y + (config.car.baseHeight / 2)*factor;

	newpwRef.x = oldRefPoint.x - (0.3 * config.car.baseWdth) * factor;
	newpwRef.y = oldRefPoint.y + (config.car.baseHeight / 2) * factor;

	frontalWheel->setRefPoint(newfwRef);
	posteriorWheel->setRefPoint(newpwRef);

	base->resizeUp(factor);
	frontalWheel->resizeUp(factor);
	posteriorWheel->resizeUp(factor);
}

void Car::resizeDown(int factor) {
	point oldRefPoint = base->getRefPoint();
	point newfwRef;
	point newpwRef;

	newfwRef.x = oldRefPoint.x + (0.3 * config.car.baseWdth) / factor;
	newfwRef.y = oldRefPoint.y + (config.car.baseHeight / 2) / factor;

	newpwRef.x = oldRefPoint.x - (0.3 * config.car.baseWdth) / factor;
	newpwRef.y = oldRefPoint.y + (config.car.baseHeight / 2) / factor;

	frontalWheel->setRefPoint(newfwRef);
	posteriorWheel->setRefPoint(newpwRef);

	base->resizeDown(factor);
	frontalWheel->resizeDown(factor);
	posteriorWheel->resizeDown(factor);
}

void Car::rotate(double deg)
{
	base->rotate(deg);
	frontalWheel->rotate(deg);
	posteriorWheel->rotate(deg);
}


///////////////////////////////////////////
IceCream::IceCream(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point circleRef = { ref.x, ref.y + config.icecream.baseWdth / 2 };

	base = new triangle(pGame, baseRef, config.icecream.baseWdth);
	iceCircle = new circle(pGame, circleRef, config.icecream.baseWdth/2);
}

void IceCream::draw() const
{
	iceCircle->draw();
	base->draw();
}

void IceCream:: resizeUp(int factor) {
	base->resizeUp(factor);
	//iceCircle->setRadius((config.icecream.baseWdth / 2 )*factor);
	iceCircle->resizeUp(factor);
}
void IceCream::resizeDown(int factor) {
	base->resizeDown(factor);
	iceCircle->resizeDown(factor);
}

void IceCream::rotate(double deg)
{
	base->rotate(deg);
	iceCircle->rotate(deg);
}




////////////////////////////////////////////

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

void Rocket::resizeUp(int factor) {
	point oldHeadRef = head->getRefPoint();
	point oldRbRef = rightbase->getRefPoint();
	point oldLbRef = liftbase->getRefPoint();
	point newHeadRef = {
		oldHeadRef.x,oldHeadRef.y*factor
	};
	point newRbRef= {
			oldRbRef.x*factor,oldRbRef.y * factor
	};
	point newLbRef = {
			oldLbRef.x* factor,oldLbRef.y* factor
	};
	liftbase->setRefPoint(newLbRef);
	rightbase->setRefPoint(newRbRef);
	head->setRefPoint(newHeadRef);

	liftbase->resizeUp(factor);
	rightbase->resizeUp(factor);
	base->resizeUp(factor);
	head->resizeUp(factor);

}
void Rocket::resizeDown(int factor) {
	point oldHeadRef = head->getRefPoint();
	point oldRbRef = rightbase->getRefPoint();
	point oldLbRef = liftbase->getRefPoint();
	point newHeadRef = {
		oldHeadRef.x,oldHeadRef.y /factor
	};
	point newRbRef = {
			oldRbRef.x * factor,oldRbRef.y /factor
	};
	point newLbRef = {
			oldLbRef.x * factor,oldLbRef.y /factor
	};
	liftbase->setRefPoint(newLbRef);
	rightbase->setRefPoint(newRbRef);
	head->setRefPoint(newHeadRef);

	liftbase->resizeUp(factor);
	rightbase->resizeUp(factor);
	base->resizeUp(factor);
	head->resizeUp(factor);

}
void Rocket::rotate(double deg)
{
	rightbase->rotate(deg);
	liftbase->rotate(deg);
	head->rotate(deg);
	base->rotate(deg);
}

///////////////////////////////////////////////////

House::House(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point headRef = { ref.x, ref.y - config.house.baseHeight/2 - (sqrt(3) / 6.0)*config.house.baseWdth };
	point doorRef = { ref.x, ref.y + config.house.baseHeight / 2 - config.house.doorhight / 2 };

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


void House ::resizeUp(int factor) {
	base->resizeUp(factor);
	door->resizeUp(factor);
	head->resizeUp(factor);

	point oldRefPoint = base->getRefPoint();
	point newHeadRef;
	point newDoorRef;
	newHeadRef.x = oldRefPoint.x;
	newHeadRef.y = oldRefPoint.y - (config.house.baseHeight / 2 - (sqrt(3) / 6.0) * config.house.baseWdth);

	newDoorRef.x = oldRefPoint.x;
	newDoorRef.y = oldRefPoint.y + (config.house.baseHeight / 2 - config.house.doorhight / 2) ;
	head->setRefPoint(newHeadRef);
	door->setRefPoint(newDoorRef);


}
void House::resizeDown(int factor) {
	point oldDoorRefPoint = door->getRefPoint();
	point newDoorRefPoint = {
		oldDoorRefPoint.x,oldDoorRefPoint.y/factor
	};
	point oldHeadRefPoint = head->getRefPoint();
	point newHeadRefPoint = {
		oldHeadRefPoint.x,oldHeadRefPoint.y/factor

	};
	door->setRefPoint(newDoorRefPoint);
	head->setRefPoint(newHeadRefPoint);
	base->resizeDown(factor);
	door->resizeDown(factor);
	head->resizeDown(factor);

}

void House::rotate(double deg)
{
	head->rotate(deg);
	base->rotate(deg);
	door->rotate(deg);
}