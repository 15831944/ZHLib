// Roon: ziqitai.c
//Date: Oct. 2 1997 by Venus
inherit JIETI;
inherit BUILD_ROOM;

void create()
{
        set("short", "����̨");
        set("long", @LONG
����̨�����������ڣ����ɲ������գ���Ϊ������ǣ�û������
�죬ɽ��֮�о��������������֡�
LONG);
        set("no_fight",1);
        set("outdoors", "xx");
        set("max_room", 3);
        set("exits",([ /* sizeof() == 1 */
            "eastdown": __DIR__"chaopath2",
//            "westup" : "u/crow/juding",
        ]));
        set("no_clean_up", 0);
        setup();
}
void init()
{
        object me;
        me=this_player();
        if (me->query_dex() > 40)
             this_object()->set("exits/down", "/d/jinshe/shanbi");
        else
             this_object()->delete("exits/down");
        remove_call_out("close");
        call_out("close", 5, this_object());
        add_action("do_jieti","jieti");
        add_action("do_decide","decide");
        return;
}
void close(object room)
{
        this_object()->delete("exits/down");
        return;
}

