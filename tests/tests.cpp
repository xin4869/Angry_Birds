/**
 * @file tests.cpp
 * @brief Using tests: 
 * @brief 1. Build project
 * @brief 2. Run 'ctest' in /build
 * @brief Alternatively use the 'Testing' tab in VS Code
 */


#ifndef UNIT_TESTS
#define UNIT_TESTS

#include <iostream>
#include <gtest/gtest.h>
#include <box2d/box2d.h>
#include "../src/objects/block.hpp"
#include "../src/objects/object_defs.hpp"
#include "../src/objects/special_birds.hpp"
#include "../src/level.hpp"


TEST(BlocksTests, Create) {
	b2World world(b2Vec2(0, -10));
	Block block(&world, 0, 0, &ObjectDefs::iceRect);
	EXPECT_NE(block.getScore(), 0);
	EXPECT_NE(block.getBody(), nullptr);
	EXPECT_NE(block.getHP(), 0);
}

TEST(BlockTests, TakeDamage) {
	b2World world(b2Vec2(0, -10));
	Block block(&world, 0, 0, &ObjectDefs::iceRect);
	block.TakeDamage(10);
	EXPECT_NE(block.getHP(), block.getMaxHP());
}

TEST(BlockTests, Destroy) {
	b2World world(b2Vec2(0, -10));
	Block block(&world, 0, 0, &ObjectDefs::iceRect);
	block.Destroy(1.0f);
	ASSERT_NE(Object::destroyList.size(), 0);
}

TEST(BirdTests, Create) {
	b2World world(b2Vec2(0, -10));
	NormalBird bird(&world, 0, 0);
	EXPECT_EQ(bird.getScore(), 0);
	EXPECT_NE(bird.getBody(), nullptr);
	EXPECT_NE(bird.getHP(), 0);
}

TEST(BirdTests, Attack) {
	b2World world(b2Vec2(0, -10));
	NormalBird bird(&world, 0, 0);
	bird.Attack();
	EXPECT_EQ(bird.getCanAttack(), false);
}

TEST(LevelTests, Load) {
	Level level("../assets/levels/level1.lvl");
	EXPECT_EQ(level.getActive(), true);
	EXPECT_EQ(level.getBirds().size(), 1);
	EXPECT_NE(level.getBlocks().size(), 0);
	EXPECT_NE(level.getPigs().size(), 0);
	EXPECT_EQ(level.getScore(), 0);
	EXPECT_EQ(level.getStars(), 0);
	EXPECT_EQ(level.getUnusedBirds().size(), 0);
}

#endif
