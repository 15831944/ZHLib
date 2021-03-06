// huagong-dafa.c 化功大法
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

    if (me->query("character") == "光明磊落")
        return notify_fail("你心中暗想：我为人光明磊落，岂能学习这种害人武功？\n");

    if (me->query("character") == "狡黠多变")
        return notify_fail("你心中暗想：我虽然不是谦谦君子，但这种损人不利己的武功学来何用？\n");

    if ((int)me->query("shen") > t)
                return notify_fail("学化功大法，要心狠手辣，奸恶歹毒，你可做得不够呀！\n");

    if ((me->query("tianmo_jieti/times")< 1) &&
        (me->query_skill("buddhism",1) || 
         me->query_skill("taoism",1) || 
         me->query_skill("mahayana",1) || 
         me->query_skill("lamaism", 1)))
                return notify_fail("你练了秃驴牛鼻子们的心法，还学化功大法做什戚！\n");

    if ((int)me->query_skill("force", 1) < 80)
                return notify_fail("你的基本内功火候不足，不能学化功大法。\n");

    if ((int)me->query_skill("poison", 1) < 40)
        return notify_fail("你的基本毒技火候不足，不能学化功大法。\n");

    if (me->query("gender") == "无性" && (int)me->query_skill("huagong-dafa", 1) > 149)
        return notify_fail("你无根无性，阴阳不调，难以领会高深的化功大法。\n");

    if ((int)me->query_skill("poison", 1) < 400 && (int)me->query_skill("poison", 1) < (int)me->query_skill("huagong-dafa", 1))
        return notify_fail("你的基本毒技水平有限，不能领会更高深的化功大法。\n");

    if ((int)me->query_skill("force", 1) < (int)me->query_skill("huagong-dafa", 1))
        return notify_fail("你的基本内功水平有限，不能领会更高深的化功大法。\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("化功大法只能用学(learn)或练毒的来增加熟练度。\n");
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
                                result = HIB"$n将化功大法运到兵刃上，和$N的兵刃相交，$N突然觉得内力源源不绝从的流了出去。\n"NOR;
                        }
                        else {
				result = HIB"只见$n手中兵刃发出淡淡蓝光，$N心中一惊，不敢妄进，将兵刃收了回去。\n"NOR;
				damage_bonus=-random(4000);
			}
                }
                else if(objectp(weapon2) && !objectp(weapon1)){
                        if (damage + damage_bonus > 0)
			{
				damage_bonus=-random(4000);
			        result = HIB"$n化功大法自然而然发动，$N突然觉得内力源源不绝从的流了出去。\n"NOR;                      
                            me->add("neili", -victim->query_skill("huagong-dafa",1));
	            		victim->add("neili", victim->query_skill("huagong-dafa",1));
			}
                	else {
				result = HIB"只见$n嘴角微微冷笑，似乎成竹在胸，$N心中一惊，不敢妄进，将进招改为守招。\n"NOR;
				damage_bonus=-random(4000);
			}

		}
        	else if( !objectp(weapon2) && objectp(weapon1) ) {
                        if (damage + damage_bonus > 0)
                        {                 
				damage_bonus=-random(4000);
		                me->add("neili", -victim->query_skill("huagong-dafa",1));
				victim->add("neili", victim->query_skill("huagong-dafa",1));
                                result = HIB"$n将身子一側，顺手把$N的兵刃一带，$N突然觉得胸中若有所失。\n"NOR;
                        }
                        else {
				result = HIB"只见$n嘿嘿一笑，竟然不招不架，$N心中一惊，不敢妄进，将兵刃收了回去。\n"NOR;
				damage_bonus=-random(4000);
			}

                }
                else{
                        if (damage + damage_bonus > 0)
                        {                 
				damage_bonus=-random(4000);
		                me->add("neili", -victim->query_skill("huagong-dafa",1));
				victim->add("neili", victim->query_skill("huagong-dafa",1));
                                result = HIB"$N的手掌和$n的身体一触，觉得内力飞快的流了出去。\n"NOR;
                        }
                        else {
				result = HIB"只见$n嘿嘿一笑，竟然不招不架，$N心中一惊，不敢妄进，将兵刃收了回去。\n"NOR;
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
        	tell_object(this_player(), "你体内不同内力互相冲撞，难以施展化功大法。\n");
        	return 0;
        }

        return __DIR__"huagong-dafa/" + func;
}



mapping curing_msg(object me)
{
        return ([
"apply_short" :me->name()+"正盘膝而坐，全身覆盖着一层薄薄的寒霜。",
"start_self" :HIW"你盘膝坐下，心中默念化功大法的口诀，开始运功疗伤。\n"NOR,
"on_self" :HIM"你运起化功大法，真气全身游走，企图化去堵塞经脉中的残留内力。\n"NOR,
"start_other" :HIM""+me->name()+"浑身颤抖，面上时红时白，身体散发一股寒气。\n"NOR,
"finish_self" :HIW"你脸色时红时白，身体四周白雾围绕，突然喷出一口淤血，一改脸上痛苦神情。\n"NOR,
"finish_other" :me->name()+"疗伤已毕，收腿起身，看上去气色饱满，精神抖擞。\n",
"unfinish_self" :"你正以化功大法化去经脉里残留内力，忽觉内息紊乱，只能暂缓疗伤。\n",
"unfinish_other":me->name()+"化去了部分内力，脸色稍有好转，精神看起来好多了。\n",
"halt_self" :"你吐气纳息，硬生生地将内息压了下去，停下了疗伤。\n",
"halt_other" :me->name() +"收起内息，身子一震，吐出一口瘀血，脸色稍显红润。\n",
        ]);
}
