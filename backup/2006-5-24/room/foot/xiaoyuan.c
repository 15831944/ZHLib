// File(/data/room/foot/xiaoyuan.c) of foot's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "大脚世界小院");
	set ("long", @LONG
这里是一个不大的院子，角落里栽了几棵树，地上零零散散有一
些碎落叶片。院门虚掩，穿过院子就是一个小屋，非常精致。 
LONG );

        set("room_key", "1 of foot");
	setup();

	set("exits", ([
                "out"    : "/d/room/playtown/road11",
	]));

        set("outdoors", "playertown");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dulewu",
        ]));
    
        set("room_owner", "大脚板");
        set("room_name", "大脚世界");
        set("room_id", "foot");
        set("room_owner_id", "foot");
        set("room_position", "青砖路");
}
