//Room: /d/foshan/beidimiao.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","������");
	set("long",@LONG
�������������ϡ�Ժ����һ����ˮ��������ʯ��ʯ�ߣ���Ȼ��
�ᡣ�������ʯ����Ѫ����Ȼ�������������ڴ�����С�
LONG);
	set("exits",([ /* sizeof() == 1 */
	    "south"  : __DIR__"street1",
	]));
        set("no_fight", 1);
        set("valid_start_room", 1);
        set("no_sleep_room", 1);
	setup();
	replace_program(ROOM);
}

