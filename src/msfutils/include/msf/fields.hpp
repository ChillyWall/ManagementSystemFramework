#ifndef PMS_FIELDS_HPP
#define PMS_FIELDS_HPP

#include <fmt/base.h>
#include <fmt/format.h>
#include <msf/DateTime.hpp>
#include <msf/types.hpp>
#include <sstream>
#include <stdexcept>

namespace msf {

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

    static constexpr c_string type() {
        return "Basic";
    }
};

/**
 * @class IntegerField
 * @brief the field for interger, represented by "Integer"
 */
class IntegerField : public BasicField<Integer> {
public:
    using BasicField<Integer>::BasicField;

    IntegerField() = default;
    IntegerField(const IntegerField& rhs) = default;
    IntegerField(IntegerField&& rhs) noexcept = default;

    IntegerField(const string& str) {
        std::istringstream iss(str);
        iss >> BasicField<Integer>::value();
        if (iss.fail()) {
            throw std::invalid_argument(
                fmt::format("Unable to convert {} to integer", str));
        }
    }

    ~IntegerField() noexcept = default;

    IntegerField& operator=(const IntegerField& rhs) = default;
    IntegerField& operator=(IntegerField&& rhs) noexcept = default;

    string str() const override {
        return fmt::to_string(BasicField<Integer>::value());
    }

    static constexpr c_string type() {
        return "Integer";
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

    BooleanField(const string& str) {
        bool res;
        if (str == "true") {
            res = true;
        } else if (str == "false") {
            res = false;
        } else {
            throw std::invalid_argument(
                fmt::format("Unable to convert {} to boolean", str));
        }
        BasicField<bool>::value() = res;
    }

    ~BooleanField() noexcept = default;

    BooleanField& operator=(const BooleanField& rhs) = default;
    BooleanField& operator=(BooleanField&& rhs) noexcept = default;

    string str() const override {
        return fmt::to_string(BasicField<bool>::value());
    }

    static constexpr c_string type() {
        return "Boolean";
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

    FloatField(const string& str) {
        std::istringstream iss(str);
        iss >> BasicField<double>::value();
        if (iss.fail()) {
            throw std::invalid_argument(
                fmt::format("Unable to convert {} to double", str));
        }
    }

    ~FloatField() noexcept = default;

    FloatField& operator=(const FloatField& rhs) = default;
    FloatField& operator=(FloatField&& rhs) noexcept = default;

    string str() const override {
        return fmt::to_string(value());
    }

    static constexpr c_string type() {
        return "Float";
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

    static constexpr c_string type() {
        return "Text";
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

    DateField(const string& str) {
        std::istringstream iss(str);
        char delimeter;
        iss >> value().year >> delimeter >> value().month >> delimeter >>
            value().day;
        if (iss.fail()) {
            throw std::invalid_argument(
                fmt::format("Unable to convert {} to Date", str));
        }
    }

    DateField& operator=(const DateField& rhs) = default;
    DateField& operator=(DateField&& rhs) noexcept = default;
    ~DateField() noexcept = default;

    /**
     * @brief get the date in "yy-mm-dd" format
     * @return the date string
     */
    string str() const {
        return fmt::format("{}-{:02}-{:02}", BasicField<Date>::value().year,
                           BasicField<Date>::value().month,
                           BasicField<Date>::value().day);
    }

    static constexpr c_string type() {
        return "Date";
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

    TimeField(const string& str) {
        std::istringstream iss(str);
        char delimeter;
        iss >> value().hour >> delimeter >> value().minute >> delimeter >>
            value().second;
        if (iss.fail()) {
            throw std::invalid_argument(
                fmt::format("Unable to convert {} to Time", str));
        }
    }

    ~TimeField() noexcept = default;

    TimeField& operator=(const TimeField& rhs) = default;
    TimeField& operator=(TimeField&& rhs) noexcept = default;

    /**
     * @brief get the time in "hour:minute:second" format
     * @return the time string
     */
    string str() const {
        return fmt::format("{:02}:{:02}:{:02}", BasicField<Time>::value().hour,
                           BasicField<Time>::value().minute,
                           BasicField<Time>::value().second);
    }

    static constexpr c_string type() {
        return "Time";
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

    DateTimeField(const string& str) {
        std::istringstream iss(str);
        char delimeter;
        iss >> value().year >> delimeter >> value().month >> delimeter >>
            value().day >> delimeter >> value().hour >> delimeter >>
            value().minute >> delimeter >> value().second;
        if (iss.fail()) {
            throw std::invalid_argument(
                fmt::format("Unable to convert {} to DateTime", str));
        }
    }

    ~DateTimeField() noexcept = default;

    DateTimeField& operator=(const DateTimeField& rhs) = default;
    DateTimeField& operator=(DateTimeField&& rhs) noexcept = default;

    /**
     * @brief get the date time in "yy-mm-dd hr:min:sec" format
     * @return the date time string
     */
    string str() const {
        return fmt::format("{}-{:02}-{:02} {:02}:{:02}:{:02}",
                           BasicField<DateTime>::value().year,
                           BasicField<DateTime>::value().month,
                           BasicField<DateTime>::value().day,
                           BasicField<DateTime>::value().hour,
                           BasicField<DateTime>::value().minute,
                           BasicField<DateTime>::value().second);
    }

    static constexpr c_string type() {
        return "DateTime";
    }
};
} // namespace msf
#endif
