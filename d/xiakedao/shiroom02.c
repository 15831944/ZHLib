// /d/xiakedao/shiroom02.c ���͵� ʯ��2

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����ڶ���ʯ�ң�ֻ����ǰһ�����˵��ǽ����ݺᡣ���˸��ֳ�
��������׽�Խ���������ײ�������������������ż������̲�һ
�ĶϽ���ǽ��Ҳ��Щ���������İߺۡ��Ա�����λ��������������ʲ
�ᡣʯ��(wall)���������ּ���
LONG );
        set("exits", ([
                "north" : __DIR__"shihole1",
        ]));
        set("item_desc", ([
                "wall" : @WALL
ǽ�����Ϸ����š��⹳˪ѩ�����������֡����ֵ��·������������
��������ǧС�֣��ʻ����죬��С��ͬ����һ���ǣ������ָ�������
�����⹳��������һ��д���ǣ��׾���ʫ�ƣ�������ֱ�۽�����ʤ��
ȫ������
WALL
        ]));

        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        setup();
}
void init()
{
        add_action("do_study","think");
}
#include "/d/xiakedao/shiroom.h"
