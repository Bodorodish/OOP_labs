#include "npc.h"

// Конструктор с координатами
NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}

// Конструктор из потока ввода
NPC::NPC(NpcType t, std::istream& is) : type(t) {
    is >> x >> y;
}

// Подписка наблюдателя
void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

// Уведомление наблюдателей о результате боя
void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto& observer : observers) {
        observer->on_fight(shared_from_this(), defender, win);
    }
}

// Проверка расстояния между NPC
bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) const {
    return std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2);
}

// Методы для проверки типа (по умолчанию возвращают false)
bool NPC::is_knight() const { return false; }
bool NPC::is_druid() const { return false; }
bool NPC::is_elf() const { return false; }

// Сохранение базовых данных объекта в поток
void NPC::save(std::ostream& os) {
    os << x << " " << y << std::endl;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, NPC& npc) {
    os << "{ type: " << npc.type 
       << ", x: " << npc.x 
       << ", y: " << npc.y 
       << " }";
    return os;
}