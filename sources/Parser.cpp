// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <Parser.hpp>

Parser::Parser(std::vector<Student> new_student)
        : name_w(4), group_w(5), avg_w(3), debt_w(4) {
    students = std::move(new_student);
    for (const auto& student : students) {
        if (student.To_String(Field_Name[0]).length() > Get_Width(Field_Name[0]))
            Set_Width(Field_Name[0], student.To_String(Field_Name[0]).length());
        if (student.To_String(Field_Name[1]).length() > Get_Width(Field_Name[1]))
            Set_Width(Field_Name[1], student.To_String(Field_Name[1]).length());
        if (student.To_String(Field_Name[2]).length() > Get_Width(Field_Name[2]))
            Set_Width(Field_Name[2], student.To_String(Field_Name[2]).length());
        if (student.To_String(Field_Name[3]).length() > Get_Width(Field_Name[3]))
            Set_Width(Field_Name[3], student.To_String(Field_Name[3]).length());
    }
}

std::ostream& operator<<(std::ostream& os, const Parser& parser) {
    parser.Filler_separation(os);
    parser.Filler_top(os, parser);
    for (const auto& student : parser.Get_Vector()) {
        parser.Print_students(student, os);
    }
    parser.Filler_separation(os);
    return os;
}

auto Parser::Get_Width(const string& index) const -> size_t {
    if (index == Field_Name[0]) {
        return name_w;
    } else if (index == Field_Name[1]) {
        return group_w;
    } else if (index == Field_Name[2]) {
        return avg_w;
    } else if (index == Field_Name[3]) {
        return debt_w;
    }
    return 0;
}

void Parser::Set_Width(const string& index, size_t new_Value) {
    if (index == Field_Name[0]) {
        name_w = new_Value;
    } else if (index == Field_Name[1]) {
        group_w = new_Value;
    } else if (index == Field_Name[2]) {
        avg_w = new_Value;
    } else if (index == Field_Name[3]) {
        debt_w = new_Value;
    }
}
auto Parser::Get_Vector() const -> std::vector<Student> { return students; }
void Parser::Print_students(const Student& student, std::ostream& os) const {
    Filler_separation(os);
    os << "|" << student.To_String(Field_Name[0]);
    Filler(Get_Width(Field_Name[0]) -
           student.To_String(Field_Name[0]).length(), os);
    os << "|" << student.To_String(Field_Name[1]);
    Filler(Get_Width(Field_Name[1]) -
           student.To_String(Field_Name[1]).length(), os);
    os << "|" << student.To_String(Field_Name[2]);
    Filler(Get_Width(Field_Name[2]) -
           student.To_String(Field_Name[2]).length(), os);
    os << "|" << student.To_String(Field_Name[3]);
    Filler(Get_Width(Field_Name[3]) -
           student.To_String(Field_Name[3]).length(), os);
    os << "|" << std::endl;
}

void Parser::Filler_separation(std::ostream& os) const {
    os << "|";
    for (size_t i = 0; i < Get_Width(Field_Name[0]); ++i) {
        os << "-";
    }
    os << "|";
    for (size_t i = 0; i < Get_Width(Field_Name[1]); ++i) {
        os << "-";
    }
    os << "|";
    for (size_t i = 0; i < Get_Width(Field_Name[2]); ++i) {
        os << "-";
    }
    os << "|";
    for (size_t i = 0; i < Get_Width(Field_Name[3]); ++i) {
        os << "-";
    }
    os << "|" << std::endl;
}
void Parser::Filler_top(std::ostream& os, const Parser& parser) const {
    os << "|" << Field_Name[0];
    Filler(parser.Get_Width(Field_Name[0]) - Field_Name[0].length(), os);
    os << "|" << Field_Name[1];
    Filler(parser.Get_Width(Field_Name[1]) - Field_Name[1].length(), os);
    os << "|" << Field_Name[2];
    Filler(parser.Get_Width(Field_Name[2]) - Field_Name[2].length(), os);
    os << "|" << Field_Name[3];
    Filler(parser.Get_Width(Field_Name[3]) - Field_Name[3].length(), os);
    os << "|\n";
}
void Parser::Filler(size_t difference, std::ostream& os) {
    for (size_t i = 0; i < difference; ++i) {
        os << " ";
    }
}
Parser Parser::From_File(const string& json_Path) {
    std::ifstream file(json_Path);
    if (!file) {
        throw std::runtime_error{"unable to open file"};
    }
    json data;
    file >> data;
    if (data.empty()) {
        throw std::runtime_error{"file is empty"};
    }
    if (!data.at("items").is_array()) {
        throw std::runtime_error{"incorrect items field, items should be an array"};
    }
    if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
        throw std::runtime_error{
                R"(incorrect count field, count at meta
     should be equal items field size)"};
    }
    std::vector<Student> newStudents;
    for (const auto& item : data.at("items")) {
        Student newStudent(item);
        newStudents.push_back(newStudent);
    }
    return Parser(newStudents);
}

Parser Parser::From_String(const string& json_String) {
    json data = json::parse(json_String);
    if (!data.at("items").is_array()) {
        throw std::runtime_error{"incorrect items field, items should be an array"};
    }
    if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
        throw std::runtime_error{
                R"(incorrect count field, count at meta
     should be equal items field size)"};
    }
    std::vector<Student> newStudents;
    for (const auto& item : data.at("items")) {
        Student newStudent(item);
        newStudents.push_back(newStudent);
    }
    return Parser(newStudents);
}
