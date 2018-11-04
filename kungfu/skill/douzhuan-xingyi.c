// douzhuan-xingyi ��ת����

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
        "ֻ�������ϡ�һ����$n��$p����һ�У�������$N��һ����\n",
        "���Ǳ�$n�����б���ж����\n",
        "����$n����һ�࣬����ת�����е�$p����$N�о���������ʩ��\n",
});

string *unarmed_parry_msg = ({
        "���Ǳ�$p˫��һ�ƣ�$N�Ĺ��ƶ�ʱ���˷���\n",
        "$n����һת��$Nֻ���õ����е�����ȫ�����䵽�˿մ���\n",
        "����$N�о�����޻���һ����˵�����Ĺ��졣\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int valid_enable(string usage) { return usage == "parry"; }
int can_not_hubo() {return 1;}

int valid_learn(object me)
{
        if ((int)me->query_skill("zihui-xinfa", 1) < 100)
                return notify_fail("����ϻ��ķ���򻹲���������ѧϰ��ת���ơ�\n");

        if ((int)me->query_skill("parry", 1) < 100)
                return notify_fail("��Ļ����мܼ������յĻ������������޷�ѧϰ��ת���ơ�\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��ת����ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed valid_damage(object target, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        if ((int) me->query_skill("douzhuan-xingyi", 1) < 100)
        return;

        if (!living(me) || (me->is_busy() && random(3) == 0)) return;
        dp = target->query_skill("force", 1);
        ap = me->query_skill("douzhuan-xingyi", 1);

        if (ap / 2 + random(ap) > dp)
        if ((int) me->query_skill("zihui-xinfa", 1) < 280)
        {
                result = ([ "damage" : -damage ]);

                switch(random(5))
                {
                case 0:
                        result += ([ "msg" : HIY "$N" HIY "ֻ����ȫ���ܵ������𵴣�"
                                             HIY "��ɫ��Ĳ԰ס�\n" NOR ]);

                        message_vision(HIR "\n$N" HIR "������������ͼ��"
                                       HIR "$n" HIR "�Ĺ���ת��"
                           HIR "$n" HIR "�Լ�����!\n\n"NOR,me,target);
                        target->receive_damage("qi", damage / 5);
                        me->add("neili", -30);
                        break;
                case 1:
                        result += ([ "msg" : HIC "$n" HIC "����һ�У�$N"
                                             HIC "��ʱ����׼����������"
                                            "����һ�����������ĸо���\n" NOR ]);
                        break;
                case 2:
                        result += ([ "msg" : HIC "$n" HIC "����һת,"
                                             HIC "$N" HIC "ֻ���õ����е�����"
                                             HIC "ȫ�����䵽�˿մ���\n" NOR ]);
                        break;
                case 3:
                        result += ([ "msg" : HIC "$n" HIC "˫��ǰ̽����۴���"
                                             HIC "$N" HIC "�ұۣ��ұ�ʹ��" HIC "$N"
                                             HIC "��������" HIC "$N" HIC "���л�ȥ ��\n" NOR ]);
                        break;
                default:
                        result += ([ "msg" : HIC "$N" HIC "һ���ۿ�������$n"
                                             HIC "��Ȼ��$n" HIC "����һж��"
                                             "��$N" HIC "�Ĺ������������Ρ�\n" NOR ]);
                        break;
                }
                       return result;
           }
      else
           {
                result = ([ "damage" : -damage ]);
                switch(random(6))
                {
                case 0:
                        result += ([ "msg" : HIY "$N" HIY "ֻ����ȫ���ܵ������𵴣���ɫ��Ĳ԰ס�\n" NOR ]);
                        message_vision(HIR "\n̸Ц�䣬" HIR "$N" HIR "��ʹ��" HIR "$n" HIR "��������,"
                                       HIR "��" HIR "$n" HIR "�Ĺ���ת��"
                           HIR "$n" HIR "�Լ�����!\n\n"NOR,me,target);
                        target->receive_wound("qi", damage / 4);
                        me->add("neili", -30);
                        break;
                case 1:
                        result += ([ "msg" : HIY "$N" HIY "��ôҲ�벻��" HIY "$n" HIY "�ܹ�ʹ���Լ��ĳ���������"
                                             HIY "ֻ����ȫ���ܵ������𵴣����İ��ʹ��һ����Ѫ���!!\n"NOR ]);
                        message_vision(HIR "\n��Ȼ���ذ���" HIR "$N" HIR "ʹ��" HIR "$n" HIR "�ľ��У�"
                                       HIR "�����������ڼ�������" HIR "$n" HIR "��ȥ��\n\n"NOR,me,target);
                        target->receive_wound("qi", damage / 2);
                        me->add("neili", -100);
                        break;
                case 2:
                        result += ([ "msg" : MAG "�����һ��������������" MAG "$n" MAG "һ��һ����"
                                             MAG "$n" MAG "��������Խ����������һ�ԡ�\n" NOR ]);
                        message_vision(HIR "\n" HIR "$N" HIR "����Ʈ����˫�����裬ȴ��" HIR "$n" HIR "�ľ��У�"
                                       HIR "�������ϲ�������" HIR "$n" HIR "��ȥ��\n\n"NOR,me,target);
                        target->receive_wound("qi", damage / 3);
                        me->add("neili", -50);
                        break;
                case 3:
                        result += ([ "msg" : MAG "����һ����������" MAG "$N" MAG "��" MAG "$N" MAG "����"
                                             MAG "$n" MAG "������"
                                             MAG "Ī��������ﻬ��һ�� ��\n" NOR ]);
                        break;
                case 4:
                        result += ([ "msg" : MAG  "$N" MAG  "һ���ۿ�������$n"
                                             MAG "��Ȼ��$n" MAG  "����һж��"
                                             "��$N" MAG "�Ĺ������������Ρ�\n" NOR ]);
                        break;
                default:
                        result += ([ "msg" : MAG "ֻ�������ϡ�һ����" MAG "$n" MAG "��������һ�У�"
                                             MAG "������" MAG "$N" MAG "��һ����\n" NOR ]);
                        break;
                }
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}
