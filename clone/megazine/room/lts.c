#include <ansi.h>

inherit ROOM;

int is_chat_room() { return 1; } 

void create()
{
        set("short",HIW "聊天室" NOR);
	set("long", @LONG
这里是〖地狱〗杂志社聊天室，你可以看见这里的设备十分齐全
你可以在这里好好的聊天。
LONG
	);

	set("exits", ([ 
                        "south" : __DIR__"fourroom",
        ]));

        set("objects", ([
                        "/clone/megazine/room/npc/ltxj" : 1,
        ]));

        set("no_fight",1);   
	setup();
}
