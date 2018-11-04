// /d/wizard/guest_room.c

#include <room.h>
inherit ROOM;

int is_chat_room() {return 1;}
void create()
{
	set("short", "��ʦ�����");
	set("long", @LONG
��������ʦ����ҽ����ĵط����������ʲô������Ҫ����ʦ��
�̣���������������(post)�������������ǣ�浽���ջ����Ѿ��ڰ�
���ļ�������ϸ˵������ʦ�ǾͲ�һ����ش�¥������ʦ��Ϣ�ң�
һ����ҵ��������ϲ�ȥ�ˡ�
LONG );

	set("exits", ([
		"up": __DIR__"wizard_room",
		"west":__DIR__"mingren_room",
		"southeast": "/d/city/wumiao"
        ]));
	set("no_fight", "1");
	create_door("southeast", "����", "northwest", DOOR_CLOSED);
	setup();
	"/clone/board/towiz_b"->foo();
}

int valid_leave(object me, string dir)
{
        if (dir == "up" && (! userp(me) || ! wizardp(me)))
                return notify_fail("����ֻ����ʦ���ܽ�ȥ��\n");
        return ::valid_leave(me, dir);
}

