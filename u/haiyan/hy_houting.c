#include <ansi.h>
#include <mudlib.h>
#include <getconfig.h>

inherit ROOM; 
int top_list(object ob1,object ob2);
int get_score(object ob);

void create() 
{ 
     set("short", "后  厅"); 
     set("long", @LONG 
这里是海燕的用来测试的地方。
LONG); 
     set("exits", ([ 
         "east"     : __DIR__"hy_hy01",  
         "down"     : "/d/city/wumiao2" ,
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
}

void init()
{
     add_action("do_xiake","xiake");
}

int do_xiake(object me, string arg)
{
        
        object *list,*ob;
        int i,num;
        string msg;

        ob = filter_array(objects(), (: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));
        msg =  HIY"\n            ┏  "+BRED HIR+LOCAL_MUD_NAME()+"在线十大侠客"NOR+ HIY"  ┓\n"NOR+HIM;
        msg += "┏━━━┯━┻━━━━━━━━┯━━┻━━━┯━━━━━┓\n";
        msg += "┃ 名次 │    高        手    │ 门      派 │ 正    神 ┃\n";
        msg += "┠───┴──────────┴──────┴─────┨\n";
        num = 10;

        for (i = 0 ;i < num ; i++) {
                if( i >= sizeof(list)) 
                        msg += "┃暂时空缺。                                            ┃ \n";
                else {
                        if(list[i] != me) msg += BBLU HIY;
                        if(list[i] == me) msg += BYEL HIY;
                        msg += sprintf("┃%-7s %-22s%-16s %5d  ┃\n"NOR+HIM,
                                       chinese_number(i+1),
                                       list[i]->query("name")+"("+list[i]->query("id")+")",
                                       list[i]->query("family")?  list[i]->query("family/family_name"):"普通百姓",
                                       get_score(list[i]));
                }
        }
        msg += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
        msg += HIW"  您现在的正神是："+sprintf("%5d",get_score(me))+"。\n"NOR; 
        write(msg);
        return 1;

}
int top_list(object ob1, object ob2)
{
        int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

        return (score2 >= score1) ? 1 : -1;
}

int get_score(object ob)
{
        int score;
        score = ob->query("shen");
        return score;
}

