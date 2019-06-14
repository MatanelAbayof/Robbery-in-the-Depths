#pragma once
//---- include section ------
#include <string>
#include "NPC.h"

//---- using section --------
using std::string;

/*
 * Crab class
 */
class Crab
	: public NPC
{
public:
	// char
	static const char CHAR = 'c';
	// constructor
	explicit Crab(GameScreen& gameScreen, int numOfLife = DEFAULT_LIFE);
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override { return "Crab: { " + NPC::toString() + " }"; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override;
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override;
	virtual void onCollide(MachineGun* machineGun) override {}; // TODO use this
	virtual void onCollide(Grenade* grenade) override;
	virtual void onCollide(Explosion* explosion) override;
	virtual void onCollide(Box* box) override;
	virtual void onCollide(ExitLevel* exitLevel) override {} // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
	// event when direction changed
	virtual void onDirectionChanged() override {}; // TODO: use this
		// event on die
	virtual void onDie() override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 20;
	// minimum radius to see the player
	static const float MIN_PLAYER_RADIUS;
	// default number of life
	static const int DEFAULT_LIFE = 1;
	// damage
	static const int DAMAGE = 1;
	// flag that check if player in crab radius
	bool m_isPlayerInRadius;
	// timer
	Timer m_timer;
	// init
	void init();
	// register flag in BOFactory
	static bool isRegistered;
	// get crab size
	static const sf::Vector2i& getCrabSize();	
	// on collide on solid
	void onCollideSoild(BoardObject* bo);
};

