// huagong-dafa.c ������
// by yucao
// Modified by Venus Oct.1997
#include <ansi.h>
#include <combat.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
     return force == "guixi-gong";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("huagong-dafa", 1);
    return lvl * lvl * 15 * 20 / 100 / 200;
}

int valid_learn(object me)
{
    int i = (int)me->query_skill("huagong-dafa", 1);
    int t = -1000, j;

    t += -i*1000;

    if (me->query("character") == "��������")
        return notify_fail("�����а��룺��Ϊ�˹������䣬����ѧϰ���ֺ����书��\n");

    if (me->query("character") == "������")
        return notify_fail("�����а��룺����Ȼ����ǫǫ���ӣ����������˲��������书ѧ�����ã�\n");

    if ((int)me->query("shen") > t)
                return notify_fail("ѧ�����󷨣�Ҫ�ĺ���������������������ò���ѽ��\n");

    if ((me->query("tianmo_jieti/times")< 1) &&
        (me->query_skill("buddhism",1) || 
         me->query_skill("taoism",1) || 
         me->query_skill("mahayana",1) || 
         me->query_skill("lamaism", 1)))
                return notify_fail("������ͺ¿ţ�����ǵ��ķ�����ѧ��������ʲ�ݣ�\n");

    if ((int)me->query_skill("force", 1) < 80)
                return notify_fail("��Ļ����ڹ�����㣬����ѧ�����󷨡�\n");

    if ((int)me->query_skill("poison", 1) < 40)
        return notify_fail("��Ļ�����������㣬����ѧ�����󷨡�\n");

    if (me->query("gender") == "����" && (int)me->query_skill("huagong-dafa", 1) > 149)
        return notify_fail("���޸����ԣ���������������������Ļ����󷨡�\n");

    if ((int)me->query_skill("poison", 1) < 400 && (int)me->query_skill("poison", 1) < (int)me->query_skill("huagong-dafa", 1))
        return notify_fail("��Ļ�������ˮƽ���ޣ�������������Ļ����󷨡�\n");

    if ((int)me->query_skill("force", 1) < (int)me->query_skill("huagong-dafa", 1))
        return notify_fail("��Ļ����ڹ�ˮƽ���ޣ�������������Ļ����󷨡�\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("������ֻ����ѧ(learn)�������������������ȡ�\n");
}

mixed hit_by(object me, object victim, int damage, int damage_bonus, int factor)
{
        object weapon1 = me->query_temp("weapon");
        object weapon2 = victim->query_temp("weapon");

        int ap, dp;
        string result;

	if (!victim->query("canewhua")) return damage;
	
	dp = (int)victim->query_skill("huagong-dafa",1);

        if (objectp(weapon2) ){
		if (weapon2->query("skill_type") == "staff")
	                dp += victim->query_skill("tianshan-zhang",1);
		else return damage;
        } else if (!objectp(weapon2) ) {
                if ( victim->query_skill_prepared("strike") != "chousui-zhang"  || 		     victim->query_skill_prepared("claw") != "sanyin-wugongzhao")
                        return damage;
                dp += victim->query_skill("strike")/2;
                dp += victim->query_skill("claw")/2;
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
		                me->add("neili", -victim->query_skill("huagong-dafa",1));
				victim->add("neili", victim->query_skill("huagong-dafa",1));
				damage_bonus=-random(4000);
                                result = HIB"$n���������˵������ϣ���$N�ı����ཻ��$NͻȻ��������ԴԴ�����ӵ����˳�ȥ��\n"NOR;
                        }
                        else {
				result = HIB"ֻ��$n���б��з����������⣬$N����һ�����������������������˻�ȥ��\n"NOR;
				damage_bonus=-random(4000);
			}
                }
                else if(objectp(weapon2) && !objectp(weapon1)){
                        if (damage + damage_bonus > 0)
			{
				damage_bonus=-random(4000);
			        result = HIB"$n��������Ȼ��Ȼ������$NͻȻ��������ԴԴ�����ӵ����˳�ȥ��\n"NOR;                      
                            me->add("neili", -victim->query_skill("huagong-dafa",1));
	            		victim->add("neili", victim->query_skill("huagong-dafa",1));
			}
                	else {
				result = HIB"ֻ��$n���΢΢��Ц���ƺ��������أ�$N����һ�������������������и�Ϊ���С�\n"NOR;
				damage_bonus=-random(4000);
			}

		}
        	else if( !objectp(weapon2) && objectp(weapon1) ) {
                        if (damage + damage_bonus > 0)
                        {                 
				damage_bonus=-random(4000);
		                me->add("neili", -victim->query_skill("huagong-dafa",1));
				victim->add("neili", victim->query_skill("huagong-dafa",1));
                                result = HIB"$n������һ�ȣ�˳�ְ�$N�ı���һ����$NͻȻ��������������ʧ��\n"NOR;
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
		                me->add("neili", -victim->query_skill("huagong-dafa",1));
				victim->add("neili", victim->query_skill("huagong-dafa",1));
                                result = HIB"$N�����ƺ�$n������һ�������������ɿ�����˳�ȥ��\n"NOR;
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
        mapping skl;
        string *sname;
        int v, k=0;

	if (mapp(this_player()->query("tianmo_jieti")))
	        return __DIR__"huagong-dafa/" + func;
 
        skl=this_player()->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );

        for(v=0; v<sizeof(skl); v++) {
                if (sname[v] != "taixuan-shengong" && SKILL_D(sname[v])->valid_enable("force"))
                k++;
        }

        if ( !this_player()->query("tianmo_jieti/times") && k >=3 )
        {
        	tell_object(this_player(), "�����ڲ�ͬ���������ײ������ʩչ�����󷨡�\n");
        	return 0;
        }

        return __DIR__"huagong-dafa/" + func;
}



mapping curing_msg(object me)
{
        return ([
"apply_short" :me->name()+"����ϥ������ȫ������һ�㱡���ĺ�˪��",
"start_self" :HIW"����ϥ���£�����Ĭ����󷨵Ŀھ�����ʼ�˹����ˡ�\n"NOR,
"on_self" :HIM"�����𻯹��󷨣�����ȫ�����ߣ���ͼ��ȥ���������еĲ���������\n"NOR,
"start_other" :HIM""+me->name()+"�������������ʱ��ʱ�ף�����ɢ��һ�ɺ�����\n"NOR,
"finish_self" :HIW"����ɫʱ��ʱ�ף��������ܰ���Χ�ƣ�ͻȻ���һ����Ѫ��һ������ʹ�����顣\n"NOR,
"finish_other" :me->name()+"�����ѱϣ�������������ȥ��ɫ�����������ӡ�\n",
"unfinish_self" :"�����Ի����󷨻�ȥ���������������������Ϣ���ң�ֻ���ݻ����ˡ�\n",
"unfinish_other":me->name()+"��ȥ�˲�����������ɫ���к�ת�����������ö��ˡ�\n",
"halt_self" :"��������Ϣ��Ӳ�����ؽ���Ϣѹ����ȥ��ͣ�������ˡ�\n",
"halt_other" :me->name() +"������Ϣ������һ���³�һ����Ѫ����ɫ���Ժ���\n",
        ]);
}
