inherit AREA_ROOM; 

void create()
{
	set("short", "ҩ��");
	set("long", @LONG
����һ��ҩ�̣�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ
���ϵļ��ٸ�С������ɢ�������ġ�һ��С���վ�ڹ�̨����
���Ź˿͡���̨������һ�ŷ��ƵĹ�档
LONG);
	set("objects", ([
                __DIR__"npc/ping" : 1,
                __DIR__"npc/boss6" : 1,
	]));
             set("area/ziyuan", "ҩ��"); 
        set("exits", ([
		"south" : __DIR__"dongdajie2",
	]));
	set("coor/x",20);
	set("coor/y",10);
	set("coor/z",0);
	setup();
	//replace_program(ROOM);
}
