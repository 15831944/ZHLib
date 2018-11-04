// Room: /d/shaolin/hanshui1.c
// Date: YZC 96/01/19

#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_yell(string arg);
void reset();

void create()
{
        set("short", "��ˮ�ϰ�");
        set("long", @LONG
��ǰ��һ�����η����Ĵ�(river)���������������۾�����
�����ɴ���������������һ�����������̯����Ҿͽ������ڰ�
�ߣ���������֧һ��ľ�壬���ϰ����˻�������ĺ������㡣��
ȥ��Զ�����������Ϻӿڣ����ٹ����Ͷ�������ȴ��ɴ��ڶɡ�
LONG );
        set("exits", ([
                "south" : __DIR__"yidao2",
        ]));

        set("item_desc", ([
                "river" : "��������һҶС�ۣ�Ҳ��(yell)һ�����Ҿ���������\n",
        ]));

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));
        set("boat", 1);
        set("opposite", __DIR__"hanshui2");
        set("outdoors", "shaolin");
        setup();
}


/*�ڴ˸�Ǯ�ڶɻ������*/
/*���ȣ��ɴ����˰�������Ǯ������һ��ߺ�ȣ�������һӿ
 * ���룬СС�ɴ�Ƭ�̼��Խ���������εĺ��������ϱ���
 */
void init()
{
        add_action("do_dj", "dujiang");
        add_action("do_yell", "yell");
}

void check_trigger()
{
        object room;

        if (! query("exits/enter"))
        {
                if (! (room = find_object(__DIR__"duchuan")))
                        room = load_object(__DIR__"duchuan");
                if (room = find_object(__DIR__"duchuan"))
                {
                        if ((int)room->query("yell_trigger") == 0)
                        {
                                room->set("yell_trigger", 1);
                                set("exits/enter", __DIR__"duchuan");
                                room->set("exits/out", __FILE__);
                                message("vision", "һҶ���ۻ�����ʻ�˹�����������һ��̤��"
                                                  "����ϵ̰����Ա�˿�\n���¡�\n",
                                        this_object());
                                message("vision", "������һ��̤�Ű���ϵ̰����γ�һ������"
                                                  "�Ľ��ݡ�\n", room);
                                remove_call_out("on_board");
                                call_out("on_board", 15);
                        } else
                                message("vision", "ֻ���ý��������������������"
                                        "�����æ���š�����\n",this_object());
                } else
                       message("vision", "ERROR: boat not found\n", this_object());
        } else 
                message("vision", "����һֻ�ɴ��ϵ�������˵�������������أ������ɡ�\n",
                        this_object());
}


void on_board()
{
        object room;

        if (! query("exits/enter")) return;

        message("vision", "������̤�Ű��������������һ�㣬��������ʻȥ��\n",
                          this_object());

        if (room = find_object(__DIR__"duchuan"))
        {
                room->delete("exits/out");
                message("vision", "������̤�Ű���������˵��һ��������ඡ���"
                                  "���һ�㣬������\n����ʻȥ��\n", room );
        }
        delete("exits/enter");

        remove_call_out("arrive");
        call_out("arrive", 20);
}

void arrive()
{
        object room;

        if (room = find_object(__DIR__"duchuan"))
        {
                room->set("exits/out", __DIR__"hanshui2");
                message("vision", "����˵���������ϰ��ɡ����漴��һ��̤�Ű�"
                                  "���ϵ̰���\n",room );
        }
        remove_call_out("close_passage");
        call_out("close_passage", 20);
}

void close_passage()
{
        object room;

        if (room = find_object(__DIR__"duchuan"))
        {
                room->delete("exits/out");
                message("vision","������̤�Ű����������ѱ���ʻ���ġ�\n", room);
                room->delete("yell_trigger"); 
        }
}

int do_yell(string arg)
{
        string dir;

        if (! arg || arg == "" ) return 0;

        if (arg == "boat" ) arg = "����";
        if ((int)this_player()->query("age") < 16)
                message_vision("$Nʹ�����̵���������һ������" + arg + "��\n",
                               this_player());
        else
        if ((int)this_player()->query("neili") > 500)
                message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ��"
                               "�˳�ȥ��\n", this_player());
        else
                message_vision("$N������������Хһ������" + arg + "����\n",
                               this_player());
        if (arg == "����")
        {
                check_trigger();
                return 1;
        } else
                message_vision("������ԶԶ����һ���������" + arg +
                               "��������\n", this_player());
        return 1;
}

void reset()
{
        object room;

        ::reset();
        if (room = find_object(__DIR__"duchuan"))
                room->delete("yell_trigger"); 
}
int do_dj()
{
        object obj;
        int slsf;
        object me = this_player();
        slsf = me->query_skill("shaolin-shenfa",1);

        if (slsf < 180)
                  return notify_fail("����������������ң��޷�ʹ��"HIY"[һέ�ɽ�]"NOR"��\n");

        if (me->query("neili") < 100)
                  return notify_fail(HIR"�������ڵ�״̬��"HIY"[һέ�ɽ�]"HIR"��ˮ̫Σ�գ��㻹��������ȥ�ɡ�\n"NOR);

        if (me->is_busy())
                  return notify_fail("��������æ�ţ��޷��ɽ���\n");

        if (slsf >= 180){
        write(HIY"��ʹ�����־���[һέ�ɽ�]����������һԾ�Ѿ�׼ȷ����Ĳ�����һ��«έ��Ȼ��Ѹ�ٵ���԰�Ưȥ��\n"NOR);
        me->move("/d/shaolin/hanshui2");
        me->add("neili",-50);
        tell_room("/d/shaolin/hanshui2.c",HIG+me->query("name")+"���ϲ���һ��«έ���ٵ�Ư�˹�����\n"NOR);
        return 1;
        }
}
