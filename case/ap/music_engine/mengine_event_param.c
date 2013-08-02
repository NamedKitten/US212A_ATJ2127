/*******************************************************************************
 *                              US212A
 *                            Module: music engine
 *                 Copyright(c) 2003-2012 Actions Semiconductor,
 *                            All Rights Reserved.
 *
 * History:
 *      <author>    <time>           <version >             <desc>
 *      fiona.yang  2011-09-07        1.0              create this file
 *******************************************************************************/

#include "app_mengine.h"

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_start_ab(void* msg_ptr)
 * \����ab����,�ȴ�����a��
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_start_ab(void* msg_ptr)
{
    mengine_status_t *eg_status = &mengine_info.eg_status;

    if (eg_status->play_status == PlaySta)
    {
        eg_status->ab_status = PlayAB_A;//�ȴ�����A��

        eg_status->play_status = PlayAB;

        //���ø���������������
        //mmm_mp_cmd(mp_handle, MMM_MP_AB_COUNT, (unsigned int)(g_eg_cfg_p->replaytimes));

        //���ø��������������  10msΪ��λ
        //mmm_mp_cmd(mp_handle, MMM_MP_AB_WAIT_TIME, (unsigned int) (g_eg_cfg_p->replaygap * 100));

    }

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_set_apoint(void* msg_ptr)
 * \����a��
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_set_apoint(void* msg_ptr)
{
    mengine_status_t *eg_status = &mengine_info.eg_status;

    eg_status->ab_status = PlayAB_B;//�ȴ�����B��

    eg_status->play_status = PlayAB;

    mmm_mp_cmd(mp_handle, MMM_MP_SET_A, (unsigned int) NULL);//��������A������

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_set_bpoint(void* msg_ptr)
 * \����b��,��ʼ����
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_set_bpoint(void* msg_ptr)
{
    mengine_status_t *eg_status = &mengine_info.eg_status;

    eg_status->ab_status = PlayAB_Do;//��ʼab����

    eg_status->play_status = PlayAB;//���ò���״̬ΪAB����

    mmm_mp_cmd(mp_handle, MMM_MP_SET_B, (unsigned int) NULL);//��������B������

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_clear_ab(void* msg_ptr)
 * \���ab����
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_clear_ab(void* msg_ptr)
{
    mengine_status_t *eg_status = &mengine_info.eg_status;

    eg_status->ab_status = PlayAB_Null;//���AB����״̬

    eg_status->play_status = PlaySta;//�ָ���������״̬

    mmm_mp_cmd(mp_handle, MMM_MP_CLEAR_AB, (unsigned int) NULL);//�������AB��������

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_set_section_mode(void* msg_ptr)
 * \����audible���½�ģʽ/����ģʽ
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   msg_ptr->msg.content.addr //����eq��Ϣ��ָ��
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_set_section_mode(void* msg_ptr)
{
    //��������ָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;

    uint8 last_mode = mengine_info.eg_config.section_mod;

    //����Ϣָ��ָ�������copy���������
    libc_memcpy(&mengine_info.eg_config.section_mod, data_ptr->msg.content.addr, sizeof(mmm_mp_eq_info_t));
    //���޸�
    mmm_mp_cmd(mp_handle, MMM_MP_SET_CHAPTER, (unsigned int) mengine_info.eg_config.section_mod);

    //���ļ�ģʽ�л����½�ģʽ
    if ((last_mode == SWITCH_TITLE) && (mengine_info.eg_config.section_mod == SWITCH_SECTION))
    {
        _check_audible_chapter();
        if (mengine_info.eg_status.play_status == PlaySta)
        {
            _set_chapter_timer();
        }
        mengine_info.eg_playinfo.cur_file_switch |= 0x02;
    }

    //���½�ģʽ�л����ļ�ģʽ
    if ((mengine_info.eg_config.section_mod == SWITCH_TITLE) && (last_mode == SWITCH_SECTION))
    {
        //mengine_info.eg_config.location.plist_location.file_total = audbile_tracks.locat_total;
        //mengine_info.eg_config.location.plist_location.file_num = audbile_tracks.loact_num;
        _clr_chapter_timer();
    }

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_get_bkinfo(void* msg_ptr)
 * \��ȡ��ǰ���ֶϵ���Ϣ
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   msg_ptr->msg.content.addr //����ѭ����ʽ��ָ��
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_get_bkinfo(void* msg_ptr)
{
    //��Ϣָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;

    mengine_status_t *eg_status = &mengine_info.eg_status;
    mengine_config_t *eg_cfg = &mengine_info.eg_config;
    //���ڲ���
    if (eg_status->play_status == PlaySta)
    {
        //��ȡ�ϵ�
        mmm_mp_cmd(mp_handle, MMM_MP_GET_BREAK_POINT, (unsigned int) &(eg_cfg->bk_infor));
    }
    //copy��ǰ����ʱ��ͱ����ʵ���Ϣָ��ָ���������
    libc_memcpy(data_ptr->reply->content, &(eg_cfg->bk_infor), sizeof(mmm_mp_bp_info_t));

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_play_bookmark(void* msg_ptr)
 * \������ǩ����
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_play_bookmark(void* msg_ptr)
{
    bool ret_vals;

    //��Ϣָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;

    //mengine_status_t *eg_status = &mengine_info.eg_status;
    mengine_config_t *eg_cfg = &mengine_info.eg_config;

    //void * data_ptr = msg_ptr->msg.content.addr;//�����ǩ�ϵ������ָ��

    //��ǰ�ǲ���״̬,��ֹͣ����

    ret_vals = _stop(STOP_PAUSE);//��ͣ����,���ڲ���֤�ǲ���״̬��ֹͣ
    if (ret_vals == FALSE)
    {
        goto msg_end;
    }

    //����ϵ�,������_stop֮��,��Ϊ_stop�л��ȡ�ϵ㣬����_stop֮ǰ�ϵ�ᱻ����
    libc_memcpy(&eg_cfg->bk_infor, data_ptr->msg.content.addr, sizeof(mmm_mp_bp_info_t));

    //���¿�ʼ����, �����ļ�
    //ret_vals = _set_file();
    //if (ret_vals == FALSE)
    //{
    //    goto msg_end;
    //}

    ret_vals = _play(PLAY_RESUME);//����

    msg_end:
    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_set_playmode(void* msg_ptr)
 * \����ѭ��ģʽ
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   msg_ptr->msg.content.addr //����ѭ����ʽ��ָ��
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_set_playmode(void* msg_ptr)
{
    //����ѭ��ģʽ��ָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;
    uint8 cur_mode;
    uint8 old_mode;
    mengine_status_t *eg_status = &mengine_info.eg_status;

    cur_mode = *(uint8*) (data_ptr->msg.content.addr);//��ȡ��ǰѭ��ģʽ
    old_mode = mengine_info.eg_config.repeat_mode;

    mengine_info.eg_config.shuffle_flag = (uint8)(cur_mode & 0xf0);//����shuffleģʽ
    mengine_info.eg_config.repeat_mode = (cur_mode & 0x0f);//����ѭ��ģʽ

    if ((eg_status->play_status == StopSta) || (eg_status->play_status == PauseSta))
    {
        fsel_set_mode(cur_mode);//����ѭ��ģʽ
    }
    else
    {
        //ֻ�е�ǰģʽ����Ϊ���ģʽ��֮ǰģʽ��Ϊ���ģʽʱ�Ž�������
        if ((mengine_info.eg_config.repeat_mode == FSEL_MODE_INTRO) && (old_mode != FSEL_MODE_INTRO))
        {
            mmm_mp_status_t mmm_status;
            mmm_mp_cmd(mp_handle, MMM_MP_GET_STATUS, (unsigned int) &mmm_status);
            g_intro_start = (uint32) mmm_status.cur_time;
        }
    }

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_set_ab_count(void* msg_ptr)
 * \����ab��������
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   msg_ptr->msg.content.addr //����ab����������ָ��
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_set_ab_count(void* msg_ptr)
{
    //���ø���������ָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;

    uint16 rep_count;

    //��ȡ��ǰ��������
    rep_count = *(uint16*) (data_ptr->msg.content.addr);

    //mengine_info.eg_config.replaytimes = rep_count;//���渴������

    //���ø���������������
    mmm_mp_cmd(mp_handle, MMM_MP_AB_COUNT, (unsigned int) rep_count);

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_set_ab_count(void* msg_ptr)
 * \����ab�������ʱ��
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   msg_ptr->msg.content.addr //����ab���������ָ��
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_set_ab_gap(void* msg_ptr)
{
    //���ø��������ָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;
    uint8 ab_gap;

    ab_gap = *(uint8*) (data_ptr->msg.content.addr);//��ȡ��ǰ�������

    //mengine_info.eg_config.replaygap = ab_gap;///���渴��������������

    //���ø��������������  10msΪ��λ
    mmm_mp_cmd(mp_handle, MMM_MP_AB_WAIT_TIME, (unsigned int) ab_gap * 100);

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_clear_error(void* msg_ptr)
 * \��������
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_clear_error(void* msg_ptr)
{
    mengine_status_t *eg_status = &mengine_info.eg_status;

    eg_status->err_status = EG_ERR_NONE;//��������

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \void change_locat_deal(void)
 * \�ļ�·���޸ĵĴ���
 * \param[in]    para1
 * \param[in]    none:
 * \param[out]   none
 * \return       the result
 * \ingroup      mengine_control.c
 * \note
 */
/*******************************************************************************/
bool change_locat_deal(void)
{
    bool ret_val;

    //����ָ��
    mengine_config_t *eg_cfg = &mengine_info.eg_config;

    if (g_path_type != eg_cfg->fsel_type)
    {
        fsel_exit();
        ret_val = mengine_file_init();//���³�ʼ��
    }
    else
    {
        ret_val = fsel_set_location(&(eg_cfg->location.plist_location), eg_cfg->fsel_type);
        if (ret_val == FALSE)
        {
            fsel_exit();
            ret_val = mengine_file_init();//���³�ʼ��
        }
    }
    g_change_path_flag = 0;

    return ret_val;

}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_musui_delete_file(void* msg_ptr)
 * \ɾ����ǰ���ŵ��ļ�
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_musui_delete_file(void* msg_ptr)
{
    bool is_playing;
    bool ret_vals;
    //bool switch_ret;

    plist_location_t* cur_locat_ptr = (plist_location_t*) &(g_eg_cfg_p->location.plist_location);

    //��ǰ����״̬
    if (g_eg_status_p->play_status == PlaySta)
    {
        is_playing = TRUE;
    }
    else
    {
        is_playing = FALSE;
    }
    ret_vals = _stop(STOP_NORMAL);//ֹͣ����
    if (ret_vals == FALSE)
    {
        goto msg_end;
    }

    cur_locat_ptr->file_num--;

    cur_locat_ptr->file_total--;

    //����ɾ����ǰ�ļ���ʶ
    g_del_curfile = 1;

    if (g_change_path_flag == 1)
    {
        ret_vals = change_locat_deal();
    }

    //����ϵ�
    libc_memset(&(g_eg_cfg_p->bk_infor), 0, sizeof(mmm_mp_bp_info_t));

    msg_end:
    //���سɹ�
    mengine_reply_msg(msg_ptr, ret_vals);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_other_delete_file(void* msg_ptr)
 * \ɾ��������ļ�
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_other_delete_file(void* msg_ptr)
{
    bool ret_vals;

    //��Ϣָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;

    //Ҫɾ�����ļ���Ϣָ��
    file_path_info_t* del_file_path = (file_path_info_t *) (data_ptr->msg.content.addr);

    //��ǰ���ڲ��ŵ��ļ�ָ��
    file_location_t* cur_locat_ptr = (file_location_t*) &(g_eg_cfg_p->location.dirlocation);

    uint32 del_clustno = del_file_path->file_path.dirlocation.cluster_no;//ɾ���ļ���Ŀ¼�����ڵĴغ�

    uint32 del_direntry = del_file_path->file_path.dirlocation.dir_entry;//ɾ���ļ���Ŀ¼�������ڴغ��ڵ�ƫ��

    //�ж��Ƿ���ɾ����ǰ�ļ����������ֹͣ����
    if ((del_clustno == cur_locat_ptr->cluster_no) && (del_direntry == cur_locat_ptr->dir_entry))
    {
        ret_vals = _stop(STOP_NORMAL);//ֹͣ����

        cur_locat_ptr->file_num--;

        cur_locat_ptr->file_total--;

        //����ɾ����ǰ�ļ���ʶ
        g_del_curfile = 1;

        if (g_change_path_flag == 1)
        {
            ret_vals = change_locat_deal();
        }

        //����ϵ�
        libc_memset(&(g_eg_cfg_p->bk_infor), 0, sizeof(mmm_mp_bp_info_t));
    }
    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_del_favorite_deal(void* msg_ptr)
 * \ɾ����ǰ���ŵ��ղؼ��е��ļ�
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_del_favorite_deal(void* msg_ptr)
{
    //ɾ���ļ���ŵ�ָ��
    private_msg_t* data_ptr = (private_msg_t*) msg_ptr;
    //ɾ���ļ����
    uint16 del_num;

    //��ǰ���ڲ��ŵ��ļ�ָ��
    flist_location_t* cur_locat_ptr = (flist_location_t*) &(mengine_info.eg_config.location.flist_location);

    del_num = *(uint16*) (data_ptr->msg.content.addr);//��ȡ��ǰɾ���ļ����

    if (cur_locat_ptr->file_num >= del_num)
    {
        cur_locat_ptr->file_num--;
    }
    cur_locat_ptr->file_total--;
    //ɾ���ļ�
    g_del_curfile = 1;

    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \app_result_e mengine_add_favorite_deal(void* msg_ptr)
 * \���ӵ�ǰ���ŵ��ղؼ��е��ļ�
 * \param[in]    msg_ptr��Ϣָ��  para1
 * \param[in]    private_msg_t
 *               typedef struct
 *               {
 *                 unsigned char sync;		//ͬ����־��1B
 *                 sem_id_t sem_id; 		  //�ź���ID��1B
 *                 msg_apps_t msg;		    //��Ϣ���ݣ�6B
 *               } private_msg_t;
 *               typedef struct
 *               {
 *                 msg_apps_type_e  type;	//��Ϣ���ͣ�2B
 *                 union
 *                 {
 *	                 unsigned char data[4];
 *                   unsigned char *addr;
 *                 }content;					//��Ϣ���ݻ����ַ������Ϣ�Լ�Լ����4B
 *               } msg_apps_t;//˽����Ϣ���е���Ϣ�ṹ��

 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNORE ����
 * \retval       ......
 * \ingroup      mengine_event.c
 * \note
 */
/*******************************************************************************/
app_result_e mengine_add_favorite_deal(void* msg_ptr)
{
    //��ǰ���ڲ��ŵ��ļ�ָ��
    flist_location_t* cur_locat_ptr = (flist_location_t*) &(mengine_info.eg_config.location.flist_location);

    cur_locat_ptr->file_total++;
    //���سɹ�
    mengine_reply_msg(msg_ptr, TRUE);

    return RESULT_IGNORE;
}

/******************************************************************************/
/*!
 * \par  Description:
 * \int _error_timeout_handle(void* param)
 * \��̨music����ʱ�����ļ��Զ��л���һ������
 * \param[in]    param  para1
 * \param[out]   none
 * \return       int the result
 * \retval       RESULT_IGNOR ����
 * \retval
 * \ingroup      mengine_control.c
 * \note
 * \li
 */
/*******************************************************************************/
void _error_timeout_handle(void)
{
    //mengine_config_t *cfg_ptr = &mengine_info.eg_config;
    //mengine_status_t *status = &mengine_info.eg_status;
    uint8 loop_mode;
    uint16 loopcnt;
    bool ret_val;

    //codec��enhanced���ù�ϵ�����ȹرս����м�����ٸ���ѭ��ģʽ
    _stop(STOP_NORMAL);

    //��ʱ����ѭ��ģʽΪ����ѭ��
    loop_mode = g_eg_cfg_p->shuffle_flag;//ѭ��ģʽshuffle
    loop_mode |= FSEL_MODE_LOOPALL;
    fsel_set_mode(loop_mode);

    loopcnt = fsel_get_total();//��ȡ��ǰģʽ���ļ�����

    //ѭ������,ֱ���ҵ��ɲ����ļ�
    while (loopcnt > 0)
    {
        loopcnt--;
        ret_val = mengine_file_switch(STOP_NORMAL, NORMAL_SWITCH_NEXT, PLAY_NORMAL);
        if (ret_val == SWITCH_NO_ERR)
        {
            break;
        }
        else if (ret_val == SWITCH_ERR_PLAY)
        {
            //���ʱ����δ���ţ�������ų����������CLEAR_FILE����ر��ļ����
            mmm_mp_cmd(mp_handle, MMM_MP_CLEAR_FILE, (unsigned int) NULL);
        }
        else
        {
            ;//nothing
        }

        sys_os_time_dly(g_delay_time);
    }

    if (loopcnt == 0)
    {
        //δ�ҵ���Ч���Բ��ŵĸ���
        g_eg_cfg_p->location.dirlocation.file_total = 0;
    }

    //�ָ�Ĭ�ϵ�ѭ��ģʽ
    loop_mode |= (uint8) g_eg_cfg_p->repeat_mode;
    fsel_set_mode(loop_mode);
}