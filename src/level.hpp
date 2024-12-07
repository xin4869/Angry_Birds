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
	Level() :frameRate(60.0f), timeStep(1.0f / 60.0f), gravity(0, -10), world(gravity) {
		world.SetContactListener(&collisionHandler);
	}
	~Level() { clearLevel(); }

	void loadLevel(const std::string path) {
		clearLevel();
		gravity.Set(0, -10);
		slingshot.setPos(0, 2);
		scoreLimits = { 1000, 2000, 3000 };
		setScore(0);
		
		std::ifstream file(path);

		if(!file.is_open()) {
			std::cerr << "Failed to open level file." << std::endl;
			return;
		}

		parseLevelFile(file);
		initializeFirstBird();
		addGround();
		isActive = true;
	}

	void loadLevel(int level) {
		loadLevel(getFilePath(level));
	}

	void update(float deltaTime) {
		if (!isActive) return;
		accumulator += deltaTime;

		while (accumulator >= timeStep) {
			world.Step(timeStep, velocityIterations, positionIterations);
			addScore(collisionHandler.transferScore());

			for (auto i = Object::destroyList.begin(); i != Object::destroyList.end(); i++) {
				i->first -= timeStep;
				if (i->first <= 0) {
					findErase(i->second);
					delete i->second;
					i = Object::destroyList.erase(i);
					i--;
				}
				if (i->second != nullptr) i->second->getBody()->SetEnabled(false);
			}

			accumulator -= timeStep;
		}
	}

	bool isWin() { return pigs.empty(); }
	bool isLost() { return unusedBirds.empty() && birds.empty(); }

	int getStars() {
		for (size_t stars=0; stars<scoreLimits.size(); stars++) {
			if (score < scoreLimits[stars]) return stars;
		}
		return scoreLimits.size();
	}

	bool isMouseOnBird(const b2Vec2& worldPos) const {
		return currentBird && currentBird->contains(worldPos);
	}

	bool startDragging(const b2Vec2& worldPos) {
		if  (isDragging || !currentBird) return false;

		if (isMouseOnBird(worldPos)) {
			isDragging = true;
			return true;
		}
		return false;
	}

	void updateDragging(const b2Vec2& worldPos) {
		if (isDragging && currentBird) {
			slingshot.drag(currentBird, worldPos.x, worldPos.y);
		}
	}

	void endDragging() {
		if (isDragging && currentBird) {
			b2Vec2 birdPos = currentBird->getBody()->GetPosition();
			slingshot.release(currentBird, birdPos.x, birdPos.y);

			currentBird->getBody()->SetAwake(true);
			currentBird->getBody()->SetEnabled(true);

			isDragging = false;
		}
	}

	b2World& getWorld() { return world; }
	Slingshot& getSlingshot() { return slingshot; }
	void setActive(bool active) { isActive = active; }
	bool getActive() { return isActive; }
	float getScore() { return score; }
	void setScore(float value) { score = value; }
	void addScore(float add) { score += add; }
	const std::vector<Bird*>& getBirds() { return birds; }
	const std::vector<Block*>& getBlocks() { return blocks; }
	const std::vector<Pig*>& getPigs() { return pigs; }
	const std::queue<std::string>& getUnusedBirds() { return unusedBirds; }

protected:
	/**
	 * @brief Finds object in birds, blocks or pigs and deletes it from the list.
	 * @param toDelete remove this from the lists
	 */
	void findErase(Object* toDelete) {
		for (auto i=birds.begin(); i!=birds.end(); i++) {
			if (*i == toDelete) {
				birds.erase(i);
				return;
			}
		}
		for (auto i=pigs.begin(); i!=pigs.end(); i++) {
			if (*i == toDelete) {
				pigs.erase(i);
				return;
			}
		}
		for (auto i=blocks.begin(); i!=blocks.end(); i++) {
			if (*i == toDelete) {
				blocks.erase(i);
				return;
			}
		}
	}

	void clearLevel() {
		Object::destroyList.clear();

		for (auto i: birds) { delete i; }
		birds.clear();

		for (auto i: pigs) { delete i; }
		pigs.clear();

		for (auto i: blocks) { delete i; }
		blocks.clear();

		for (auto i=world.GetBodyList(); i!=nullptr; i=world.GetBodyList()) {
			world.DestroyBody(i);
		}
		setScore(0);
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
		// line is in lowercase!
		std::string parameter;
		getline(lineStream, parameter, ',');
		if (addBird(parameter)) return;

		float x = readFloat(lineStream);
		float y = readFloat(lineStream);
		float z = readFloat(lineStream);
		
		if (x == FLT_MIN || y == FLT_MIN) return;

		if (setSetting(parameter, x, y, z)) return;
		if (addPig(parameter, x, y, z)) return;
		addBlock(parameter, x, y, z);
	}
	
	static Bird* createBird(b2World* world, float x, float y, const std::string& birdType) {
        if (birdType == "normalbird") {
            return new NormalBird(world, x, y);
        } else if (birdType == "speedbird") {
            return new SpeedBird(world, x, y);
        } else if (birdType == "explodebird") {
            return new ExplodeBird(world, x, y);
        } else {
            return nullptr;
        }
    }

	void initializeFirstBird() {
		if (!currentBird && !unusedBirds.empty()) {
			std::string birdType = unusedBirds.front();
			unusedBirds.pop();

			if (birdType == "normalbird") {
				currentBird = new NormalBird(&world, slingshot.getPos().x, slingshot.getPos().y + 2.0f);
			} else if (birdType == "speedbird") {
				currentBird = new SpeedBird(&world, slingshot.getPos().x, slingshot.getPos().y + 2.0f);
			} else if (birdType == "explodebird") {
				currentBird = new ExplodeBird(&world, slingshot.getPos().x, slingshot.getPos().y + 2.0f);
			} else {
				currentBird = nullptr;
			}

			if (currentBird) {
				birds.push_back(currentBird);
			}
		}
	}

	bool addBird(const std::string& className) {
		if (ObjectDefs::getBirdDefaults(className) == nullptr) return false;
		unusedBirds.push(className);
		return true;
	}

	bool addPig(const std::string& pigName, float x, float y, float rotation) {
		ObjectDefs::ObjectDefaults* defaults = ObjectDefs::getPigDefaults(pigName);
		if (defaults == nullptr) return false;
		float rot = rotation == FLT_MIN ? 0 : rotation;
		pigs.push_back(new Pig(&world, x, y, defaults, rot));
		return true;
	}

	bool addBlock(const std::string& blockName, float x, float y, float rotation) {
		ObjectDefs::ObjectDefaults* defaults = ObjectDefs::getBlockDefaults(blockName);
		if (defaults == nullptr) return false;
		blocks.push_back(new Block(&world, x, y, defaults, rotation));
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
		for (float x=-100; x<100; x+=5.075f) {
			blocks.push_back(new Block(&world, x, -0.55f/2.0f, &ObjectDefs::fixedRectL));
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

	/**
	 * @brief Reads a float from the stream, including a ',', the delimiter
	 * @param line the stream
	 * @return the read float, or FLT_MIN if unsuccesful
	 */
	float readFloat(std::stringstream& line) {
		float val;
		// better way to do this?
		std::string parameter;
		getline(line, parameter, ',');
		std::stringstream ss(parameter);

		if (!(ss >> val)) { return FLT_MIN; }

		return val;
	}


	Bird* currentBird = nullptr;
	bool isDragging = false;

	float accumulator = 0;
	float frameRate;
	float timeStep;
	bool isActive = false;

	b2Vec2 gravity;
	b2World world; 

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
