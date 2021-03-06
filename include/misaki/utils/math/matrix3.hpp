#pragma once

#include "vec3.hpp"

namespace misaki::math {

// Row major matrix
template <typename Value>
struct TMatrix3 {
  using Row = TVector3<Value>;
  using Column = TVector3<Value>;
  using Self = TMatrix3<Value>;

  Row data[3];

  MSK_XPU TMatrix3() noexcept : TMatrix3(Self::identity()) {
  }

  MSK_XPU TMatrix3(const Row &r0, const Row &r1, const Row &r2) noexcept : data{r0, r1, r2} {}

  MSK_XPU TMatrix3(Value m00, Value m01, Value m02,
                       Value m10, Value m11, Value m12,
                       Value m20, Value m21, Value m22) noexcept : data{{m00, m01, m02},
                                                                        {m10, m11, m12},
                                                                        {m20, m21, m22}} {}

  MSK_XPU static Self from_rows(const Row &r0, const Row &r1, const Row &r2) noexcept {
    return Self(r0, r1, r2);
  }

  MSK_XPU static Self from_cols(const Column &c0, const Column &c1, const Column &c2) noexcept {
    return Self(c0.x, c1.x, c2.x,
                c0.y, c1.y, c2.y,
                c0.z, c1.z, c2.z);
  }

  MSK_XPU static Self constant(Value val) noexcept {
    return Self(val, val, val,
                val, val, val,
                val, val, val);
  }

  MSK_XPU static Self diag(const Row &vec) noexcept {
    return Self(vec.x, 0, 0,
                0, vec.y, 0,
                0, 0, vec.z);
  }

  MSK_XPU static const Self &zeros() noexcept {
    static const Self ret = Self::constant(0);
    return ret;
  }

  MSK_XPU static const Self &ones() noexcept {
    static const Self ret = Self::constant(0);
    return ret;
  }

  MSK_XPU static const Self &identity() noexcept {
    static const Self ret = Self::diag(1);
    return ret;
  }
  // Component access
  MSK_XPU Row &operator[](size_t idx) noexcept {
    return data[idx];
  }

  MSK_XPU const Row &operator[](size_t idx) const noexcept {
    return data[idx];
  }

  MSK_XPU Value &operator()(size_t row, size_t col) noexcept {
    return data[row][col];
  }

  MSK_XPU const Value &operator()(size_t row, size_t col) const noexcept {
    return data[row][col];
  }

  MSK_XPU Column col(size_t idx) const noexcept {
    return Column(data[0][idx], data[1][idx], data[2][idx]);
  }

  MSK_XPU const Row &row(size_t idx) const noexcept {
    return data[idx];
  }

  // Element-wise computation
  MSK_XPU Self &operator+=(const Self &rhs) noexcept { return *this = *this + rhs; }
  MSK_XPU Self &operator-=(const Self &rhs) noexcept { return *this = *this - rhs; }
  MSK_XPU Self &operator*=(const Self &rhs) noexcept { return *this = *this * rhs; }

  MSK_XPU Self &operator+=(Value rhs) noexcept { return *this = *this + rhs; }

  MSK_XPU Self &operator-=(Value rhs) noexcept { return *this = *this - rhs; }

  MSK_XPU Self &operator*=(Value rhs) noexcept { return *this = *this * rhs; }

  MSK_XPU Self &operator/=(Value rhs) noexcept { return *this = *this / rhs; }

  // Math operation
  MSK_XPU decltype(auto) determinant() const noexcept {
    return data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
           data[1][0] * (data[0][1] * data[2][2] - data[2][1] * data[0][2]) +
           data[2][0] * (data[0][1] * data[1][2] - data[1][1] * data[0][2]);
  }

  MSK_XPU Self inverse() const noexcept {
    Value det = determinant();
    return Value(1.0) / det *
           Self(
               {data[1][1] * data[2][2] - data[2][1] * data[1][2],
                data[2][1] * data[0][2] - data[0][1] * data[2][2],
                data[0][1] * data[1][2] - data[1][1] * data[0][2]},
               {data[2][0] * data[1][2] - data[1][0] * data[2][2],
                data[0][0] * data[2][2] - data[2][0] * data[0][2],
                data[1][0] * data[0][2] - data[0][0] * data[1][2]},
               {data[1][0] * data[2][1] - data[2][0] * data[1][1],
                data[2][0] * data[0][1] - data[0][0] * data[2][1],
                data[0][0] * data[1][1] - data[1][0] * data[0][1]});
  }

  MSK_XPU Self transpose() const noexcept {
    return Self::from_cols(data[0], data[1], data[2]);
  }

  MSK_XPU bool operator==(const Self &m) const {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        if (data[i][j] != m.data[i][j])
          return false;
    return true;
  }

  MSK_XPU bool operator!=(const Self &m) const {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        if (data[i][j] != m.data[i][j])
          return true;
    return false;
  }

  MSK_XPU bool operator<(const Self &m) const {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) {
        if (data[i][j] < m.data[i][j])
          return true;
        if (data[i][j] > m.data[i][j])
          return false;
      }
    return false;
  }

  std::string to_string() const {
    std::ostringstream os;
    os << *this;
    return os.str();
  }
};

template <typename Value>
MSK_XPU TMatrix3<Value> operator+(const TMatrix3<Value> &lhs, const TMatrix3<Value> &rhs) noexcept {
  return TMatrix3<Value>::from_rows(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

template <typename Value>
MSK_XPU TMatrix3<Value> operator-(const TMatrix3<Value> &lhs, const TMatrix3<Value> &rhs) noexcept {
  return TMatrix3<Value>::from_rows(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}

template <typename Value>
MSK_XPU TMatrix3<Value> operator*(const TMatrix3<Value> &lhs, const TMatrix3<Value> &rhs) noexcept {
  TMatrix3<Value> ret;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      ret(r, c) = dot(lhs.row(r), rhs.col(c));
    }
  }
  return ret;
}

template <typename Value>
MSK_XPU TVector3<Value> operator*(const TMatrix3<Value> &lhs, const TVector3<Value> &rhs) noexcept {
  TVector3<Value> ret;
  for (int i = 0; i < 3; ++i) {
    ret[i] = dot(lhs.row(i), rhs);
  }
  return ret;
}

template <typename Value>
MSK_XPU TMatrix3<Value> operator+(const TMatrix3<Value> &lhs, Value rhs) noexcept {
  return TMatrix3<Value>(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs);
}

template <typename Value>
MSK_XPU TMatrix3<Value> operator-(const TMatrix3<Value> &lhs, Value rhs) noexcept {
  return TMatrix3<Value>(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs);
}

template <typename Value>
MSK_XPU TMatrix3<Value> operator*(const TMatrix3<Value> &lhs, Value rhs) noexcept {
  return TMatrix3<Value>(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs);
}

template <typename Value>
MSK_XPU TMatrix3<Value> operator/(const TMatrix3<Value> &lhs, Value rhs) noexcept {
  return TMatrix3<Value>(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
}

template <typename Value>
MSK_XPU TMatrix3<Value> operator*(Value lhs, const TMatrix3<Value> &rhs) noexcept {
  return rhs * lhs;
}

// Stream
template <typename Value>
std::ostream &operator<<(
    std::ostream &oss, const TMatrix3<Value> &mat) {
  oss << "[";
  oss << mat.row(0) << ",\n ";
  oss << mat.row(1) << ",\n ";
  oss << mat.row(2);
  oss << "]";
  return oss;
}

// Type alias
using Matrix3f = TMatrix3<float>;
using Matrix3d = TMatrix3<double>;

}  // namespace misaki::math