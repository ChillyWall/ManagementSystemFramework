#include <gtest/gtest.h>
#include <pms/fields.hpp>

using namespace pms;

TEST(TestFieldValue, TestFields) {
    pms::TextField fields(std::string("test text field"));
    ASSERT_EQ(fields.value(), "test text field");

    pms::IntegerField fieldi(10);
    ASSERT_EQ(fieldi.value(), 10);

    pms::FloatField fieldf(10.0);
    ASSERT_EQ(fieldf.value(), 10.0);

    pms::BooleanField fieldb(true);
    ASSERT_EQ(fieldb.value(), true);

    pms::DateField field_d(pms::Date(2024, 12, 25));
    auto value = field_d.value();
    ASSERT_EQ(value.year, 2024);
    ASSERT_EQ(value.month, 12);
    ASSERT_EQ(value.day, 25);

    pms::TimeField field_t(pms::Time(0, 21, 24));
    auto value1 = field_t.value();
    ASSERT_EQ(value1.hour, 0);
    ASSERT_EQ(value1.minute, 21);
    ASSERT_EQ(value1.second, 24);

    pms::DateTimeField field_dt(pms::DateTime(2024, 12, 25, 0, 21, 24));
    auto value2 = field_dt.value();
    ASSERT_EQ(value2.year, 2024);
    ASSERT_EQ(value2.month, 12);
    ASSERT_EQ(value2.day, 25);
    ASSERT_EQ(value2.hour, 0);
    ASSERT_EQ(value2.minute, 21);
    ASSERT_EQ(value2.second, 24);
}

TEST(TestFieldStr, TestFields) {
    pms::TextField fields(std::string("test text field"));
    ASSERT_EQ(fields.str(), "test text field");

    pms::IntegerField fieldi(10);
    ASSERT_EQ(fieldi.str(), "10");

    pms::FloatField fieldf(10.1);
    ASSERT_EQ(fieldf.str(), "10.1");

    pms::BooleanField fieldb(true);
    ASSERT_EQ(fieldb.str(), "true");

    pms::DateField field_d(pms::Date(2024, 12, 4));
    ASSERT_EQ(field_d.str(), "2024-12-04");

    pms::TimeField field_t(pms::Time(23, 42, 5));
    ASSERT_EQ(field_t.str(), "23:42:05");

    pms::DateTimeField field_dt(pms::DateTime(2024, 12, 24, 23, 42, 5));
    ASSERT_EQ(field_dt.str(), "2024-12-24 23:42:05");
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
