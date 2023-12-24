#pragma once
#include "NPC.h"
#include "Dragon.h"
#include "WanderingKnight.h"
#include "Pegasus.h"
#include "memory"
class Visitor {
public:
    virtual bool visit(const std::shared_ptr<Dragon>&) const = 0;
    virtual bool visit(const std::shared_ptr<WanderingKnight>&) const = 0;
    virtual bool visit(const std::shared_ptr<Pegasus>&) const = 0;
};

class DragonVisitor final: public Visitor {
public:
    virtual bool visit(const std::shared_ptr<Dragon>&) const override { return false; }
    virtual bool visit(const std::shared_ptr<WanderingKnight>&) const override { return false; }
    virtual bool visit(const std::shared_ptr<Pegasus>&) const override { return true; }
};

class WanderingKnightVisitor final: public Visitor {
    public:
        virtual bool visit(const std::shared_ptr<Dragon>&) const override { return true; }
        virtual bool visit(const std::shared_ptr<WanderingKnight>&) const override { return false; }
        virtual bool visit(const std::shared_ptr<Pegasus>&) const override { return false; }
};

class PegasusVisitor final: public Visitor {
    public:
        virtual bool visit(const std::shared_ptr<Dragon>&) const override { return false; }
        virtual bool visit(const std::shared_ptr<WanderingKnight>&) const override { return false; }
        virtual bool visit(const std::shared_ptr<Pegasus>&) const override { return false; }
};

class VisitorFactory {
public:
    static std::shared_ptr<Visitor> CreateVisitor(const NpcType& type) {
        std::shared_ptr<Visitor> result;
        switch (type) {
            case NpcType::DragonType:
                result = std::static_pointer_cast<Visitor>(std::make_shared<DragonVisitor>());
                break;

            case NpcType::WanderingKnightType:
                result = std::static_pointer_cast<Visitor>(std::make_shared<WanderingKnightVisitor>());
                break;

            case NpcType::PegasusType:
                result = std::static_pointer_cast<Visitor>(std::make_shared<PegasusVisitor>());
                break;
            default:
                break;
        }
        return result;
    }
};
