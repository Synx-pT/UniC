#pragma once

#include <cstdio>
#include <cstdlib>

class String {
public:
  // Default constructor
  String();

  // Constructor from C-string
  explicit String(const char *str);

  // Copy constructor
  String(const String &other);

  // Copy assignment operator
  void operator=(const String &other);

  // Assignment from C-string
  void operator=(const char *str);

  // Destructor
  ~String();

  // Get the number of characters
  size_t size() const;

  // Get the C-string
  const char *c_str() const;

private:
  // Pointer to the allocated bytes
  char *data_ = nullptr;
  // Number of characters
  size_t size_ = 0;
};

class StringSorter {
public:
  // Constructor
  StringSorter(int n);

  // Destructor
  ~StringSorter();

  // Access operator
  String &operator[](int i);

  // Swap method
  void swap(int i, int j);

  int size() { return size_; };

  void sort();

private:
  String *strings_;
  int size_;
};
