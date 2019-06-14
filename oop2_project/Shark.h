#pragma once
//---- include section ------
#include <string>
#include "NPC.h"

//---- using section --------
using std::string;

/*
 * Shark class
 */
class Shark
	: public NPC
{
public:
	// char
	static const char CHAR = 's';
	// constructor
	explicit Shark(GameScreen& gameScreen, int numOfLife = DEFAULT_LIFE);
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "Shark: { " + NPC::toString() + " }"; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override;
	virtual void onCollide(MachineGun* machineGun) override {} // TODO use this
	virtual void onCollide(Grenade* grenade) override;
	virtual void onCollide(Explosion* explosion) override;
	virtual void onCollide(Box* box) override {}  // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override;
	// event on die
	virtual void onDie() override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 70;
	// default number of life
	static const int DEFAULT_LIFE = 3;
	// damage
	static const int DAMAGE = 2;
	// register flag in BOFactory
	static bool isRegistered;
	// radius attak
	static const float RADIUS_ATTACK;
	// thinking time
	Timer m_thinkingTime;
	// flag that check if he is in thinking state
	bool m_isInThinking;
	// flag that check if he is in radius from player
	bool m_isInRadiusFromPlayer;
	// play when inside radius from player
	void inRadiusFromPlayer();
	// init
	void init();
	// get shark size
	static const sf::Vector2i& getSharkSize();	
};


