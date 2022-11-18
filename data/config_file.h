#pragma once

#include <TGUI/Vector2.hpp>

namespace WindowData {
constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;
constexpr char TITLE[] = "Bomberman";
} // namespace WindowData

namespace Paths {
constexpr char TEXTURE_PATH[] = "../images/texture.jpg";
constexpr char BOMBER_TITLE_PATH[] = "../images/bomber.png";
constexpr char BOMB_PATH[] = "../images/bomb.png";
constexpr char MYSTERY_BOMB_PATH[] = "../images/mystery_bomb.png";
constexpr char HEART_PANEL_PATH[] = "../images/downheartpanel.png";
constexpr char RED_HEART_PATH[] = "../images/red_heart.png";
constexpr char GREY_HEART_PATH[] = "../images/grey_heart.png";
constexpr char CLICK_BOMB_PATH[] = "../images/click_bomb.png";
constexpr char HEART_BOMB_PATH[] = "../images/heart_bomb.png";
constexpr char BOMBER_PLAYER[] = "../images/bomber_player.png";
constexpr char GAME_BACKGROUND[] = "../images/game_background.jpg";
constexpr char MENU_STYLE[] = "../themes/menu.style";
constexpr char MESSAGE_BOX_STYLE[] = "../themes/messagebox.style";
constexpr char BOX_PATH[] = "../images/box.png";
constexpr char STONE[] = "../images/stone.png";
} // namespace Paths

namespace RendererNames {
constexpr char DEFAULT_BUTTON[] = "DefaultButton";
constexpr char ACTIVE_BUTTON[] = "ActiveButton";
constexpr char LAYOUT[] = "Layout";
} // namespace RendererNames

namespace KeyboardData {
constexpr int THREAD_TIME = 300;
}

namespace Json {
constexpr char RESUME[] = "../data/json/resume_messagebox.json";
constexpr char NEW_GAME[] = "../data/json/new_game_messagebox.json";
constexpr char EXIT_GAME[] = "../data/json/exit_game_messagebox.json";
constexpr char EXIT_APP[] = "../data/json/exit_messagebox.json";
} // namespace Json

namespace JsonNames {
constexpr char SIZE_WIDTH_[] = "size_width";
constexpr char SIZE_HEIGHT[] = "size_height";
constexpr char TITLE[] = "title";
constexpr char CONTENT[] = "content";
constexpr char MSGBOX_NAME[] = "messagebox_render_name";
constexpr char MSGBOX_BUTTON_NAME[] = "button_render_name";
} // namespace JsonNames

namespace MainMenuData {
constexpr int PICTURE_X_MOVEMENT = 0;
constexpr int LAYOUT_X_MOVEMENT = 0;
constexpr int PICTURE_Y_MOVEMENT = -200;
constexpr int LAYOUT_Y_MOVEMENT = 100;
constexpr tgui::Vector2f LAYOUT_SIZE{400, 300};
constexpr tgui::Vector2f PICTURE_SIZE{500, 150};
constexpr int FREE_SPACE_RATIO = 1;
constexpr int BUTTON_RATIO = 2;
namespace ButtonsText {
constexpr char EXIT[] = "Exit Game";
constexpr char LOAD[] = "Load Game";
constexpr char NEW[] = "New Game";
constexpr char RESULT[] = "See best results";
constexpr char OPTIONS[] = "Options";
} // namespace ButtonsText
} // namespace MainMenuData

namespace PanelData {
constexpr int HEART_X_POSITION = 100;
constexpr int BOMB_SUP_POS = 150;
constexpr int HEARTS_SIZE = 30;
constexpr int HEARTS_MARGIN = 15;
constexpr int HEARTS_SPACING = 10;
constexpr int BOMB_SIZE = 50;
constexpr int DEFAULT_HEART_NUMBER = 3;
constexpr int DELTA_PANEL_Y_POSITION = 70;
} // namespace PanelData

namespace BoxData {
constexpr int SIZE = 35;
constexpr int DEFAULT_BOX_SPACES = 15;
constexpr int DELTA_PANEL_Y_POSITION = PanelData::DELTA_PANEL_Y_POSITION + 20;
} // namespace BoxData

namespace BombData {
constexpr int STANDARD_LIVE_TIME = 3000;
constexpr int MINIMUM_LIVE_TIME = 1000;
constexpr int MAXIMUM_RANDOM_LIVE_TIME = 10000;
constexpr int SNAPSHOTTING_START = 1000;
constexpr int SNAPSHOTTING_PERIOD = 100;
constexpr int SIZE = BoxData::SIZE - 10;
} // namespace BombData

namespace PlayerData {
constexpr int SIZE = BoxData::SIZE - 7;
}
