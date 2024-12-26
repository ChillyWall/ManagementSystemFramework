#include <gtest/gtest.h>
#include <pms/fields.hpp>

using namespace pms;

pms::TextField field_s(std::string("test text field"));
pms::IntegerField field_i(10);
pms::FloatField field_f(3.1415);
pms::BooleanField field_b(true);
pms::DateField field_d(pms::Date(2024, 12, 5));
pms::TimeField field_t(pms::Time(0, 2, 4));
pms::DateTimeField field_dt(pms::DateTime(2024, 12, 25, 0, 21, 24));

TEST(TestFieldValue, TestFields) {
    ASSERT_EQ(field_s.value(), "test text field");

    ASSERT_EQ(field_i.value(), 10);

    ASSERT_EQ(field_f.value(), 3.1415);

    ASSERT_EQ(field_b.value(), true);

    auto value = field_d.value();
    ASSERT_EQ(value.year, 2024);
    ASSERT_EQ(value.month, 12);
    ASSERT_EQ(value.day, 5);

    auto value1 = field_t.value();
    ASSERT_EQ(value1.hour, 0);
    ASSERT_EQ(value1.minute, 2);
    ASSERT_EQ(value1.second, 4);

    auto value2 = field_dt.value();
    ASSERT_EQ(value2.year, 2024);
    ASSERT_EQ(value2.month, 12);
    ASSERT_EQ(value2.day, 25);
    ASSERT_EQ(value2.hour, 0);
    ASSERT_EQ(value2.minute, 21);
    ASSERT_EQ(value2.second, 24);
}

TEST(TestFieldStr, TestFields) {
    ASSERT_EQ(field_s.str(), "test text field");

    ASSERT_EQ(field_i.str(), "10");

    ASSERT_EQ(field_f.str(), "3.1415");

    ASSERT_EQ(field_b.str(), "true");

    ASSERT_EQ(field_d.str(), "2024-12-05");

    ASSERT_EQ(field_t.str(), "00:02:04");

    ASSERT_EQ(field_dt.str(), "2024-12-25 00:21:24");
}

TEST(TestFieldType, TestFields) {
    ASSERT_EQ(field_s.type(), "Text");
    ASSERT_EQ(field_i.type(), "Integer");
    ASSERT_EQ(field_f.type(), "Float");
    ASSERT_EQ(field_b.type(), "Boolean");
    ASSERT_EQ(field_d.type(), "Date");
    ASSERT_EQ(field_t.type(), "Time");
    ASSERT_EQ(field_dt.type(), "DateTime");
}

TEST(TestFieldConstructor, TestFields) {
    pms::TextField new_field_s(field_s.str());
    pms::IntegerField new_field_i(field_i.str());
    pms::FloatField new_field_f(field_f.str());
    pms::BooleanField new_field_b(field_b.str());
    pms::DateField new_field_d(field_d.str());
    pms::TimeField new_field_t(field_t.str());
    pms::DateTimeField new_field_dt(field_dt.str());

    ASSERT_EQ(new_field_s.value(), field_s.value());
    ASSERT_EQ(new_field_i.value(), field_i.value());
    ASSERT_EQ(new_field_f.value(), field_f.value());
    ASSERT_EQ(new_field_b.value(), field_b.value());
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
