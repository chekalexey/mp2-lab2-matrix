// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0)
        throw out_of_range("Vector size should be non negative");

    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size shoulde be smaller than MAX_VECTOR_SIZE");

    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      if (v.sz < 0) throw "negative size";
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->pMem = v.pMem;
      v.pMem = nullptr;
      this->sz = v.sz;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;

      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];

      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          pMem = v.pMem;
          sz = v.sz;
          v.pMem = nullptr;
          v.sz = 0;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= 0 && ind < sz)
          return pMem[ind];
      else
          throw out_of_range("Index out of range");
  }
  const T& at(size_t ind) const
  {
      if (ind >= 0 && ind < sz)
          return pMem[ind];
      else
          throw out_of_range("Index out of range");
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;

      for (int i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i])
              return false;

      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(this == &v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + val;
      return res;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - val;
      return res;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz != v.sz) throw "Array sizes are not equal";

      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = pMem[i] + v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.sz) throw "Array sizes are not equal";

      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = pMem[i] - v.pMem[i];
      return res;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw "Array sizes are not equal";

      T res = 0;
      for (int i = 0; i < sz; i++)
          res += pMem[i] * v.pMem[i];

      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:  
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz <= 0)
          throw out_of_range("Matrix size should be non negative");

      if (sz > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix size shoulde be smaller than MAX_MATRIX_SIZE");

      for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;

      for (int i = 0; i < sz; i++)
          for (int j = 0; j < sz; j++)
              if (m[i][j] != pMem[i][j])
                  return false;

      return true;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDanymicMatrix<T> res(sz);

      for (int i = 0; i < sz; i++)
          res.pMem[i] = val * pMem[i];

      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) throw "Sizes are not equal";

      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = pMem[i] * v;

      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.size()) throw "Sizes are not equal";

      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = m.pMem[i] + pMem[i];

      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.size()) throw "Sizes are not equal";

      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++)
          res[i] = m.pMem[i] - pMem[i];

      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.size()) throw "Sizes are not equal";

      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < m[0].size(); j++) {
              T tmp = 0;
              for (int k = 0; k < sz; k++)
                  tmp += pMem[i][k] * m[k][j];
              res[i][j] = tmp;
          }
      }

      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.size(); i++)
          cin >> v.pMem[i];

      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.size(); i++)
          cout << v.pMem[i] << endl;

      return ostr;
  }
};

#endif
