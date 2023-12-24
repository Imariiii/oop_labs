#pragma once
#include "NPC.h"

struct Pegasus final: public NPC
{
    Pegasus(int x, int y);
    Pegasus(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> attacker) override;
    friend std::ostream &operator<<(std::ostream &os, Pegasus &knight);
};