// guojing.c 无敌大将军
inherit NPC;
#include <ansi.h>
string * degree_desc = ({
       BLU "士卒" NOR,
       BLU "游击" NOR,
       HIC "参将" NOR,
       HIC "裨将" NOR,
       HIY "佐将" NOR,
       HIY "副将" NOR,
       HIR "将军" NOR,
       HIR "提督" NOR,
});               
string clear_degree(string arg);
int ask_degree();
int add_degree(object ob,int lv);
string ask_canjun();
string ask_jianlou();
string ask_lianzhu();
string ask_fuming();
string ask_shoucheng();
string ask_chetui();

void create()
{
        set_name("岳飞", ({"yue fei", "yue", "fei"}));
        set("nickname", HIY"精忠报国"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long", 
                "他就是人称精忠报国的大将军岳飞。\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set_temp("no_kill",1);
        set("chat_chance", 1);
        set("chat_msg", ({
                "岳飞叹了口气道：“金兵越来越多了...\n",
                "岳飞说道：“大丈夫在世，一定要为国为民。\n",
        }));

        set("inquiry", ([
                 "守城"  : (: ask_shoucheng :),
                 "复命"  : (: ask_fuming :),
//                 "撤退"  : (: ask_chetui :),
//                 "狙击"  : (: ask_jianlou :), 
//                 "连珠箭法" :   (: ask_lianzhu :),
                 "策封" :   (: ask_degree :),  
                 "参军" :   (: ask_canjun :), 
                ]));

        set("qi", 8000);
        set("max_qi", 8000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 24000);
        set("max_neili", 24000);
        set("jiali", 500);
        
        set("combat_exp", 25000000);
        set("score", 200000);
         
        set_skill("force", 400);                // 基本内功
        set_skill("huntian-qigong", 400);        // 混天气功
        set_skill("unarmed", 400);                // 基本拳脚
        set_skill("xianglong-zhang", 400);        // 降龙十八掌
        set_skill("dodge", 400);                // 基本躲闪
        set_skill("xiaoyaoyou", 400);                // 逍遥游
        set_skill("parry", 400);                // 基本招架
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");         
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");
        prepare_skill("unarmed","xianglong-zhang");
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
}

string ask_shoucheng()
{
        object *ene;
        object me = this_player();

        if(is_fighting()) 
        {
                ene=query_enemy();
                
                if(sizeof(ene)>1) return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和这"+sizeof(ene)+"位高手切磋几下！”\n";
                if(sizeof(ene)==1) return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和"+ene[0]->name()+"切磋几下！”\n";
        }

        if(me->query_temp("guo_shoucheng/mark_shadi") || me->query_temp("guo_jianlou/mark_jianlou") )
        return "“"+RANK_D->query_respect(me)+"不是已有任务了吗！”\n";

       if ((int)me->query("combat_exp")<100000)
       return "“"+RANK_D->query_respect(me)+"手无缚鸡之力，还是别领任务的为好！”\n";

       if ( (int)me->query_skill("force") < 20 )
       return "守城是件危险工作，我看"+RANK_D->query_respect(me)+"的基本内力不足！\n";

       if ( !me->query("family/family_name") )
       return "“"+RANK_D->query_respect(me)+"无门无派，来历不明，不敢有劳！”\n";

       if ((int)me->query_condition("jobshadi_failed"))
       {
        message_vision("$N对着$n摇了摇头说：逃跑失败了还来见我??\n", this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你还是别领任务的为好！”\n";
       }

       if( me->query("guo_shoucheng/failed") )
       {
         me->apply_condition("jobshadi_failed",16);
         return "“临阵脱逃，还敢回来见我！！？？”\n";
       } 

       if ((int)me->query_condition("jobshadi_limit")>1)
       {
        message_vision("$N对着$n摇了摇头说：你不是正做着吗??\n", this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你快点回你的岗位上去！”\n";
       }

       if ((int)me->query_condition("guojob2_busy"))
       {
        message_vision(CYN"$N对着$n摇了摇头说：疲惫之师不利作战！！\n"NOR,
                                                        this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你还是休息一下再来吧！”\n";
       }
       
       if (me->query("shen")>0)
       {
        switch( random(2) ) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi",1);
                        me->set_temp("guo_shoucheng/carry_location","eastgate1");                
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去玄武内门帮助宋军守城吧。";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi",2);
                        me->set_temp("guo_shoucheng/carry_location","northgate1");                
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去青龙内门帮助宋军守城吧。";

                       break;
                }        
        }
        else
        {
        switch( random(2) ) {
                case 0:
                        me->set_temp("guo_shoucheng/mark_shadi",3);
                        me->set_temp("guo_shoucheng/carry_location","southgate1");
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去朱雀内门帮助宋军守城吧。";

                       break;
                case 1:
                        me->set_temp("guo_shoucheng/mark_shadi",4);
                        me->set_temp("guo_shoucheng/carry_location","westgate1");
                return "“现在金兵侵犯中原，这位"+RANK_D->query_respect(me)+"去白虎内门帮助宋军守城吧。";

                       break;
                }
        }
}


string ask_jianlou()
{
        object *ene;
        object me = this_player();

        if(is_fighting()) 
        {    
         ene=query_enemy(); 

         if(sizeof(ene)>1)
         return "“请"+RANK_D->query_respect(me)
                  +"稍等片刻，我先和这"+sizeof(ene)+"位高手切磋几下！”\n";
         if(sizeof(ene)==1)
         return "“请"+RANK_D->query_respect(me)+"稍等片刻，我先和"
                  +ene[0]->name()+"切磋几下！”\n";
        }

        if( me->query_temp("guo_jianlou/mark_jianlou") || me->query_temp("guo_shoucheng/mark_shadi") )
        return "“"+RANK_D->query_respect(me)+"不是已有任务了吗！”\n";

       if ((int)me->query_condition("jobshadi_failed"))
       {
        message_vision(
        "$N对着$n摇了摇头说：逃跑失败了还来见我??\n", this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你还是别领任务的为好！”\n";
       }

       if( me->query("guo_shoucheng/failed") )
       {
         me->apply_condition("jobshadi_failed",16);
         return "“临阵脱逃，还敢回来见我！！？？”\n";
       } 

       if ( (int)me->query_skill("arrow",1) < 50)
       {
        message_vision(CYN"$N对着$n摇了摇头说：你的基本箭法太差了！\n"NOR,
                                                       this_object(), me);
        return "“"+RANK_D->query_respect(me)+"，我怕你难以胜任啊！”\n";
       }                                               

       if ((int)me->query_condition("jobjianlou_limit")>1)
       {
        message_vision("$N对着$n摇了摇头说：你不是正做着吗？？\n", 
                                                       this_object(), me);
        return "“"+RANK_D->query_respect(me)+"，请你快点回你的岗位上去！”\n";
       }
       if ((int)me->query_condition("guojob2_busy"))
       {
        message_vision(CYN"$N对着$n摇了摇头说：疲惫之师不利作战！！\n"NOR,
                                                        this_object(), me);
        return "“"+RANK_D->query_respect(me)+"你还是休息一下再来吧！”\n";
       }

       me->set_temp("guo_jianlou/mark_jianlou",2);
       me->set_temp("guo_jianlou/where","east_out");
       return "“那就有劳这位"+RANK_D->query_respect(me)
              +"前往青龙内门的东城箭楼，负责狙击金兵箭手的任务吧。\n”";
}

string ask_fuming()
{
        int job_pot,job_exp,job_tihui,reward;
        object me = this_player();

        if( !me->query_condition("jobshadi_failed") && me->query("guo_shoucheng/failed") )
        {
         me->delete_temp("guo_shoucheng");
         me->delete_temp("guo_jianlou"); 
         me->apply_condition("jobshadi_failed",15);
         return "“临阵脱逃，还敢回来复命！！？？”\n";
        } 

        if( me->query_temp("guo_shoucheng/help_killed")
            && !me->query_temp("guo_shoucheng/job_over") ) 
        {
                 job_exp=((int)me->query_temp("guo_shoucheng/help_killed"))*40;
                job_pot=job_exp*2/3;
                job_tihui=job_pot/2;
                job_exp=job_exp;
                me->add("combat_exp", job_exp);
                me->add("potential",job_pot);
                me->add("experience",job_tihui);
                tell_object(me,HIW"你被奖励了"+chinese_number(job_exp)+"点经验值！及"+chinese_number(job_pot)+"点潜能！及"+chinese_number(job_tihui)+"点体会！\n"NOR);
                me->delete_temp("guo_shoucheng/help_killed");        
                me->apply_condition("guojob2_busy",4);
                me->add("guo_shoucheng/reward_exp", job_exp);
                me->add("guo_shoucheng/reward_potential",job_pot);  
                me->add("guo_shoucheng/reward_experience",job_tihui);  
                me->add("guo_shoucheng/reward_potential",job_pot);  
        return "“"+RANK_D->query_respect(me)
               +"，为国杀敌，不错不错！”\n";
        }
           
        if( (!me->query_temp("guo_shoucheng/mark_shadi")
                || !me->query_temp("guo_shoucheng/job_over")) 
             && (!me->query_temp("guo_jianlou/mark_jianlou")
                || !me->query_temp("guo_jianlou/job_over")) )    
        return "“你好象没完成任务吧，还来复什么命？”\n";
        
        if(me->query_temp("guo_shoucheng/killed_mgb")<2 
           && me->query_temp("guo_jianlou/killed_mgb")<2)
        {
         me->delete_temp("guo_shoucheng");

         me->delete_temp("guo_jianlou");  
         return "“你杀了几个敌人啊，就从前线逃回来了？\n";
        }

        message_vision(CYN "$N对$n说道：“"+RANK_D->query_respect(me)+"辛苦了，去休息一下吧！”\n" NOR, this_object(), me);
          job_exp=((int)me->query_temp("guo_shoucheng/killed_mgb"))*40;
         job_exp=job_exp+((int)me->query_temp("guo_jianlou/killed_mgb"))*50; 
        job_pot=job_exp*2/3;
        job_tihui=job_pot/2;
        reward=((int)me->query_temp("guo_shoucheng/killed_mgb")
               + (int)me->query_temp("guo_jianlou/killed_mgb"))/10+1;

        tell_object(me, HIW"你被奖励了"+chinese_number(job_exp)+"点经验值及"+chinese_number(job_pot)+"点潜能及"+chinese_number(job_tihui)+"点体会！\n"NOR);
        me->apply_condition("guojob2_busy",4);
        me->add("combat_exp", job_exp);
        me->add("potential",job_pot);
        me->add("experience",job_tihui);
        me->add("guo_shoucheng/reward_exp", job_exp);
        me->add("guo_shoucheng/reward_potential",job_pot);  
        me->add("guo_shoucheng/reward",reward);  
        me->delete_temp("guo_jianlou");    
        me->delete_temp("guo_shoucheng");        
        return "“"+RANK_D->query_respect(me)
               +"，为国杀敌，奋勇当先，当记军功"HIY+chinese_number(reward)+NOR+CYN"策！！！”\n";
}

string ask_chetui()
{
         object me;
         me = this_player();
         if( !me->query_temp("guo_shoucheng/start_job") )
         return "你没有领任务,跑这里瞎嚷嚷什麽?";
         me->apply_condition("jobshadi_limit",0);
         me->add("combat_exp",-100+random(20));
         me->apply_condition("jobshadi_failed",6);
         me->delete_temp("guo_shoucheng");
         me->delete("guo_shoucheng/failed");
         return "没关系,下次继续努力 。";
}

string ask_lianzhu()
{
      object me=this_player(),ob=this_object();

      if ( me->query("guo_shoucheng/reward") > 100)
      {
       message_vision(HIC"$N哈哈大笑道：“这套连珠箭法(lianzhu-arrow)我就"
       +"传于你了，\n望你奋勇杀敌，多立战功，我也无憾了！\n"NOR,ob);
       return "时间紧迫，现在就开始学吧(qingjiao lianzhu-arrow)！\n";
      } else
      {
       message_vision(HIC"$N微微点头道：“这套连珠箭法(lianzhu-arrow)是我的"
       +"毕生心血之作，\n不便轻易相传！！\n"NOR,ob);
       return "若阁下真有奋勇杀敌，助我大宋之心，日后必慷慨相送！\n";
      }
}

void init()
{
   object me=this_player();
   if( me->query("guo_shoucheng/reward")>100)
   add_action("do_study","qingjiao");
}

int do_study(string arg)
{
     string skill; 
     object me=this_player(),ob=this_object();

     if( !arg || arg!="lianzhu-arrow")
     return notify_fail("你要向郭靖请教(qingjiao)什么？\n"); 
      
     if( me->query_skill("lianzhu-arrow",1) > me->query_skill("arrow",1) )
     return notify_fail("你的基本箭法太差了，无法继续学习连珠箭法。\n"); 

     if( me->query_skill("lianzhu-arrow",1)*me->query_skill("lianzhu-arrow",1)
        > me->query("guo_shoucheng/reward")*50 )
     return notify_fail("你的守城军功不够多，岳飞不愿继续教你了！\n"); 

     if( me->query("learned_points") >= me->query("potential") )
     return notify_fail("你的潜能不够了！\n"); 

     if( me->query("jing") < 100 || me->query("qi") < 400 )
     return notify_fail("你现在太累了，先休息一下吧！\n"); 

     me->receive_damage("qi",10 + random(40));
     me->receive_damage("jing", 10 + random(40));        
     me->add("learned_points",1);
     message_vision(HIC"$N指点了$n一些有关"HIW"「连珠箭法」"HIC"的问题，"
                    +"$n似乎有些心得。\n"NOR,ob,me);
     me->improve_skill("lianzhu-arrow",random(me->query_skill("arrow",1)),0);

     return 1;
}

int ask_degree()
{
        int lv;
        object ob = this_player();

        if( ob->query_temp("degree_jungong") )
        {
         command("say "+RANK_D->query_respect(ob)+"稍安勿躁，"
                                     +"我已经派人前往请封了！\n");
         return 1;
        }

        if (ob->query("guo_shoucheng/reward") > (100*(1+ob->query("degree_jungong"))*(1+ob->query("degree_jungong"))))
        lv = ob->query("degree_jungong") + 1;

        if( lv > sizeof(degree_desc) )
        {
         command("say "+"草民岂敢为大人请封，大人若亲自"
                 +"前往朝纲，前途自不限量！\n");
         return 1;   
        }

        if( lv <= ob->query("degree_jungong") )
        {
         command("say "+ob->query("name")
               +"，要获得更高的策封，必须多立军功才可以啊！\n");
         return 1;
        }
        command("say "+RANK_D->query_respect(ob)+"请稍候，"
        +"我即刻派人前往京城为"+RANK_D->query_respect(ob)+"请封！\n");

        call_out("add_degree",10,ob,lv);
        ob->set_temp("degree_jungong",1);
        message("channel:rumor",MAG"【大宋襄阳】"NOR+YEL
        +CHINESE_D->chinese_date((time()-14*365*24*60*60))
        +"，一匹快马从襄阳出发，直奔大宋京城！\n"NOR,users());

        return 1;
}

int add_degree(object ob,int lv)
{
        string degree,old_degree;
        degree=degree_desc[lv-1];

        if( ob->query("degree") ) old_degree=ob->query("degree");
        else old_degree="";

        message("channel:rumor",MAG"【大宋京城】"HIY"奉天承命，皇帝诏曰："
        +"策封 "+old_degree+" "+HIW+ob->query("name")
        +HIY" 为大宋 "NOR+degree+HIY"，钦此！\n"NOR,users());
        ob->delete_temp("degree_jungong");

        if( ob->query("degree") )
        {
         if( ob->query("degree_ask") )
         degree=HIM " ☆ " NOR+clear_degree(ob->query("degree"))
              +HIM " ☆ " NOR+degree+HIM " ☆ "NOR;
         else
         degree=HIM " ☆ " NOR+clear_degree(ob->query("degree"))
              +degree+HIM " ☆ " NOR;
        } else
         degree=HIM " ☆ " NOR+degree
              +HIM " ☆ " NOR;   

        ob->set("degree_jungong",lv);
        ob->set("degree",degree);
        ob->add("weiwang",lv*500); 
        return 1;
}

string clear_degree(string arg)
{
        if( (strsrch(arg, BLU "士卒" NOR) >= 0) ||
            (strsrch(arg, BLU "游击" NOR) >= 0) ||
            (strsrch(arg, HIC "参将" NOR) >= 0) ||
            (strsrch(arg, HIC "裨将" NOR) >= 0) ||
            (strsrch(arg, HIY "佐将" NOR) >= 0) ||
            (strsrch(arg, HIY "副将" NOR) >= 0) ||
            (strsrch(arg, HIR "将军" NOR) >= 0) ||
            (strsrch(arg, HIR "提督" NOR) >= 0) ||
            (strsrch(arg, HIM " ☆ " NOR) >= 0))
          {
            arg = replace_string(arg, BLU "士卒" NOR,"");
            arg = replace_string(arg, BLU "游击" NOR,""); 
            arg = replace_string(arg, HIC "参将" NOR,"");
            arg = replace_string(arg, HIC "裨将" NOR,"");   
            arg = replace_string(arg, HIY "佐将" NOR,"");
            arg = replace_string(arg, HIY "副将" NOR,"");   
            arg = replace_string(arg, HIR "将军" NOR,"");
            arg = replace_string(arg, HIR "提督" NOR,"");   
            arg = replace_string(arg, HIM " ☆ " NOR,"");
          }
          return arg;
}

string ask_canjun()
{
        object me = this_player(); 
        string temp;  
       int jungong, reward;

        if( me->query_temp("jun_quest") )
         return "将军已经披甲上阵了，快到前方去吧！？\n";
        
        if( me->query("age") < 18 )
         return RANK_D->query_respect(me)
                              +"，你还小，以后再来为国效力吧！\n";

        if( me->query("combat_exp") < 3000000 )
         return RANK_D->query_respect(me)
                     +"其志可嘉，无奈手无缚鸡之力，还是请回吧！\n";

        jungong=me->query("degree_jungong");
        if( jungong < 4 )
         return "您的军衔太低微了，到前方估计没什么用啊！\n";

        temp=read_file("/quest/quest_jun/song/master");
        if( temp == "" )
         return "现在前方没有战事，将军以后再来吧！\n";

             me->set_temp("jun_quest/party","song");
        me->delete("party");
        reward = 0; 
        temp = sprintf("%d", reward); 
        write_file("/quest/quest_jun/song/reward", temp, 1); 
        return "将军来的正是时候，请马上出发奔赴前线支援吧！\n";
}

