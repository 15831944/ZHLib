// Room: /d/pk/turen11.c
// This is a room made by roommaker. write by Fan. :)

inherit ROOM;

void create()
{
	set("short", "[1;31m���˳�[2;37;0m");
	set("long", @LONG
������ɭ�ֲ������ϵ����ǲ�֫��ʬ���޴����ǰ���ɫ��Ѫ�Ρ�������
������������־��裬��֪��������ͻ�ܳ�һ����Ӱ��
LONG
);
	set("trds", "1");
	set("exits", ([ /* sizeof() == 3 */
  "northwest" : __DIR__"turen7",
  "north" : __DIR__"turen8",
  "east" : __DIR__"turen12",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
