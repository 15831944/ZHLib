// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// whistle.c 找回坐骑

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        string file;

        if (! str)
                return notify_fail("你要召唤什么坐骑？\n");

        if (me->is_busy() || me->query("doing"))  
                return notify_fail("你现在正忙，等你有空了再说吧。\n");
                
        if (me->is_in_prison())   
                return notify_fail("你正在做牢呢，你想干什么？！\n"); 
                
        if (me->is_fighting()) 
                return notify_fail("你现在正在战斗！\n"); 
                
                
        if (environment(me)->query("no_magic") || environment(me)->query("no_fly")) 
                return notify_fail("你发现这里有点古怪，你的坐骑好象不能进来！\n");    
                
        if (! stringp(file = me->query("can_whistle/" + str)))
                return notify_fail("你不知道如何召唤这个坐骑。\n");

        if (file_size(file + ".c") < 0 && file_size(file) < 0)
                return notify_fail("你不知道如何召唤这个坐骑。\n");

        if (me->is_ghost())
                return notify_fail("等你还了阳再召唤吧。\n");

        call_other(file, "???");
        ob = find_object(file);
        if (! ob || ! ob->receive_whistle(me))
        {
                message_vision(HIM "$N" HIM "吹了一声口哨。\n"
                               "然而什么也没有发生 :)\n", me);
        } else
                ob->set_temp("petowner", me);

        if (me->is_fighting())
                me->start_busy(2 + random(3));

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : whistle <坐骑的ID>

此指令可让你把你的坐骑呼唤过来，当然你得有一定的精力施展才行。
HELP );
        return 1;
}

