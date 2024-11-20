/**
 * @file tests.cpp
 * @brief Using tests: 
 * @brief 1. Build project
 * @brief 2. Run 'ctest' in /build
 * @brief Alternatively use the 'Testing' tab in VS Code
 * 
 */


#ifndef _AB_UNIT_TESTS_
#define _AB_UNIT_TESTS_

#include <gtest/gtest.h>
#include <box2d/box2d.h>
#include "../src/objects/block.hpp"
#include "../src/objects/object_defs.hpp"
//#include "../src/visual/texture_manager.hpp"


class BlockTest : public testing::Test
{
protected:
	BlockTest() : world(b2World(b2Vec2(0, -10)))
	{  		
		block = Block(&world, 0, 0, &ObjectDefs::iceRectL);
	}
	
  	b2World world;
	Block block;
};

TEST_F(BlockTest, Creation)
{
	EXPECT_EQ(1, 0);
}

TEST_F(BlockTest, TakeDamage)
{
	// implement
	EXPECT_EQ(1, 0);
}

TEST_F(BlockTest, Destroy)
{
	// implement
	EXPECT_EQ(1, 0);
}

#endif
