#pragma once
#include "npc.h"

struct Knight : public NPC {
    Knight(int x, int y);
    Knight(std::istream& is);

    void print() override;

    bool is_knight() const override;

    bool accept(const std::shared_ptr<NPC>& attacker) override;


    bool fight(std::shared_ptr<Druid> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Knight> other) override;

    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Knight& knight);
};
