#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "xuanming_poison"; }

string chinese_name() { return "玄冥寒毒"; }

string update_msg_others()
{
       return MAG "$N脸色发紫，全身不住的颤抖，牙关格格作响。\n" NOR;
}

string update_msg_self()
{
        return MAG "只感到一股奇寒从体内犹然而升，沁入三焦六脉，看来是玄冥神掌之毒发作了！\n" NOR;
}
int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 4;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 4;
}


