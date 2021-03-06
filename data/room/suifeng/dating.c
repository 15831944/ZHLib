// File(/data/room/suifeng/dating.c) of suifeng's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "桃花谷大厅");
	set ("long", @LONG
这就是桃花谷主人柳随风迎送客人的地方。正中有些桌椅，侧面
是两扇屏风。东首是主人柳随风的房间，有一扇木门虚掩着。南边是
大门，出去就是院子。 
LONG );

	setup();

	set("exits", ([
                "east"   : __DIR__"woshi",
		"north"  : __DIR__"houyuan",
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("no_sleep_room", 1);

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("room_owner", "柳随风");
        set("room_name", "桃花谷");
        set("room_id", "taohuagu");
        set("room_owner_id", "suifeng");
        set("room_position", "寒水潭");
}
