//Room: leidongping.c �׶�ƺ
//Date: Oct. 2 1997 by That
#include <ansi.h>
inherit ROOM;

void create()
{
      set("short","�׶�ƺ");
      set("long",@LONG
�׶�ƺһ������·���պ��ˣ�·���Ǳ����������ɼ�֣�·���������
�ľ���Ͽ�ȡ����ﳤ���������֣����ɺڰ������Ͻ��������Ա���һ������
�ɴ������ǡ���ʮ���̡�����������µ�ϴ��ء�
LONG);
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
          "northdown"  : __DIR__"lingyunti",
          "southup"    : __DIR__"bashisipan1",
          "east"       : __DIR__"lengsl1",
      ]));
      setup();
}

int valid_leave(object me, string dir)
{
        int c_exp,c_skill;
        me = this_player();
        if (dir == "southup" )
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

