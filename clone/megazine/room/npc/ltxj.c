#include <ansi.h>

inherit NPC;

int ask_me();
int unm;

void create ()
{
        set_name("聊天丫鬟" ,({"liaotian yahuan", "yahuan", "liaotian"}));
        set("gender","女性");
        set("title", HIW "〖地狱〗杂志社" NOR);
        set("nickname", HIB "聊无敌" NOR);
        set("age", 18);
        set("long", "聊天丫鬟虽然才到二八，但对聊天已经有了很高的造诣。\n"
                    "她有倾国倾城之貌，容色丽郁，娇艳绝伦，堪称人间仙子！\n");
        set("str", 10);
        set("dex", 16);
        set("con", 30);
        set("int", 56);

        set_skill("idle-force", 300);

        set("combat_exp", 2000);

        set("max_qi", 200);
        set("max_jing", 200);
        set("max_neili", 100);
        set("neili", 100);

        set("attitude","friendly");
        set("inquiry",([
                "为什么" : "就是不...", 
                "小桦" : "小混混一个，没什么好说的", 
                "小二邮箱" : "这个人是新手的代言人。", 
                "社长夫人" : "这个嘛.....我知道，但就是不告诉你们", 
                "打你" : "你敢的话，就试一试啊！", 
                "当心我扁你" : "你敢的话，就试一试啊！", 
                "扁你" : "你敢的话，就试一试啊！", 
                "你敢" : "我就敢！哼....", 
                "男朋友" : "这是我的秘密！", 
                "终极地狱" : "这个你都不知道？你现在玩得就是终极地狱！", 
                "爱情" : "咯咯...这个不能告诉你哦！", 
                "喝酒" : "不会.", 
                "聊些什么呢" : "这个要你说啊！", 
                "聊些什么" : "这个要你说啊！", 
                "结婚了吗" : "我为什么要告诉你呢？", 
                "结婚" : "我为什么要告诉你呢？", 
                "风狐" : "这是我们尊敬的社长大人。", 
                "聊什么" : "你想聊什么啊！", 
                "name" : "我就是专门和玩家聊天地聊天丫鬟。",
                "工作" : "就是和你们这些无聊的人聊天。",
                "屠人魔" : "这你也不知道呀，他是终极地狱的高手呀.",
                "你好漂亮" : (: ask_me :),
                "你帮我" : "我可帮不了你什么，陪你聊聊天还可以哦！",
                "help" : "我可帮不了你什么，陪你聊聊天还可以哦！",
                "陪我聊天好吗?" : "当然可以啦！",
                "chat" : "当然可以啦！",
                "聊天" : "当然可以啦！",
                "miller" : "我可是她的丫鬟！",
                "kill" : "小贝在哪啊?有人欺负我！",
                "fight" : "小贝在哪啊?有人欺负我！",
                "你多大啦" : "今年刚够18岁呢！",
                "你多大" : "今年刚够18岁呢！",
                "age" : "今年刚够18岁呢！",
                "年龄" : "今年刚够18岁呢！",
                "你在这里做什么啊？" : "陪玩家聊天呀！",
                "work" : "就是和你们这些无聊的人聊天。",
                "here" : "这里是〖地狱〗杂志社的领地。",
        ]));

        setup();
        set("chat_chance", 1);
        set("chat_msg",({ "聊天小姐得意的说道：有谁能比我还能聊天呢？\n", }));
        carry_object("/clone/cloth/female1-cloth")->wear();
        carry_object("/clone/cloth/female-shoe")->wear();

}
void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting",1, ob);
        }

        add_action("do_look", "look");
        add_action("do_hug", "hug");
        add_action("do_hug", "hug1");
        add_action("do_hug", "marry");
        add_action("do_hug", "lovelook");
        add_action("do_hug", "fang");
        add_action("do_hug", "hug2");
        add_action("do_hug", "hug3");
        add_action("do_hug", "18mo");
        add_action("do_hug", "mo");
        add_action("do_hug", "kiss");
        add_action("do_hug", "kiss1");
        add_action("do_hug", "kiss2");
        add_action("do_hug", "kiss3");
        add_action("do_hug", "love1");
        add_action("do_hug", "love2");
        add_action("do_hug", "love3");
        add_action("do_hug", "colorlook");
        add_action("do_kok", "kok");
        add_action("do_kok", "slap");
        add_action("do_kok", "kick");
        add_action("do_kok", "pat");
        add_action("do_kok", "nip");
        add_action("do_kok", "fight");
        add_action("do_kok", "kill");
        add_action("do_wuliao", "wuliao");
        add_action("do_wuliao", "chat");
}

void greeting(object me)
{
        if (me->query("id") == "wfoxd" || me->query("id") == "miller")
        {
                command("jump " + me->query("id"));
                if (me->query("id") == "miller")
                {
                        command("say 我好想你啊，你怎么现在才来啊？");
                        return;
                }
                command("say 热烈欢迎风狐社长检查工作情况！\n");
                return;
        }
 
        if (me->query("age") < 16)
        {
                 command("say 小孩子聊什么天，一边去玩！");
                 command("kick " + me->query("id"));
                 message("vision", me->query("name") + "被聊天丫鬟踢了出去。\n",
                         environment(me), ({ me }));
                 me->move("/d/city/kedian");
                 message("vison", me->query("name") + "被人从里面踢了出来。\n",
                         environment(me), ({ me }));
                 return;
        }

        if (me->query("gender") == "男性")
        {
                if (me->query("per") >= 27)
                {
                        command("wa " + query("id"));
                        command("say 这位帅哥，我们可以好好聊聊吗？\n");
                }
                else
                {
                        command("nod " + query("id"));
                        command("say 这位先生有何贵干？\n");
                }
        }

        return;
}

int do_look(string target)
{
	object me;
	object ob=this_object();

	me = this_player();
	if (target == "yahuan" || target == "liaotian yahuan" || target == "liaotian")

        {
                command("angry " + me->query("id"));
                command("say 随便看陌生女子是一种不礼貌的行为，难道这个你都不知道吗？");
        }
}

int do_hug(string target)
{
	object me;
	object ob=this_object();

	me = this_player();
	if (id(target))
        { 
                if (me->query_temp("liumang") == 1)
                {
                        message("vision", WHT + ob->query("name") + "(" +ob->query("id")+ ")：" +
                                me->query("class") + me->query("name") + "真是本性难移，现在又在耍流氓了！\n" NOR, users());
                        message_vision(HIG "聊天小姐轻轻的点了你一下，你只觉得有点晕了！\n" NOR, me);
                        me->add("jing", -400);
                        me->delete_temp("liumang");
                        return 1;
                }

                message("vision", WHT + ob->query("name") + "(" +ob->query("id")+ ")：" + "大家注意！！！" +
                                  me->query("class") + me->query("name") + "在耍流氓了！\n"NOR, users());
                message_vision(HIG "聊天小姐轻轻的点了你一下，你只觉得有点晕了！\n" NOR, me);
                me->add("jing", -300);
                me->set_temp("liumang",1);
        }
        return 1;
}

int do_kok(string target)
{
	object me;
	object ob=this_object();

	me = this_player();
	if (id(target))
  	{
                if (me->query_temp("liumang") == 1)
	 	{
                        message("vision", WHT + ob->query("name") + "(" +ob->query("id")+ ")：" +
                                          me->query("class") + me->query("name") + "真是恶习难改，现在又在欺负人了！\n" NOR,
                                          users());
                         message_vision(HIG "聊天小姐轻轻的点了你一下，你只觉得有点晕了！\n" NOR, me);
                         me->add("jing", -400);
                         me->delete_temp("liumang");
                         return 1;
                }

	  	message("vision", WHT + ob->query("name") + "(" +ob->query("id")+ ")：" + "大家注意！！！" +
                                  me->query("class") + me->query("name") + "又在欺负人了！\n"NOR, users() );
                message_vision(HIG "聊天小姐轻轻的点了你一下，你只觉得有点晕了！\n" NOR, me);
                me->add("jing", -300);
                me->set_temp("liumang",1);
        }

        return 1;
}

int ask_me()
{
	object me , ob;

	me = this_player();
	command("say 是吗？谢谢你的夸奖");
	if (random(5) == 0)
        {
	  	 command("say 既然你说的那么好听，我就给你点东西吧！");
                 ob = new("/clone/megazine/obj/zazhi2");
	  	 ob->move(me, 1);
	  	 message_vision("聊天丫鬟给$N本〖地狱〗杂志。\n",me);
        }
        return 1;
}

int do_wuliao(string target)
{
        object me;

        if (id(target)) 
                command("say 当然可以啦！就让我们开始这段闲聊吧！");

        return 1;
}
