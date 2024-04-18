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
void Sign::resizeUp(int factor) {
	point oldRefBottom = base->getRefPoint();
	point newRefBottom;
	newRefBottom.y = base->getHeight() + top->getRefPoint().y + top->getHeight();
	newRefBottom.x = oldRefBottom.x;
	base->setRefPoint(newRefBottom);

	top->resizeUp(factor);
	base->resizeUp(factor);

}

void Sign::resizeDown(int factor)  {
	point oldRefBottom = base->getRefPoint();
	point newRefBottom;
	newRefBottom.y = base->getHeight() + top->getRefPoint().y + top->getHeight();
	newRefBottom.x = oldRefBottom.x;
	base->setRefPoint(newRefBottom);

	top->resizeDown(factor);
	base->resizeDown(factor);

}




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
	base->resizeUp(factor);
	//frontalWheel->setRadius(config.car.wheelRadius *factor);
	frontalWheel->resizeUp(factor);
	posteriorWheel->resizeUp(factor);
}
void Car::resizeDown(int factor) {
	base->resizeDown(factor);
	//frontalWheel->setRadius(config.car.wheelRadius / factor);
	frontalWheel->resizeDown(factor);
	posteriorWheel->resizeDown(factor);
}

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

House::House(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	point baseRef = ref;
	point headRef = { ref.x, ref.y - config.house.baseHeight / 2 - config.house.headwdth / 2 };
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
	point oldDoorRefPoint = door->getRefPoint();
	point newDoorRefPoint = {
		oldDoorRefPoint.x,oldDoorRefPoint.y* factor
	};
	point oldHeadRefPoint = head->getRefPoint();
	point newHeadRefPoint = {
		oldHeadRefPoint.x,oldHeadRefPoint.y*factor

	};
	door->setRefPoint(newDoorRefPoint);
	head->setRefPoint(newHeadRefPoint);
	base->resizeUp(factor);
	door->resizeUp(factor);
	head->resizeUp(factor);

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