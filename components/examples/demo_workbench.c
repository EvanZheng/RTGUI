#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_application.h>

#include <rtgui/widgets/container.h>

static rt_bool_t demo_workbench_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	/* ����Ŀǰֻ�԰����¼�����Ȥ�������ǰworkbench����ģʽ��ʾ״̬��������  */
	if ((event->type == RTGUI_EVENT_KBD) && !RTGUI_APPLICATION_IS_MODALED(RTGUI_APPLICATION(widget)))
	{
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;

		if (ekbd->type == RTGUI_KEYDOWN)
		{
			if (ekbd->key == RTGUIK_RIGHT)
			{
				demo_view_next(RT_NULL, RT_NULL);
				return RT_TRUE;
			}
			else if (ekbd->key == RTGUIK_LEFT)
			{
				demo_view_prev(RT_NULL, RT_NULL);
				return RT_TRUE;
			}
		}
	}

	/* ������ǻ����¼���ʹ��viewԭ�����¼����������� */
	return rtgui_application_event_handler(widget, event);
}

static void workbench_entry(void* parameter)
{
	struct rtgui_application* app;

	app = rtgui_application_create(rt_thread_self(),
            "main", "guiapplication");
	if (app == RT_NULL) return;

	rtgui_widget_set_event_handler(RTGUI_WIDGET(app), demo_workbench_event_handler);

	/* ��ʼ���������ӵ���ͼ */
#if RT_VERSION == 4
	demo_view_benchmark(app);
#endif

	demo_view_dc(app);
#if RT_VERSION == 4
#ifdef RTGUI_USING_TTF
	demo_view_ttf(app);
#endif
#endif

#ifndef RTGUI_USING_SMALL_SIZE
	demo_view_dc_buffer(app);
#endif
	demo_view_animation(app);
#ifndef RTGUI_USING_SMALL_SIZE
	demo_view_buffer_animation(app);
	// demo_view_instrument_panel(app);
#endif
	demo_view_window(app);
	demo_view_label(app);
	demo_view_button(app);
	demo_view_checkbox(app);
	demo_view_progressbar(app);
	demo_view_scrollbar(app);
	demo_view_radiobox(app);
	demo_view_textbox(app);
	demo_view_listbox(app);
	demo_view_menu(app);
	demo_view_listctrl(app);
	demo_view_combobox(app);
	demo_view_slider(app);
	demo_view_notebook(app);
	demo_view_mywidget(app);
#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
	demo_view_image(app);
#endif
#ifdef RT_USING_MODULE	
#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
	demo_view_module(app);
#endif
#endif
	demo_listview_view(app);
	demo_listview_icon_view(app);
#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
	demo_fn_view(app);
#endif

	/* ��ʾ��ͼ */
	demo_view_show();

	/* ִ�й���̨�¼�ѭ�� */
	rtgui_application_exec(app);

	/* ȥע��GUI�߳� */
	rtgui_application_destroy(app);
}

void workbench_init()
{
	static rt_bool_t inited = RT_FALSE;

	if (inited == RT_FALSE) /* �����ظ���ʼ�������ı��� */
	{
		rt_thread_t tid;

		tid = rt_thread_create("wb",
			workbench_entry, RT_NULL,
			2048 * 2, 25, 10);

		if (tid != RT_NULL) rt_thread_startup(tid);

		inited = RT_TRUE;
	}
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void workbench()
{
	workbench_init();
}
/* finsh���������������ֱ��ִ��workbench()������ִ������ĺ��� */
FINSH_FUNCTION_EXPORT(workbench, workbench demo)
#endif
