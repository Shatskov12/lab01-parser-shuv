// Copyright 2020 Shatskov12 <qweser2016@mail.ru>

#ifndef LAB_01_PARSER_STUDENT_HPP
#define LAB_01_PARSER_STUDENT_HPP
#pragma once
#include <any>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using std :: string;
using any = std :: any;
using std :: cout;
using std :: setw;
using std :: runtime_error;
using std :: setfill;
using std :: any_cast;

const char Field_Name[4][6] = {"name", "group", "avg", "debt"};

struct Student {
public:
    enum Type {
        Null,
        String,
        Integer,
        Array,
        Double};

    explicit Student(json);

    explicit Student(string, any, any, any);

    bool operator==(const Student&) const;

    string To_String(const string&) const;

    auto Get_Type(const string&) const -> Type;

    auto Get_Field(const string&) const -> any;

private:
    string name;
    any group;
    any avg;
    any debt;

    Type name_type = String;
    Type group_type;
    Type avg_type;
    Type debt_type;
};

#endif  // LAB_01_PARSER_STUDENT_HPP
