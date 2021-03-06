// File(/data/room/mei/dating.c) of mei's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "彩云之南大厅");
	set ("long", @LONG
这就是彩云之南主人段诗雨迎送客人的地方。正中有些桌椅，侧
面是两扇屏风。东首是主人段诗雨的房间，有一扇木门虚掩着。南边
是大门，出去就是院子。 
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
    
        set("room_owner", "段诗雨");
        set("room_name", "彩云之南");
        set("room_id", "mei");
        set("room_owner_id", "mei");
        set("room_position", "山路");
}
