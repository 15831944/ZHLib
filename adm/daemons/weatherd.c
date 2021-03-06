// 天气预报精灵
// 从网络上抓取信息，预报天气
// 本例子为抓取来自："202.106.184.193"的天气预报信息。

#include <runtime_config.h>
#include <getconfig.h>
#include <net/socket.h>
#include <ansi.h>

// 202.106.184.193 202.108.36.156
#define SITE "202.106.184.193 80"

inherit F_DBASE;

int have_get = 0;
int fail = 0;
string msg = "";

int check_time();
void close(int fd);
void write_s(int fd);

void create()
{
      set("channel_id", "天气探测精灵");
      seteuid(getuid());
      check_time();
}

int check_time()
{
      mixed* times = localtime(time());
      int hours = times[2];
      int fd,fc;

      if(1 || (hours == 3 && ! have_get)) // 每天3点开始抓网页
      {
             fd = socket_create(STREAM, "read_callback", "write_callback");

             if(fd < 0)
             {
                   write("socket_create error " + socket_error(fd) + "\n");
                   socket_close(fd);
                   return 1;
             }

             fc = socket_connect(fd, SITE, "read_callback", "write_callback");

             if(fc != EESUCCESS)
             {
                   close(fd);
                   write("socket_connect error " + socket_error(fc) + "\n");
                   socket_close(fd);
                   return 1;
             }
/*
             remove_call_out("write_s");
             call_out("write_s", 2, fd);
*/
             remove_call_out("close");
             call_out("close", 20, fd); // 等待二十秒，过时认为连接失败。
       }

       if(hours == 12)
       {
               have_get = 0; // 12点清除标记
               msg = "";
               fail = 0;
       }

       remove_call_out("check_time");
       call_out("check_time", 15 * 60);
       return 1;
}

void read_callback(int fd, mixed val)
{
        CHANNEL_D->do_channel(this_object(), "wiz", HIR "msg = " + val + "\n" NOR);
        msg += sprintf("%s", val);
        CHANNEL_D->do_channel(this_object(), "wiz", HIR "msg = " + msg + "\n" NOR);
        log_file("weather_msg", msg);
}

void write_callback(int fd)
{
        CHANNEL_D->do_channel(this_object(), "wiz", HIR "msg2 = " + msg + "\n" NOR);
        return;
}

void close(int fd)
{        
        if(strsrch(msg, "HTTP/1.1 200 OK") != -1) //成功读取
        {
               log_file("weather", msg + "\n");
               have_get = 1;
        }

        // 超时关闭连接
        socket_close(fd);

        return;
}
