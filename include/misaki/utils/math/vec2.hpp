#pragma once

#include "common.hpp"

namespace misaki::math {

template <typename Value>
class TVector2 {
 public:
  using Self = TVector2<Value>;
  Value x, y;

  MSK_XPU constexpr TVector2() noexcept : x(0), y(0) {}

  MSK_XPU constexpr TVector2(Value x, Value y) noexcept : x(x), y(y) {}

  MSK_XPU constexpr TVector2(Value x) noexcept : x(x), y(x) {}

  template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
  MSK_XPU constexpr TVector2(const TVector2<T> &vec) noexcept : x(Value(vec.x)), y(Value(vec.y)) {}

  // Component access operation
  MSK_XPU Value &operator[](size_t idx) noexcept {
    return *(&x + idx);
  }

  MSK_XPU const Value &operator[](size_t idx) const noexcept {
    return *(&x + idx);
  }

  // Inline math functions
  MSK_XPU auto norm() const noexcept {
    return std::sqrt(squared_norm());
  }

  MSK_XPU auto squared_norm() const noexcept {
    return x * x + y * y;
  }

  MSK_XPU Self normalize() const noexcept {
    static_assert(std::is_floating_point_v<Value>);
    return *this / norm();
  }

  MSK_XPU Self clamp(Value min_v, Value max_v) const noexcept {
    return Self(std::clamp(x, min_v, max_v),
                std::clamp(y, min_v, max_v));
  }

  MSK_XPU Self abs() const noexcept {
    return Self(std::abs(x), std::abs(y));
  }

  MSK_XPU Self ceil() const noexcept {
    return Self(std::ceil(x), std::ceil(y));
  }

  MSK_XPU Self floor() const noexcept {
    return Self(std::floor(x), std::floor(y));
  }

  MSK_XPU auto hsum() const noexcept {
    return x + y;
  }

  MSK_XPU auto hprod() const noexcept {
    return x * y;
  }

  MSK_XPU Value max_coeff() const noexcept { return std::max({x, y}); }

  MSK_XPU Value min_coeff() const noexcept { return std::min({x, y}); }

  // Unary squared_norm
  MSK_XPU Self &operator+=(const Self &rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  MSK_XPU Self &operator-=(const Self &rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  MSK_XPU Self &operator*=(const Self &rhs) noexcept {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  MSK_XPU Self &operator/=(const Self &rhs) noexcept {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  MSK_XPU Self &operator+=(Value rhs) noexcept {
    x += rhs;
    y += rhs;
    return *this;
  }

  MSK_XPU Self &operator-=(Value rhs) noexcept {
    x -= rhs;
    y -= rhs;
    return *this;
  }

  MSK_XPU Self &operator*=(Value rhs) noexcept {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  MSK_XPU Self &operator/=(Value rhs) noexcept {
    x /= rhs;
    y /= rhs;
    return *this;
  }

  MSK_XPU bool operator==(const Self &c) const { return x == c.x && y == c.y; }
  MSK_XPU bool operator!=(const Self &c) const { return x != c.x || y != c.y; }

  std::string to_string() const {
    std::ostringstream os;
    os << *this;
    return os.str();
  }
};
// Unary operation
template <typename Value>
MSK_XPU TVector2<Value> operator-(const TVector2<Value> &vec) noexcept {
  return TVector2<Value>(-vec.x, -vec.y);
}

template <typename Value>
MSK_XPU inline auto norm(const TVector2<Value> &v) {
  return v.norm();
}

template <typename Value>
MSK_XPU inline auto squared_norm(const TVector2<Value> &v) {
  return v.squared_norm();
}

template <typename Value>
MSK_XPU inline auto normalize(const TVector2<Value> &v) {
  return v.normalize();
}

template <typename Value>
MSK_XPU inline auto abs(const TVector2<Value> &v) {
  return v.abs();
}

template <typename Value>
MSK_XPU inline auto ceil(const TVector2<Value> &v) {
  return v.ceil();
}

template <typename Value>
MSK_XPU inline auto floor(const TVector2<Value> &v) {
  return v.floor();
}

template <typename Value>
MSK_XPU inline auto hmin(const TVector2<Value> &v) {
  return v.min_coeff();
}

template <typename Value>
MSK_XPU inline auto hmax(const TVector2<Value> &v) {
  return v.max_coeff();
}
// Binary operation
template <typename Value>
MSK_XPU TVector2<Value> operator+(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename Value>
MSK_XPU TVector2<Value> operator-(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename Value>
MSK_XPU TVector2<Value> operator*(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename Value>
MSK_XPU TVector2<Value> operator/(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator+(const TVector2<Value> &lhs, T rhs) noexcept {
  return TVector2<Value>(lhs.x + rhs, lhs.y + rhs);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator-(const TVector2<Value> &lhs, T rhs) noexcept {
  return TVector2<Value>(lhs.x - rhs, lhs.y - rhs);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator*(const TVector2<Value> &lhs, T rhs) noexcept {
  return TVector2<Value>(lhs.x * rhs, lhs.y * rhs);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator/(const TVector2<Value> &lhs, T rhs) noexcept {
  return TVector2<Value>(lhs.x / rhs, lhs.y / rhs);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator+(T lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs + rhs.x, lhs + rhs.y);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator-(T lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs - rhs.x, lhs - rhs.y);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator*(T lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs * rhs.x, lhs * rhs.y);
}

template <typename Value, typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
MSK_XPU TVector2<Value> operator/(T lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(lhs / rhs.x, lhs / rhs.y);
}
// Math functions
template <typename Value>
MSK_XPU auto dot(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename Value>
MSK_XPU TVector2<Value> min(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y));
}

template <typename Value>
MSK_XPU TVector2<Value> max(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y));
}

template <typename Value>
MSK_XPU TVector2<Value> abs(const TVector2<Value> &lhs, const TVector2<Value> &rhs) noexcept {
  return TVector2<Value>(std::abs(lhs.x, rhs.x), std::abs(lhs.y, rhs.y));
}

// Stream
template <typename Value>
std::ostream &operator<<(
    std::ostream &oss, const TVector2<Value> &vec) {
  oss << "[";
  oss << vec.x << ", ";
  oss << vec.y;
  oss << "]";
  return oss;
}

// Type alias
using Vector2f = TVector2<float>;
using Vector2d = TVector2<double>;
using Vector2i = TVector2<int>;
using Vector2u = TVector2<uint32_t>;

}  // namespace misaki::math