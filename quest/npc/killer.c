// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// killer.c

#include <ansi.h>
inherit CLASS_D("generate") + "/chinese";

void create()
{
        
        mapping my;

        ::create();
        set("gender", "男性" );
        set("age", 30 + random(30));
        set_name(BLU "蒙面人" NOR, ({"figure", "mengmian ren", "ren"}));
        set("long", "这个人头上戴著蒙面头罩，八成准备干什麽坏事。\n");
        set("attitude", "friendly");
        set("scale", 150);
        set("chat_chance_combat", 120);
        set_temp("apply/armor", 300);
        set_temp("apply/damage", 200);

}

void set_from_me(object me, int scale)
{
        int sk_lvl;
        string *ks;
        int i;
        int exp;
        object ob = this_object();
        
        exp = me->query("combat_exp");
        set("combat_exp", exp);
        
        exp /= 100;
        sk_lvl = to_int(pow(to_float(exp), 1.0 / 3)) * 10 + 1; 
        
        if (! ob->query_skills())
                return;
        ks = keys(ob->query_skills());
        for (i = 0; i < sizeof(ks); i++)
                ob->set_skill(ks[i], sk_lvl);               
}

void init()
{
        object me = this_player(); 
        
        ::init();
        if (interactive(me) && visible(me) && 
            ! is_fighting()) 
        {
                set_from_me(me, 100);
                kill_ob(me);
        }
}

void kill_ob(object ob)
{
        if (! is_busy())
                exert_function("powerup");

        message_vision(HIB "$n对$N，喝道: “什么人如此大胆，"+
                           "竟敢擅闯柳绿山庄？！\n" NOR, ob, this_object());
        ::kill_ob(ob);
}

void unconcious()
{
        message_vision(HIR "$N大叫一声：好厉害！然后地板突然翻起，$N钻了进去不见了。\n",
                       this_object());
        destruct(this_object());
        return ;
}

