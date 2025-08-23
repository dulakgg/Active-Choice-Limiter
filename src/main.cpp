#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>

#include <Geode/modify/LevelBrowserLayer.hpp>

#include <Geode/modify/SecretLayer2.hpp>

#include <Geode/modify/LevelInfoLayer.hpp>

#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

static int getLevelIDFromSettings() {
  return static_cast < int > (Mod::get() -> getSettingValue < int64_t > ("force-level-id"));
}

static void searchForLevelIDFromModSettings() {
  auto forcedLevelID = getLevelIDFromSettings();
  if (forcedLevelID < 128) return;
  queueInMainThread([forcedLevelID] {
    auto obj = GJSearchObject::create(SearchType::Type19, geode::utils::numToString(forcedLevelID));
    auto scene = LevelBrowserLayer::scene(obj);
    CCDirector::sharedDirector() -> replaceScene(scene);
  });
}

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {
  bool init(GJSearchObject * obj) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      obj = GJSearchObject::create(SearchType::Type19, geode::utils::numToString(forcedLevelID));
    }
    return LevelBrowserLayer::init(obj);
  }
};
class $modify(MyLevelInfoLayer, LevelInfoLayer) {
  bool init(GJGameLevel * level, bool challenge) {
    if (!LevelInfoLayer::init(level, challenge)) return false;
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127 && (!level || level -> m_levelID != forcedLevelID)) {
      queueInMainThread([] {
        searchForLevelIDFromModSettings();
      });
    }
    return true;
  }
};
class $modify(MySecretLayer2, SecretLayer2) {
  void onSecretLevel(cocos2d::CCObject* sender) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      searchForLevelIDFromModSettings();
      return;
    }
    SecretLayer2::onSecretLevel(sender);
  }
}
class $modify(MyMenuLayer, MenuLayer) {
  void onPlay(CCObject * sender) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      searchForLevelIDFromModSettings();
      return;
    }
    MenuLayer::onPlay(sender);
  }

  void onDaily(CCObject * sender) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      searchForLevelIDFromModSettings();
      return;
    }
    MenuLayer::onDaily(sender);
  }
  void onMoreGames(CCObject * sender) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      searchForLevelIDFromModSettings();
      return;
    }
    MenuLayer::onMoreGames(sender);
  }
};

class $modify(MyCreatorLayer, CreatorLayer) {
  void onDailyLevel(CCObject * sender) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      searchForLevelIDFromModSettings();
      return;
    }
    CreatorLayer::onDailyLevel(sender);
  }
  void onEventLevel(CCObject * sender) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      searchForLevelIDFromModSettings();
      return;
    }
    CreatorLayer::onEventLevel(sender);
  }
  void onGauntlets(CCObject * sender) {
    auto forcedLevelID = getLevelIDFromSettings();
    if (forcedLevelID > 127) {
      searchForLevelIDFromModSettings();
      return;
    }
    CreatorLayer::onGauntlets(sender);
  }
};
// now ain't that beautiful code <3
