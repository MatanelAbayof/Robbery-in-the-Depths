#include "~main_tests.h"
#ifdef MATANEL_TESTS

 //-------------- include section ---------------
#pragma region Includes
#include <Box2D/Box2D.h>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp> // JSON library
#include <iostream>
#include "VerticalLayout.h"
#include "ErrorDialog.h"
#include "Button.h"
#include "MainScreen.h"
#include "LevelInfo.h"
#include "LevelFileManager.h"
#include "Matrix.h"
#include "GameObjectInfo.h"
#include "GOIFileParser.h"
#include "GameObjectView.h"
#include "GameObjectsList.h"
#include "BODS.h"
#include "GameScreen.h"
#include "World.h"
#include "Shark.h"
#include "Wall.h"
#include "Crab.h"
#include "Chest.h"
#include "EditMapView.h"
#include "Flow.h"
#include "EditMenu.h"
#include "EditScreen.h"
#include "AK47.h"
#include "Rubber.h"
#include "GameController.h"
#include "Grenade.h"
#include "GrenadeLauncher.h"
#include "BOFactory.h"
#include "Utilities.h"
#include "MachineGun.h"
#include "Box.h"
#include "GameAnimText.h"
#pragma endregion

 //-------------- libs -------------------------
#pragma region Libs
// for SFML library
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#pragma comment ( lib, "sfml-network-d.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#else
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#pragma comment ( lib, "sfml-network.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#endif
#pragma endregion

//-------------- using section -----------------
#pragma region Usings
using namespace GUI; // for tests only
#pragma endregion

//-------------- declare functions -------------
#pragma region Declarations
void testGameAnimText();
void testBOFactory();
void testGameController();
void testEditMenu();
void testEditor();
void testBox2DLib();
void testWorld();
void testBODS();
void testGameObjectView();
void testGameObjectInfo();
void testMatrix();
void testLevelFileManager();
void testLevelInfo();
void testMainScreen();
void testGUI();
void testGradientColor();
void testCleanScreen();
#pragma endregion

// -------------- globals & constants -----------
#pragma region globals & constants

#pragma endregion

//--------------  main ---------------------------
void matanel_main()
{
    std::cout << "Hello Matanel World!\n";
	// initialize random seed
	srand(unsigned (time(NULL)));
	GUI::SoundManager::getInterface();
	try
	{
		//testGameAnimText();
		//testBOFactory();
		//testGradientColor();
		testGameController();
		//testEditor();
		//testWorld();
		//testEditMenu();
		//testBox2DLib();
		//testBODS();
		//testGameObjectView();
		//testGameObjectInfo();
		//testMatrix();
		//testLevelFileManager();
		//testLevelInfo();
		//testMainScreen();
		//testGUI();
		//testCleanScreen();
	}
	catch (const std::exception& ex)
	{
		// Oh No! error...
		ErrorDialog::show(ex.what());
	}
}

void testGameAnimText() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	std::shared_ptr<GameAnimText> gat = std::make_shared<GameAnimText>(window);
	//for(int i = 0; i < 10; ++i)
	//	gat->showText("Text " + std::to_string(i));

	int c = 0;
	gat->addClickListener([&gat, &c](View& v) {
		//gat->showText("Text " + std::to_string(c));
		c++;
	});
	mainLayout.addView(gat);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

void testGameController() {
	GameController gameController;
	gameController.run();
}

void testBOFactory() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Screen");
	window.close();
	GameScreen gameScreen(window);


	BOFactory& boFactory = BOFactory::getInterface();
	

	// create BOs
	std::vector<std::shared_ptr<BoardObject>> bos;
	for (int i = 0; i < 10; ++i) {
		//char c = (i % 2 == 0) ? Player::CHAR : Shark::CHAR;
		//auto bo = boFactory.create(c, gameScreen);
		//bos.push_back(bo);
	}

	std::cout << boFactory.getInterface().toString() << std::endl;

	std::cout << "BOs:" << std::endl;
	for (auto& bo : bos) {
		std::cout << bo->toString() << std::endl;
	}
}

void testEditor() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Screen");

	// create editor
	EditScreen editScreen(window);

	// load level info
	LevelFileManager lfm;
	const LevelInfo& levelInfo = lfm.getLevel("matanel map");
	editScreen.getEditMapView()->importLevelInfo(levelInfo);

	editScreen.getEditMenu()->getExitButton()->addClickListener([&editScreen](View& v) {
		editScreen.close();
	});
	editScreen.getEditMenu()->getSaveButton()->addClickListener([&editScreen, &lfm](View& v) {
		const LevelInfo& levelInfo = editScreen.getEditMapView()->exportLevelInfo();
		lfm.editLevel(levelInfo);
		AlertDialog::show("Level saved!", "The level saved successfuly!", "OK");
	});
	editScreen.getEditMapView()->forEach([&editScreen](const Cell& cell, const std::shared_ptr<MapCellView>& mapCellView) {
		mapCellView->addEnterListener([&editScreen, cell](View& v){
			editScreen.getEditMenu()->setCurrentCell(cell);
		});
	});
	editScreen.getGameObjs()->addGOVClickListener([&editScreen](const std::shared_ptr<GameObjectView>& gov) {
		editScreen.getEditMapView()->setEditMode(EditMapView::EditMode::Add);
		editScreen.getEditMapView()->setAddChar(gov->getGOI().getSpecialChar());
	});
	editScreen.getEditMenu()->getDeleteButton()->addClickListener([&editScreen](View& view) {
		editScreen.getEditMapView()->setEditMode(EditMapView::EditMode::Remove);
	});

	editScreen.run();
}

void testWorld() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Screen");

	GameScreen gameScreen(window);

	// load level info
	LevelFileManager lfm;
	const LevelInfo& levelInfo = lfm.getLevel("The Shark Territory");
	gameScreen.loadLevel(levelInfo);

	// get player
	std::shared_ptr<Player> player = gameScreen.getWorld().getBODS().getPlayer();
	auto gl = std::make_shared<GrenadeLauncher>(player.get());
	gl->setInfLimit();
	auto ak47 = std::make_shared<AK47>(player.get());
	ak47->setInfLimit();
	player->addTool(gl);
	player->addTool(ak47);
	
	gameScreen.getWorld().addKeyDownListener([&gameScreen, &player](sf::Keyboard::Key& keyCode) {
		float offset = 10.f;
		sf::Vector2f mousePos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));
		switch (keyCode)
		{
		case sf::Keyboard::Key::U: {
			player->setTransparency(player->getTransparency() - 10);
		} break;
		case sf::Keyboard::Key::K: {
			GameAnimText::TextInfo ti;
			ti.m_color = sf::Color(255, 0, 0);
			ti.m_text = "Example Text";
			gameScreen.getGameAnimText()->showText(ti);
		} break;
		case sf::Keyboard::Key::Num2: {
			gameScreen.getWorld().getCamera().zoom(0.95f);
		} break;
		case sf::Keyboard::Key::Num1: {
			gameScreen.getWorld().getCamera().zoom(1.05f);
		} break;
		case sf::Keyboard::Key::P: {
			std::cout << "-------------------------------------------------" << std::endl;
			std::cout << gameScreen.getWorld().getBODS().toString() << std::endl;
		} break;
		case sf::Keyboard::Key::W: {
			std::shared_ptr<Wall> wall = std::make_shared<Wall>(gameScreen);
			wall->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(wall);
		} break;
		case sf::Keyboard::Key::C: {
			std::shared_ptr<Crab> crab = std::make_shared<Crab>(gameScreen);
			crab->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(crab);
		} break;
		case sf::Keyboard::Key::T: {
			std::shared_ptr<Chest> chest = std::make_shared<Chest>(gameScreen);
			chest->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(chest);
		} break;
		case sf::Keyboard::F: {
			std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
			flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);
			flow->setPosition(mousePos);
			flow->setFlow(sf::Vector2f(0.0025f, 0.f));
			gameScreen.getWorld().getBODS().requestAddBO(flow);
		} break;
		case sf::Keyboard::H: {
			std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
			flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);
			flow->setPosition(mousePos);
			flow->setFlow(sf::Vector2f(0.f, 0.0025f));
			gameScreen.getWorld().getBODS().requestAddBO(flow);
		} break;
		case sf::Keyboard::J: {
			std::shared_ptr<Flow> flow = std::make_shared<Flow>(gameScreen);
			flow->setSize(BoardObject::getDefaultSize().x * 4, BoardObject::getDefaultSize().y * 4);
			flow->setPosition(mousePos);
			flow->setFlow(sf::Vector2f(0.f, -0.0025f));
			gameScreen.getWorld().getBODS().requestAddBO(flow);
		} break;
		case sf::Keyboard::R: {
			std::shared_ptr<Rubber> rubber = std::make_shared<Rubber>(gameScreen);
			rubber->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(rubber);
		} break;
		case sf::Keyboard::G: {
			std::shared_ptr<Grenade> grenade = std::make_shared<Grenade>(gameScreen, player.get());
			grenade->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(grenade);
		} break;
		case sf::Keyboard::M: {
			std::shared_ptr<MachineGun> mg = std::make_shared<MachineGun>(gameScreen, MachineGun::Direction::RIGHT);
			auto gl = std::make_shared<GrenadeLauncher>(mg.get());
			gl->setInfLimit();
			mg->setWeapon(gl);
			mg->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(mg);
		} break;
		case sf::Keyboard::B: {
			std::shared_ptr<Box> box = std::make_shared<Box>(gameScreen);
			box->setPosition(mousePos);
			gameScreen.getWorld().getBODS().requestAddBO(box);
		} break;
		case sf::Keyboard::LControl: {
			player->setNumOfLife(Player::getMaxLife());
		} break;
		}
	});
	gameScreen.getWorld().addClickListener([&gameScreen](View& view) {
		sf::Vector2f pos = gameScreen.getWorld().getWindow().mapPixelToCoords(sf::Mouse::getPosition(gameScreen.getWorld().getWindow()));

		std::shared_ptr<Shark> shark = std::make_shared<Shark>(gameScreen);
		shark->setPosition(pos);
		gameScreen.getWorld().getBODS().requestAddBO(shark);
	});

	gameScreen.getWorld().getCamera().zoom(1.5f);
	gameScreen.run([&gameScreen, &player]() {
		gameScreen.getWorld().getBODS().handleRequests();
	});
}

void testEditMenu() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	// add edit menu
	std::shared_ptr<EditMenu> em = std::make_shared<EditMenu>(window);
	mainLayout.addView(em);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

void testBODS() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	GameScreen gameScreen(window);
	BODS bods;

	for (int i = 0; i < 15; ++i) {
		std::shared_ptr<Shark> bo = std::make_shared<Shark>(gameScreen);
		bo->setPosition(sf::Vector2f{ float(i),float(i) });
		bo->setSize(sf::Vector2i{ i,i });
		bods.requestAddBO(bo);
	}
	bods.requestAddBO(std::make_shared<Player>(gameScreen));

	bods.handleRequests();

	bods.prepareLevel(); // must use this!!!!!!!



	/*for (auto it = bods.getBOs().begin(); it != bods.getBOs().end(); ++it) {
		BoardObject* bo = &**it;
		bods.getAABBTree().updateObject(bo);
		auto ov = bods.getAABBTree().queryOverlaps(bo);
		int ovSize = 0;
		for (auto ovIt = ov.begin(); ovIt != ov.end(); ++ovIt)
			ovSize++;
		std::cout << ovSize << std::endl;
	}*/
	
	//bods.requestRemoveBO(*bods.getBOs().begin());
	//bods.handleRequests();

	std::cout << bods.getPlayer()->toString() << std::endl;
	//std::cout << bods.toString() << std::endl;
}

void testBox2DLib() {
	struct QueryHandler
	{
		bool QueryCallback(int32 proxyId) {
			std::cout << "QueryCallback. prId=" << proxyId << std::endl;
			return true;
		}
	};

	struct Actor {
		int id;
		int32 m_proxyId;
		b2AABB m_aabb;
	};

	std::vector<std::shared_ptr<Actor>> actors;
	b2DynamicTree tree;
	QueryHandler queryHandler;

	// insert
	for (int i = 0; i < 10; ++i) {
		std::shared_ptr<Actor> actor = std::make_shared<Actor>();
		actors.push_back(actor);
		actor->id = i;
		actor->m_aabb.lowerBound = b2Vec2(float(i), float(i));
		actor->m_aabb.upperBound = b2Vec2(float(i + 1), float(i + 1));
		actor->m_proxyId = tree.CreateProxy(actor->m_aabb, static_cast<void*>(actor.get()));
	}

	auto lastAABB = actors[0]->m_aabb;
	actors[0]->m_aabb = actors[1]->m_aabb;
	b2Vec2 displacement = actors[0]->m_aabb.GetCenter() - lastAABB.GetCenter();
	tree.MoveProxy(actors[0]->m_proxyId, actors[0]->m_aabb, displacement);


	/*// move
	for (auto& actor : actors) {
		b2AABB aabb0 = actor->m_aabb;
		b2Vec2 displacement = actor->m_aabb.GetCenter() - aabb0.GetCenter();
		tree.MoveProxy(actor->m_proxyId, actor->m_aabb, displacement);
	}*/


	// query
	for (auto& actor : actors) {
		std::cout << "act=" << actor->m_proxyId << std::endl;
		tree.Query(&queryHandler, actor->m_aabb);
	}

	// remove
	for (auto& actor : actors) {
		tree.DestroyProxy(actor->m_proxyId);
	}
}


void testGameObjectView() {
	/*

	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);


	std::shared_ptr<GameObjectsList> gol = std::make_shared<GameObjectsList>(window);
	mainLayout.addView(gol);

	gol->addGOVClickListener([](const std::shared_ptr<GameObjectView>& gov) {
		std::cout << gov->getGOI().getName() << std::endl;
	});

	std::cout << mainLayout.toString() << std::endl;
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}*/
}

void testGameObjectInfo() {
	std::vector<GameObjectInfo> gois = GOIFileParser::parseGOIFile();
	for (GameObjectInfo& goi : gois)
		std::cout << goi.toString() << std::endl;

	//json goiJSON = { { "name", "player" }, { "isUnique", true }, { "specialChar", 'a' } };
	//GameObjectInfo goi = GameObjectInfo::parse(goiJSON);
	//std::cout << goi.toString() << std::endl;
}

void testMatrix() {
	Matrix<int> m(5, 3);
	int i = 0;
	for (auto it = m.begin(); it != m.end(); ++it) {
		(*it) = i;
		i++;
	}

	for (auto it = m.cbegin(); it != m.cend(); ++it) {
		std::cout << it.getCell().toString() << "\n";
	}

	for (auto n : m) {
		std::cout << n << "\n";
	}
}

void testLevelFileManager() {
	LevelFileManager lfm;
	//std::cout << lfm.toString() << std::endl;


	// create level
	/*LevelInfo li;
	li.getLevelChars().resize(150, 25);
	for (char& c : li.getLevelChars()) {
		c = ' ';
	}
	li.setName("Tsunami on the way");
	li.setIndex(8);
	lfm.addLevel(li);*/

	for (int i = 0; i < lfm.getNumOfLevels(); ++i) {
		const LevelInfo& levelInfo = lfm.getLevel(i);
		std::cout << levelInfo.toString() << std::endl;
		std::cout << levelInfo.toJSON() << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
	}
	//LevelInfo levelInfo = lfm.getLevel(0);
	//levelInfo.getLevelChars().resize(0, 0);
	//lfm.editLevel(levelInfo);

	//const LevelInfo& levelInfo = lfm.getLevel("level2");
	//lfm.addLevel(lfm.getLevel(0));
}

void testLevelInfo() {
	LevelInfo levelInfo;
	levelInfo.setIndex(2);
	levelInfo.setName("dasds");
	levelInfo.getLevelChars().resize(3, 5);
	Matrix<char>& levelChars = levelInfo.getLevelChars();
	for (int rowNum = 0; rowNum < levelChars.getNumOfRows(); ++rowNum) {
		for (int colNum = 0; colNum < levelChars.getNumOfCols(); ++colNum) {
			Cell cell(rowNum, colNum);
			levelChars[cell] = 'a';
		}
	}	
	std::cout << levelInfo.toString() << std::endl;
	std::cout << levelInfo.toJSON() << std::endl;
	std::cout << "check inversed:" << std::endl;
	std::cout << LevelInfo::parse(levelInfo.toJSON()).toJSON() << std::endl;
}

void testMainScreen() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	MainScreen mainScreen(window);
	mainScreen.run();
}

void testGUI() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	// create buttons
	for (int i = 0; i < 3; i++) {
		std::shared_ptr<Button> bt = std::make_shared<Button>(window, "Button " + std::to_string(i));
		bt->addClickListener([](View& v) {
			v.disable();
		});
		mainLayout.addView(bt);
	}
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

void testGradientColor() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");


	
	sf::Color fromColor(76, 226, 255), toColor(15, 0, 80);
	sf::Vertex rectangle[] =
	{
		sf::Vertex({0,0}, fromColor),
		sf::Vertex({float(window.getSize().x), 0}, fromColor),
		sf::Vertex({float(window.getSize().x), float(window.getSize().y)}, toColor),
		sf::Vertex({0, float(window.getSize().y)}, toColor)
	};

	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(rectangle, 4, sf::Quads);
		window.display();
	}
}

void testCleanScreen() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

#endif // MATANEL_TESTS