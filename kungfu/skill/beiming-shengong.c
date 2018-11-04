// beimin-shengong.c ��ڤ��
// By Hop
// Update by smallbear 03.04.29

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_force(string force)
{
        return force == "xiaoyao-xinfa" ||
               force == "xiaowuxiang";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("beiming-shengong", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("beiming-shengong", 1);

        if (me->query("gender") == "����" && lvl > 49)
                return notify_fail("���޸����ԣ���������������������ı�ڤ�񹦡�\n");

        if (me->query("int") < 32)
                return notify_fail("����ñ�ڤ�񹦼����ޱȣ�������ᡣ\n");

        if (me->query("con") < 24)
                return notify_fail("��������ת��һ����������ǰ��ʱһ�ڣ�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("��ڤ��ֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}

mixed hit_by(object me, object victim, int damage, int damage_bonus, int factor)
{
        int percent,force1,force2,dodge1,dodge2,lv1,lv2;

        force1 = victim->query_skill("force"); 
        force2 = me->query_skill("force"); 
        dodge1 = victim->query_skill("dodge"); 
        dodge2 = me->query_skill("dodge"); 

        lv1= force1*dodge1;
        lv2= force2*dodge2;

        lv2 = lv2*3/2;
        if ((int)victim->query_skill("beiming-shengong",1)>100
         && !me->query_temp("weapon")
         && me->query("max_neili")>500
        && lv1/2 + random(lv1) > lv2 )
        {
                victim->add("max_neili", 1*(5+((int)victim->query_skill("beiming-shengong",1)/100)));
                me->add("max_neili", -1*(5+((int)victim->query_skill("beiming-shengong",1)/100)));

                if (victim->query("max_neili") > (int)victim->query_skill("force") * (int)victim->query("con") * 2 / 3 * 2)
                        victim->set("max_neili",victim->query_skill("force") * (int)victim->query("con") * 2 / 3 * 2);

                return ([ "msg": HIR "$N��������һ�����У�ȴ����ֻ��Ϣ��һ����һ��������$n���˹�ȥ��\n" NOR ]);
        }
        
        return damage;
}

string exert_function_file(string func)
{
    return __DIR__"beiming-shengong/" + func;
}

