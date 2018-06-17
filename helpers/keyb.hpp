/* This source code file is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed along this file,
 * you can obtain one at https://opensource.org/licenses/MIT .
 */
#ifndef FUNCS_KEYB_HPP
#define FUNCS_KEYB_HPP
#include <SFML/Window.hpp>

bool keyb(const sf::Keyboard::Key& k) {
    return sf::Keyboard::isKeyPressed(k);
}

bool keyb(const sf::Keyboard::Key& x, const sf::Keyboard::Key& y) {
    return sf::Keyboard::isKeyPressed(x) && sf::Keyboard::isKeyPressed(y);
}

bool keyb(const sf::Keyboard::Key& x, const sf::Keyboard::Key& y, const sf::Keyboard::Key& z) {
    return sf::Keyboard::isKeyPressed(x) && sf::Keyboard::isKeyPressed(y) && sf::Keyboard::isKeyPressed(z);
}

#define   kA                  sf::Keyboard::A            ///< The A key
#define   kB                  sf::Keyboard::B            ///< The B key
#define   kC                  sf::Keyboard::C            ///< The C key
#define   kD                  sf::Keyboard::D            ///< The D key
#define   kE                  sf::Keyboard::E            ///< The E key
#define   kF                  sf::Keyboard::F            ///< The F key
#define   kG                  sf::Keyboard::G            ///< The G key
#define   kH                  sf::Keyboard::H            ///< The H key
#define   kI                  sf::Keyboard::I            ///< The I key
#define   kJ                  sf::Keyboard::J            ///< The J key
#define   kK                  sf::Keyboard::K            ///< The K key
#define   kL                  sf::Keyboard::L            ///< The L key
#define   kM                  sf::Keyboard::M            ///< The M key
#define   kN                  sf::Keyboard::N            ///< The N key
#define   kO                  sf::Keyboard::O            ///< The O key
#define   kP                  sf::Keyboard::P            ///< The P key
#define   kQ                  sf::Keyboard::Q            ///< The Q key
#define   kR                  sf::Keyboard::R            ///< The R key
#define   kS                  sf::Keyboard::S            ///< The S key
#define   kT                  sf::Keyboard::T            ///< The T key
#define   kU                  sf::Keyboard::U            ///< The U key
#define   kV                  sf::Keyboard::V            ///< The V key
#define   kW                  sf::Keyboard::W            ///< The W key
#define   kX                  sf::Keyboard::X            ///< The X key
#define   kY                  sf::Keyboard::Y            ///< The Y key
#define   kZ                  sf::Keyboard::Z            ///< The Z key
#define   kNum0               sf::Keyboard::Num0         ///< The 0 key
#define   kNum1               sf::Keyboard::Num1         ///< The 1 key
#define   kNum2               sf::Keyboard::Num2         ///< The 2 key
#define   kNum3               sf::Keyboard::Num3         ///< The 3 key
#define   kNum4               sf::Keyboard::Num4         ///< The 4 key
#define   kNum5               sf::Keyboard::Num5         ///< The 5 key
#define   kNum6               sf::Keyboard::Num6         ///< The 6 key
#define   kNum7               sf::Keyboard::Num7         ///< The 7 key
#define   kNum8               sf::Keyboard::Num8         ///< The 8 key
#define   kNum9               sf::Keyboard::Num9         ///< The 9 key
#define   kEscape             sf::Keyboard::Escape       ///< The Escape key
#define   kLControl           sf::Keyboard::LControl     ///< The left Control key
#define   kLShift             sf::Keyboard::LShift       ///< The left Shift key
#define   kLAlt               sf::Keyboard::LAlt         ///< The left Alt key
#define   kLSystem            sf::Keyboard::LSystem      ///< The left OS specific key: window (Windows and Linux) apple (MacOS X) ...
#define   kRControl           sf::Keyboard::RControl     ///< The right Control key
#define   kRShift             sf::Keyboard::RShift       ///< The right Shift key
#define   kRAlt               sf::Keyboard::RAlt         ///< The right Alt key
#define   kRSystem            sf::Keyboard::RSystem      ///< The right OS specific key: window (Windows and Linux) apple (MacOS X) ...
#define   kMenu               sf::Keyboard::Menu         ///< The Menu key
#define   kLBracket           sf::Keyboard::LBracket     ///< The [ key
#define   kRBracket           sf::Keyboard::RBracket     ///< The ] key
#define   kSemiColon          sf::Keyboard::SemiColon    ///< The ; key
#define   kComma              sf::Keyboard::Comma        ///< The  key
#define   kPeriod             sf::Keyboard::Period       ///< The . key
#define   kQuote              sf::Keyboard::Quote        ///< The ' key
#define   kSlash              sf::Keyboard::Slash        ///< The / key
#define   kBackSlash          sf::Keyboard::BackSlash    ///< The \ key
#define   kTilde              sf::Keyboard::Tilde        ///< The ~ key
#define   kEqual              sf::Keyboard::Equal        ///< The = key
#define   kDash               sf::Keyboard::Dash         ///< The - key
#define   kSpace              sf::Keyboard::Space        ///< The Space key
#define   kReturn             sf::Keyboard::Return       ///< The Return key
#define   kBackSpace          sf::Keyboard::BackSpace    ///< The Backspace key
#define   kTab                sf::Keyboard::Tab          ///< The Tabulation key
#define   kPageUp             sf::Keyboard::PageUp       ///< The Page up key
#define   kPageDown           sf::Keyboard::PageDown     ///< The Page down key
#define   kEnd                sf::Keyboard::End          ///< The End key
#define   kHome               sf::Keyboard::Home         ///< The Home key
#define   kInsert             sf::Keyboard::Insert       ///< The Insert key
#define   kDelete             sf::Keyboard::Delete       ///< The Delete key
#define   kAdd                sf::Keyboard::Add          ///< The + key
#define   kSubtract           sf::Keyboard::Subtract     ///< The - key
#define   kMultiply           sf::Keyboard::Multiply     ///< The * key
#define   kDivide             sf::Keyboard::Divide       ///< The / key
#define   kLeft               sf::Keyboard::Left         ///< Left arrow
#define   kRight              sf::Keyboard::Right        ///< Right arrow
#define   kUp                 sf::Keyboard::Up           ///< Up arrow
#define   kDown               sf::Keyboard::Down         ///< Down arrow
#define   kNumpad0            sf::Keyboard::Numpad0      ///< The numpad 0 key
#define   kNumpad1            sf::Keyboard::Numpad1      ///< The numpad 1 key
#define   kNumpad2            sf::Keyboard::Numpad2      ///< The numpad 2 key
#define   kNumpad3            sf::Keyboard::Numpad3      ///< The numpad 3 key
#define   kNumpad4            sf::Keyboard::Numpad4      ///< The numpad 4 key
#define   kNumpad5            sf::Keyboard::Numpad5      ///< The numpad 5 key
#define   kNumpad6            sf::Keyboard::Numpad6      ///< The numpad 6 key
#define   kNumpad7            sf::Keyboard::Numpad7      ///< The numpad 7 key
#define   kNumpad8            sf::Keyboard::Numpad8      ///< The numpad 8 key
#define   kNumpad9            sf::Keyboard::Numpad9      ///< The numpad 9 key
#define   kF1                 sf::Keyboard::F1           ///< The F1 key
#define   kF2                 sf::Keyboard::F2           ///< The F2 key
#define   kF3                 sf::Keyboard::F3           ///< The F3 key
#define   kF4                 sf::Keyboard::F4           ///< The F4 key
#define   kF5                 sf::Keyboard::F5           ///< The F5 key
#define   kF6                 sf::Keyboard::F6           ///< The F6 key
#define   kF7                 sf::Keyboard::F7           ///< The F7 key
#define   kF8                 sf::Keyboard::F8           ///< The F8 key
#define   kF9                 sf::Keyboard::F9           ///< The F9 key
#define   kF10                sf::Keyboard::F10          ///< The F10 key
#define   kF11                sf::Keyboard::F11          ///< The F11 key
#define   kF12                sf::Keyboard::F12          ///< The F12 key
#define   kF13                sf::Keyboard::F13          ///< The F13 key
#define   kF14                sf::Keyboard::F14          ///< The F14 key
#define   kF15                sf::Keyboard::F15          ///< The F15 key
#define   kPause              sf::Keyboard::Pause        ///< The Pause key

#endif // FUNCS_KEYB_HPP
