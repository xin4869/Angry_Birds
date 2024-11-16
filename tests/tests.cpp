/**
 * @file tests.cpp
 * @brief Using tests: 
 * @brief 1. Build project
 * @brief 2. Run 'ctest' in /build
 * @brief Alternatively use the 'Testing' tab in VS Code
 * 
 */

#include <gtest/gtest.h>
#include "../src/includes.hpp"

#ifndef _AB_UNIT_TESTS_
#define _AB_UNIT_TESTS_

class BlockTest : public testing::Test
{
protected:
	BlockTest() : world(b2World(b2Vec2(0, -10)))
	{  		
		
	}
	
  	b2World world;
	Block block;
};

TEST_F(BlockTest, CreationValues)
{
	b2BodyDef body = ObjectDefs::GetBodyDef(b2BodyType::b2_dynamicBody);
	b2PolygonShape shape = ObjectDefs::GetBoxShape(1, 1);
	block = Block(&world, &body, &shape, 1, 0, 0);
	
	EXPECT_NE(block.hp, 0);
	EXPECT_NE(block.sprite.getTextureRect().height, 0);
	EXPECT_EQ(block.body->GetWorld(), &world);
}

TEST_F(BlockTest, CreationDefaults)
{
	block = Block::GetIceBlock(&world, 0, 0, 1, 1);

	EXPECT_NE(block.hp, 0);
	EXPECT_NE(block.sprite.getTextureRect().height, 0);
	EXPECT_EQ(block.body->GetWorld(), &world);
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
