// Room: /city/wudao1.c

#include <ansi.h>

inherit __DIR__"underlt";

void create()
{
        set("short", "�����");
        set("long", @LONG
���������滷ɽ��ֻ�б����������ڵ�һƺɽ��ƽ�ء�ɽ��ɽ�������λ�
�����죬ɽ���µ�ƽ���̲������м�����˸���̨������һ���ȥ�������
�������α����ȫ��������������ı��䳡�أ�
LONG );
        set("outdoors", "city");
        set("exits", ([
                "leitai"      : __DIR__"leitai",
                "east"        : __DIR__"wudao4",
                "north"        : __DIR__ "biwu_road",
        ]));
        set("no_fight", 1);
        setup();
        init_here();
        replace_program(__DIR__"underlt");
}

