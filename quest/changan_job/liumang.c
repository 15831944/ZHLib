
#include <ansi.h>
inherit NPC;

mapping *data=({
(["name":"流氓", "id":"liu mang",]),
(["name":"混混", "id":"hun hun",]),
(["name":"盗贼", "id":"dao zei",]),
(["name":"强盗", "id":"qiang dao",]),
(["name":"小偷", "id":"xiao tou",]),
});

void create()
{
	mapping npc;
       npc=data[random(sizeof(data))];
	set_name(npc["name"],({ npc["id"] }));
	set("gender", "男性");
	set("age", 19);
	set("long", "此人贼眉鼠眼，一看就让人觉得非奸即盗，但肯定只是个小混混。\n");
	
	set("combat_exp", 1000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();	
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        add_action("do_agree", "agree");
        add_action("do_disagree", "disagree");

        remove_call_out("disappear");
        call_out("disappear", 30);

        remove_call_out("runaway");
        call_out("runaway", 360);
}

void lost()
{
    object ob, me;
    ob = this_object();
    me = ob->query_temp("last_opponent");
    if ( ! ob->query("owner") && 
         me->query("changanjob/kind") == "patrol")
    {
        ob->set("owner", me );    
        me->add("changanjob/catch_num",1);
        message_vision(CYN"$N对$n说道：老实点，速速随我去衙门治罪，否则叫你皮肉受苦！\n"
                       "$n无奈道：哎，既然落在你手里我也无话可说，但请将我从轻发落。\n"NOR ,
                        me, ob);         
       command("whisper " + me->query("id") + " 这位" + RANK_D->query_respect(me) + 
               "你若肯放我一马，我有重谢。");  
       tell_object(me, "你是同意(agree)接受贿赂还是不同意(disagree)呢？\n");      
    }

} 

int do_agree()
{
     object me, ob, pay;
     me = this_player();
     ob = this_object();
     if ( me != ob->query("owner") ) return 1;     
     pay = new("/clone/money/gold");
     pay->set_amount(1);
     pay->move(me, 1);        
     command("say 多谢这位" + RANK_D->query_respect(me) + "高抬贵手，这点银子恳请笑纳！");     
     message_vision(CYN"$N递给$n一两黄金，接着一下就溜得不见了踪影。\n"NOR ,ob, me);       
     destruct(ob);
     return 1;     
}

int do_disagree()
{
     object me, ob;
     me = this_player();
     ob = this_object();
     if ( me != ob->query("owner") ) return 1;  
     command("sigh");
     command("say 既然这位" + RANK_D->query_respect(me) + "执意如此，我也唯有束手就擒了！");     
     message_vision(CYN"$N开始跟随$n行动。\n"NOR,ob, me); 
     ob->set_leader(me);
     me->set("changanjob/catch", ob);
     return 1;  
}

void win() 
{
        object ob = this_object();
        message_vision(CYN"$N大笑道：这等身手也来捉贼？回去再修炼十年吧！"
                       "大爷我可没工夫陪你玩咯。\n说着$N便嗖的一下跑了。\n",ob);
        destruct(ob);
}

void disappear()
{
        object ob = this_object();

        // 没人抓的话很快就消失
        if (living(ob) && ! ob->query("owner")
            && ! ob->is_busy() && ! ob->is_fighting() )
        {
                message_vision(WHT "$N眼珠子一转，猛地一抽身，瞬间便"
                               "逃得无影无踪。\n\n", ob);
                destruct(ob);
        }
}

void runaway()
{
        object ob = this_object();
        // 时间到了必消失
        message_vision(WHT "\n$N一看四下没人，嗖地一下溜得无影无踪。\n\n", ob);
        destruct(ob);       
}

void unconcious() 
{ 
        die(); 
} 