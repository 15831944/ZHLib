// Room: /city/zahuopu.c
// YZC 1995/12/04 

inherit AREA_ROOM;

void create()
{
	set("short", "�ӻ���");
	set("long", @LONG
����һ��СС���ӻ��̣�����С�������һ�أ�����һЩ�ճ���Ʒ��
���ƹ������������һֻ�����ϣ��к��Ź������ˡ���˵˽������Ҳ��һ
Щ���صĶ�����̯������һ������(zhaopai)��
LONG );
	set("item_desc", ([
		"zhaopai": "���� \"list\" �г������\"buy\" ���ϰ幺�\n",
	]));
	set("exits", ([
		"north" : __DIR__"dongdajie1",
		"up"    : __DIR__"garments",
	]));
	set("objects", ([
                __DIR__"npc/boss4": 1,
                __DIR__"npc/yang": 1,
	]));
        set("area/ziyuan", "ԭ��");
//	set("no_clean_up", 0);
	setup();
}

