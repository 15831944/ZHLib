//Room: dongan-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "�������");
        set ("long", @LONG
�����ǵ����ֶ��������Ϊ���֣����˱��ǵľ����⣬���в�����
�����ÿͺ����ˡ�����������򶫾��ǳ����ǵ����µ��ڡ������ţ���
���ǹʻʹ��ķ�ڼ�����������Ǵ����������������ܲ��ˡ�
LONG);
        set("exits", 
        ([ //sizeof() == 2
		"west" : __DIR__"fengxu3",
        	"east" : __DIR__"dongan-daokou",
                "north" : __DIR__"xym_zb",
        ]));

        set("outdoors", "changan");
        setup();
        replace_program(ROOM);
}
