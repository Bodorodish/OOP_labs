#include "include/npc.h"
#include "include/knight.h"
#include "include/druid.h"
#include "include/elf.h"

#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <random>
#include <chrono>


constexpr int MAP_WIDTH = 100;
constexpr int MAP_HEIGHT = 100;
constexpr int GAME_DURATION = 30; // seconds
constexpr size_t NUM_NPCS = 50;

std::mutex npc_mutex;
std::mutex cout_mutex;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(0, MAP_WIDTH - 1);

void print_map(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Карта NPC:" << std::endl;
    for (const auto& npc : npcs) {
        if (npc->alive()) {
            std::cout << "NPC: ";
            npc->print();
            std::cout << std::endl;
        }
    }
}

void move_npcs(std::vector<std::shared_ptr<NPC>>& npcs) {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(npc_mutex);
            for (auto& npc : npcs) {
                if (!npc->alive()) continue;

                int dx = dist(gen) % 2 == 0 ? 1 : -1;
                int dy = dist(gen) % 2 == 0 ? 1 : -1;
                npc->x = std::clamp(npc->x + dx, 0, MAP_WIDTH - 1);
                npc->y = std::clamp(npc->y + dy, 0, MAP_HEIGHT - 1);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void fight_npcs(std::vector<std::shared_ptr<NPC>>& npcs) {
    std::uniform_int_distribution<> dice_roll(1, 6);
    while (true) {
        {
            std::lock_guard<std::mutex> lock(npc_mutex);
            for (size_t i = 0; i < npcs.size(); ++i) {
                if (!npcs[i]->alive()) continue;
                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    if (!npcs[j]->alive() || !npcs[i]->is_close(npcs[j], npcs[i]->kill_distance())) continue;

                    int attack = dice_roll(gen);
                    int defense = dice_roll(gen);
                    if (attack > defense && npcs[j]->accept(npcs[i])) {
                        npcs[j]->kill();
                    } else {
                        npcs[i]->kill();
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::vector<std::shared_ptr<NPC>> npcs;
    for (size_t i = 0; i < NUM_NPCS; ++i) {
        int x = dist(gen);
        int y = dist(gen);
        switch (i % 3) {
            case 2:
                npcs.push_back(std::make_shared<Elf>(x, y));
                break;
            case 1:
                npcs.push_back(std::make_shared<Knight>(x, y));
                break;
            case 0:
                npcs.push_back(std::make_shared<Druid>(x, y));
                break;
        }
    }

    std::thread movement_thread(move_npcs, std::ref(npcs));
    std::thread combat_thread(fight_npcs, std::ref(npcs));

    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(GAME_DURATION)) {
        {
            std::lock_guard<std::mutex> lock(npc_mutex);
            print_map(npcs);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    movement_thread.detach();
    combat_thread.detach();

    std::cout << "\nИгра завершена. Выжившие NPC:" << std::endl;
    {
        std::lock_guard<std::mutex> lock(npc_mutex);
        for (const auto& npc : npcs) {
            if (npc->alive()) {
                npc->print();
                std::cout << std::endl;
            }
        }
    }

    return 0;
}
