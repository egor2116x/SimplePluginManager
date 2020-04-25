#include <iostream>
#include "gtest/gtest.h"
#include "../PluginManager/PluginManager.h"

TEST(PluginManagerV1Test, loadPluginsIfValidPluginPath)
{
    PluginManager_v1 pluginManager;
    std::wstring path = GetExecAppPath();
    EXPECT_TRUE(pluginManager.LoadPlugins(path));
}

TEST(PluginManagerV1Test, loadPluginsIfIncorrectPluginPath)
{
    PluginManager_v1 pluginManager;
    EXPECT_FALSE(pluginManager.LoadPlugins(L".\\"));
}

TEST(PluginManagerV1Test, initPluginsSuccess)
{
    PluginManager_v1 pluginManager;
    std::wstring path = GetExecAppPath();
    ASSERT_TRUE(pluginManager.LoadPlugins(path));
    EXPECT_TRUE(pluginManager.InitPlugins());
}

TEST(PluginManagerV1Test, initPluginsFailedIfNotLoaded)
{
    PluginManager_v1 pluginManager;
    EXPECT_FALSE(pluginManager.InitPlugins());
}

TEST(PluginManagerV1Test, runPluginsSuccess)
{
    PluginManager_v1 pluginManager;
    std::wstring path = GetExecAppPath();
    ASSERT_TRUE(pluginManager.LoadPlugins(path));
    ASSERT_TRUE(pluginManager.InitPlugins());
    EXPECT_TRUE(pluginManager.RunPlugins());
}

TEST(PluginManagerV1Test, runPluginsFailedifNotLoaded)
{
    PluginManager_v1 pluginManager;
    std::wstring path = GetExecAppPath();
    EXPECT_FALSE(pluginManager.RunPlugins());
}

TEST(PluginManagerV1Test, freePlugins)
{
    PluginManager_v1 pluginManager;
    std::wstring path = GetExecAppPath();
    ASSERT_TRUE(pluginManager.LoadPlugins(path));
    EXPECT_TRUE(pluginManager.FreePlugins());
}

TEST(PluginManagerV1Test, getVersionSuccess)
{
    PluginManager_v1 pluginManager;
    EXPECT_TRUE(pluginManager.GetVersion() != 0);
}

TEST(CommonTest, getExecAppPath)
{
    std::wstring result = GetExecAppPath();
    EXPECT_TRUE(!result.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

