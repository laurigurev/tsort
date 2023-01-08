#pragma once

#define sizeofbits(x) (sizeof(x) * 8)

template <size_t N>
struct bitset2 {
        constexpr bitset2() noexcept : counter(0)
        {
                // printf("bitset2::bitset2() size %llu\n", (N / sizeofbits(size_t)) + 1);
                memset(data, 0, sizeof(size_t));
        }
        constexpr bool test(const size_t i) noexcept
        {
                const size_t a = i % sizeofbits(size_t);
                const size_t b = (i - a) / sizeofbits(size_t);
                if (data[b] & (1 << a)) return true;
                return false;
        }
        constexpr bool all() noexcept
        {
                if (counter == N) return true;
                return false;
        }
        constexpr bool any()
 noexcept        {
                if (counter) return true;
                return false;
        }
        constexpr bool none() noexcept
        {
                // printf("bitset2::none() counter %llu\n", counter);
                if (counter == 0) return true;
                return false;
        }
        constexpr size_t size() noexcept
        {
                return N;
        }
        constexpr size_t count() noexcept
        {
                return counter;
        }
        constexpr void set(const size_t i) noexcept
        {
                const size_t a = i % sizeofbits(size_t);
                const size_t b = (i - a) / sizeofbits(size_t);
                data[b] |= (1 << a);
                counter++;
                // printf("bitset2::set() i %llu, b %llu, a %llu counter %llu\n", i, b, a, counter);
        }
        constexpr void reset(const size_t i) noexcept
        {
                const size_t a = i % sizeofbits(size_t);
                const size_t b = (i - a) / sizeofbits(size_t);
                data[b] ^= (1 << a);
                if (counter) counter--;
                // printf("bitset2::reset() i %llu, b %llu, a %llu, counter %llu", i, b, a, counter);
                // printf(", data[%llu] %llu\n", b, data[b]);
        }
        constexpr void flip() noexcept
        {
                for (size_t n : data) n = !n;
                counter = N - counter;
        }
        constexpr size_t find_first() noexcept
        {
                for (size_t i = 0; i < 1; i++) {
                        if (!data[i]) continue;
                        for (size_t j = 0; j < sizeofbits(size_t); j++) {
                                const size_t mask = 1 << j;
                                if (data[i] & mask) return (i + j);
                        }
                }
                return -1;
        }
        constexpr bool operator[](size_t i) noexcept
        {
                const size_t a = i % sizeofbits(size_t);
                const size_t b = (i - a) / sizeofbits(size_t);
                return (data[b] & (1 << a));
        }
        constexpr bitset2& operator^=(const bitset2& bs) noexcept
        {
                for (size_t i = 0; i < 1; i++) {
                        data[i] ^= bs.data[i];
                }
                return *this;
        }

        size_t data[(N / sizeofbits(size_t)) + 1];
        size_t counter;
};
