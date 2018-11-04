// /kungfu/class/gaibang/jian.c

inherit NPC;
inherit F_MASTER;

string ask_me(string, object);
int ask_dai();
int auto_perform();

void create()
{
        set_name("����", ({"jian zhanglao", "jian", "zhanglao"}));
        set("title", "ؤ��Ŵ�����");
        set("nickname", "ִ������");
        set("gender", "����");
      set("no_get",0);
        set("age", 50);
        set("long", 
                "������ؤ���ִ�����ϣ�������ִ�Ʒ����Լ�������ȡ�\n"
                "������������𣬵�������˭���������־������顣\n");

        set("attitude", "peaceful");
        set("rank",9);
        
        set("str", 27);
        set("int", 22);
        set("con", 24);
        set("dex", 20);

        set("qi", 900);
        set("max_qi", 900);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);

        set("combat_exp", 880000);
        set("score", 20000);

        set_skill("force", 170);
        set_skill("jiaohua-neigong", 170);
        set_skill("unarmed", 165);
        set_skill("changquan", 165);
        set_skill("dodge", 150);
        set_skill("feiyan-zoubi", 150);
        set_skill("parry", 175);
        set_skill("staff", 150);
        set_skill("jiaohua-bangfa", 150);

        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
        map_skill("parry", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "jiaohua-bangfa");

        create_family("ؤ��", 18, "�Ŵ�����");

        set("chat_chance", 1);
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: auto_perform :),
        }) );

        set("inquiry", ([
                "������" :     (: ask_me, "ling" :),
                "����"   :     (: ask_dai :), 
                 
        ]));

        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(8);
        carry_object("/d/gaibang/obj/budai")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
        
}

void init()
{
        object ob;
        mapping myfam;
        
        ::init();
        set_heart_beat(1);      
        if (!living(this_object())) return;
        if (interactive(ob = this_player()) && !is_fighting() 
        && file_name(environment(this_object())) == "/d/city/gbandao" ) {
                myfam = (mapping)ob->query("family");
          if ((!myfam || myfam["family_name"] != "ؤ��") &&
                        (!wizardp(ob))) {
                        remove_call_out("saying");
                        call_out("saying",2,ob);
                }
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment())
                return;

        message_vision("\n���Ͽ���$Nһ�ۣ������˵����������������˼�˵�Ҳ���"
            "�������ؤ����ӣ�\n���ֲ�����ؤ��Ҵ����ܿ��԰ɣ���\n"
            "˵������һ̧��$N˳��Ӧ��һ������ɵġ�ƨ�����ƽɳ����ʽ��"
            "������ߴ\n\n", ob);
        remove_call_out("kicking");
        call_out("kicking",1,ob);
        
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment())
                return;

        ob->move("/d/city/pomiao");
         message("vision","ֻ�����ء���һ����������" +  ob->query("name") +
                "��С������˳�����ƨ������һ�������Ьӡ��\n", environment(ob), ob);
}

void attempt_apprentice(object ob)
{
/*        if ((int)ob->query_str() < 25) {
                command("say ����ؤ�������һ���Ը���Ϊ����" + 
                RANK_D->query_respect(ob) + "����̫�����ƺ�����ѧؤ��Ĺ���");
                return;
        }

        if( ob->query("family/family_name") != "ؤ��" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say �ߣ�����������Ϊ�ȣ����ݲ�����������������ļһ\n");
                        return;
                }

                command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
                "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
                ob->set("rank", 1); 
                command("recruit " + ob->query("id"));
                ob->set("title", "ؤ��һ������");
        } 
        else
        {
                ob->set_temp("title", ob->query("title"));
                command("recruit " + ob->query("id"));
                ob->set("title", ob->query_temp("title"));
                ob->delete_temp("title");
        }
*/
      command("say �Ϸ���ͽ�ܣ�" + RANK_D->query_respect(ob) + "������ذɡ�");
}

int accept_object(object ob, object obj)
{
        int rank;
        object me = this_object();

 if( ob->query("family/family_name") != me->query("family/family_name") ) {
                command("say ���Ҳ���ͬһ���ɣ���������������к��ã��� ��ذɣ�");
                return 0;
        }

        rank = ob->query("rank");
        if( rank >= 9 ) {
                command("say ���ڰ���λ���Ŵ����ϣ���λ�����ڰ��������޷������ˣ�");
                return 0;
        }

        if( obj->query("id") == "qingzhu ling" ) 
        {
                if( obj->query_temp("owner") != ob->query("name") ) {
                        command("say �㲻���������������ˣ�");
                        return 0;
                }
                if( !obj->query_temp("win_times") ) {
                        command("say ����δսʤһ��ͬ��ʦ�ֵܣ������Ͻ�����������");
                        return 0;
                }
                if( !obj->query_temp("win_last") ) {
                        command("say ����δսʤͬ����ʦ�֣������Ͻ�����������");
                 return 0;
                }
                if( ob->query("combat_exp") < ((2000 + 500*(rank-1)) * rank*rank)) {
                        command("say ���ս�����鲻�㣬�����Ͻ�����������");
                        return 0;
                }
                if( !objectp(present("bu dai", ob)) ) {
                        command("say �����ϵĲ����Ķ�ȥ�ˣ�����Ϊؤ����ӣ��������ڣ�����������");
                        return 0;
                }

                command("say �ã�����������������ˡ�" + ob->query("name") + "����Ը�����Ϊؤ��" +
                                chinese_number(ob->query("rank")+1) + "��������");

                add_action("do_say", "say");
                ob->delete_temp("leaving", 1);
                ob->set_temp("thinking", 1);
                ob->set_temp("new_rank", ob->query("rank")+1);
                remove_call_out("destroying");
                call_out("destroying", 1, ob, obj);
                return 1;
        }

        command("smile");
        command("say �ⶫ�����ҿ�û��ʲô�á�");
        command("give " + obj->query("id") + " to " + me->query("id"));
        return 0;
}

void destroying(object ob, object obj)
{
        int i;
        object *inv;
        inv = all_inventory(ob);
        for(i=0; i<sizeof(inv); i++) {
                if(inv[i]->query("id") == obj->query("id"))
                        destruct(inv[i]);
        }

        destruct(obj);
        return;
}

int do_say(string arg)
{
        object me, ob, dai;
        int i_rank, exp_substracted = 0;

        me = this_object();
        ob = this_player();
                
        if( !arg || arg=="" ) return 0;
        if( arg=="Ը��" && ob->query_temp("thinking") 
        && ob->query_temp("new_rank") == ob->query("rank") + 1
        && objectp(present("bu dai", ob)) ) 
        {
                if( ob->query("rank") < 9 )
                        ob->set("rank", ob->query_temp("new_rank"));
                else return 0;

                ob->delete_temp("thinking");
                ob->delete_temp("gaibang_winner");
                ob->delete_temp("new_rank");

                if( ob->query("rank") >= 9 )
                        ob->set("title", "ؤ��" + chinese_number(ob->query("rank")) + "������");
                else
                        ob->set("title", "ؤ��" + chinese_number(ob->query("rank")) + "������");

                ob->add("combat_exp", 1500 * (ob->query("rank")-1));
                tell_object(ob, "��ľ���ֵ�����" + chinese_number(1500 * (ob->query("rank")-1)) + "�㣡\n");

                command("say ��ϲ��ϲ���ӽ��Ժ�����Ǳ���" + chinese_number(ob->query("rank")) + "�������ˣ�");

                if(objectp(dai = present("bu dai", ob)) ){
                        dai->unequip();
                        dai->add_amount(1);
                        message_vision("\n���ϴ�$N����ժ�²�����������ȡ������������" +
                                chinese_number(ob->query("rank")) + 
                                "��������������һ�����Խ���������$N���ϡ�\n\n", ob);
                        dai->wear();
                } else {
                        dai=new("/d/gaibang/obj/dai");
                        dai->move(ob);
                        message_vision("\n����ȡ��һ�����������Խ�������$N���ϡ�\n\n", ob);
                        dai->wear();
          }

                return 1;
        }

        return 0;

}
int ask_dai()
{
        object dai;
        object ob=this_player();
        if( ob->query("family/family_name") == "ؤ��" && ob->query("rank") == 1 && !objectp(present("bu dai", ob)) )
        {
                dai=new("/d/gaibang/obj/budai");
                dai->move(ob);
                message_vision("\n����ȡ��һ�����������Խ�������$N���ϡ�\nȻ�������ĳ���˵������Ϊؤ����ӣ��������ڣ�������������\n", ob);
                dai->wear();
                return 1;
        }
        else
        command("say ���´Ӻ�˵�𰡣�");
        return 1;
}

string ask_me(string name, object obj)
{
        mapping fam; 
        object me = this_player();
        
        if( !(fam = this_player()->query("family")) || fam["family_name"] != "ؤ��")
                return RANK_D->query_respect(this_player()) + 
                "����ؤ����ӣ���֪�˻��Ӻ�̸��";

        if ( name == "ling") {
                if( this_player()->query("combat_exp") < 1000 ) 
                        return RANK_D->query_respect(this_player()) + 
                        "ս�����鲻�㣬�����ʸ���ȡ�����";

          obj=new("d/gaibang/obj/qingzhu-ling");
                obj->move(this_player());
                obj->set_temp("owner", this_player()->query("name"));
                message_vision("$N����$nһ�������\n", this_object(), this_player());

                return "ƾ���������������������ʦ�ֵ��ǱȻ��书��";
        }

        
}
                

int auto_perform()
{
        object me = this_object();
  object target = me->select_opponent();
        object weapon = me->query_temp("weapon");

        if ( !me->is_fighting() ) {
                if ( me->query("eff_qi") < me->query("max_qi") )
                        exert_function("heal");
                me->set("jiali", 100);

                return 1;
        }

        if ( !me->query_temp("powerup") ) {
                return exert_function("powerup");
        }

        if ( objectp(weapon) ) {
                if ( !random( (int)me->query("combat_exp") * 2
                   / (int)target->query("combat_exp") + 1) 
                && !me->query_temp("shengang") ) 
                        return exert_function("shengang");

                if ( weapon->query("skill_type") == "staff" )
                        return perform_action("staff.feizhang");
 }
        else
                return perform_action("strike.leiting");
}


