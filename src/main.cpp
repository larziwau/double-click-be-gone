#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <chrono>

using namespace geode::prelude;

auto sinceFirstClick = std::chrono::steady_clock::now();
auto interval = Mod::get()->getSettingValue<int64_t>("delay");
bool firstClick = false;

// yoinked from click sounds
bool isLessThanNMillis(auto time) {
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - time)
		.count() < interval;
}


class $modify(PlayerObject) {

public:	
	bool pushButton(PlayerButton p0) {
		if (!Mod::get()->getSettingValue<bool>("disable")) {		
			if (PlayerObject::m_isSecondPlayer) {
				interval = 0;
				// i absolutely DON'T know how to fix dual mode i'm sorry
			}
			else {
				interval = Mod::get()->getSettingValue<int64_t>("delay");
			}
			if (p0 == PlayerButton::Jump) {
				if (!firstClick) {
					firstClick = true;
					sinceFirstClick = std::chrono::steady_clock::now();
				} else {
					firstClick = false;
					if (isLessThanNMillis(sinceFirstClick)) {
						return false;
					}
				}
			}
		}
		return PlayerObject::pushButton(p0);
	}
};
