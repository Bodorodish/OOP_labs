#include "../include/knight.h"
#include "../include/druid.h"
#include "../include/elf.h"

Knight::Knight(int x, int y) : NPC(KnightType, x, y) {}

Knight::Knight(std::istream& is) : NPC(KnightType, is) {}

void Knight::print() {
    std::cout << *this;
}

bool Knight::is_knight() const {
    return true;
}

bool Knight::fight(std::shared_ptr<Druid> other) {
    fight_notify(other, false);
    return false;
}

bool Knight::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, true); // Knight побеждает эльфа
    return true;
}

bool Knight::fight(std::shared_ptr<Knight> other) {
    fight_notify(other, false);
    return false;
}

void Knight::save(std::ostream& os) {
    os << KnightType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Knight& knight) {
    os << "knight: " << *static_cast<NPC*>(&knight) << std::endl;
    return os;
}

bool Knight::accept(const std::shared_ptr<NPC>& attacker) {
    if (attacker->is_knight()) {
        return false;
    } else if (attacker->is_druid()) {
        return false;
    } else if (attacker->is_elf()) {
        return true;
    }
    return false;
}