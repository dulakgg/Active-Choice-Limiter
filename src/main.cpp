#include <Geode/Geode.hpp>

#include <Geode/modify/MenuLayer.hpp>

#include <Geode/modify/LevelBrowserLayer.hpp>

#include <Geode/modify/LevelInfoLayer.hpp>

#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

static int getThatLevelYallWant() {
  return static_cast < int > (Mod::get() -> getSettingValue < int64_t > ("force-level-id"));
}

static void openSearchThingyForLevel() {
  auto theBestNameForAVariable = getThatLevelYallWant();
  if (theBestNameForAVariable <= 0) return;
  queueInMainThread([theBestNameForAVariable] {
    auto obj = GJSearchObject::create(SearchType::Type19, std::to_string(theBestNameForAVariable));
    auto scene = LevelBrowserLayer::scene(obj);
    CCDirector::sharedDirector() -> replaceScene(scene);
  });
}

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {
  bool init(GJSearchObject * obj) {
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0) {
      obj = GJSearchObject::create(SearchType::Type19, std::to_string(theBestNameForAVariable));
    }
    return LevelBrowserLayer::init(obj);
  }
};
class $modify(MyLevelInfoLayer, LevelInfoLayer) {
  bool init(GJGameLevel * level, bool challenge) {
    if (!LevelInfoLayer::init(level, challenge)) return false;
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0 && (!level || level -> m_levelID != theBestNameForAVariable)) {
      queueInMainThread([] {
        openSearchThingyForLevel();
      });
    }
    return true;
  }
};

class $modify(MyMenuLayer, MenuLayer) {
  void onPlay(CCObject * sender) {
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0) {
      openSearchThingyForLevel();
      return;
    }
    MenuLayer::onPlay(sender);
  }

  void onDaily(CCObject * sender) {
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0) {
      openSearchThingyForLevel();
      return;
    }
    MenuLayer::onDaily(sender);
  }
  void onMoreGames(CCObject * sender) {
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0) {
      openSearchThingyForLevel();
      return;
    }
    MenuLayer::onMoreGames(sender);
  }
};

class $modify(MyCreatorLayer, CreatorLayer) {
  void onDailyLevel(CCObject * sender) {
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0) {
      openSearchThingyForLevel();
      return;
    }
    CreatorLayer::onDailyLevel(sender);
  }
  void onEventLevel(CCObject * sender) {
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0) {
      openSearchThingyForLevel();
      return;
    }
    CreatorLayer::onEventLevel(sender);
  }
  void onGauntlets(CCObject * sender) {
    auto theBestNameForAVariable = getThatLevelYallWant();
    if (theBestNameForAVariable > 0) {
      openSearchThingyForLevel();
      return;
    }
    CreatorLayer::onGauntlets(sender);
  }
};
// now ain't that beautiful code <3