// caoping.c
inherit ROOM;
void create()
{
        set("short","��ƺ");
        set("long",
             "������һ�鷼��ƺ���̲����𣬺������裬���˸е���⡣\n"
             "����ż��Ҳ�������˻��ߡ�\n"
        );
        set("exits", ([
                "west" : __DIR__"shijie",
        ]));
        set("objects" , ([
             "/clone/beast/caihuashe" : random(4),
        ]));
        set("outdoors", "baituo");
        setup();
        replace_program(ROOM);
}
