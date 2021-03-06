// dealer.c 商人
// Written by Lonely

#pragma save_binary

#include <ansi.h>
#include <command.h>
#include <dbase.h>
#include <name.h>
#include <config.h>

class goods {
        string name;
        string id;
        string type;
        string file;
        string unit;
        int amount;
        int value;
        int number;
}

nosave int uptime;
nosave int no_trade = 0;
nosave int load_goods = 0;

protected class goods *all_goods = ({});
protected void init_goods();
protected varargs int add_good_all(string file, int price, int amount);

/*
void setup()
{
        init_goods();
        ::setup();
        if (! uptime)
                uptime = time();
}
*/

protected void init_goods()
{
        string *gds, name;
        mixed items;
        int price;
        int i, number;

        items = query("vendor_goods");

        if (! arrayp(items) && ! mapp(items) || ! sizeof(items))
                return;

        no_trade = 1;
        all_goods = ({});

        gds = mapp(items) ? keys(items) : items;
        for (i = 0; i < sizeof(gds); i++)
        {
                name = gds[i];
                price = mapp(items) && items[gds[i]] > 0 ? items[gds[i]] : 0;
                add_good_all(name, price);
        }

        no_trade = 0;
        load_goods = 1;
}

protected varargs int add_good_all(string file, int price, int amount)
{
        object ob;
        class goods item;
        string type;

        if (! stringp(file))
                return 0;

        if (amount > 0 && sizeof(all_goods))
        {
                foreach(item in all_goods)
                {
                        if (item->file != file)
                                continue;

                        item->amount = amount;
                        return 1;
                }
        }

        call_other(file, "???");
        if (! objectp(find_object(file)))
        {
                log_file("log", sprintf("No found vendor good:%s\n", file));
                return 0;
        }

        /*
        ob = new(file);
        if (! ob)
        {
                log_file("log", sprintf("No found vendor good:%s\n", file));
                return 0;
        }
        */
        ob = find_object(file);

        if (ob->is_weapon_ob())
                type = "武器";
        else if (ob->is_armor_ob())
                type = "防具";
        else if (ob->is_liquid())
                type = "饮具";
        else if (ob->is_food())
                type = "食物";
        else if (ob->is_container())
                type = "容器";
        else if (ob->is_book())
                type = "书籍";
        else
                type = "其它";


        item = new(class goods);

        item->name = ob->query("name");
        item->id = ob->query("id");
        item->type = type;
        item->file = file;
        item->unit = ob->query("base_unit") ? ob->query("base_unit")
                                            : ob->query("unit");
        item->amount =  amount ? amount : -1;
        item->value = price ? price :
                        (ob->query("base_value") ? ob->query("base_value"):
                                                   ob->query("value"));
        item->number = sizeof(all_goods) + 1;

        all_goods += ({ item });
        destruct(ob);
        return 1;
}

string is_vendor_good(string arg)
{
        mixed items;
        object ob;
        int i, n;

        n = sizeof(all_goods);
        if (! n) return "";

        for(i=0;i<n;i++)
        {
                if ((all_goods[i]->file)->id(arg)
                ||  all_goods[i]->file == arg
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg)
                {
                        if (all_goods[i]->amount != -1)
                                return "";

                        return all_goods[i]->file;
                }
        }

        return "";
}

void add_carry_good()
{
        mixed obs;
        int i, j;
        int amount;
        
        if (obs = all_inventory())
        {
                obs = unique_array(obs, (: base_name($1) :));

                for (i = 0; i < sizeof(obs); i++)
                {
                        for (j = 0; j < sizeof(obs[i]);  j++)
                        {
                                if (obs[i][j]->query("equipped") ||
                                    obs[i][j]->query("money_id") ||
                                    obs[i][j]->is_character())
                                        continue;

                                if (is_vendor_good(base_name(obs[i][j])) != "")
                                        continue;

                                amount = obs[i][j]->query_amount() ? obs[i][j]->query_amount()
                                                                   : sizeof(obs[i]);
                                add_good_all(base_name(obs[i][j]), 0, amount);
                        }
                }
        }
}
        
varargs int do_list(string arg)
{
        string output, desc;
        int amount;
        class goods item;
        object me;
        mixed obs; 
        int i, j, number;
        
        me = this_player();

        if (no_trade)
                return notify_fail("现在正在盘库，请等一下再来。\n");

        if (! wizardp(me) && me->query_condition("killer"))
                return notify_fail(CYN "店铺不做杀人犯的生意！\n" NOR);

        if (me->is_busy())
        {
                write("你正在忙着呢。\n");
                return 1;
        }

        // 处理同房间有一个以上 dealer 的情况。
        if (arg && ! id(arg) &&
            arg != query("name"))
                return 0;
                
        if (! load_goods)
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }       
        
        add_carry_good();
        if (! sizeof(all_goods))
        {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        output = this_object()->name() + "目前出售以下物品：\n";
        output += sprintf("%5s%-30s%-10s%-10s\n","序 号", "    商  品","  单  价","        数  量");
        output += "--------------------------------------------------------------\n";
        foreach (item in all_goods)
        {
                if (item->amount < 0)
                        desc = "大量供应";
                else if (item->amount == 0)
                        desc = "暂时缺货";
                else if (item->amount < 11)
                        desc = sprintf("仅剩%2d%2s", item->amount, item->unit);
                else if (item->amount < 31)
                        desc = sprintf("还剩%2d%2s", item->amount, item->unit);
                else
                        desc = "货源充足";

                output += sprintf("(%3d)%" + sprintf("%d", (30 + color_len(item->name))) +
                                  "-s：每%s%s" CYN "(现货%s)\n" NOR,
                                  item->number,
                                  item->name + "(" + item->id + ")",
                                  item->unit,
                                  MONEY_D->price_str(item->value), desc);
        }
        
        write(output);
        return 1;
}

int do_buy(string arg)
{
        mapping room_obmap; 
        string  bunch;
        object *obs;
        object  ob;
        object  room;
        object  me;
        mixed   value;
        int     amount;
        int     val_factor;
        int     i, j, n, s;
        int     much;
        string  my_id;
        string  start_room;
        
        if (! arg)
                return notify_fail("你想买什么？\n");

        if ((me = this_player())->is_busy())
        {
                write("你正在忙着呢！\n");
                return 1;
        }

        if (no_trade)
                return notify_fail("现在正在盘库，请等一下再来。\n");

        if (query_temp("busy"))
        {
                write(CYN + name() + "不耐烦道：“没看见我这"
                      "儿正忙着么？”\n" NOR);
                return 1;
        }
        
        if (sscanf(arg,"%s from %s", arg, my_id) == 2)
        {
                if (! id(my_id) && my_id != query("name"))
                        return 0;
        }                

        if (! query("carried_items"))
        {
                if (stringp(start_room = query("startroom")) &&
                    (room = find_object(start_room)) != environment())
                {
                        // I am not in start room.
                        message_vision("$N大叫一声：“不好，我怎么跑到这儿来了？”\n"
                                       "说罢头也不回的急急忙忙的溜走了。\n", this_object());
                        if (! objectp(room) ||
                            ! mapp(room_obmap = room->query_temp("objects")) ||
                            member_array(this_object(), values(room_obmap)) == -1)
                        {
                                destruct(this_object());
                        } else
                                this_object()->move(room);
                        return 1;
                }
        }

        if (sizeof(filter_array(all_inventory(me), 
                                (: ! $1->query("equipped") :))) >= MAX_ITEM_CARRIED)
        {
                write("你身上的东西太多了，先处理一下再买东西吧。\n");
                return 1;
        }

        if (sscanf(arg, "%d %s", amount, arg) != 2)
                // not indicate the amount of the items
                amount = 1;

        if (amount < 1)
        {
                write(CYN + name() + "疑惑的问道：“没见过这种买法，你到底想买几个单位呢？”\n" NOR);
                return 1;
        }
        
        if (amount > 100)
        {
                write(CYN + name() + "忙道：“慢慢来，一次最多买一百个单位。”\n" NOR);
                return 1;
        }

        if (! load_goods)
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }
        
        add_carry_good();
        n = sizeof(all_goods);
        if (! n)
        {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }
        
        val_factor = 10;
        for(i = 0; i < n; i++)
        {
                if ((all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg)
                {
                        if (! (all_goods[i]->amount))
                        {
                                command(sprintf("say 对不起，目前这%s缺货，您过一段时间再来吧",
                                        all_goods[i]->name));
                                return 1;
                        }

                        if (all_goods[i]->amount > 0)
                        {
                                val_factor = 12;
                                ob = present(all_goods[i]->id, this_object());
                                if (amount > all_goods[i]->amount)
                                        amount = all_goods[i]->amount;
                        }
                        break;
                }
        }

        if (i >= n)
	{
		write("你想买什么？\n");
		return 1;
	}
        
        value = count_mul(amount, all_goods[i]->value);
        value = count_div(count_mul(value, val_factor), 10);
        
        /*
        if (value > 1000000000 || value * val_factor / val_factor != value)
        {
                write(CYN + name() + CYN "大惊失色道：这么大一笔生意？我"
                      "可不好做。\n" NOR);
                return 1;
        }
        */
        
        if (me->query_skill("higgling", 1) > 99)
        {
                if (me->query_skill("higgling", 1) > 399)
                        value = count_div(count_mul(value, 7), 10);
                else
                if (me->query_skill("higgling", 1) > 199)
                        value = count_div(count_mul(value, 8), 10);
                else
                if (me->query_skill("higgling", 1) > 99)
                        value = count_div(count_mul(value, 9), 10);
        } else
        if (stringp(bunch = me->query("bunch/bunch_name")) &&
            bunch == (string)this_object()->query("bunch/bunch_name"))
                value = count_div(count_mul(value, 8), 10);
        // 开了店的玩家才采购时享受八折优惠
        else
        if (SHOP_D->is_owner(me->query("id")))
                value = count_div(count_mul(value, 8), 10);

        if (count_le(value, 0))
                value = 1;

        switch (MONEY_D->player_pay(me, value))
        {
        case 0:
                write(CYN + name() + "冷笑道：“穷光蛋，一边呆着去！”\n" NOR);
                return 1;
        case 2:
                write(CYN + name() + "皱眉道：“您还有没有零"
                      "钱啊？银票我可找不开。”\n" NOR);
                return 1;
        case 3:
                write(CYN + name() + "皱眉道：“您还有没有零"
                      "钱啊？钻石我可找不开。”\n" NOR);
                return 1;
        default:
                set_temp("busy", 1);

                if (me->query_skill("higgling", 1) > 99 || SHOP_D->is_owner(me->query("id")))
                {
                        switch (random(3))
                        {
                        case 0:
                                command("say 既然大家都是做买卖的，就给你打点折吧。");
                                break;
                        case 1:
                                command("say 也罢，既然是大老板光顾，就便宜点卖给你吧。");
                                break;
                        default:
                                command("say 呵呵。大老板又来采购么？那么就给你打点折吧。");
                                break;
                        }
                }  else
                if (stringp(bunch = me->query("bunch/bunch_name")) &&
                    bunch == (string)this_object()->query("bunch/bunch_name"))
                        command("say 既然大家都是同帮兄弟，就给你打点折吧。");

                much = atoi(count_div(value, 5));
                if (much <= 0) much = 1;

                if (stringp(bunch == (string)this_object()->query("bunch/bunch_name")) &&
                    bunch != me->query("bunch/bunch_name"))
                        BUNCH_D->add_bunch_info(bunch, "npc_money", much);

                if (ob)
                {
                        object old_ob;
                        if (ob->query_amount())
                        {
                                ob = new(base_name(old_ob = ob));
                                ob->set_amount(amount);
                                old_ob->add_amount(-amount);
                                ob->move(me, 1);
                        } else
                        {
                                obs = all_inventory();
                                obs = filter_array(obs, (: base_name($1) == base_name($(ob)) :));
                                s = 0;
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        s++;
                                        if (s > amount)
                                                break;

                                        obs[j]->move(me, 1);
                                }
                        }
                } else
                {
                        ob = new(all_goods[i]->file);
                        if (ob->query_amount())
                        {
                                ob->set_amount(amount);
                                ob->move(me, 1);
                       
                        } else
                        {
                                ob->move(me, 1);
                                for (j = 0; j < amount-1; j++)
                                {
                                        ob = new(all_goods[i]->file);                                       
                                        ob->move(me, 1);
                                }
	                }
                                
                }

                all_goods[i]->amount -= amount;                
                message_vision(sprintf("$N从$n那里买下了%s%s%s%s。\n",
                        all_goods[i]->amount == 0 ? "最后" : "",
                        chinese_number(amount),
                        all_goods[i]->unit,
                        all_goods[i]->name), me, this_object());
        }

        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

        return 1;
}

void enough_rest()
{
        delete_temp("busy");
}

int do_look(string arg)
{
        string who;
        object ob,me;
        int sum,i,flag,n, rtn;

        if ((me = this_player())->is_busy())
        {
                write("你正在忙着呢！\n");
                return 1;
        }

        if (! arg || arg == "")
        {
                write("你想看什么？\n");
                return 1;
        }

        // 处理同房间有一个以上 dealer 的情况。
        if (sscanf(arg,"%s from %s", arg, who) == 2)
        {
                if (! id(who) && who != query("name"))
                        return 0;
        }

        if (! load_goods)
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }
        
        add_carry_good();
        n = sizeof(all_goods);
        if (! n)
        {
                write(sprintf("目前%s没有可以卖的东西。\n",query("name")));
                return 1;
        }

        for (i=0;i<n;i++)
        {
                if((all_goods[i]->file)->id(arg)
                || filter_color(all_goods[i]->name) == arg
                || sprintf("%d",all_goods[i]->number) == arg)
                {
                        ob = new(all_goods[i]->file);
                        LOOK_CMD->look_item(me, ob);
                        destruct(ob);
                        return 1;
                }
        }
        
        if (i >= n)
        {
                write("你想看什么？\n");
                return 1;
        }
}

void reset()
{
        int i, t;
        object *obs;

        t = time();
        if (! uptime)
                uptime = t;

        if (t - uptime >= 3600)
        {
                uptime = t;
                init_goods();
        }

        obs = all_inventory();
        for (i = 0; i < sizeof(obs); i++)
                if (i >= 100 || obs[i]->query_weight() >= 1000000)
                        destruct(obs[i]);
}