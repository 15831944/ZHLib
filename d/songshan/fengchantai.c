// Room: /d/songshan/fengchangtai.c
// Date: CSWORD 96/03/25
inherit JIETI;

inherit ROOM;

void create()
{
	set("short", "����̨");
	set("long", @LONG
��������̨�ɴ���ʯ������ÿ���ʯ����ü���ƽ��������
��Ϊ����������������ģ�������£��ƿ����ʣ����費������
Ŀ��������ң���ɸ����ţ��ƺ�����һ�ߣ�������������������
�ڣ����϶��ǵ�����ɽ��
LONG );
        set("no_fight",1);
	set("exits", ([
		"eastdown" : __DIR__"junjigate",
	]));
	set("outdoors", "songshan");
	set("no_clean_up", 0);
	setup();
}

void init()
{
        add_action("do_jieti","jieti");
        add_action("do_decide","decide");
}
