// /kungfu/skill/lonely-sword/perform/jue.c 「总诀式」
// by smallfish
// 2002/10
 
#include <ansi.h>

int yanlian(object me);
int halt_yanlian(object me);
void remove_pending(object me);

int perform(object me)
{
    object weapon;
    int skill;    //最高的剑技值

    if(me->is_busy())
        return notify_fail("你正忙着呢！\n");

    skill = me->query_skill("lonely-sword",1);

    if (environment(me)->query("no_fight"))
		return notify_fail("这里太嘈杂，你不能静下心来演练。\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword")
        return notify_fail("你手中无剑，如何演练独孤九剑？\n");

    if (me->is_fighting())
        return notify_fail("你正在战斗中，无法演练总诀式。\n");

    if (! skill || skill < 20)
        return notify_fail("你的独孤九剑等级不够, 不能演练「总诀式」！\n");

    if(me->query("jing") < 50)
        return notify_fail("你的精力不济，无法演练总诀式。\n");

    if(me->query("neili") < 110)
        return notify_fail("你的内力不济，无法演练总诀式。\n");

    if (! me->can_improve_skill("lonely-sword"))
        return notify_fail("你的实战经验不够，无法体会「总诀式」！\n");

    if (skill >= (int)me->query_skill("sword",1))
	return notify_fail("你的基本剑法修为有限，无法进一步提升独孤九剑！\n");

    message_vision("$N轻振手中的" + weapon->name() + "，随意击刺起来，虽不成招法，却如行云流水，浑然天成。\n",me);

    me->set_temp("apply/short", ({ me->name() +"正在演练剑法。"}));
    me->set_temp("pending/yanlian", 1);

    me->start_busy((: yanlian :), (: halt_yanlian :));
    return 1;
}

int yanlian(object me)
{
    object weapon;
    string *all_skills;       //所有技能
    int i,sword_skill = 0;    //最高的剑技值

    if(!living(me) || 
        me->is_ghost() || 
        !objectp(weapon = me->query_temp("weapon")) ||
        weapon->query("skill_type") != "sword" ||
        me->query_skill_mapped("sword") != "lonely-sword" )
    {
        remove_pending(me);
        return 0;
    }

    if(me->query("jing") < 50 || me->query("neili") < 110)
    {
        tell_object(me,"你突然觉得神困力乏，实在无法再继续演练独孤九剑。\n");
        message_vision("$N演练良久，收势若有所思，虽面显疲乏，却似乎有所心得。\n",me);
        remove_pending(me);
        return 0;
    }

    all_skills = keys(me->query_skills());
    for(i=0;i<sizeof(all_skills);i++)
    { 
        if(SKILL_D(all_skills[i])->valid_enable("sword") && all_skills[i] != "lonely-sword")
        {
            if(me->query_skill(all_skills[i],1) >  sword_skill)
                sword_skill = me->query_skill(all_skills[i],1);
        }
    }
    i = me->query_int() + (me->query_skill("sword",1)/3 + random(sword_skill));
    if(i < 100) i = 50 + random(100);

    if(random(10) == 1)
        message_vision("$N舞动"+weapon->name()+"，随意击刺，虽不成招法，却如行云流水，浑然天成。\n",me);
    else
        tell_object(me,"你舞动"+weapon->name()+"，随意击刺，虽不成招法，却如行云流水，浑然天成。\n");
    me->improve_skill("lonely-sword", i);

    me->add("jing",-40);
    me->add("neili",-100);
    write(MAG"你对「独孤九剑」加深了一些领会！\n"NOR);
    return 1;
}

int halt_yanlian(object me)
{
    object weapon;
    weapon = me->query_temp("weapon");

    tell_object(me, "你气沉丹田，硬生生地将运转不息的剑势顿住，随即微微一笑。\n");
    message("vision", me->name() +"微微一笑，扣指轻弹手中的"+weapon->name()+"，随即罢手收势。\n",environment(me),me);

    remove_pending(me); 
    me->start_busy(1+random(3));
    return 1;
}

void remove_pending(object me)
{
    me->delete_temp("pending/yanlian");
    me->delete_temp("apply/short");
}
