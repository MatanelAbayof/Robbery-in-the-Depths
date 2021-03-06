#pragma once

//---- include section ------
#include <string>
#include "NPC.h"
#include "MovingObject.h"
#include "AK47.h"
#include "Timer.h"

//---- using section --------
using std::string;

/*
 * MachineGun class
 */
class MachineGun :
	public NPC
{
public:
	// constructor
	explicit MachineGun(GameScreen& gameScreen, MovingObject::Direction directoin);
	// get gun
	const std::shared_ptr<HotWeapon>& getGun() const { return m_gun; }
	// check if this object is don't blocking movement
	virtual bool canMoveThroughMe() const override { return false; }
	// draw
	virtual void draw() override;
	// set weapon
	void setWeapon(const std::shared_ptr<HotWeapon>& weapon) { m_gun = weapon; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override {}
	virtual void onCollide(Player* player) override {}
	virtual void onCollide(Shark* shark) override {}
	virtual void onCollide(Crab* crab) override {}
	virtual void onCollide(Rubber* rubber) override {}
	virtual void onCollide(Chest* chest) override {}
	virtual void onCollide(Wall* wall) override {}
	virtual void onCollide(Flow* flow) override {}
	virtual void onCollide(Bullet* bullet) override;
	virtual void onCollide(MachineGun* machineGun) override {}
	virtual void onCollide(Grenade* grenade) override {}
	virtual void onCollide(Explosion* explosion) override {}
	virtual void onCollide(Box* box) override {}
	virtual void onCollide(ExitLevel* exitLevel) override {}
	// convert to string
	virtual string toString() const override { return "MachineGun: { " + InteractableObject::toString() + " }"; }
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override {};
	// event when direction changed
	virtual void onDirectionChanged() override { }
	// make float effect
	virtual void floatEffect() override { setFloatAcc(sf::Vector2f(0.f, 0.f)); }
private:
	// register flags in BOFactory
	static bool isRegisteredLeft, isRegisteredRight, isRegisteredUp, isRegisteredDown;
	// chars
	static const char CHAR_LEFT_MG = '1';
	static const char CHAR_RIGHT_MG = '2';
	static const char CHAR_UP_MG = '3';
	static const char CHAR_DOWN_MG = '4';
	// draw priority
	static const int DRAW_PRIORITY = 7;
	// default number of life
	static const int DEFAULT_LIFE = INT_MAX;
	// shooting pause seconds
	static const int SHOOTING_PAUSE_SECONDS= 2;
	// radius shot
	static const float RADIUS_SHOT;
	// gun
	std::shared_ptr<HotWeapon> m_gun;
	// timer
	Timer m_time;
	// shooting pause clock
	sf::Clock shootingPauseClock;
	// init
	void init();
	// check if can shot
	bool canShot() const;
};

