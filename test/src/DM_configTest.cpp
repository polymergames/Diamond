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

#include "gtest/gtest.h"
#include "D_StdConfigLoader.h"

using namespace Diamond;

class TestConfigLoader : public StdConfigLoader {
public:
    bool testParse(const std::string &line,
                   const std::string &expKey,
                   const std::string &expVal) {
        std::string key, val;
        bool ok = parseLine(line, key, val);

        EXPECT_EQ(expKey, key);
        EXPECT_EQ(expVal, val);

        return ok;
    }
};


TEST(ConfigTest, Parses) {
    TestConfigLoader configLoader;
    bool ok;

    ok = configLoader.testParse("Boss:Ahnaf", "Boss", "Ahnaf");
    EXPECT_TRUE(ok);

    ok = configLoader.testParse("MyPowerLevel:9001", "MyPowerLevel", "9001");
    EXPECT_TRUE(ok);
}


TEST(ConfigTest, InvalidParses) {
    TestConfigLoader configLoader;
    bool ok;

    ok = configLoader.testParse("iamerror", "", "");
    EXPECT_FALSE(ok);

    ok = configLoader.testParse(":wut", "", "");
    EXPECT_FALSE(ok);

    ok = configLoader.testParse("wut:", "", "");
    EXPECT_FALSE(ok);
}


TEST(ConfigTest, LoadsFile) {
    StdConfigLoader configLoader;

    ConfigTable config = configLoader.load("game.cfg");

    EXPECT_EQ(config.size(), 11);

    EXPECT_EQ(config.get("Game"), "Life");
    EXPECT_EQ(config.get("Difficulty"), "HardAF");

    EXPECT_EQ(config.getInt("PowerLevel"), 9001);
    EXPECT_EQ(config.getInt("Release"), 0);
    EXPECT_FLOAT_EQ(config.getFloat("pi"), 3.14);

    EXPECT_EQ(config.get("Price"), "Death");
    EXPECT_EQ(config.get("Graphics"), "Ultra");

    EXPECT_TRUE(config.getBool("Running"));
    EXPECT_TRUE(config.getBool("Purchased"));
    EXPECT_FALSE(config.getBool("Completed"));
    EXPECT_TRUE(config.getBool("Multiplayer"));
}


TEST(ConfigTest, WritesFile) {
    StdConfigLoader configLoader;
    ConfigTable config;

    config.set("Game", "Snake");
    config.set("Fun", true);
    config.set("Highscore", 300);
    config.set("pi", 3.14);

    EXPECT_EQ(config.size(), 4);

    configLoader.write(config, "dump.cfg");

    ConfigTable loadedConfig = configLoader.load("dump.cfg");

    EXPECT_EQ(loadedConfig.get("Game"), "Snake");
    EXPECT_TRUE(loadedConfig.getBool("Fun"));
    EXPECT_EQ(loadedConfig.getInt("Highscore"), 300);
    EXPECT_FLOAT_EQ(loadedConfig.getFloat("pi"), 3.14);
}
