// shandong3.c
// Modified by Java Apr.27 1998

inherit ROOM;

void create()
{
        set("short","ɽ��");
        set("long",@LONG
����һ��СС��ɽ����Ѫ������Ĳ���֮�ء���춴˵رȽ����أ�
��Һ���Ѱ��������������һ�Ź��������湩��ʲ�ᶫ�����㿴���塣
���ϻ���һЩģ�����������ͼ����Ҳ��֪����Щʲô��
LONG );
        set("exits",([
                "out" : __DIR__"shandong2",
                "east": __DIR__"xiuxishi",
        ]));
        set("objects", ([
                CLASS_D("xuedao")+"/laozu" :1,
                __DIR__"npc/x_lama" :1,
        ]));
	set("valid_startroom", 1);
        setup();
        replace_program(ROOM);

        "/clone/board/xuedao_b"->foo();
}
