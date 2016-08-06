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
#include "D_SDLConfigLoader.h"

using namespace Diamond;

class TestConfigLoader : public StdConfigLoader {
public:
    enum TestStatus {
        TESTERROR,
        TESTPARSED,
        TESTCOMMENT,
        TESTEMPTY
    };

    void testParse(const std::string &line,
                   const std::string &expKey,
                   const std::string &expVal,
                   TestStatus expStatus) {
        std::string key, val;
        Status status = parseLine(line, key, val);

        EXPECT_EQ(expKey, key);
        EXPECT_EQ(expVal, val);

        switch (expStatus) {
            case TESTERROR:
                EXPECT_EQ(status, ERROR);
                break;
            case TESTPARSED:
                EXPECT_EQ(status, PARSED);
                break;
            case TESTCOMMENT:
                EXPECT_EQ(status, COMMENT);
                break;
            case TESTEMPTY:
                EXPECT_EQ(status, EMPTY);
                break;
            default:
                break;
        }
    }
};


static ConfigTable testLoadsFile(ConfigLoader &configLoader) {
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

    return config;
}


TEST(ConfigTest, ParsesNormal) {
    TestConfigLoader configLoader;

    configLoader.testParse("Boss:Ahnaf", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse("MyPowerLevel:9001", "MyPowerLevel", "9001",
                           TestConfigLoader::TestStatus::TESTPARSED);

}

TEST(ConfigTest, ParsesSpaceRight) {
    TestConfigLoader configLoader;

    configLoader.testParse("Boss: Ahnaf", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse("MyPowerLevel: 9001", "MyPowerLevel", "9001",
                           TestConfigLoader::TestStatus::TESTPARSED);

}

TEST(ConfigTest, ParsesSpaceLeft) {
    TestConfigLoader configLoader;

    configLoader.testParse("Boss :Ahnaf", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse("MyPowerLevel :9001", "MyPowerLevel", "9001",
                           TestConfigLoader::TestStatus::TESTPARSED);

}

TEST(ConfigTest, ParsesSpaceBoth) {
    TestConfigLoader configLoader;

    configLoader.testParse("Boss : Ahnaf", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse("MyPowerLevel : 9001", "MyPowerLevel", "9001",
                           TestConfigLoader::TestStatus::TESTPARSED);

}

TEST(ConfigTest, ParsesSpacesGalore) {
    TestConfigLoader configLoader;

    configLoader.testParse("Boss : Ahnaf ", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse(" Boss : Ahnaf ", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);
}


TEST(ConfigTest, InvalidParses) {
    TestConfigLoader configLoader;

    configLoader.testParse("iamerror", "", "",
                           TestConfigLoader::TestStatus::TESTERROR);

    configLoader.testParse(":wut", "", "",
                           TestConfigLoader::TestStatus::TESTERROR);

    configLoader.testParse("wut:", "", "",
                           TestConfigLoader::TestStatus::TESTERROR);
}


TEST(ConfigTest, EmptySkips) {
    TestConfigLoader configLoader;

    configLoader.testParse("", "", "",
                           TestConfigLoader::TestStatus::TESTEMPTY);
}


TEST(ConfigTest, CommentBeginSkips) {
    TestConfigLoader configLoader;

    configLoader.testParse("#", "", "",
                           TestConfigLoader::TestStatus::TESTCOMMENT);

    configLoader.testParse("# ", "", "",
                           TestConfigLoader::TestStatus::TESTCOMMENT);

    configLoader.testParse(" #This is a comment", "", "",
                           TestConfigLoader::TestStatus::TESTCOMMENT);

    configLoader.testParse(" # This is a comment", "", "",
                           TestConfigLoader::TestStatus::TESTCOMMENT);

    configLoader.testParse("# This is a comment", "", "",
                           TestConfigLoader::TestStatus::TESTCOMMENT);

    configLoader.testParse("#  This is a comment", "", "",
                           TestConfigLoader::TestStatus::TESTCOMMENT);
}

TEST(ConfigTest, CommentEndSkips) {
    TestConfigLoader configLoader;

    configLoader.testParse("Boss:Ahnaf # That's me", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse("MyPowerLevel:9001#I'm powerful", "MyPowerLevel", "9001",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse("Boss:Ahnaf# That's me", "Boss", "Ahnaf",
                           TestConfigLoader::TestStatus::TESTPARSED);

    configLoader.testParse("MyPowerLevel:9001 #I'm powerful", "MyPowerLevel", "9001",
                           TestConfigLoader::TestStatus::TESTPARSED);
}


TEST(StdConfigTest, LoadsFile) {
    StdConfigLoader configLoader;
    testLoadsFile(configLoader);
}


TEST(StdConfigTest, WritesFile) {
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


TEST(SDLConfigTest, LoadsFile) {
    SDLConfigLoader configLoader;
    testLoadsFile(configLoader);
}
