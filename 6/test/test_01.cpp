#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/knight.h"
#include "../include/druid.h"
#include "../include/elf.h"
#include <memory>

TEST(FightTest, KnightKillsElfElfKillsKnight) {
    auto knight = std::make_shared<Knight>(0, 0);
    auto elf = std::make_shared<Elf>(1, 1);

    EXPECT_TRUE(knight->accept(elf));
    EXPECT_TRUE(elf->accept(knight));
}

TEST(FightTest, ElfKillsDruid) {
    auto elf = std::make_shared<Elf>(0, 0);
    auto druid = std::make_shared<Druid>(1, 1);

    EXPECT_TRUE(elf->accept(druid));
    EXPECT_FALSE(druid->accept(elf));
}

TEST(FightTest, DruidKillsDruid) {
    auto druid1 = std::make_shared<Druid>(0, 0);
    auto druid2 = std::make_shared<Druid>(1, 1);

    EXPECT_TRUE(druid1->accept(druid2));
    EXPECT_TRUE(druid2->accept(druid1));
}

TEST(FightTest, SameTypeFightDraw) {
    auto knight1 = std::make_shared<Knight>(0, 0);
    auto knight2 = std::make_shared<Knight>(1, 1);

    EXPECT_FALSE(knight1->accept(knight2));
    EXPECT_FALSE(knight2->accept(knight1));

    auto elf1 = std::make_shared<Elf>(0, 0);
    auto elf2 = std::make_shared<Elf>(1, 1);

    EXPECT_FALSE(elf1->accept(elf2));
    EXPECT_FALSE(elf2->accept(elf1));

    auto druid1 = std::make_shared<Druid>(0, 0);
    auto druid2 = std::make_shared<Druid>(1, 1);

    EXPECT_TRUE(druid1->accept(druid2));
    EXPECT_TRUE(druid2->accept(druid1));
}

TEST(FightTest, DistanceTest) {
    auto knight = std::make_shared<Knight>(0, 0);
    auto elf = std::make_shared<Elf>(5, 5);

    EXPECT_FALSE(knight->is_close(elf, 4));
    EXPECT_TRUE(knight->is_close(elf, 10));
}
