#include <iostream>
#include "include/rectangle.h"
#include "include/trapezoid.h"
#include "include/rhombus.h"


int main() {
    const int MAX_FIGURES = 100;
    figure* figures[MAX_FIGURES];
    int figure_count = 0;
    int choice;

    while (true) {
        std::cout << "какая фигура? (1 - прямоугольник, 2 - трапеция, 3 - ромб, 0 - выход): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Пожалуйста, введите корректное число.\n";
            continue;
        }

        if (choice == 0 || figure_count >= MAX_FIGURES) break;

        figure* fig = nullptr;
        if (choice == 1) {
            fig = new Rectangle();
        } else if (choice == 2) {
            fig = new Trapezoid();
        } else if (choice == 3) {
            fig = new Rhombus();
        }

        if (fig) {
            std::cout << "4 координаты по порядку (xi, yi): ";
            std::cin >> fig;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очищаем буфер ввода
                std::cout << "ошибка ввода координат" << std::endl;
                delete fig;
                continue;
            }

            figures[figure_count++] = fig;
        }
    }

    std::cout << "\nфигуры в массиве:\n";
    double total_area = 0;
    for (int i = 0; i < figure_count; i++) {
        figure::point center = figures[i]->mass_center();
        std::cout << figures[i] << ", площадь = " << static_cast<double>(*figures[i])
                << ", геометрический центр = (" << center.x << ", " << center.y << ")" << std::endl;
        total_area += static_cast<double>(*figures[i]);
    }

    std::cout << "\nобщая площадь: " << total_area << "\n";

    int index;
    std::cout << "удалить фигуру по индексу (-1 - пропустить): ";
    std::cin >> index;
    if (index >= 0 && index < figure_count) {
        delete figures[index];
        for (int i = index; i < figure_count - 1; i++) {
            figures[i] = figures[i + 1];
        }
        figure_count--;
        std::cout << "фигура под номером  " << index << " удалена\n";
    }

    for (int i = 0; i < figure_count; i++) {
        delete figures[i];
    }

    return 0;
}
