#pragma once
#include "NPC.h"
#include "Visitor.h"

struct WanderingKnight final: public NPC
{
    WanderingKnight(int x, int y);
    WanderingKnight(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC>) override;
    friend std::ostream &operator<<(std::ostream &os, WanderingKnight &knight);
};