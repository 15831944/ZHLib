// File(/data/room/suifeng/houyuan.c) of suifeng's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "�һ��Ⱥ�Ժ");
	set ("long", @LONG
�����һ��ȵĺ�Ժ������һЩ���ݣ��󲿷��Ƕ���֪����Ұ����
�ݡ���������������Ҳ����ȥҲ�ǳ�Ư������ʱ������������ƣ��
�ˣ��͵���������Ƭ������Ϣ��Ҳ��ʱ����������������������
��һ�����ա� 
LONG );

	setup();

	set("exits", ([
                "south"  : __DIR__"dating",
	]));

        set("outdoors", "quanzhen");
        set("sleep_room", 1);

        set("room_owner", "�����");
        set("room_name", "�һ���");
        set("room_id", "taohuagu");
        set("room_owner_id", "suifeng");
        set("room_position", "��ˮ̶");
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
