// Room: /guiyun/jinship.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
	set("short", "���ս��");
	set("long", @LONG
�����Ǵ�����ʹ��ս������������Ϸ���������ţ������
���Ѽ��������ں�����һ����Ц�����һ������ֺ�����
LONG );
        set("outdoors", "guiyun");
//	set("no_clean_up", 0);

	set("exits", ([
		"out" : __DIR__"ship",
	]));
	set("objects", ([
		"/d/huanghe/npc/peng" : 1,
		"/d/huanghe/npc/sha" : 1,
		"/d/huanghe/npc/liang" : 1,
		"/d/huanghe/npc/hou" : 1,
		"/d/huanghe/npc/ma" : 1,
		"/d/huanghe/npc/qian" : 1,
		"/d/huanghe/npc/shen" : 1,
		"/d/huanghe/npc/wu" : 1,
		"/kungfu/class/xueshan/lingzhi" : 1,
		__DIR__"npc/duantiande" : 1,
		__DIR__"npc/wanyankang" : 1,
		__DIR__"npc/wanyanhonglie" : 1,
		__DIR__"npc/jinbing" : 1 + random(3),
	]));
	setup();
	replace_program(ROOM);
}
