// Room: /city/qianzhuang.c
// YZC 1995/12/04 

inherit AREA_ROOM;

void create()
{
	set("short", "Ǯׯ");
	set("long", @LONG
����һ�����ֺŵ�Ǯׯ�����м��������ʷ����ȫ�����ض��зֵꡣ
�����е���Ʊ�����ǳ��ã�ͨ��ȫ�����ڶ����ǽ�Ϲ��˿�����(paizi)��
LONG );
	set("exits", ([
                "east" : __DIR__"beidajie1",
                "up" : __DIR__"qnbank1",
	]));
	set("item_desc", ([
		"paizi" : @TEXT
     ��Ǯׯ�ṩ���·���
      ��Ǯ        deposit����cun
      ȡǮ        withdraw����qu
      Ǯ�Ҷһ�    convert����duihuan
      ����        check����chazhang
TEXT
	]) );

	set("objects", ([
                __DIR__"npc/qian" : 1,
                __DIR__"npc/boss5" : 1,
	]));
        set("area/ziyuan", "Ǯ��");
	setup();
}

