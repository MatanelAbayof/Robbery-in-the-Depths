#pragma once
//---- include section ------
#include <string>
#include "MovingObject.h"
#include "Character.h"

//---- using section --------
using std::string;

/*
 * Projectile class
 */
class Projectile :
	public MovingObject
{
public:
	// convert to string
	virtual string toString() const override { return "Projectile { " + MovingObject::toString() + " }"; }
	// get my owner
	Character* getMyOwner() { return m_owner; }
protected:
	// constructor
	explicit Projectile(GameScreen& gameScreen, Character* owner, Direction direction = Direction::RIGHT);
private:
	// draw priority
	static const int DRAW_PRIORITY = 22;
	// my owner
	Character* m_owner;
	// init
	void init(Direction direction);	
};

