// guozhuang.c
// Date: Nov.1997 by Venus
// Updated by Rama 

#include <ansi.h>
#include <room.h>
inherit ROOM;
int do_knock(string arg);
int do_open(string arg);

void create()
{
        set("short", "��ׯ");
        set("long", @LONG
ׯ԰�Ĵ������ǡ���ׯ���������֡�����(gate)���գ����澲��
�ĵ�һ��������û�С�
LONG);
        set("exits", ([
            "east"      : __DIR__"dadao1",
        ]));
        set("item_desc", ([
           "gate" : "���Ĵ��Ž����ţ�����(knock)���ɡ�\n"
        ]));

//        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="gate")
        return notify_fail("�������������ţ����һ�㶯����û�У������Ǵ����淴���ˡ�\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("��Ҫ��ʲô��\n");
          if (arg != "gate")
                return notify_fail("��Ҫ��ʲô��\n");
          if( arg=="gate" ) {
                message_vision("$N�����������š�\n", me);
                if (me->query("bang_bad/name")!="С����" && (int)me->query("shen") <= 0)
                {
                        message_vision(HIB"����֨ѽһ�����ˣ�������̽����ͷ��������$N����˵����������Ͷ������С����İɣ�����
˵��һ�Ѱ�$N���˽�ȥ��\n"NOR, me);
                        me->move(__DIR__"xdh_hzfb");
                        return 1;
                }
                if( me->query("bang_good") || (int)me->query("shen") > 0 ) 
                { 
                        message_vision("����֨ѽһ�����ˣ�������̽����ͷ��������$N����˵��������������Ҳ�����ˣ���Ĳ��ͷ���ô����\n�ű����صĹ����ˡ�\n",me);  
                        return 1; 
                } 
                message_vision("����֨ѽһ�����ˣ�������̽����ͷ��������$N����˵��������Ȼ�Ǳ�����ֵܣ��ͽ����ɣ�����
˵��һ�Ѱ�$N���˽�ȥ��\n",me);
                me->move(__DIR__"xdh_hzfb"); 
                return 1; 
        }
        
        return 1;
}
