// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string bunch;

        if (! arg || arg == "")
                return notify_fail("你要加入谁的帮会？\n");

        if (me->query("combat_exp") < 1000)
                return notify_fail("你才初入江湖，在磨练磨练吧。\n");    
                                         
        if (stringp(bunch = me->query("bunch/bunch_name")) ||
            stringp(bunch = me->query("league/league_name")))
                return notify_fail("抱歉，你已经是「" + bunch + "」的人了，无法加入其他帮会。\n");
                
        if (me->is_fighting() || me->is_busy())
                return notify_fail("你正忙着呢。\n");
                
        if (me->query("id") == arg)
                return notify_fail("你没法这么做！\n");
                
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("这儿没有这么个人。\n");
                
        if ((object)me->query_temp("invite/target") != ob)
                return notify_fail("抱歉，" + ob->query("name") + "并没有邀请你参加他的帮会。\n");
                
        if (! stringp(bunch = ob->query("bunch/bunch_name")))
                return notify_fail("抱歉，" + ob->query("name") + "现在不属于任何帮会！\n");                           

        BUNCH_D->add_member_into_bunch(bunch, me->query("id"));
        BUNCH_D->add_bunch_fame(bunch, me->query("weiwang") / 10); 
        me->set("bunch/time", time());
        me->set("bunch/bunch_name", bunch);
        me->set("bunch/level", 1);
        me->set("bunch/title", "帮众");
                        
        message("channel:rumor", HIY "【中华帮会】某人：" + me->query("name") + 
                                 "(" + me->query("id") + ")加入帮会「" + bunch + 
                                 "」，誓死为「" + bunch + "」效力！\n" NOR, users());
                                 
        me->delete_temp("invite/target");
        
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：join | jiaru <某人>
这个指令用来加入某人的帮会。前提是某人必须邀请你。

相关指令：invite
HELP
        );
        return 1;
}




