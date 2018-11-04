// jiangong �๤

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();
int  do_move(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("�๤", ({ "jian gong", "jiangong" }));
        set("long", "����һ���๤���۹ⲻ����˸����֪"
                    "���ڴ�ʲô������\n");
        set("gender", "����");
        set("age", 38);
        set("no_get", 1);
        set_skill("unarmed", 100);

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);

        set("combat_exp", 500000);
        set("shen_type", 1);
        set("inquiry", ([
            "����" : (: ask_job :),
            "��ʯ" : (: ask_job :),
            "job"  : (: ask_job :),
        ]));
        setup();

        set("chat_chance", 1);
        set("chat_msg", ({
                "�๤�ȵ����죡����Ҹɣ�\n",
                "�๤һ����ӣ�����������̵ģ�����ҷ���ʵ�㡣\n",
                "�๤���������ܣ���֪���ڴ�ʲô���⡣ \n",
                "�๤�ݺݵĳ���һ���˼��£��������ô��ʯͷ���������ˣ����Ɀ����\n",
        }) );
}

void init()
{
        add_action("do_move", "move");
}

string ask_buy()
{
        return "������в��ٶ����˱ض�����Ӵ!\n";
}

string ask_job()
{
	object *uob;
        object me;

        me = this_player();
        if (me->query_temp("job/move"))
                return "������ʯ�������û�У��ٺ����ҳ����㣡";

        if (me->query("combat_exp") < 1500)
                return "����㾭��Ҳ����ʯ���죿���һ��翴�㲻˳�۾Ͱ���ŵ��ˡ�";

        if (me->query("combat_exp") > 15000)
                return "������Ҳ����ʯͷ���������ˣ��һ��������˰ɣ�";

        if (me->query("qi") < 60)
                return "�ҿ�������������������������˰ɣ��ҿɲ����ֳ���������";

        if (me->query_str() < 25)
                return "��˵���ж��������Ҳ�������֣�";

        uob = filter_array(users(), (: query_ip_name($1) == $(query_ip_name(me)) :));
	uob = filter_array(uob, (: objectp($1) && $1->query_temp("job/move") :));

	if (sizeof(uob) > 5)
	{
		me->start_busy(3);
		return "�Բ��������IP����ʯ������ID̫���ˣ�";
	}

        me->set_temp("job/move", 1);
        return "�ã����ȥɽ�ϰ�ʯ������(move)�����⹤�ʿɲ���Ŷ��";
}

int do_move(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("����æ���أ����ż���\n");

        if (! me->query_temp("job/move"))
                return notify_fail("����û��Ϲæ��ɶ��\n");

        me->set_temp("job/step", 1);
	me->start_busy((: working :), (: halt_working :));
        tell_object(me, "�㿪ʼ������\n");
        return 1;
}

int working(object me)
{
        string msg;
        int finish;
        int b;

        if (! me->query_temp("job/step"))
                me->set_temp("job/step", 1);

        if (! living(me))
        {
                me->delete_temp("job/move");
                me->delete_temp("job/step");
                return 0;
        }

        finish = 0;
        switch (me->query_temp("job/step"))
        {
        case 1:
                me->receive_damage("qi", 3);
                msg = "$N�첽�ĳ�ɽ����ȥ��";
                break;
        case 2:
                me->receive_damage("qi", 2);
                msg = "$N�ߵ�ɽ����������������ʯ�ϵġ�";
                break;
        case 3:
                me->receive_damage("qi", 2);
                msg = "�����Ĺ���ɨ��$Nһ�ۣ��ƺ�û������һ�������ֵ����ˣ��Ƕ���ȥ�Ƕ��ᡣ";
                break;
        case 4:
                me->receive_damage("qi", 8);
                msg = "$N�ϵ����Ƶĵط���ѡ��һ���������Լ���ʯ�ϣ����ڼ�ͷ��";
                break;
        case 5:
        case 7:
        case 9:
                me->receive_damage("qi", 10);
                msg = "$N����ʯ�ϣ�һ��һ����ɽ�°���";
                break;
        case 6:
                me->receive_damage("qi", 12);
                msg = "$N���˿��������˵��ͷ��ʯ�ϣ�����ǰ����";
                break;
        case 8:
                me->receive_damage("qi", 15);
                msg = "$N���ü�ͷ��ʯ��Խ��Խ�أ�ֻ�û�һ�¼翸��";
                break;
        default:
                me->receive_damage("qi", 8);
                msg = "$N��ʯ�Ͽ���$n�����ʯ��װ�ϳ��ӣ��������˿�����";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                object ob;
                if (me->query_str() >= 30)
                        msg += "$n����$N���ʯ�ϣ��ȵ�������"
                               "������ô���ʯ��Ҳ�������ˣ�\n";
                else
                        msg += "$n����$N���ʯ�ϣ������У��ɵ�"
                               "����������������Ĺ�Ǯ��\n";
                me->delete_temp("job/move");
                me->delete_temp("job/step");

                b = 7 + random(4);
                me->add("combat_exp", b);
                me->add("potential", (b + 2) / 3);
                me->improve_skill("unarmed", (b + 1) / 2);
                if (me->query("potential") > me->query_potential_limit())
                        me->set("potential", me->query_potential_limit());

                ob = new("/clone/money/coin");
                ob->set_amount(100 + (me->query_str() - 25) * 10);
                ob->move(this_object());
        }

        message_vision(msg, me, this_object());
        if (finish)
        {
                if (b > 0)
                {
                        tell_object(me, HIC "\n������" +
                                    chinese_number(b) +
                                    "�㾭���" +
                                    chinese_number((b + 2) / 3) +
                                    "��Ǳ�ܡ�\n\n" NOR);
                }
                command("give coin to " + me->query("id"));
                command("drop coin");
                return 0;
        }

        me->add_temp("job/step", 1);
        return 1;
}

int halt_working(object me)
{
        if (me->query_temp("job/step") >= 4)
        {
                message_vision("$N�Ѽ�ͷ��ʯ��һ�ԣ��������ֵ���"
                               "�������ˣ��治���˸ɵĻ\n", me);
        } else
        {
                message_vision("$N̾�˿������������첻���ˣ�\n", me);
        }

        me->delete_temp("job/move");
        me->delete_temp("job/step");
        return 1;
}
