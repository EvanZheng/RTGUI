/*
 * �����嵥��edit�ؼ���ʾ
 *
 * ������ӻ���conatiner�Ͻ���edit�ؼ�����ʾ
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/edit.h>

/* ����������ʾedit�ؼ�����ͼ */
rtgui_container_t *demo_view_edit(void)
{
//  rtgui_rect_t rect, textbox_rect;
    rtgui_container_t *container;
    struct rtgui_edit *edit;

    /* �ȴ���һ����ʾ�õ���ͼ */
    container = demo_view("Edit View");

    edit = rtgui_edit_create(container, 10, 35, 220, 200);
    rtgui_edit_set_text(edit,
                        "Edit beta v0.1\n"
                        "Hello RT-Thread\n"
                        "this's edit demo\n"
                        "rtgui_edit_create\n"
                        "rtgui_edit_append_line\n"
                        "rtgui_edit_insert_line\n"
                        "rtgui_edit_delete_line\n"
                        "rtgui_edit_connect_line\n"
                        "a\n"
                        "b\n"
                        "c\n"
                        "d\n"
                        "1234567890\n");

    return container;
}
