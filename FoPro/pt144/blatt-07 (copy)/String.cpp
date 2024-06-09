#include "String.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>

// ____________________________________________________________________________
String::String() {
  data_ = new char[1];
  data_[0] = '\0';
  size_ = 0;
}

// ____________________________________________________________________________
String::String(const char *str) {
  if (str) {
    size_ = 0;
    while (str[size_] != '\0') {
      size_++;
    }
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = str[i];
    }
    data_[size_] = '\0';
  } else {
    data_ = new char[1];
    data_[0] = '\0';
    size_ = 0;
  }
}

// ____________________________________________________________________________
String::String(const String &other) {
  size_ = other.size_;
  data_ = new char[size_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
  data_[size_] = '\0';
}

// ____________________________________________________________________________
void String::operator=(const String &other) {
  if (c_str() != other.c_str()) { // Check for self-assignment
    delete[] data_;
    size_ = other.size_;
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
    data_[size_] = '\0';
  }
}

// ____________________________________________________________________________
void String::operator=(const char *str) {
  if (str) {
    delete[] data_;
    size_ = 0;
    while (str[size_] != '\0') {
      size_++;
    }
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = str[i];
    }
    data_[size_] = '\0';
  } else {
    delete[] data_;
    data_ = new char[1];
    data_[0] = '\0';
    size_ = 0;
  }
}

// ____________________________________________________________________________
String::String(String &&other) {
  // Identitätsdiebstahl
  data_ = other.data_;
  size_ = other.size_;
  other.data_ = nullptr;
  other.size_ = 0;
}

// ____________________________________________________________________________
String &String::operator=(String &&other) {
  delete[] data_;
  data_ = other.data_;
  size_ = other.size_;
  other.data_ = nullptr;
  other.size_ = 0;
  return *this;
}

// ____________________________________________________________________________
String::~String() { delete[] data_; }

// Get the number of characters
size_t String::size() const { return size_; }

// Get the C-string
const char *String::c_str() const { return data_; }

// ---STRING SORTER---

// ____________________________________________________________________________
StringSorter::StringSorter(int n) {
  strings_ = new String[n];
  size_ = n;

  for (int i = 0; i < n; i++) {
    strings_[i] = String();
  }
}

// ____________________________________________________________________________
StringSorter::~StringSorter() { delete[] strings_; }

// ____________________________________________________________________________
String &StringSorter::operator[](int i) { return strings_[i]; }

// ____________________________________________________________________________
void StringSorter::swap(int i, int j) {
  String temp = strings_[i];
  strings_[i] = strings_[j];
  strings_[j] = temp;
}

// ____________________________________________________________________________
void StringSorter::swapMove(int i, int j) {
  String temp = std::move(strings_[i]);
  strings_[i] = std::move(strings_[j]);
  strings_[j] = std::move(temp);
}

// ____________________________________________________________________________
void StringSorter::sortWithCopy() {
  bool did_swap = true;
  while (did_swap) {
    did_swap = false;

    for (int i = 0; i < size() - 1; i++) {

      if (strcmp(strings_[i].c_str(), strings_[i + 1].c_str()) > 0) {
        did_swap = true;
        swap(i, i + 1);
      }
    }
  }
}

// ____________________________________________________________________________
void StringSorter::sortWithMove() {
  bool did_swap = true;
  while (did_swap) {
    did_swap = false;

    for (int i = 0; i < size() - 1; i++) {

      if (strcmp(strings_[i].c_str(), strings_[i + 1].c_str()) > 0) {
        did_swap = true;
        swapMove(i, i + 1);
      }
    }
  }
}