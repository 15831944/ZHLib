// Updated by rama

inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "����");
        set("long", @LONG 
���������µ�һ����ۡ�������ľ��涣��ڸ�ͤͤ���е�ʿ��
����ȥ��û�˵ÿ����㣬��û�˽Ӵ��㡣����õ�һ�ֿ��ɵ�ʧ�䡣
�Ա���һ��ľ�ţ�door����
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"westroad1",
        ]));
        set("item_desc", ([
                "door" : "����ľ�Ž����ţ���Щ�����ˡ�\n" ,
        ]));

        setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="door")
        return notify_fail("������������ľ�ţ����һ�㶯����û�У������Ǳ������ˣ�\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("��Ҫ��ʲô��\n");
          if (arg != "door")
                return notify_fail("��Ҫ��ʲô��\n");
          if( arg=="door" ) {
                message_vision("$N����������ľ�š�\n", me);
                if (me->query("bang_bad/name")!="������" && (int)me->query("shen") <= 0)
                {
                        message_vision(HIB"ľ��֨ѽһ�����ˣ�������̽����ͷ��������$N����˵����������Ͷ�����������ŵİɣ�����
˵��һ�Ѱ�$N���˽�ȥ��\n"NOR, me);
                        me->move(__DIR__"xlm_cdfb");
                        return 1;
                }
                if( me->query("bang_good") || (int)me->query("shen") > 0 ) 
                { 
                                command("say ��������аħ������Ҵ�ô��\n"); 
                        return 1; 
                } 
                message_vision("ľ��֨ѽһ�����ˣ�������̽����ͷ��������$N����˵��������Ȼ�Ǳ��ŵ��ֵܣ��ͽ����ɣ�����
˵��һ�Ѱ�$N���˽�ȥ��\n",me);
                me->move(__DIR__"xlm_cdfb"); 
                return 1; 
        }
        
        return 1;
}
  
