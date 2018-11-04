//ROOM: /d/yanziwu/bozhou.c

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "������");
        set("long",@LONG
һƬ«έ�����״����ֳ�һ�����룬��С��ֻ�����ſ����⻨��Ҷ
��������ˮ����ͨ�˴�ɴ˿ɳ˴��뿪�����롣������ϵ��һβС��
(zhou)������ԶԶ����ȥ��һ�����ӡ�
LONG );
        set("outdoors", "yanziwu");

        set("exits", ([
            "east"  : __DIR__"pindi",
	    "northdown" : __DIR__"muti",
        ]));

        set("item_desc", ([
            "zhou" : "����������ͺ�����ϵ��С�ۡ�����һ��������Ů�����ϵĿ���ֻҪ��
��(enter)�Ϳ��Գ����ˡ�\n",
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("boat",1);
        set("opposite", __DIR__"hupan");
        setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_cross", "cross");
}

int do_enter(string arg)
{
        object ob ;
        string dir;

        if (! arg || arg != "zhou")
        {
                tell_object(this_player() , "��ҪͶˮ��\n" );
                return 1;
        }
        ob = this_player();
        message_vision("����һ����������Ľ�����Ů����$N���ۣ���"
		       "����㣬�����밶��\n�����뽥������Ұ��Զ"
		       "ȥ��\n", ob);
        ob->move(__DIR__"taihu");
        tell_object(ob, HIG "���ں���Ʈ�������ܿ������Ľ���������\n" NOR);
        call_out("home", 10, ob);
        return 1;
}

void home(object ob)
{
	if (! objectp(ob))
		return;

        tell_object(ob, "С��������������ؿ����ˣ�������С"
		    "��������Ů���ֵ���\n");
        ob->move(__DIR__"hupan");
}

int do_cross()
{
        object me;

        me = this_player();
        if (me->query_skill("dodge") < 100)
        {
                tell_object(me, random(2) ? "����ú���̫��û��ʮ��İ���Ծ��ȥ��\n"
                                          : "�㿴�ź�嫵�̫�������ﲻ�����˸�ͻ��û��������\n");
                return 1;
        }

        if (me->query("neili") < 100)
        {
                tell_object(me, "�������������������Ϣһ����˵�ɡ�\n");
                return 1;
        }

        me->add("neili", -50);
        message_vision("$N����һ�Σ���ȻԾ��̫����ֻ��$P��̤�岨������Զȥ��\n", me);
        tell_object(me, "��˳���ĵ����˱˰���\n");
        me->move(__DIR__"hupan");
        return 1;
}

