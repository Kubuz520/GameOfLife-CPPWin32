#pragma once

// Enum reprezentujący puste (O) i pełne (X) miejsca na planszy
enum class Type {
    O,
    X
};

// Funkcja zwracająca Char z enuma
char GetType(Type type);