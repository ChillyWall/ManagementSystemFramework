#ifndef PMS_FIELDS_HPP
#define PMS_FIELDS_HPP

#include <fmt/base.h>
#include <fmt/format.h>
#include <pms/DateTime.hpp>
#include <pms/types.hpp>

namespace pms {

/**
 * @class BasicField
 * @brief the base class for fields
 * @tparam T the type of the data
 */
template <typename T>
class BasicField {
private:
    T value_;

public:
    BasicField() {}

    explicit BasicField(const T& val) : value_(val) {}
    explicit BasicField(T&& val) : value_(std::move(val)) {}

    BasicField(const BasicField& rhs) = default;
    BasicField(BasicField&& rhs) noexcept = default;
    ~BasicField() noexcept = default;

    BasicField& operator=(const BasicField& rhs) = default;
    BasicField& operator=(BasicField&& rhs) noexcept = default;

    /**
     * @brief get the value
     * @return the const reference of the value
     */
    const T& value() const {
        return value_;
    }

    /**
     * @brief get the value
     * @return the reference of the value
     */
    T& value() {
        return const_cast<T&>(static_cast<const BasicField*>(this)->value());
    }

    /**
     * @brief get the string representation of the field's data
     * @return the string
     */
    virtual string str() const = 0;
};

/**
 * @class IntegerField
 * @brief the field for interger, represented by "Integer"
 */
class IntegerField : public BasicField<Integer> {
public:
    IntegerField() = default;
    IntegerField(const IntegerField& rhs) = default;
    IntegerField(IntegerField&& rhs) noexcept = default;

    using BasicField<Integer>::BasicField;

    ~IntegerField() noexcept = default;

    IntegerField& operator=(const IntegerField& rhs) = default;
    IntegerField& operator=(IntegerField&& rhs) noexcept = default;

    string str() const override {
        return fmt::to_string(BasicField<Integer>::value());
    }
};

/**
 * @class BooleanField
 * @brief the field for boolean, represented by "Boolean"
 */
class BooleanField : public BasicField<bool> {
public:
    using BasicField<bool>::BasicField;

    BooleanField() = default;
    BooleanField(const BooleanField& rhs) = default;
    BooleanField(BooleanField&& rhs) noexcept = default;

    ~BooleanField() noexcept = default;

    BooleanField& operator=(const BooleanField& rhs) = default;
    BooleanField& operator=(BooleanField&& rhs) noexcept = default;

    string str() const override {
        return fmt::to_string(BasicField<bool>::value());
    }
};

/**
 * @class FloatField
 * @brief the field for floating number, represented by "Float"
 */
class FloatField : public BasicField<double> {
public:
    using BasicField<double>::BasicField;

    FloatField() = default;
    FloatField(const FloatField& rhs) = default;
    FloatField(FloatField&& rhs) noexcept = default;
    ~FloatField() noexcept = default;

    FloatField& operator=(const FloatField& rhs) = default;
    FloatField& operator=(FloatField&& rhs) noexcept = default;

    string str() const override {
        return fmt::to_string(BasicField<double>::value());
    }
};

/**
 * @class TextField
 * @brief the field for text, represented by "Text"
 */
class TextField : public BasicField<string> {
public:
    using BasicField<string>::BasicField;

    TextField() = default;
    TextField(const TextField& rhs) = default;
    TextField(TextField&& rhs) noexcept = default;
    ~TextField() noexcept = default;

    TextField& operator=(const TextField& rhs) = default;
    TextField& operator=(TextField&& rhs) noexcept = default;

    string str() const override {
        return BasicField<string>::value();
    }
};

/**
 * @class DateField
 * @brief the field for date, represented by "Date"
 */
class DateField : public BasicField<Date> {
public:
    using BasicField<Date>::BasicField;

    DateField(const DateField& rhs) = default;
    DateField(DateField&& rhs) noexcept = default;
    DateField& operator=(const DateField& rhs) = default;
    DateField& operator=(DateField&& rhs) noexcept = default;
    ~DateField() noexcept = default;

    /**
     * @brief get the date in specific format
     * @param fmt_str the format string, uses {0}, {1}, {2} to represent
     * year, month, and day
     * @return the date string
     */
    string str(const string& fmt_str) const {
        return fmt::format(fmt_str, BasicField<Date>::value().year,
                           BasicField<Date>::value().month,
                           BasicField<Date>::value().day);
    }

    /**
     * @brief get the date in string type, formatted as "yy-mm-dd"
     * @return the date string
     */
    string str() const override {
        return str("{:04}-{:02}-{:02}");
    }
};

/**
 * @class TimeField
 * @brief the field for time, represented by "Time"
 */
class TimeField : public BasicField<Time> {
public:
    using BasicField<Time>::BasicField;

    TimeField() = default;
    TimeField(const TimeField& rhs) = default;
    TimeField(TimeField&& rhs) noexcept = default;
    ~TimeField() noexcept = default;

    TimeField& operator=(const TimeField& rhs) = default;
    TimeField& operator=(TimeField&& rhs) noexcept = default;

    /**
     * @brief get the time in specific format
     * @param fmt_str the format string, uses {0}, {1}, {2} to represent
     * hour, minute, and second
     * @return the time string
     */
    string str(const string& fmt_str) const {
        return fmt::format(fmt_str, BasicField<Time>::value().hour,
                           BasicField<Time>::value().minute,
                           BasicField<Time>::value().second);
    }

    /**
     * @brief get the date in string type, formatted as "h:m:s"
     * @return the time string
     */
    string str() const override {
        return str("{:02}:{:02}:{:02}");
    }
};

/**
 * @class DateTimeField
 * @brief the field for date and time, represented by "DateTime"
 */
class DateTimeField : public BasicField<DateTime> {
public:
    using BasicField<DateTime>::BasicField;

    DateTimeField() = default;
    DateTimeField(const DateTimeField& rhs) = default;
    DateTimeField(DateTimeField&& rhs) noexcept = default;
    ~DateTimeField() noexcept = default;

    DateTimeField& operator=(const DateTimeField& rhs) = default;
    DateTimeField& operator=(DateTimeField&& rhs) noexcept = default;

    /**
     * @brief get the date time in specific format
     * @param fmt_str the format string, uses {0}, {1}, {2}, {3}, {4}, {5}
     * to represent year, month, day, hour, minute, and second
     * @return the date time string
     */
    string str(string fmt_str) const {
        return fmt::format(fmt_str, BasicField<DateTime>::value().year,
                           BasicField<DateTime>::value().month,
                           BasicField<DateTime>::value().day,
                           BasicField<DateTime>::value().hour,
                           BasicField<DateTime>::value().minute,
                           BasicField<DateTime>::value().second);
    }

    /**
     * @brief convert the field to string, in format "y-m-d h:m:s"
     * @return the date time string
     */
    string str() const override {
        return str("{:04}-{:02}-{:02} {:02}:{:02}:{:02}");
    }
};
} // namespace pms
#endif
