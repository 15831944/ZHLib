// wuluo-zhang.c ����������
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action": "$Nһ�������һ�С����б�꡹ֱϮ$n��$l�����ް��ۼ�",
    "force" : 30,
    "dodge" : 30,
    "lvl"   : 0,
    "skill_name" : "���б��",
    "damage_type": "����"
]),
([  "action": "$Nת������������һ�С��������ϡ��������㣬���ƻ���$n������",
    "force" : 50,
    "dodge" : 40,
    "damage": 5,
    "lvl"   : 10,
    "skill_name" : "��������",
    "damage_type": "����"
]),
([  "action": "$N�鲽����һ�С���Ҷ���⡹������һת������$n",
    "force" : 60,
    "dodge" : 45,
    "damage": 10,
    "lvl"   : 20,
    "skill_name" : "��Ҷ����",
    "damage_type": "����"
]),
([  "action": "$Nһ�С���·δ������˫�ƻ���������Ӱ����ƮƮ������$n",    
    "force" : 70,
    "dodge" : 55,
    "damage": 15,
    "lvl"   : 34,
    "skill_name" : "��·δ��",
    "damage_type": "����"
]),
([  "action": "$Nһ�С������������������ָ΢΢�ſ�������$n������",
    "force" : 90,
    "dodge" : 70,
    "damage": 20,
    "lvl"   : 45,
    "skill_name" : "�������",
    "damage_type": "����"
]),
([  "action": "$Nת���ͷ������һЦ��ʹ��һ�С���ң���䡹��һ���ĳ����·�ʳ����˼��̻�",  
    "force" : 110,
    "dodge" : 75,
    "damage": 25,
    "lvl"   : 59,
    "skill_name" : "��ң����",
    "damage_type": "����"
]),
([  "action": "$N����Ʈ����һ�С�������������˫�������������$n",
    "force" : 120,
    "dodge" : 80,
    "damage": 30,
    "lvl"   : 80,
    "skill_name" : "��������",
    "damage_type": "����"
]),
});

int valid_enable(string usage)
{
    	return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
    	return combo == "jinyu-quan";
}

mapping query_action(object me, object weapon)
{
        int i, j, pm, level;
       	object target;
	string *msg;

	level   = (int) me->query_skill("wuluo-zhang",1);
	pm = me->query_temp("piaomiao");
	target = me->select_opponent();
	weapon = me->query_temp("weapon");

	msg = ({ 
		HIM"\n$N��ɫ���죬������ͻ���죬һ�п���һ�С�\n"NOR,
                HIW"\n$N������ɢ���İ���ͻȻת"NOR GRN"��"NOR HIW"�����־���Ҳת������һ�֣������ھ���������������������\n"NOR,
                HIR"\n$N��ɫ����תΪ���죬���������������ھ����������������Χ��˫���������д���������ʽҲԽ��Խ�࣡\n"NOR,
                HBWHT BLK"\nֻ��$N���ϼ���ͻȻή���������ľ�������鶯��������ͻ��Ȼ���죡\n"NOR,
	});

	if( pm > 1 && pm < 6 && !me->query_temp("piaomiao_attack")) {

		message_vision( msg[pm-2] , me, weapon);
		me->set_temp("piaomiao_attack", 1);
		for( j=0; j < pm-1; j++ )
		{
			me->add("neili", -50);
			COMBAT_D->do_attack(me, target, weapon);
		}
		me->delete_temp("piaomiao_attack", 1);
		me->add_temp("piaomiao", 1);

	}

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_learn(object me)
{
	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wuluo-zhang", 1))
		return notify_fail("��Ļ����Ʒ�������ޣ��޷�������������������ơ�\n");

	return 1;
}

int practice_skill(object me)
{
    	if ((int)me->query("qi") < 50)
        	return notify_fail("�������̫���ˣ����������������ơ�\n");

    	if ((int)me->query("neili") < 30)
        	return notify_fail("�������̫���ˣ����������������ơ�\n");

    	me->receive_damage("qi", 40);
    	me->add("neili", -13);

    	return 1;
}
string perform_action_file(string action)
{
        return __DIR__"wuluo-zhang/" + action;
}

