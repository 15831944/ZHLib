// xiaowu.c
inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
��������С���Ժ󣬷������ﾹȻ��������Ĳ��ܴ�����
��Ȼ����˵�ǽ�̻Իͣ��������������Ƶ����������������Σ�����
�磬��������......����ʤ����ǽ�Ϲ���һ����������һ�߰���
���١�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
            "out" : __DIR__"xiaoyuan",
        ]));
        set("objects", ([ /* sizeof() == 1 */
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "meizhuang");

        setup();
        replace_program(ROOM);
}

