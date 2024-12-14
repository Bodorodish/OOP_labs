#include "../include/druid.h"
#include "../include/knight.h"
#include "../include/elf.h"

Druid::Druid(int x, int y) : NPC(DruidType, x, y) {}

Druid::Druid(std::istream& is) : NPC(DruidType, is) {}

void Druid::print() {
    std::cout << *this;
}

bool Druid::is_druid() const {
    return true;
}

bool Druid::fight(std::shared_ptr<Druid> other) {
    fight_notify(other, true); // Друид убивает другого друида
    return true;
}

bool Druid::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return false;
}

bool Druid::fight(std::shared_ptr<Knight> other) {
    fight_notify(other, false);
    return false;
}

void Druid::save(std::ostream& os) {
    os << DruidType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Druid& druid) {
    os << "druid: " << *static_cast<NPC*>(&druid) << std::endl;
    return os;
}

bool Druid::accept(const std::shared_ptr<NPC>& attacker){
    if (attacker->is_knight()) {
        return false;
    } else if (attacker->is_druid()) {
        return true;
    } else if (attacker->is_elf()) {
        return false;
    }
    return false;
}