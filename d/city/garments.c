inherit AREA_ROOM;

void create()
{
	set("short", "���µ�");
	set("long", @LONG
�������������¹󸾳���֮��������Ҳ��������Ҳң�֬
�ۺ�ɡ���Ϊ��������ʱ�У�һֱ�����������Ե�װ�硣����
�Ǹ��ܿ��˵�СŮ����������һ������ʱ���������������Ů
�˼���һ�𣬻�������������
LONG );
	set("exits", ([
		"down" : __DIR__"zahuopu",
	]));
	set("objects", ([
                __DIR__"npc/zeng": 1,
                __DIR__"npc/boss7": 1,
	]));
	set("no_fight", 1);
	set("coor/x",10);
	set("coor/y",-10);
	set("coor/z",10);
        set("area/ziyuan", "��ƥ");
	setup();
	//replace_program(ROOM);
}

