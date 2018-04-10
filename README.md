# LCD Menu

This is small and simple library for rendering a menu on an LCD.

This library should work with any Arduino-compatible board. Tested with an Arduino Uno clone.

## How to use

Include the header files for the [New LiquidCrystal library](https://bitbucket.org/fmalpartida/new-liquidcrystal/overview). Create an instance of the right LCD driver object. Refer to the [documentation](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home) of the New LiquidCrystal library on how to do this.

Include the header file and create an instance of the `LcdMenu` object. Create a render function for each line you want to display in your menu.

The following example will initialise an instance of the LCD menu and then scroll through all the set menu items with a 200 millisecond interval.

```
LiquidCrystal_I2C lcd(LCD_ADDR, 2, 1, 0, 4, 5, 6, 7);
LCD* lcd_p = &lcd;

void menu_item_1 (LCD* lcd, byte line, boolean is_active) {
  lcd->print(is_active ? "> " : "  ");
  lcd->print("item 1");
}

void menu_item_2 (LCD* lcd, byte line, boolean is_active) {
  lcd->print(is_active ? "> " : "  ");
  lcd->print("item 2");
}

void menu_item_3 (LCD* lcd, byte line, boolean is_active) {
  lcd->print(is_active ? "> " : "  ");
  lcd->print("item 3");
}

void menu_item_4 (LCD* lcd, byte line, boolean is_active) {
  lcd->print(is_active ? "> " : "  ");
  lcd->print("item 4");
}

void menu_item_5 (LCD* lcd, byte line, boolean is_active) {
  lcd->print(is_active ? "> " : "  ");
  lcd->print("item 5");
}

void menu_item_6 (LCD* lcd, byte line, boolean is_active) {
  lcd->print(is_active ? "> " : "  ");
  lcd->print("item 6");
}

LineRenderer line_renderers[6] = {
  menu_item_1,
  menu_item_2,
  menu_item_3,
  menu_item_4,
  menu_item_5,
  menu_item_6
};

LcdMenu menu(
  lcd_p,
  4,
  line_renderers,
  6,
  LCD_MENU_SCROLL_PER_ITEM |
  LCD_MENU_SCROLL_INFINITE |
  LCD_MENU_INFINITE_CONTINUOUS);

setup () {
  // Configure the LCD
  lcd_p->begin(LCD_WIDTH, LCD_HEIGHT);
  lcd_p->setBacklightPin(3, POSITIVE);
  lcd_p->setBacklightPin(HIGH);
}

byte screen_index = 0;

loop () {
  lcd_state_manager.navigateDown();

  lcd_p->clear();
  lcd_state_manager.render();

  delay(200);
}
```

## API

### `void LineRenderer(LCD* lcd, byte line_index, bool is_active)` function typedef

The renderers passed to the LcdMenu object should accept a pointer to the LCD object, a byte containing the position of this menu item on the display and boolean which specifies if this item is selected.

The `line_index` argument can be used when you want to use the `setCursor()` function of the LCD object. The `is_active` argument can be used to determine if there should be some sort of arrow or other indicator rendered when this item is active.

| Argument | Type | Description |
| -------- | :--: | ----------- |
| lcd        | LCD* | A pointer to the LCD object. |
| line_index | byte | The index of the line being rendered. |
| is_active  | bool | True if this item is selected. False if this item is not selected. |

### `LcdMenu(LCD* lcd, byte lcd_height, LineRenderer* renderers, byte number_of_renderers, byte settings)` constructor

Initialises the `LcdMenu` object. Note: the array of renderers cannot be changed after initialisation.

```
LcdMenu menu(lcd_p,
  4,
  line_renderers,
  6,
  LCD_MENU_SCROLL_PER_ITEM |
  LCD_MENU_SCROLL_INFINITE |
  LCD_MENU_INFINITE_CONTINUOUS);
```

These values can be set for the settings argument:

| Option |  |  |
| --- | --- | --- |
| Scroll per ...    | Item: `LCD_MENU_SCROLL_PER_ITEM` | Page: `LCD_MENU_SCROLL_PER_PAGE` |
| Scroll (in)finite | Finite: `LCD_MENU_SCROLL_FINITE` | Infinite: `LCD_MENU_SCROLL_INFINITE` |
| Infinite mode     | Continuous: `LCD_MENU_INFINITE_CONTINUOUS` | Interrupted: `LCD_MENU_INFINITE_INTERRUPTED` |

Chose one value from each row and "or" them together like this:

```
// Default, the infinite mode doesn't do anything when not scrolling infinitly, so omit it.
LCD_MENU_SCROLL_PER_ITEM | LCD_MENU_SCROLL_FINITE

// Scroll per page, inifinitly and jump to the next page when going past the end of the renderers array.
LCD_MENU_SCROLL_PER_PAGE | LCD_MENU_SCROLL_INFINITE | LCD_MENU_INFINITE_INTERRUPTED
```

| Argument | Type | Description |
| -------- | :--: | ----------- |
| lcd                 | LCD*          | A pointer to the LCD object. |
| lcd_height          | byte          | The height of the used LCD. |
| renderers           | LineRenderer* | An array of LineRenderer functions. |
| number_of_renderers | byte          | The number of renderers. |
| settings            | byte          | A byte containing the settings for this LcdMenu. |

### `void navigateUp()` method

Moves the selection one item up. When scrolling is set to finite, calling this method hsa no effect when the first item is already selected. Call this method when, for example, you pressed an "up" button.

```
menu.navigateUp();
```

### `void navigateDown()` method

Moves the selection one item down. When scrolling is set to finite, calling this method has no effect when the last item is already selected. Call this method whem, for example, you pressed an "down" button.

```
menu.navigteDown();
```

### `void render()` method

Renders the menu. This method should be called after changing the selection. When you fail to do this, changed made in the selected item will not be reflected by the rendered menu.

```
menu.render();
```

### `byte getSelectedItemIndex()` method

Returns the index of the selected item. Use this to determine what to do when, for example, you press an "enter" button.

```
byte selectedIndex = menu.getSelectedItemIndex();
```
