/*
 * �����嵥��edit�ؼ���ʾ
 *
 * ������ӻ���conatiner�Ͻ���edit�ؼ�����ʾ
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/edit.h>
#include <rtgui/widgets/button.h>

void demo_edit_readin_file(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_button_t *button;
	struct rtgui_edit *edit;
	const char* filename = "/test_readin.txt";
	int fd;
	
	RT_ASSERT(object != RT_NULL);
	button = RTGUI_BUTTON(object);
	/* ȡ��editָ�� */
	edit = RTGUI_EDIT( RTGUI_WIDGET(button)->user_data );

	/* �ж��ļ��Ƿ���� */
	fd= open(filename, O_RDONLY, 0);
	if(fd < 0)
	{	/* �����ڴ���,�򴴽��� */
		rt_kprintf("file:\"%s\" does not exist!\n", filename);
		return;
	}
	close(fd);
	
	rt_kprintf("read-in file:\"%s\"\n", filename);
	rtgui_edit_readin_file(edit, filename);
}

void demo_edit_saveas_file(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_button_t *button;
	struct rtgui_edit *edit;
	const char* filename = "/test_saveas.txt";
	int fd;
	
	RT_ASSERT(object != RT_NULL);
	button = RTGUI_BUTTON(object);
	/* ȡ��editָ�� */
	edit = RTGUI_EDIT( RTGUI_WIDGET(button)->user_data );

	/* �ж��ļ��Ƿ����, ���������ɾ��֮ */
	fd= open(filename, O_RDONLY, 0);
	if(fd > 0)
	{
		close(fd);
		/* �������win32�е���, ���ֹ�ɾ�����ļ���, NT���ļ���ֻ����,unlinkɾ������ */
		if(unlink(filename) == -1)
			rt_kprintf("Could not delete %s\n", filename);
	}
	
	rt_kprintf("save as file:\"%s\"\n", filename);
	rtgui_edit_saveas_file(edit, filename);
}

/* ����������ʾedit�ؼ�����ͼ */
rtgui_container_t* demo_view_edit(void)
{
	rtgui_rect_t rect;
	rtgui_container_t* container;
	struct rtgui_edit* edit;
	struct rtgui_button* button;

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
						"˫�ֽڲ���\n"
						"a\n"
						"b\n"
						"c\n"
						"d\n"
						"1234567890\n");
	
	/* ����һ����ť, ��ȡĳ���ļ� */
	demo_view_get_rect(container, &rect);
	rect.x1 += 10;
	rect.x2 = rect.x1 + 100;
	rect.y1 += 200;
	rect.y2 = rect.y1 + 22;
	button = rtgui_button_create("ReadIn File");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, demo_edit_readin_file);
	/* ʹ��user_data����editָ�� */
	RTGUI_WIDGET(button)->user_data = (rt_uint32_t)edit;
	
	/* ����һ����ť, ����Ϊĳ���ļ� */
	demo_view_get_rect(container, &rect);
	rect.x1 += 130;
	rect.x2 = rect.x1 + 100;
	rect.y1 += 200;
	rect.y2 = rect.y1 + 22;
	button = rtgui_button_create("SaveAs File");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, demo_edit_saveas_file);
	/* ʹ��user_data����editָ�� */
	RTGUI_WIDGET(button)->user_data = (rt_uint32_t)edit;

	return container;
}
