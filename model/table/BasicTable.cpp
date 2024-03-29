#include "BasicTable.h"
#include <filesystem>
namespace fs = std::filesystem;

string BasicTable::dataFilePath = "./data/";

void BasicTable::save() const {
    pt::ptree root, array;
    for(const auto& element: m_elements) {
        array.push_back(make_pair("item", element->encode()));
    }
    root.put_child(name(), array);
    string fileName = dataFilePath + name() + "Data.xml";
    if (!fs::is_directory(dataFilePath)) {
        if (fs::create_directory(dataFilePath)) {
            pt::write_xml(fileName, root);
        }
    } else {
        pt::write_xml(fileName, root);
    }
}

vector<const Object*> BasicTable::filter(const function<bool(const Object*)> &f) const {
    vector<const Object*> out;
    for (auto i: m_elements) {
        if (f(i)) out.emplace_back(i);
    }
    return out;
}

vector<Object*> BasicTable::filter(const function<bool(const Object*)> &f) {
    vector<Object*> out;
    for (auto i: m_elements) {
        if (f(i)) out.emplace_back(i);
    }
    return out;
}

const Object *BasicTable::first(const function<bool(const Object*)> &f) const {
    auto result = filter(f);
    return result.empty() ? nullptr : result.front();
}

Object *BasicTable::first(const function<bool(const Object*)> &f) {
    auto result = filter(f);
    return result.empty() ? nullptr : result.front();
}