/*
 * File    : rhow_q.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to ask a mud for a list of users logged on.
 */

// Ported to ES2 mudlib by Annihilator@ES2.
// UPDATE BY SMALLFISH@HUAXIA

#include <command.h>
#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>

inherit F_CLEAN_UP;
inherit F_DBASE;

/*
* Someone has asked us for a remote who...
* Lets oblige them.
*/
void incoming_request(mapping info)
{
        object *who;
        string str, *bits,now_str;
        int i,str_len,aaa,a,b,key,is_end;

        if(!ACCESS_CHECK(previous_object())) return;

        if (stringp(info["NAME"]) && stringp(info["PORTUDP"])) {
                if (info["NAME"] == Mud_name()) return ;
                if (info["MUDTYPE"] != MUD_TYPE) return ;
                if (!DNS_MASTER->dns_mudp(info["NAME"])) {
                        PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);
                        CHANNEL_D->do_channel( this_object(), "sys",
                                sprintf("rwho request from %s rejected, ping_q sent.", info["NAME"] ) );
                }

                str = WHO_CMD->main(0, info["VERBOSE"] ? "-l -i": "-i", 1);
                
                str_len = strlen(str);

                aaa = 0;
                if (str_len > 1000)
                        aaa = str_len / 1000;

                if (!aaa )
                        DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
                                "@@@" + DNS_RWHO_A +
                                "||NAME:" + Mud_name() +
                                "||PORTUDP:" + udp_port() +
                                "||RWHO:" + str +
                                "||ASKWIZ:" + info["ASKWIZ"] +
                                "||KEY:0" +
                                "@@@\n");
                else
                {
                        key = random(10000000);                 
                        for (i = 0;i <aaa+1;i++)
                        {
                                a = i*1000;
                                b = ((i+1)*1000-1 > str_len-1)?str_len-1:(i+1)*1000-1;
                                now_str = str[a..b];
                                is_end = 0;
                                if (i == aaa)
                                        is_end = 1;
                                DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
                                        "@@@" + DNS_RWHO_A +
                                        "||NAME:" + Mud_name() +
                                        "||PORTUDP:" + udp_port() +
                                        "||RWHO:" + now_str +
                                        "||ASKWIZ:" + info["ASKWIZ"] +
                                        "||KEY:" + key +
                                        "||NUM:" + is_end +
                                        "@@@\n");
                        }                               
                }
    } //if (stringp(info["NAME"]) && stringp(info["PORTUDP"]))
}

void send_rwho_q(string mud, object them, int verbose)
{
        mapping info;
        string askwiz;

        if(!ACCESS_CHECK(previous_object())
        &&      base_name(previous_object()) != WHO_CMD) return;

        if (!them) them = this_player();
        askwiz = geteuid(them);
        info = DNS_MASTER->query_mud_info(mud);
        if (!info) return ;
        DNS_MASTER->send_udp(info["HOSTADDRESS"], info["PORTUDP"],
                "@@@"+DNS_RWHO_Q+
                "||NAME:"+ Mud_name() +
                "||PORTUDP:"+ udp_port() +
                "||ASKWIZ:"+ askwiz +
                "||MUDTYPE:"+ MUD_TYPE +
                (verbose ? "||VERBOSE:1" : "") +
                "||@@@\n");
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "���羫��");
}

int visiblep(object obj) { return 1; }

string get_name(object obj) { return capitalize(geteuid(obj)); }

int support_rwho_q_VERBOSE() { return 1; }

