#ifndef CPPURSES_PAINTER_DETAIL_NCURSES_PAINT_ENGINE_HPP
#define CPPURSES_PAINTER_DETAIL_NCURSES_PAINT_ENGINE_HPP
#include <cstddef>

/* Paint_engine Requires:
 *   void put_glyph(const Glyph& g);
 *   void put(std::size_t x, std::size_t y, const Glyph& g) {
 *   void move_cursor(std::size_t x, std::size_t y);
 *   void show_cursor(bool show = true);
 *   void hide_cursor(bool hide = true);
 *   void refresh();
 */

namespace cppurses {
struct Glyph;
namespace detail {

/// Provides access to basic painting functionality, using ncurses internally.
class NCurses_paint_engine {
   public:
    /// Initializes the terminal screen for painting.
    NCurses_paint_engine();

    /// Restores the terminal screen to the original state, before program run.
    ~NCurses_paint_engine();

    NCurses_paint_engine(const NCurses_paint_engine&) = delete;
    NCurses_paint_engine(NCurses_paint_engine&&) = default;
    NCurses_paint_engine& operator=(const NCurses_paint_engine&) = delete;
    NCurses_paint_engine& operator=(NCurses_paint_engine&&) = default;

    /// Places a Glyph \p g on the screen at the current cursor position.
    void put_glyph(const Glyph& g);

    /// Places a Glyph \p g at coordinates \p x , \p y. (0,0) is top left.
    void put(std::size_t x, std::size_t y, const Glyph& g) {
        this->move_cursor(x, y);
        this->put_glyph(g);
    }  // namespace detail

    /// Moves the cursor to point \p x , \p y on screen. (0,0) is top left.
    void move_cursor(std::size_t x, std::size_t y);

    /// Turns the cursor display on.
    void show_cursor(bool show = true);

    /// Turns the cursor display off.
    void hide_cursor(bool hide = true) { this->show_cursor(!hide); }

    /// Flushes all of the changes made by this class to the screen.
    void refresh();

   private:
    /// Registers a handler for the window resize signal from the kernel.
    void setup_sigwinch();

    /// paints a character to the screen and waits for SLOW_PAINT time.
    void paint_temporary(char display);
};

}  // namespace detail
}  // namespace cppurses
#endif  // CPPURSES_PAINTER_DETAIL_NCURSES_PAINT_ENGINE_HPP
