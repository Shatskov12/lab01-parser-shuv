// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <Parser.hpp>

Parser::Parser(std::vector<Student> new_student) {
  students = std::move(new_student);
  for (const auto& student : students) {
    if (student.ToString(FieldName[0]).length() >\
        GetWidth(FieldName[0]))
      SetWidth(FieldName[0], student.ToString(FieldName[0]).length());
    if (student.ToString(FieldName[1]).length() >\
      GetWidth(FieldName[1]))
      SetWidth(FieldName[1], student.ToString(FieldName[1]).length());
    if (student.ToString(FieldName[2]).length() >\
      GetWidth(FieldName[2]))
      SetWidth(FieldName[2], student.ToString(FieldName[2]).length());
    if (student.ToString(FieldName[3]).length() >\
      GetWidth(FieldName[3]))
      SetWidth(FieldName[3], student.ToString(FieldName[3]).length());
  }
}

std::ostream& operator<<(std::ostream &os, const Parser& parser) {
  parser.Filler(os);
  std::stringstream tab;
  tab << "|" << FieldName[0];
  for (size_t i = 0;
       i < (parser.GetWidth(FieldName[0]) - FieldName[0].length());
       ++i){
    tab << " ";
  }
  tab << "|" << FieldName[1];
  for (size_t i = 0;
       i < parser.GetWidth(FieldName[1]) - FieldName[1].length();
       ++i){
    tab << " ";
  }
  tab << "|" << FieldName[2];
  for (size_t i = 0;
       i < parser.GetWidth(FieldName[2]) - FieldName[2].length();
       ++i){
    tab << " ";
  }
  tab << "|" << FieldName[3];
  for (size_t i = 0;
       i < parser.GetWidth(FieldName[3]) - FieldName[3].length();
       ++i){
    tab << " ";
  }
  tab << "|";
  os << tab.str() << std::endl;

  for (const auto& student : parser.GetVector()) {
    parser.Print(student, os);
  }
  parser.Filler(os);

  return os;
}

auto Parser::GetWidth(const string& index) const -> size_t {
  if ( index == FieldName[0] ){
    return name_w;
  } else if ( index == FieldName[1] ){
    return group_w;
  } else if ( index == FieldName[2] ){
    return avg_w;
  } else if ( index == FieldName[3] ){
    return debt_w;
  } return 0;
}

void Parser::SetWidth(const string& index, size_t newValue) {
  if ( index == FieldName[0] ){
    name_w = newValue;
  } else if ( index == FieldName[1] ){
    group_w = newValue;
  } else if ( index == FieldName[2] ){
    avg_w = newValue;
  } else if ( index == FieldName[3] ){
    debt_w = newValue;
  }
}
auto Parser::GetVector() const -> std::vector<Student> {
  return students;
}
void Parser::Print(const Student& student, std::ostream& os) const {
  Filler(os);
  os << "|" << student.ToString(FieldName[0]);
  Filler(GetWidth(FieldName[0]), student.ToString(FieldName[0]).length(), os);
  os << "|" << student.ToString(FieldName[1]);
  Filler(GetWidth(FieldName[1]), student.ToString(FieldName[1]).length(), os);
  os << "|" << student.ToString(FieldName[2]);
  Filler(GetWidth(FieldName[2]), student.ToString(FieldName[2]).length(), os);
  os << "|" << student.ToString(FieldName[3]);
  Filler(GetWidth(FieldName[3]), student.ToString(FieldName[3]).length(), os);
  os << "|" << std::endl;
}

void Parser::Filler(std::ostream& os) const {
  os << "|";
  for (size_t i = 0; i < GetWidth(FieldName[0]); ++i){
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < GetWidth(FieldName[1]); ++i){
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < GetWidth(FieldName[2]); ++i){
    os << "-";
  }
  os << "|";
  for (size_t i = 0; i < GetWidth(FieldName[3]); ++i){
    os << "-";
  }
  os << "|" << std::endl;
}
void Parser::Filler(size_t size, size_t len, std::ostream& os) {
  for (size_t i = 0; i < size - len; ++i){
    os << " ";
  }
}
Parser Parser::FromFile(const string& jsonPath) {
  std::ifstream file(jsonPath);
  if (!file) {
    throw std::runtime_error{"unable to open file"};
  }
  json data;
  file >> data;
  if (data.empty()){
    throw std::runtime_error
        {"file is empty"};
  }
  if (!data.at("items").is_array()){
    throw std::runtime_error
        {"incorrect items field, items should be an array"};
  }
  if (data.at("items").size() !=\
      data.at("_meta").at("count").get<size_t>()) {
    throw std::runtime_error
        {
            R"(incorrect count field, count at meta
     should be equal items field size)"
        };
  }
  std::vector<Student> newStudents;
  for ( const auto& item : data.at("items") ){
    Student newStudent(item);
    newStudents.push_back(newStudent);
  }
  return Parser(newStudents);
}

Parser Parser::FromString(const string& jsonString) {
  json data = json::parse(jsonString);
  if (!data.at("items").is_array()){
    throw std::runtime_error
        {"incorrect items field, items should be an array"};
  }
  if (data.at("items").size() !=\
      data.at("_meta").at("count").get<size_t>()){
    throw std::runtime_error
        {
            R"(incorrect count field, count at meta
     should be equal items field size)"};
  }
  std::vector<Student> newStudents;
  for ( const auto& item : data.at("items") ){
    Student newStudent(item);
    newStudents.push_back(newStudent);
  }
  return Parser(newStudents);
}
