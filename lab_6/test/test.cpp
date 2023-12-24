#include <gtest/gtest.h>
#include "NPC.h"
#include "Dragon.h"
#include "WanderingKnight.h"
#include "Pegasus.h"

TEST(AcceptTest, DragonAttackKnight) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = dragon->accept(knight);
    ASSERT_TRUE(success);
}

TEST(AcceptTest, KnightAttackDragon) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = knight->accept(dragon);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, KnightAttackPegasus) {
    std::shared_ptr<NPC> pegasus = std::make_shared<Pegasus>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = pegasus->accept(knight);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, PegasusAttackKnight) {
    std::shared_ptr<NPC> pegasus = std::make_shared<Pegasus>(10, 15);
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(7, 15);
    bool success = knight->accept(pegasus);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, PegasusAttackDragon) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> pegasus = std::make_shared<Pegasus>(7, 15);
    bool success = dragon->accept(pegasus);
    ASSERT_FALSE(success);
}

TEST(AcceptTest, DragonAttackPegasus) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    std::shared_ptr<NPC> pegasus = std::make_shared<Pegasus>(7, 15);
    bool success = pegasus->accept(dragon);
    ASSERT_TRUE(success);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
