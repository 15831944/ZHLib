// sroad6.c
// Modified by Java Apr.27 1998

inherit ROOM;
void create()
{
        set("short","��ѩɽ��");
        set("long",@LONG
����ѩ�أ�����̹ǡ���������������ˣ���Ȼ���ܲ�ס�ˡ�
LONG );
        set("exits",([
                "northdown" : __DIR__"sroad5",
                "westup"    : __DIR__"sroad7",
        ]));
        set("outdoors", "xueshan");
        setup();
	replace_program(ROOM);
}
