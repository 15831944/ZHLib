// count.c

inherit SKILL;

string type() { return "knowledge"; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
        object ob;

        if( (int)me->query_skill("literate",1) < 50 )
                return notify_fail("你的文化知识太差，无法理解阴阳八卦的奥妙。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("阴阳八卦只能用学(learn)的来增加熟练度。\n");
}
