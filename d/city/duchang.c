// Room: /city/duchang.c
// YZC 1995/12/04 

inherit AREA_ROOM;

void create()
{
	set("short", "�ĳ�");
	set("long", @LONG
�����Ƕĳ��Ĵ��ã����ܵķ����ﴫ����ߺ������ĶĲ�����������
�ġ���С���ķ��䡣ǽ�����۴�����һ������(paizi)��
LONG );
	set("item_desc", ([
		"paizi" : "��¥�Ĺ��������ڲ��Խ׶Ρ�\n",
	]));
	set("objects", ([
		CLASS_D("shenlong")+"/pang" : 1,
                __DIR__"npc/boss" : 1,
                      "/d/beijing/npc/duke" : 2, 
                      "/d/beijing/npc/haoke1" : 2, 
                      	
               	
	]));
        set("area/ziyuan", "����");
	set("exits", ([
		"west" : __DIR__"daxiao",
//                "north" : "/u/sinb/shaizifang",
		"up"   : __DIR__"duchang2",
		"east" : __DIR__"nandajie1",
	]));
	setup();
}

