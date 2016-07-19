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
    class ConfigTable {
    public:
        std::string get(const std::string &key) { return m_table[key]; }

        void set(const std::string &key,
                 const std::string &value) { m_table[key] = value; }

        size_t size() const { return m_table.size(); }

    private:
        std::unordered_map<std::string, std::string> m_table;
    };
}


#endif // D_CONFIGTABLE_H
