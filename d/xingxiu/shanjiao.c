// tianshan: /d/xingxiu/shanjiao.c
// Jay 3/17/96

inherit ROOM;

void create()
{
        set("short", "��ɽ����");
        set("long", @LONG
��������ɽ���£������Ǹ������Ƶ���ɽ�������ʱ����Կ���ɽ��
�ϵı�����һ����ɽ�������Ϊ���롣�������������ľ۾������Ͻ���
�ޱߵ���������ɴ�ɳĮ��
LONG );
        set("exits", ([
            "westup" : __DIR__"tianroad1",
            "north"  : __DIR__"kedian",
            "northwest" : __DIR__"beijiang",
            "southwest" : __DIR__"nanjiang",
            "southeast" : __DIR__"silk4",
        ]));
        set("outdoors", "xingxiuhai" );
        set("objects", ([
                __DIR__"npc/trader" : 1
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
	if (! userp(me) && dir == "southwest")
		return 0;

	return ::valid_leave(me, dir);
}

