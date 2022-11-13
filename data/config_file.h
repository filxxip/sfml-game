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
constexpr char BOMBER_PLAYER[] = "../images/bomber_player.png";
constexpr char GAME_BACKGROUND[] = "../images/game_background.jpg";
constexpr char MENU_STYLE[] = "../themes/menu.style";
constexpr char MESSAGE_BOX_STYLE[] = "../themes/messagebox.style";
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
