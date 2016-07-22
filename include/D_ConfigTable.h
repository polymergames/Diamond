/*
    Copyright 2016 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef D_CONFIGTABLE_H
#define D_CONFIGTABLE_H

#include <string>
#include <unordered_map>

namespace Diamond {
    using tConfigHashMap = std::unordered_map<std::string, std::string>;

    /**
     * Stores key-value pairs for configuration items.
     * All get functions return the value-initialized type
     * if the given key is not found.
     */
    class ConfigTable {
    public:

        bool hasKey(const std::string &key) const {
            return m_table.find(key) != m_table.end();
        }


        std::string get(const std::string &key) {
            return m_table[key];
        }

        std::string get(const std::string &key) const {
            return findGet(key);
        }


        int getInt(const std::string &key) {
            return std::atoi(m_table[key].c_str());
        }

        int getInt(const std::string &key) const {
            return std::atoi(findGet(key).c_str());
        }


        float getFloat(const std::string &key) {
            return std::atof(m_table[key].c_str());
        }

        float getFloat(const std::string &key) const {
            return std::atof(findGet(key).c_str());
        }


        bool getBool(const std::string &key) {
            return stringToBool(m_table[key]);
        }

        bool getBool(const std::string &key) const {
            return stringToBool(findGet(key));
        }


        void set(const std::string &key,
                 const std::string &value) { m_table[key] = value; }

        void set(const std::string &key,
                 const char *value) { m_table[key] = value; }

        void set(const std::string &key,
                 int value) { m_table[key] = std::to_string(value); }

        void set(const std::string &key,
                 float value) { m_table[key] = std::to_string(value); }

        void set(const std::string &key,
                 double value) { m_table[key] = std::to_string(value); }

        void set(const std::string &key,
                 bool value) { m_table[key] = std::to_string((int)value); }


        size_t size() const { return m_table.size(); }


        const tConfigHashMap &data() const { return m_table; }

    private:
        tConfigHashMap m_table;

        std::string findGet(const std::string &key) const {
            auto i = m_table.find(key);
            return i != m_table.end() ? i->second : std::string();
        }

        bool stringToBool(const std::string &str) const {
            return str == "1"    ||
                   str == "y"    ||
                   str == "Y"    ||
                   str == "T"    ||
                   str == "yes"  ||
                   str == "Yes"  ||
                   str == "YES"  ||
                   str == "true" ||
                   str == "True" ||
                   str == "TRUE";
        }
    };
}


#endif // D_CONFIGTABLE_H
