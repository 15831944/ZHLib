// Room: /d/suzhou/road1.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
	set("short", "��ʯ�ٵ�");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ������
�������ҴҶ��������������һЩС��̯���ƺ���һ�����С�
����������ݳ��ˡ�
LONG );
	set("outdoors", "suzhou");
	set("max_room", 5);
	set("exits", ([
		"south"     : __DIR__"beimen",
		"southwest" : __DIR__"huqiu",
		"northwest" : "/d/guiyun/shanlu2",
	]));
	setup();
}
