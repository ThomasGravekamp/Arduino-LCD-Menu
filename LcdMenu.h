#ifndef __ARDUINO_LCD_MENU
#define __ARDUINO_LCD_MENU

#include "Arduino.h"
#include "LCD.h"

#define LCD_MENU_SCROLL_PER_ITEM      0x00
#define LCD_MENU_SCROLL_PER_PAGE      0x01
#define LCD_MENU_SCROLL_FINITE        0x00
#define LCD_MENU_SCROLL_INFINITE      0x02
#define LCD_MENU_INFINITE_CONTINUOUS  0x00
#define LCD_MENU_INFINITE_INTERRUPTED 0x04

#define shouldScrollPerPage(settings) (settings & LCD_MENU_SCROLL_PER_PAGE)
#define shouldScrollInfinitly(settings) (settings & LCD_MENU_SCROLL_INFINITE)
#define shouldInterruptInfinity(settings) (settings & LCD_MENU_INFINITE_INTERRUPTED)

typedef void (*LineRenderer)(LCD*, byte, bool);

class LcdMenu {
    public:
        LcdMenu(
            LCD* lcd,
            byte lcd_height,
            LineRenderer* renderers,
            byte number_of_renderers,
            byte settings);

        void navigateUp();
        void navigateDown();

        void render();

        byte getSelectedItemIndex();

    private:
        LCD* _lcd_instance_pointer;
        byte _lcd_height;

        LineRenderer* _renderers;
        byte _number_of_renderers;

        byte _active_item_index;
        byte _render_from_index;

        byte _settings;
};

#endif
