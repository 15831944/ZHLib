// Room: /d/pk/turen7.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "[1;31mɥ����[2;37;0m");
	set("long", @LONG
������ɭ�ֲ������ϵ����ǲ�֫��ʬ���޴����ǰ���ɫ��Ѫ�Ρ�������
������������־��裬��֪��������ͻ�ܳ�һ����Ӱ��
LONG
);
	set("trds", "1");
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"turen3",
  "southeast" : __DIR__"turen11",
  "east" : __DIR__"turen8",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
