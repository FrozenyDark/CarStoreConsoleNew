#include "Object.h"

ElementType getType(int id) {
    switch (id) {
        default: return et_empty;
        case 1: return et_boolean;
        case 2: return et_number;
        case 3: return et_string;
        case 4: return et_array;
        case 5: return et_object;
    }
}

ElementValue::ElementValue() {
    type = et_empty;
}

ElementValue::ElementValue(bool i) {
    type = et_boolean;
    value.boolean = i;
}

ElementValue::ElementValue(int i) {
    type = et_number;
    value.number = i;
}

ElementValue::ElementValue(double i) {
    type = et_number;
    value.number = i;
}

ElementValue::ElementValue(const std::string& i) {
    type = et_string;
    value.string = new std::string(i);
}

ElementValue::ElementValue(const char i[]) {
    type = et_string;
    value.string = new std::string(i);
}

ElementValue::ElementValue(const std::vector<ElementValue>& i) {
    type = et_array;
    value.array = new std::vector(i);
}

ElementValue::ElementValue(const Object& i) {
    type = et_object;
    value.object = i.clone();
}

ElementValue::ElementValue(const ElementValue& obj) {
    type = obj.type;
    switch (type) {
        case et_boolean:
            value.boolean = obj.value.boolean;
            break;
        case et_number:
            value.number = obj.value.number;
            break;
        case et_string:
            value.string = new std::string(*obj.value.string);
            break;
        case et_array:
            value.array = new std::vector(*obj.value.array);
            break;
        case et_object:
            value.object = obj.value.object->clone();
            break;
        default:
            break;
    }
}

ElementValue &ElementValue::operator=(const ElementValue &obj) {
    type = obj.type;
    switch (type) {
        case et_boolean:
            value.boolean = obj.value.boolean;
            break;
        case et_number:
            value.number = obj.value.number;
            break;
        case et_string:
            value.string = new std::string(*obj.value.string);
            break;
        case et_array:
            value.array = new std::vector(*obj.value.array);
            break;
        case et_object:
            value.object = obj.value.object->clone();
            break;
        default:
            break;
    }
    return *this;
}

bool ElementValue::operator==(const ElementValue &obj) const {
    if (type != obj.type) return false;
    switch (type) {
        case et_boolean: return value.boolean == obj.value.boolean;
        case et_number: return value.number == obj.value.number;
        case et_string: return *value.string == *obj.value.string;
        case et_array: return *value.array == *obj.value.array;
        case et_object: return *value.object == *obj.value.object;
        default: return true;
    }
}

ElementValue::~ElementValue() {
    switch (type) {
        case et_string:
            delete value.string;
            break;
        case et_array:
            delete value.array;
            break;
        case et_object:
            delete value.object;
            break;
        default:
            break;
    }
}

std::string ElementValue::toString() const {
    auto convertArray = [](const ElementValue& value) {
        return value.toString();
    };
    string num;
    switch (type) {
        case et_empty:
            return "null";
        case et_boolean:
            return value.boolean ? "true" : "false";
        case et_number:
            num = to_string(value.number);
            while (num.back() == '0') num.pop_back();
            if (num.back() == '.') num.pop_back();
            return num;
        case et_string:
            return *value.string;
        case et_array:
            return join(*value.array, convertArray, ", ");
        case et_object:
            return value.object->toString();
    }
}

Object::Object(const Object & obj) {
    _values = map<std::string, ElementValue>(obj._values);
}

ElementValue &Object::operator[](const std::string & i) {
    auto value = _values.find(i);
    if (value == _values.end()) {
        _values[i] = ElementValue();
    }
    return _values[i];
}

const ElementValue &Object::operator[](const std::string & i) const {
    auto value = _values.find(i);
    if (value == _values.end()) {
        throw std::out_of_range("Key not found.");
    }
    return _values.at(i);
}

Object &Object::operator=(const Object & obj) {
    _values = map<std::string, ElementValue>(obj._values);
    return *this;
}

bool Object::operator==(const Object &obj) const {
    for (const auto& field: fields()) {
        if (values().contains(field.first) && obj.values().contains(field.first)) {
            if (values().at(field.first) != obj[field.first]) return false;
        }
    }
    return true;
}

std::string Object::toString() const {
    auto convert = [](std::pair<std::string, ElementValue> i) {
        return "(" + i.first + ":" + i.second.toString() + ")";
    };
    return join(values(), convert, ", ");
}

const map<std::string, TypeName> CarModelClass::fields() const {
    map<std::string, TypeName> f;
    f.insert(std::make_pair("id", TypeName {et_string, "ID"}));
    f.insert(std::make_pair("mark", TypeName {et_string, "Mark"}));
    f.insert(std::make_pair("model", TypeName {et_string, "Model"}));
    f.insert(std::make_pair("type", TypeName {et_string, "Type"}));
    return f;
}

const map<std::string, TypeName> CarClass::fields() const {
    map<std::string, TypeName> f;
    f.insert(std::make_pair("id", TypeName {et_string, "ID"}));
    f.insert(std::make_pair("model_id", TypeName {et_string, "Model ID"}));
    f.insert(std::make_pair("mark", TypeName {et_string, "Mark"}));
    f.insert(std::make_pair("color", TypeName {et_string, "Color"}));
    f.insert(std::make_pair("price", TypeName {et_number, "Price"}));
    return f;
}

const map<std::string, TypeName> ManagerClass::fields() const {
    map<std::string, TypeName> f;
    f.insert(std::make_pair("id", TypeName {et_string, "ID"}));
    f.insert(std::make_pair("firstname", TypeName {et_string, "First name"}));
    f.insert(std::make_pair("lastname", TypeName {et_string, "Last name"}));
    f.insert(std::make_pair("age", TypeName {et_number, "Age"}));
    f.insert(std::make_pair("city", TypeName {et_string, "City"}));
    f.insert(std::make_pair("phone", TypeName {et_string, "Phone"}));
    return f;
}

const map<std::string, TypeName> CarManagerClass::fields() const {
    map<std::string, TypeName> f;
    f.insert(std::make_pair("car_id", TypeName {et_string, "Car ID"}));
    f.insert(std::make_pair("manager_id", TypeName {et_string, "Manager ID"}));
    f.insert(std::make_pair("lastname", TypeName {et_string, "Last name"}));
    f.insert(std::make_pair("city", TypeName {et_string, "City"}));
    f.insert(std::make_pair("phone", TypeName {et_string, "Phone"}));
    f.insert(std::make_pair("mark", TypeName {et_string, "Mark"}));
    return f;
}