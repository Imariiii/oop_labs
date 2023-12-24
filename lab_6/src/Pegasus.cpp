#include "Pegasus.h"
#include "Dragon.h"
#include "WanderingKnight.h"

Pegasus::Pegasus(int x, int y) : NPC(PegasusType, x, y) {}
Pegasus::Pegasus(std::istream &is) : NPC(PegasusType, is) {}

void Pegasus::print()
{
    std::cout << *this;
}

void Pegasus::save(std::ostream &os)
{
    os << PegasusType << std::endl;
    NPC::save(os);
}

bool Pegasus::accept(const std::shared_ptr<NPC> attacker) {
    std::shared_ptr<Visitor> attacker_visitor = VisitorFactory::CreateVisitor(attacker->get_type());
    std::shared_ptr<Pegasus> defender = std::dynamic_pointer_cast<Pegasus>(std::const_pointer_cast<NPC>(shared_from_this()));
    bool result = attacker_visitor->visit(defender);
    attacker->fight_notify(defender, result);
    return result;
}


std::ostream &operator<<(std::ostream &os, Pegasus &knight)
{
    os << "Pegasus: " << *static_cast<NPC *>(&knight) << std::endl;
    return os;
}