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
constexpr char MENU_STYLE[] = "../themes/menu.style";
constexpr char MESSAGE_BOX_STYLE[] = "../themes/messagebox.style";
} // namespace Paths

namespace RendererNames {
constexpr char BUTTON[] = "Button";
constexpr char LAYOUT[] = "Layout";
constexpr char MSGBOX[] = "ExitMessageBox";
constexpr char MSGBOX_BUTTON[] = "ExitMessageBoxButtons";
} // namespace RendererNames

namespace KeyboardData {
constexpr int THREAD_TIME = 2000;
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
constexpr int TEXT_SIZE = 18;
constexpr char EXIT_TITLE[] = "Exit Game";
constexpr char EXIT_CONTENT[] = "Are you sure the exit this game?";

} // namespace MessageBoxData