// sample master.c code
// xiake island master.c

inherit NPC;
inherit F_MASTER;

string ask_me();
int auto_perform();

void create()
{
        set_name("³�н�", ({"lu youjiao", "lu", "youjiao"}));
        set("title", "ؤ��Ŵ�����");
        set("nickname", "�ư���ͷ");
        set("gender", "����");
        set("age", 45);
        set("long", 
                "³�н���Ȼ�书�㲻�ö�����֣������ڽ�����ȴ����������\n"
                "��Ϊ����ؤ�����������壬���¹������䣬��ú��߹������ء�\n");
        set("attitude", "peaceful");
        set("rank",9);
        set("str", 35);
        set("int", 21);
        set("con", 32);
        set("dex", 25);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1200);
        set("max_jing", 1200);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 80);
        
        set("combat_exp", 1000000);
        set("shen_type", 1);
        set("score", 25000);
        
        set_skill("force", 180);
        set_skill("jiaohua-neigong", 180);
        set_skill("unarmed", 180);
        set_skill("changquan", 150);
        set_skill("hand",160);
        set_skill("shexing-diaoshou",160);
        set_skill("dodge", 150);
        set_skill("feiyan-zoubi", 150);
        set_skill("parry", 170);
        set_skill("staff", 170);
        set_skill("begging", 120);
        set_skill("checking", 150);
        set_skill("jueming-tui", 180);

        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "jueming-tui");
        map_skill("parry", "jueming-tui");
       map_skill("hand","shexing-diaoshou");
        map_skill("dodge", "feiyan-zoubi");
        create_family("ؤ��", 18, "�Ŵ�����");
        
        set("inquiry", ([
                "�ȷ�ͼ��" : (: ask_me :),
                "ͼ��" : (: ask_me :),
                "�ܼ�" : (: ask_me :),
                "����" : (: ask_me :),
                ]));

        set("book_count", 1);

        set("chat_chance_combat", 50);
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.xianglong" :),
                (: exert_function, "recover" :),
        }) );

        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(8);
        carry_object("/d/gaibang/obj/budai")->wear();
        
}


void attempt_apprentice(object ob)
{
        if (ob->query("class")=="bonze") {
                if (ob->query("gender")=="Ů��")
                        command ("say ʦ̫���ǳ����ˣ���ô���ڱ������л����أ�");
                return;
        }

        if ( (int)ob->query("int") >= 25 && !(int)ob->query("tianmo_jieti")) {
                command("say ����ؤ�������һ���Ը���Ϊ����" + 
                RANK_D->query_respect(ob) + "�ϻ۹��ˣ��ƺ�����ѧؤ��Ĺ���");
                return;
        }

        if( ob->query("family/family_name") != "ؤ��" )
        {
                if( ob->query("rank") > 1 ) {
                        command("say ����������Ϊ�ȣ����ݲ�����������������ļһ\n");
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
}

string ask_me()
{
        mapping fam; 
        object ob, me=this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "ؤ��")
                return RANK_D->query_respect(this_player())+"�뱾�����ԨԴ����ô�ܿ�������Ҫ����ͼ�⣿";

       if ((fam = this_player()->query("family")) || fam["family_name"] = "ؤ��")
                return RANK_D->query_respect(this_player())+"����ȥ�����о�";
         
}

int accept_object(object me, object obj)
{

        object ob = this_player();

        if ( (obj->name() == "ţƤ�ƴ�" || obj->name() == "����ƴ�")
        && obj->query("liquid/type") == "alcohol" ) {
                call_out("drink_jiudai", 1, this_object(), ob, obj);
                return 1;
        }

        command( "say �ⶫ���Ͻл��Ҳ�����Ȥ���������Ը������Űɡ�" );
        return 0;
}

int drink_jiudai(object me, object ob, object obj)
{
        if ( obj->query("liquid/remaining") >= 5 ) {
                message_vision("³�н�����ƴ�һ��ͷ���������ƹ�ཹ�ཱུ�һ��������\n", me);
                command( "taste" );
                if ( ob->query("family/family_name") == "ؤ��" ) {
                        command( "nod" );
                        command( "say �ã���ʲô�������ʰɡ�" );
                        ob->set_temp("lu", 1);
                }
                else {
                        command( "say ��л��λ"+RANK_D->query_respect(ob)+"������治����\n" );
                        command( "smile" );
                }
        }
        else if ( obj->query("liquid/remaining") == 0 ) {
                message_vision("³�нŴ�ŭ˵�����㵱����ɵ�İ����ø��վƴ�����ǲ���ӣ�\n", me);
                if ( ob->query("family/family_name") == "ؤ��" ) {
                        command( "slap " + obj->query("id") );
                        ob->set_temp("lu", 2);
                }
        }
        else {
                command( "say �ٺ٣�����ô��ƾ�����ָ���㣿̫���˰ɣ�");
        }

        remove_call_out("destroy_it");
        call_out("destroy_it", 1, obj);
        return 1;
}
        
void destroy_it(object obj)
{
        destruct(obj);
}


int auto_perform()
{
        object me=this_object();
        object weapon=me->query_temp("weapon");
        object opp=me->select_opponent();

        if ( !me->is_fighting() ) {
                if ( me->query("eff_qi") < me->query("max_qi") )
                        exert_function("heal");
                me->set("jiali", 50);

                return 1;
        }

        if ( !me->query_temp("powerup") ) {
                return exert_function("powerup");
        }

        if ( objectp(weapon) ) {
                if ( !me->query_temp("shengang") )
                        return exert_function("shengang");

                if ( weapon->query("skill_type") == "staff" )
                        return perform_action("staff.chan");
        }
        else {
                        return perform_action("strike.leiting");
        }
}

