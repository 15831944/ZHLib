// shishi1.c
// by shilling 97.2

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
����һ��ʯͷ���ɵķ��䣬��Ϊ�þ�û����������ɢ����һЩ�����ŵ�
��ζ�������е������Կ�����˿�ͳ漣��
LONG );
	set("exits", ([
		"up" : __DIR__"midao",
	]));


	set("objects",([
                __DIR__"obj/putuan" : 1,
		CLASS_D("xiaoyao") + "/xiaoyaozi" : 1,
	]));

	setup();
	replace_program(ROOM);
}
