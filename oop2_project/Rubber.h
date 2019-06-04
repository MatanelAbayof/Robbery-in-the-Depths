#pragma once
//---- include section ------
#include <string>
#include "NPC.h"
#include "AK47.h"
#include "Tool.h"
#include "Timer.h"

//---- using section --------
using std::string;

/*
 * Rubber class
 */
class Rubber :
	public NPC
{
public:
	// char
	static const char CHAR = 's';
	// constructor
	explicit Rubber(GameScreen& gameScreen, int numOfLife = DEFAULT_LIFE);
	// event when direction changed
	virtual void onDirectionChanged() override;
	// draw
	virtual void draw() override;
	// get gun
	const std::shared_ptr<Tool>& getTool() const { return m_tool; }
	// event on die
	virtual void onDie() override;
	// convert to string
	virtual string toString() const override { return "Rubber: { " + NPC::toString() + " }"; }
	// collide events (using with double dispatch)
	virtual void onCollide(BoardObject* obj) override { obj->onCollide(this); }
	virtual void onCollide(Player* player) override {} // TODO use this
	virtual void onCollide(Shark* shark) override {} // TODO use this
	virtual void onCollide(Crab* crab) override {} // TODO use this
	virtual void onCollide(Rubber* rubber) override {} // TODO use this
	virtual void onCollide(Chest* chest) override {} // TODO use this
	virtual void onCollide(Wall* wall) override {} // TODO use this
	virtual void onCollide(Flow* flow) override;
	virtual void onCollide(Bullet* bullet) override {} // TODO use this
protected:
	// the object choose where to go
	virtual void playChoice(Direction lastDirection, bool isCollided) override;
private:
	// draw priority
	static const int DRAW_PRIORITY = 80;
	// default number of life
	static const int DEFAULT_LIFE = 6;
	// init
	void init();
	// radius attak
	float m_radiusAttack;
	// radius shot
	float m_radiusShot;
	// gun
	std::shared_ptr<Tool> m_tool;
	// time
	Timer m_time;
};

