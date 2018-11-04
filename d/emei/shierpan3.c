//Room: shierpan3.c ʮ����
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
      set("short","ʮ����");
      set("long",@LONG
����ʯ�׶��۶��䣬�ųơ�ʮ���̡������·���и������أ�����������
���л���(clap)���ɴ����Ͽɴﻪ�϶��������������֡�
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
          "eastdown"  : __DIR__"shierpan2",
          "southwest" : __DIR__"shierpan4",
      ]));
      set("no_clean_up", 0);
      setup();
}
void init()
{
      add_action("do_clap", "clap");
}

int do_clap()
{
      message_vision("���ں�Ȼ���ܴ���һ��������Ⱥ�ܴ�"
                     "����ϣ��������һ�ܴ�����Ⱥ�ܱ��Ȼ\n"
                     "��ֹ����������Ϊ�ˡ�\n", this_player());
      return 1;
}

int valid_leave(object me, string dir)
{
        int c_exp,c_skill;
        me = this_player();
        if (dir == "southwest" )
        {
                c_exp   = me->query("combat_exp");
                c_skill = me->query_skill("dodge",1);
                if (me->query("qi") > 10)
                {
                        if (((c_skill*c_skill*c_skill/10) < c_exp) &&
                            (c_skill<101))
                           me->improve_skill("dodge",
                                             (int)me->query_skill("dodge", 1) / 5);
                        tell_object(me,"�����ϰ�ʮ���̣���Щ���ˡ�\n");
                } else
                {
                        me->set("qi", 0);
                        tell_object(me, "��̫���ˣ���Ҳ�߲����ˡ�\n");
                        return notify_fail("����ЪЪ������·�ɡ�\n");
                }
      }
      return 1;
}

