#pragma once
#include <cstdarg>

template <typename T>
T max(int count, ...) {
    if (count > 0) {
        va_list candidates;
        va_start(candidates, count);

        T candidate = va_arg(candidates, T);
        for (int i = 1; i < count; i++) {
            T temp = va_arg(candidates, T);
            candidate = (temp > candidate ? temp : candidate);
        }

        va_end(candidates);
        return candidate;
    } else {
        return T();
    }
}

template <typename T>
T min(int count, ...) {
    if (count > 0) {
        va_list candidates;
        va_start(candidates, count);

        T candidate = va_arg(candidates, T);
        for (int i = 1; i < count; i++) {
            T temp = va_arg(candidates, T);
            candidate = (temp < candidate ? temp : candidate);
        }

        va_end(candidates);
        return candidate;
    } else {
        return T();
    }
}