#include "includes.h"

boolean COND_hide()  // hide a menu element
{
  return false;  // hidden
}

void lcdml_menu_clear()
{
}

void lcdml_menu_display()
{
  // for first test set font here
  u8g.setFont(_LCDML_DISP_font);
  //u8g.setColorIndex(1); // Instructs the display to draw with a pixel on.

  // declaration of some variables
  // ***************
  // content variable
  char content_text[_LCDML_DISP_cols];  // save the content text of every menu element
  // menu element object
  LCDMenuLib2_menu *tmp;
  // some limit values
  uint8_t i = LCDML.MENU_getScroll();
  uint8_t maxi = _LCDML_DISP_rows + i;
  uint8_t n = 0;

   // init vars
  uint8_t n_max             = (LCDML.MENU_getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.MENU_getChilds());
  uint8_t scrollbar_min     = 0;
  uint8_t scrollbar_max     = LCDML.MENU_getChilds();
  uint8_t scrollbar_cur_pos = LCDML.MENU_getCursorPosAbs();
  uint8_t scroll_pos        = ((1.*n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos);


 // for first test set font here
  u8g.setFont(_LCDML_DISP_font);
  u8g.setColorIndex(1); // Instructs the display to draw with a pixel on.

  // generate content
  u8g.firstPage();
  do {
    n = 0;
    i = LCDML.MENU_getScroll();
    // update content
    // ***************

    // clear menu
    // ***************

    // check if this element has children
    if ((tmp = LCDML.MENU_getDisplayedObj()) != NULL)
    {
      // loop to display lines
      do
      {
        // check if a menu element has a condition and if the condition be true
        if (tmp->checkCondition())
        {
          // check the type off a menu element
          if(tmp->checkType_menu() == true)
          {
            // display normal content
            LCDML_getContent(content_text, tmp->getID());
            u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind, _LCDML_DISP_box_y0 + _LCDML_DISP_font_h * (n + 1), content_text);
          }
          else
          {
            if(tmp->checkType_dynParam()) {
              tmp->callback(n);
            }
          }
          // increment some values
          i++;
          n++;
        }
      // try to go to the next sibling and check the number of displayed rows
      } while (((tmp = tmp->getSibling(1)) != NULL) && (i < maxi));
    }

    // set cursor
    u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_cur_space_before, _LCDML_DISP_box_y0 + _LCDML_DISP_font_h * (LCDML.MENU_getCursorPos() + 1),  _LCDML_DISP_cursor_char);

    if(_LCDML_DISP_draw_frame == 1) {
       u8g.drawFrame(_LCDML_DISP_box_x0, _LCDML_DISP_box_y0, (_LCDML_DISP_box_x1-_LCDML_DISP_box_x0), (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0));
    }

    // display scrollbar when more content as rows available and with > 2
    if (scrollbar_max > n_max && _LCDML_DISP_scrollbar_w > 2)
    {
      // set frame for scrollbar
      u8g.drawFrame(_LCDML_DISP_box_x1 - _LCDML_DISP_scrollbar_w, _LCDML_DISP_box_y0, _LCDML_DISP_scrollbar_w, _LCDML_DISP_box_y1-_LCDML_DISP_box_y0);

      // calculate scrollbar length
      uint8_t scrollbar_block_length = scrollbar_max - n_max;
      scrollbar_block_length = (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0) / (scrollbar_block_length + _LCDML_DISP_rows);

      //set scrollbar
      if (scrollbar_cur_pos == 0) {                                   // top position     (min)
        u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y0 + 1                                                     , (_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
      }
      else if (scrollbar_cur_pos == (scrollbar_max-1)) {            // bottom position  (max)
        u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y1 - scrollbar_block_length                                , (_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
      }
      else {                                                                // between top and bottom
        u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y0 + (scrollbar_block_length * scrollbar_cur_pos + 1),(_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
      }
    }
  } while ( u8g.nextPage() );
}

// TEAM LOGO ARRAY
static const unsigned char Project_Logo_bits[] PROGMEM = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xe0, 0x03, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x01, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf8, 0x07, 0x30, 0x04, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x18, 0x06, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
   0x5f, 0x0e, 0x02, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf0, 0xdf, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xdf, 0x1c, 0x0c, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x5e, 0x70, 0x08, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf6, 0x0c, 0x03, 0x08, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x0c, 0x06, 0x08, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x19,
   0x1c, 0x8c, 0x0d, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x14, 0x1c, 0x18, 0x07, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x16, 0x38, 0x08, 0x02, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x12,
   0x30, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x13, 0x00, 0x98, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x11, 0x00, 0xf0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86, 0x11,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc3, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x41, 0x10, 0x00, 0xc0, 0x01, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x18,
   0xc0, 0x63, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x60, 0x20, 0x08, 0x60, 0x26, 0x02, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x08, 0x20, 0x64, 0x03, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xb0, 0xff, 0x0b,
   0x20, 0xc4, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x90, 0xff, 0x0b, 0x60, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xff, 0x0b, 0xc0, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xff, 0x0b,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0xe8, 0xff, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xff, 0x0b, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xff, 0x0b,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0xe8, 0xff, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xff, 0x05, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xff, 0x05,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0xd8, 0xff, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0xb0, 0xff, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x7e, 0x03,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0xc0, 0xbd, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0xc3, 0x61, 0x60, 0x00, 0x1e, 0x63, 0x3e, 0x78, 0x60, 0x18, 0x0e, 0xf8,
   0x30, 0xe6, 0x83, 0xc7, 0xe3, 0x63, 0x60, 0x00, 0x3f, 0x63, 0x7e, 0xfc,
   0xe0, 0x18, 0x1f, 0xf8, 0x31, 0xe6, 0xc7, 0xcf, 0x73, 0x67, 0x60, 0x00,
   0x33, 0x63, 0xe6, 0xcc, 0xe0, 0x98, 0x3b, 0x98, 0x33, 0x66, 0xce, 0xcc,
   0x33, 0x66, 0x60, 0x00, 0x03, 0x63, 0xc6, 0x0c, 0xe0, 0x99, 0x31, 0x18,
   0x33, 0x66, 0xcc, 0xc0, 0x33, 0x66, 0x60, 0x00, 0x07, 0x63, 0xc6, 0x1c,
   0xe0, 0x99, 0x31, 0x18, 0x33, 0x66, 0xcc, 0xc1, 0x33, 0x66, 0x60, 0x00,
   0x0e, 0x63, 0xc6, 0x38, 0x60, 0x9b, 0x31, 0x18, 0x33, 0x66, 0x8c, 0xc3,
   0x33, 0x66, 0x60, 0x00, 0x1c, 0x63, 0xc6, 0x70, 0x60, 0x9b, 0x31, 0x18,
   0x33, 0x66, 0x0c, 0xc7, 0xf3, 0x67, 0x60, 0x00, 0x38, 0x63, 0xc6, 0xe0,
   0x60, 0x9e, 0x31, 0x18, 0x33, 0x66, 0x0c, 0xce, 0xf3, 0x67, 0x60, 0x00,
   0x30, 0x63, 0xc6, 0xc0, 0x60, 0x9e, 0x31, 0x18, 0x33, 0x66, 0x0c, 0xcc,
   0x33, 0x66, 0x60, 0x00, 0x33, 0x77, 0xe6, 0xcc, 0x60, 0x9c, 0x3b, 0x98,
   0x73, 0x67, 0xce, 0xcc, 0x33, 0xe6, 0xe7, 0x07, 0x3f, 0x3e, 0x7e, 0xfc,
   0x60, 0x1c, 0x1f, 0xf8, 0xe1, 0xe3, 0xc7, 0xcf, 0x33, 0xe6, 0xe7, 0x07,
   0x1e, 0x1c, 0x3e, 0x78, 0x60, 0x18, 0x0e, 0xf8, 0xc0, 0xe1, 0x83, 0xc7,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff };

void display_logo(void)
{
  u8g.drawXBMP( 0, 0, 128, 64, Project_Logo_bits);
}
