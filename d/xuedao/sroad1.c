// sroad1.c
// Modified by Java Apr.27 1998

inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long",@LONG
�������ǳ�ɽ���룬��ͨ���㡣һ��ɽ·������ɽ�䣬������
�رߺ���ԭ��
LONG );
        set("exits",([
                "north"  : "/d/city3/nanheqiaos",
                "westup" : __DIR__"sroad2",
        ]));
        set("outdoors", "xueshan");
        setup();
        replace_program(ROOM);
}

