//  Room:  /d/city4/hanguguan.c

inherit  ROOM;

void  create  ()
{
	set("short",  "���ȹ�");
	set("long",  @LONG
������ǹź��Źء���������ɽ���������򣬹�����С�����
ǿ��һ��֮�أ��ƹض������������Զ�������ɨ���£�������Ϊ
���ݴˣ����ɹ����˿��أ���������ʤ֮������������������Ҳ��
�ڴ�����������¾���ǧ�����£��������ж�������
LONG);
	set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  __DIR__"road1",
                "westup"  :  "/d/luoyang/guandaoe4",
		"west"  :  __DIR__"road2",
		"south" :  "/d/xiangyang/caodi3",
	]));
	set("outdoors", "changan");
	setup();
	replace_program(ROOM);
}