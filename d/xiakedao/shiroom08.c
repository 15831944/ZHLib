// /d/xiakedao/shiroom08.c ���͵� ʯ��8

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "ʯ��");
        set("long", @LONG
ʯ�����У�һλ��üɮ�˺�һλ����֮���������书��һ����Ů
���Ա߲��籼�У�����֮�ʣ�����������Ǻ�г������һ����ɫ��м
��վ��ǽ�ǣ���ָ��ʯ��(wall)����ָժ���˵���ʽ��
LONG );
        set("exits", ([
                "east" : __DIR__"shihole2",
        ]));
        set("item_desc", ([
                "wall" : @WALL
ǽ�����Ϸ����š�������������������֡��ֵ��·��̵���һ������
�˿ڵĹ��£��������ʩ�������ˣ����ۺ��ϡ�ֻ��ͼ����Ů��Ŀ��
�飬�Ա��Ƿ����΢Ц������µ�ˮ�Ƶ�������Զ����ɫ����һ�塣
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
