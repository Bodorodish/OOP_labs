#pragma once
#include "npc.h"

struct Elf : public NPC {
    Elf(int x, int y);
    Elf(std::istream& is);

    void print() override;

    bool is_elf() const override;

    bool accept(const std::shared_ptr<NPC>& attacker) override;

    bool fight(std::shared_ptr<Druid> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Knight> other) override;

    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Elf& elf);
};
