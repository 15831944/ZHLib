// huashan-sword.c
// Modified by Venus Oct.1997
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "name"  : "�з�����",
        "action": "$Nʹһ�С��з����ǡ�������$w���Ⱪ������$n��$l��ȥ",
        "force" : 70,
	"attack": 10,
	"parry" : 5,
        "dodge" : 10,
        "damage": 30,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "name"  : "�ޱ���ľ",
        "action": "$N������ת��һ�С��ޱ���ľ������$n��$l",
        "force" : 120,
	"attack": 20,
	"parry" : 15,
        "dodge" : 20,
        "damage": 40,
        "lvl"   : 20,
        "damage_type":  "����"
]),
([      "name"  : "���ڤڤ",
        "action": "$N�趯$w��һ�С����ڤڤ��Ю�������������$n��$l",
        "force" : 160,
	"attack": 25,
	"parry" : 20,
        "dodge" : 30,
        "damage": 55,
        "lvl"   : 40,
        "damage_type":  "����"
]),
([      "name"  : "ƽɳ����",
        "action": "$N����$w����һ����������ƽɳ���㡹��$n��$l�̳�����",
        "force" : 190,
	"attack": 30,
	"parry" : 28,
        "dodge" : 35,
        "damage": 70,
        "lvl"   : 60,
        "damage_type":  "����"
]),
([      "name"  : "��������",
        "action": "$N����$w���Ⱪ����һ�С��������á���$n$l��ȥ",
        "force" : 220,
	"attack": 40,
	"parry" : 33,
        "dodge" : 40,
        "damage": 90,
        "lvl"   : 80,
        "damage_type":  "����"
]),
([      "name"  : "�׺����",
        "action": "$N����$w����һ���⻡��ֱָ$n$l��һ�С��׺���ա���������������ȥ",
        "force" : 260,
	"attack": 50,
	"parry" : 40,
        "dodge" : -20,
        "damage": 110,
        "lvl"   : 100,
        "damage_type":  "����"
]),
});

int can_not_hubo() {return 1;}
int valid_learn(object me)
{
    object ob;

    if ((int)me->query("max_neili") < 100)
        return notify_fail("�������������û�а취����ɽ������\n");

    if (! (ob = me->query_temp("weapon"))
    ||  (string)ob->query("skill_type") != "sword" )
        return notify_fail("���������һ�ѽ�����ѧϰ������\n");

    if (me->query_skill("sword", 1) < me->query_skill("huashan-sword", 1))
	return notify_fail("��Ļ�������������ޣ��޷���������Ļ�ɽ������\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, count, level, lvl, used;
        object target;
	string *msg = ({});

	if (!weapon)
		weapon = me->query_temp("weapon");

        if (!me || !weapon)
	{
	        for (i = sizeof(action); i > 0; i--)
        	        if (level > action[i-1]["lvl"])
                	        return action[NewRandom(i, 20, level/5)];
	}

        msg =
        ({ 
                HIC"\n$N����һ������һ����������ķ���ҲԽ��Խǿ��\n"NOR,
                HIW"\n$N��������������һ�ɾ���������չ��$nֻ���������ˣ����ϡ����ϱ�����ε��������ۡ�\n"NOR,
                HIR"\n$N����һ�죬����ɽ�������ӵ����쾡��,����"+(weapon?weapon->name():"����")+HIR"��ʹ�����缲������һ�㡣��\n"NOR,
                HIY"\n$N��һ����������"+(weapon?weapon->name():"����")+HIY"�����������Σ�һ������һ����������װ㹥�ϣ�\n"NOR,
               
        });

	level = (int) me->query_skill("huashan-sword", 1);
	lvl = (int) me->query_skill("zixia-shengong", 1);
        used = me->query_temp("kuaijian");
        target = me->select_opponent();

	if (used > 20) me->set_temp("kuaijian",0);

        if(level >= 120 && 
           lvl >= 120 && 
           !me->query_temp("kuangfeng_kuaijian") && 
           used > 5 && 
           used < 10 &&
           target)
        {
                message_vision( msg[used-6] , me, target);
                me->set_temp("kuangfeng_kuaijian", 1);
                for( count=0; count < used - 4; count++ )
                {
                        me->add("jingli", 0);
                        me->add("neili", -20);
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
                }
                me->delete_temp("kuangfeng_kuaijian");
        }

	if( !me->query_temp("kuangfeng_kuaijian"))
                me->add_temp("kuaijian", 1);

        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("�������̫�ͣ�û�а취��ϰ��ɽ������\n");
                
    if ((int)me->query("neili") < 40)
        return notify_fail("�������������û�а취��ϰ��ɽ������\n");

    if (!me->query_temp("weapon") || me->query_temp("weapon")->query("skill_type") != "sword")
	return notify_fail("�㲻�Ұѽ�������ô��ϰ��ɽ������\n");

    if (me->query_skill("sword",1) < me->query_skill("huashan-sword",1))
	return notify_fail("��Ļ�������̫���ˡ�\n");

    me->receive_damage("qi", 50);
    me->add("neili", -31);
    return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string action)
{
        return __DIR__"huashan-sword/" + action;
}
