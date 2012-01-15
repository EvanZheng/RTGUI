#include <rtthread.h>

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>

rt_bool_t picture_win_onpaint(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;
		struct rtgui_event_paint event;

		/* begin drawing */
		dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(widget));
		if (dc == RT_NULL)
			return RT_FALSE;

		/* get window rect */
		rtgui_widget_get_rect(RTGUI_WIDGET(widget), &rect);

		RTGUI_DC_BC(dc) = white;
		rtgui_dc_fill_rect(dc, &rect);

		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}
	else
	{
		return rtgui_win_event_handler(widget, event);
	}
}

rt_bool_t window_focus(void)
{
	rtgui_label_t *label;

	rtgui_button_t* start_btn;
	rtgui_button_t* stop_btn;
	rtgui_toplevel_t *parent;
    rtgui_win_t *win, *picture_win;
	rtgui_rect_t rect = {0, 20, 240, 320};

	/* ����һ������ */
	win = rtgui_win_create(RT_NULL,
			"������",
			&rect,
			RTGUI_WIN_STYLE_DEFAULT);
	/* �����ͼ��λ����Ϣ */
	rtgui_widget_get_rect(RTGUI_WIDGET(win), &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(win), &rect);
	rect.x1 += 10;
	rect.x2 -= 5;
	rect.y2 = rect.y1 + 20;

	/* ���������õı�ǩ */
	label = rtgui_label_create("������");
	/* ���ñ�ǩλ����Ϣ */
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	/* ��ӱ�ǩ����ͼ�� */
	rtgui_view_add_child(RTGUI_VIEW(win),
			RTGUI_WIDGET(label));
	/*��ӷŴ�ť*/

	/* �����ͼ��λ����Ϣ */
	rtgui_widget_get_rect(RTGUI_WIDGET(win), &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(win), &rect);
	rect.x1 += 10;
	rect.y2 -= 10;
	rect.y1 = rect.y2 - 25;
	rect.x2 = rect.x1 + 50;

	/* ����"����"��ť */
	start_btn = rtgui_button_create("��ť1");
	/* ���ð�ť��λ����Ϣ */
	rtgui_widget_set_rect(RTGUI_WIDGET(start_btn), &rect);
	/* ��Ӱ�ť����ͼ�� */
	rtgui_view_add_child(RTGUI_VIEW(win),
			RTGUI_WIDGET(start_btn));

	/* ���ֹͣ��ť*/
	rtgui_widget_get_rect(RTGUI_WIDGET(win), &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(win), &rect);
	rect.x2 -= 10;
	rect.y2 -= 10;
	rect.x1 = rect.x2 - 50;
	rect.y1 = rect.y2 - 25;

	/* ����"ֹͣ"��ť */
	stop_btn = rtgui_button_create("��ť2");
	/* ���ð�ť��λ����Ϣ */
	rtgui_widget_set_rect(RTGUI_WIDGET(stop_btn), &rect);
	/* ��Ӱ�ť����ͼ�� */
	rtgui_view_add_child(RTGUI_VIEW(win),
			RTGUI_WIDGET(stop_btn));

	parent = RTGUI_TOPLEVEL(rtgui_widget_get_toplevel(RTGUI_WIDGET(start_btn)));
	/*����һ����ͼWindows�ؼ�*/
	rtgui_widget_get_rect(RTGUI_WIDGET(win), &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(win), &rect);
	rect.x1 += 10;
	rect.y1 += 20;
	rect.x2 = rect.x1 + 200;
	rect.y2 = rect.y1 + 150;
	picture_win = rtgui_win_create(parent,
			"��ͼ����", &rect,
            RTGUI_WIN_STYLE_NO_TITLE|RTGUI_WIN_STYLE_NO_BORDER|RTGUI_WIN_STYLE_NO_FOCUS);
    //�������ڣ�û�б�������û����С�����ڣ�Ҳ���ܻ�ȡ����
	/* ���windows���¼�*/
	rtgui_view_add_child(RTGUI_VIEW(win),
			RTGUI_WIDGET(picture_win));
	rtgui_widget_set_event_handler(RTGUI_WIDGET(picture_win),
			picture_win_onpaint);

	/* ��ģ̬��ʾ���� */
	rtgui_widget_focus(RTGUI_WIDGET(win));//�趨�������ȡ����
	rtgui_win_show(win, RT_FALSE);
	rtgui_win_show(picture_win,RT_FALSE);

	/* ִ�й���̨�¼�ѭ�� */
	rtgui_win_event_loop(win);
	return RT_TRUE;
}

