#pragma once
//---- include section ------
#include <string>
#include "BoardObject.h"

//---- using section --------
using std::string;

/*
 * InteractableObject class
 */
class InteractableObject
	:public BoardObject
{
public:
	// constructor
	explicit InteractableObject(sf::RenderWindow& window, GameScreen& gameScreen);
	// convert to string
	// TODO
	virtual string toString() const override { return "InteractableObject: {" + BoardObject::toString() + "}"; }
private:

};
