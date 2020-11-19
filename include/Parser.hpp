// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#ifndef INCLUDE_JSONPARSER_HPP_
#define INCLUDE_JSONPARSER_HPP_
#pragma once
#include <any>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <Student.h>
using json = nlohmann::json;
using string = std :: string;
using any = std :: any;
using std :: cout;
using std :: setw;
using std :: runtime_error;
using std :: setfill;
using std :: any_cast;

class Parser {
 private:
  std::vector<Student> students;
  size_t name_w = 4;
  size_t group_w = 5;
  size_t avg_w = 3;
  size_t debt_w = 4;
 public:
  explicit Parser(std::vector<Student>);

  auto GetWidth(const string&) const -> size_t;

  void SetWidth(const string&, size_t);

  auto GetVector() const -> std::vector<Student>;

  void Print(const Student& student, std::ostream& os) const;

  void Filler(std::ostream& os) const;

  static void Filler(size_t size, size_t len, std::ostream& os);

  static Parser FromFile(const string&);

  static Parser FromString(const string&);

  friend std::ostream& operator<<(std::ostream&, const Parser&);
};

#endif // INCLUDE_JSONPARSER_HPP_
