// sroad5.c
// Modified by Java Apr.27 1998

inherit ROOM;
void create()
{
        set("short","��ѩɽ");
        set("long",@LONG
�����ر�ѩ������ǰ�װ�����һƬ���Ӷ����������ģ�������ʼ���١�
LONG );
        set("exits",([
                "eastdown"  : __DIR__"sroad4",
                "southup"   : __DIR__"sroad6",
        ]));
        set("outdoors", "xueshan");
        setup();
	replace_program(ROOM);
}
