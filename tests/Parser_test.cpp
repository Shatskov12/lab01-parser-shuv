// Copyright 2020 MIX-1 <danilonil1@yandex.ru>


#include <gtest/gtest.h>
#include <Parser.hpp>

TEST(Parser_Test, Print) {
      const char j_string[] =\
R"({"name": "Ivan Ivanov", "group": "IU10-39", "avg": "4", "debt": "C++"})";
      json j = json::parse(j_string);
      Student Nikita(j);

      const char j_string1[] =\
R"({"name": "Ivan Ivanov", "group": 39, "avg": 4, "debt": null})";
      j = json::parse(j_string1);
      Student Ivan(j);

      const char j_string2[] =\
      R"({"name": "Ivan Ivanov", "group": "Nine", "avg": 3.33, "debt": ["C++", "Linux", "Network"]})";
      j = json::parse(j_string2);
      Student Petr(j);

Parser parser(std::vector<Student>{Petr, Ivan, Nikita});

  std::stringstream parser_stream;
  parser_stream << parser;
  string ref_string =\
      R"(|-----------|-------|----|-------|
|name       |group  |avg |debt   |
|-----------|-------|----|-------|
|Ivan Ivanov|Nine   |3.33|3 items|
|-----------|-------|----|-------|
|Ivan Ivanov|39     |4   |null   |
|-----------|-------|----|-------|
|Ivan Ivanov|IU10-39|4   |C++    |
|-----------|-------|----|-------|
)";

  EXPECT_TRUE(ref_string == parser_stream.str());
}
TEST(Parser_Test, Empty_Students) {
  Parser parser(std::vector<Student>{});
  std::stringstream res;
  res << parser;
  const char ref_str[] = R"(|----|-----|---|----|
|name|group|avg|debt|
|----|-----|---|----|
)";
  EXPECT_EQ(res.str(), ref_str);
  EXPECT_EQ(parser.Get_Width(""), 0);
}
TEST(Parser_Test, File_Open_Bad) {
  try {
    Parser::From_File("Bad_File.json");
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("unable to open file"));
  }
}
TEST(Parser_Test, Empty_File) {
  string json_string1 =\
R"({})";
  std::ofstream true_file;
  true_file.open("true_file.json", std::ios::out);
  true_file << json_string1;
  true_file.close();
  try {
    Parser::FromFile("true_file.json");
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("file is empty"));
  }
}
TEST(Parser_Test, Items_is_array_Bad) {
  string json_string1 =\
R"({
"items": 0,
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null,
"_meta": {
"count": 3
}
})";
  std::ofstream true_file;
  true_file.open("true_file.json", std::ios::out);
  true_file << json_string1;
  true_file.close();
  try {
    Parser::From_File("true_file.json");
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() ==
                string("incorrect items field, items should be an array"));
  }
  try {
    Parser::From_String(json_string1);
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() ==
                string("incorrect items field, items should be an array"));
  }
}
TEST(Parser_Test, Count_Bad) {
  string json_string1 =\
R"({
"items": [
{
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null
}
],
"_meta": {
"count": 2
}
})";
  std::ofstream true_file;
  true_file.open("true_file.json", std::ios::out);
  true_file << json_string1;
  true_file.close();
  try {
    Parser::From_File("true_file.json");
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() ==
                string(R"(incorrect count field, count at meta
     should be equal items field size)"));
  }
  try {
    Parser::From_String(json_string1);
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() ==
                string(R"(incorrect count field, count at meta
     should be equal items field size)"));
  }
}
TEST(Parser_Test, All_Good) {
  string json_string1 =\
R"({
"items": [
{
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null
}
],
"_meta": {
"count": 1
}
})";
  string table_true =\
 R"(|-----------|-----|---|----|
|name       |group|avg|debt|
|-----------|-----|---|----|
|Ivan Ivanov|39   |4  |null|
|-----------|-----|---|----|
)";
  std::ofstream true_file;
  true_file.open("true_file.json", std::ios::out);
  true_file << json_string1;
  true_file.close();
  std::stringstream parser_stream1;
  parser_stream1 << Parser::From_File("true_file.json");
  EXPECT_EQ(parser_stream1.str(), table_true);
  std::stringstream parser_stream2;
  parser_stream2 << Parser::From_String(json_string1);
  EXPECT_EQ(parser_stream2.str(), table_true);
}
