#include <gtest/gtest.h>
#include "npc.h"
#include "dragon.h"
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

TEST(MOVE, MoveDragon){
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>(10, 15);
    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE_MOVE_DRAGON{50};
    dragon->move(DISTANCE_MOVE_DRAGON, DISTANCE_MOVE_DRAGON, MAX_X, MAX_Y);
    auto [x, y] = dragon->position();
    ASSERT_EQ(x, 60);

}

TEST(MOVE, MovePegasus){
    std::shared_ptr<NPC> pegasus = std::make_shared<Pegasus>(10, 15);
    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE_MOVE_PEGASUS{1};
    pegasus->move(DISTANCE_MOVE_PEGASUS, DISTANCE_MOVE_PEGASUS, MAX_X, MAX_Y);
    auto [x, y] = pegasus->position();
    ASSERT_EQ(x, 11);
}

TEST(MOVE, MoveKnight){
    std::shared_ptr<NPC> knight = std::make_shared<WanderingKnight>(10, 15);
    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE_MOVE_KNIGHT{30};

    knight->move(DISTANCE_MOVE_KNIGHT, DISTANCE_MOVE_KNIGHT, MAX_X, MAX_Y);
    auto [x, y] = knight->position();
    ASSERT_EQ(x, 40);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
