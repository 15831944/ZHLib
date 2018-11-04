// auctiond.c
// ����ϵͳ
// Written by jjgod for hell. 01/10/01.
// Modify by Rcwiz for HERO.CD 2003 5 10

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_DBASE;

int clean_up() { return 1; }

#define auction_info    my["auction_info"]
#define lot_percent     4 / 100
#define MAX_SIZE        30

public  void   add_auction(object me, object ob, int money);
public  void   cancel_auction(object me);
public  string check_auction_info();
private void   message_auction(string msg);
private string check_auction(object ob);
private int get_cur_obj(int flag);
private string get_random_words();
private string change_money_unit(int money);

void create()
{
        mapping my;
        
        seteuid(getuid());
        
        set("channel_id", "����ʦ[Auctioneer]");
        CHANNEL_D->do_channel(this_object(), "sys", "���������Ѿ�������");

        my = query_entire_dbase();
        auction_info = ([ ]);
        set_heart_beat(1);
}

void heart_beat()
{
        mapping my;
        string *id;
        int i, money, next;
        object me;
        object ob;
        object obj;

        my = query_entire_dbase();
        
        if (! mapp(auction_info) || ! sizeof(auction_info))
                return;

        id = keys(auction_info);

        i = get_cur_obj(0);
        next = get_cur_obj(1);

        if (! objectp(me = find_player(auction_info[id[i]]["id"])))
                 map_delete(auction_info, id[i]);

        if (! objectp(obj = auction_info[id[i]]["goods"]))
                 map_delete(auction_info, id[i]);

        if (stringp(auction_info[id[i]]["now"]) &&
            ! objectp(ob = find_player(auction_info[id[i]]["now"])))
                map_delete(auction_info[id[i]], "now");

        // �мۼ��
        if (auction_info[id[i]]["ready"] ||
            (time() - auction_info[id[i]]["time"] >= 20 &&
            auction_info[id[i]]["start"]))
        {    
                if (auction_info[id[i]]["ready"])
                         auction_info[id[i]]["ready"] = 0;

                if (! auction_info[id[i]]["start"])
                         auction_info[id[i]]["start"] = 1;

                auction_info[id[i]]["state"] += 1;
                auction_info[id[i]]["time"] = time();

                message_auction(sprintf("Ŀǰ��������%s��%s��%s�Ρ�",
                                filter_color(obj->short()),
                                MONEY_D->money_str(auction_info[id[i]]["value"]),
                                chinese_number(auction_info[id[i]]["state"])));

               if (auction_info[id[i]]["state"] >= 3)
               {
                     if (! objectp(ob))
                     {
                            message_auction(sprintf("%s���˾��ۣ�ȡ��������",
                                            filter_color(obj->short())));
                            map_delete(auction_info, id[i]);
                     } else
                     {
                           money = auction_info[id[i]]["value"];
                           message_auction(sprintf("%s�ɹ�����%s��",
                                           ob->name(),
                                           filter_color(obj->short()),
                                           ));

                           if (ob->query("balance") < money)
                           {
                                        tell_object(me, "����" + ob->name() + "������Ǯ"
                                                    "��ֻ�����ա�\n");
                                        tell_object(ob, "�����㸶����Ǯ��ֻ�����ա�\n");
                                        map_delete(auction_info, id[i]);

                                        return ;
                           }
                           else if (me->query("balance") < money * lot_percent)
                           {
                                        tell_object(ob, "����" + me->name() + "������Ӷ��"
                                                        "��ֻ�����ա�\n");
                                        tell_object(me, "�����㸶����Ӷ��ֻ�����ա�\n");
                                        map_delete(auction_info, id[i]);
                                        return;
                           }
                           // �������
                           else 
                           {
                                        tell_object(ob, "���յ���������������" +
                                                        obj->short() + "��\n");
                                        tell_object(me, "���" + obj->short() + "���������д���"
                                                        "��" + ob->name() + "��\n");
 
                                        ob->add("balance", -money);
                                        me->add("balance", -1 * (money * lot_percent));
                                        me->add("balance", money);
                                        map_delete(auction_info, id[i]);
                                        obj->move(ob);
                                        return;
                           }
                   }
             } // time over
        }

        return ;
}

// ���һ������Ʒ
public void add_auction(object me, object ob, int money)
{
        mapping my;
        string id;
        string msg, key, base_ob;
        string* ids;
        int i;
                 
        my = query_entire_dbase();
        id = me->query("id");
        key = get_random_words();

        if (sizeof(auction_info) > MAX_SIZE)
        {
                tell_object(me, "���������Ѿ��������Ժ����ԣ�\n");
                return;
        }

        if (stringp(msg = check_auction(ob)))
        {
                tell_object(me, msg);
                return;
        }
        
        base_ob = base_name(ob);
 
        ids = keys(auction_info);

        for (i = 0; i < sizeof (ids); i ++)
        {
                if (! objectp(auction_info[ids[i]]["goods"]))
                {
                       map_delete(auction_info, ids[i]);
                       continue;
                }
                if (base_ob == base_name(auction_info[ids[i]]["goods"]) &&
                    auction_info[ids[i]]["id"] == me->query("id"))
                {
                       tell_object(me, "����ͬʱ����������ͬ����Ʒ��\n");
                       return;
                }
        }

        if (me->query("balance") < money * lot_percent)
        {
                tell_object(me, "����㣬֧������Ӷ��\n");
                return;
        }

        auction_info[key] = ([ "goods"     : ob,
                               "time"      : time(),
                               "join_time" : time(),
                               "value"     : money,
                               "lot"       : money * lot_percent,
                               "state"     : 0,
                               "ready"     : 1,
                               "id"        : id,]);

        tell_object(me, "��׼������" + ob->short() + NOR "��Ŀǰ" + 
                        (strlen(msg = MONEY_D->money_str(money * lot_percent)) ?
                        "����Ҫ����" + msg : "����Ҫ����") + "Ӷ��\n");

        write(HIG "\n�������Ʒ�Ѽ����������У��Ժ�������\n" NOR);

        if (! query_heart_beat())        
                    set_heart_beat(1);

        return;
}

// ���������Ʒ
private string check_auction(object ob)
{
        string msg;

        if (! ob->query("value") && ! ob->query("base_value"))
                return "��������ɲ�ֵǮ�ġ�\n";

        if (ob->query("no_sell") || ob->query("no_drop"))
        {
                if (stringp(msg = ob->query("no_sell")))
                        return msg;
                return "��������ɲ������ˡ�\n";
        }

        if (ob->is_character())
                return "����Ҳ����������\n";

        if (ob->query("money_id"))
                return "��û�ù�Ǯ����\n";

        if (ob->query("food_supply"))
                return "�Եĺȵĵ�����ȥ�����ˡ�\n";
}

// ȡ��������Ʒ
public void cancel_auction(object me)
{
        mapping my;
        string id;
        string name;
        object ob;
        int i, count;
        int money;
        string* key;

        id = me->query("id");
        my = query_entire_dbase();

        if (! mapp(auction_info) || ! sizeof(auction_info))
        {
                tell_object(me, "û���κζ�����������\n");
                return;
        }

        key = keys(auction_info);        
        count = 0;
        money = 0;

        for (i = 0; i < sizeof(key); i ++)
        {
              if (me->query("id") == auction_info[key[i]]["id"])
              {
                     count ++;
                     money += auction_info[key[i]]["value"];
                     map_delete(auction_info, key[i]);
              }
        }

        if (count)
        {
                tell_object(me, "��ȡ������������Ʒ��\n");
                message_auction(sprintf("%sȡ����������",
                                me->name()));
                
               if ( money /= 30)
               {
                       tell_object(me, HIR "������ʱȡ����������֧���� "
                                   + change_money_unit(money) + " ��Υ"
                                   "Լ��\n" NOR);

                       me->add("balance", -money);
               }
        } 
        else 
                tell_object(me, "��û�������κζ�����\n"); 

        return;
}

// �鿴������Ʒ
public string check_auction_info()
{
        mapping my;
        string msg, name, state;
        string *id;
        object ob;
        int i;

        my = query_entire_dbase();
        
        if (! mapp(auction_info) || ! sizeof(auction_info))
                msg = "Ŀǰû���κ�������������Ʒ��\n";

        else
        {
                msg = "Ŀǰ������������Ʒ��������Щ��\n";
                msg += HIC "��" HIY "��״̬����������������������Ʒ������������������"
                       "���������������ߩ������������������۸񩤩���������" HIC "��\n" NOR;
                
                id = keys(auction_info);
                for (i = 0; i < sizeof(id); i++)
                {
                        if (! find_player(auction_info[id[i]]["id"]))
                        {
                                map_delete(auction_info, id[i]);
                                continue;
                        }
                        if (! objectp(ob = auction_info[id[i]]["goods"]))
                        {
                                map_delete(auction_info, id[i]);
                                continue;
                        }
                        
                        if (! stringp(auction_info[id[i]]["now"]) || 
                            ! objectp(find_player(auction_info[id[i]]["now"])))
                                name = "��";
                        else name = find_player(auction_info[id[i]]["now"])->name() +
                                    "(" + find_player(auction_info[id[i]]["now"])->query("id") +
                                    ")";

                        if (auction_info[id[i]]["start"])
                                state = HIR "������" HIC;

                        else if (i == get_cur_obj(1))
                                state = HIG "��һ��" HIC;
 
                        else 
                                state = "�ȴ���" HIC;
                                                
                        msg += sprintf(HIC "  %10s %35s %22s %24s\n" NOR,
                                       state,
                                       filter_color(ob->short()),
                                       name, 
                                       MONEY_D->money_str(auction_info[id[i]]["value"]));
                }
                msg += HIC "��" HIY "����������������������������������������������������"
                       "����������������������������������������������" HIC "��\n" NOR;
                msg += sprintf("Ŀǰ����%s������Ʒ��\n", chinese_number(sizeof(auction_info)));
                if (! sizeof(auction_info)) msg = "Ŀǰû���κ�������������Ʒ��\n";
        }
        return msg;
}

// ���뾺��
public void join_auction(object me, int money)
{
        mapping my;
        object ob;
        object obj;
        int i;
        string* key;
        string name;

        my = query_entire_dbase();

        if (! mapp(auction_info) || ! sizeof(auction_info))
        {
                tell_object(me, "����û������ʲô������\n");
                return;
        }

        key = keys(auction_info);

        for (i = 0; i < sizeof(key); i ++)
        {                     
               if (auction_info[key[i]]["start"])
               {
                     name = auction_info[key[i]]["id"];
                     break;
               }                             
        }
         
        if (! stringp(name))
        {
                tell_object(me, "�����ȴ��У����Ժ����ԡ�\n");
                return ;
        }

        if (! objectp(ob = find_player(name)))
        {
                tell_object(me, "������Ѿ���������Ү��\n");
                map_delete(auction_info, key[i]);
                return;
        }
        if (! objectp(obj = auction_info[key[i]]["goods"]))
        {
                tell_object(me, "��������ת������Ʒ��ȡ���������ߵ������ʸ�\n");
                map_delete(auction_info, name);
                return;
        }
        if (money <= auction_info[key[i]]["value"])
        {
                tell_object(me, "������˼ҿ��²���Ҫ��\n");
                return;
        }
        if (stringp(auction_info[key[i]]["now"]) &&
            auction_info[key[i]]["now"] == me->query("id"))
        {
                tell_object(me, "�����ϴγ��۵ľ�����ɡ�\n");
                return;
        }

        message_auction(sprintf("%s(%s)����%s��%s��һ�Ρ�",
                                me->name(), me->query("id"),
                                filter_color(obj->short()), 
                                MONEY_D->money_str(money)));

        auction_info[key[i]]["now"] = me->query("id");
        auction_info[key[i]]["value"] = money;
        auction_info[key[i]]["time"] = time();
        auction_info[key[i]]["lot"] = money * lot_percent;
        auction_info[key[i]]["state"] = 1;

        return;
}

// ��ȡ��ǰ������Ϣ
private int get_cur_obj(int flag)
{
        mapping my;
        int i, cur;
        string* id;

        my = query_entire_dbase();
        id = keys(auction_info);
        cur = 0;
        
        // ��ȡ��һ����������Ʒ���к�
        if (flag)
        {     
              for (i = 0; i < sizeof (id) - 1; i ++)
              {
                  if (auction_info[id[cur]]["join_time"] >= 
                      auction_info[id[i + 1]]["join_time"] && 
                      ! auction_info[id[i + 1]]["start"])
                          cur = i + 1;
              }
              return cur;
        }
        
        for (i = 0; i < sizeof (id) - 1; i ++)
        {
              if (auction_info[id[cur]]["join_time"] >= 
                  auction_info[id[i + 1]]["join_time"])
                       cur = i + 1;
        }

        return cur;
                 
}

private string get_random_words()
{
        string* random_words = ({
                  "1",
                  "2",
                  "3",
                  "4",
                  "5",
                  "6",
                  "7",
                  "8",
                  "9",
                  "0"
        });
        string* id;
        string result;
        mapping my;
        int i;

        my = query_entire_dbase();
        
        id = keys(my);

        result = "";
        for (i = 0; i < 4; i ++)
             result += random_words[random(sizeof(random_words))];
        
        if (sizeof(result) != 4)
             message_auction("error result != 4");

        if (mapp(auction_info[result]))
             get_random_words();
        
        else 
             return result;
}

string change_money_unit(int money)
{
        int i, unit, left_money;
        string new_unit;
        
        new_unit = "";
        unit = money / 10000;
        left_money = money - unit * 10000;
        if (unit)new_unit += chinese_number(unit) + "���ƽ�";
        if (left_money && unit)new_unit += "��";

        unit = left_money / 100;
        left_money = left_money - unit * 100;
        if (unit)new_unit += chinese_number(unit) + "������";
        if (left_money && unit)new_unit += "��";

        if (left_money)new_unit += chinese_number(unit) + "��ͭǮ";

        return new_unit;
}

// ����������Ϣ
private void message_auction(string msg)
{
        CHANNEL_D->do_channel(this_object(), "bill", msg);
}
