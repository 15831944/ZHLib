// Room: /d/xiakedao/xkroad5.c
// Modified by Java on Feb.14.1998
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�����Ǹ�СС��ۡ����溣��Ư���ż���С����̧������������
�����ޱ��޼ʡ���Ÿ�ӹ��˼⣬������Ȼ��
LONG );
        set("outdoors", "xiakedao");
	set("exits", ([
		"east"    : __DIR__"xkroad4",
	]));
	set("objects", ([
		__DIR__"npc/shizhe" : 1,
	]));
	setup();
}

void init()
{
    add_action("do_enter", "enter");
}

int do_enter ( string arg )
{
    object ob ;
    string dir;
    if( !arg || arg !="boat" )
       {
         tell_object(this_player() , "��Ҫ enter �Ķ���\n" ) ;
         return 1 ;
       }
    ob = this_player () ;
    message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", ob);
    message_vision("�������𷫣��������Ϸ����С�\n", ob);
    ob->move("/d/xiakedao/dahai") ;
    tell_object(ob, BLU "���ں��Ϻ�����������ҹ.......\n" NOR ) ;
    call_out("home", 10 , ob );
    return 1 ;
}

void home( object ob )
{
    tell_object(ob , "�����ڵִ��˺������ߡ������´�����\n" ) ;
    ob->move (__DIR__"haitan") ;
}
