// Room: /d/pk/turen2.c
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
  "west" : __DIR__"turen1",
  "southeast" : __DIR__"turen6",
  "south" : __DIR__"turen5",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
