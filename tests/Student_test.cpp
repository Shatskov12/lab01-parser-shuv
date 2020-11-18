// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <gtest/gtest.h>
#include <Student.h>

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}
TEST(Student_Test, EmptyIndex){
  const char j_string[] =\
      R"({"name": "Ivan Ivanov", "group": 9, "avg": 4, "debt": null})";
  Student emptyStudent((json::parse(j_string)));

  EXPECT_EQ(emptyStudent.GetType(""), Student::Null);
  EXPECT_EQ(std::any_cast<std::nullptr_t>(emptyStudent.GetField("")), \
      nullptr);
}
TEST(Student_Test, Student_Good_Filling) {
  string json_string1 =\
R"(
{
"name": "Ivan Ivanov",
"group": "IU10-39",
"avg": "4",
"debt": "C++"
})";
  Student student1(json::parse(json_string1));
  EXPECT_TRUE(student1 == 
  Student("Ivan Ivanov", string("IU10-39"), string("4"), string("C++")));
  string json_string2 =\
R"(
{
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null
})";
  Student student2(json::parse(json_string2));
  EXPECT_TRUE(student2 == Student("Ivan Ivanov", 39, 4, nullptr));
  string json_string3 =\
R"(
{
"name": "Ivan Ivanov",
"group": "Nine",
"avg": 3.33,
"debt": [
        "C++",
        "Linux",
        "Network"
      ]
})";
  Student student3(json::parse(json_string3));
  EXPECT_TRUE(student3 == 
   Student(
   "Ivan Ivanov",
   string("Nine"),
   3.33,
   std::vector<string>{"C++", "Linux", "Network"})
   );
}
TEST(Student_Test, Student_Bad_Filling) {
  string json_string1 =\
R"(
{
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null
})";
  Student student1(json::parse(json_string1));
  EXPECT_FALSE(student1 == 
  Student(
   "Petr Ivanov",
   39.10,
   nullptr, 
   std::vector<string>{"C++", "Linux", "Network"})
   );
  string json_string2 =\
R"(
{
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null
})";
  Student student2(json::parse(json_string2));
  EXPECT_FALSE(student1 ==
  Student(
  "Petr Ivanov", 
  std::vector<string>{"C++", "Linux", "Network"}, 
  std::vector<string>{"C++", "Linux", "Network"}, 
  2)
  );
  string json_string3 =\
R"(
{
"name": "Ivan Ivanov",
"group": 39,
"avg": 4,
"debt": null
})";
  Student student3(json::parse(json_string3));
  EXPECT_FALSE(student1 == 
  Student(
  "Petr Ivanov", 
  nullptr, 
  std::vector<string>{"C++", "Linux", "Network"}, 
  2.10)
  );
}
TEST(Student_Test, Incorect_Group) {
  string json_string1 =\
R"(
{
"name": "Ivan Ivanov",
"group": 9.10,
"avg": 3.33,
"debt": [
        "C++",
        "Linux",
        "Network"
      ]
})";
  try {
    Student student1(json::parse(json_string1));
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("incorrect data in field GROUP"));
  }
  string json_string2 =\
R"(
{
"name": "Ivan Ivanov",
"group": [
        "C++",
        "Linux",
        "Network"
      ],
"avg": 3.33,
"debt": [
        "C++",
        "Linux",
        "Network"
      ]
})";
  try {
    Student student1(json::parse(json_string2));
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("incorrect data in field GROUP"));
  }
  string json_string3 =\
R"(
{
"name": "Ivan Ivanov",
"group": null,
"avg": 3.33,
"debt": [
        "C++",
        "Linux",
        "Network"
      ]
})";
  try {
    Student student1(json::parse(json_string3));
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("incorrect data in field GROUP"));
  }
}
TEST(Student_Test, Incorect_Avg) {
  string json_string1 =\
R"(
{
"name": "Ivan Ivanov",
"group": 9,
"avg": null,
"debt": [
        "C++",
        "Linux",
        "Network"
      ]
})";
  try {
    Student student1(json::parse(json_string1));
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("incorrect data in field AVG"));
  }
  string json_string2 =\
R"(
{
"name": "Ivan Ivanov",
"group": 9,
"avg": [
        "C++",
        "Linux",
        "Network"
      ],
"debt": [
        "C++",
        "Linux",
        "Network"
      ]
})";
  try {
    Student student1(json::parse(json_string2));
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("incorrect data in field AVG"));
  }
}
TEST(Student_Test, Incorect_Debt) {
  string json_string1 =\
R"(
{
"name": "Ivan Ivanov",
"group": 9,
"avg": 3.33,
"debt": 2
})";
  try {
    Student student1(json::parse(json_string1));
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("incorrect data in field DEBT"));
  }
  string json_string2 =\
R"(
{
"name": "Ivan Ivanov",
"group": 9,
"avg": 3.33,
"debt": 1.5
})";
  try {
    Student student1(json::parse(json_string2));
  } catch (std::runtime_error& e) {
    EXPECT_TRUE(e.what() == string("incorrect data in field DEBT"));
  }
}

