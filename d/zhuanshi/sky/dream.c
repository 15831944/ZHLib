#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "���ξ���" NOR);
        set("long", CYN @LONG
�������ξ�����о������Ժ����ģ���ʶ�ܲ�������
�Ĵ����ǰ�ããһƬ����ʲô�������С�
LONG NOR );
 /*       set("exits", ([
                "enter" : __DIR__"sky1",
]));*/
        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                "/adm/npc/buddha2": 1,
        ]));

        setup();
}

