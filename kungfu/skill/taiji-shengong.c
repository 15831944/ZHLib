// taiji-shengong.c ̫����
// Modified by haiyan

#include <ansi.h> 

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "hunyuan-yiqi" ||
               force == "yijinjing" ||
               force == "wudang-xinfa" ||
               force == "shaolin-xinfa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("taiji-shengong", 1);
    return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
    if ( me->query("gender") == "����" && (int)me->query_skill("taiji-shengon", 1) > 19)
         return notify_fail("���޸����ԣ����������������������̫���񹦡�\n");

    if ((int)me->query_skill("force", 1) < 100)
         return notify_fail("��Ļ����ڹ���򻹲�����\n");

    if ((int)me->query_skill("taoism", 1) < 100)
         return notify_fail("��Ե����ķ������̫ǳ���޷����̫���񹦡�\n");

    if ((int)me->query_skill("taoism", 1) < (int)me->query_skill("taiji-shengong", 1))
         return notify_fail("��Ե����ķ���������ޣ��޷���������̫���񹦡�\n");

    if ((int)me->query_skill("force", 1) < (int)me->query_skill("taiji-shengong", 1))
         return notify_fail("��Ի����ڹ�ˮƽ���ޣ��޷���������̫���񹦡�\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("̫����ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed hit_by(object ob, object me, int damage) 
{
        object weapon = me->query_temp("weapon");
        int ap, dp, shan;
        string result;

        if (me->query_skill("taiji-shengong",1) < 300) return damage;

        if (me->query("neili") < 1000) return damage;

        if (damage <=0) return damage;

        if (!living(me) || (me->is_busy() && random(3) == 0))  return damage;

        dp = ob->query_skill("force",1) + ob->query_skill("parry",1);

        ap = me->query_skill("taiji-shengong",1);
        if (objectp(weapon))
            ap += me->query_skill("taiji-jian", 1);
        else
            ap += me->query_skill("taiji-quan", 1);

        if (me->query("jiali"))  {
        if ( ap / 3 + random(ap) > dp )
        {
             if (me->query("character") == "��������" ||
                 me->query("character") == "������") 
                   shan = damage / 2;
             else  shan = damage / 4;

             if (objectp(weapon))
             {
                result = HIY "$n" HIY "Ĭ��̫���񹦣�����" + weapon->name() +
                         HIY "��Ȧ��Բ���������⣬��$N" HIY "������\n"
                         HIY "$N" HIY "�����Լ�����ʽ������ת�����û����Լ���"
                         HIY "�̲�ס�ƺ�һ�������ۡ����³�һ��" HIR "��Ѫ" HIY "��\n"NOR;
                me->add("neili", -150);
                ob->receive_damage("qi", shan);
                ob->receive_wound("qi", shan/2 + random(shan/2));
                return ([ "msg" : result, "damage" : -damage ]);
             }
             else
             {
                result = HIY "$N" HIY "һ�����ô���$n"
                         HIY "���ϣ������Ӿ���ȴ������ͬ����������һ�㣬"
                         HIY "ʹ����˿����������æ���֣���Ȼ��������$n"
                         HIY "�������𣬡��ء���һ����ֻ��$N" HIY "�����񵾲ݰ����ɳ���\n"NOR;
                me->add("neili", -150);
                ob->receive_damage("qi", shan * 2 );
                ob->receive_wound("qi", shan + random(shan));
                return ([ "msg" : result, "damage" : -damage ]);
             }
        } }
        return damage;
}

string exert_function_file(string func)
{
        return __DIR__"taiji-shengong/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short"   : me->name() +"���������ͷ������"HIW"�뵰���"NOR"������������",
"start_self"    : HIW"���̤̫����Ǳ��������������Ѩ����ת���ˣ�������Ϣ��\n"NOR,
"on_self"       : HIM"�����������ڷ���·��ת�������ܼã��о����ƴ�����ɫ��\n"NOR,
"start_other"   : HIM"ֻ��"+ me->name() +"�����������Ϣ������ͷ��ð��˿˿������\n"NOR,
"finish_self"   : HIW"��ֻ����Ϣ��ת˳�������������ϵ��վ��������\n"NOR,
"finish_other"  : me->name() +"�Ұ׵���ɫ�������󣬻��������ۣ�վ��������\n",
"unfinish_self" : "�㽥�������������󾢲��̣����ò��������ڰ��˵���Ϣ�ջء�\n",
"unfinish_other": me->query("eff_qi") < me->query("max_qi")*3/4 ?
                  "�͵���"+ me->name() +"��һ�ţ����������Ѫ��\n" :
                  "�͵���"+ me->name() +"��һ�ţ��³����Ϻ���Ѫ��\n",
"halt_self"     : "�㽫��·����ѹ�����������ϵ��������������������ƽ����\n",
"halt_other"    : me->name() +"����΢΢һ������˫�ۣ������ƺ����Ϻ��˲��١�\n",
        ]);
}

