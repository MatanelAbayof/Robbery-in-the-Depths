//---- include section ------
#include "ImageButton.h"
#include "SoundManager.h"

GUI::ImageButton::ImageButton(sf::RenderWindow& window, const string& text)
	: VerticalLayout<GUI::View>(window)
{
	initComponents(window, text);
}

GUI::ImageTexture& GUI::ImageButton::getImage()
{
	return m_image->getImage();
}

void GUI::ImageButton::setText(const string& text)
{
	m_text->setText(text);
}

string GUI::ImageButton::getText() const
{
	return m_text->getText();
}

void GUI::ImageButton::setTextColor(const sf::Color& textColor)
{
	m_text->setTextColor(textColor);
}

sf::Color GUI::ImageButton::getTextColor() const
{
	return m_text->getTextColor();
}

void GUI::ImageButton::setTextHAligment(TextView::TextHAlignment textHAl)
{
	m_text->setTextHAlignment(textHAl);
}

string GUI::ImageButton::toString() const
{
	return "ImageButton: { " + VerticalLayout<GUI::View>::toString() + " }";
}

void GUI::ImageButton::initComponents(sf::RenderWindow& window, const string& text)
{
	// create views
	m_image = std::make_shared<ImageView>(window);
	m_text = std::make_shared<TextView>(window, text);

	// set my border
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1);

	// set buttons border
	Border buttonBorder(sf::Color::Black, 1);

	addView(m_image, 0.75f);
	addView(m_text, 0.25f);
}
