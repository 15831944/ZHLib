#include <ansi.h> 
inherit ROOM;
int do_cai(string arg);

void create()
{
        set("short", "��������");
        set("long", @LONG
����һƬï�ܵ����֡��ܶ�ü�ʮ�ɸߵĴ�������һ�飬��һ�Ѱ������
ɡ�������¶����ڱεð�Ȼ�޹⡣�����л���ʱ������������Ȼ���������졣
LONG );
        set("exits", ([
                "west" : __DIR__"liandan_lin2",
        ]));

        set("no_clean_up", 0); 
        setup();       
}
void init()
{
        add_action("do_cai","cai");
}

int do_cai(string arg)
{
        object me=this_player();
        object ob;
        object ob1;
        if ( (int)me->query_temp("caiyao")<1)
                return notify_fail("�������˷�ʱ���ˣ����߰ɡ�\n");

        if (!arg || arg != "yao")
                return notify_fail("��Ҫ��ʲô��\n");

        if ( me->is_busy() )
                return notify_fail("�����ң��ȱ𼱡�\n");
       
        if ( (int)me->query("jing")<40)
                return notify_fail("��̫���ˣ���Ϣ�°ɡ�\n");

        if ( (int)me->query("qi")<40)
                return notify_fail("��̫���ˣ���Ϣ�°ɡ�\n");

        if ( (int)me->query_temp("caiyao")==2)
                return notify_fail("�������֣���ȥ���˰ɡ�\n"); 
        message_vision("$Nſ�ڵ��ϣ��ɴ����۾��ڲݴ�����Ѱ��ҩ�ݣ�����©����Ŀ�ꡣ\n",me); 
        remove_call_out("cai"); 
        call_out("cai", 5, me);
        me->start_busy(3); 
        return 1;
}
 
int cai(object me)
{ 
        object ob;
        object ob1;        
        if (random(10)<7)
        {
        me->receive_damage("jing",10+random(20));
        me->receive_damage("qi",10+random(20));   
        message_vision(CYN"һ�������󣬲ݴ����ƺ�û��$NҪ�ҵĶ�����$Nʧ����̾�˿�����\n"NOR,me);
        }

        if(random(6)==1) 
        {         
        tell_room(environment(me),HIR"�ݴ���һ��ζ���ͻȻ���һ�����ߡ�\n"NOR );
        ob=new("/d/beijing/npc/liandan_dushe");
        ob->move("/d/beijing/liandan_lin7");
        }

   else if(random(6)==1) 
        {         
        tell_room(environment(me),HIR"���Ӻ���ͻȻ����һ�������ɲ�����ӣ�����һ�Ѷ̵�����������\n"NOR );
        ob=new("/d/beijing/npc/liandan_langzhong");
        ob->move("/d/beijing/liandan_lin7");
        }

   else
        { 
        ob1 = new("/d/beijing/npc/dan/caoyao");
        ob1->move(me);
        me->receive_damage("jing",10+random(20));
        me->receive_damage("qi",10+random(20));
        me->add_temp("caiyao", 1);
        message_vision(HIG"$N���˰��죬���ڷ�������һ������������Ĳ����в�ͬ��
С������ؾ��˳�����\n"NOR,me); 
        }
        return 1;
       
}

