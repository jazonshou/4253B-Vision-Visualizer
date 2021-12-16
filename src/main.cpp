#include "main.h"
#include <iostream>
#include <cstring>
#include <string.h>

#define LVGL_SCREEN_WIDTH 480
#define LVGL_SCREEN_HEIGHT 240

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
                     int id, const char * title)
{
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_free_num(btn, id);

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, title);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

    return btn;
}

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t tglBorder, lv_color_t textColor, lv_obj_t * btn)
{
    lv_style_t * btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 4);

    for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

    btnStyle[0].body.main_color = rel;
    btnStyle[0].body.grad_color = rel;
    btnStyle[0].text.color = textColor;

    btnStyle[1].body.main_color = pr;
    btnStyle[1].body.grad_color = pr;
    btnStyle[1].text.color = textColor;

    btnStyle[2].body.main_color = tglRel;
    btnStyle[2].body.grad_color = tglRel;
    btnStyle[2].body.border.width = 2;
    btnStyle[2].body.border.color = tglBorder;
    btnStyle[2].text.color = textColor;

    btnStyle[3].body.main_color = tglPr;
    btnStyle[3].body.grad_color = tglPr;
    btnStyle[3].body.border.width = 2;
    btnStyle[3].body.border.color = tglBorder;
    btnStyle[3].text.color = textColor;

    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);

    return btnStyle;
}

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn)
{
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);
}

lv_obj_t *myButton;
lv_style_t style;

lv_obj_t *background;
lv_style_t backgroundStyle;

pros::Vision vision(2, pros::E_VISION_ZERO_CENTER);
pros::vision_signature_s_t RED_SIG = pros::Vision::signature_from_utility(1, 9245, 9551, 9398, -249, -81, -165, 11.000, 0);
// sensor.set_signature(0, RED_SIG);

char thing[] = {'h', 'i'};
char *word = thing;

lv_color_t hi = LV_COLOR_MAKE(150, 0, 0);

void opcontrol() {
    Gif gif("/usd/crab-rave.gif", lv_scr_act());

	while (true) {
		pros::delay(20);
	}


    /*
    createBtn(myButton, 20, 20, 20, 20, 1, word);
    createBtnStyle(&style, ((lv_color_t) {{150, 0, 0, 0xff}}), bob, bob, bob, bob, bob, myButton);
    */

    // lv_style_copy(&style, &lv_style_plain);
    // style.body.main_color = LV_COLOR_MAKE(150, 0, 0);
    // style.body.grad_color = LV_COLOR_MAKE(150, 0, 0);
    // style.body.radius = 0;
    // style.text.color = LV_COLOR_MAKE(255, 255, 255);

    // lv_style_copy(&backgroundStyle, &lv_style_plain);
    // backgroundStyle.body.main_color = LV_COLOR_MAKE(0, 0, 0);
    // backgroundStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 0);
    // backgroundStyle.body.radius = 0;
    // backgroundStyle.text.color = LV_COLOR_MAKE(255, 255, 255);

    // while(true) {
    //     //background
    //     background = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    //     lv_obj_set_free_num(background, 0); //set button is to 0
    //     lv_obj_set_style(background, &backgroundStyle);
    //     lv_obj_set_size(background, LVGL_SCREEN_WIDTH, LVGL_SCREEN_HEIGHT); //set the button size
    //     lv_obj_align(background, NULL, LV_ALIGN_CENTER, 0, 0); //set the position to top mid

    //     pros::vision_object_s_t rtn = vision.get_by_size(0);

    //     myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    //     lv_obj_set_free_num(myButton, 0); //set button is to 0
    //     lv_obj_set_style(myButton, &style);

    //     double visionW = (double)rtn.width / (VISION_FOV_WIDTH/2) * (LVGL_SCREEN_WIDTH/2);
    //     double visionH = (double)rtn.height / (VISION_FOV_HEIGHT/2) * (LVGL_SCREEN_HEIGHT/2);
    //     lv_obj_set_size(myButton, visionW, visionH); //set the button size

    //     double visionX = (double)rtn.x_middle_coord / (VISION_FOV_WIDTH/2) * (LVGL_SCREEN_WIDTH/2);
    //     double visionY = (double)rtn.y_middle_coord / (VISION_FOV_HEIGHT/2) * (VISION_FOV_HEIGHT/2);
    //     lv_obj_align(myButton, NULL, LV_ALIGN_CENTER, visionX, visionY); //set the position to top mid

    //     pros::delay(40); // fat delay to minimize lag
    // }
}
