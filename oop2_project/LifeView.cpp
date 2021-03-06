#include "LifeView.h"

LifeView::LifeView(sf::RenderWindow& window, int numOfLife)
	: HorizontalLayout(window)
{
	init();
	if (numOfLife > Character::getMaxLife()) {
		throw(std::out_of_range("Cant have more life then " + Character::getMaxLife()));
	}
	setNumOfLife(numOfLife);
}

void LifeView::updateLifeParts(int numOfLife)
{
	float lifeMissingPrecent, lifeLeftPrecent;
	lifeMissingPrecent = lifeLeftPrecent = static_cast<float>(numOfLife);
	lifeLeftPrecent /= Character::getMaxLife();
	lifeMissingPrecent = (Character::getMaxLife() - lifeMissingPrecent) / Character::getMaxLife();
	this->setRelativeWidth(0, lifeLeftPrecent);
	this->setRelativeWidth(1, lifeMissingPrecent);
	if (lifeLeftPrecent > lifeMissingPrecent) {
		m_barFullPart->getBackground().setColor(sf::Color(int(255.f * lifeMissingPrecent * 2.f), 255, 0));
	}
	else {
		m_barFullPart->getBackground().setColor(sf::Color(255, int(255.f * lifeLeftPrecent * 2.f), 0));
	}
}

void LifeView::setNumOfLife(int numOfLife)
{
	checkLegalLife(numOfLife);
	if (numOfLife <= Character::getMaxLife()) {
		m_numOfLife = numOfLife;
		updateLifeParts(numOfLife);
	}
}

string LifeView::toString() const
{
	return "LifeView: { " + HorizontalLayout::toString() + " }";
}

void LifeView::checkLegalLife(int numOfLife) const
{
	if (numOfLife < 0)
		throw std::out_of_range("Number of life (=" + std::to_string(numOfLife) + ") is illegal");
}

void LifeView::init()
{
	getBorder().setColor(sf::Color::Black);
	m_barFullPart = std::make_shared<GUI::ImageView>(getWindow());
	m_barFullPart->getBackground().setColor(sf::Color::Green);
	addView(m_barFullPart);
	m_barEmptyPart = std::make_shared<GUI::ImageView>(getWindow());
	m_barEmptyPart->getBackground().setColor(sf::Color(100,100,100));
	addView(m_barEmptyPart);
}
