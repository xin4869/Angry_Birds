#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <fstream>
#include <queue>
#include "objects/get_object_defaults.hpp"
#include "slingshot.hpp"
#include "objects/object.hpp"

class Level
{
public:
	Level(const std::string& levelPath, float frameRate = 60.0f) :
			frameRate(frameRate), timeStep(1.0f / frameRate), gravity(0, -10), world(gravity)
	{
		world.SetGravity(gravity);
		world.SetContactListener(&collisionHandler);
		loadLevel(levelPath);
	}
	Level(int level, float frameRate = 60.0f) : Level(getFilePath(level), frameRate) {}
	Level() : world(b2Vec2(0, -10)), gravity(0, -10), frameRate(60.0f), timeStep(1.0f / 60.0f) {
		world.SetContactListener(&collisionHandler);
	}
	~Level() { clearLevel(); }

	void loadLevel(const std::string path) {
		clearLevel();
		gravity.Set(0, -10);
		slingshot.setPos(0, 2);
		scoreLimits = { 1000, 2000, 3000 };
		
		std::ifstream file(path);

		if(!file.is_open()) {
			std::cerr << "Failed to open level file." << std::endl;
			return;
		}

		parseLevelFile(file);
		addGround();
		isActive = true;
  	}

	void loadLevel(int level) {
		loadLevel(getFilePath(level));
	}

	void update() {
		if (!isActive) return;
		world.Step(timeStep, velocityIterations, positionIterations);

		for (auto i = Object::destroyList.begin(); i != Object::destroyList.end(); i++) {
			(*i).first -= timeStep;
			if ((*i).first <= 0) {
				i = Object::destroyList.erase(i);
				i--;
			}
			if ((*i).second != nullptr) (*i).second->getBody()->SetEnabled(false);
		}
	}

	int getStars() {
		for (size_t stars=0; stars<scoreLimits.size(); stars++) {
			if (score < scoreLimits[stars]) return stars;
		}
		return scoreLimits.size();
	}

	b2World& getWorld() { return world; }
	Slingshot& getSlingshot() { return slingshot; }
	void setActive(bool active) { isActive = active; }
	float getScore() { return score; }
	void setScore(float value) { score = value; }
	void addScore(float add) { score += add; }
	void launchObject(Object* object) { slingshot.launchObject(object); }

protected:
	void clearLevel() {
		for (auto i: birds) { delete i; }
		birds.clear();

		for (auto i: pigs) { delete i; }
		pigs.clear();

		for (auto i: blocks) { delete i; }
		blocks.clear();

		for (auto i=world.GetBodyList(); i!=nullptr; i->GetNext()) {
			world.DestroyBody(i);
		}
		isActive = false;
	}

	const std::string getFilePath(int level) {
		return "assets/levels/level" + std::to_string(level) + ".lvl";
	}

	void parseLevelFile(std::ifstream& file) {
		std::string line;
		std::stringstream lineStream;

		while (!file.eof())
		{
			getline(file, line);
			toLower(line);
			
			if (line[0] == '#' || line == "") continue;
			
			lineStream = std::stringstream(line);
			parseLine(lineStream);
		}
		world.SetGravity(gravity);
		file.close();
	}

	void parseLine(std::stringstream& lineStream) {
		std::string parameter;
		getline(lineStream, parameter, ',');
		if (addBird(parameter)) return;

		float x = readFloat(lineStream);
		float y = readFloat(lineStream);
		float z = readFloat(lineStream);
		
		if (x == FLT_MIN || y == FLT_MIN) return;

		if (setSetting(parameter, x, y, z)) return;
		if (addPig(parameter, x, y)) return;
		addBlock(parameter, x, y);
	}

	bool addBird(const std::string& className) {
		if (ObjectDefs::getBirdDefaults(className) == nullptr) return false;
		unusedBirds.push(className);
		return true;
	}

	bool addPig(const std::string& pigName, float x, float y) {
		ObjectDefs::ObjectDefaults* defaults = ObjectDefs::getPigDefaults(pigName);
		if (defaults == nullptr) return false;
		pigs.push_back(new Pig(&world, x, y, defaults));
		return true;
	}

	bool addBlock(const std::string& blockName, float x, float y) {
		ObjectDefs::ObjectDefaults* defaults = ObjectDefs::getBlockDefaults(blockName);
		if (defaults == nullptr) return false;
		blocks.push_back(new Block(&world, x, y, defaults));
		return true;
	}

	bool setSetting(const std::string& setting, float x, float y, float z=-1) {
		// may need to change if more settings are added
		if (setting == "gravity") {
			gravity.Set(x, y);
			return true;
		}
		if (setting == "slingshot") {
			slingshot.setPos(x, y);
			return true;
		}
		if (x >= y || y >= z || z < 0 || z == FLT_MIN) return false;
		if (setting == "scorelimits") {
			scoreLimits = { x, y, z };
		}
		return false;
	}

	void addGround() {
		for (float x=-100; x<100; x+=5.075) {
			blocks.push_back(new Block(&world, x, -0.55f/2, &ObjectDefs::fixedRectL));
		}
	}

	char asciitolower(char in) {
		if (in <= 'Z' && in >= 'A')
			return in - ('Z' - 'z');
		return in;
	}

	void toLower(std::string& string) {
		for (size_t i=0; i<string.size(); i++) {
			string[i] = asciitolower(string[i]);
		}
	}

	float readFloat(std::stringstream& line) {
		float val;
		// better way to do this?
		std::string parameter;
		getline(line, parameter, ',');
		std::stringstream ss(parameter);

		if (!(ss >> val)) { return FLT_MIN; }

		return val;
	}

	b2Vec2 gravity;
	b2World world;

	float frameRate;
	float timeStep;
	bool isActive = false;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	std::queue<std::string> unusedBirds;
	std::array<float, 3> scoreLimits;
	float score = 0;

	std::vector<Bird*>birds;
	std::vector<Pig*>pigs;
	std::vector<Block*> blocks;
	Slingshot slingshot;
	ObjectCollisions collisionHandler;
};

#endif // LEVEL_HPP
