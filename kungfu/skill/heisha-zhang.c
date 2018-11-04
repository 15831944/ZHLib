// /kungfu/skill/heisha-zhang.c ��ɳ��
// By Alf, Last Update 2002.03
// һ��������������š��������̡��ķ����ѡ����ھ�١���������

#include <ansi.h>
inherit SKILL;

mapping *action =
({
([
    "action":   "$N����׹�����һ����ʹ�С�һ��������������ɻ�$n��$l",
    "dodge": -10,
    "parry": -10,
    "force": 180,
    "damage_type": "����"
]),
([
    "action":   "$N����һ�٣�˫��һ��һʽ���������š������ҷ���$n��$l",
    "dodge": -20,
    "parry": -20,
    "force": 200,
    "damage_type": "����"
]),
([
    "action":   "$N������$nһת��һ�С��������̡�չ������$n��$l��������",
    "dodge": -10,
    "parry": -10,
    "force": 220,
    "damage_type": "����"
]),
([
    "action":   "$N��һ�䣬ʹ�С��ķ����ѡ�����Ӱǧ����ã��ͻ�$n��$l",
    "dodge": -30,
    "parry": -30,
    "force": 250,
    "damage_type": "����"
]),
([
    "action":   "$N����һת��ʹ��һʽ�����ھ�١���������Ӱ��ס��$n��$l",
    "dodge": -20,
    "parry": -20,
    "force": 280,
    "damage_type": "����"
]),
([
    "action":   "$N��Хһ����һʽ��������������˫�ƻ��裬���Ʋ���$n��$l",
    "dodge": -10,
    "parry": -10,
    "force": 300,
    "damage_type": "����"
]),
});

int valid_enable(string usage)
{
    return usage=="unarmed" || usage=="parry";
}

int valid_learn(object me)
{
    if(me->query_temp("weapon")||me->query_temp("secondary_weapon"))
        return notify_fail("����ɳ�Ʊ�����֡�\n");
    if((int)me->query("max_neili") < 100)
        return notify_fail("�������̫�����޷�����ɳ�ơ�\n");
    return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    if((int)me->query("qi")<40)
        return notify_fail("�������̫���ˡ�\n");
    if((int)me->query("neili")<10)
        return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
    me->receive_damage("qi",30);
    me->add("neili",-5);
    return 1;
}

mixed hit_ob(object me,object victim,int damage_bonus)
{
    if(random(me->query_skill("heisha-zhang"))>50)
        victim->apply_condition("heisha_poison",
        random(me->query_skill("heisha-zhang")/10)+1+victim->query_condition("heisha_poison"));
    if(damage_bonus<100)
        return 0;
    if(random(damage_bonus/2)>victim->query_str())
    {
        victim->receive_wound("qi",(damage_bonus-100)/2);
        return 
HIB"ֻ���á��项��һ�����죬"+victim->name()+"����"+me->name()+"��������õ����˳�ȥ��\n" NOR;
    }
}

string perform_action_file(string action)
{
    return "/kungfu/skill/heisha-zhang/" + action;}

