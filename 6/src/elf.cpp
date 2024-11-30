#include "../include/elf.h"
#include "../include/knight.h"
#include "../include/druid.h"

Elf::Elf(int x, int y) : NPC(ElfType, x, y) {}

Elf::Elf(std::istream& is) : NPC(ElfType, is) {}

void Elf::print() {
    std::cout << *this;
}

bool Elf::is_elf() const {
    return true;
}

bool Elf::fight(std::shared_ptr<Druid> other) {
    fight_notify(other, true); // Эльф убивает друида
    return true;
}

bool Elf::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false);
    return false;
}

bool Elf::fight(std::shared_ptr<Knight> other) {
    fight_notify(other, true); // Эльф убивает рыцаря
    return true;
}

void Elf::save(std::ostream& os) {
    os << ElfType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Elf& elf) {
    os << "elf: " << *static_cast<NPC*>(&elf) << std::endl;
    return os;
}

bool Elf::accept(const std::shared_ptr<NPC>& attacker) {
    if (attacker->is_knight()) {
        return true;
    } else if (attacker->is_druid()) {
        return true;
    } else if (attacker->is_elf()) {
        return false;
    }
    return false;
}