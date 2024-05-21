#pragma once

class game;
/////////////////////////////////// class operation  //////////////////
//Base class of all operations supported by the application
class operation
{
protected:
	game* pGame;	//pointer to the game class
public:
	operation(game* r_pGame);

	//Function Act:
	//Implements the action that should be taken by this operation
	//Should be overriden by derived classes
	virtual void Act() = 0;
	int c = 0;
};
/////////////////////////////////// class operAddSign  //////////////////
//Responsible for 
//1- collectign data about a new Sign shape to add
//2- Adding the new shape to the list of shapes (throgh the grid class)
class operAddSign :public operation
{
public:
	operAddSign(game* r_pGame);
	virtual void Act();
};


class operRocket :public operation {
public:
	operRocket(game* r_pGame);
	virtual void Act();

};


class operAddIceCream : public operation
{
public:
	operAddIceCream(game* r_pGame);
	virtual void Act();


};
class operAddCar : public operation
{
public:
	operAddCar(game* r_pGame);
	virtual void Act();


};
class operAddHouse : public operation
{
public:
	operAddHouse(game* r_pGame);
	virtual void Act();


};

class operAddTree : public operation
{
public:
	operAddTree(game* r_pGame);
	virtual void Act();


};

class operDELETE : public operation
{
public:
	operDELETE(game* r_pGame);
	virtual void Act();
};

class operResizeUp :public operation {
public:
	operResizeUp(game* r_pGame);
	virtual void Act();
};

class operResizeDown :public operation {
public:
	operResizeDown(game* r_pGame);
	virtual void Act();
};



class operRotate : public operation
{
public:
	operRotate(game* r_pGame);
	virtual void Act();


};

class operRefresh : public operation
{
public:
	operRefresh(game* r_pGame);
	virtual void Act();


};


class operMoveUp : public operation
{
public:
	operMoveUp(game* r_pGame);
	virtual void Act();
};

class operMoveDown : public operation
{
public:
	operMoveDown(game* r_pGame);
	virtual void Act();
};


class operMoveRight : public operation
{
public:
	operMoveRight(game* r_pGame);
	virtual void Act();
};


class operMoveLeft : public operation
{
public:
	operMoveLeft(game* r_pGame);
	virtual void Act();
};
class operSaveProgress : public operation
{
public:
	operSaveProgress(game* r_pgame);
	virtual void Act();
};

class operHint : public operation
{
public:
	operHint(game* r_pgame);
	virtual void Act();
};


class operRandomizeShapes :public operation
{
public:
	operRandomizeShapes(game* r_pgame);
	virtual void Act();
};

class operSelectLevel :public operation
{
public:
	operSelectLevel(game* r_pGame);
	virtual void Act();
};

class operLoad : public operation
{
public:
	operLoad(game* r_pGame);
	virtual void Act();
};

class operExit : public operation
{
public:
	operExit(game* r_pGame);
	virtual void Act();

};

class operPowerUp : public operation
{
public:
	operPowerUp(game* r_pGame);
	virtual void Act();

};