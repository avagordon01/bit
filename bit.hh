#if defined __GNUC__
#include <immintrin.h>
#elif defined _MSC_VER
#include <intrin.h>
#endif
#include <limits>

namespace bit {

namespace {
#if __cplusplus >= 201703L
#define no_discard [[nodiscard]]
#else
#define no_discard
#endif
}

enum class endian {
#if defined __GNUC__
    little = __ORDER_LITTLE_ENDIAN__,
    big    = __ORDER_BIG_ENDIAN__,
    native = __BYTE_ORDER__
#elif defined _WIN32
    little = 0,
    big    = 1,
    native = little
#endif
};

template<class T>
constexpr bool has_single_bit(T x) noexcept {
    return popcount(x) == 1;
}
template<class T>
constexpr T bit_ceil(T x) {
    if (x == ~T{0}) {
        return 0;
    } else if (has_single_bit(x)) {
        return x;
    } else {
        return T{1} << bit_width(x);
    }
}
template<class T>
constexpr T bit_floor(T x) noexcept {
    if (x != 0) {
        return T{1} << (bit_width(x) - 1);
    } else {
        return 0;
    }
}
template<class T>
constexpr T bit_width(T x) noexcept {
    return std::numeric_limits<T>::digits - countl_zero(x);
}
template<class T>
no_discard
constexpr T rotl(T x, int s) noexcept {
    int r = s % std::numeric_limits<T>::digits;
    if (s == 0) {
        return x;
    } else if (s > 0) {
        return (x << r) | (x >> (std::numeric_limits<T>::digits - r));
    } else {
        return (x >> -r) | (x << (std::numeric_limits<T>::digits + r));
    }
}
template<class T>
no_discard
constexpr T rotr(T x, int s) noexcept {
    int r = s % std::numeric_limits<T>::digits;
    if (s == 0) {
        return x;
    } else if (s > 0) {
        return (x >> r) | (x << (std::numeric_limits<T>::digits - r));
    } else {
        return (x << -r) | (x >> (std::numeric_limits<T>::digits + r));
    }
}
template<class T>
constexpr int countl_zero(T x) noexcept {
#if defined __GNUC__
    if (x != 0) {
        return __builtin_clzll(x);
    } else {
        return 0;
    }
#elif defined _MSC_VER
    return _BitScanReverse64(x);
#else
    int i;
    T mask = T{1} << (std::numeric_limits<T>::digits - 1);
    for (i = 0; (x & mask) == 0; x <<= 1, i++);
    return i;
#endif
}
template<class T>
constexpr int countl_one(T x) noexcept {
    return countl_zero(~x);
}
template<class T>
constexpr int countr_zero(T x) noexcept {
#if defined __GNUC__
    if (x != 0) {
        return __builtin_ctzll(x);
    } else {
        return 0;
    }
#elif defined _MSC_VER
    return _BitScanForward64(x);
#else
    int i;
    for (i = 0; (x & 1) == 0; x >>= 1, i++);
    return i;
#endif
}
template<class T>
constexpr int countr_one(T x) noexcept {
    return countl_one(~x);
}
template<class T>
constexpr int popcount(T x) noexcept {
#if defined __GNUC__
    return __builtin_popcountll(x);
#else
    int c = 0;
    for (int i = 0; i < std::numeric_limits<T>::digits; i++) {
        c += (x & 1);
        x >>= 1;
    }
    return c;
#endif
}

}
