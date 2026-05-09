
#include "Type.h"

// Funkcja zwracająca Char z enuma
char GetType(Type type) {
    switch (type) {
    case Type::O:
        return 'O';
    case Type::X:
        return 'X';
    default:
        return 'O';
    }
}