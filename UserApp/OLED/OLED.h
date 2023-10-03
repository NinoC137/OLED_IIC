#ifndef OLED_H
#define OLED_H

#include <stdint.h>
#include "main.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// the I2C address of oled
#define OLED_I2C_ADDRESS    0x78

//the resolution of oled   128*64
#define MAX_COLUMN      128
#define MAX_ROW         64

#define X_WIDTH         MAX_COLUMN
#define Y_WIDTH         MAX_ROW

#define IIC_CMD 0x00
#define IIC_DAT 0x40

#define OLED_CMD_SCROLL_H_RIGHT  0x26
#define OLED_CMD_SCROLL_H_LEFT   0x27
#define OLED_CMD_CONTINUOUS_SCROLL_V_AND_H_RIGHT 0x29
#define OLED_CMD_CONTINUOUS_SCROLL_V_AND_H_LEFT 0x2A
#define OLED_CMD_DEACTIVATE_SCROLL 0x2E
#define OLED_CMD_ACTIVATE_SCROLL 0x2F
#define OLED_CMD_SET_VERTICAL_SCROLL_AREA 0xA3

#define CHAR_SIZE_WIDTH 6
#define CHAR_SIZE_HIGHT 12

typedef enum
{
    PEN_CLEAR = 0x00,
    PEN_WRITE = 0x01,
    PEN_INVERSION= 0x02,
}pen_typedef;

/*
 * 关于SSD1306内存分区:
 *  纵向:
 *      Page 0 ~ 8
 *  横向
 *      Seg 0 ~ 128
 *  每一个Page中对应一个8bit数据位, 用于存放纵向的显示像素位
 *      例如(0x00)是全部熄灭, (0x0F)是点亮下半Page
 * */


/**
  * @brief          initialize the oled device
  * @param[in]      none
  * @retval         none
  */
/**
  * @brief          初始化OLED模块，
  * @param[in]      none
  * @retval         none
  */
void OLED_init(void);

uint32_t OLED_Pow(uint8_t m, uint8_t n);
uint8_t check_num_len(uint32_t num);
void OLED_show_num(uint8_t x, uint8_t y, uint32_t num, uint8_t mode, uint8_t len);
void OLED_show_floatNum(uint8_t x, uint8_t y, float num, uint8_t mode);

void OLED_scrollingSetup(uint8_t scoll_mode,uint8_t start_page,uint8_t end_page,uint8_t frequency);
void OLED_scrollStart();
void OLED_scrollStop();
/**
  * @brief          turn on OLED display
  * @param[in]      none
  * @retval         none
  */
void OLED_display_on(void);

/**
  * @brief          turn off OLED display
  * @param[in]      none
  * @retval         none
  */
void OLED_display_off(void);

/**
  * @brief          operate the graphic ram(size: 128*8 char)
  * @param[in]      pen: the type of operate.
                    PEN_CLEAR: set ram to 0x00
                    PEN_WRITE: set ram to 0xff
                    PEN_INVERSION: bit inversion
  * @retval         none
  */
void OLED_operate_gram(pen_typedef pen);


/**
  * @brief          cursor set to (x,y) point
  * @param[in]      x:X-axis, from 0 to 127
  * @param[in]      y:Y-axis, from 0 to 7
  * @retval         none
  */
void OLED_set_pos(uint8_t x, uint8_t y);


/**
  * @brief          draw one bit of graphic raw, operate one point of screan(128*64)
  * @param[in]      x: x-axis, [0, X_WIDTH-1]
  * @param[in]      y: y-axis, [0, Y_WIDTH-1]
  * @param[in]      pen: type of operation,
                        PEN_CLEAR: set (x,y) to 0
                        PEN_WRITE: set (x,y) to 1
                        PEN_INVERSION: (x,y) value inversion
  * @retval         none
  */
void OLED_draw_point(uint8_t x, uint8_t y, pen_typedef pen);

/**
  * @brief          draw one part of screan(128*64)
  * @param[in]      x1: x-axis, [0, X_WIDTH-1]
  * @param[in]      y1: y-axis, [0, Y_WIDTH-1]
  * @param[in]      x2: x-axis, [0, X_WIDTH-1]
  * @param[in]      y2: y-axis, [0, Y_WIDTH-1]
  * @param[in]      pen: type of operation,
                        PEN_CLEAR: set (x,y) to 0
                        PEN_WRITE: set (x,y) to 1
                        PEN_INVERSION: (x,y) value inversion
  * @retval         none
  */
void OLED_Full_area(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, pen_typedef pen);

/**
  * @brief          draw a line from (x1, y1) to (x2, y2)
  * @param[in]      x1: the start point of line
  * @param[in]      y1: the start point of line
  * @param[in]      x2: the end point of line
  * @param[in]      y2: the end point of line
  * @param[in]      pen: type of operation,PEN_CLEAR,PEN_WRITE,PEN_INVERSION.
  * @retval         none
  */
void OLED_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, pen_typedef pen);


/**
  * @brief          show a character
  * @param[in]      row: start row of character
  * @param[in]      col: start column of character
  * @param[in]      chr: the character ready to show
  * @retval         none
  */
void OLED_show_char(uint8_t row, uint8_t col, uint8_t chr);

/**
  * @brief          show a character string
  * @param[in]      row: row of character string begin
  * @param[in]      col: column of character string begin
  * @param[in]      chr: the pointer to character string
  * @retval         none
  */
void OLED_show_string(uint8_t row, uint8_t col, uint8_t *chr);

/**
  * @brief          formatted output in oled 128*64
  * @param[in]      row: row of character string begin, 0 <= row <= 4;
  * @param[in]      col: column of character string begin, 0 <= col <= 20;
  * @param          *fmt: the pointer to format character string
  * @note           if the character length is more than one row at a time, the extra characters will be truncated
  * @retval         none
  */
void OLED_printf(uint8_t row, uint8_t col, const char *fmt,...);

/**
  * @brief          send the data of gram to oled sreen
  * @param[in]      none
  * @retval         none
  */
void OLED_refresh_gram(void);


//Animation demo -- Nino
void animateLineDemo1();
void animatePointDemo2();
void animatePseudo3DDemo();
void animateStringDemo();

typedef struct Ball_t{
    uint8_t x;
    uint8_t y;
} Ball_t;

void animateBallAnimation(int frameRate, int duration);

#endif

