// lingboweibu.c �貨΢��

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
        "����$n����Ʈ��������һ�ݣ����ѱܿ���\n",
        "$n������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
        "����$n����һ�ã�$N��һ�����˸��ա�\n",
        "ȴ��$n�㲻��أ����Դܿ����ߣ����˿�ȥ��\n",
        "$n����΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage) 
{ 
        return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me) { return 1; }
int can_not_hubo() {return 1;}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        if ((int)me->query_skill("lingbo-weibu", 1) < 100 )
                return;

        if (!living(me) || (me->is_busy() && random(3) == 0)) return;

        dp = ob->query_skill("force", 1); 
        ap = me->query_skill("lingbo-weibu",1);

          if (ap / 2 + random(ap) > dp)


        {
                result = ([ "damage" : -damage ]);

                   switch (random(2))
                {
                case 0:
                        result += (["msg" : HIW "ֻ��$n" HIW "΢΢һЦ����������ζ���$N"
                                            HIW "��ǰ��ʱ������������$n" HIW "�Ļ�Ӱ����$N"
                                            HIW "��ȫ�޷������ʵ��\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "����$n" HIW "����һԾ���Ѳ�������Ӱ��$N"
                                            HIW "���д󺧣�ȴ�ּ�$n" HIW "���籼��������"
                                            "֮���ɣ��������˷�����˼��\n" NOR]);
                        break;
                }
                return result;
        }
}


string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}


int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("�������̫���ˣ��������貨΢����\n");

        if ((int)me->query("neili") < 50)
                return notify_fail("�������̫���ˣ��������貨΢����\n");

        me->receive_damage("qi", 50);
        me->add("neili", -30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingbo-weibu/" + action;
}


