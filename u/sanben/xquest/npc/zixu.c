
//紫虚道人  趣味任务取消及发放者

#include <ansi.h>
              
inherit NPC;
inherit F_UNIQUE;

#define BAG           "/u/sanben/xquest/obj/bag"
#define MIRROR        "/u/sanben/task/mirror"


int ask_quest();
int ask_cancel();
int ask_mirror();
int ask_hulu();

void create()
{         seteuid(getuid());
        set_name("紫虚道人", ({ "zixu daoren", "zixu", "daoren" }));
        set("long", @LONG
此人身着道袍，须发皆白，一副仙风道骨的气
派。这便是武林中号称「紫虚乌有」二道仙中
的紫虚道人。传说此人早已得道成仙，可通神
界。
LONG);
        set("nickname", HIW "仙风道骨" NOR);
        set("title", HIC "紫虚观观主" NOR);
        set("gender", "男性" );
        set("age", 108);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);

        set("inquiry", ([
                       "修炼"      : (: ask_quest :),
                       "任务"      : (: ask_quest :),
                       "取消"      : (: ask_cancel :),
                       "cancel"    : (: ask_cancel :),
                       "乾坤宝镜"      : (: ask_mirror :),
                       "宝镜"      : (: ask_mirror :),
                       "mirror"      : (: ask_mirror :),    

        ]));

        set_skill("force", 500);
        set_skill("huntian-baojian", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("lunhui-jian", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("buddhism", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "huntian-baojian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "lunhui-jian");

        prepare_skill("unarmed", "huntian-baojian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
        }));

    
        setup();
        carry_object("/d/wudang/obj/whiterobe")->wear();

}

// 发放趣味任务
int ask_quest()
{       

        object  me;

    me = this_player();

    if ( mapp(me->query("xquest")))
        {
         message_vision(CYN "$N" CYN "盯着$n看了看，说道：“你现在有任务在身，"
                            "要是完成不了就先和我说一声取消。”\n"NOR,
                        this_object(), me);
                        return 1;
        }

        if ( time() - me->query("xquest_last_cancel") < 60 )
        {
         message_vision(CYN "$N" CYN "盯着$n看了看，说道：“你刚取消过一次任务，"
                            "先喝口水歇会儿再接着领下一个吧。”\n"NOR,
                        this_object(), me);
                        return 1;
        }


      message_vision(CYN "$N" CYN "盯着$n看了看，点点头说：“很好，既然你有心"
                        "修炼，我便指点你一条明路。”\n"NOR,
                    this_object(), me);
      me->set("xquest/target_npc", "紫虚道人");
      call_other(XQUEST, "next_quest", me );  //呼叫next_quest涵数产生新的任务
      return 1;
}

//取消趣味任务

int ask_cancel()
{       
      object    me,*obj;
      int i;

      me = this_player();

      if ( ! mapp(me->query("xquest")))
        {
         message_vision(CYN "$N" CYN "盯着$n看了看，说道：“你有没有搞错，"
                            "你又没任务在身取消什么？”\n"NOR,
                        this_object(), me);
                        return 1;
        }

      if ( time() - me->query("xquest_total_cancel/time") > 3600 )
      {
         me->delete("xquest_total_cancel");
         me->set("xquest_total_cancel/time", time());
      }
      else
      {
         if ( me->query("xquest_total_cancel/total") >= 5 )
         {
            message_vision(CYN "$N" CYN "盯着$n看了看，说道：“一小时内只能"
                            "取消五次任务！”\n"NOR,
                        this_object(), me);
                        return 1;
         }
      }

         message_vision(CYN "$N" CYN "盯着$n看了看，说道：“嗯，有那么几次挫折"
                            "是很正常的，\n关键是要有勇气再接再厉才能走向最终"
                            "的成功。”\n"NOR,
                            this_object(), me);

      if ( me->query("xquest/kind") == "do_drawing")   //销毁要埋的小布包
        {
                obj = all_inventory(me);
                for(i=0; i<sizeof(obj); i++) 
                {       
                        if (base_name(obj[i]) == BAG)
                        {
                                destruct(obj[i]);
                                
                                message_vision(HIG "$N对$n说道：“既然你不想帮人家的忙"
                                "了那这个小布包我就帮你物归原主了。”\n"
                            "$N说着就从$n怀里搜走一个小布包\n"NOR,
                                this_object(),me );

                                break;
                        }  
                }       
         }

       tell_object(me, HIG"你的趣味任务取消了。重新来过吧！\n"NOR);

        if ( me->query("weiwang") > 10000 && me->query("score") > 10000 )
        {
           me->add("weiwang", -100);
           me->add("score", -100);

           tell_object(me, HIR"你的阅历和江湖威望受到了一定损失！\n"NOR);
        }
         me->delete("xquest");
         me->delete("xquest_count");
         me->set("xquest_last_cancel", time());

         me->add("xquest_total_cancel/total", 1);

        return 1;
}

int ask_mirror()
{       
    
      object me, ob, *obj;
      int i,have;
      me = this_player();
      have = 0;

      obj = all_inventory(me);
                for(i=0; i<sizeof(obj); i++) 
                {       
                        if (base_name(obj[i]) == MIRROR)
                        {
                  have = 1;
                        }  
         }

            if ( have == 1 )

            {
               message_vision(HIG "$N对$n说道：“你身上已经有一个宝镜了"
                                                  "别贪得无厌！”\n"NOR,
                                this_object(),me );
               return 1;
            }
            else
            {

           ob = new(MIRROR);
           ob->move(me);

       message_vision(HIG "$N盯着$n看了看，说道：“嗯，这个宝镜你可得慎用！\n"
                         "好好用它锻炼锻炼你的判断力和观察力吧。”\n"NOR
                         CYN"$N从怀里拿出一面乾坤宝镜交给$n。\n"NOR,
                            this_object(), me);
              return 1;
            }

      return 1;

}


void unconcious()
{
        die();
}
