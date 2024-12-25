#include <array>
#include <gtest/gtest.h>
#include <pms/BasicItem.hpp>
#include <pms/fields.hpp>
#include <string>

using namespace pms;
using std::array;
using std::string;

TEST(TestItemValue, TestBasicItem) {
    array<string, 5> field_names = {"name", "in_reading", "admision_time",
                                    "student_id", "education_system"};
    using Prisoner = BasicItem<5, TextField, BooleanField, DateField, TextField,
                               IntegerField>;
    Prisoner prisoner(TextField("郭金锋"), BooleanField(true),
                      DateField(Date(2024, 9, 1)), TextField("2024303424"),
                      IntegerField(4));
    ASSERT_EQ(prisoner.get_field_count(), 5);
    ASSERT_EQ(prisoner.get_field_value<0>(), string("郭金锋"));
    ASSERT_EQ(prisoner.get_field_value<1>(), true);
    Date value = prisoner.get_field_value<2>();
    ASSERT_EQ(value.year, 2024);
    ASSERT_EQ(value.month, 9);
    ASSERT_EQ(value.day, 1);
    ASSERT_EQ(prisoner.get_field_value<3>(), string("2024303424"));
    ASSERT_EQ(prisoner.get_field_value<4>(), 4);
}

TEST(TestItemStr, TestBasicItem) {
    array<string, 5> field_names = {"name", "in_reading", "admision_time",
                                    "student_id", "education_system"};
    using Prisoner = BasicItem<5, TextField, BooleanField, DateField, TextField,
                               IntegerField>;
    Prisoner prisoner(TextField("郭金锋"), BooleanField(true),
                      DateField(Date(2024, 9, 1)), TextField("2024303424"),
                      IntegerField(4));
    ASSERT_EQ(prisoner.get_field_str<0>(), string("郭金锋"));
    ASSERT_EQ(prisoner.get_field_str<1>(), string("true"));
    ASSERT_EQ(prisoner.get_field_str<2>(), string("2024-09-01"));
    ASSERT_EQ(prisoner.get_field_str<3>(), string("2024303424"));
    ASSERT_EQ(prisoner.get_field_str<4>(), string("4"));

    array<string, 5> str_arr(prisoner.get_fields_str());
    ASSERT_EQ(str_arr.at(0), string("郭金锋"));
    ASSERT_EQ(str_arr.at(1), string("true"));
    ASSERT_EQ(str_arr.at(2), string("2024-09-01"));
    ASSERT_EQ(str_arr.at(3), string("2024303424"));
    ASSERT_EQ(str_arr.at(4), string("4"));
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
