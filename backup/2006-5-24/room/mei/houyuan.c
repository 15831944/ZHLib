// File(/data/room/mei/houyuan.c) of mei's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "����֮�Ϻ�Ժ");
	set ("long", @LONG
���ǲ���֮�ϵĺ�Ժ������һЩ���ݣ��󲿷��Ƕ���֪����Ұ��
���ݡ���������������Ҳ����ȥҲ�ǳ�Ư������ʱ��ʫ���������ƣ
���ˣ��͵���������Ƭ������Ϣ��Ҳ��ʱ��������������������
�д�һ�����ա� 
LONG );

	setup();

	set("exits", ([
                "south"  : __DIR__"dating",
	]));

        set("outdoors", "quanzhou");
        set("sleep_room", 1);

        set("room_owner", "��ʫ��");
        set("room_name", "����֮��");
        set("room_id", "mei");
        set("room_owner_id", "mei");
        set("room_position", "ɽ·");
}

void init()
{
        add_action("do_sit", "sit");
        this_player()->delete_temp("has_sit");
}

int do_sit(string arg)
{
        object me;

        me = this_player();
        if (me->query_temp("has_sit"))
        {
                message_vision("$N��������ҡ��ҡ���ò���⡣\n", me);
                return 1;
        }

        message_vision("$N���˵ĵط���������������ȥ���ɶ��ˡ�\n", me);
        me->set_temp("has_sit", 1);
        return 1;
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("has_sit"))
        {
                message_vision("$N����������վ��������\n", me);
                me->delete_temp("has_sit");
        }

        return ::valid_leave(me, dir);
}
