inherit ROOM;

void create()
{
        set("short", "����㳡");
        set("long", @LONG
�����ǳ��е������ģ�һ���ܿ����Ĺ㳡��������ʯ���档һЩ���ֺ�
�е��������������������������������ݡ�������һ�ô��������̸�
��ڣ��ݴ�����ǧ������䣬���������е���ʷ��֤�����ɵײ���һ���ܴ�
������ (dong)�� ����Կ������������Ը��ص�������������������������
�У�һ�ɷ������󣬶��߲�ʱ�ش������ʵĶ�������������������������ˣ�
һƬ�ྲ��
LONG );
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : "����һ���ڲ����еĴ󶴣����治֪����Щʲô�Ź֡�\n",
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
//            "up" : "/u/jedi/214room",
                "north" : __DIR__"beidajie1",
        ]));

        set("objects", ([
                "/d/city/npc/jpl2": 1,
                __DIR__"npc/liapo" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
        return 0;

        if( arg=="dong" ) 
        {
                if (me->is_busy() )
                {
                        return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
                        return 1; 
                }

                message("vision",
                        me->name() + "һ�������������˽�ȥ��\n",
                        environment(me), ({me}) );
                me->move("/d/gaibang/inhole");
                message("vision",
                        me->name() + "�Ӷ������˽�����\n",
                        environment(me), ({me}) );
                return 1;
        }
}       

