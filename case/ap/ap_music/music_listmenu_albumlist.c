/*******************************************************************************
 *                              US212A
 *                            Module: music ui
 *                 Copyright(c) 2003-2012 Actions Semiconductor,
 *                            All Rights Reserved.
 *
 * History:
 *      <author>    <time>           <version >             <desc>
 *     fiona.yang   2011-10-26          1.0              create this file
 *******************************************************************************/

#include "app_music.h"

#include "app_music_albumlist.h"

#include "app_music_menu_config.h"

album_brow_t g_album_list[PIC_ONE_SCREEN] _BANK_DATA_ATTR_;

/*! \brief 传给codec的图片window */
wregion_t region_in _BANK_DATA_ATTR_;

/*! \brief 实际解码用的图片window */
wregion_t region_out _BANK_DATA_ATTR_;

/*! \brief 定义九宫格图片的x,y起始坐标 */
const uint8 pic_start_x[] = { 2, 44, 86 };
const uint8 pic_start_y[] = { 18, 60, 102 };

/*! \brief 物理按键与按键事件的对应关系*/
const key_map_t preview_key_map_list[] =
{
    /*! next事件 */
    {{ KEY_NEXT, 0, KEY_TYPE_DOWN | KEY_TYPE_LONG | KEY_TYPE_HOLD }, EVENT_PICTURE_PREVIEW_MOVENEXT },
    /*! prev事件 */
    {{ KEY_PREV, 0, KEY_TYPE_DOWN | KEY_TYPE_LONG | KEY_TYPE_HOLD }, EVENT_PICTURE_PREVIEW_MOVEPREV },
    /*! 短按mode option事件 */
    {{ KEY_MODE, 0, KEY_TYPE_SHORT_UP }, EVENT_PICTURE_OPTION },
    /*! 长按mode返回事件 */
    {{ KEY_VOL, 0, KEY_TYPE_SHORT_UP }, EVENT_PICTURE_RETURN },
    /*! 短按play键事件*/
    {{ KEY_PLAY, 0, KEY_TYPE_SHORT_UP }, EVENT_DIRECTORY_ENTER_SON },
    /*! 结束标志 */
    {{ KEY_NULL, 0, KEY_TYPE_NULL }, MSG_NULL },
};

/******************************************************************************/
/*!
 * \par  Description:
 *	  获取一屏专辑项的文件名及当前专辑是否存在专辑图片
 * \param[in]   p_dir_control  文件浏览结构体指针
 * \param[out]  none
 * \return      none
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
void load_album_item_data(dir_control_t *p_dir_control)
{
    brow_decode_t decode_param;

    decode_param.num = (uint8)(p_dir_control->bottom - p_dir_control->top + 1);
    decode_param.option = 1;
    decode_param.top = p_dir_control->top + 1;

    fsel_browser_get_albums(&decode_param, g_album_list);
}

/******************************************************************************/
/*!
 * \par  Description:
 *	  设置预览模式窗位置
 * \param[in]   pregion  当前region
 * \param[in]   pic_number 当前文件序号
 * \param[out]  none
 * \return      none
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
void init_prev_view_window(wregion_t *pregion, uint16 pic_number)
{
    uint8 row_counter;
    uint8 colume_counter;

    uint8 pic_no = (uint8) pic_number % PIC_ONE_SCREEN;
    row_counter = pic_no / PIC_PER_ROW;
    colume_counter = pic_no % PIC_PER_COLUME;

    pregion->x = pic_start_x[colume_counter];
    pregion->y = pic_start_y[row_counter];
    pregion->w = PIC_PREV_VIEW_WIDTH;
    pregion->h = PIC_PREV_VIEW_HEIGHT;
    return;
}

/******************************************************************************/
/*!
 * \par  Description:
 *	  画预览图片的FRAME，实现清选中框或画选中框的效果
 * \param[in]   区域坐标region，颜色值color
 * \param[out]  none
 * \return      none
 * \retval      none
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
static void show_frame(wregion_t region, uint32 color)
{
    wregion_t frame_region;

    //画横向frame
    ui_set_backgd_color(color);
    frame_region.x = region.x - PIC_FRAME_HEIGHT;
    frame_region.y = region.y - PIC_FRAME_HEIGHT;
    frame_region.w = PIC_FRAME_WIDTH;
    frame_region.h = PIC_FRAME_HEIGHT;
    ui_clear_screen(&frame_region);
    frame_region.y = region.y + region.h;
    ui_clear_screen(&frame_region);

    //画纵向frame
    frame_region.x = region.x - PIC_FRAME_HEIGHT;
    frame_region.y = region.y - PIC_FRAME_HEIGHT;
    frame_region.w = PIC_FRAME_HEIGHT;
    frame_region.h = PIC_FRAME_WIDTH;
    ui_clear_screen(&frame_region);
    frame_region.x = region.x + region.w;
    ui_clear_screen(&frame_region);

    return;
}
/******************************************************************************/
/*!
 * \par  Description:
 *	  画激活项选中框，消隐非激活项选中框
 * \param[in]   old_active, active,
 * \param[out]
 * \return
 * \retval
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
void show_active_frame(uint16 old_active, uint16 active)
{
    DC dc_status;

    ui_get_DC_status(&dc_status);
    if (old_active != active)
    {
        init_prev_view_window(&region_in, old_active);
        show_frame(region_in, Color_BLACK_def);
    }
    //非激活项region坐标计算后，画激活项选中框
    init_prev_view_window(&region_in, active);
    show_frame(region_in, Color_WHITE_def);
    ui_set_pen_color(dc_status.pen_color);
    ui_set_backgd_color(dc_status.backgd_color);
}
/******************************************************************************/
/*!
 * \par  Description:
 *	  显示激活项文件名，如果为目录，显示目录名
 * \param[in]   none
 * \param[out]  none
 * \return      ui_result_e
 * \retval      not care
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
void pic_show_filename(uint8 *filename)
{
    ui_result_e ui_result;
    int8 language_id = UNICODEDATA;
    style_infor_t picture_style;
    textbox_private_t picture_textbox_param;

    if ((filename[0] != 0xff) && (filename[1] != 0xfe))
    {
        language_id = (int8) g_setting_comval.g_comval.language_id;
    }
    //显示文件名
    picture_style.type = UI_AP;
    picture_style.style_id = ALBUM_NAME_TEXTBOX;
    picture_textbox_param.lang_id = language_id;

    picture_textbox_param.str_id = -1;
    picture_textbox_param.str_value = filename;
    ui_result = (ui_result_e) ui_show_textbox(&picture_style, &picture_textbox_param, TEXTBOX_DRAW_NORMAL);

    //是否需要滚屏显示文件名
    if (ui_result == UI_NEED_SCROLL)
    {
        restart_app_timer(scroll_frush_id);
    }
    else
    {
        stop_app_timer(scroll_frush_id);
    }

    return;
}

/******************************************************************************/
/*!
 * \par  Description:
 *	  显示文件总数和激活项序号
 * \param[in]   active  激活项文件序号
 * \param[out]  none
 * \return      none
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
void show_active_num(uint16 active, uint8 mode)
{
    style_infor_t picture_style;
    numbox_private_t picture_numbox_param;

    picture_style.type = UI_AP;
    picture_style.style_id = TRACK_NUMBER_BOX;
    picture_numbox_param.total = dir_control.list_total;
    picture_numbox_param.value = active + 1;

    if (mode == TRUE)
    {
        mode = NUMBOX_DRAW_ALL;
    }
    else
    {
        mode = NUMBOX_DRAW_NUMBER;
    }
    //调用numbox显示 居中透明显示
    ui_show_numbox(&picture_style, &picture_numbox_param, mode);
}
/******************************************************************************/
/*!
 * \par  Description:
 *	  文件名滚动显示定时器服务函数
 * \param[in]   none
 * \param[out]  none
 * \return      none
 * \ingroup     pic_preview
 * \note
 * \li  由于文件名已经缓存到UI驱动的显示buffer，因此不需要传递任何参数
 *******************************************************************************/
void scroll_play_flag(void)
{
    ui_show_textbox(NULL, NULL, TEXTBOX_DRAW_SCROLL);
}

/******************************************************************************/
/*!
 * \par  Description:
 *	  GUI及系统消息处理函数
 * \param[in]   path_info 文件路径
 * \param[in]   p_dir_control 文件浏览结构体指针
 * \param[out]  none
 * \return      none
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
app_result_e pic_preview_deal_msg(file_path_info_t *path_info, dir_control_t *p_dir_control)
{
    bool bret;
    input_gui_msg_t ui_msg;
    private_msg_t pri_msg;
    msg_apps_type_e gui_event;
    app_result_e ui_result = RESULT_NULL;

    bret = get_gui_msg(&ui_msg);
    if (bret == TRUE)
    {
        if (com_key_mapping(&ui_msg, &gui_event, preview_key_map_list) == TRUE)
        {
            ui_result = pic_preview_proc_key_event(path_info, p_dir_control, gui_event);
        }
    }
    else
    {
        bret = get_app_msg(&pri_msg);
        if (bret == TRUE)
        {
            ui_result = music_message_deal(&pri_msg);
        }
    }
    return ui_result;
}

/******************************************************************************/
/*!
 * \par  Description:
 *	  显示一屏九宫格图片缩略图
 * \param[in]   p_dir_control 文件浏览结构体指针
 * \param[out]  none
 * \return      app_result_e 事件处理返回值
 * \ingroup     pic_preview
 * \note
 * \li   绘制缩略图时是否需要响应按键?
 *******************************************************************************/
app_result_e prev_view_one_screen(dir_control_t *p_dir_control)
{
    uint16 i;
    region_t region;
    uint16 top = p_dir_control->top;
    uint16 bottom = p_dir_control->bottom;
    uint16 active = p_dir_control->active;
    uint16 old_active = p_dir_control->old;
    uint8 list_no = (uint8)(active - top);

    uint8 *filename = g_album_list[list_no].name_buf;

    show_active_num(active, FALSE);

    if (active == old_active)
    {
        region.x = 0;
        region.y = 16;
        region.width = 128;
        region.height = 128;

        //清屏显示图片
        ui_clear_screen(&region);

        load_album_item_data(p_dir_control);

        for (i = top; i <= bottom; i++)
        {
            list_no = (uint8)(i - top);

            //设置对应文件预览窗口
            init_prev_view_window(&region_in, i);

            if (g_album_list[list_no].album_flag == 0)
            {
                ui_show_pic(ALBUM_NO, region_in.x, region_in.y);
            }
            else
            {
                pic_paint(list_no);
            }
            sys_os_time_dly(1);
        }

        //由于显示图片过程中使用了LCD_BUFFER空间，因此需要重新加载一屏数据
        load_album_item_data(p_dir_control);
    }

    pic_show_filename(filename);

    show_active_frame(old_active, active);

    return RESULT_NULL;
}
/******************************************************************************/
/*!
 * \par  Description:
 *    计算缩略图dir_control变量相关成员值
 * \param[in]    none
 * \param[out]   none
 * \return       none
 * \ingroup      pic_preview
 * \note
 *******************************************************************************/
void init_list_para(void)
{
    uint16 cur_group;
    dir_control.old = dir_control.active;
    cur_group = (dir_control.active / PIC_ONE_SCREEN);
    dir_control.top = cur_group * PIC_ONE_SCREEN;
    dir_control.bottom = dir_control.top + PIC_ONE_SCREEN - 1;
    if (dir_control.bottom > (dir_control.list_total - 1))
    {
        dir_control.bottom = (dir_control.list_total - 1);
    }

    pic_init_display_buffer();
}

/******************************************************************************/
/*!
 * \par  Description:
 *	  图片缩略图场景模块
 * \param[in]   void
 * \param[out]  none
 * \return      app_result_e 返回值
 * \ingroup     pic_preview
 * \note
 *******************************************************************************/
app_result_e pic_preview(file_path_info_t *path_info, dir_com_data_t *dir_com)
{

    bool need_draw_all = TRUE;
    bool need_draw = TRUE;
    bool is_scene_exit = FALSE;

    app_result_e ui_result = RESULT_NULL;

    dir_control.dir_disk = path_info->file_path.dirlocation.disk;

    //初始化该成员,防止路径记忆出错
    dir_control.one_page_count = 6;

    dir_control.dir_com = dir_com;

    dir_control.enter_dir = TRUE;

    //解码初始化
    ui_result = pic_decode_init(&dir_control, path_info);
    if (ui_result != RESULT_NULL)
    {
        is_scene_exit = TRUE;
    }

    while (!is_scene_exit)
    {
        if (need_draw_all == TRUE)
        {
            need_draw_all = FALSE;

            if (dir_control.enter_dir == TRUE)
            {
                dir_control.list_total = g_dir_browser.dir_total + g_dir_browser.file_total;
                if (dir_control.list_total == 0)
                {
                    gui_dialog_msg(DIALOG_MSG, DIALOG_INFOR_WAIT, S_NO_SONG);
                    is_scene_exit = TRUE;
                    ui_result = RESULT_PIC_RETURN;
                    continue;
                }

                //读取当前层次文件浏览路径记录
                read_history_item(g_dir_browser.layer_no, &dir_control);

                dir_control.enter_dir = FALSE;

                dir_control.old = dir_control.active = (dir_control.list_no - 1);
            }
            show_active_num(dir_control.active, TRUE);
            init_list_para();
            need_draw = TRUE;
        }

        if (need_draw == TRUE)
        {
            need_draw = FALSE;

            //需重绘预览界面
            prev_view_one_screen(&dir_control);
        }

        ui_result = pic_preview_deal_msg(path_info, &dir_control);

        switch (ui_result)
        {
            case RESULT_NULL:
            case RESULT_IGNORE:
            break;

            case RESULT_PIC_NEXTITEM:
            need_draw = TRUE;
            break;

            case RESULT_REDRAW:
            ui_clear_screen(NULL);
            case RESULT_PIC_NEXTSCREEN:
            need_draw_all = TRUE;
            break;

            default:
            is_scene_exit = TRUE;
            break;
        }
        sys_os_time_dly(1);
    }
    kill_app_timer(scroll_frush_id);
    scroll_frush_id = -1;

    if (ui_result == RESULT_PIC_RETURN)
    {
        ui_result = RESULT_LISTMENU_MENU;
    }
    //回写并释放空间
    write_history_item(0, &dir_control, TRUE);
    return ui_result;
}
