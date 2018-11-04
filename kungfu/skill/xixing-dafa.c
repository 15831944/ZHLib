// xixing-dafa.c ���Ǵ�

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xixing-dafa", 1);
        return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xixing-dafa", 1);

        if (me->query("family/family_name") != "�������")
                return notify_fail("����������̾�ѧ���������ˡ�\n");

        if (me->query("character") == "��������")
                return notify_fail("�����а��������ֺ����书����ѧ��������\n");

        if (me->query("gender") == "����")
                return notify_fail("��ͻȻ�о���Ϣ���ң���������óȻ��ϰ�󷨡�\n");

        if (me->query("con") < 26)
                return notify_fail("�����Ű��շ�����ת��һ����Ϣ����Ȼ"
                                   "������������������ȴ��һ�������\n");

        if ( (int)me->query_skill("riyue-xinfa", 1) < 150 )
                return notify_fail("��������ķ��ȼ�̫�ͣ�����������ž�ѧ��\n");

        if (lvl >= 10 && lvl < 180 && me->query("max_neili"))
                return notify_fail("��û�а������Ǵ󷨵ľ��Ͻ���"
                                   "��ɢȥ�����ڻ��������Լ������д󷨡�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("���Ǵ�ֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}

mixed hit_by(object me, object victim, int damage, int damage_bonus, int factor)
{
        object weapon1 = me->query_temp("weapon");
        object weapon2 = victim->query_temp("weapon");

        int ap, dp;
        string skilltype,result;
        mapping prepare;

        dp = (int)victim->query_skill("xixing-dafa",1);
        if (dp<100) return damage;

        if (objectp(weapon2) ){
                skilltype=weapon2->query("skill_type");
                dp += victim->query_skill(skilltype,1);
        } else {
                prepare = victim->query_skill_prepare();
                if (! prepare) prepare = ([]);
                switch (sizeof(prepare))
                {
                        case 0: skilltype = "unarmed"; break;
                        case 1: skilltype = (keys(prepare))[0]; break;
                        case 2: skilltype = (keys(prepare))[victim->query_temp("action_flag")]; break;
                }
                dp += victim->query_skill(skilltype,1);
        }

        ap = me->query_skill("force",1);
        if (objectp(weapon1))
                ap += me->query_skill("parry");
        else
                ap += me->query_skill("dodge");

        if ( dp > ap/2 + random(ap) ) {
                if ( objectp(weapon2) && objectp(weapon1)) {
                        if (damage + damage_bonus > 0)
                        {                 
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                                damage_bonus=-random(4000);
                                result = HIB"$n�ı�������Ȼ������˸����$N�ı����ཻ��$NͻȻ��������ԴԴ�����ӵ����˳�ȥ��\n"NOR;
                        }
                        else {
                                result = HIB"ֻ��$n���б��з���������ã��$N����һ�����������������������˻�ȥ��\n"NOR;
                                damage_bonus=-random(4000);
                        }
                }
                else if(objectp(weapon2) && !objectp(weapon1)){
                        if (damage + damage_bonus > 0)
                        {
                                damage_bonus=-random(4000);
                                result = HIB"$nͻȻ�������Ǵ󷨣�$NͻȻ��������ԴԴ���������˳�ȥ��\n"NOR;                      
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                        }
                        else {
                                result = HIB"ֻ��$n�������㣬����ӭ��ǰ����$N����һ�������������������и�Ϊ���С�\n"NOR;
                                damage_bonus=-random(4000);
                        }

                }
                else if( !objectp(weapon2) && objectp(weapon1) ) {
                        if (damage + damage_bonus > 0)
                        {                 
                                damage_bonus=-random(4000);
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                                result = HIB"$n����һ����˳����$N�ı��в�������һ����$NͻȻ��������������ʧ��\n"NOR;
                        }
                        else {
                                result = HIB"ֻ��$n�ٺ�һЦ����Ȼ���в��ܣ�$N����һ�����������������������˻�ȥ��\n"NOR;
                                damage_bonus=-random(4000);
                        }

                }
                else{
                        if (damage + damage_bonus > 0)
                        {                 
                                damage_bonus=-random(4000);
                                me->add("neili", -victim->query_skill("force"));
                                victim->add("neili", victim->query_skill("force"));
                                result = HIB"$N�����ƺ�$n������һ������������һ�գ�������к������\n"NOR;
                        }
                        else {
                                result = HIB"ֻ��$n�ٺ�һЦ����Ȼ���в��ܣ�$N����һ�����������������������˻�ȥ��\n"NOR;
                                damage_bonus=-random(4000);
                        }
                                
                }
                return ([ "msg" : result, "damage" : damage_bonus ]);
        }
        return damage;
}

string exert_function_file(string func)
{
        return __DIR__"xixing-dafa/" + func;
}

void check_count(object me)
{
        if (me->query("max_neili") >= 3000 &&
            me->query("exception/xixing-count") > 1000)
        {
                me->apply_condition("xixing-fanshi",
                        me->query_condition("xixing-fanshi") +
                        me->query("exception/xixing-count") / 10);
                me->delete("exception/xixing-count");
        }
}

void skill_improved()
{
        this_player()->add("exception/xixing-count",
                           (int)this_player()->query_skill("xixing-dafa", 1) + 1);
        check_count(this_player());
}

