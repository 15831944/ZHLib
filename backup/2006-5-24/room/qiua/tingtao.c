// File(/data/room/qiua/tingtao.c) of qiua's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
	set("short", "���θ�");
	set ("long", @LONG
��������һ�ǵ����θ�������紵��Ҷ�������������ķǳ���
�У����������Ŀ�������ʵ����һ�������书�ĺ�ȥ���� 
LONG );

	set("exits", ([
                "west" : __DIR__"zhulin",
	]));

        set("sleep_room", 1);
        setup();

        set("research_improve", 15);  //15% improved
    
        set("room_owner", "��һ");
        set("room_name", "��ʵ");
        set("room_id", "qiua");
        set("room_owner_id", "qiua");
        set("room_position", "ɽ·");
}
