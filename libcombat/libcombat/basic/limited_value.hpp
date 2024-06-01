#ifndef LIBCOMBAT_BASIC_LIMITED_VALUE_HPP
#define LIBCOMBAT_BASIC_LIMITED_VALUE_HPP

namespace libcombat::basic
{
    template <typename T>
    class LimitedValue
    {
    private:
        T value;
        T min;
        T max;
    public:
        T get() const { return value; }
        explicit operator T() const { return value; }

        void change() { value = std::max(min, std::min(max, value)); }

        LimitedValue<T> operator+(const T &scalar) const { return LimitedValue<T>(value + scalar); }
        LimitedValue<T> operator-(const T &scalar) const { return LimitedValue<T>(value - scalar); }
        LimitedValue<T> operator*(const T &scalar) const { return LimitedValue<T>(value * scalar); }
        LimitedValue<T> operator/(const T &scalar) const { return LimitedValue<T>(value / scalar); }

        void operator+=(const T &scalar) { value += scalar; change(); }
        void operator-=(const T &scalar) { value -= scalar; change(); }
        void operator*=(const T &scalar) { value *= scalar; change(); }
        void operator/=(const T &scalar) { value /= scalar; change(); }

        bool operator==(const T &scalar) const { return value == scalar; }
        bool operator!=(const T &scalar) const { return value != scalar; }
        bool operator<(const T &scalar) const { return value < scalar; }
        bool operator>(const T &scalar) const { return value > scalar; }
        bool operator<=(const T &scalar) const { return value <= scalar; }
        bool operator>=(const T &scalar) const { return value >= scalar; }

        LimitedValue<T> operator+(const LimitedValue<T> &other) const { return LimitedValue<T>(value + other.value); }
        LimitedValue<T> operator-(const LimitedValue<T> &other) const { return LimitedValue<T>(value - other.value); }
        LimitedValue<T> operator*(const LimitedValue<T> &other) const { return LimitedValue<T>(value * other.value); }
        LimitedValue<T> operator/(const LimitedValue<T> &other) const { return LimitedValue<T>(value / other.value); }

        void operator+=(const LimitedValue<T> &other) { value += other.value; change(); }
        void operator-=(const LimitedValue<T> &other) { value -= other.value; change(); }
        void operator*=(const LimitedValue<T> &other) { value *= other.value; change(); }
        void operator/=(const LimitedValue<T> &other) { value /= other.value; change(); }

        bool operator==(const LimitedValue<T> &other) { return value == other.value; }
        bool operator!=(const LimitedValue<T> &other) { return value != other.value; }
        bool operator<(const LimitedValue<T> &other) { return value < other.value; }
        bool operator>(const LimitedValue<T> &other) { return value > other.value; }
        bool operator<=(const LimitedValue<T> &other) { return value <= other.value; }
        bool operator>=(const LimitedValue<T> &other) { return value >= other.value; }

        LimitedValue(T value, T min, T max) : Stat<T>(value, min, max), min(min), max(max) {}
        LimitedValue(const LimitedValue<T> &other) : Stat<T>(other), min(other.min), max(other.max) {}
        LimitedValue(LimitedValue<T> &&other) : Stat<T>(other), min(other.min), max(other.max) {}

        void change() { value = std::max(min, std::min(max, value)); }
    };

    template <typename T>
    LimitedValue<T> operator+(const T &scalar, const LimitedValue<T> &stat) { return stat + scalar; }

    template <typename T>
    LimitedValue<T> operator-(const T &scalar, const LimitedValue<T> &stat) { return stat - scalar; }

    template <typename T>
    LimitedValue<T> operator*(const T &scalar, const LimitedValue<T> &stat) { return stat * scalar; }

    template <typename T>
    LimitedValue<T> operator/(const T &scalar, const LimitedValue<T> &stat) { return stat / scalar; }

    template <typename T>
    bool operator==(const T &scalar, const LimitedValue<T> &stat) { return stat == scalar; }

    template <typename T>
    bool operator!=(const T &scalar, const LimitedValue<T> &stat) { return stat != scalar; }

    template <typename T>
    bool operator<(const T &scalar, const LimitedValue<T> &stat) { return stat < scalar; }

    template <typename T>
    bool operator>(const T &scalar, const LimitedValue<T> &stat) { return stat > scalar; }

    template <typename T>
    bool operator<=(const T &scalar, const LimitedValue<T> &stat) { return stat <= scalar; }

    template <typename T>
    bool operator>=(const T &scalar, const LimitedValue<T> &stat) { return stat >= scalar; }

} // namespace libcombat::basic


#endif // LIBCOMBAT_BASIC_LIMITED_VALUE_HPP