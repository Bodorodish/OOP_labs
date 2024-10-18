#include "../include/converter.h"
#include <string>

std::string FromIntToString(int num){
    const std::string UNITS[10] = {"sıfır", "bir", "iki", "üç", "dört", "beş", "altı", "yedi", "sekiz", "dokuz"};
    const std::string TENS[10] = {"on", "yirmi", "otuz", "kırk", "elli", "altmış", "yetmiş", "seksen", "doksan"};
    if (num < 10){
        return UNITS[num];
    }
    return TENS[num / 10 - 1] + " " + UNITS[num % 10];
}
