#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cmath>

// Тип NPC
enum NpcType {
    Unknown = 0,
    KnightType = 1,
    DruidType = 2,
    ElfType = 3
};

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<class NPC> attacker, 
                          const std::shared_ptr<class NPC> defender, 
                          bool win) = 0;
    virtual ~IFightObserver() = default;
};

struct NPC : public std::enable_shared_from_this<NPC> {
    NpcType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<IFightObserver>> observers;


    bool is_alive{true};


    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream& is);

    virtual ~NPC() = default;

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);

    virtual bool is_close(const std::shared_ptr<NPC>& other, size_t distance) const;

    virtual bool accept(const std::shared_ptr<NPC>& attacker) = 0;

    virtual bool is_knight() const;
    virtual bool is_druid() const;
    virtual bool is_elf() const;

    virtual bool fight(std::shared_ptr<class Knight> other) = 0;
    virtual bool fight(std::shared_ptr<class Druid> other) = 0;
    virtual bool fight(std::shared_ptr<class Elf> other) = 0;

    virtual void print() = 0;

    virtual void save(std::ostream& os);

    friend std::ostream& operator<<(std::ostream& os, NPC& npc);


    bool alive() const { return is_alive; }
    void kill() { is_alive = false; }
    virtual size_t kill_distance() const = 0;
};
