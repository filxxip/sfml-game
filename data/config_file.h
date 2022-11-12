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
constexpr char MSGBOX[] = "ExitMessageBox";
constexpr char EMPTY_MSGBOX[] = "EmptyMessageBox";
constexpr char MSGBOX_BUTTON[] = "ExitMessageBoxButtons";
constexpr char EMPTY_MSGBOX_BUTTON[] = "EmptyMessageBoxButtons";
} // namespace RendererNames

namespace KeyboardData {
constexpr int THREAD_TIME = 300;
}

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

namespace MessageBoxData {
constexpr tgui::Vector2f BASE_SIZE{250, 110};
constexpr tgui::Vector2f EMPTY_SIZE{140, 60};
constexpr int TEXT_SIZE = 18;
constexpr char EXIT_TITLE[] = "Exit App";
constexpr char NEW_GAME_TITLE[] = "Starting New Game";
constexpr char EXIT_GAME_TITLE[] = "Exit Game";
constexpr char RESUME_GAME_TITLE[] = "Resume Game";
constexpr char EMPTY_CONTENT[] = "";
constexpr char EMPTY_TITLE[] = "";
constexpr char EXIT_CONTENT[] = "Are you sure the exit this app?";
constexpr char NEW_GAME_CONTENT[] = "Are you sure to start new game?";
constexpr char EXIT_GAME_CONTENT[] = "Are you sure to finish this game?";

} // namespace MessageBoxData