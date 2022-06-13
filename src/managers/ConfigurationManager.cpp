#include <managers/ConfigurationManager.h>
#include <managers/LanguageManager.h>
#include <extensions/StringExtensions.h>
#include <persistence/JsonLoader.h>
#include <services/DiscordService.h>

#include <iostream>

Json::Value ConfigurationManager::configurations = NULL;

void ConfigurationManager::load()
{
    JsonLoader::load(JsonLoader::getApplicationFolder() + "/config.json", configurations);
}

std::string ConfigurationManager::getHost()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "HOST");

    if (value == NULL)
    {
        std::cout << "Unable to find configuration file. Using default (host = '127.0.0.1')" << std::endl;
        return "127.0.0.1";
    }

    return value.asString();
}

unsigned int ConfigurationManager::getPort()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "PORT");

    if (value == NULL)
    {
        std::cout << "Unable to find configuration file. Using default (port = 52424)" << std::endl;
        return 52424;
    }

    return value.asUInt();
}

bool ConfigurationManager::showAegis()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "DISPLAY_OPTIONS:AEGIS");

    if (value == NULL)
        return true;

    return value.asBool();
}

bool ConfigurationManager::showAghanim()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "DISPLAY_OPTIONS:AGHANIM");

    if (value == NULL)
        return true;

    return value.asBool();
}

bool ConfigurationManager::showGoldAndLastHit()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "DISPLAY_OPTIONS:GOLD_AND_LAST_HIT");

    if (value == NULL)
        return true;

    return value.asBool();
}

bool ConfigurationManager::showKillDeathAssist()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "DISPLAY_OPTIONS:KILL_DEATH_ASSIST");

    if (value == NULL)
    {
        return true;
    }

    return value.asBool();
}

bool ConfigurationManager::showSmoke()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "DISPLAY_OPTIONS:SMOKE");

    if (value == NULL)
        return true;

    return value.asBool();
}

std::string ConfigurationManager::getLocale()
{
    if (configurations == NULL)
        load();

    Json::Value value = JsonLoader::getNode(configurations, "LOCALE");

    std::string lang("System");

    if (value != NULL)
        lang = value.asString();

    lang = StringExtensions::toLowerCase(lang);

    //Update Settings
    if (lang == "system" && configurations != NULL)
    {
        lang = LanguageManager::getSystemLanguage();
        configurations["LOCALE"] = lang; 
    }

    return lang;
}