# 4253B Vision Visualizer

This project experiments with [LVGL](https://lvgl.io/) and the [VEX vision sensor](https://www.vexrobotics.com/276-4850.html). Debugging the vision sensor is difficult without an interface that can see what the vision sensor sees. Thus, I used LVGL to display "blobs" of color from the vision sensor. 

I also experimented with [gif-pros](https://github.com/theol0403/gif-pros), an open-source VEX library for displaying gifs. 

## Installation

This project uses [PROS](https://pros.cs.purdue.edu/). Download at your own risk. 

## Usage

There are 3 primary functions I used for LVGL (lines 79-135 in, ``main.cpp``). Much of the code is inspired by this [tutorial](https://github.com/Yessir120/4253B-Vision-Visualizer/blob/master/src/main.cpp), by Dennis Ranish from Vexmen team 81K. 

```cpp
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
```

To display feedback from the vision sensor, I continuously updated the dimensions and locations of a box in a loop. 

```cpp
while(true) {
    //background
    background = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(background, 0); //set button is to 0
    lv_obj_set_style(background, &backgroundStyle);
    lv_obj_set_size(background, LVGL_SCREEN_WIDTH, LVGL_SCREEN_HEIGHT); //set the button size
    lv_obj_align(background, NULL, LV_ALIGN_CENTER, 0, 0); //set the position to top mid

    pros::vision_object_s_t rtn = vision.get_by_size(0);

    myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(myButton, 0); //set button is to 0
    lv_obj_set_style(myButton, &style);

    double visionW = (double)rtn.width / (VISION_FOV_WIDTH/2) * (LVGL_SCREEN_WIDTH/2);
    double visionH = (double)rtn.height / (VISION_FOV_HEIGHT/2) * (LVGL_SCREEN_HEIGHT/2);
    lv_obj_set_size(myButton, visionW, visionH); //set the button size

    double visionX = (double)rtn.x_middle_coord / (VISION_FOV_WIDTH/2) * (LVGL_SCREEN_WIDTH/2);
    double visionY = (double)rtn.y_middle_coord / (VISION_FOV_HEIGHT/2) * (VISION_FOV_HEIGHT/2);
    lv_obj_align(myButton, NULL, LV_ALIGN_CENTER, visionX, visionY); //set the position to top mid

    pros::delay(40); // fat delay to minimize lag
}
```

## License
[MIT](https://choosealicense.com/licenses/mit/)
