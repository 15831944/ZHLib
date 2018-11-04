// File(/data/room/mei/woshi.c) of mei's room
// Create by LUBAN written by Doing Lu

#include <room.h>
#include <ansi.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����֮������");
	set ("long", @LONG
�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������
һ�����ӣ�����һ����ܣ��������һЩ�顣�������Ӳ��õ÷ǳ���
�أ������ݻ������������ס� 
LONG );

        set("objects", ([
                "/adm/npc/obj/jubaoxiang" : 1,
        ]));
	setup();

        set("exits", ([
                "west" : __DIR__"dating",
        ]));

        create_door("west", "ľ��", "east", DOOR_CLOSED);
        
    
        set("sleep_room", 1);
        set("loving_room", 1);
        set("no_fight", 1);
    
        set("room_owner", "��ʫ��");
        set("room_name", "����֮��");
        set("room_id", "mei");
        set("room_owner_id", "mei");
        set("room_position", "ɽ·");
}

void init()
{
        add_action("do_findbaby", "xunzhao");
}

int do_findbaby(string arg)
{
        object me = this_player(), baby;
        string file;

        if (! arg || (arg != "baby" && arg != "child") ||
            ! is_room_owner(me)) 
                return 0;

        if (! me->query("couple/child"))
                return notify_fail("���ֻ�û�к��ӣ��������ʲô���ְ���\n");

        if (objectp(baby = find_living(me->query("couple/child")))
        &&  environment(baby) && baby->is_baby())
                return notify_fail("���ǵĺ����Ѿ��ܳ�ȥ���ˣ��ú��Ĵ����Ұɣ�\n");

        if (me->query("gender") == "Ů��")
                file = read_file("/data/baby/" + me->query("id") + ".o");
        else file = read_file("/data/baby/" + me->query("couple/id") + ".o");

        if (stringp(file))
        {
                baby = new("/clone/user/baby");

                baby->load_baby(me);
                baby->move(environment(me));
                message_vision("���Ȼ����������" +
                        ({"̽��һ��С�Թ�", "���һ˫С��Ѿ", "���һ֧С��"})
                        [random(3)] + "������\n", me);

        } else
        {
                tell_object(me, MAG "���ǵĺ��Ӳ���ز���ˣ���ڰ��ɡ�\n" NOR);
                me->delete("couple/child");
                me->delete("couple/child_name");
        }
        return 1;
}      
