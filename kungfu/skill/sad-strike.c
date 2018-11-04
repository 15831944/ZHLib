inherit SKILL;

#include <ansi.h>

mapping *action = ({
([      "action" : "$Nһ�С�"HIW"�������"NOR"��̧ͷ���죬��������������һ��"
                   "���Լ�ͷ���տ��ĳ�������б�£��������ɻ�\n"
                   "�Σ���ɢ��������$n��$l",
        "force"  : 40,
        "attack" : 40,
        "dodge"  : 40,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "�������",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"HIG"��������"NOR"���ֱ��´������ް�������ʽ��"
                   "ͻȻ�������붯���������䡢˫��ͷ��������\n"
                   "�ر�������������ʽ����ײ��$n",
        "force"  : 50,
        "attack" : 45,
        "dodge"  : 45,
        "damage" : 25,
        "lvl"    : 10,
        "skill_name" : "��������",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"HIB"�����ˮ"NOR"����������Ʈ����������ˮ������"
                   "ȴ����֮�������ƴ��ż�ǧ����ɳһ�㣬����\n"
                   "�빥$n",
        "force"  : 60,
        "attack" : 50,
        "dodge"  : 50,
        "damage" : 30,
        "lvl"    : 20,
        "skill_name" : "�����ˮ",
        "damage_type": "����"
]),

([      "action" : "$Nһ�С�"HIY"��������"NOR"�������ո���ͷ�������£��Ų���"
                   "�أ����������������$n��$l",
        "force"  : 70,
        "attack" : 55,
        "dodge"  : 55,
        "damage" : 35,
        "lvl"    : 40,
        "skill_name" : "��������",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"HIR"��ʬ����"NOR"���߳�һ�š���һ�ŷ���ʱ�л��"
                   "㱣�����ԼԼ���������޵�����$n",
        "force"  : 90,
        "attack" : 60,
        "dodge"  : 60,
        "damage" : 40,
        "lvl"    : 60,
        "skill_name" : "��ʬ����",
        "damage_type": "����"
]),
([      "action" : "$N˫��ƽ�У�һ�С�"HIM"ӹ������"NOR"��û����ɵ�����$n��$l",
        "force"  : 100,
        "attack" : 70,
        "dodge"  : 65,
        "damage" : 45,
        "lvl"    : 80,
        "skill_name" : "ӹ������",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"RED"������ʩ"NOR"��ͻȻ�������࣬ͷ�½��ϣ�����"
                   "���ӣ�һ������$n��$l",
        "force"  : 120,
        "attack" : 80,
        "dodge"  : 70,
        "damage" : 50,
        "lvl"    : 100,
        "skill_name" : "������ʩ",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"YEL"�ľ�����"NOR"����ĿԶ���������鸡����ǰ�Ż�"
                   "������ȫ����ʽ����ѧ�и������޲��Ǻ�",
        "force"  : 140,
        "attack" : 90,
        "dodge"  : 75,
        "damage" : 55,
        "lvl"    : 120,
        "skill_name" : "�ľ�����",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"BLU"������ʳ"NOR"�������鸡�����缸�첻�Բ�˯��"
                   "�ĽŲ��ʲյ�Ϯ��$n�����ԣ����ƺ���ȭ��\n"
                   "��$n��$l",
        "force"  : 160,
        "attack" : 100,
        "dodge"  : 80,
        "damage" : 60,
        "lvl"    : 140,
        "skill_name" : "������ʳ",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"HIC"�ǻ��չ�"NOR"�����Ҵ�����ʵʵ�Ĺ���$n��$l",
        "force"  : 190,
        "attack" : 110,
        "dodge"  : 85,
        "damage" : 65,
        "lvl"    : 160,
        "skill_name" : "�ǻ��չ�",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"CYN"��������"NOR"������������״������бб����$n��$l",
        "force"  : 220,
        "attack" : 125,
        "dodge"  : 90,
        "damage" : 90,
        "lvl"    : 70,
        "skill_name" : "��������",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"MAG"���񲻰�"NOR"���������ݼ�ת��չ���ṦΧ��$n"
                   "�������ߣ���Ȼ�����������$n��$l",
        "force"  : 250,
        "attack" : 140,
        "dodge"  : 95,
        "damage" : 75,
        "lvl"    : 200,
        "skill_name" : "���񲻰�",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"WHT"��;ĩ·"NOR"������$n���ԣ����ƾٵ���ǰƽ"
                   "�ƶ�������������бб����$n��$l",
        "force"  : 270,
        "attack" : 140,
        "dodge"  : 100,
        "damage" : 80,
        "lvl"    : 220,
        "skill_name" : "��;ĩ·",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"HIY"����ľ��"NOR"��˫Ŀֱֱ�Ķ���$n�����嶯Ҳ��"
                   "��һ�µķ���$n",
        "force"  : 290,
        "attack" : 150,
        "dodge"  : 105,
        "damage" : 85,
        "lvl"    : 240,
        "skill_name" : "����ľ��",
        "damage_type": "����"
]),
([      "action" : "$N��ͷڤ�룬һ�С�"HIB"������ʧ"NOR"����������ƽƽ����$n"
                   "��$l",
        "force"  : 320,
        "attack" : 150,
        "dodge"  : 110,
        "damage" : 90,
        "lvl"    : 260,
        "skill_name" : "������ʧ",
        "damage_type": "����"
]),
([      "action" : "$Nһ�С�"HIB"��ͨ�˴�"NOR"��˫�ƻγ�ǧ����Ӱ��$n��������"
                   "��֮��",
        "force"  : 360,
        "attack" : 150,
        "dodge"  : 115,
        "damage" : 95,
        "lvl"    : 280,
        "skill_name" : "��ͨ�˴�",
        "damage_type": "����"
]),
([      "action" : "$N����ǰ��һ�С�"HIB"¹��˭��"NOR"���������ȣ��Կ������"
                   "һ��ת���Ѿ�ת����$n�������ָ����\n"
                   "��$n�Ĵ�׵Ѩ",
        "force"  : 400,
        "attack" : 150,
        "dodge"  : 120,
        "damage" : 100,
        "lvl"    : 300,
        "skill_name" : "¹��˭��",
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry" || usage=="unarmed"; }

int valid_learn(object me)
{
        if (me->query("gender") != "����") 
                return notify_fail("����᲻������˼��һ���˵����顣\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����Ȼ�����Ʊ�����֡�\n");

        if ((int)me->query("max_neili") < 2000)
                return notify_fail("�������̫�����޷�����Ȼ�����ơ�\n");

        if ((int)me->query_str() < 45)
                return notify_fail("��ı���̫�����޷�����Ȼ�����ơ�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("sad-strike", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 160)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("���������������Ȼ�����ơ�\n");

        me->receive_damage("qi", 150);
        me->add("neili", -85);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 300) return 0;

          if (random(10) > 4) 
        {
                victim->receive_wound("qi", (damage_bonus - 300) / 3);
                return HIR "ֻ��" + victim->name() +
                       HIR "һ���ƺߣ����ۡ��������һ�����Ѫ��\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"sad-strike/" + action;
}


