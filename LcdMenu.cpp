#include "LcdMenu.h"

LcdMenu::LcdMenu (
        LCD* lcd,
        byte lcd_height,
        LineRenderer* renderers,
        byte number_of_renderers,
        byte settings) {
    _lcd_instance_pointer = lcd;
    _lcd_height = lcd_height;

    _renderers = renderers;
    _number_of_renderers = number_of_renderers;

    _active_item_index = 0;
    _render_from_index = 0;

    _settings = settings;
};

void LcdMenu::navigateUp () {
    if (_active_item_index == _render_from_index) {
        if (shouldScrollPerPage(_settings)) {
            if (shouldScrollInfinitly(_settings) && _render_from_index < _lcd_height) {
                _render_from_index = _number_of_renderers - (
                       shouldInterruptInfinity(_settings) ?
                            (_number_of_renderers % _lcd_height) :
                            (_lcd_height - _render_from_index));
            }
            else if (_render_from_index % _lcd_height != 0 || _render_from_index == 0) {
                _render_from_index = 0;
            }
            else {
                _render_from_index -= _lcd_height;
            }
        }
        else {
            if (shouldScrollInfinitly(_settings)) {
                if (_render_from_index == 0) {
                    _render_from_index = _number_of_renderers - (
                           shouldInterruptInfinity(_settings) ? _lcd_height : 1);
                }
                else {
                    _render_from_index--;
                }
            }
            else if (_render_from_index != 0) {
                _render_from_index--;
            }
        }
    }

    _active_item_index--;
    if (_active_item_index == 255) {
        if (shouldScrollInfinitly(_settings)) {
            _active_item_index = _number_of_renderers - 1;
        }
        else {
            _active_item_index++;
        }
    }
};

void LcdMenu::navigateDown () {
    byte bottom_index = _render_from_index + _lcd_height - 1;
    if (bottom_index >= _number_of_renderers - 1) {
        if (shouldInterruptInfinity(_settings)) {
            bottom_index = _number_of_renderers - 1;
        }
        else {
            bottom_index = bottom_index % _number_of_renderers;
        }
    }

    if (_active_item_index == bottom_index) {
        if (shouldScrollPerPage(_settings)) {
            _render_from_index += _lcd_height;
            if (shouldScrollInfinitly(_settings)) {
                if (_render_from_index >= _number_of_renderers) {
                    if (shouldInterruptInfinity(_settings)) {
                        _render_from_index = 0;
                    }
                    else {
                        _render_from_index -= _number_of_renderers;
                    }
                }
            }
            else if (_render_from_index >= _number_of_renderers) {
                _render_from_index = _number_of_renderers - (_number_of_renderers % _lcd_height);
            }
        }
        else {
            if (shouldScrollInfinitly(_settings)) {
                if (_render_from_index == _number_of_renderers - (
                       shouldInterruptInfinity(_settings) ?
                            _lcd_height :
                            1)) {
                    _render_from_index = 0;
                }
                else {
                    _render_from_index++;
                }
            }
            else if (_render_from_index != _number_of_renderers - _lcd_height) {
                _render_from_index++;
            }
        }
    }

    _active_item_index++;
    if (_active_item_index == _number_of_renderers) {
        if (shouldScrollInfinitly(_settings)) {
            _active_item_index = 0;
        }
        else {
            _active_item_index--;
        }
    }
};

void LcdMenu::render () {
    byte offset = 0;
    byte render_index = 0;
    do {
        render_index = _render_from_index + offset;
        if (shouldScrollInfinitly(_settings) && !(shouldInterruptInfinity(_settings))) {
            if (render_index >= _number_of_renderers) {
                render_index = render_index % _number_of_renderers;
            }
        }

        if (render_index == _number_of_renderers) {
            return;
        }

        _lcd_instance_pointer->setCursor(0, offset);
        _renderers[render_index](_lcd_instance_pointer, offset, render_index == _active_item_index);
        offset++;
    } while (offset < _lcd_height);
};

byte LcdMenu::getSelectedItemIndex () {
    return _active_item_index;
};
