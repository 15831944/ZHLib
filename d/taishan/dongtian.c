// Room: /d/taishan/.c
// Date: CSWORD 96/03/25
inherit JIETI;

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������᷶��Ķ�����ڡ��������ξ���������Ͽ�ڡ�ӥ��ȣ�
�����ɽ��
LONG );
        set("no_fight",1);
	set("exits", ([
		"west" : __DIR__"tanhai",
	]));
	set("no_clean_up", 0);
	set("outdoors", "taishan");
	setup();
}
void init()
{
        add_action("do_jieti","jieti");
        add_action("do_decide","decide");
}

