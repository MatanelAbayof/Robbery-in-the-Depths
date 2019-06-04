#include "EditScreen.h"

EditScreen::EditScreen(sf::RenderWindow& window)
	: BaseClass(window)
{
	initComponents();
}

string EditScreen::toString() const
{
	return "EditScreen: { " + BaseClass::toString() + " }";
}

void EditScreen::initComponents()
{
	getBackground().setColor(sf::Color::Transparent);

	// init edit map view
	m_editMapView = std::make_shared<EditMapView>(getWindow());
	//m_editMapView->getCamera().setViewport(sf::FloatRect(0.f, 0.3f, 1.f, 0.7f)); // TODO not work
	addBackRootView(m_editMapView);

	// init edit menu
	m_editMenu = std::make_shared<EditMenu>(getWindow());
	addView(m_editMenu, sf::FloatRect(0.f, 0.f, 1.f, 0.1f));

	// init game objects
	m_gameObjs = std::make_shared<GameObjectsList>(getWindow());
	addView(m_gameObjs, sf::FloatRect(0.f, 0.1f, 1.f, 0.1f));
}