// /d/xiakedao/shiroom05.c ���͵� ʯ��5

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "ʯ��");
        set("long", @LONG
һλ�ɷ���ǵ���������һλ�ߴ���������д��书�����˾���
��ֿս�����ʽ������������󾢷罫���ڵû�Ѽ���������������
ʯ��(wall)��ͼ�����ǰವ½�롣
LONG );
        set("exits", ([
                "south" : __DIR__"shihole2",
        ]));
        set("item_desc", ([
                "wall" : @WALL
ǽ�����Ϸ����š�ʮ��ɱһ�ˡ��������֡����µ�ͼ��ȴ��һ������
ɽˮ��������ɽ�����֣�����ľ��֦�����̲�һ��ǰ���ݺᣬ��Ҳ��
���۽�������������ͼ��������Сע��
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
