#pragma once
//---- include section ------
#include <string>
#include "VerticalLayout.h"
#include "GameObjectView.h"

//---- using section --------
using std::string;

/*
 * GameObjectsList class
 */
class GameObjectsList
	: public GUI::VerticalLayout<GameObjectView>
{
public:
	// base class
	using BaseClass = GUI::VerticalLayout<GameObjectView>;
	// constructor
	explicit GameObjectsList(sf::RenderWindow& window);
	// add game object view click listener
	void addGOVClickListener(std::function<void(const std::shared_ptr<GameObjectView>&)> onGOVClicked);
	// convert to string
	virtual string toString() const override;
private:
	// list of game object view
	std::vector<std::shared_ptr<GameObjectView>> m_gameObjects;
	// init components
	void initComponents();
};
