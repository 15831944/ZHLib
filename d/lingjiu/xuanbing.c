//ROOM xuanbing.c

inherit ROOM;



void init();
int do_climb(object me);



        
void create()
{
        set("short","������");
        set("long",@LONG
���������ڹ��ĵط��� ����������һ��ǧ������(ice)������ð��˿
˿������ ������˺������ˣ��㲻�ɵô���һ��������
LONG
        );
        
        set("exits", ([
                "east" : __DIR__"changl13",
        ]));

        set("item_desc", ([
            "ice" : "����һ�������ɽ֮�۵�ǧ������,��˵������������°빦��.\n�����������(climb)��ȥ.\n",
        ]));

        set("coor/x",-130);
        set("coor/y",130);
        set("coor/z",70);
        setup();
}


void init()
{
        add_action("do_climb", "climb");
        
}

int do_climb(object me)
{      
        me=this_player();
        if(!me->query_skill("bahuang-gong", 1)||(int)me->query_skill("bahuang-gong", 1) < 10)
           {
                write("��İ˻�����Ψ�Ҷ�����Ϊ���������������溮��\n");                   
                message_vision("$N�Ѿ�������������,��������òҲҵģ��Ͻ�����������\n",me);
                return 1; 
          }
        
        message_vision("$N�Ѿ�������������,���ڴ������������ˡ�\n",me);
        
        me->set_temp("ice", 1);

        me->move("d/lingjiu/ice");
        return 1;
}

        
        


