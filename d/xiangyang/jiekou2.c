// Room: /d/xiangyang/jiekou2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "��ֿ�");
	set("long", @LONG
��Ϊ�����ʮ�ֽֿڣ����Էǳ����֡�С��С����������
��ߺ���ţ��������ǵ���Ʒ����Ȼ���������ɹž����ţ�����
��������������˿���Ľ��ţ�����������˾�ռ��ߡ�ϰ��Ϊ��
�ˡ�������С��ͬ�����������ǵ��ϰ���ס�����棬�������
������ʯ�̾͵Ĵ�֡����߾��Ǵ����������޼����ܲ���
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
                "east"  : __DIR__"wjb_damen",
		"south" : __DIR__"eastroad2",
		"west"  : __DIR__"northroad2",
		"north" : __DIR__"xiaorong2",
	]));
	set("objects", ([
		__DIR__"npc/kid" : 1,
		"/d/village/npc/seller" : 1,
	]));
	setup();
	replace_program(ROOM);
}
