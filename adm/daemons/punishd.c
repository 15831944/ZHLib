// punish the berays user
#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#define PK_PUNISH   "/d/special/tongtiandao"
#define ALL_PKS     99999999
#define WANT_PKS    8

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "ִ������");
        CHANNEL_D->do_channel( this_object(), "sys", "ִ�������Ѿ�������");

        remove_call_out("monitor");
        call_out("monitor", 1);
}

int clean_up() { return 1; }

void family_punish();

string *punishers = ({
        CLASS_D("xiakedao") + "/zhangsan",
        CLASS_D("xiakedao") + "/lisi",
});

string *catchers = ({
        CLASS_D("misc") + "/zhang",
});

mapping family_punishers = ([
        "�䵱��"   : ({ CLASS_D("misc") + "/chongxu" }),
        "������"   : ({ CLASS_D("misc") + "/fangsheng" }),
        "��ɽ��"   : ({ CLASS_D("misc") + "/murenqing" }),
        "������"   : ({ CLASS_D("misc") + "/guoxiang" }),
        "�һ���"   : ({ CLASS_D("misc") + "/taogu" }),
        "������"   : ({ CLASS_D("misc") + "/zhong" }),
        "ؤ��"     : ({ CLASS_D("misc") + "/wangjiantong" }),
        "��Ĺ��"   : ({ CLASS_D("misc") + "/popo" }),
        "ȫ���"   : ({ CLASS_D("misc") + "/laodao" }),
        "������"   : ({ CLASS_D("misc") + "/xiaoxian" }),
        "��ң��"   : ({ CLASS_D("misc") + "/liqiushui" }),
        "������"   : ({ CLASS_D("misc") + "/laoseng" }),
        "Ѫ����"   : ({ CLASS_D("misc") + "/hongri" }),
        "���չ�"   : ({ CLASS_D("misc") + "/tonglao" }),
        "�컨��"   : ({ CLASS_D("misc") + "/yuwanting" }),
        "Ľ������" : ({ CLASS_D("misc") + "/furen" }),
        "ŷ������" : ({ CLASS_D("misc") + "/laonu" }),
        "�������" : ({ CLASS_D("misc") + "/huyidao" }),
        "���ϻ���" : ({ CLASS_D("misc") + "/duansh" }),
]);

void monitor()
{
        int i;
        object *obs;
        string *aviable;
        string punisher;
        string catcher;
        string msg;

        remove_call_out("monitor");
        call_out("monitor", 180 + random(60));

        if (VERSION_D->is_boot_synchronizing())
                // ����������ͬ���汾����ô�������ͷ�ϵͳ
                return;

	// when the pking was going, I won't let the punisher out,
	// because the competitor may in PKD.
	if (PK_D->is_pking())
		return;

/*      //////////// ��̳����վ
        if (LEAGUEWAR_d->is_working())
        {}
*/
        CHANNEL_D->do_channel(this_object(), "sys",
			      "��������ɨ������������ҡ�");

        // search all the player for punishing
        obs = filter_array(users(),
			   (: $1->query("combat_exp") >= 100000 &&
                    ////////////////////////////////////////////// $1->query("combat/need_punish") &&
                              ! $1->is_in_prison() &&
			      ! $1->is_ghost() &&
                              //! wizardp($1) &&
			      environment($1) :));

	if (sizeof(obs))
        {
        	obs = sort_array(obs, (: $2->query("combat_exp") -
        			         $1->query("combat_exp") :));
                i = 0;
                for (i = 0; i < sizeof(obs); i ++)
                {            
                        if (! objectp(obs[i]) ||
                            ! living(obs[i]) ||
                            obs[i]->query("doing"))continue;
                        if (base_name(environment(obs[i])) == PK_PUNISH)continue;
                        if (obs[i]->query("combat/WPK") > WANT_PKS || 
                            obs[i]->query("combat/PKS") > ALL_PKS)
                                  obs[i]->apply_condition("pk", 7200); // 24Сʱ

                        if (! obs[i]->query_condition("pk"))continue;

                        obs[i]->set("startroom", PK_PUNISH);
                        tell_object(obs[i], HIC "ִ����������㣺����PK�����ˣ������߰ɣ���\n" NOR);
                        tell_object(obs[i], HIG "��Ȼ����о�ͷһ�� ����\n" NOR);
                        obs[i]->move(PK_PUNISH);
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                              "��˵" + obs[i]->name(1) + HIM "����PK���ȣ���������" HIW 
                                              "ͨ�쵺" HIM "��ʮ��Сʱ��\n" NOR);
                        
                        log_file("pk_punish", sprintf("%s(%s) �� %s ����PK���ȱ�����24Сʱ��\n",
                                                      obs[i]->name(), 
                                                      obs[i]->query("id"), 
                                                      ctime(time())));
                }
        }

        // search all the player for catching
        obs = filter_array(users(),
			   (: $1->query("combat_exp") < 300000 &&
                              $1->query_condition("killer") &&
			      ! $1->is_ghost() &&
                              ! $1->is_in_prison() &&
                              ! wizardp($1) &&
			      environment($1) :));

	if (sizeof(obs))
        {
        	obs = sort_array(obs, (: $2->query("combat_exp") -
        			         $1->query("combat_exp") :));

                aviable = filter_array(catchers, (: ! find_object($1) :));
                i = 0;
                while (sizeof(aviable) && i < sizeof(obs))
                {
                        punisher = aviable[random(sizeof(aviable))];
                        punisher->start_catch(obs[i]);
                        aviable -= ({ punisher });
                        i++;
                }

                
                
        }

        // Normal I won't check the player
        if (random(10) == 0 || 1)
                family_punish();
}

void family_punish()
{
        object ob;
        object *obs;
        mapping betrayer;
        string *punishers;
        string punisher;
        string key;

        obs = filter_array(users(), (: $1->query("combat_exp") >= 100000 &&
                                       ! environment($1)->query("no_fight") &&
                                       mapp($1->query("betrayer")) :));

        if (! sizeof(obs))
                return;

        foreach (ob in obs)
        {
                betrayer = ob->query("betrayer");
                foreach (key in keys(betrayer))
                {
                        if (key == "times") continue;
                        if (! arrayp(punishers = family_punishers[key]))
                        {
                                ob->add("detach/" + key, 1);
                                ob->add("detach/times", 1);
                                betrayer["times"] -= betrayer[key];
                                map_delete(betrayer, key);
                                if (betrayer["times"] < 1)
                                        ob->delete("betrayer");
                                continue;
                        }

                        punishers = filter_array(punishers, (: ! find_object($1) :));
                        if (! sizeof(punishers))
                                // No punishers aviable now
                                continue;

                        punisher = punishers[random(sizeof(punishers))];
			if (file_size(punisher + ".c") < 0)
			{
				log_file("static/log", "can not find punisher: "
					 + punisher + "\n");
				break;
			}
                        punisher->start_punish(ob, key);
                        break;
                }
        }
}