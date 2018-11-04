// Room: /city/wudao4.c
// Date: Feb.28 1998 by Java

#include <ansi.h>

inherit __DIR__"underlt";

void create()
{
        set("short", "武道场");
        set("long", @LONG
这里是三面环山，只有北面有条出口的一坪山间平地。山坡山阵阵松涛哗
哗作响，山脚下的平地绿草如茵，中间架起了个擂台，四周一溜过去搭着凉棚，
棚中桌椅杯盆俱全。
        西面是少年组的比武场，东面是青年组的比武场，
                  南面是成年组的比武场。
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

