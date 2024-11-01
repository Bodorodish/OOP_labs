#include <iostream>
#include <memory>
#include <vector>
#include "include/array.h"
#include "include/rectangle.h"
#include "include/trapezoid.h"
#include "include/rhombus.h"

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;

    while (true) {
        std::cout << "Выберите фигуру (1 - Прямоугольник, 2 - Трапеция, 3 - Ромб): ";
        int choice;
        std::cin >> choice;

        std::shared_ptr<Figure<double>> figure;

        try {
            if (choice == 1) {
                figure = std::make_shared<Rectangle<double>>();
                std::cout << "Введите координаты точек (x1 y1 x2 y2): ";
                std::cin >> dynamic_cast<Rectangle<double>*>(figure.get());
            } else if (choice == 2) {
                figure = std::make_shared<Trapezoid<double>>();
                std::cout << "Введите координаты точек (x1 y1 x2 y2 x3 y3 x4 y4): ";
                std::cin >> dynamic_cast<Trapezoid<double>*>(figure.get());
            } else if (choice == 3) {
                figure = std::make_shared<Rhombus<double>>();
                std::cout << "Введите координаты точек (x1 y1 x2 y2 x3 y3 x4 y4): ";
                std::cin >> dynamic_cast<Rhombus<double>*>(figure.get());
            } else if (choice == -1){
                std::cout << "Выходим......" << std::endl;
                break;
            } else {
                std::cout << "Неверный выбор! Пожалуйста, попробуйте снова." << std::endl;
                continue;
            }

            figures.add(figure);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка ввода: " << e.what() << std::endl;
            continue;
        }
    }

    double totalArea = 0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << figures[i].get() << std::endl;
        totalArea += figures[i]->area();
    }

    std::cout << "Общая площадь фигур: " << totalArea << std::endl;

    return 0;
}
