// Room: /city/dangpu.c
// YZC 1995/12/04 

inherit AREA_ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ����������ƽ���Ƶĵ��̣�һ����߸ߵĹ�̨���������ǰ��
��̨�ϰ���һ������(paizi)����̨���������ϰ壬һ˫��������������
�������㡣
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);
	set("item_desc", ([
		"paizi" : "��ƽ����\n
list        ����
sell        �� 
buy         ��
pawn        �䵱
redeem      ��
value       ����
check       ��ѯ

",
	]));
	set("objects", ([
                __DIR__"npc/tang" : 1,
                __DIR__"npc/boss3" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"nandajie1",
	]));
        set("area/ziyuan", "�ʽ�");

	setup();
}
