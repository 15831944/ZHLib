// Room: /d/guanwai/chufang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������ƣ��������ڣ���ζ�˱Ƕ�������ǽ��һ����̨��֧��һ�ڴ����
������������������࣬�Աߵ�һ���������Ű�����ͷ��
LONG );
	set("exits", ([
		"south" : __DIR__"houyuan",
	]));
	set("objects",([
		__DIR__"obj/wan" : 2,
                __DIR__"obj/mantou" : 5,
	]));
	set("resource/water", 1);
	setup();
	replace_program(ROOM);
}
