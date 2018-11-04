// qian.c
// originally coded by xiang

inherit NPC;
inherit F_BANKER;
void create()
{
        set_name("Ǯ�ۿ�", ({"qian yankai", "qian", "yankai"}));
        set("title", "Ǯׯ�ƹ�");
        set("nickname", "������");
        set("gender", "����");
        set("age", 34);
        set("str", 22);
        set("int", 24);
        set("dex", 18);
        set("con", 18);
        set("qi", 500);
        set("max_qi", 500);
        set("jing", 100);
        set("max_jing", 100);
        set("shen", 0);

        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 2);
        set("chat_msg", ({
        	"Ǯ�ۿ�������˵�����������Ѿ����ϰ������ʷ���ڽ��Ͽ���˵"
		"�ǵ�һ�ҡ�\nǮ�ۿ�Ц��˵�����ڱ����Ǯ����Ϣ��ȡǮ��ʮ��"
		"֮һ�����ѣ��͹������Ű�ɡ�\n"
        }));
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);
        setup();
}

void init()
{
        object ob;
        
        ::init();        
        if (base_name(environment()) != this_object()->query("startroom")) 
                return;
                
        if (interactive(ob = this_player()) && ! is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 0, ob);
        }
        add_action("do_check", "check");
        add_action("do_check", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        add_action("do_tax", "tax");
        delete_temp("busy");
}
void greeting(object ob)
{
        string bunch;
        int money;
        
        ob = this_player();
        
        if (! stringp(bunch = ob->query("bunch/bunch_name")))            
        {
                return;
        }
        
        if (ob->query("bunch/level") != 9)
        {
                message_vision("$NЦ����Ķ���$n��������������ʱ���˴�ת�ʰ�����\n", this_object(), ob);   
                return;
        }        

        money = BUNCH_D->query(bunch + "/bangzhu_money");
        if (money < 1)
        {
                message_vision("$N��$n��Ц��������" + bunch + "��Ŀǰ���ʿ�ת����\n", this_object(), ob);
                return;
        }

        BUNCH_D->set(bunch + "/bangzhu_money", 0);        
        BUNCH_D->save();
        
        if ((int)ob->query("balance") + money < 2000000000)
                ob->add("balance", money);
        ob->save();
        
        message_vision("$N����" + bunch + "�����������" + MONEY_D->money_str(money) + 
                        "ת����$n�����¡�\n", this_object(), ob);

}


