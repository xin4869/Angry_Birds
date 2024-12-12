#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <fstream>
#include <queue>
#include "objects/get_object_defaults.hpp"
#include "slingshot.hpp"
#include "objects/object.hpp"
#include "objects/ground.hpp"

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

	/**
	 * @brief Load a level from a level file
	 * @param path path to level file
	 */
	void loadLevel(const std::string path) {
		clearLevel();
		gravity.Set(0, -10);
		slingshot.setPos(-15, 3);
		scoreLimits = { 1000, 2000, 3000 };
		setScore(0);
		
		std::ifstream file(path);

		if(!file.is_open()) {
			std::cerr << "Failed to open level file." << std::endl;
			return;
		}

		parseLevelFile(file);
		setNextBird();
		addGroundBlocks();
		isActive = true;
	}

	void loadLevel(int level) {
		loadLevel(getFilePath(level));
	}

	/**
	 * @brief Updates the game
	 * @param deltaTime update by this time
	 */
	void update(float deltaTime) {
		if (!isActive) return;
		accumulator += deltaTime;

		while (accumulator >= timeStep) {
			world.Step(timeStep, velocityIterations, positionIterations);
			
			addScore(collisionHandler.transferScore());

			updateAllTexture();
			addToDestroyList();
			cleanDestroyList();

			accumulator -= timeStep;
		}
	}

	void addToDestroyList() {
		for (auto& bird: birds) {
			if (bird->getHP() == 0) {bird->Destroy(3.f);} 
			else if (bird->isUsed() && !bird->isMoving()) {bird->Destroy(3.f);} 
			else if (bird->isOut()) {bird->Destroy();}
		}

		for (auto& pig: pigs) {
			if (pig->getHP() == 0) {pig->Destroy(3.f);} 
			else if (pig->isOut()) {pig->Destroy();}
		}

		for (auto& block: blocks) {
			if (block->getBody()->GetType() == b2_staticBody) {return;}
			else {
				if (block->getHP() == 0) {block->Destroy(2.f);}
				else if (block->isOut()) {block->Destroy();}
			}			
		}
	}

	void disableAllDestroyed() {	
		for (auto i = Object::destroyList.begin(); i != Object::destroyList.end();) {
			i->first -= timeStep;
			// for implicitly detecting birds (score == 0)
			if ( i->second != nullptr && (i->second->getDisableOnDestroy() || i-> first <= 0) ) {
				i->second->getBody()->SetEnabled(false);
				i->second->playSound("bird destroyed");
				
			}
			
			if (i->first <= -3.f) {
				if (i->second != nullptr) {
					if (i->second == currentBird) currentBird = nullptr;
					findErase(i->second);
					delete i->second;
				}
				i = Object::destroyList.erase(i);
			} else {i++;}
		}		
	}

	void finalDestroy() {	
		for (auto i = Object::destroyList.begin(); i != Object::destroyList.end();) {
			i->first -= timeStep;
			// for implicitly detecting birds (score == 0)
			if (i->second != nullptr && i->second->getDisableOnDestroy()) {
				i->second->getBody()->SetEnabled(false);
			}
			if (i->first <= 0) {
				if (i->second != nullptr) {
					if (i->second == currentBird) currentBird = nullptr;
					findErase(i->second);
					delete i->second;
				}
				i = Object::destroyList.erase(i);
			} else {i++;}
		}		
	}

	void updateAllTexture() {
		for (auto& bird : birds) {
			bird->updateTexture(timeStep);
		}

		for (auto& pig : pigs) {
			pig->updateTexture(timeStep);
		}

		for (auto& block : blocks) {
			if (block->getBody()->GetType() != b2_staticBody) {
				block->updateTexture(timeStep);
			}		
		}

	}

	/**
	 * @brief Tells if game is won
	 * @return true if won
	 */
	bool isWin() { return pigs.empty(); }
	/**
	 * @brief Tells if game is lost
	 * @return true if lost
	 */
	bool isLost() {
		bool lost = unusedBirds.empty() && birds.empty();
		if (!lost) return false;
		if (Object::destroyList.size() > 0) return false;
		return lost;
	}

	/**
	 * @brief Get number of stars based on score and score limits
	 * @return int stars
	 */
	int getStars() {
		for (size_t stars=0; stars<scoreLimits.size(); stars++) {
			if (score < scoreLimits[stars]) return stars;
		}
		return scoreLimits.size();
	}

	std::unique_ptr<Ground>& getGround() { return ground; }

	// std::vector<b2Vec2>& getGroundPoints() { return groundPoints; }

	/**
	 * @brief Is position on current active bird?
	 * @param worldPos position in world coordinates
	 * @return true if position on bird
	 */
	bool isMouseOnBird(const b2Vec2& worldPos) const {
		return currentBird && currentBird->contains(worldPos);
	}

	/**
	 * @brief Try to start dragging bird in slingshot
	 * @param worldPos Drag from here
	 * @return true if succesful
	 */
	bool startDragging(const b2Vec2& worldPos) {
		if  (isDragging) return false;

		if (isMouseOnBird(worldPos)) {
			isDragging = true;
			return true;
		}
		return false;
	}

	/**
	 * @brief Updates bird dragging
	 * @param worldPos Drag here
	 */
	void updateDragging(const b2Vec2& worldPos) {
		if (isDragging && currentBird) {
			slingshot.drag(currentBird, worldPos.x, worldPos.y);
		}
	}

	/**
	 * @brief Ends bird dragging, launches bird
	 */
	void endDragging() {
		if (isDragging && currentBird) {
			b2Vec2 birdPos = currentBird->getBody()->GetPosition();
			slingshot.release(currentBird, birdPos.x, birdPos.y);

			currentBird->getBody()->SetAwake(true);
			currentBird->getBody()->SetEnabled(true);
			currentBird->useBird();

			isDragging = false;
		}
	}

	/**
	 * @brief Set the next bird into the slingshot if available
	 */
	void setNextBird() {
		if (unusedBirds.empty()) return;
		if (currentBird && currentBird->getCanAttack()) return;

		std::string birdType = unusedBirds.front();
		unusedBirds.pop();

		if (birdType == "normalbird") {
			currentBird = new NormalBird(&world, slingshot.getPos().x + 0.5f, slingshot.getPos().y + 2.f);
		} else if (birdType == "speedbird") {
			currentBird = new SpeedBird(&world, slingshot.getPos().x + 0.5f, slingshot.getPos().y + 2.f);
		} else if (birdType == "explodebird") {
			currentBird = new ExplodeBird(&world, slingshot.getPos().x + 0.5f, slingshot.getPos().y + 2.f);
		} else {
			currentBird = nullptr;
		}

		if (currentBird) {
			currentBird->getBody()->SetAwake(false);
			birds.push_back(currentBird);
		}
	}

	b2World& getWorld() { return world; }
	Slingshot& getSlingshot() { return slingshot; }
	Bird* getCurrentBird() { return currentBird; }
	void setActive(bool active) { isActive = active; }
	bool getActive() { return isActive; }
	bool getDragging() { return isDragging; }
	b2Vec2 getGravity() { return gravity; }
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
		for (auto i=birds.begin(); i!=birds.end();) {
			if (*i == toDelete) {
				birds.erase(i);
				return;
			}			
			++i;
		}

		for (auto i=pigs.begin(); i!=pigs.end();) {
			if (*i == toDelete) {
				pigs.erase(i);
				return;
			}
			++i;
		}

		for (auto i=blocks.begin(); i!=blocks.end(); i++) {
			if (*i == toDelete) {
				blocks.erase(i);
				return;
			}
			++i;
		}
	}

	/**
	 * @brief Clears and deletes level objects
	 */
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

	/**
	 * @brief Level number to default file path
	 * @param level level number
	 * @return const std::string level file path
	 */
	const std::string getFilePath(int level) {
		return "assets/levels/level" + std::to_string(level) + ".lvl";
	}

	/**
	 * @brief Parses and loads level file
	 * @param file file object
	 */
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

	/**
	 * @brief Parses a line from file, performs action if valid line
	 * @param lineStream line to parse
	 */
	void parseLine(std::stringstream& lineStream) {
		// line is in lowercase!
		std::string parameter;
		getline(lineStream, parameter, ',');
		if (addGround(parameter, lineStream)) return;
		if (addBird(parameter)) return;

		float x = readFloat(lineStream);
		float y = readFloat(lineStream);
		float z = readFloat(lineStream);
		
		if (x == FLT_MIN || y == FLT_MIN) return;

		if (setSetting(parameter, x, y, z)) return;
		if (addPig(parameter, x, y, z)) return;
		if (addBlock(parameter, x, y, z)) return;
	}


	// static Bird* createBird(b2World* world, float x, float y, const std::string& birdType) {
    //     if (birdType == "normalbird") {
    //         return new NormalBird(world, x, y);
    //     } else if (birdType == "speedbird") {
    //         return new SpeedBird(world, x, y);
    //     } else if (birdType == "explodebird") {
    //         return new ExplodeBird(world, x, y);
    //     } else {
    //         return nullptr;
    //     }
    // }

	/**
	 * @brief Adds unused bird based on name
	 * @param className name of bird class
	 * @return true if succesful
	 */
	bool addBird(const std::string& className) {
		if (ObjectDefs::getBirdDefaults(className) == nullptr) return false;
		unusedBirds.push(className);
		return true;
	}

	/**
	 * @brief Adds a pig to world
	 * @param pigName pig defaults name (see pig)
	 * @param x world x pos
	 * @param y world y pos
	 * @param rotation in degrees
	 * @return true if succesful
	 */
	bool addPig(const std::string& pigName, float x, float y, float rotation) {
		ObjectDefs::ObjectDefaults* defaults = ObjectDefs::getPigDefaults(pigName);
		if (defaults == nullptr) return false;
		float rot = rotation == FLT_MIN ? 0 : rotation;
		pigs.push_back(new Pig(&world, x, y, defaults, rot));
		return true;
	}

	/**
	 * @brief Adds a block to world
	 * @param blockName block defaults name (see block)
	 * @param x world x pos
	 * @param y world y pos
	 * @param rotation in degrees
	 * @return true if succesful
	 */
	bool addBlock(const std::string& blockName, float x, float y, float rotation) {
		ObjectDefs::ObjectDefaults* defaults = ObjectDefs::getBlockDefaults(blockName);
		if (defaults == nullptr) return false;
		blocks.push_back(new Block(&world, x, y, defaults, rotation));
		return true;
	}

	/**
	 * @brief Sets a setting value
	 * @param setting Setting name
	 * @param x parameter 1
	 * @param y parameter 2
	 * @param z parameter 3
	 * @return true if succesful
	 */
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

	bool addGround(const std::string& parameter, std::stringstream& lineStream) {
		if (parameter != "ground") return false;
		float x, y;
		while (true) {
			x = readFloat(lineStream);
			y = readFloat(lineStream);
			if (x == FLT_MIN || y == FLT_MIN) break;
			groundPoints.push_back(b2Vec2(x, y));
		}
		if (!groundPoints.empty()) {
			ground = std::make_unique<Ground>(&world, groundPoints);
		}
		return true;
	}

	/**
	 * @brief Adds an invisible fixed ground to world
	 */
	void addGroundBlocks() {
		for (float x=-100; x<100; x+=5.075f) {
			blocks.push_back(new Block(&world, x, -0.55f/2.0f, &ObjectDefs::fixedRectL));
		}
	}

	/**
	 * @brief Character to lowercase
	 * @param in char
	 * @return char lowercase'd
	 */
	char asciitolower(char in) {
		if (in <= 'Z' && in >= 'A')
			return in - ('Z' - 'z');
		return in;
	}

	/**
	 * @brief Transforms string to lowercase, in place
	 * @param string to transform
	 */
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
	std::vector<b2Vec2> groundPoints;

	std::vector<Bird*>birds;
	std::vector<Pig*>pigs;
	std::vector<Block*> blocks;
	std::unique_ptr<Ground> ground;
	Slingshot slingshot;
	ObjectCollisions collisionHandler;
};

#endif // LEVEL_HPP
