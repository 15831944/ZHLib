// Updated by Lonely

#include <ansi.h>
inherit NPC;

mapping *first_name=({
([      "name":"孙",      "id":"sun"    ]),
([      "name":"吴",      "id":"wu"     ]),
([      "name":"独孤",    "id":"dugu"   ]),
([      "name":"赖",      "id":"lai"    ]),
([      "name":"林",      "id":"lin"    ]),
([      "name":"赵",      "id":"zhao"   ]),
([      "name":"任",      "id":"ren"    ]),
([      "name":"钱",      "id":"qian"   ]),
([      "name":"李",      "id":"li"     ]),
([      "name":"张",      "id":"zhang"  ]),
([      "name":"臧",      "id":"zang"   ]),
([      "name":"徐",      "id":"xu"     ]),
([      "name":"杨",      "id":"yang"   ]),
([      "name":"邱",      "id":"qiu"    ]),
([      "name":"舒",      "id":"shu"    ]),
([      "name":"叶",      "id":"ye"     ]),
([      "name":"刘",      "id":"liu"    ]),
([      "name":"周",      "id":"zhou"   ]),
([      "name":"杨",      "id":"yang"   ]),
([      "name":"王",      "id":"wang"   ]),
([      "name":"梁",      "id":"liang"  ]),
([      "name":"黄",      "id":"huang"  ]),
([      "name":"林",      "id":"lin"    ]),
([      "name":"陈",      "id":"chen"   ]),
([      "name":"谢",      "id":"xie"    ]),
([      "name":"鲁",      "id":"lu"     ]),
([      "name":"何",      "id":"he"     ]),
([      "name":"曾",      "id":"zeng"   ]),
([      "name":"郭",      "id":"guo"    ]),
([      "name":"成",      "id":"cheng"  ]),
([      "name":"南宫",    "id":"nangong"  ]),
([      "name":"欧阳",    "id":"ouyang"   ]),
([      "name":"长孙",    "id":"zhangsun" ]),
([      "name":"慕容",    "id":"murong"   ]),
([      "name":"西门",    "id":"ximen"    ]),
([      "name":"公孙",    "id":"gongsun"  ]),
([      "name":"端木",    "id":"duanmu"  ]),
});

mapping *second_name=({
([      "name":"",      "id":""      ]),
([      "name":"风",    "id":"feng"  ]),
([      "name":"德",    "id":"de"    ]),
([      "name":"晓",    "id":"xiao"  ]),
([      "name":"富",    "id":"fu"    ]),
([      "name":"达",    "id":"da"    ]),
([      "name":"默",    "id":"mo"    ]),
([      "name":"玄",    "id":"xuan"  ]),
([      "name":"海",    "id":"hai"   ]),
([      "name":"自",    "id":"zi"    ]),
([      "name":"泰",    "id":"tai"   ]),
([      "name":"昭",    "id":"zhao"  ]),
([      "name":"",      "id":""      ]),
([      "name":"通",    "id":"tong"  ]),
([      "name":"耘",    "id":"yun"   ]),
([      "name":"奋",    "id":"fen"   ]),
([      "name":"宏",    "id":"hong"  ]),
([      "name":"荣",    "id":"rong"  ]),
([      "name":"鹏",    "id":"peng"  ]),
([      "name":"冲",    "id":"chong" ]),
([      "name":"灏",    "id":"hao"   ]),
([      "name":"思",    "id":"si"    ]),
([      "name":"理",    "id":"li"    ]),
([      "name":"刚",    "id":"gang"  ]),
([      "name":"武",    "id":"wu"    ]),
([      "name":"逸",    "id":"yi"    ]),
});
          
mapping *third_name=({
([      "name":"峰",    "id":"feng"  ]),
([      "name":"华",    "id":"hua"   ]),
([      "name":"奇",    "id":"qi"    ]),
([      "name":"歌",    "id":"ge"    ]),
([      "name":"旭",    "id":"xu"    ]),
([      "name":"发",    "id":"fa"    ]),
([      "name":"威",    "id":"wei"   ]),
([      "name":"晖",    "id":"hui"   ]),
([      "name":"城",    "id":"cheng" ]),
([      "name":"轩",    "id":"xuan"  ]),
([      "name":"勇",    "id":"yong"  ]),
([      "name":"泰",    "id":"tai"   ]),
([      "name":"在",    "id":"zai"   ]),
([      "name":"君",    "id":"jun"   ]),
([      "name":"军",    "id":"jun"   ]),
([      "name":"凡",    "id":"fan"   ]),
([      "name":"伟",    "id":"wei"   ]),
([      "name":"帆",    "id":"fan"   ]),
([      "name":"雄",    "id":"xiong" ]),
([      "name":"涛",    "id":"tao"   ]),
([      "name":"波",    "id":"bo"    ]),
([      "name":"杰",    "id":"jie"   ]),
([      "name":"郎",    "id":"lang"  ]),
});                                     

string *degree_desc=({
       HIC "裨将" NOR,
       HIY "佐将" NOR,
       HIY "副将" NOR,
       HIR "将军" NOR,
       HIR "提督" NOR,
       HIR "总督" NOR,
       MAG "兵部侍郎" NOR,
       MAG "兵部尚书" NOR,
       HIB "镇北节度使" NOR,
});                            

int get_exp_rate();
int get_level(int exp);   

// 求三次方根
int sqrt3(int x) 
{
        float y = 1.0 / 3.0; 
        x = pow(x, y); 
        return x; 
}

void create()
{
        int lvl, skill, nl, exp;
        string id, idf;
        string name;  
        int index;

        index = random(sizeof(first_name));
        name = first_name[index]["name"];
        id = first_name[index]["id"];
        idf = id; 

        index = random(sizeof(second_name));
        name += second_name[index]["name"];
        id += " " + second_name[index]["id"];

        index = random(sizeof(third_name));
        name += third_name[index]["name"];
        id += third_name[index]["id"];

        set_name(name, ({id, idf}));

        set("gender", "男性");
        set("age", random(20) + 20);
        set("str", 160);
        set("dex", 160);
        set("con", 160);

        set("long", "这是一名大宋将军，正威风凛凛地巡视着自己的队伍。\n");

        set("int", 30);
        set("str", 30 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("age", 20 + random(30));
        set("per", 15 + random(15)); 
        set("age", 20 + random(30));
        set("per", 15 + random(15));                                         
        set("no_get",1);
        
        exp = get_exp_rate() / 10;
        skill = get_level(exp);
        
        if (skill < 100) skill = 100;
        
        set("combat_exp", exp);       
        nl = skill * 10 + exp / 10000;
        
        set("max_neili", nl);
        set("neili", query("max_neili") * 3 / 2); 
        set("max_jingli", nl);
        set("jingli", query("max_jingli"));
        set("max_qi", nl * 10);
        set("qi",  query("max_qi"));
        set("eff_qi", query("max_qi"));
        set("max_jing", nl);
        set("eff_jing", query("max_jing"));
        set("jiali", skill / 2); 

        set_skill("taiji-shengong", skill);
        set_skill("wuhu-duanmendao", skill);
        set_skill("tiyunzong", skill);
        set_skill("taiji-quan", skill);
        set_skill("cuff", skill);
        set_skill("force", skill);
        set_skill("dodge", skill);
        set_skill("blade", skill);
        set_skill("parry", skill);
        set_skill("arrow", skill*2/3);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("blade", "wuhu-duanmendao");   
        prepare_skill("cuff", "taiji-quan");
  
        set_temp("jun_quest/party", "song"); 
        set("quest_ob", 1);  
        set("start_time", time());
        add_temp("apply/armor", 400);
        add_temp("apply/damage", 100);
        setup();
        
        lvl = (query("str") + skill / 10) / 10 - 1;
        if (lvl > 8) lvl = 8;
        lvl = lvl - 2;
        if (lvl < 3) lvl = 3;
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl);
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/tiejia")->wear();   
        carry_object(__DIR__"obj/pifeng")->wear();  
}

int get_level(int exp)
{
        int level;
        
        exp /= 1000;
        level = sqrt3(exp);
        return level * 10;
}

int get_exp_rate()
{
        int max_exp = 10000000, exp_rate;
        
        foreach (object user in users())
        {
                if (! environment(user)) continue;
                if (wizardp(user)) continue;
                
                if (user->query("combat_exp") > max_exp)
                        max_exp = (int)user->query("combat_exp");
        }

        return max_exp;
}

void change_ob()
{ 
        int jungong;
        object ling, king;

        jungong = 4 + random(query("combat_exp") / 5000000 + 1);
        if (jungong > 12) jungong = 12;
        set("title", degree_desc[jungong - 4]);
        set("degree_jungong", jungong);
        
        king = WAR_D->query_king();
        
        ling = new("/adm/npc/obj/lingjian");
        ling->set("owner", query("id"));
        
        if (objectp(king))
                ling->set("master", king->query("id"));
                
        ling->move(this_object());
        ling->check_me(this_object());
        return;
}

void init()
{     
        if (this_player()->query_temp("jun_quest/party") != "meng")
        {
                add_action("do_kill", "team kill");
                add_action("do_kill", "touxi");
                add_action("do_kill", "kill");
                add_action("do_kill", "hit");
                add_action("do_kill", "fight");
                add_action("do_kill", "steal");
                add_action("do_kill", "beg");
                add_action("do_kill", "persuade");
        }                    
}       

int do_kill(string arg)
{
        string what, who;
        
        if (! arg) return 0;
                               
        if (this_object()->id(arg))
        {
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        }
        else
        if (sscanf(arg,"%s from %s", what, who) == 2 && this_object()->id(who))
        {
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        }
        return 0;
}

void die()
{
        message_vision("$N率领的宋军将士寡不敌众，不幸"
                + HIR "全军覆没" NOR "！\n", this_object());
        destruct(this_object());
        return;
}

