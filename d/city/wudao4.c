// Room: /city/wudao4.c
// Date: Feb.28 1998 by Java

#include <ansi.h>

inherit __DIR__"underlt";

void create()
{
        set("short", "�����");
        set("long", @LONG
���������滷ɽ��ֻ�б����������ڵ�һƺɽ��ƽ�ء�ɽ��ɽ�������λ�
�����죬ɽ���µ�ƽ���̲������м�����˸���̨������һ���ȥ�������
�������α����ȫ��
        ������������ı��䳡��������������ı��䳡��
                  �����ǳ�����ı��䳡��
LONG );
        set("outdoors", "city");
        set("exits", ([
                "north"       : __DIR__"ximenroad",
                "west"        : __DIR__"wudao1",
//                "east"        : __DIR__"wudao2",
//                "south"       : __DIR__"wudao3",
        ]));
        set("no_fight", 1);
        setup();
        "/clone/board/wudao_b"->foo();
        init_here();
        replace_program(__DIR__"underlt");
}

