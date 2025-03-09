#include<bits/stdc++.h>
#include<sstream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<wchar.h>
#include<locale>
#include<mmsystem.h> 
#include<fstream>
#include<exception>
#pragma comment(lib,"Winmm.lib")
#pragma GCC optimize(3)//快约10ms 
using namespace std;
/*未经wqx同意禁止转载 
2024.2.11 7015
2024.6.28 箱子和打死鬼的奖励丰富一点 矛、mvb要能使蜘蛛网振动 
2024.7.26 虫子会繁殖了，所以把它复活禁了。蜘蛛得再强一点 
2024.9.15 迷宫换了映射生成方式，大蜘蛛实力似乎变强了 
2024.10.2 快被大蜘蛛薄纱了↑真打不到一点；聚在一起的墙内部挖空，空间宽敞了点，出口标牌加多了，但是路还是不好找 
2024.10.3 怎么有时候莫名其妙闪退
2024.10.8 战斗体系更新：反弹效果、鬼攻击和移动分开
2024.10.9 感觉打不过石化鬼了；钥匙门增多一点 
2024.10.19 换了个奇葩的迷宫生成方式，路稍微绕一点，上下楼更多了 
2024.11.9 鬼可以开箱子门了；解决了长期存在的鬼被mvb卡住的问题 
2025.1.19 玩家视野受到鼠标远近的限制；鬼潜伏在箱子中的逻辑更新 
2025.1.24 做好了物品栏的架构大调整，为武器的更新打好基础；鬼的反应速度增加变慢了 
2025.2.1 吸血鬼会避光，会被强光晒伤
2025.2.6 长矛可以八方向挥来挥去了，并且可以刺到鬼 
2025.2.14 设置game_log程序日志，方便查错 
2025.2.15 匕首、短剑、长刀 
2025.2.21 短剑和长刀只能在视野范围内出现；解决长矛的BUG 
2025.3.2 鬼向你冲来！（调bug调了半天QwQ） 
idea:
1.用鼠标按下-拖拽-松开的方式发射远程武器或扔东西
2.电梯
3.球可放入箱子内；球不能拉，只能推/走到上面
4.鬼的攻击和移动彻底分离，攻击用反应时间判断 
5.玩家按shift键格挡（用盾）/擒拿 
6.尝试各种稀奇古怪的迷宫生成算法
7.物品的生成不要太随机，设置类似奖励房间的聚集区域
8.钥匙不要总是聚在出生地附近
9.钥匙种类0-9
10.可以在关键位置使用密码门 
11.除了普通房间外（现在生成的），增加更多奇奇怪怪的房间
12.看的方向和速度方向相反时速度减慢 
13.武器种类丰富一点，可以在迷宫里自由拾取 
14.重新设置物品捡拾系统 
15.敌人是时候再丰富一下种类和攻击方式了
16.玩家按shift翻滚几格，可以无视中间格子生物、球、椅子、桌子等的阻挡，体力减少 
17.显示敌人的血量 
18.武器格挡 
一、单位制度
	物理量名  游戏名称       实际大小
	时间      毫秒           1ms 
	长度      格             1格=2个字符
	温度      degree         1 degree=1摄氏度 
二、BUG记录 
	1、地图左边缘墙生成错误
	    1）制造、出现时间：2022.1
	    2）出现条件
	    	(1)地图总长16~17个房间，房间长5格
	    3）表现外观
	        (1)墙体显示为其他字符（全黑/门/生物/（错误的）出口）
		    (2)出错处数据记录有误 
		4）消灭时间：2022.7.14前 
	2、出口标牌输出错误
		1）制造、出现时间：2022.6.27
		2）出现条件：输出出口标牌时（char(24~27)） 
		3）表现外观
			(1)程序卡死 
		4）消灭时间：2022.7.10
		   方法：换为中文字符 
	3、钥匙门开关状态错误
		1）制造时间：2022.8
		2）出现时间：2022.9
		3）出现条件：多次游戏
		4）出现原因：初始化时围绕房间生成门（doors_around_rooms）的函数没有设置门为未开启，此次游戏中打开的门再次
			游戏时开关状态会仍是开启，即同一个位置的门保持开启，可以多次累加 
		5）消灭时间：2022.9.30 
	4、异世界窗户错误
		1）制造时间：2023.4 
		2）出现时间：2022.7.5
		3）出现条件：多次游戏且后一次的地图没有完全包含前一次的
		4）出现原因：仅初始化了当前所需地图区域，且有窗户生成在边缘墙上 
	5、屏幕帧率过低
		1）制造时间：2023.7
		2）出现条件：未知
		3）表现外观：输出卡顿，尤其是生物较多时 
	6、Failed to execute
		1）时间：2024.2.25
		2）原因：内存超限 
	7、100*100最大地图大小运行时错误
		1）时间：2024.10.3
		2）表现：生成或开始游戏后运行时错误 
		3）原因
			(1)dis_to_player/exit部分空地值为0，被用作除数爆了 
			(2)make_window判断条件似乎有安全隐患？
		4）次日未复现，似乎已消灭 
三、游戏地图
	1、概念界定
		1）格：一个位置或其长度/宽度 
		2）格点：一个位置/格（正方形）的顶点，每格与四个格点相邻，一格的左下角格点（打印显示为左上）坐标设为此格
			坐标(x,y)，左上角(x,y+1)，右下角(x+1,y)，右上角(x+1,y+1)
		3）边缘墙：满足x==1||x==length||y==1||y==width的位置的集合
		4）矩形：排成长方形的一些位置的集合 
		5）房间：存在于一个不包含墙的长宽都≥2的矩形的一些位置的集合 
	2、大小
		长length格，宽width格，高height*2层（x，y，z都从1开始编号）
		1~height层为一般游戏区，height+1~height*2层为扩展虫巢区（详见【虫子巢穴】） 
	3、生成
		1）框架（空地+墙+楼梯+巢穴）
			rand_maze生成初始地图，形成特定路径
			fill_dead_ends删除一部分道路
			make_room去除地图中一部分连起来的墙（全部清除/形成网格） 
				包含了pos_in_room的记录 
		2）生成玩家make_player
			包含了各位置与玩家距离的记录 
		3）生成敌人make_enemy
		4）生成物品make_thing 
四、 门
	1、钥匙门
		1）种数：4种
		2）生成
			(1)随机（普通、越远越多）
			(2)围绕房间生成 
	2、钥匙
		1）种数：4种（对应门） 
		2）生成
			(1)随机（普通、越远越少）
			(2)房间内生成
			(3)根据门生成
				[1]模式：确保打开每扇门的钥匙都能在不打开这扇门的情况下取到
				[2]实现方法
					①准备
						BFS二件套：Q、vst
						vector<position_3D> vspace已访问、没有物品的空地	
						vector<position_3D> vdoor[4]已访问、未放对应钥匙的门（四种分别记录） 
						vector<position_3D> vkind可以选择的门的种类 
					②初始化：
						a.全部清空
						b.把玩家坐标作为起点 
					③重复执行： 
						a.BFS遍历（打开已访问、已放对应钥匙的门）能到的地方，
						更新vspace，过程中碰到未访问的门都加入vdoor
						b.为下次循环准备 
							把4种门中数量不为0、不比空地多的种类加入vkind 
							至少有一种门可以选： 
								在vkind中随机取出一种门，把这种门全部加入Q并去掉，
								在vspace中随机取出这种门数量的空地放置对应的一种钥匙
						 	否则退出循环 
					注意：所有BFS遍历不会重复访问已访问过的地方（之前循环的也不会）！  
		3）使用
			(1)状态：【上锁】【打开】【关闭】 
			(2)【上锁】时有对应钥匙/【关闭】时 可以打开进入，并设置为【打开】状态
			(3)【打开】状态下可以走到门位置，按下空格键【关闭】（生物不可直接进入） ，玩家可以四处移动 
	3、隐藏门
		1）无需钥匙打开，打开通过后自动关闭 
		2）与墙体显示相同 
	4、旋转门
		1）大小：2*2
		2）玩家碰到可以旋转。旋转时带动范围内所有可移动物品、生物一起旋转
		3）示意图
			门  	玩门
		  ↑玩门	门   
五、玩家
	1、移动
		1）方向操控
			方向键 对应数字 坐标变化
			上     0        (x,y-1,z) 
			右     1        (x+1,y,z)
			下     2        (x,y+1,z)
			左     3        (x-1,y,z)
			【移动】模式下改变位置，【改变朝向】模式下仅改变方向 
		2）碰撞检测
		   格式：（碰到……（如果……（且/或……）就……（，然后……）（否则……（，然后……））） 
			(1)碰到墙就停下
			(2)碰到门如果有对应钥匙就进门否则停下 
		3）特殊移动
			(1)手动上下楼：按下空格键就上/下楼 自动上下楼：碰到楼梯就上/下楼
			(2)碰到电梯就跳出选楼层界面，然后移动到对应楼层
	2、侦测物品
		物品名    捡拾    使用（键1：使用1，键2：使用2，……）    特殊效果（键1：效果1，键2：效果2，……）
		钥匙      自动    自动                                    开对应门
		出口标牌  无      无                                      指向到达出口的最近路线的方向
		镜子      无      无                                      反射光线，使玩家能看到更远的地方；使移动物品改变方向 
		窗户      无	  向它移动                                开关窗户（可以遮挡鬼的视线） 
	3、视野计算
		1）规则：遇到楼梯上/下楼，碰到镜子拐弯（或许还要限定最远距离？）
			墙看到表面一层，除此以外都能看穿
		2）准备
			int game_map[][][].in_player_sight玩家最后一次看到这个位置的时间，记为游戏地图 
			queue<position_3D> pos_in_sight现在要在屏幕上新显示的位置，记为队1 
			queue<position_2D> pos_lst_sight上次在屏幕上显示的位置（scr），记为队2
			queue<position_2D> pos_backup位置（scr）备份，为下回合的队2做准备，记为队3 
			string print_game_map_pos(position_3D pos)屏幕输出编码 
			map<position_2D,string> screen_pos屏幕上的位置显示内容的编码（就用print_game_map_pos(kind=3)） 
			map<position_2D,int> screen_z屏幕上现在需要显示的位置所处的楼层（z坐标） 
			position_3Dtoscr、position_scrto3D等各种坐标的转换函数 
			(1)初始化（all_assigned）：每次游戏开始时清空一下上面那些东西（screen_z每回合都要） 
			(2)标记已看到：
			 	[1]已经标记过游戏地图至[3]
				[2]标记游戏地图，入队1，标记screen_z，结束 
				[3]此位置是玩家位置：标记screen_z，结束 
		3）方法
			(1)十字形
				[1]简介：十字形视角（前后左右）+两侧可视范围优化 
				[2]优点：实现简单 缺点：走廊里完全够用，房间里不能看到全部范围 
			    [3]实现方法
					①先把玩家所在的位置入队1，标记一下游戏地图
					②向4个方向计算视野，入队1，标记一下游戏地图
						如果这个位置视线可以穿过，就把它两侧的位置入队1，标记已看到
						否则看两侧位置在与现在玩家视线方向相反的方向上的前一个位置，
						如果前一个位置视线可以穿过，就把它对应侧的位置入队1，标记已看到 
			(1)拟真形
				[1]简介：以玩家位置为起点进行BFS搜索，碰到墙就记录它遮挡的视线范围（坐标系方向角，以玩家位置的四格点
					为原点），不访问被完全遮挡的位置，直到所有视线范围均被遮挡
				[2]优点：更为真实的计算了视野，实现相对容易 
				   缺点：时间复杂度稍高，有精度误差（至少13格外才会产生），且暂无处理镜子的能力 
				[3]准备
					bool occlusion[4][360]记录玩家位置4个格点上被遮挡的视线方位角，0：未遮挡，1：被遮挡
					int cnt_occlusion[4]记录玩家位置4个格点上未被遮挡的视线方位角还剩几个，即occlusion[0~3]中0个数 
					int calc_angle(position_3D p)计算p相对玩家位置的方位角（0~360°） 
					bool invisible(position_3D p)返回p是否看不到 
					void mark_occlusion(position_3D p)标记p遮挡的角度范围
					queue<position_3D> visible_stair所有能看到的楼梯的位置 
					BFS二件套：Q、vst
					局部位置变量：u、v、v2 
					初始化（assigned）：每次计算前occlusion清零，cnt_occlusion[0~3]都设为360 
					方位角枚举方法（逆时针，最大359°）：for(int i=最小角度;i!=(最大角度+1)%360;i=(i+1)%360)
				[4]实现方法（player_calculate_vision2(position_3D pos=player1.pos)）
					①玩家坐标入队并标记vst
					②队列为空或cnt_occlusion[0~3]都为0至⑨，否则取出队首u  
					③不能扩展至②，否则扩展到v
					④v超出地图范围至③ 
					⑤看不到v（invisible(v)）就标记vst，至③
					⑥v是不可透视位置：标记occlusion（mark_occlusion(v)）
					⑦v入队并标记vst，在游戏地图中标记，至⑧ 
					⑧v是楼梯：把它通往的位置v2入队visible_stair；至③ 
					⑨玩家想看到楼上/下：枚举visible_stair中每个位置u，
					occlusion清零，cnt_occlusion[0~3]都设为360， 
					标记玩家通过此楼梯看到的方位角范围为可见（mark_occlusion()，改变cnt_occlusion，同时取反occlusion）， 
					调用player_calculate_vision2(u) 
		4）屏幕更新（screen_update）时
			(1)清理队2
				[1]取出队首spos 
				[2]根据spos和screen_z求出屏幕现在这个位置要打印游戏地图上哪个位置（now_pos） 
					screen_z没有屏幕这个位置的信息：把这个位置涂黑，更新screen_pos，886 
				[3]判断 
					这里now_pos的显示内容编码和现在屏幕上（未更新）的显示内容编码不同：
						重新输出now_pos（print_game_map_pos(now_pos)），更新screen_pos
					d.now_pos加入队3
			(2)处理队1
				[1]取出队首now_pos
				[2]输出（print_game_map_pos(now_pos)）
				[3]position_3Dtoscr(now_pos)加入队3 
			(3)队3的内容全部移到队2 
		5）模糊效果 
			(1)产生：蜘蛛网、雾气
			(2)计算
			(3)显示 
	4、生命体征
		1）生命值
			(1)初始：100%
			(2)减至0玩家死亡，游戏失败
		2）体力值
			(1)初始：100%
			(2)玩家移动时减少1点，否则<100%就每0.5秒回复1点
	5、道具 
		1）食物 
			等级\效果  体力恢复ADDL  生命回复ADDS  
			1          +40%          +20%
			2          +20%          +10%
			3		   +10%          +5%
									（恢复无上限）
		2）透视
			给玩家一段时间的透视效果
		3）烟雾弹
			可捡拾放入物品栏，使用时产生蓝色雾气并迅速扩散 
	6、攻击
		1）武器能量/耐久度 
			(1)生成方法：随机生成、离玩家越远越少/多、离出口越远越少/多 
		2）武器种类
			(1)激光枪 LAS 
				[1]显示：地上青色“枪”；手持时玩家显示为青色“激” 
				[2]使用：按下鼠标，消耗1点武器能量，向鼠标方向发出青色激光束，持续0.5秒，
					 （每把枪武器能量生成时都是随机的，用完自动丢弃消失） 
				[2]特点：发射瞬间命中目标，碰到墙或锁上的门就中断，碰到镜子就反射，两者都会产生青色亮光
				[3]特殊效果：点燃TNT、蜡烛等 
			(2)回旋镖 DAR
				[1]显示：地上×十，可堆叠；手持时玩家显示为蓝色“镖” 
				[2]使用：按下鼠标，消耗数量1，向鼠标方向扔出回旋镖，速度15m/s，
				[3]特点：速度较高，碰到墙或锁上的门就停止飞行，变成可捡拾的物品，可回收
					击穿鬼带有击退效果，分20%速度；
					30%暴击率，暴击时分80%速度 
				[4]特殊效果：
					损坏窗户、镜子、帘子
			(3)矛 SPE
				[1]显示：地上一格“↑”；手持时玩家显示为“矛”，正常情况下伸出一格“↑”，前刺时2格 
				[2]使用：
					每次移动/改变方向，向玩家朝向伸出长度为1的矛，保持不变直到下次
					按下鼠标前刺到2格，或者斜向 
					碰撞判断：挥舞矛改变方向时第一次碰到；刺出时碰到 
						碰到敌人耐久度减少（与敌人速度有关）并造成击退伤害 
				[3]特点：瞬间命中目标，虫子被击中无法移动和攻击，碰到墙或锁上的门就停下
				[4]特殊效果：暂无 
			(4)匕首 DAG
				[1]显示：地上一格银色“匕”；手持时玩家显示为银色“匕”
				[2]使用：按下方向键攻击敌人时伤害*5，玩家闪烁“匕”
				[3]特点：增加拳击伤害，取消击退，30%暴击
					各种属性与匕首的种类有关 
				[4]特殊效果：对窗户按下方向键，窗户耐久-25
				[5]耐久：100，用完自动消失
			(5)剑 SWO
				[1]显示：地上一格黑色“剑”；手持时正常情况下向玩家朝向伸出一格“剑”
				[2]使用：
					挥动鼠标挥剑，命中鼠标方向的敌人，带有击退
				[3]特点：一格攻击范围，20%暴击
					各种属性与剑的种类有关 
				[4]特殊效果：对窗户按下方向键/挥剑，窗户耐久-25
				[5]耐久：100，用完自动消失
			(6)长刀
				[1]显示：地上两格“—刀”；手持时正常情况下向玩家朝向伸出两格“—刀”
				[2]使用
					移动鼠标挥刀，每次改变方向都计算一次伤害（刀锋伤害比刀柄高，击退比刀柄低）
					按空格键踢出的范围为刀的范围，伤害*2，击退*2 
				[3]特点：2格攻击范围，8方向，20%暴击
					各种属性与刀的种类有关 
				[4]特殊效果：对窗户按下方向键/挥刀，窗户耐久-50 
				[5]耐久：100，用完自动消失
			(7)步枪
				[1]显示：地上1格黑色“枪”；手持时正常情况下玩家显示为“步”，向玩家朝向伸出一格“枪”
					（可能会显示特定名字 e.g.M4A1,PR5,AK47）
				[2]使用
					按下鼠标开火，消耗一格弹药，一些枪可以连发 
					弹夹打光会消耗几秒自动换弹，全部打完就没了
					弹夹会随机生成，显示为黑色“弹” 
					子弹不可见，有开火音效，命中后显示“＠”，有击退效果 
				[3]特点：只能被墙、箱子、隐藏门挡下，可打穿门、窗户、大蜘蛛的腿（造成伤害）
					各种属性与枪的种类有关 
				[4]特殊效果：对窗户开火，窗户耐久-50 
				[5]弹夹容量：10，塞在物品栏里，会占空间
			(8)飞斧
				[1]显示：略深的红色“斧” 
				[2]使用：按下鼠标，消耗数量1，向鼠标方向扔出回旋镖，速度15m/s，
				[3]特点：速度较高，碰到墙或锁上的门就停止飞行，变成可捡拾的物品，可回收
					击穿鬼带有击退效果，分75%速度；
					50%暴击率，暴击时分100%速度 
				[4]特殊效果：
					损坏窗户、镜子、帘子
			(9)盾
				[1]显示：括号
				[2]使用
					面向鼠标朝向显示，若无空间就不显示
					按下鼠标击飞盾所在位置的生物
					快速旋转可沿切线方向击飞 
				[3]特点：盾所在位置生物无法直接对玩家造成伤害，击退*0.2；飞来的东西传递动能*0.5，并若不朝向飞来物体会自动丢弃
				{4]特殊效果：撞击窗户，窗户耐久-20 
				[5]耐久：100，每次格挡都会减少 
			
		3）武器存放 
			(1)操作 
				[1]拿取 
					面向它时按f拾取（长刀要面向刀柄） 
					若有多个物品堆叠，拾取最上方的（即显示出来的）
					（弹夹同理）
					若主/副武器空，当作主/副武器
					否则若物品栏有空位，放入后面 
				[2]丢弃
					选中武器所在区域（主武器/副武器/物品栏），选中武器，按q丢弃到面向的位置
					若有多个物品堆叠，放到最下面
					删除对应存放位置
					（弹夹同理）
				[3]切换
					打开物品栏，选中武器，再次点击或按e换到主武器
					按ctrl或点击副武器切换主副武器 
					若主武器为步枪，选中弹夹，点击或按e（自动丢弃当前弹夹）换弹，删去对应位置
			(2)实现
				每个武器生成时唯一编号id，从WEAPON_ID_START=10开始编号（错开物品栏其他物品的code） 
				以编号为下标记录武器信息数组：
					种类，耐久/能量，是否用完消失，特殊名称，
					种类：SPR=1,LSG,DART,DAGGER,SWORD,LSWD,BLSWD,RIFLE,AXE 
					如果能堆叠：堆叠在哪个id上面（under），没有就是None=0 
				THING中标记哪个id在最上面（top=None/...）
				主/副武器相关变量记录堆叠在最上面的id（Top），没有=None
				物品栏只存储武器id 
				操作注意点：
					首先注意id/top是否为None 
					其次注意武器是否已消失
					若已消失按丢弃武器处理 
				拿起武器（若物品栏存得下）：
					若武器已消失，按丢弃处理 
					若top!=None，拿取top，weapon[top].under=None
					物品栏存武器id
				选中物品栏武器时： 
					若id!=None，根据id查找武器信息并显示
				物品栏武器（id）切换到主武器：
					若主武器None，top=id 
					若此武器可与主武器堆叠则weapon[id].under=Top,Top=id	e.g.飞镖 
					否则与主武器交换 
				丢弃武器（id）：
					首先判断武器是否None 
					若找到丢弃位置，然后： 
						沿着top->under1->under2->...找到最后一个ID（最下面的） 
						weapon[ID].under=id 
					top=weapon[id].under
					weapon[id].under=对应位置.top
					若此武器未消失，对应位置.top=id 
				交换主副武器：
					若主副武器均非None：
						swap(weapon[idx].under,weapon[idy].under)
					否则 单独存在的.under=None
					swap(主.Top,副.Top) 
				player_use_weapon针对玩家使用主武器判断操作 
				武器使用中耐久/能量用尽：
					删除存放位置编号并标记已消失
					对应存放位置.top=weapon[id].under 
		4）赤手空拳
			按方向键——拳	按空格键——脚
			拳伤害低但攻速稍快 
		5）屏幕提示
			(1)消灭敌人有红色“KO”提示  
			(2)近战武器挥舞时播放动画 
	7、物品交互 
		1）可移动物品（mvb） 
			(1)模式：【推】【拉】【扔】 
			(2)操控方法
				[1]按d键切换模式
				[2]【推】模式下：
					①可同时推动多个物品
					②优先推动所处位置的物品（如果有的话） 
				[3]【拉】模式下：
					①碰到物品选中
					②切换模式或移动时选中物品被阻挡而无法拉动，取消选中
					③移动时若不移到选中物品处，则选中物品跟在身后
				[4]【扔】模式下：（按空格键） 
					①推的物品向其方向移动至无法移动
					②对生物造成伤害 
			(3)可移动物品
							箱子	桌子	椅子   足球   鬼   玩家   虫 
				视线穿透	×	 	√		√      √    √   √     √
				玩家在此 	×		√		√      √    √   √     √
				质量（kg）  40      20      10      5     10   10     5
		2）宝箱（目前暂用箱子替代）
			(1)交互方法
				[1]未选中时向其按空格键，可打开此方向的箱门（视野更新）
				[2]向打开的箱门移动可进入箱子 
				[3]处于箱子中按空格键效果同[1]
				[4]处于箱子中可直接向相邻箱子移动，不用打开箱门
			(2)特性
				[1]敌对生物无法打开箱门，无法进入开启的箱子，无法透过关闭的箱子攻击玩家（非物理攻击除外） 
				[2]箱子不透光（玩家可透过箱门缝隙往外看，手电筒同理，calculate_vision1()） 
				[3]飞的东西无法进入箱子 
	8、力气
		(1)拳击：2N 消耗1点体力 
		(2)脚踢：15N 消耗(物品质量*0.4)点体力 
	9、特殊效果
		(1)透视、视野模糊 
		(2)虚弱
			体力持续降低 
			持续t秒，每秒降低x点体力，无法自动回复体力，无法使用空格键击飞物体或生物
			显示为灰色前景 
		(3)眩晕
			摆动视野中心 
			持续t秒，玩家在屏幕上显示的位置来回摆动(screen_center)，每次摆动间隔为Tms(T>=200ms)，摆动距离1格，方向随机 
			显示为青色前景 
		(4)失明 
			玩家视野范围缩小
			降低calculate_vision2参数mx_dis至1~5 
			显示为黑色前景 
		(5)中毒
			持续扣血 
			持续t秒，每秒扣x滴血 
			显示为绿色前景 
		(6)迷惑
			使玩家视野中出现一些错误影像 
			持续t秒，屏幕输出时随机（概率为a）在某些位置显示随机种类的生物？ 
			显示为黄色前景 
六、距离
	1、直线距离（两点间的距离公式）
	2、曼哈顿距离（MHT_DIST）
	3、步行/搜索距离（生物从一点走到另一点的步数）
七、屏幕显示 
	1、分区（左中右，三分天下） 
		1）玩家信息栏[0,0]->[46,48] 47*49 
		2）游戏地图区[46,0]->[142,48] 97*49
		3）玩家物品栏[142,0]->[188,48] 47*49 
			(1)格式
				[1]表格
					左上角："物品栏"
					行标签：数量、耐久、增益、使用指南等
					列标签：物品名+显示图像 
				[2]MC风格 
					第1~2行："持有物品：     数量：   耐久：   " 
					第2行："使用方法："
					第3行：所有物品的图像（按加入顺序排序） 
			(2)使用
				[1]按f键查找物品/选中物品并退出
				[2]查找物品时使用方向键选择
	2、屏幕更新（见“玩家”）
	3、颜色
		1）256色 SetConsoleTextAttribute(hout,0x00~0xff);
		2）RGB颜色
			(1)背景色 printf("\033[48;2;%d;%d;%dm",back.r,back.g,back.b);
			   前景色 printf("\033[38;2;%d;%d;%dm",forw.r,forw.g,forw.b);
			(2)编码方式：lh->hsv->rgb
				[1]lh=light亮度+hue色相
					亮度light：-100~0~100（s0v0~s0v100~s100v100） 
					色相hue：0~359（h）+360（白） 
				[2]色环 
					h 0  30  60  90  120  150 180  210 240  270 300  330 360
					 红  橙  黄 草绿  绿 墨绿  青 青蓝  蓝 湛蓝  紫 紫红  白 
			(3)加速技术：换色优化 
		 		每次设置颜色时判断背景/前景色是否切换，若更换才使用printf，并记录颜色至back_now/forw_now 
	4、地图打印
		1）背景色back
			(1)优先级（注意有些东西是不会出现在同一位置的） 
				尸体（KO）>玩家光圈（提示信息）>生物加减血/巢穴口受损的光圈> 
				>激光束光圈>箱>B型蜘蛛本体>B型蜘蛛附肢>隐藏门>窗户（开/关）>帘子
				>门（开/关）>出口>鬼的光圈（技能）>墙>空地
		2）前景色forw+输出字符串out
			(1)优先级
				KO>蜘蛛网（51~100） 
				>↑↓←→>玩家姓名 
				>闪>石>穿>鬼 
				>A、B型蜘蛛本体>虫>B型蜘蛛附肢
				>箱>桌>椅>球
				>矛>回旋镖>A型蜘蛛附肢>蜘蛛丝（1~50） 
				>门（锁/关）>食物>巢穴口>激光束>出口标牌>门（开）>隐藏门>镜子>窗户>帘子>道具>钥匙
				>灯>出口>楼梯>墙>空地 
		3）光照强度brightness 
			实际亮度=亮度+brightness
			（限制于[-100,100]） 
八、计时器、标志 
	1、准备
		map<string,int> game_timer记录未来某个事件发生时的游戏时间
		map<string,bool> game_flag记录某个事件是否发生 
	2、使用
	e.g.game_timer["玩家移动"]=game_time+1000;玩家体力值player1.vts.stg.strength_value在下一秒（1000ms）回复+1
		game_flag["清除尸体"]=true;有尸体被清理，更新屏幕 
		屏幕擦去“KO”字样 
		1秒后…… 
		if(game_timer["pvsr"]<=game_time&&……) player1.vts.stg.strength_value++;玩家体力值回复+1
	3、计时方式对比
		1）game_time%间隔时间
			简便，任务量大时不准，但可作为屏幕输出自适应卡顿的手段
		2）game_timer[??]<=game_time?...game_timer[??]+=间隔时间
			精确，卡顿时易造成超载运行
		3）game_timer[??]<=game_time?...game_timer[??]=game_timer+间隔时间
		或game_timer[??]+间隔时间<=game_time?...game_timer[??]=game_timer
			准确，可使对象与玩家保持相同卡顿程度
九、敌人
	1、区域更新（减小计算量）
		1）初始化：队列队列（Qbug/Qghost）为空
		2）每次玩家视野计算将能看到且不在队列的敌人加入队列，并设置敌人为更新状态（.update=true） 
		3）每次更新敌人时，离玩家距离>50且玩家不能看到，这个敌人就出队，停止更新（.update=false）
			若敌人移动时碰到不更新的敌人，把它加入队列，并设置这个敌人为更新状态（.update=true） 
	2、虫子
		1）生成
			(1)位置：巢穴，一开始在随机位置 
			(2)游戏中随机频率新生成 
		2）移动
			(1)方向：初始随机，碰到墙或其它生物就转弯（会消耗时间），碰到楼梯如果楼上/下没有其他生物就上下楼，碰到巢穴就进入 
			(2)速度：1~10格/1000毫秒（生成时确定）
		3）攻击
			(1)方式：碰撞
			(2)伤害：1~5滴血（与速度有关）  
		4）血量：5点
			(1)对玩家造成伤害+1
			(2)被激光/回旋镖/矛击中-5
			(3)被击飞每0.5s-1
			(4)血量=0时死亡，重生至巢穴内部随机位置（没有空位就等着） 
	3、虫子巢穴
		1）生成：巢穴口位于距离玩家一定距离外的空地，离出口越近越多，同时在巢穴内部地图生成同一位置的巢穴口并对应 
		2）巢穴口血量：3点
		被激光击中-1，血量=0时被摧毁并消失，不能再作为巢穴口
		3）虫子/玩家进入可传送至巢穴内部地图 
		4）存储：game_map[1~length][1~width][height+1~height+height].things.nst 
		5）陈设：只有空地和墙，没有任何物品 
	4、蜘蛛
		1）分类
			(1)A型：视力差，会织网，通过蛛网振动寻找猎物，主要近战 
			╲ ︹╱	╲ ∨╱
			＞蛛＜	〔蛛〕
			╱ ︺╲	╱ ∧╲
			(2)B型：视力好：会跟随玩家，主要远程发射蛛丝，但无法进入狭小空间（周围8格不能有障碍），无法被击退 
			〔  〕		╲ ∨︹		 ╲︹╱		 ︹∨╱
			＞蛛＜		〔蛛		＞蛛＜		  蛛〕
			╱︺ ╲		╱∧︺		〔  〕		︺∧╲
		2）生成 
			(1)位置：一开始在随机位置 
			(2)游戏中随机频率新生成 
		3）移动
			(1)速度：2~4格/1000毫秒 
			(2)分情况：
				[1]玩家碰到自己的蛛丝（且和自己相连）：沿着蛛丝向玩家方向移动并发动攻击 
				[2]随机模式：随机概率转弯（不消耗时间），碰到楼梯就随机概率进入，不会进入巢穴 
					移动到某新位置u的概率与离出生点的距离、蛛丝耐久度有关 
				[3]跟随模式（B型）
					 每次移动前向视野范围内（最远距离：5格）最近的玩家/鬼（隐身鬼也看得到？）移动（如果有的话） 
			(3)B型蜘蛛无法向后转 
		4）攻击
			(1)碰撞：1~5滴血（与速度有关，对虫子也有效）并有概率给玩家附加中毒效果（幻觉、无法移动、体力降低等） 
			(2)发射蛛丝：玩家在最远蛛丝发射距离内时，有概率发射蛛丝缠住玩家 
				蛛丝性质：飞行中不减速，可穿过空地、蜘蛛附肢、楼梯口、开着的门、球 
				实现方法：
				[1]发射：蛛丝初始位置在蜘蛛正前方，因此发射前蜘蛛必须面向目标（夹角<45°） 
				[2]飞行：速度10~15m/s，视蜘蛛血量而定
				[3]命中：击中无法进入的（墙、门、箱子等）停下在面前，击中生物变成蛛网（endurance+=75） 
			(3)毒液
				[1]麻痹：造成10s虚弱效果 
		5）血量：20点
			(1)被激光/回旋镖击中-5
			(2)被扔中每0.5秒-1 
			(3)血量=0时死亡，重生至地图随机位置
		6）物品交互 
			(1)开挡路的门（锁/关都行），推挡路的物品（推不动就算了） 
			(2)每次移动都留下蛛丝
		7）蛛网 
			(1)耐久度endurance：0~100 
				振幅k：0~1000 开始减少时间t：以毫秒为单位 
				add(x)新增振动：
					k=max(0,k-game_time+t)+x;计算上次振动到现在k还剩k-game_time+t或0，并加上增加量x 
					t=game_time;更新时间为当前时间 
			(2)效果
				情况		耐久变化	作用 
				蜘蛛经过 	+10
				物品飞过	-2*v		减速（v*(1.5-耐久*0.01)） 
				玩家经过	-20			停顿减少耐久直到耐久<=50，每次停顿体力-2 
				虫子经过				耐久>25就动不了 
			(3)显示（根据耐久度） 
				1~25：＊  26~50：ㄨ  51~75：丝  76~100：网
				位于其他物品上：前景色设为高亮白色 
	5、鬼
		1）生成
			(1)位置：一开始在随机位置 
			(2)游戏中随机频率新生成 
		2）移动
			(1)速度：3~5格/1000毫秒（生成时确定）
			(2)分情况：
				[1]能看到玩家：向玩家方向移动，不移出玩家视野 
				[2]听到玩家声音：向声音来源移动 
				[3]发现玩家足迹：跟着足迹方向移动 
				[4]随机模式：随机概率转弯（不消耗时间），碰到楼梯/巢穴就随机概率进入 
		3）攻击
			(1)方式：碰撞、击飞 
			(2)伤害：1~5滴血（与速度有关）  
		4）血量：30点
			(1)被激光/回旋镖击中-5/-3
			(2)被扔中每0.5秒-1 
			(3)血量=0时死亡，重生至巢穴内部随机位置（没有空位就等着）
		5）物品交互
			(1)推动物品
			(2)打碎玻璃（每次耐久度-20） 
			(3)开已解锁的钥匙门（第一步碰撞【打开】，第二步进入） 
			(4)力气
				[1]拳击：2N
				[2]脚踢：20N
		6）特殊属性 
			(1)进攻：正常、穿墙（附带透视）、隐身、瞬移（附带15格以内透视）、吸血
			(2)防御：正常、闪避（远程武器无效）、石化（击退抗性、矛等冷兵器无效）、肉盾（所有物理伤害无效，且不参与物理系统） 
		7）显示
			(1)字符
				隐身：魍 
				穿墙：魆
				瞬移：魉 
				石化：魑
				闪避：魅 
				其他：鬼+特定颜色 
十、运动和力
	1、运动
		1）基本移动：player_detect_move、deal_bug、deal_ghost
			主动移动 
		2）推动：push_thing
			被动移动、连续移动（碰到镜子可转向） 
		3）飞行：throw_removable
		 	被动移动、动能传导、碰障弹开 
		4）通用公式
			a=F/m加速度计算 
			m1v1+m2v2=m1'v1'+m2'v2'动量守恒 
			1/2 m1v1^2 + 1/2 m2v2^2 = 1/2 m1'v1'^2 + 1/2 m1'v1'^2动能守恒
			Δv1=2m2/(m1+m2)*(v2-v1)  Δv2=2m1/(m1+m2)*(v1-v2) 推导式 
十一、可损坏物品
	耐久度减少	推动/玩家脚踢	物体击飞	回旋镖命中	激光命中 
		镜子			50		撞击速度*5	撞击速度*5	0 
		窗户 			5		撞击速度	撞击速度	0
		帘子			0		0			50			1
十二、光照系统
	1、光源		范围				功率	特点 
	   手电筒	player1.d1-45°~45°100		跟随玩家运动 
	   灯 		无限 				50~150  不动，可开关 
	2、光照强度brightness（≠light）
		1）初始化：100 
		2）计算：（每个光源增加/减少）功率/距离
			调用calculate_vision2()，对每个照到的位置计算 
		3）显示亮度light'转化
			记当前位置为u，周围可视位置为v1,v2...vn 
			(1)透光位置：u->brightness
			(2)不透光位置：max(v1->brightness,v2->brightness,...)
			light'=light+brightness;limit_number(light',-100,100);
	3、灯动态更新 
		1）准备
			struct light->id每个灯分配一个编号 
			queue<position_3D> pos_affect_light;要更新光照的位置
			queue<position_3D> light_area[id];每个灯最后一次更新照亮的所有位置
		2）初始化
			将照到的位置加入light_area[id]
		3）更新条件：箱子推动、帘损坏、窗户损坏/开关 
		4）步骤
			(1)遍历pos_affect_light，调用calculate_vision2()求出能照射到更新位置的每盏灯 
			(2)对于每盏灯：
				light_area[id]中每个位置.brightness减少并出列，调用calculate_vision2()，
				每个照到的位置.brightness增加，并加入light_area[id] 
	4、更新手电筒
		1）准备
			item::queue<position_3D> lst;手电筒最后一次更新照到的位置
		2）更新条件：玩家视野重新计算时 
		3）步骤
			(1)pos_flashlight每个位置.brightness减少并出列
			(2)在player_calculate_vision2()中，对于计算玩家视野时ret的每个位置v：
			求出方向角a=calc_angle(player1.pos,v)，VPOS.brightness+=P/sqrt(dis)*cos(abs(player.d-a)/90*PI);余弦差角衰减 
十三、游戏画质提升
	1、逻辑层
		1）不重复输出相同位置（详见视野计算）
		2）相同颜色不重复设置（set_RGBcolor）
		3）大量位置分批次输出（详见视野计算）
		4）限制手电筒更新光照频率
		5）开O2 
	2、输出层
		1）增大输出缓冲区（setvbuf，必须放在最前面）
		2）cout.tie(0)、ios::sync_with_stdio(false)等
		3）尽量少用endl 
*/
#define MMPP(a,b,c,d) MP(MP(a,b),MP(c,d))
#define MP(a,b) make_pair(a,b)
#define PPII pair<PII,PII >
#define PII pair<int,int>
#define PSB pair<string,bool>
#define TD3 tuple<double,double,double>
#define MT make_tuple
#define PRESS_KEY_UP 72
#define PRESS_KEY_DOWN 80
#define PRESS_KEY_LEFT 75
#define PRESS_KEY_RIGHT 77
#define PRESS_KEY_TAB 9
#define PRESS_KEY_ENTER 13
#define PRESS_KEY_ESC 27
#define PRESS_KEY_SPACE 32
#define PRESS_KEY_SHIFT 16 
#define PRESS_KEY_CTRL 17
#define	PRESS_KEY_0	48
#define	PRESS_KEY_1	49
#define	PRESS_KEY_2	50
#define	PRESS_KEY_3	51
#define	PRESS_KEY_4	52
#define	PRESS_KEY_5	53
#define	PRESS_KEY_6	54
#define	PRESS_KEY_7	55
#define	PRESS_KEY_8	56
#define	PRESS_KEY_9	57
#define	PRESS_KEY_A	97
#define	PRESS_KEY_B	98
#define	PRESS_KEY_C	99
#define	PRESS_KEY_D	100
#define	PRESS_KEY_E	101
#define	PRESS_KEY_F	102
#define	PRESS_KEY_G	103
#define	PRESS_KEY_H	104
#define	PRESS_KEY_I	105
#define	PRESS_KEY_J	106
#define	PRESS_KEY_K	107
#define	PRESS_KEY_L	108
#define	PRESS_KEY_M	109
#define	PRESS_KEY_N	110
#define	PRESS_KEY_O	111
#define	PRESS_KEY_P	112
#define	PRESS_KEY_Q	113
#define	PRESS_KEY_R	114
#define	PRESS_KEY_S	115
#define	PRESS_KEY_T	116
#define	PRESS_KEY_U	117
#define	PRESS_KEY_V	118
#define	PRESS_KEY_W	119
#define	PRESS_KEY_X	120
#define	PRESS_KEY_Y	121
#define	PRESS_KEY_Z	122
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000)?1:0)  //用来检测按键的点击事件
#define REP(a) for(ll counting_variable=1;counting_variable<=a;counting_variable++)
typedef long long ll;
POINT ScreenP;
HWND h; 
CONSOLE_FONT_INFO consoleCurrentFont;
HANDLE hin=GetStdHandle(STD_INPUT_HANDLE);
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);//句柄（字体颜色专用） 
const int SMALLEST_TIME=10;//游戏时间最小单位：10毫秒
const int MAX_SCREEN_LENGTH=189,MAX_SCREEN_WIDTH=49;//ConsolePauser的最大长宽（注意每个字符长1宽2） 
const int MAX_LENGTH=100,MAX_WIDTH=100,MAX_HEIGHT=10;//游戏地图的最大长宽高 
const int HUE=360,LIGHT=100;//色相（0~359）、亮度（-100~100） 
const int KINDS_OF_DOORS=4,KINDS_OF_KEYS=4;//门、钥匙的种类数量：4
const int KINDS_OF_FOOD=2,EFFECT_OF_FOOD=3;//食物的种类数：2；效果等级数：3 
const int MAX_OBJECT_NUM=1000000;//物品最多数目 
const int MAX_PLAYER_SPEED=2000;//玩家的最大速度 
const int MAX_SIZE_OF_ITEM_LAB=17;//玩家物品栏的最大容量
const int CREATURES_NUM=4;//生物种类数（玩家、虫子、蜘蛛、鬼） 
const int MAX_BUG_NUM=1000000,MAX_SPIDER_NUM=500000,MAX_GHOST_NUM=100000;//虫子、蜘蛛、鬼的最大数量 
const int SPIDERB_SIGHT=10,GHOST_SIGHT=20;
const int MAX_LIGHT_NUM=1000000;//灯的最大数量 
const int T_SPREAD_DELAY=50;//t_spread（ms）越低扩散计算精度越高 
const double V_FOG_SPREAD=0.5;//v_spread（Δ%/s）越大扩散速度越快
const int INF=2e9;//游戏最大数字∞ 
const double PI=acos(-1);//Π 
const double eps=1e-4;//极小值
int game_map_from=0;//游戏地图来源（0：随机生成 1：读取模板） 
bool game_pause=false,game_end=false,game_success=false,start_again=false;//是否暂停/结束游戏、成功逃脱、重新开始
int game_time,start_time;//游戏（进行、开始）时间
double now_timer;//当前计时器时间（ms）
int lst_see_time;//上次重新计算玩家视野的时间 
map<string,int> game_timer;//游戏计时器 
map<string,bool> game_flag;//游戏标志 
PII back_now=MP(-100,360),forw_now=MP(0,360);//现在颜色 
void gotoxy(int x=0,int y=0);
void set_RGBcolor(int light1,int hue1,int light2,int hue2);
int RAND(int max,int min);
bool RAND_BOOL(int a);
enum MAP_FROM{
	RANDOM,FILE_MODEL
};
enum MAZE{//迷宫的墙壁、门、通道等 
	WALL,SPACE,EXIT,UPSTAIR,DOWNSTAIR,NEST,DOORS,STAIRS//前两个位置不准改 
};
enum FLOOR{//地板状况 
	NORMAL,HOLE
}; 
enum PLAYER_ENEMY{//玩家和敌人（改了这个记得改nobody_here、CREATURES_NUM等） 
	NOBODY,PLAYER,BUG,SPIDER,GHOST
};
enum OBJECT{//可堆叠拾取物品种类 
	NONE,KEY,FOO,WCG,SMO,PER,LAS/*激光枪*/,DAR/*飞镖*/,SPE/*长矛*/,DAG/*匕首*/,SWO/*剑*/,BLA/*长刀*/ 
	//LAS之后都是武器 
};
enum ALL_ITEM{//所有物品
	K1=1,K2,K3,K4,AS1,AS2,AS3,AL1,AL2,AL3,SM,PPT,BX,BL,TT,CE//取首字符和尾字符 
};
enum DOOR{//门
	DOOR1=1,DOOR2,DOOR3,DOOR4
};
enum DOOR_KEY{//钥匙 
	KEY1=1,KEY2,KEY3,KEY4
};
enum FOOD_KIND{//食物
	ADDS=1,ADDL//生命恢复和体力恢复
}; 
enum WEAPON{//武器（这个改了记得去 wcnt 更新一下！） 
	SPR=1,LSG,DART
};
enum MOVABLE{//可移动物品（这个改了记得去 movable 更新一下！）
	BOX,DESK,CHAIR,BALL
};
enum DEAL_ITEM{//处理可移动物品的方式
	PUSH,PULL,PUSH_HARD,BREAK 
};
enum DIRECTION_KEY{//方向键
	STOP=0,
	UP,DOWN,LEFT,RIGHT
};
enum CHANGE_DIRECTION{//改变方向
	TURN_RIGHT,TURN_BACK,TURN_LEFT 
};
enum ACTION_KIND{//玩家的操作类型 
	RUN,WALK,CHOOSE_ITEM,CHANGE_WPN 
};
enum ATTACK_ATTRIBUTE{//攻击性属性 
	VAMPIRE=1,DISAPP,THROUGH,INSTANT
}; 
enum DEFENSE_ATTRIBUTE{//防御性属性
	EVADE=1,ROCK,SHIELD
};
int length,width,height;//游戏地图长宽高 
int cnt_notWALL,cnt_SPACE,cnt_STAIRS;//计数 
struct RGB_color{//RGB颜色编码 
	int r,g,b;//0~255
	void init(int _r,int _g,int _b){
		r=_r;g=_g;b=_b;
	}
};
struct position_2D{//坐标结构体（xOy） 
	int x,y;//x坐标和y坐标 
	void init(){
		x=y=0;
	}
	bool operator<(position_2D a)const{//重载< 
		return x<a.x||(x==a.x&&y<a.y);
	}
	bool operator==(position_2D a)const{//重载== 
		return x==a.x&&y==a.y;	
	}
	bool operator!=(position_2D a)const{//重载!=
		return x!=a.x||y!=a.y;	
	}
	void output1(bool enter=0){//打印坐标 
		cout<<"("<<x<<","<<y<<")";
		if(enter) cout<<"\n";
	}
}pos00;
struct position_3D{//坐标结构体（xOyOz） 
	int x,y,z;//x坐标、y坐标和z坐标 
	void init(){
		x=y=z=0;
	}
	bool operator==(position_3D a)const{//重载== 
		return x==a.x&&y==a.y&&z==a.z;	
	}
	bool operator!=(position_3D a)const{//重载!=
		return x!=a.x||y!=a.y||z!=a.z;	
	}
	bool operator<(position_3D a)const{//重载<
		if(x!=a.x) return x<a.x;
		if(y!=a.y) return y<a.y;
		return z<a.z;	
	}
	void output1(bool enter=0){//打印坐标 
		cout<<"("<<x<<","<<y<<","<<z<<")";
		if(enter) cout<<"\n";
	}
}pos000;
		struct pheromone{//虫子的信息素 
			int disapp,id,d;//信息素消失的时间、谁留下的、指向 
			void init(){
				disapp=d=0;id=-1;
			}
		};
	struct enemy{//敌人信息 
		int id;//敌人的编号 
		bool dead;//生物是死是活 
		int body_disapp;//尸体消失的时间 
		pheromone phm;//信息素
		int ghost_block;//上一个鬼在这里追玩家被障碍阻挡的时间（防止卡住） 
		void init(){
			id=-1;dead=false;body_disapp=ghost_block=-INF;
			phm.init();
		}
		void init2(){
			id=-1;dead=false;body_disapp=0;
		}
	};
		struct key_door{//门
			bool exist;
			int kind;//DOOR1,DOOR2,DOOR3,DOOR4
			int state;//0：上锁，1：打开，2：关闭 
			bool light_through;//是否透明 
			void init(){
				exist=kind=state=light_through=0;
			}
		};
		struct hiden_door{//隐藏门
			bool exist;
			int kind;//1：伪装成墙 2：伪装成箱子 
			void init(){
				exist=kind=0;
			} 
		}; 
		struct exit_sign{//出口标牌结构体
			bool exist;//有没有出口标牌 
			int dir;//出口标牌指示的出口方向
			void init(){
				exist=dir=0;
			}
		};
		struct mirror{//镜子结构体
			bool exist;//有没有镜子 
			int dir,side;//镜子的方向和面数
			/*      0	1	2	3
			1side  ◤  ◥  ◢  ◣
			2side 	╱	╲  
			*/
			int endurance;//耐久度 
			void init(){
				exist=dir=side=endurance=0;
			}
			void damage(int edc){
				endurance-=edc;
				if(endurance<=0) init();
			}
		};
		struct window{//窗户结构体
			bool exist;//有没有窗户 
			int endurance;//耐久度 
			bool state;//开关状态（0：关 1：开） 
			void init(){
				exist=endurance=state=0;
			}
			void damage(int edc,position_3D u);
		};
		struct curtain{//帘子结构体
			bool exist;//有没有帘子
			int endurance;//耐久度 
			void init(){
				exist=endurance=0;
			}
		};
		struct food_pile{//食物结构体
			/*一个位置只有一个 
			bool exist;//有没有食物 
			int kind,effect;//kind:0,ADDS,ADDL effect:1,2,3（效果有多大） 
			void init(){
				exist=kind=effect=0;
			}*/
			int food_cnt[KINDS_OF_FOOD][EFFECT_OF_FOOD];//食物堆叠 
			//food_cnt[i][j]:i(kind)->ADDS-1(0),ADDL-1(1),j(effect)->1(0),2(1),3(2)
			bool exist(){
				for(int i=0;i<KINDS_OF_FOOD;i++)
					for(int j=0;j<EFFECT_OF_FOOD;j++)
						if(food_cnt[i][j]>0) return true;
				return false;
			} 
			void init(){
				memset(food_cnt,0,sizeof(food_cnt));
			}
			void make(int kind,int effect){
				if(kind<=0||effect<=0) return;
				if(kind>KINDS_OF_FOOD||effect>EFFECT_OF_FOOD) return;
				//kind:ADDS=1,ADDL=2 effect:1,2,3
				food_cnt[kind-ADDS][effect-1]++;
			}
			int kind(){//显示的种类
				for(int i=0;i<KINDS_OF_FOOD;i++)
					for(int j=EFFECT_OF_FOOD-1;j>=0;j--)
						if(food_cnt[i][j]>0) return i+ADDS;
			}
			int effect(){//显示的等级 
				for(int i=0;i<KINDS_OF_FOOD;i++)
					for(int j=EFFECT_OF_FOOD-1;j>=0;j--)
						if(food_cnt[i][j]>0) return j+1;
			}
		};
		struct laser{//激光束结构体
			bool exist;//有没有激光束 
			int laser_beam;//激光束的形式（0~3：各个方向—｜　4：命中目标※） 
			void init(){
				exist=laser_beam=0;
			}
		};
		struct weapon_energy_edc{//武器能量/耐久度回复
			bool exist;
			int num,kind;//哪种武器的能量/耐久度回复（0：激光枪 1：矛）
			void init(){
				exist=num=kind=0;
			}
		};
		struct dart{//回旋镖结构体
			bool exist(){//有没有回旋镖
				return num[0]>0||num[1]>0;
			}
			bool exist0(){//有没有地上的回旋镖
				return num[0]>0;
			}
			bool exist1(){//有没有飞行的回旋镖
				return num[1]>0;
			}
			int num[2];//0：（显示时用）地上 /1：（给敌人用）飞行中  的回旋镖的数量 
			void init(){
				num[0]=num[1]=0;
			} 
		}; 
		struct spear{//矛结构体
			bool exist;//有没有矛
			int d;//矛的方向
			bool head;//矛头 
			void init(){
				exist=d=head=0;
			} 
		};
		struct sword{//拿着的剑结构体
			bool exist;//有没有剑
			void init(){
				exist=0;
			} 
		};
		struct blade{//拿着的刀结构体
			bool exist;//有没有刀 
			bool head;//是不是刀刃 
			void init(){
				exist=head=0;
			} 
		};
		struct nest{//虫子的巢穴口
			bool exist;//有没有巢穴口 
			int id;//编号
			position_3D to;//对应的巢穴口位置（注意：可能是进去也可能是出来） 
			void init(){
				exist=0;id=-1;to.init();
			} 
		};
		struct movable{//可移动物体
			bool exist;
			int kind;//0：箱子 1：桌子 2：椅子 3：皮球 
			bool door[4];//箱子是否开启 初始为关闭（0） 
			void init(){
				exist=kind=0;
				memset(door,0,sizeof(door));
			}
		};
		struct footprint{//足迹结构体
			bool exist(){//有没有足迹
				return d!=-1;
			}
			int d;//玩家足迹方向（4：上/下楼） 
			void init(){
				d=-1;
			}
		};
		struct perspective{//使玩家产生透视效果的物品
			bool exist;
			int kind,time;//2~3,5000ms~20000ms 
			void init(){
				exist=kind=time=0;
			} 
		};
		struct smoke_bomb{//烟雾弹
			bool exist;
			//double absorbance[3];
			void init(){
				exist=false;
				//memset(absorbance,0,sizeof(absorbance));
			}
		};
		struct light{//灯
			bool exist;
			int p;//功率 
			int id;//编号 
			bool update;//需要更新 
			bool state;//状态（0：关 1：开） 
			void init(){
				exist=p=update=0;state=1;id=-1;
			}
		};
		struct spider_leg{//蜘蛛腿
			int num;//有几只腿在这里 
			int id;//-1:不确定要重新计算 >=0：最晚来的蜘蛛的编号 
			void init(){
				num=0;id=-1;
			}
		};
			bool RAND_BOOL(int a);
		struct spider_net{//蜘蛛网
			int endurance;
			int k,t;//振幅（0~1000）和衰减起始时间
			//每1ms振幅-1 
			bool exist(){
				return endurance>0;
			} 
			void init(){
				endurance=k=t=0;
			}
			void addedc(int k,position_3D u);
			int nowk(){//当前振幅
				return max(0,k-game_time+t);//防止降到负数 
			}
			void addk(int x){//game_time时振动幅度增加x 
				k=max(0,nowk()+x);//更新振幅（防止降到负数） 
				t=game_time;//改变起始时间 
			}
			void mxk(int x){//game_time时振动幅度与x取最大值 
				k=max(0,max(nowk(),x));//更新振幅（防止降到负数） 
				t=game_time;//改变起始时间 
			}
		};
		struct spider_silk{//蜘蛛丝
			int num;//数量 
			bool exist(){
				return num>0;
			}
			void init(){
				num=0;
			}
		};
		struct fog{//雾气 
			double absorbance[3];//吸光率：0.00~100.00，0为没有雾，分颜色考虑 
			//RGB_color col;//雾气的颜色（影响模糊效果的叠加颜色） 
			bool update;//是否在pos_fog中 
			bool exist(){
				return absorbance[0]>eps||absorbance[1]>eps||absorbance[2]>eps; 
			}
			void init(){
				memset(absorbance,0,sizeof(absorbance));
				update=0;
				//col.init(255,255,255);
			}
		};
	struct thing{
		int fir;//最上面的物品object编号 
		key_door kdr;
		hiden_door hdr;
		int key;//0,KEY1,KEY2,KEY3,KEY4
		mirror mirrors;
		window windows; 
		curtain crt;
		movable mvb;
		light lgt;
		food_pile foods;
		weapon_energy_edc wee;
		nest nst;  
		laser lsr;
		dart drt;
		spear spr;
		sword swd;
		blade bld;
		smoke_bomb smb;
		perspective ppt;  
		spider_leg slg;
		spider_net snt;
		spider_silk ssk;
		bool empty(){//表示这里是否没有东西 ||exit_signs.exist不用管出口标牌 
			return !(kdr.exist||hdr.exist||key||mirrors.exist||windows.exist||crt.exist||mvb.exist||lgt.exist||nst.exist
			||lsr.exist||drt.exist()||spr.exist||swd.exist||bld.exist
			||slg.num>0||snt.exist()||ssk.exist()||fir>=0); 
		}
		bool noitem(){//没有object以外的物品 
			return !(kdr.exist||hdr.exist||mirrors.exist||windows.exist||crt.exist||mvb.exist||lgt.exist||nst.exist
			||lsr.exist||drt.exist()||spr.exist||swd.exist||bld.exist||slg.num>0||snt.exist()||ssk.exist()); 
		}
		//以下不加入存在物品判断（标记物）  
		exit_sign exit_signs;
		footprint fpt;//不显示 
		fog fogs;//仅能通过模糊效果观察到 
		void init(){//初始化 
			fir=-1; 
			key=0;
			kdr.init();hdr.init();exit_signs.init();mirrors.init();windows.init();crt.init();mvb.init();lgt.init();foods.init();
			wee.init();nst.init();lsr.init();drt.init();spr.init();swd.init();bld.init();smb.init();ppt.init();
			slg.init();snt.init();ssk.init();fogs.init();
			fpt.init();
		}
	};
		struct velocity{//速度共用体（v）
			double speed;//单位：格/1000毫秒（不得为0！），有正负 
			int wait_time;//走1格停多少毫秒（不得为0！），恒为正 
			void tv(){//wait_time->speed
				if(wait_time<=0) wait_time=1;//防止出错 
				speed=1000.0/wait_time;
			}
			void vt(){//speed->wait_time
				if(fabs(speed)>0.01) wait_time=1000/fabs(speed)+0.5;//四舍五入 
				else wait_time=100000;//speed小到一定程度就默认为0.01 
				if(wait_time<=0) wait_time=1;//防止出错 
			}
		};
	struct force_move{
		int tx,ty;//运动时间 
		velocity vx,vy;//速度 
		bool lock;//锁定，无法交互（在mvb队列中） 
		PII from;//来源（<物种,id>） 
		void init(){
			tx=ty=-1;
			vx.speed=0;vx.vt();
			vy.speed=0;vy.vt();
			lock=0;
			from=MP(0,-1);
		}
		void init2(double speed,double angle,PII f){//被扔出去的东西 
			tx=ty=game_time; 
			double tmpx=cos(angle/180.0*PI),tmpy=sin(angle/180.0*PI);//vx/v、vy/v（有正负） 
			vx.speed+=speed*tmpx;vx.vt();//加速度 
			vy.speed+=speed*tmpy;vy.vt();//加速度 
			if(tx<=game_time) tx=game_time+vx.wait_time;//防止瞬间移动2格 
			if(ty<=game_time) ty=game_time+vy.wait_time;//防止瞬间移动2格 
			lock=true;
			from=f;
		}
		void init3(double spx,double spy){//改变运动物体的速度
			vx.speed=spx;vx.vt();
			vy.speed=spy;vy.vt();
		}
		void init4(double speed,double angle){//改变运动物体的速度
			vx.speed=speed*cos(angle/180.0*PI);vx.vt();
			vy.speed=speed*sin(angle/180.0*PI);vy.vt();
		}
		double speed(){//总速度（正） 
			return sqrt(vx.speed*vx.speed+vy.speed*vy.speed); 
		}
	};
	struct in_sight{
		int player;//玩家最后一次看到这个位置的时间（=lst_see_time：玩家现在看得到，<lst_see_time：玩家现在看不到）
		double vague[3];//player_vague 玩家看到这个位置的模糊程度（0~1），分不同颜色（r0g1b2） 
		int other;//其他生物 
		void init(){
			player=other=-INF;
			vague[0]=vague[1]=vague[2]=0;
		}
		double pvg(){
			return (vague[0]+vague[1]+vague[2])/3;
		} 
		bool vague_exist(){
			return vague[0]>eps||vague[1]>eps||vague[2]>eps; 
		}
	};
struct MAP{//改了这里要去all_assigned改一下 
	int maze;//WALL,SPACE,EXIT,UPSTAIR,DOWNSTAIR,LIFT
	int floor;//NORMAL,HOLE 
	int player_enemy;//NOBODY,PLAYER,BUG,GHOST
	int brightness;//光照亮度 
	enemy emy;//敌人信息 
	thing things;//物品 
	force_move fcmv;//力和运动 
	in_sight ist;
	void init(){
		floor=NORMAL;
		maze=WALL;
		player_enemy=NOBODY;
		brightness=-95;//微弱的环境光 
		emy.init(); 
		things.init();
		fcmv.init();
		ist.init();
	}
	double mass();
	bool update_light(){//此位置变化更新光照是否有用（不浪费时间） 
		return 1;//brightness>-100&&(ist.player==lst_see_time||ist.other==lst_see_time)
	}
	bool see(int being=GHOST,int attack=0){//生物是否可看见此位置 
		if(being==GHOST){
			if(attack==VAMPIRE)//来自吸血鬼的威慑 
				return brightness>=-100&&brightness<=0&&ist.pvg()<0.5;
			if(attack==THROUGH)//来自穿墙鬼的威慑 
				return brightness>=-100&&brightness<=100&&ist.pvg()<0.7;
			return brightness>=-80&&brightness<=80&&ist.pvg()<0.4;
		}
		else if(being==SPIDER) return brightness>=-90&&brightness<=30&&ist.pvg()<0.4;
		//亮度合适、模糊度(0~1)够低 
		return false;
	}
	bool see_fr(){//生物是否可从此位置看见别处
	    return ist.pvg()<0.4;//模糊度(0~1)够低
	}
	bool burn_vampire(){//光强是否可灼烧吸血鬼
		return brightness>0; 
	}
}game_map[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
struct direction{//方向结构体 
	int d1,d2;//d1（前后）偏d2（左右）方向 
};
		struct life_injury{//生命和受伤结构体
			int change;//下面这个变了没有（1：增加 2：减少） 
			double life;//生命值（0%~100%，%省略）
			double hurt,recovery;//受伤值、回复值 
			double lst_hurt;//上次受伤的减少值 
			PII last_injury_from;//上次伤害来源 
			int last_injury_time;//上次受伤时间 
			int no_hurt;//免伤效果截止时间 
			void init(double lf){//初始化 
				life=lf;hurt=recovery=lst_hurt=change=0;last_injury_from=MP(0,-1);last_injury_time=-INF; 
				no_hurt=-INF; 
			}
			bool canhurt(){
				return no_hurt<=game_time;
			}
		};
		struct strength{//体力结构体
			bool change;//下面这个变了没有 
			double physical_strength;//体力值（0%~100%，%省略）
			int recovery_time;//恢复时间 
			void init(){//初始化 
				physical_strength=100;change=1;recovery_time=300;
			}
		};
	struct vital_signs{//生命体征结构体 
		life_injury lfin;//生命和受伤
		strength stg;//体力 
		void init(){//初始化 
			lfin.init(100);stg.init(); 
		}
	};
	struct kill_count{//击杀数
		int sum;
		int det[CREATURES_NUM+1];//NOBODY==0
		bool change;//击杀数是否变化 
		void init(){
			sum=change=0;
			memset(det,0,sizeof(det));
		}
		void update(int add,int kind){
			sum+=add;det[kind]+=add;
			change=true;
		} 
		string detail(int k=0);
	}; 
	struct score{//分数（泛指游戏结束时评级要用的指标） 
		int time_spent;//逃出花费的时间 
		kill_count kc;//击杀数 
		int shoot_times,shoot_hit_times;//击杀数、使用射击类武器次数，命中敌人次数 
		double hit_rate;//命中率 
		int hurt_times;//遭受攻击次数 
		void init(){//初始化 
			time_spent=shoot_times=shoot_hit_times=hit_rate=hurt_times=0;
			kc.init();
		}
	};
		struct key{//钥匙结构体
			int door_keys[KINDS_OF_KEYS];//存储不同种类的钥匙
			int treasure_keys;//用来开宝箱的钥匙
			void init(){//初始化 
				memset(door_keys,0,sizeof(door_keys));
				treasure_keys=0;
			} 
		};
		struct stored_food{//玩家存储的食物结构体
			int food_cnt[KINDS_OF_FOOD][EFFECT_OF_FOOD];//存储不同效果的食物 
			void init(){//初始化 
				memset(food_cnt,0,sizeof(food_cnt));
			} 
		};
			struct laser_gun_info{//激光枪的数据 
				int last_time,cool_time;//持续时间、冷却时间 
				int kind,kd_cnt;//模式、模式总数 
				bool kd_change;//上面这个变了没有
				int kd_energy[5];//模式对应的能量消耗 
				string kname[5];//模式名
				void init(){
				 	kind=0;last_time=300;cool_time=200;
				 	kd_cnt=5;
				 	kd_energy[0]=1;kd_energy[1]=3;kd_energy[2]=3;kd_energy[3]=4;kd_energy[4]=8;
				 	kname[0]="正常";kname[1]="三联";kname[2]="三向";kname[3]="四处扫射";kname[4]="八面开花";
				}
			};
			/*
			struct holding_spear{//手持矛
				int endurance;//耐久度 
				void init(){
					endurance=100;
				}
			};
			struct throwing_dart{//回旋镖
				int num;//数量 
				void init(){
					num=0;
				}
			};*/
		struct weapon_carried{//武器
			int primary,secondary;//主武器、副武器 
			//对应物品栏中的编号
			bool sw_change;//上面这个变了没有
			laser_gun_info lsg;
			/*
			throwing_dart drt;
			holding_spear hsr;*/
			bool data_change,mode_change;//以上武器的参数信息/模式变了没有 
			void init(){
				primary=secondary=-1;
				sw_change=data_change=mode_change=0; 
				lsg.init();//drt.init();hsr.init();
			}
		};
		struct removable{//可移动的物品 
			int deal_kind;//处理物品的方式（PUSH,PULL） 
			bool dl_change;//上面这个变了没有 
			position_3D select;//选中物体的位置
			bool throw_ready;//准备扔东西 
			void init(){
				deal_kind=PUSH;dl_change=throw_ready=false; 
				select.init();
			} 
		}; 
		struct flashlight{//手电筒
			bool state;//0：关 1：开 
			int angle;//照射角度：d-angle ~ d+angle 
			int p;//功率 
			bool change;//上面这些参数变了没有 
			queue<pair<position_3D,int> > lst;//上次更新照射的地方（位置，光照强度增量） 
			void init(){
				state=0;angle=60;p=70;change=0;
				while(!lst.empty()) lst.pop();
			}
		};
		struct prop{//道具 
			int smb;//烟雾弹
			void init(){
				smb=0;
			} 
		};
	struct item{//物品结构体 
		key keys; 
		stored_food foods;
		prop pp;
		bool num_change;//物品数量是否变化 
		int select_number;//选中的物品在物品栏里的编号（0~） 
		bool sn_change;//上面这个变了没有  
		vector<int> item_lab,item_num;//物品栏（最顶层物品编号+数量）
		bool il_change;//上面这个变了没有 
		weapon_carried wpn;
		removable rmv;
		flashlight flt;
		void init(){//初始化 
			keys.init();
			foods.init();
			pp.init();
			//以上是物品具体信息 
			num_change=0; 
			select_number=0;sn_change=il_change=0;
			wpn.init();
			item_lab.clear();item_num.clear();
			for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++) item_lab.push_back(-1),item_num.push_back(0);
			flt.init();
		}
		string item_name(int sn);//物品名字 
		//int item_num(int sn);//物品数量 
		int item_endurance(int sn);//物品耐久 
		string item_method(int sn);//物品使用方法 
		void print_item(int k);//根据物品的编码打印物品 
		void print1();//打印物品栏选中的物品信息 
		void print2();//打印物品栏里的所有物品
		void print3();//给选中物体标记位置
		void wpn_print1();//打印“武器栏” 
		void wpn_print2();//打印主武器及其信息 
		void wpn_print3();//打印副武器
	};
		struct x_ray{//透视 
			int num,time;//视野层数（1是正常状态，即透视num-1层）、结束时间，只能看见x_ray层阻挡视线位置内的位置
		    bool change;//上面这些变了没有 
			void init(){
				num=1;time=-1;
				change=false; 
			}
		};
		struct dim_sight{//快速移动中的视野模糊
			int cpt,part;//完全/部分模糊的最小距离（>） 
			int time,last;//上次移动的时间 
			bool dim;//当前是否模糊显示 
			void init(){
				cpt=15;part=7;
				time=-INF;last=700;
				dim=false; 
			}
		};
		struct weakness{//虚弱 
			int end;//效果结束时间
			int t,T;//上次减体力时间、减体力周期 
			int x;//减体力量 
		    bool change;//上面这些变了没有 
		    PII from;//效果来源 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=t=-INF;
				T=0;
				x=0;
				change=false; 
				from=MP(0,-1);
			}
		};
		struct vertigo{//眩晕
			int end;//效果结束时间
			int t,T;//上次摆动时间、摆动周期 
		    bool change;//上面这些变了没有 
		    PII from;//效果来源 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=t=-INF;T=0;
				change=false; 
				from=MP(0,-1);
			}
		}; 
		struct blindness{//致盲
			int end;//效果结束时间
			int vision_dis;//可视最远距离（曼哈顿）
		    bool change;//上面这些变了没有 
		    PII from;//效果来源 
			bool exist(){
				return end>game_time;
			}
			void init(){
				end=-INF;
				vision_dis=-1;
				change=false; 
				from=MP(0,-1);
			}
		};
		struct methysis{//中毒
			int end;//效果结束时间
			int t,T;//上次扣血时间、扣血周期
			int x;//每次扣血扣血量 
		    bool change;//上面这些变了没有 
		    PII from;//效果来源 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=t=-INF;
				T=x=0;
				change=false; 
				from=MP(0,-1);
			}
		};
		struct confusion{//迷惑
			int end;//效果结束时间
			int a;//屏幕出现错误影像的概率
		    bool change;//上面这些变了没有 
		    PII from;//效果来源 
			bool exist(){
				return end>game_time;
			} 
			void init(){
				end=-INF;
				a=0;
				change=false; 
				from=MP(0,-1);
			} 
		};
	struct special_effect{//特殊效果结构体（不包括回血、回体力）
		x_ray xry; 
		dim_sight dst;
		weakness wks;
		vertigo vtg;
		blindness bds;
		methysis mts;
		confusion cfs;
		void init(){
			xry.init();//正常视野
			dst.init();
			
			wks.init();
			vtg.init();
			bds.init();
			mts.init();
			cfs.init();
		}
		bool exist(){//现在是否有特殊效果 
			return xry.num>1||wks.exist()||vtg.exist()||bds.exist()||mts.exist()||cfs.exist();
		}
		bool change(){
			return xry.change||wks.change||vtg.change||bds.change||mts.change||cfs.change;
		}
	};
struct player{//玩家 
	position_3D pos;//坐标
	int d1,d2;//移动方向，视线/瞄准方向
	int color;//如何显示（0：正常蓝 1：补血绿 2：受伤红 3：变方向↑↓←→4：格挡 5：闪烁字） 
	string flash_word; 
	int angle,lsta;//鼠标指向的方向（0~359）
	int alc;//鼠标方向上次改变时间 angle lst change 
	velocity w;//角速度（°/s） 
	position_3D mpos;//鼠标位置 
	vital_signs vts;//生命体征 
	score scr;//分数 
	velocity vlc;//速度 
	item items;//物品
	special_effect spe;//特殊效果 
	string name;//名字 
	int grid;//格挡持续至什么时间 
	void init();//初始化 
	/*以下为标志变量*/
	bool d1_change,d2_change,move;//方向是否改变，是否改变了位置
	bool up_down,ud_change,lst_ud,lst_enter,enter_nest;
	//是否（自动）上/下楼梯或者进/出巢穴口，前面这个变了没有，上次是否自动上/下楼梯，上次是否自动进/出巢穴口
	bool flash,use_weapon,pull_thing,enemy_move;//是否闪烁，是否使用武器，是否拉动物品，虫子/鬼（在视野里）是否改变了位置 
	int action_kind;//玩家动作（0：奔跑 1：行走 2：选择物品 4：改变方向）
	//RUN,WALK,CHOOSE_ITEM,CHANGE_WPN
	bool ak_change;//上面这个变了没有 
}player1; 
struct pos_player_see{//玩家看得见的格子 
	position_3D pos;//坐标
};
queue<position_3D> pos_in_sight;
//玩家现在看得见的新（屏幕上对应位置没有显示）位置
queue<position_2D> pos_lst_sight;
//上次屏幕上显示的位置
set<position_2D> pos_backup;//备份（去重）
set<position_3D> pos_change;//在视野内自己更新的位置 
map<position_2D,string> screen_pos;//屏幕上的位置显示内容的编码 
map<position_2D,int> screen_z;//屏幕上现在需要显示的位置所处的楼层（z坐标） 
struct rectangle{//矩形结构体（用于屏幕区域等） 
	position_2D upper_left,lower_right;//左上角和右下角
	void init(position_2D ul,position_2D lr){//初始化 
		upper_left=ul,lower_right=lr;
	} 
	void init(int x_1,int y_1,int x_2,int y_2){//初始化 
		upper_left=(position_2D){x_1,y_1},lower_right=(position_2D){x_2,y_2};
	}
	void output_frame(string c="*",PPII color=MP(MP(-100,360),MP(0,360)),int kind=1){//输出矩形边框 
		PII back=color.first,forw=color.second;//背景色和前景色 
		for(int x=upper_left.x;x+c.size()-1<=lower_right.x;x+=c.size()){
			int y_1=upper_left.y,y_2=lower_right.y;
			gotoxy(x,y_1);
			set_RGBcolor(back.first,back.second,forw.first,forw.second);//SetConsoleTextAttribute(hout,color);
			cout<<c;
			gotoxy(x,y_2);
			cout<<c;
		}
		if(kind)
			for(int y=upper_left.y;y<=lower_right.y;y++){
				int x_1=upper_left.x,x_2=lower_right.x;
				gotoxy(x_1,y);
				set_RGBcolor(back.first,back.second,forw.first,forw.second);//SetConsoleTextAttribute(hout,color);
				cout<<c;
				gotoxy(x_2,y);
				cout<<c;
			}
	}
	bool contain(position_2D u){//u在此屏幕区域中（不包括边界） 
		int x_1=upper_left.x,x_2=lower_right.x;
		int y_1=upper_left.y,y_2=lower_right.y;
		return u.x>x_1&&u.x<x_2&&u.y>y_1&&u.y<y_2;
	}
}whole_screen,vital_signs_area,item_area,weapon_area;
//整个屏幕、游戏地图区域、玩家信息栏、玩家物品栏、玩家武器栏 
position_2D screen_center;//屏幕中心对应的地图坐标 
	struct food{//一份食物 
		int kind,effect;//kind:0,ADDS,ADDL effect:1,2,3
		void init(){kind=effect=0;}
		bool operator==(food b){
			return kind==b.kind&&effect==b.effect;
		}
	}food00;
	struct weapon_charge{//武器充能（装弹/耐久）
		int num,kind;//哪种武器的能量/耐久度回复（0：激光枪 1：矛）
		void init(){num=kind=0;} 
		bool operator==(weapon_charge b){
			return num==b.num&&kind==b.kind;
		}
	};
	struct see_through_prop{//透视道具
		int kind,time;//2~3,5000ms~20000ms  
		void init(){kind=time=0;}
		bool operator==(see_through_prop b){
			return kind==b.kind&&time==b.time;
		}
	}ppt00;
struct object{//地图物品 
	int type;//NONE,KEY,FOO,WCG,SMO,PER,LAS,DAR,SPE,DAG,SWO,BLA
	int und;//下面放的物品的id（没有：-1） 
	union{
		int key;//0,KEY1,KEY2,KEY3,KEY4
		food foods;
		weapon_charge wcg;
		int lsrE,sprE,daggerE,swordE,bladeE;
		see_through_prop stp;
	};
	void init(){
		type=NONE;
		und=-1;
		key=lsrE=sprE=daggerE=swordE=bladeE=0;
		foods.init();wcg.init();stp.init();
	}
	bool nowea(){
		return type<LAS;
	}
};
bool operator==(object a,object b){
	if(a.type!=b.type) return false;
	switch(a.type){
		case KEY:return a.key==b.key;
		case FOO:return a.foods==b.foods;
		case WCG:return a.wcg==b.wcg;
		case LAS:case DAR:case SPE:case DAG:case SWO:case BLA:return 1;
		case SMO:return 1;
		case PER:return a.stp==b.stp;
	}
	return true;
}
vector<object> objects;//地图所有物品的列表 
bool type_weapon(int type){
	return type>=LAS;
}
int object_type(int x){//objects[item_lab[x]].type 
	vector<int> &v=player1.items.item_lab;
	if(x<0||x>=v.size()) return NONE;
	int id=v[x];
	if(id<0) return NONE;
	return objects[id].type;
}
void new_object(object obj,int &fir){//产生新的物品 
	obj.und=fir;
	fir=objects.size();//从0开始编号 
	objects.push_back(obj);
}
bool add_object1(position_3D pos,int id){//放置物品obects[id]到pos
	if(id<0) return 0;
	MAP &POS=game_map[pos.x][pos.y][pos.z];
	thing &THING=POS.things;
	objects[id].und=THING.fir;
	THING.fir=id; 
	if(POS.ist.player==lst_see_time) pos_change.insert(pos);//屏幕更新 
	return 1;
}
bool del_object1(position_3D pos){//拿走pos最上层物品
	MAP &POS=game_map[pos.x][pos.y][pos.z];
	thing &THING=POS.things;
	int id=THING.fir;
	if(id<0) return 0;
	THING.fir=objects[id].und;
	objects[id].und=-1;
	if(POS.ist.player==lst_see_time) pos_change.insert(pos);//屏幕更新 
	return 1;
}
bool add_object2(int id,int x){//放置物品objects[id]到item_lab[x]最上层/最下层  
	if(id<0) return 0;
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(x<0||x>=v.size()) return 0;
	if(v[x]<0) items.il_change=true;
	if(v[x]>=0&&type_weapon(objects[v[x]].type)){
		int tmp=v[x];
		while(objects[tmp].und>=0) tmp=objects[tmp].und;//如果v[x]非空就把武器放在最下层 
		objects[tmp].und=id;
		items.item_num[x]++;//数量+1 
		items.num_change=true;
		if(x==items.wpn.primary||x==items.wpn.secondary){
			items.wpn.sw_change=items.wpn.data_change=1;//及时更新 
		}
		return 1;//记得返回 
	}
	objects[id].und=v[x];
	v[x]=id;
	items.item_num[x]++;
	items.num_change=true;
	return 1;
}
bool del_object2(int x){//拿走item_lab[x]最上层物品
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(x<0||x>=v.size()) return 0;
	int id=v[x];
	if(id<0) return 0;
	v[x]=objects[id].und;
	objects[id].und=-1;
	items.item_num[x]--;//数量-1 
	if(v[x]<0) items.il_change=true;
	items.num_change=true;
	weapon_carried &wpn=items.wpn;
	if(x==wpn.primary){
		if(v[x]<0){
			wpn.primary=wpn.secondary;//主武器换成副武器 
			wpn.secondary=-1;//副武器 无 
			wpn.sw_change=1;
		}
		wpn.data_change=1;//及时更新 
	}
	if(x==wpn.secondary){
		if(v[x]<0){
			wpn.secondary=-1;//副武器 无 
			wpn.sw_change=1;
		}
		wpn.data_change=1;//及时更新 
	}
	return 1;
}
void player_putback_weapon(int id){
	if(id<0) return;
	object &ob=objects[id];
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	bool success=0;
	for(int i=0;i<v.size();i++)
		if(v[i]>=0){
			object ob2=objects[v[i]];
			if(ob==ob2){//堆在一样的上面 
				ob.und=v[i];
				v[i]=id;
				success=1;
				break;
			}
		}
	if(!success){
		for(int i=0;i<v.size();i++)
			if(v[i]<0){//不然就放在空位置 
				ob.und=v[i];
				v[i]=id;
				break;
			}
		/*
		if(!success){//再不然新开一个位置 
			v.push_back(-1);
			del_object1(pos);
			add_object2(id,v.size()-1);
		}*/
	}
} 
bool add_weapon(int x){//拿出新武器 
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(x<0||x>=v.size()) return 0;
	weapon_carried &wpn=items.wpn;
	wpn.secondary=wpn.primary;
	wpn.primary=x;
	wpn.data_change=wpn.sw_change=1;
	return 1;
}
bool object_addE(int x,int add){//作用于物品栏中的激光枪、长矛等 
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	weapon_carried &wpn=items.wpn;
	if(x<0||x>v.size()) return 0;
	int id=v[x];
	if(id<0) return 0;
	object &obj=objects[id];
	int flag=0;
	switch(obj.type){
		case LAS:
			obj.lsrE+=add;
			if(obj.lsrE<=0) flag=2;
			else flag=1;
			break;
		case SPE:
			obj.sprE+=add;
			if(obj.sprE<=0) flag=2;
			else flag=1;
			break;
		case DAG:
			obj.daggerE+=add;
			if(obj.daggerE<=0) flag=2;
			else flag=1;
			break;
		case SWO:
			obj.swordE+=add;
			if(obj.swordE<=0) flag=2;
			else flag=1;
			break;
		case BLA:
			obj.bladeE+=add;
			if(obj.bladeE<=0) flag=2;
			else flag=1;
			break;
	}
	if(flag==2) del_object2(x);//能量/耐久耗光 
	if(flag) wpn.data_change=1;
	return flag;
}
int object_cnt(int id){//堆叠计数 
	int cnt=0;
	while(id>=0){
		id=objects[id].und;
		cnt++;
	}
	return cnt;
}
queue<position_3D> spears,swords,blades,laser_beams;//上次显示在屏幕上矛、剑、刀、激光束的队列 
queue<pair<position_3D,int> > laser_beam_light;//激光束照亮范围队列 
struct flying_dart{//飞行的回旋镖
	position_3D pos;//坐标 
	int tx,ty;//每次飞动的时间 
	velocity vx,vy;//x、y方向上的速度（有正负） 
	int id;//编号 
	void init(position_3D u,double angle,int _id){//初始化
		id=_id;
		pos=u; 
		tx=ty=game_time; 
		double speed=15;//回旋镖速度15m/s 
		double tmpx=cos(angle/180.0*PI),tmpy=sin(angle/180.0*PI);//vx/v、vy/v（有正负） 
		vx.speed=speed*tmpx;vx.vt();
		vy.speed=speed*tmpy;vy.vt();
		if(vx.wait_time<vy.wait_time) ty+=vy.wait_time-vx.wait_time;
		else tx+=vx.wait_time-vy.wait_time;
	}
}; 
queue<flying_dart> darts;//飞行中的回旋镖队列
struct flying_mvb{//飞行的可移动物品
	position_3D pos;//坐标 
	int lst_move_time;//上次飞动时间 
	void init(position_3D u){
		pos=u; 
		lst_move_time=game_time; 
	} 
}; 
queue<flying_mvb> mvbs;//飞行中的东西队列
struct bug{//虫子结构体
	position_3D pos;//坐标 
	int d;//方向 
	velocity vlc;//速度  
	life_injury lfin;//生命
	int lst_ud;//上次上下楼时间（防止卡在一对楼梯里） 
	bool change_pos;//被打死了，改变位置复活 
	bool update;//是否要更新（减小计算量） 
	int enter_nest;//上次进出巢穴口时间 
	void init(position_3D u,double speed);
};
vector<bug> bugs;//编号：0~MAX_BUG_NUM-1
queue<int> Qbug_hurt;//虫子队列（编号）
struct bug_nest{//虫子巢穴口结构体
	position_3D pos;//坐标
	life_injury lfin;//生命
	bool destroy;//是否被摧毁 
	void init(position_3D u);
};
vector<bug_nest> bug_nests;//虫子的巢穴口
struct spider{//蜘蛛结构体 
	position_3D pos;//坐标 
	position_3D bir;//出生点 
	position_3D prey;//猎物最后出现的位置 
	int d;//方向（4：上下楼、进出巢穴口） 
	velocity vlc;//速度  
	life_injury lfin;//生命
	bool kind;//0：A型 1：B型 
	bool change_pos;//被打死了，改变位置复活 
	bool update;//是否要更新（减小计算量） 
	void init(position_3D u,bool k);
}; 
vector<spider> spiders;//编号：0~MAX_SPIDER_NUM-1
queue<int> Qspider_hurt;//蜘蛛队列（编号）
struct flying_ssk{//飞行的蜘蛛丝
	position_3D pos;//坐标 
	int tx,ty;//每次飞动的时间 
	velocity vx,vy;//x、y方向上的速度（有正负） 
	void init(position_3D u,double speed,double angle){//初始化（抄dart的） 
		pos=u; 
		tx=ty=game_time; 
		double tmpx=cos(angle/180.0*PI),tmpy=sin(angle/180.0*PI);//vx/v、vy/v（有正负） 
		vx.speed=speed*tmpx;vx.vt();
		vy.speed=speed*tmpy;vy.vt();
		if(vx.wait_time<vy.wait_time) ty+=vy.wait_time-vx.wait_time;
		else tx+=vx.wait_time-vy.wait_time;
	}
}; 
queue<flying_ssk> ssks;//飞行中的蛛丝队列
string spider_image[2][4][3][3]={//AB型*4方向*3y*3x 
	{//A型 
		{//d=0
			{"╲ ","︹","╱ "},
			{"＞","蛛","＜"},
			{"╱ ","︺","╲ "},
		},
		{//d=1
			{"╲ ","∨","╱ "},
			{"〔","蛛","〕"},
			{"╱ ","∧","╲ "},
		},
		{//d=2 
			{"╲ ","︹","╱ "},
			{"＞","蛛","＜"},
			{"╱ ","︺","╲ "},
		},
		{//d=3
			{"╲ ","∨","╱ "},
			{"〔","蛛","〕"},
			{"╱ ","∧","╲ "},
		}
	},
	{//B型 
		{//d=0
			{"〔","","〕"},
			{"＝","蛛","＝"},
			{"╱ ","︺","╲ "},
		},
		{//d=1
			{"╲ ","‖","︹"},
			{"〔","蛛",""},
			{"╱ ","‖","︺"},
		},
		{//d=2 
			{"╲ ","︹","╱ "},
			{"＝","蛛","＝"},
			{"〔","","〕"},
		},
		{//d=3
			{"︹","‖","╱ "},
			{"","蛛","〕"},
			{"︺","‖","╲ "},
		}
	}
};//空字符就是不用输出 
		struct skill_vampire{
			int time;
			void init(){
				time=0;
			}
		};
		struct skill_through{
			bool use;//是否正在使用 
			int time;//效果开始/结束时间 
			void init(){
				use=time=0;
			}
		};
		struct skill_disappear{ 
			bool use;//是否正在使用 
			int time;//效果开始/结束时间（即切换use的时间点） 
			int maxt;//最多隐身时间 
			int kind;//种类（1：拟态，伪装成墙 2：消失） 
			void init(){
				use=time=maxt=0;kind=1; 
			}
		};
		struct skill_instant{
			int p;//每次移动瞬移概率 
			int dis;//瞬移后离玩家最大距离 
			void init(){
				p=dis=0;
			}
		};
		struct skill_evade{
			bool use;//是否正在使用
			int k;//闪避概率 
			void init(){
				use=k=0;
			}
		};
		struct skill_rock{
			bool use;//是否正在使用 
			double k;//抗击退系数（速度*=k） 
			void init(){
				use=0;k=1;
			}
		};
	struct special_attribute{//特殊属性
		int attack,defense;
		//攻击性技能（VAMPIRE,DISAPP,THROUGH,INSTANT）、防御性技能（EVADE,ROCK,SHIELD） 
		skill_vampire vpr;
		skill_through thr;
		skill_disappear disa;
		skill_instant ins;
		skill_evade eva;
		skill_rock rck;
		void init(int a=0,int d=0){
			attack=a;defense=d;
			vpr.init();thr.init();disa.init();ins.init();
			eva.init();rck.init();
		}
		bool can_through(){//能否穿墙 
			return attack==THROUGH&&thr.use;
		} 
		bool can_disappear(){//是否隐身
			return attack==DISAPP&&disa.use;
		}
		bool can_evade(){//是否闪避 
			return (defense==EVADE||defense==SHIELD)&&RAND_BOOL(eva.k);
		}
	};
struct ghost{//鬼结构体 
	position_3D pos;//坐标 
	position_3D goal;//移动目标 
	int d;//方向（4：上下楼、进出巢穴口） 
	velocity vlc;//速度  
	life_injury lfin;//生命
	special_attribute spat;//技能 
	special_effect spe;//特殊效果 
	double attack_time;//反应时间（0~1）
	//指每次移动周期后attack_time*vlc.wait_time发动攻击 
	bool change_pos;//被打死了，改变位置复活 
	bool update;//是否要更新（减小计算量） 
	bool rampage;//是否在横冲直撞（弹射起步） 
	void init(position_3D u,int att,int def);
};
vector<ghost> ghosts;//编号：0~MAX_GHOST_NUM-1
queue<int> Qghost_hurt;//鬼队列（编号） 
queue<position_3D> pos_dead;//尸体队列 
struct barrel{//桶结构体
	position_3D pos;//坐标 
	velocity vlc;//速度 
	bool stage;//状态（静/动） 
}; 
struct tnt{//炸弹结构体 
	position_3D pos;//坐标
	bool stage;//状态（静止/引燃） 
};
queue<barrel> barrels;//桶队列
queue<tnt> TNTs;//炸弹队列
queue<PPII> message_box;//消息（a杀了b） 
queue<position_3D> pos_affect_light,lights_update;//所有改变状态并对光照造成影响的位置、需要更新（LGT.update==1）的所有灯的位置 
vector<position_3D> light_area[MAX_LIGHT_NUM];//每个id的灯最后一次更新的光照范围 
queue<position_3D> pos_fog;//有可能扩散的雾 
int dx4[4]={0,1,0,-1};
int dy4[4]={-1,0,1,0};
//前、右、后、左 
int dx8[8]={0,1,1,1,0,-1,-1,-1};
int dy8[8]={-1,-1,0,1,1,1,0,-1};
//前、右前、右、右后、后、左后、左、左前 
queue<position_3D> Q;
bool vst[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int dis[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int dis_to_exit[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9],dis_to_player[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int pos_cnt[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
int mx_dis_to_player;
bool pos_in_room[MAX_LENGTH+9][MAX_WIDTH+9][MAX_HEIGHT*2+9];
vector<position_3D> pos_dis_to_player_door[MAX_LENGTH*MAX_WIDTH*MAX_HEIGHT*2],pos_dis_to_player_key[MAX_LENGTH*MAX_WIDTH*MAX_HEIGHT*2];
vector<position_3D> pos_in_nest;
//BFS专用
int sum1[MAX_LENGTH+9][MAX_WIDTH+9],sum2[MAX_LENGTH+9][MAX_WIDTH+9];
//前缀和 
bool flagx[MAX_LENGTH+9],flagy[MAX_WIDTH+9];
int val_x[MAX_LENGTH+9][2],val_y[MAX_WIDTH+9][2];
//横纵坐标映射 
int fa_dsu[MAX_LENGTH*MAX_WIDTH*MAX_HEIGHT*2+9];
//并查集 
bool stair_exist[MAX_HEIGHT+9][2];//记录某层楼有没有上0/下1楼梯
vector<position_3D> divided_walls;//分隔墙/可以挖楼梯的地板 
//迷宫生成 
int occlusion[4][360];
int cnt_visible[4]={360,360,360,360};
double vague[4][360][3];//不同颜色的模糊程度（0.00：完全清晰，1.00：啥也看不清） 
queue<position_3D> pos_vague;//模糊的位置 
//视野计算 
char sound_spider_move[5][20]={
	"昆虫行动1.wav",
	"昆虫行动2.wav",
	"昆虫行动3.wav",
	"昆虫行动4.wav",
	"昆虫行动5.wav"
};
//声音 
double screen_zoom;//屏幕缩放值
//游戏日志
std::ofstream logFile1("game_log.txt",std::ios::app),logFile2("game_log.txt",std::ios::trunc); 
//变量 
void logMessage(const std::string& message,int kind=1){//游戏日志 
	if(kind==1) logFile1<<message<<std::endl;
	else logFile2<<message<<std::endl;
	/*
    if(logFile.is_open()){
        logFile<<message<<std::endl;
        logFile.close();
    }*/
}
void clearGameLog(){
	logMessage("",2);
	/*
	//以截断模式打开文件，这会清空文件内容
    std::ofstream file("game_log.txt", std::ios::trunc);
    //如果文件成功打开，会自动关闭，因为 ofstream 对象析构时会关闭文件
    */
}
double get_screen_zoom(){//获取屏幕缩放值
	HWND hWnd=GetDesktopWindow();
    HMONITOR hMonitor=MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    //获取监视器逻辑宽度与高度
    MONITORINFOEX miex;
    miex.cbSize=sizeof(miex);
    GetMonitorInfo(hMonitor, &miex);
    int cxLogical=(miex.rcMonitor.right-miex.rcMonitor.left);
    int cyLogical=(miex.rcMonitor.bottom-miex.rcMonitor.top);
    //获取监视器物理宽度与高度
    DEVMODE dm;
    dm.dmSize=sizeof(dm);
    dm.dmDriverExtra=0;
    EnumDisplaySettings(miex.szDevice,ENUM_CURRENT_SETTINGS,&dm);
    int cxPhysical=dm.dmPelsWidth;
    int cyPhysical=dm.dmPelsHeight;
    //缩放比例计算 （实际上使用任何一个即可） 
    double horzScale=((double)cxPhysical/(double)cxLogical);//宽度缩放值 
    double vertScale=((double)cyPhysical/(double)cyLogical);//高度缩放值 
    return horzScale;
}
position_2D pos_mouse(){//鼠标当前位置（x不一定为偶数） 
	GetCursorPos(&ScreenP);
	ScreenToClient(h,&ScreenP);
	//ScreenP.x*=screen_zoom;ScreenP.y*=screen_zoom;//屏幕缩放比例 *screen_zoom
	GetCurrentConsoleFont(hout,FALSE,&consoleCurrentFont);//获取字体信息
	consoleCurrentFont.dwFontSize.X=consoleCurrentFont.dwFontSize.Y/2;
	position_2D pos; 
	int sx=consoleCurrentFont.dwFontSize.X,sy=consoleCurrentFont.dwFontSize.Y;
	pos.x=ScreenP.x/sx;
	pos.y=(ScreenP.y-sy*2)/sy;
	return pos;
}
void hideCursor(){//隐藏光标 
	CONSOLE_CURSOR_INFO cursor_info1={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info1);
} 
void gotoxy(int x,int y){//移动光标
	if(x<0||x>MAX_SCREEN_LENGTH-1||y<0||y>MAX_SCREEN_WIDTH-1) return;
	COORD pos={short(x),short(y)};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
position_2D GetConsoleCursor(){
	position_2D coordScreen={0,0}; //光标位置
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi)){
		coordScreen.x=csbi.dwCursorPosition.X;
		coordScreen.y=csbi.dwCursorPosition.Y;
	}
	return coordScreen; //光标位置
}
bool pos_in_game_map(position_2D pos){
	return whole_screen.contain(pos)
	&&!vital_signs_area.contain(pos)&&!item_area.contain(pos)&&!weapon_area.contain(pos);
}
void SLEEP(int x){//延时（单位：毫秒） 
	int time_now=clock();
	while(clock()-time_now<x); 
}
LARGE_INTEGER nbegin_time,nend_time,nFreq;
void init_timer(){//初始化 
    QueryPerformanceFrequency(&nFreq); 
}
void start_timer(){//计时开始（仅调用一次） 
    QueryPerformanceCounter(&nbegin_time);
} 
void read_timer(){//计时器读取（不停止计时）
	logMessage("read_timer()",2); 
    QueryPerformanceCounter(&nend_time);
    now_timer=(double)(nend_time.QuadPart-nbegin_time.QuadPart)/(double)nFreq.QuadPart*1000;//单位：毫秒 
}
void CLEAR(){
	cout.flush();
	SetConsoleTextAttribute(hout,0x07);
	system("cls");
	SetConsoleTextAttribute(hout,0x07);
}
void RGB_init(){
	DWORD dwMode=0;
	GetConsoleMode(hout,&dwMode);
	dwMode|=0x0004;
	SetConsoleMode(hout,dwMode);
}
RGB_color code_to_RGB(double light,double hue,double vague){
	/*hsv模式
	hue：色度0~360 
	light：自定义亮度（>0：饱和度 <0：亮度）-100~100
	vague：自定义模糊值 0.00~1.00 
	*/
	double l=light/100.0,s=1.0,v=1.0,r=0,g=0,b=0;
	if(light>0) s=1.0-l;
	else v=1.0+l;
	s=max(0.0,s-vague);//s=max(0.0,s-0.5);模糊效果测试 
	//设置hsv 3个量 
	int h=floor(hue/60.0);
	double f=hue/60.0-h,p=v*(1.0-s),q=v*(1.0-f*s),t=v*(1.0-(1.0-f)*s);
	switch(h){
		case 0:r=v,g=t,b=p;
			break;
		case 1:r=q,g=v,b=p;
			break;
		case 2:r=p,g=v,b=t;
			break;
		case 3:r=p,g=q,b=v;
			break;
		case 4:r=t,g=p,b=v;
			break;
		case 5:r=v,g=p,b=q;
			break;
		case 6:r=g=b=v;
			break;
	}
	r*=255;g*=255;b*=255;
	return (RGB_color){int(r),int(g),int(b)};//rgb取整 
}
void limit_int(int &a,int l,int r);
void limit_double(double &a,double l,double r);
void RGB_brightness(double (&ret)[3],double col[3],double x){//输入double[3]、int，输出&double[3]（->ret） 
//x：亮度（brightness）double类型方便计算 
	x=1.0+x/100.0;
	//e.g. -20->80% 20->120% 
	ret[0]=col[0]*x;
	ret[1]=col[1]*x;
	ret[2]=col[2]*x; 
	//直接按百分比计算 
	limit_double(ret[0],0,1);
	limit_double(ret[1],0,1);
	limit_double(ret[2],0,1);
	//防止越界
	//注意vague范围[0,1] 
}
void set_text_color(RGB_color back,RGB_color forw);
void set_RGBcolor(int light1,int hue1,int light2,int hue2){
	limit_int(light1,-100,100);
	limit_int(light2,-100,100);
	RGB_color back,forw;
	back=code_to_RGB(light1,hue1,0);
	back_now=MP(light1,hue1);
	forw=code_to_RGB(light2,hue2,0);
	forw_now=MP(light2,hue2);
	set_text_color(back,forw);
	//if(back_now!=MP(light1,hue1)){
	//}
	//if(forw_now!=MP(light2,hue2)){
	//}
}
RGB_color mix_color(RGB_color colA,RGB_color colB,double (&rate)[3]){
	//col=colA*(1-rate)+colB*rate
	//rate:R/G/B 
	RGB_color col;
	col.r=(1.0-rate[0])*colA.r+rate[0]*colB.r;
	col.g=(1.0-rate[1])*colA.g+rate[1]*colB.g;
	col.b=(1.0-rate[2])*colA.b+rate[2]*colB.b;
	return col;
}
void set_RGBcolor_vague(int light1,int hue1,int light2,int hue2,double (&vague)[3]){//带有模糊效果 
	//vague背景前景共用 ->前景、背景色的混合程度，与模糊效果的颜色的混合程度 
	//(light3,hue3)表示模糊效果的颜色 ,int light3,int hue3
	//vague:R/G/B 
	limit_int(light1,-100,100);
	limit_int(light2,-100,100);
	for(int i=0;i<3;i++) limit_double(vague[i],0,1);
	
	back_now=MP(light1,hue1);//
	forw_now=MP(light2,hue2);//
	
	RGB_color back,forw;
	/*
	back=code_to_RGB(light1,hue1,0);
	forw=code_to_RGB(light2,hue2,0);*/
	double separate_vague=max(vague[0],max(vague[1],vague[2]));
	back=code_to_RGB(light1,hue1,separate_vague);
	forw=code_to_RGB(light2,hue2,separate_vague);
	//背景、前景色分别单独模糊，以最大值计算 
	
	RGB_color back_forw;
	back_forw.r=back.r*0.9+forw.r*0.1;
	back_forw.g=back.g*0.9+forw.g*0.1;
	back_forw.b=back.b*0.9+forw.b*0.1;
	//vague=1的前景、背景混色 
	back=mix_color(back,back_forw,vague);
	forw=mix_color(forw,back_forw,vague);
	//back.r=(1-vague)*back.r+vague*r;back.g=(1-vague)*back.g+vague*g;back.b=(1-vague)*back.b+vague*b;
	//forw.r=(1-vague)*forw.r+vague*r;forw.g=(1-vague)*forw.g+vague*g;forw.b=(1-vague)*forw.b+vague*b;
	//背景前景色按照vague混一下 
	
	//RGB_color vague_color=code_to_RGB(light3,hue3,0);//模糊叠加的颜色（不要填vague参数！） 
	RGB_color vague_color=code_to_RGB(0,360,0);//模糊叠加白色
	//最终效果由vague[3]决定 
	back=mix_color(back,vague_color,vague);
	forw=mix_color(forw,vague_color,vague);
	
	set_text_color(back,forw);
	//if(back_now!=MP(light1,hue1)){
	//}
	//if(forw_now!=MP(light2,hue2)){
	//}
}
void wait_until(int key){
	while(1){
		if(_kbhit()){
			int c=_getch();
			if(c==key) return;
		}
	}
}
void MUSIC(const char name[],int n){//控制播放音乐
//n代表模式，0为停止播放，1为播放一次，2为重复播放
	return;//全部静音 
	char File[100],path[100]="./音频/";
	if(n==1||n==2) strcpy(File,"play ");
	else if(n==0) strcpy(File,"close ");
	strcat(path,name);
	strcat(File,path);
	if(n==2) strcat(File," repeat");
	mciSendString(File,NULL,0,NULL);
}
void init_dsu(int num){
	for(int i=1;i<=num;i++) fa_dsu[i]=i;
}
int find_dsu(int x){
	if(fa_dsu[x]==x) return x;
	return fa_dsu[x]=find_dsu(fa_dsu[x]); 
} 
void unit_dsu(int x,int y){
	int u=find_dsu(x),v=find_dsu(y);
	if(u==v) return;
	if(rand()%2) fa_dsu[u]=v;
	else fa_dsu[v]=u;
}
int cnt_dsu(int num){
	int cnt=0;
	for(int i=1;i<=num;i++)
		if(fa_dsu[i]==i) cnt++;
	return cnt;
}
bool pos_in_area(int posx,int posy,int areax,int areay,int areal,int areaw){//判断坐标是否在指定范围内
	//areal 范围长 areaw 范围宽 
	return posx>=areax&&posx<=areax+areal-1&&posy>=areay&&posy<=areay+areaw-1;
}
bool pos_in_area2(int posx,int posy,int areax1,int areay1,int areax2,int areay2,int kind=1){//判断坐标是否在指定范围内
	//areal 范围长 areaw 范围宽 
	//kind：1闭2开 
	if(kind==1) return posx>=areax1&&posx<=areax2&&posy>=areay1&&posy<=areay2;
	if(kind==2) return posx>areax1&&posx<areax2&&posy>areay1&&posy<areay2;
	return false;
}
position_2D position_3Dto2D(position_3D pos){
	return (position_2D){pos.x,pos.y};
} 
position_3D position_2Dto3D(position_2D pos,int z){
	return (position_3D){pos.x,pos.y,z};
}
position_2D position_2Dtoscr(position_2D pos){
	return (position_2D){(pos.x-screen_center.x)*2+MAX_SCREEN_LENGTH/2,(pos.y-screen_center.y)+MAX_SCREEN_WIDTH/2};
} 
position_2D position_3Dtoscr(position_3D pos){
	return (position_2D){(pos.x-screen_center.x)*2+MAX_SCREEN_LENGTH/2,(pos.y-screen_center.y)+MAX_SCREEN_WIDTH/2};
} 
position_2D position_scrto2D(position_2D pos){
	return (position_2D){(pos.x-MAX_SCREEN_LENGTH/2)/2+screen_center.x,pos.y-MAX_SCREEN_WIDTH/2+screen_center.y};
}
position_3D position_scrto3D(position_2D pos,int z){
	pos.x=pos.x/2*2;//转化成偶数 
	return (position_3D){(pos.x-MAX_SCREEN_LENGTH/2)/2+screen_center.x,pos.y-MAX_SCREEN_WIDTH/2+screen_center.y,z};
}
//三维、二维和屏幕地图显示坐标互相转换 
direction ptp(position_3D a,position_3D b){//b->a的方向 
	direction ret;
	if(a.x>b.x) ret.d2=1;//右
	else if(a.x<b.x) ret.d2=3;//左
	else ret.d2=-1;
	if(a.y<b.y) ret.d1=0;//上
	else if(a.y>b.y) ret.d1=2;//下
	else ret.d1=-1;
	/*
	gotoxy();
	set_RGBcolor(-100,0,0,0);
	cout<<"direction "<<ret.d1<<","<<ret.d2<<endl;*/
	return ret; 
}
void dtp_error(int &dir,int d,string func,int id=-1){ 
	if(dir<0||dir>=d){
		gotoxy();
		set_RGBcolor(-100,0,0,0);
		cout<<func<<": dtp error["<<id<<"]->"<<dir<<" d="<<d<<endl;
		dir=0;//改掉 
	}
}
position_2D dtp2(position_2D pos,int dir,int d){//在pos位置的d方向是什么位置 
	dtp_error(dir,d,"dtp2"); 
	switch(d){
		case 4:return (position_2D){pos.x+dx4[dir],pos.y+dy4[dir]};
		case 8:return (position_2D){pos.x+dx8[dir],pos.y+dy8[dir]};
		default:return (position_2D){0,0};
	}
}
position_3D dtp3(position_3D pos,int dir,int d){//在pos位置的d方向是什么位置 
	dtp_error(dir,d,"dtp3"); 
	switch(d){
		case 4:return (position_3D){pos.x+dx4[dir],pos.y+dy4[dir],pos.z};
		case 8:return (position_3D){pos.x+dx8[dir],pos.y+dy8[dir],pos.z};
		default:return (position_3D){0,0,0};
	}
}
int turn(int dir,int op,int d=4,int id=-1){//给定当前方向（d）和一个操作（op）（TURN_RIGHT,TURN_BACK,TURN_LEFT）
	dtp_error(dir,d,"turn",id); 
	if(d==4){
		switch(op){
			case TURN_RIGHT:return (dir+1)%d;
			case TURN_BACK:return (dir+2)%d;
			case TURN_LEFT:return (dir+3)%d;
		}
	}
	else if(d==8){
		switch(op){
			case TURN_RIGHT:return (dir+2)%d;
			case TURN_BACK:return (dir+4)%d;
			case TURN_LEFT:return (dir+6)%d;
		}
	}
	return dir;
}
int atd(int angle){
	int a2=angle%90;
	int d1=(angle/90+1)%4,d2=(d1+1)%4;//d1={270~359->0 0~89->1 90~179->2 180~269->3}
	if(a2>45) return d2;
	return d1;
}
int fatd(int angle){//返回值与atd相反 
	int a2=angle%90;
	int d1=(angle/90+1)%4,d2=(d1+1)%4;//d1={270~359->0 0~89->1 90~179->2 180~269->3} × 
	if(a2>45) return d1;
	return d2;
}
bool cmpa(int a,int b){//角度小于 
	return (a-b+360)%360>180;
} 
int sub_angle(int a,int b){//a、b之间的最小夹角（≤180）
	return min((a-b+360)%360,(b-a+360)%360);
} 
int calc_angle(position_3D a,position_3D b){//a->b计算方向角（int） 
	position_3D c=b;c.x-=a.x;c.y-=a.y;
	int angle=(c.x==0?90:atan(1.0*abs(c.y)/abs(c.x))/PI*180);//C++三角函数使用弧度制 
	//cout<<abs(c.y)<<"/"<<abs(c.x)<<"->"<<angle<<"\n";
	if(c.x<0){
		if(c.y>0) angle=180-angle;
		else angle+=180;
	}
	else if(c.y<0) angle=360-angle;
	return angle;
}
int calc_angle2(double x,double y){//Δx、Δy计算方向角 
	int angle=(x==0?90:atan(1.0*abs(y)/abs(x))/PI*180.0);//C++三角函数使用弧度制 
	//cout<<abs(c.y)<<"/"<<abs(c.x)<<"->"<<angle<<"\n";
	if(x<0){
		if(y>0) angle=180-angle;
		else angle+=180;
	}
	else if(y<0) angle=360-angle;
	return angle;
}
double MAP::mass(){
	double m=0;
	switch(player_enemy){
		case SPIDER:
			m+=4; 
			if(emy.id>=0&&emy.id<spiders.size()&&spiders[emy.id].kind) m+=4;
			break;
		case GHOST:
			m+=2.5;
			break;
		case PLAYER:
			m+=2;
			break;
		case BUG:
			m+=1;
			break;
	}
	if(things.mvb.exist)
		switch(things.mvb.kind){
			case BOX:
				m+=8;
				break;
			case DESK:
				m+=4;
				break;
			case CHAIR:
				m+=2;
				break;
			case BALL:
				m+=0.67;
				break;
		}
	if(m<0.1) m+=0.1;
	return m;
}
bool wall_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==WALL;
}
bool space_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==SPACE;
}
bool exit_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==EXIT;
}
bool upstair_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==UPSTAIR;
}
bool downstair_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==DOWNSTAIR;
}
bool stair_here(position_3D u){
	return game_map[u.x][u.y][u.z].maze==UPSTAIR||game_map[u.x][u.y][u.z].maze==DOWNSTAIR;
}
bool body_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	return POS.emy.dead&&POS.emy.body_disapp>game_time;
}
bool player_here(position_3D u){
	return player1.pos==u;
}
bool bug_here(position_3D u){
	//try{
	//	if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("数组越界");
		MAP &POS=game_map[u.x][u.y][u.z];
		int id=POS.emy.id;
		if(id<0||id>=bugs.size()){
			if(POS.player_enemy==BUG) POS.player_enemy=NOBODY;
			return 0;
		}
	//	if(id<0||id>=bugs.size()) throw std::out_of_range("数组越界");
		bug &bg=bugs[id];
		if(POS.player_enemy==BUG&&bg.pos!=u) POS.player_enemy=NOBODY;
		if(POS.player_enemy!=BUG&&bg.pos==u) POS.player_enemy=BUG;
		return bg.pos==u;
	//}
	//catch(const std::out_of_range &e){
    //    std::cerr << "异常发生: " << e.what() << std::endl;
	//}
	//以生物结构体中的坐标为准 
}
bool bug_nest_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.nst.exist;
}
bool spider_body_here(position_3D u){//蜘蛛本体 
	//try{
	//	if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("数组越界");
		MAP &POS=game_map[u.x][u.y][u.z];
		int id=POS.emy.id;
		if(id<0||id>=spiders.size()){
			if(POS.player_enemy==SPIDER) POS.player_enemy=NOBODY;
			return 0;
		}
	//	if(id<0||id>=spiders.size()) throw std::out_of_range("数组越界");
		spider &sr=spiders[id];
		if(POS.player_enemy==SPIDER&&sr.pos!=u) POS.player_enemy=NOBODY;
		if(POS.player_enemy!=SPIDER&&sr.pos==u) POS.player_enemy=SPIDER;
		return sr.pos==u;
	//}
	//catch(const std::out_of_range &e){
    //    std::cerr << "异常发生: " << e.what() << std::endl;
	//}
	//以生物结构体中的坐标为准 
}
bool hiden_door_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.hdr.exist;
} 
bool check_leg(position_3D u,position_3D v){//判断一个蜘蛛附肢是否穿墙角了 
	if(u.x==v.x||u.y==v.y) return true;//四方向一定没问题
	position_3D u2=u,v2=v;//两对角位置的相邻两格 
	u2.y=v.y;v2.y=u.y;//u2:(ux,vy) v2:(vx,uy)
	if(wall_here(u2)&&wall_here(v2)) return false;
	return true;
}
PSB str_spider_leg(position_3D u){
//u如果有蜘蛛附肢，返回其字符；否则返回"" 
	try{
		PSB none=MP("",0);
		if(wall_here(u)||hiden_door_here(u)) return none;//墙壁不显示蜘蛛附肢 
		if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("数组越界 xyz");
		MAP &POS=game_map[u.x][u.y][u.z];
		spider_leg &slg=POS.things.slg;
		if(slg.num<=0) return none;//没有就不浪费时间了 
		if(slg.id>=0&&slg.id<spiders.size()){//有蜘蛛编号信息 
			spider &sr=spiders[slg.id];
			position_3D v=sr.pos;
			int ix=1+u.x-v.x,iy=1+u.y-v.y;//在spider_image中的坐标
			if(!pos_in_area2(ix,iy,0,0,2,2)||!check_leg(u,v)||sr.kind>1||sr.kind<0||sr.d>=4||sr.d<0) return none;//出界或穿墙 
			if(sr.kind>1||sr.kind<0||iy<0||iy>2||ix<0||ix>2||sr.d>=4||sr.d<0) throw std::out_of_range("数组越界 spider_image");
			return MP(spider_image[sr.kind][sr.d][iy][ix],sr.kind);//xy互换（屏幕显示和数组排列是xy轴互换的） 
		}
		string s="";
		for(int i=0;i<8;i++){
			position_3D v=dtp3(u,i,8);
			if(!pos_in_area2(v.x,v.y,1,1,length,width)) continue;//防止出界 
			MAP &NPOS=game_map[v.x][v.y][v.z];
			if(NPOS.emy.id>=0&&NPOS.emy.id<=spiders.size()&&spider_body_here(v)&&check_leg(u,v)){//找到蜘蛛 
				int id=NPOS.emy.id;
				spider &sr=spiders[id];
				int j=turn(i,TURN_BACK,8,1);//这条附肢在虫子哪个方向
				int ix=1+dx8[j],iy=1+dy8[j];//在spider_image中的坐标
				if(!pos_in_area2(ix,iy,0,0,2,2)||!check_leg(u,v)||sr.kind>1||sr.kind<0||sr.d>=4||sr.d<0) return none;//出界或穿墙 
				if(sr.kind>1||sr.kind<0||iy<0||iy>2||ix<0||ix>2||sr.d>=4||sr.d<0) throw std::out_of_range("数组越界 spider_image");
				s=spider_image[sr.kind][sr.d][iy][ix];//xy互换（屏幕显示和数组排列是xy轴互换的） 
				POS.things.slg.id=id;//下次就不用再找了 
				if(sr.kind&&s!="") return MP(s,1);//防止B型蜘蛛前部凹陷覆盖其他蜘蛛的附肢 
			}
		}
		return MP(s,0); 
	}
	catch(const std::out_of_range &e){
        std::cerr << "异常发生: " << e.what() << std::endl;
	}
}
bool spider_leg_here(position_3D u){//是否有B型蜘蛛的腿（A型蜘蛛的腿伸在外面只起到装饰作用） 
	PSB ssl=str_spider_leg(u);
	return ssl.first!=""&&ssl.second;
}
bool spider_here(position_3D u){//是否能碰到蜘蛛（AB身体/B腿） 
	return spider_body_here(u)||spider_leg_here(u);
}
bool ghost_here(position_3D u){
	//try{
	//	if(u.x<0||u.y<0||u.z<0) throw std::out_of_range("数组越界");
		MAP &POS=game_map[u.x][u.y][u.z];
		int id=POS.emy.id;
		if(id<0||id>=ghosts.size()){
			if(POS.player_enemy==GHOST) POS.player_enemy=NOBODY;
			return 0;
		}
	//	if(id<0||id>=ghosts.size()) throw std::out_of_range("数组越界");
		ghost &gt=ghosts[id];
		if(POS.player_enemy==GHOST&&gt.pos!=u) POS.player_enemy=NOBODY;
		if(POS.player_enemy!=GHOST&&gt.pos==u) POS.player_enemy=GHOST;
		return gt.pos==u;
	//}
	//catch(const std::out_of_range &e){
    //    std::cerr << "异常发生: " << e.what() << std::endl;
	//}
}
bool ghost_here_a(position_3D u,int att=-1){
	if(!ghost_here(u)) return 0;
	MAP &POS=game_map[u.x][u.y][u.z];
	int id=POS.emy.id;
	if(POS.player_enemy!=GHOST||id<0||id>=ghosts.size()) return false;
	ghost gt=ghosts[id];
	return att==-1||gt.spat.attack==att;
}
bool ghost_here_d(position_3D u,int def=-1){
	if(!ghost_here(u)) return 0;
	MAP &POS=game_map[u.x][u.y][u.z];
	int id=POS.emy.id;
	if(POS.player_enemy!=GHOST||id<0||id>=ghosts.size()) return false;
	ghost gt=ghosts[id];
	return def==-1||gt.spat.defense==def;
}
bool enemy_here(position_3D u){//考虑B型蜘蛛附肢 
	MAP &POS=game_map[u.x][u.y][u.z];
	int k=POS.player_enemy;
	return bug_here(u)||ghost_here(u)||spider_here(u);
}
bool enemy_here2(position_3D u){//不考虑B型蜘蛛附肢 
	MAP &POS=game_map[u.x][u.y][u.z];
	int k=POS.player_enemy;
	return bug_here(u)||ghost_here(u)||spider_body_here(u);
}
bool dead_here(position_3D u){//有尸体 
	MAP &POS=game_map[u.x][u.y][u.z];
	return POS.emy.dead&&POS.emy.body_disapp>game_time;
}
bool nobody_here(position_3D u){//考虑B型蜘蛛附肢 
	return !(player_here(u)||bug_here(u)||spider_here(u)||ghost_here(u));
}
bool nobody_here2(position_3D u){//不考虑B型蜘蛛附肢
	return game_map[u.x][u.y][u.z].player_enemy==NOBODY;
}
bool empty_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.empty();
}
bool noitem_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.noitem();
}
int key_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=KEY) return false;
	return objects[id].key;
}
food food_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=FOO) return food00;
	return objects[id].foods;
}
bool smb_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=SMO) return false;
	return true;
}
see_through_prop ppt_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].type!=PER) return ppt00;
	return objects[id].stp;
}
int weapon_above(position_3D u){
	int id=game_map[u.x][u.y][u.z].things.fir;
	if(id<0||objects[id].nowea()) return 0;
	return objects[id].type;
}
bool door_here(position_3D u,int state=-1){
	return game_map[u.x][u.y][u.z].things.kdr.exist
	&&(state==-1||game_map[u.x][u.y][u.z].things.kdr.state==state);
}
bool key_door_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist;
}
bool locked_door_here(position_3D u){
	return door_here(u,0);
}
bool open_door_here(position_3D u){
	return door_here(u,1);
}
bool closed_door_here(position_3D u){
	return door_here(u,2);
}
bool door1_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR1;
}
bool door2_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR2;
}
bool door3_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR3;
}
bool door4_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.kdr.exist&&game_map[u.x][u.y][u.z].things.kdr.kind==DOOR4;
}
bool (*doorx_here[4])(position_3D)={door1_here,door2_here,door3_here,door4_here};
bool laser_beam_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.lsr.exist;
} 
bool mirror_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.mirrors.exist;
}
int mirror_relect(int md,int side,int dir){//反射方向计算
	int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=md;
	if(side==1){
		if(dir==d3) return d2;
		else if(d2==d3) return d1;
		return -1;
	}
	else{
		if(dir%2==d3) return d2;
		return d1;
	} 
} 
bool normv_here(position_3D u){
	return !game_map[u.x][u.y][u.z].things.mvb.exist;
}
bool box_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.mvb.exist&&THING.mvb.kind==BOX;
}
bool closed_box_here(position_3D u){//全关的箱子 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[0]+MVB.door[1]+MVB.door[2]+MVB.door[3]==0;
}
bool closed_box_here(position_3D u,int d){
	if(d<0||d>4) return true;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[d]==0;
}
bool open_box_here(position_3D u){//全开的箱子 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[0]+MVB.door[1]+MVB.door[2]+MVB.door[3]==4; 
}
bool open_box_here(position_3D u,int d){
	if(d<0||d>4) return true;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return MVB.exist&&MVB.kind==BOX&&MVB.door[d]==1;
}
bool mvb_here(position_3D u,int lock=-1){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.mvb.exist&&(lock==-1||POS.fcmv.lock==lock);
}
bool mvb_through(position_3D u,int dir){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	mirror &MIRRORS=THING.mirrors;
	return !(wall_here(u)||door_here(u,0)||door_here(u,2)||mvb_here(u,1)
	||mirror_here(u)&&mirror_relect(MIRRORS.dir,MIRRORS.side,dir)==-1
	||spider_leg_here(u));
}
bool flying_thing_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	return (mvb_here(u)||nobody_here2(u))&&POS.fcmv.lock==1;
}
bool window_here(position_3D u){
	return game_map[u.x][u.y][u.z].things.windows.exist;
}
bool curtain_here(position_3D u){
	return space_here(u)&&game_map[u.x][u.y][u.z].things.crt.exist;
}
bool nest_here(position_3D u){
	return space_here(u)&&game_map[u.x][u.y][u.z].things.nst.exist;
}
bool food_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.foods.exist();
}
bool smoke_bomb_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.smb.exist;
}
bool ppt_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return THING.ppt.exist;
}
bool divided_here(position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	return wall_here(u)||THING.hdr.exist;
}
int divided_part(position_3D u){//一个墙周围分隔部分的数量 
	int cnt=0;
	init_dsu(4);//初始化 
	for(int i=0;i<4;i++){ 
		int j=turn(i,TURN_LEFT,4,2),k=turn(i,TURN_RIGHT,4,3);//相邻方向 
		position_3D v1=dtp3(u,i,4),v2=dtp3(u,j,4),v3=dtp3(u,k,4);//四方向
		position_3D v4=dtp3(v1,j,4),v5=dtp3(v1,k,4);//对角 
		int a=i+1,b=j+1,c=k+1;//编码 
		if(!divided_here(v1)){
			if(!divided_here(v2)&&!divided_here(v4)) unit_dsu(b,a);//左边连通 
			if(!divided_here(v3)&&!divided_here(v5)) unit_dsu(c,a);//右边连通 
		}
		else cnt++;
	}
	return cnt_dsu(4)-cnt;
}
bool no_mirror_around(position_3D pos){//检查一个位置会不会与镜子相邻或重合
	if(game_map[pos.x][pos.y][pos.z].things.mirrors.exist) return false; 
	for(int i=0;i<4;i++){
		position_3D v=dtp3(pos,i,4);
		if(pos_in_area2(v.x,v.y,1,1,length,width,2)
		&&game_map[v.x][v.y][v.z].things.mirrors.exist) return false;
	}
	return true;
}
bool worth_relecting(position_3D pos){//反射这个位置对玩家是有用的 
	return space_here(pos)||stair_here(pos);
} 
bool in_room(position_3D pos){//位置在某个房间内 
	if(wall_here(pos)) return false;
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT,4,4);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(wall_here(a)) continue;
		if(wall_here(b)){
			i++;
			continue;
		}
		position_3D c=dtp3(a,j,4);//pos的i方向、j方向、i偏j方向的位置
		if(!wall_here(c)) return true; 
	}
	return false;
}
bool in_walls(position_3D pos){//位置在连成一片的墙里（至少2*2大小） 
	//和上面完全相反 
	if(!wall_here(pos)) return false;
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT,4,5);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(!wall_here(a)) continue;
		if(!wall_here(b)){
			i++;
			continue;
		}
		position_3D c=dtp3(a,j,4);//pos的i方向、j方向、i偏j方向的位置
		if(wall_here(c)) return true; 
	}
	return false;
}
bool fog_through(position_3D u,position_3D pos){//雾气可以穿过这里 pos->u
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	int door_d_u=atd(calc_angle(u,pos)),door_d_pos=atd(calc_angle(pos,u));
	return !(wall_here(u)||door_here(u,0)||door_here(u,2)||window_here(u)
	||(u.z==pos.z//注意箱子的判断 
	?closed_box_here(u,door_d_u)||closed_box_here(pos,door_d_pos)
	:box_here(u)||box_here(pos))
	);//只在巢穴内扩散 &&u.z>height
	//墙、门、箱、窗 
}
bool block_light(position_3D u){//处于此位置，位置本身遮挡视野 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return box_here(u)&&!open_box_here(u);
}
bool light_through(position_3D u,int kind=2){//光线可以直接穿过这个位置
//kind=1：激光（可以穿过帘子，但无法穿过B型蜘蛛的腿） 
//kind=2：视线（可以穿过腿吗？） 
//kind=3：B型蜘蛛的视线（可以透过自己的腿看） 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	ghost gt;gt.init(pos000,0,0);
	bool through_ghost=true;//视线能否穿过鬼，没有鬼就为true 
	if(ghost_here(u)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){
		gt=ghosts[POS.emy.id];
		through_ghost=(gt.spat.can_disappear()?gt.spat.disa.kind!=1:1);
	}
	movable &MVB=THING.mvb;
	bool box_state=(box_here(u)&&!open_box_here(u));//关上的箱子 
	bool door_state=((door_here(u,0)||door_here(u,2))&&!THING.kdr.light_through);//关上的不透明门 
	bool maze_state=(space_here(u)||stair_here(u));
	bool curtain_state=(THING.crt.exist&&nobody_here(u)&&!THING.spr.exist&&!THING.bld.exist);
	if(kind==1)
		return !(box_state
		||THING.hdr.exist||door_state)
		&&!spider_leg_here(u)
		&&(maze_state||(THING.windows.exist&&THING.windows.state));
	else if(kind==2)
		return !(box_state
		||THING.hdr.exist||door_state||curtain_state
		)//"网" ||THING.snt.endurance>75
		&&!spider_leg_here(u)
		&&(maze_state||(THING.windows.exist&&THING.windows.state))&&through_ghost;
	else
		return !(box_state
		||THING.hdr.exist||door_state||curtain_state
		)//"网" ||THING.snt.endurance>75
		&&(maze_state||(THING.windows.exist&&THING.windows.state))&&through_ghost;
}
bool light_through2(position_3D u,int d,int kind=2){//光线可以沿d方向（相对u）穿过这个位置
	//calculate_vision专用（四方向） 
//kind=1：激光（可以穿过帘子） 
//kind=2：视线
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	ghost gt;gt.init(pos000,0,0);
	bool through_ghost=true;//视线能否穿过鬼，没有鬼就为true 
	if(ghost_here(u)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){
		gt=ghosts[POS.emy.id];
		through_ghost=(gt.spat.can_disappear()?gt.spat.disa.kind!=1:1);
	}
	movable &MVB=THING.mvb;
	int d2=turn(d,TURN_BACK);//箱门2个对立方向都要判断 
	if(kind==1)
		return !(closed_box_here(u,d)||closed_box_here(u,d2)//关上的箱子 
		||THING.hdr.exist||((door_here(u,0)||door_here(u,2))&&!THING.kdr.light_through))//关上的不透明门 
		&&!spider_leg_here(u)
		&&(space_here(u)||stair_here(u)||(THING.windows.exist&&THING.windows.state));
	else
		return !(closed_box_here(u,d)||closed_box_here(u,d2)//关上的箱子 
		||THING.hdr.exist||((door_here(u,0)||door_here(u,2))&&!THING.kdr.light_through)||(THING.crt.exist&&nobody_here(u)&&!THING.spr.exist)
		)//"网" ||THING.snt.endurance>75
		&&!spider_leg_here(u)
		&&(space_here(u)||stair_here(u)||(THING.windows.exist&&THING.windows.state))&&through_ghost;
}
double light_vague(position_3D u,int col){//此处造成玩家视野的模糊效果的程度（返回值∈0.00~1.00），分RGB 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	double ret=min(100.0,THING.fogs.absorbance[col])/100.0;
	//=THING.fogs.absorbance/100.0;雾  or  =max(0,THING.snt.endurance-50)*1.0/100.0;"丝 网" 
	return max(min(ret,1.0-eps),0.0+eps);//防止越界 
}
bool push_thing(position_3D pos,int dir,int kind);
int spiderB_part_through(position_3D u,int dir,int d){//B型蜘蛛身体某一部分碰撞检测 
//dir:移动四方向 d:腿的八方向/身体（d=8） 
	if(dir>=4||dir<0||d>8||d<0) return false;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	bool tmp=(MVB.exist?MVB.kind!=BOX:1)&&!(door_here(u,0)||door_here(u,2)||THING.hdr.exist||THING.lsr.exist)&&(stair_here(u)||space_here(u));
	if(d<8){
		if(d%2==0){//四方向 
			if(d==dir*2) return true;//正前方随便什么都可以 
			return tmp&&!POS.fcmv.lock
			//&&!THING.spr.existB型蜘蛛腿不能碰矛，但是会被卡住 
			&&!spider_body_here(u);
			//可以从物品上爬过去（箱子、飞的不行，不能穿过隐藏门） 
		}
		else{//斜向（判定会宽松一点） 
			if(!tmp) return -1;//斜向卡住扣分 
			return !POS.fcmv.lock
			&&!THING.lsr.exist//&&(stair_here(u)||space_here(u))
			//&&!THING.spr.exist B型蜘蛛腿不能碰矛，但是会被卡住 
			&&!spider_body_here(u);
			//可以从物品上爬过去（飞的不行） 
		}
	}
	return tmp&&!POS.fcmv.lock
	&&!THING.spr.exist//B型蜘蛛本体不能碰矛 
	&&nobody_here2(u)&&THING.slg.num<=1;//B型蜘蛛要考虑是不是自己的腿
	//可以从物品上爬过去（箱子、飞的不行，不能穿过隐藏门）不能碰到矛 
}
bool spider_through(position_3D u,int d,bool k){//蜘蛛可以穿过
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	bool tmp=nobody_here(u);
	if(k){//B型蜘蛛 
		int cnt=0;//斜向卡住的次数 
		for(int i=0;i<8;i++){//腿的方向 
			if(turn(d*2,TURN_BACK,8,6)==i) continue;//背后的附肢一定会碰到上次的身体（注意d是4方向的） 
			position_3D v=dtp3(u,i,8);
			int spt=spiderB_part_through(v,d,i);
			if(spt==0) return false;//一处不行就都不行 
			if(spt==-1){
				cnt++;
				if(cnt>=2) return false;//斜向不能卡住2次 
			}
		}
		int spt=spiderB_part_through(u,d,8);
		if(spt==0) return false;//一处不行就都不行 
		if(spt==-1){
			cnt++;
			if(cnt>=2) return false;//斜向不能卡住2次 
		}
		return true;
	}
	movable &MVB=THING.mvb;
	return (MVB.exist?MVB.kind!=BOX:1)&&!POS.fcmv.lock&&!THING.spr.exist//蜘蛛可以从物品上爬过去（箱子、飞的不行） 
	&&!(door_here(u,0)||door_here(u,2)||THING.lsr.exist)&&(stair_here(u)||space_here(u))
	&&nobody_here(u);//不能撞到B型蜘蛛附肢上 
} 
bool spider_towards(position_3D u,int d,bool k){//蜘蛛可以向此处移动（不一定真的位移，可能发生物品交互）
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	int door_d=(d==4?0:turn(d,TURN_BACK,4,7));
	return spider_through(u,d,k)
	||(door_here(u,0)||door_here(u,2))&&RAND_BOOL(50)
	||d!=4&&closed_box_here(u,door_d)&&RAND_BOOL(100)//有概率破门 
	||bug_here(u)&&POS.emy.id>=0//吃虫子 
	||ghost_here(u)//打鬼 
	||k&RAND_BOOL(50);//有概率原地转圈 
}
bool ghost_through(position_3D pos,position_3D u,int d,bool att_thr){//鬼可以穿过
	//pos--d-->u 
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	bool normal_route=
		!(THING.hdr.exist||door_here(u,0)||door_here(u,2)||THING.lsr.exist||THING.drt.exist1())
		&&(stair_here(u)||space_here(u))&&nobody_here(u)
		&&!POS.fcmv.lock;
	if(d==-1) return normal_route;//瞬移 
	//if(closed_box_here(pos,d)) return false;
	if(att_thr) return pos_in_area2(u.x,u.y,1,1,length,width,1)&&!POS.fcmv.lock&&nobody_here(u);//穿墙（不包括边缘墙） 
	if(d==4)//上下楼/出入巢穴口特殊处理 
		return !box_here(u)&&normal_route;
	int reverse_d=turn(d,TURN_BACK);
	bool pos_open_box=open_box_here(pos,d);
	bool u_open_box=open_box_here(u,reverse_d);
	bool go_through_box=(box_here(pos)?pos_open_box:true)&&(box_here(u)?u_open_box:true);
	return (MVB.exist?(push_thing(u,d,0)||go_through_box):1)
		&&normal_route;
} 
bool ghost_towards(position_3D pos,position_3D u,int d,bool att_thr){//鬼可以向此处移动（不一定真的位移，可能发生物品交互）
	//pos--d-->u 
	//if(box_here(pos)&&game_map[pos.x][pos.y][pos.z].things.mvb.door[d]==0) return false;
	MAP &POS=game_map[u.x][u.y][u.z];
	thing &THING=POS.things;
	movable &MVB=THING.mvb;
	return ghost_through(pos,u,d,att_thr)
	||closed_box_here(pos,d)
	||(MVB.exist&&!POS.fcmv.lock&&(d<4?1:MVB.kind!=BOX))
	||THING.windows.exist||door_here(u,2)
	||bug_here(u)||spider_body_here(u);//攻击虫子和蜘蛛 
}
int count_around_pos(position_3D pos,int d,bool (*fp)(position_3D),int n=length,int m=width){
	int cnt=0;
	switch(d){
		case 4:
			for(int i=0;i<4;i++){
				position_3D v=dtp3(pos,i,4);
				if(pos_in_area2(v.x,v.y,1,1,n,m)&&fp(v)) cnt++;
			}
			break;
		case 8:
			for(int i=0;i<8;i++){
				position_3D v=dtp3(pos,i,8);
				if(pos_in_area2(v.x,v.y,1,1,n,m)&&fp(v)) cnt++;
			}
			break;
	}
	return cnt;
}
int gcd(int m,int n){//最大公约数
	if(m%n==0) return n;
	else return gcd(n,m%n);//辗转相除法 
}
int lcm(int m,int n){//最小公倍数 
	return m/gcd(m,n)*n;//原数的积=最大公约数*最小公倍数 
} 
void nearest_RATIO(int a,int b,int l){//最接近的范围限制比值 
	if(a==0||b==0){
		cout<<a<<":"<<b;
		return;
	}
	int k1=1000,k2=1,min=k1*b-k2*a;
	for(int i=1;i<=l;i++){
		for(int j=1;j<=l;j++){
			if(abs(i*b-j*a)<min&&i*b>=j*a){
				k1=i;k2=j;
				min=k1*b-k2*a;
			}
		}
	}
	cout<<k1<<":"<<k2;
}
void limit_int(int &a,int l,int r){//限制a在[l,r]范围内 
	a=max(a,l);
	a=min(a,r);
}
void limit_double(double &a,double l,double r){//限制a在[l,r]范围内 
	a=max(a,l);
	a=min(a,r);
}
int rafz(double num){//roundAwayFromZero背向零取整 
    if(num>=0) return ceil(num);
	return floor(num);
}
int MHT_DIST(int x1,int y1,int x2,int y2){//曼哈顿距离 
	return abs(x1-x2)+abs(y1-y2);
}
int MHT_DIST2(int x1,int y1,int z1,int x2,int y2,int z2){//三维曼哈顿距离
	return  abs(x1-x2)+abs(y1-y2)+abs(z1-z2);
}
int MHT_DIST_p3(position_3D u,position_3D v){//曼哈顿距离 
	return abs(u.x-v.x)+abs(u.y-v.y)+abs(u.z-v.z);
}
int NED(int x1,int y1,int x2,int y2){//normal euclidean distance 欧几里得距离
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
int NED2(int x1,int y1,int z1,int x2,int y2,int z2){//normal euclidean distance 欧几里得距离
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
}
double NED_p3(position_3D u,position_3D v){//normal euclidean distance 欧几里得距离
	return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2)+pow(u.z-v.z,2));
}
void CUT_LINE(int length,char x){//分割线 
	for(;length>0;length--){
		cout<<x;		
	}
	cout<<"\n";
}
void PRINT(rectangle area,int x,int y,string a,int times=1,int time=0,bool enter=false){
//自定义输出（重复、延时、自动换行） 
	position_2D pos;
	pos.x=x,pos.y=y;
	for(int i=1;i<=times;i++){
		for(int j=0;j<int(a.size());j++,pos.x++){
			if(pos.x>=0&&pos.y>=0&&(int(a[j])>=0||int(a[j-1]>=0))) gotoxy(pos.x,pos.y);
			if(pos_in_area2(pos.x,pos.y
			,area.upper_left.x,area.upper_left.y,area.lower_right.x,area.lower_right.y,2)){
				cout<<a[j];
				cout.flush();
				SLEEP(time);
			}
		}
		if(enter) cout<<endl,pos.y++,pos.x=x;
	}
	cout.flush();
}
string connect_str(string a,string b,string c="",string d="",string e="",string f="",string g="",string h=""){
	//连接字符串（最多8个） 
	string ret;
	ret+=a;ret+=b;ret+=c;ret+=d;ret+=e;ret+=f;ret+=g;ret+=h;
	return ret;
}
string int_to_str(int x,int y=0){//int整型转化成string字符串（y位，少位用前导0补充，y==0时代表不使用前导0） 
	string s="";string f=(x<0?"-":"");
	if(x==0){
		if(y==0) return "0"; 
		while(y--) s+='0';
		return s;
	}
	x=abs(x);
	while(x){
		s+=char(x%10+'0');
		x/=10;
	}
	reverse(s.begin(),s.end());
	while(y!=0&&int(s.size()+f.size())<y) s='0'+s;
	s=f+s;
	return s;
}
string ll_to_str(ll x,ll y=0){//ll整型转化成string字符串（y位，少位用前导0补充，y==0时代表不使用前导0） 
	string s="";string f=(x<0?"-":"");
	if(x==0){
		if(y==0) return "0"; 
		while(y--) s+='0';
		return s;
	}
	x=abs(x);
	while(x){
		s+=char(x%10+'0');
		x/=10;
	}
	reverse(s.begin(),s.end());
	while(y!=0&&ll(s.size()+f.size())<y) s='0'+s;
	s=f+s;
	return s;
}
string double_to_str(double x,int y=0,int z=0){//double浮点数转化成string字符串（保留y位小数，总共z个字符，少位用前导0补充） 
	if(y>15) y=15;
	bool negative=x<0;string f=(x<0?"-":"");
	if(x<0) x=-x;
	ll a=x*pow(10,y)+0.5,b=a/pow(10,y),c=(b>0?log10(b):0)+1;
	string s=ll_to_str(a,c+y);
	if(c<ll(s.size())) s.insert(c,".");
	while(z!=0&&s.size()+f.size()<z) s='0'+s;
	s=f+s;
	return s;
}
string PII_to_str(PII x){
	int a=x.first,b=x.second;
	return int_to_str(a)+","+int_to_str(b);
} 
string PPII_to_str(PPII x){
	PII a=x.first,b=x.second;
	return "("+PII_to_str(a)+")"+","+"("+PII_to_str(b)+")";
} 
string to_time(int hour,int min,int sec,string k="HH小时MM分钟SS秒",bool leading0=false){
	min+=sec/60;sec%=60;hour+=min/60;min%=60;
	string ret=k,h=int_to_str(hour),m=int_to_str(min),s=int_to_str(sec);
	if(leading0){
		if(h.size()<2) h='0'+h;
		if(m.size()<2) m='0'+m;
		if(s.size()<2) s='0'+s;
	}
	int p1,p2,p3;
	p1=ret.find("HH");
	if(hour!=0) ret.replace(p1,2,h);
	else ret.erase(0,ret.find("MM")-p1);
	p2=ret.find("MM");
	if(min!=0) ret.replace(p2,2,m);
	else ret.erase(p2,ret.find("SS")-p2);
	p3=ret.find("SS");
	if(sec!=0||(hour==0&&min==0)) ret.replace(p3,2,s);
	else ret.erase(p3,ret.size()-p3);
	return ret;
}
string repeat_char(char c,int times){
	string s="";
	if(times<=0) return "";
	while(times--) s+=c;
	return s;
}
string repeat_str(string s,int times){
	string ret="";
	if(times<=0) return "";
	while(times--) ret+=s;
	return ret;
}
string being_name(PII x){//生物名称
	int k=x.first,id=x.second;
	if(id<0&&k!=PLAYER) return "ERROR";//防爆 
	switch(k){
		case PLAYER:return "玩家";
		case BUG:return "虫子"+int_to_str(id)+"号";
		case SPIDER:return "蜘蛛"+int_to_str(id)+"号";
		case GHOST:return "鬼"+int_to_str(id)+"号";
	}
	return "未知生物";
}
string being_name2(int k){//生物名称
	switch(k){
		case PLAYER:return "玩家";
		case BUG:return "虫子";
		case SPIDER:return "蜘蛛";
		case GHOST:return "鬼";
	}
	return "未知生物";
}
string kill_count::detail(int k){
	string ret="";
	switch(k){
		case 0:
			for(int i=1;i<=CREATURES_NUM;i++)
				if(i!=PLAYER) ret+="杀"+being_name2(i)+int_to_str(det[i])+"只 ";
			break;
		default:return "";
	}
	return ret;
}
void formatted_output(int kind,rectangle area,int x,int y,PPII color,string s,int times=1,int time=0,bool enter=false){
//kind=1：正常打印 2：PRINT；color=-1：和上次一样；x=INF：跟在上次后面 
	game_flag["测试专用"]=true; 
	position_2D pos;
	if(x==INF) pos=GetConsoleCursor();
	else pos.x=x,pos.y=y;
	PII back=color.first,forw=color.second;//背景色和前景色 
	if(back.first!=-1) set_RGBcolor(back.first,back.second,forw.first,forw.second);//SetConsoleTextAttribute(hout,color);
	if(kind==1){
		for(int i=0;i<int(s.size());i++,pos.x++){
			if(pos.x>=0&&pos.y>=0&&(int(s[i])>=0||int(s[i-1])>=0)) gotoxy(pos.x,pos.y);
			if(pos_in_area2(pos.x,pos.y
			,area.upper_left.x,area.upper_left.y,area.lower_right.x,area.lower_right.y,2)){
				cout<<s[i];
				cout.flush();
			}
			else break;
		}
	}
	else PRINT(area,pos.x,pos.y,s,times,time,enter);
}
void print_key(int k,PII light=MP(0,360)){//light:灯光亮度 
	switch(k){
		case KEY1:
			set_RGBcolor(light.first,light.second,0,0);//红 SetConsoleTextAttribute(hout,light+0x0c);
			cout<<"1";
			break;
		case KEY2:
			set_RGBcolor(light.first,light.second,0,0);//红 SetConsoleTextAttribute(hout,light+0x0c);
			cout<<"2";
			break;
		case KEY3:
			set_RGBcolor(light.first,light.second,-100,360);//黑 SetConsoleTextAttribute(hout,light+0x00);
			cout<<"3";
			break;
		case KEY4:
			set_RGBcolor(light.first,light.second,-100,360);//黑 SetConsoleTextAttribute(hout,light+0x00);
			cout<<"4";
			break;
	}
	cout<<"="; 
}
void print_food(int kind,int effect){
	switch(effect){
		case 1:set_RGBcolor(0,360,-20,60);//白深黄 SetConsoleTextAttribute(hout,0xf6);
			break;
		case 2:set_RGBcolor(0,360,-20,300);//白深紫 SetConsoleTextAttribute(hout,0xf5);
			break;
		case 3:set_RGBcolor(0,360,0,240);//白蓝 SetConsoleTextAttribute(hout,0xf9);
			break;
	}
	if(kind==ADDL) cout<<"v+"; 
	else cout<<"回";
}
void print_smk(){
	set_RGBcolor(0,360,-50,360);
	cout<<"烟";
}
void print_ppt(int kind,int time){
	switch(kind){
		case 1:set_RGBcolor(0,360,0,240);//蓝 
			break;
		case 2:set_RGBcolor(0,360,-20,300);//深紫 
			break;
		case 3:set_RGBcolor(0,360,-20,60);//深黄 
			break;
	}
	cout<<int_to_str(time/1000,2); 
}
void print_laser_gun(){
	set_RGBcolor(0,360,0,180);//青
	cout<<"激";
}
void print_dart(int x){
	set_RGBcolor(0,360,0,240);//蓝
	if(x%2) cout<<"× ";
	else cout<<"十"; 
}
void print_spear(){
	set_RGBcolor(0,360,-20,60);//深黄 
	cout<<"矛";
}
void print_dagger(){
	set_RGBcolor(0,360,-40,360);//银 
	cout<<"匕";
}
void print_sword(){
	set_RGBcolor(0,360,-40,360);//银 
	cout<<"剑";
}
void print_blade(){
	set_RGBcolor(0,360,-20,360);//银 
	cout<<"刀";
}
void print_space(){
	set_RGBcolor(0,360,0,360);//白白 SetConsoleTextAttribute(hout,0xff);
	cout<<"  ";
}
string item::item_name(int sn){//保证返回值长度>=6 
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return "无    "; 
	int id=v[sn];
	if(id<0) return "      ";
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return "钥匙"+int_to_str(ob.key)+" "; 
		case FOO:
			if(ob.foods.kind==ADDS) return "生命↑"+int_to_str(ob.foods.effect)+"级";
			return "体力↑"+int_to_str(ob.foods.effect)+"级";
		case SMO:return "烟雾弹";
		case PER:return "透视道具";
		case LAS:return "激光枪"; 
		case DAR:return "飞镖"; 
		case SPE:return "长矛"; 
		case DAG:return "匕首";
		case SWO:return "短剑"; 
		case BLA:return "长刀"; 
		/*
		case BX:return "箱子  ";
		case BL:return "木桶  ";
		case TT:return "TNT   ";
		case CE:return "蜡烛  ";*/
	}
	return "ERROR ";
}
/*
int item::item_num(int sn){
	item &items=player1.items;
	vector<int> &v=items.item_lab;
	if(sn<0||sn>=v.size()) return 0; 
	int id=v[sn];
	if(id<0) return 0;
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return ITEM.keys.door_keys[k-K1+KEY1-1]; 
		case FOO:
			return ITEM.foods.food_cnt[ob.foods.kind-ADDS][ob.foods.effect-1];
		case SMO:return ITEM.pp.smb;
	}
	return 0;
}*/
int item::item_endurance(int sn){
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return 0; 
	int id=v[sn];
	if(id<0) return 0;
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return 0; 
		case FOO:return 0; 
		case WCG:return 0;
		case SMO:return 0; 
		case PER:return 0;  
		case LAS:return 0; 
		case DAR:return 0;
		case SPE:return ob.sprE; 
		case DAG:return ob.daggerE;
		case SWO:return ob.swordE;
		case BLA:return ob.bladeE;
	}
	return 0;
}
string item::item_method(int sn){
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return "无"; 
	int id=v[sn];
	if(id<0) return "无";
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:return "鼠标点击门"; 
		case FOO:return "无"; 
		case WCG:return "无"; 
		case SMO:return "无"; 
		case PER:return "无"; 
		case LAS:return "点击开火"; 
		case DAR:return "点击飞掷"; 
		case SPE:return "旋转突刺"; 
		case DAG:return "近战自动";
		case SWO:return "移动突刺，挥舞砍杀";
		case BLA:return "振刀击退，挥舞砍杀"; 
	}
	return "无"; 
}
void item::print_item(int sn){
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()){
		print_space();//空无一物
		return;
	}
	int id=v[sn];
	if(id<0){
		print_space();//空无一物
		return;
	}
	object &ob=objects[id];
	int k=ob.type;
	switch(k){
		case KEY:
			print_key(ob.key);
			break;
		case FOO:
			print_food(ob.foods.kind,ob.foods.effect);
			break;
		case SMO:
			print_smk();
			break;
		case PER:
			print_ppt(ob.stp.kind,ob.stp.time);
			break;
		case LAS:
			print_laser_gun();
			break;
		case DAR:
			print_dart(sn);
			break;
		case SPE:
			print_spear();
			break; 
		case DAG:
			print_dagger();
			break; 
		case SWO:
			print_sword();
			break; 
		case BLA:
			print_blade();
			break;
		default:
			set_RGBcolor(-100,360,0,0);
			cout<<"ERROR";
	}
}
void item::print1(){//输出标题
	position_2D opos;
	opos.x=item_area.upper_left.x;opos.y=item_area.upper_left.y;//参考点 
	PPII col;
	if(player1.action_kind==CHOOSE_ITEM) col=MMPP(0,360,-100,360);//白底黑字 
	else col=MMPP(-100,360,0,360);//黑底白字 
	formatted_output(1,item_area,opos.x+1,opos.y+1,col,"物");
	formatted_output(1,item_area,opos.x+1,opos.y+2,col,"品");
	formatted_output(1,item_area,opos.x+1,opos.y+3,col,"栏");
}
void item::print2(){//输出第1、2行 
	position_2D opos;
	opos.x=item_area.upper_left.x+3;opos.y=item_area.upper_left.y+1;//参考点
	PPII col;
	vector<int> &v=player1.items.item_lab;
	int sn=item::select_number;
	for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++){//第一行写物品名 
		if(sn==i) col=MMPP(0,360,-100,360);//白底黑字 
		else col=MMPP(-100,360,0,360);//黑底白字 
		formatted_output(1,item_area,opos.x,opos.y,col,item_name(i)+"  ");
		opos.x+=6; 
	}
	formatted_output(2,item_area,opos.x,opos.y,MMPP(-100,360,-100,360)," ",6*(MAX_SIZE_OF_ITEM_LAB-v.size()));
	opos.x=item_area.upper_left.x+3;opos.y++;
	for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++){//第二行写 * 物品示意图 *
		if(sn==i) col=MMPP(0,360,-100,360);//白底黑字 
		else col=MMPP(-100,360,0,360);//黑底白字 
		formatted_output(1,item_area,opos.x,opos.y,col,"＊  ＊");
		gotoxy(opos.x+2,opos.y);
		print_item(i);//到2个*中间输出 
		cout.flush();
		opos.x+=6; 
	}
	formatted_output(2,item_area,opos.x,opos.y,MMPP(-100,360,-100,360)," ",6*(MAX_SIZE_OF_ITEM_LAB-v.size()));
}
void item::print3(){//输出第3行 
	if(item::select_number<0) return;//没选择物品
	int sn=item::select_number;
	position_2D opos;
	opos.x=item_area.upper_left.x+3;opos.y=item_area.upper_left.y+3;//参考点
	PPII col;
	vector<int> &v=player1.items.item_lab;
	if(item_num.size()<MAX_SIZE_OF_ITEM_LAB) return;
	for(int i=0;i<MAX_SIZE_OF_ITEM_LAB;i++){//第三行写 * (耐久度) * 数量 
		if(sn==i) col=MMPP(0,360,-100,360);//白底黑字 
		else col=MMPP(-100,360,0,360);//黑底白字 
		formatted_output(1,item_area,opos.x,opos.y,col,"＊＊"+int_to_str(item_num[i],2));
		opos.x+=6; 
	}
	formatted_output(2,item_area,opos.x,opos.y,MMPP(-100,360,-100,360)," ",6*(MAX_SIZE_OF_ITEM_LAB-v.size()));//统一清空后面的部分 
} 
string weapon_name(int sw){
	switch(sw){
		case LAS:return "激光枪";
		case DAR:return "回旋镖";
		case SPE:return "矛"; 
		case DAG:return "匕首";
		case SWO:return "短剑"; 
		case BLA:return "长刀";
		default:return "NONE";
	}
}
string weapon_method(int sw){
	switch(sw){
		case LAS:return "按下S键发射";
		case DAR:return "按下S键投掷";
		case SPE:return "挥舞突刺"; 
		case DAG:return "近战自动";
		case SWO:return "点击突刺，挥舞砍杀"; 
		case BLA:return "振刀击退，挥舞砍杀"; 
		default:return "ERROR";
	}
}
string weapon_status(int id){
	if(id<0) return "          ";
	object &ob=objects[id];
	switch(ob.type){
		case LAS:return "能量："+int_to_str(ob.lsrE);
		case DAR:return "数量："+int_to_str(object_cnt(id));
		case SPE:return "耐久："+int_to_str(ob.sprE);
		case DAG:return "耐久："+int_to_str(ob.daggerE);
		case SWO:return "耐久："+int_to_str(ob.swordE);
		case BLA:return "耐久："+int_to_str(ob.bladeE);
		default:return "ERROR";
	}
}
void item::wpn_print1(){
	PPII col=MMPP(-100,360,0,360);
	position_2D opos;
	opos.x=weapon_area.upper_left.x;opos.y=weapon_area.upper_left.y;//参考点
	if(player1.action_kind==CHANGE_WPN) col=MMPP(0,360,-100,360);//白底黑字 
	else col=MMPP(-100,360,0,360);//黑底白字 
	formatted_output(1,weapon_area,opos.x+1,opos.y+1,col,"武");
	formatted_output(1,weapon_area,opos.x+1,opos.y+2,col,"器");
	formatted_output(1,weapon_area,opos.x+1,opos.y+3,col,"栏");
	opos.x+=3;opos.y++;
} 
void item::wpn_print2(){
	PPII col=MMPP(-100,360,0,360);
	string name;
	position_2D opos;
	opos.x=weapon_area.upper_left.x+3;opos.y=weapon_area.upper_left.y+1;//参考点
	vector<int> &v=item_lab;
	int x=wpn.primary,id=-1,sw=-1;//x:主武器物品栏编号 sw:主武器type 
	if(x>=0&&x<v.size()){
		id=v[x];
		if(id>=0) sw=objects[id].type;
		switch(sw){
			case LAS:col=MMPP(-100,360,0,180);break; 
			case DAR:col=MMPP(-100,360,0,240);break; 
			case SPE:col=MMPP(-100,360,-20,60);break;
			case DAG:col=MMPP(-95,360,-5,360);break;
			case SWO:col=MMPP(-90,360,-10,360);break;
			case BLA:col=MMPP(-85,360,-15,360);break;
		}
	}
	name=weapon_name(sw);
	formatted_output(1,weapon_area,opos.x,opos.y,MMPP(-100,360,0,360),"主武器：<");
	formatted_output(1,weapon_area,opos.x+9,opos.y,col,name);//有主武器就打印 
	formatted_output(1,weapon_area,opos.x+9+name.size(),opos.y,MMPP(-100,360,0,360),">    ");
	opos.x+=2;opos.y++;
	formatted_output(1,weapon_area,opos.x,opos.y,col,weapon_status(id)+"  ");//主武器的信息 
}
void item::wpn_print3(){
	PPII col=MMPP(-100,360,0,360);
	vector<int> &v=item_lab;
	int x=wpn.secondary,sw=-1;
	if(x>=0&&x<v.size()){
		sw=v[x];
		if(sw>=0) sw=objects[sw].type;
	}
	string name=weapon_name(sw);
	position_2D opos;
	opos.x=weapon_area.upper_left.x+3;opos.y=weapon_area.upper_left.y+3;//参考点
	formatted_output(1,weapon_area,opos.x,opos.y,MMPP(-100,360,0,360),"副武器：<");
	formatted_output(1,weapon_area,opos.x+9,opos.y,col,name);//有副武器就打印 
	formatted_output(1,weapon_area,opos.x+9+name.size(),opos.y,MMPP(-100,360,0,360),">    ");
}
void set_text_color(RGB_color back,RGB_color forw){//设置字体颜色的ANSI转义字符 
	//printf(("\033[48;2;"+int_to_str(back.r)+";"+int_to_str(back.g)+";"+int_to_str(back.b)+"m").c_str());
	//printf(("\033[38;2;"+int_to_str(forw.r)+";"+int_to_str(forw.g)+";"+int_to_str(forw.b)+"m").c_str());
	printf("\033[48;2;%d;%d;%dm",back.r,back.g,back.b);
	printf("\033[38;2;%d;%d;%dm",forw.r,forw.g,forw.b);
}
int interconnection_distance(position_3D s,position_3D e,int max_dis,position_3D no_reach){
	//从s到e的步行距离（BFS） 
	memset(vst,0,sizeof(vst));
	memset(dis,0,sizeof(dis));
	while(!Q.empty()) Q.pop();
	vst[s.x][s.y][s.z]=1;
	dis[s.x][s.y][s.z]=0;
	Q.push(s);
	while(!Q.empty()){
		position_3D u=Q.front();Q.pop();
		if(u==e) return dis[u.x][u.y][u.z];
		if(dis[u.x][u.y][u.z]>max_dis) return -1;
		for(int i=0;i<4;i++){
			position_3D v=dtp3(u,i,4);
			if(v.x>=1&&v.x<=length&&v.y>=1&&v.y<=width&&v.z>=1&&v.z<=height
				&&!(vst[v.x][v.y][v.z]&&v!=no_reach)
				&&!wall_here(v)
				&&!door_here(v)
				){
				if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
				else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
				vst[v.x][v.y][v.z]=1;
				dis[v.x][v.y][v.z]=dis[u.x][u.y][u.z]+1;
				Q.push(v);
			}
		}
	}
	return -1; 
}
bool useful_door(position_2D u,int z,int dis){//判断门是否有用
	position_2D a,b;//门前、门后的位置
	a.x=0;b.x=0;
	for(int i=0;i<4;i++){
		position_2D v=dtp2(u,i,4);
		if(pos_in_area2(v.x,v.y,1,1,length,width,2)&&space_here(position_2Dto3D(v,z))){
			if(a.x==0) a=v;
			else{
				b=v;
				break;
			}
		}
	}
	if(a.x==0||b.x==0) return false;//这个位置不能连上两个空地
	position_3D no_reach={-1,-1,-1};
	int dmaze=game_map[u.x][u.y][z].maze;
	if(game_map[u.x][u.y][z].maze!=WALL) game_map[u.x][u.y][z].maze=WALL;//no_reach=position_2Dto3D(u,z);
	int connect=interconnection_distance((position_3D){a.x,a.y,z},(position_3D){b.x,b.y,z},dis,no_reach);
	game_map[u.x][u.y][z].maze=dmaze;
	if(connect==-1||connect>=dis) return true;
	return false;
}
bool invisible(position_3D pos,position_3D p){//pos看不见p位置 
	for(int i=0;i<4;i++){
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//玩 
		int mn=-1,mx=-1; 
		for(int j=0;j<4;j++){
			position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//标 
			if(u==v) continue;
			int a=calc_angle(u,v);
			if(mn==-1||cmpa(a,mn)) mn=a;
			if(mx==-1||cmpa(mx,a)) mx=a;
		}
		/*
		if(sub_angle(mn,mx)>5||pos.x==p.x||pos.y==p.y)
		//mn=mx,即p位置的可视角度<=10°时，判断为看不见 
		//特殊情况：横平竖直时保证看到 
		*/
		for(int j=mn;j!=(mx+1)%360;j=(j+1)%360)
			if(occlusion[i][j]>0) return false;
	}
	return true; 
}
void mark_lose_sight(int i,int j){//标记此处看不见了（单点修改） 
	if(occlusion[i][j]>0){
		occlusion[i][j]--;
		if(occlusion[i][j]==0) cnt_visible[i]--;
	}
} 
void mark_lose_sight_area(int i,int mn,int mx){//标记此处看不见了（区间修改） 
	for(int j=mn;j!=(mx+1)%360;j=(j+1)%360)
		mark_lose_sight(i,j); 
}
void calc_mark_vague(position_3D p,position_3D pos){//计算p模糊值并记录到game_map 
	//p_vague：p是否造成模糊效果 
	int cnt=0;//计数器 
	double sum[3];
	//p的总模糊效果=avg(vague[0~3][mn~mx])
	for(int i=0;i<4;i++){
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//玩 
		int mn=-1,mx=-1; 
		for(int j=0;j<4;j++){
			position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//标 
			if(u==v) continue;
			int a=calc_angle(u,v);
			if(mn==-1||cmpa(a,mn)) mn=a;
			if(mx==-1||cmpa(mx,a)) mx=a;
		}
		for(int j=mn;j!=(mx+1)%360;j=(j+1)%360){
			for(int k=0;k<3;k++){//RGB
				double p_vague=light_vague(p,k);//R/G/B的模糊度 
				if(p_vague>eps){//这里模糊再标记 
					vague[i][j][k]=1.0-(1.0-vague[i][j][k])*(1.0-p_vague);//计算模糊叠加 
					//if(fabs(vague[i][j]-1.0)<eps)//模糊到完全看不清 
					//	mark_lose_sight(i,j); 
				}
				if(occlusion[i][j]>0) sum[k]+=vague[i][j][k]; 
				//所有能看见的位置都计算模糊值 ?
			}
			if(occlusion[i][j]>0) cnt++;
		}
	}
	double (&ret)[3]=game_map[p.x][p.y][p.z].ist.vague;//p的模糊数组 
	for(int i=0;i<3;i++){//RGB
		if(cnt==0){//防止爆掉 
			ret[i]=1.0;//啥都看不见 
			return;
		}
		double avg=sum[i]/cnt;//R/G/B单独一个颜色的平均模糊值 
		limit_double(avg,0.0,1.0);
		ret[i]=avg;//[0,1]返回p的模糊值 
	}
}
void mark_line_occlusion(position_3D pos,position_3D u,position_3D p,position_3D v1,position_3D v2,int i){
	int a=calc_angle(u,v1),b=calc_angle(u,v2);
	if(u==v1) a=calc_angle(pos,p);
	if(u==v2) b=calc_angle(pos,p);
	//保证贴脸时计算正确 
	if(cmpa(b,a)) swap(a,b);//保证角度排列正确 
	mark_lose_sight_area(i,a,b);
}
void mark_occlusion(position_3D p,position_3D pos,bool kind=1){//p位置遮挡了pos视线
	//kind 1:特判箱子等 0：不特判 
	//看清谁遮挡谁？ 
	for(int i=0;i<4;i++){
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//玩 
		//接下来看p怎么遮挡 
		if(kind&&box_here(p)&&!closed_box_here(p)&&!open_box_here(p)){//有开着的箱子
			//全关：下面那段算 全开：没影响 
			movable &MVB=game_map[p.x][p.y][p.z].things.mvb;
			/*
				       d=0
				x,y o======o x+1,y
				    |      |
				d=3 | 格子 | d=1
				    |      |
			  x,y+1 o======o x+1,y+1
			           d=2
			v1、v2在图中按顺时针排列 你确定是对玩家也是顺时针？ 
			[a,b]即为箱门遮挡的视野方向 
			*/
			//BUG HERE
			if(MVB.door[0]==0){//此方向门关了 
				position_3D v1=p,v2=p;
				v2.x++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
			if(MVB.door[1]==0){//此方向门关了 
				position_3D v1=p,v2=p;
				v1.x++;
				v2.x++;v2.y++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
			if(MVB.door[2]==0){//此方向门关了 
				position_3D v1=p,v2=p;
				v1.x++;v1.y++;
				v2.y++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
			if(MVB.door[3]==0){//此方向门关了 
				position_3D v1=p,v2=p;
				v1.y++;
				mark_line_occlusion(pos,u,p,v1,v2,i);
			}
		}
		else{
			int mn=-1,mx=-1; 
			for(int j=0;j<4;j++){
				position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//标 
				if(u==v) continue;
				int a=calc_angle(u,v);
				if(mn==-1||cmpa(a,mn)) mn=a;
				if(mx==-1||cmpa(mx,a)) mx=a;
			}
			mark_lose_sight_area(i,mn,mx);
		}
	}
}
void prd(){
	gotoxy(0,40);
	for(int j=0;j<360;j++) printf("%4d",j);
	//cout<<"\n";
	for(int i=0;i<4;i++){
		for(int j=0;j<360;j++) printf("%4d",occlusion[i][j]);
		//cout<<"\n";
	}
}
bool rand_error(int max,int min){
	if(max<min){
		formatted_output(1,whole_screen,30,30,MMPP(-100,360,0,0),"随机数参数又写反了！！");
		return true;
	}
	return false;
}
int my_rand(){
	return (rand()<<15)+rand();
}
int RAND(int max,int min){//随机数 
	if(rand_error(max,min)) swap(max,min);
	int num=my_rand()%(max-min+1)+min;
	return num;
}
bool RAND_BOOL(int a){//概率随机布尔值 
	int num=my_rand()%100+1;
	if(num<=a) return 1;
	else return 0;
}
int RAND_ALTO(int max,int min,int a){//群体随机数 
	if(rand_error(max,min)) swap(max,min);
	int k=min;
	for(int i=1;i<=max-min+1;i++){
		if(RAND_BOOL(a)) k++;
	}
	return k;
}
double RAND_DOUBLE(double max,double min){
	if(rand_error(max*1000,min*1000)) swap(max,min);
	int num=my_rand()%int(max*1000-min*1000+1)+min*1000;//min*1000~max*1000
	return num/1000.0;//三位小数精度 
}
void RAND_EXIT_AROUND_GAME_MAP(int cnt,int l=length,int w=width,int h=height){//地图长宽高 
	vector<position_3D> v;//存储可能会被选到的位置
	/* l=5,w=5
	0表示不可能会被选到，1表示有可能会被选到 
		(1,1)==>01110<==(l,1)
				10001
				10001
				10001
    	(1,w)==>01110<==(l,w)
 	当然，每层楼都要算进去
 	此外，选到的位置：至少要和一个非墙格子相邻（不连上一个通道那我怎么逃出去？）*/ 
	for(int z=1;z<=height+h;z++){//找出所有可以设置出口的位置 
		for(int x=2;x<l;x++){
			if(game_map[x][2][z].maze!=WALL)
				v.push_back((position_3D){x,1,z});
			if(game_map[x][w-1][z].maze!=WALL)
				v.push_back((position_3D){x,w,z});
		}
		for(int y=2;y<w;y++){
			if(game_map[2][y][z].maze!=WALL)
				v.push_back((position_3D){1,y,z});
			if(game_map[l-1][y][z].maze!=WALL)
				v.push_back((position_3D){l,y,z});
		}
	}
	for(int i=1;i<=cnt&&v.size()>0;i++){
		int j=RAND(v.size()-1,0);
		position_3D u=v[j];
		swap(v[j],v[v.size()-1]);v.pop_back();
		game_map[u.x][u.y][u.z].maze=EXIT;
		//Q.push(u);vst[u.x][u.y][u.z]=1;//为出口标牌的设置做准备 
		/*
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				FOGS.absorbance=1000000;//初始化，后续慢慢扩散
				FOGS.update=true; 
				pos_fog.push(u);//加入队列 */
	} 
}
int RAND_MIRROR_DIRECTION(position_3D pos){//随机选镜子方向 
	vector<int> v;//存储可能会被选到的镜子朝向 
	/*  				0◤	   1◥	  2◢	 3◣ 
	反射哪个方向的位置  1→2↓ 2↓3← 3←0↑ 0↑1→ 
	*/
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT),k=turn(i,TURN_LEFT);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(worth_relecting(a)&&worth_relecting(b)) v.push_back(k);
	}
	if(v.size()>0) return v[RAND(v.size()-1,0)];
	return -1;
}
position_3D RAND_PLAYER_IN_GAME_MAP(int l=length,int w=width,int h=height){
//在游戏地图里随机选择玩家的位置（空地无人，远离出口，不疑无路） 
	vector<position_3D> v;//存储可能会被选到的位置
	int mx_dis=0;
	for(int z=1;z<=h;z++)
		for(int y=2;y<w;y++)
			for(int x=2;x<l;x++){
				position_3D u;
				u.x=x;u.y=y;u.z=z;
				if(space_here(u)&&nobody_here(u)&&empty_here(u)
				&&count_around_pos(u,4,space_here)+count_around_pos(u,4,stair_here)>=1){
					if(dis_to_exit[x][y][z]>mx_dis){
						v.clear();
						v.push_back(u);
						mx_dis=dis_to_exit[x][y][z];
					}
					else if(dis_to_exit[x][y][z]==mx_dis) v.push_back(u);
				}
			}
	if(v.size()>0) return v[RAND(v.size()-1,0)];
	return (position_3D){length/2,width/2,1};
}
void window::damage(int edc,position_3D u){//砸窗户=减耐久值（+墙变空地）+屏幕更新+光照更新 
	MAP &POS=game_map[u.x][u.y][u.z];
	bool in_sight=POS.ist.player==lst_see_time;
	endurance-=edc;
	if(endurance<=0){
		if(state==0&&POS.update_light()) pos_affect_light.push(u);//窗被砸没更新光照 
		init();
		POS.maze=SPACE;
		if(in_sight) game_flag["物品消失"]=true;
		if(MHT_DIST(u.x,u.y,player1.pos.x,player1.pos.y)<=10&&u.z==player1.pos.z)
			MUSIC("Glass_Breaking.wav",1);//提示音 
	}
	else if(in_sight){
		game_flag["物品损坏"]=true;
		pos_change.insert(u);
	}
}
void spider_net::addedc(int k,position_3D u){
	MAP &POS=game_map[u.x][u.y][u.z];
	int a=endurance;
	endurance=max(0,min(100,endurance+k));
	int b=endurance;
	/*不动态更新了，太卡了 
	if(RAND_BOOL(abs(a*a-b*b)/2)//变化越大，更新的可能性越大 
	&&(a>50||b>50)&&(k>0?POS.ist.pvg()<=95:1)//大于95再更模糊也看不出来了 
	&&game_map[u.x][u.y][u.z].ist.player==lst_see_time) game_flag["蛛网变化"]=true;*/
}
struct cmp_bug{
	bool operator() (int &a,int &b){
		string s1="虫子"+int_to_str(a);
		string s2="虫子"+int_to_str(b);
		return game_timer[s1]>game_timer[s2];
	}
};
priority_queue<int,vector<int>,cmp_bug > Qbug;//虫子队列（编号）
struct cmp_spider{
	bool operator() (int &a,int &b){
		string s1="蜘蛛"+int_to_str(a);
		string s2="蜘蛛"+int_to_str(b);
		return game_timer[s1]>game_timer[s2];
	}
};
priority_queue<int,vector<int>,cmp_spider > Qspider;//蜘蛛队列（编号）
struct cmp_ghost{
	bool operator() (int &a,int &b){
		string s1="鬼"+int_to_str(a);
		string s2="鬼"+int_to_str(b);
		return game_timer[s1]>game_timer[s2];
	}
};
//priority_queue<int,vector<int>,cmp_ghost > Qghost;//鬼队列（编号）
queue<int> Qghost;//鬼队列（编号，不加速） 
void io_init(){
	// 清空游戏日志 
	clearGameLog();
	 
	// 为std::cout设置一个大的缓冲区
    const size_t bufferSize = 1024 * 1024; // 1MB的缓冲区大小
    char buffer[bufferSize];
 
    // 将缓冲区与std::cout关联
    setvbuf(stdout, buffer, _IOFBF, bufferSize);
}
void API_init(){//与WINAPI有关的初始化 
	DWORD mode;GetConsoleMode(hin,&mode);
	mode&=~ENABLE_QUICK_EDIT_MODE;SetConsoleMode(hin,mode);
	h=GetForegroundWindow();
	screen_zoom=get_screen_zoom();
}
//常用函数 
void screen_partition();
void welcome_player();
void ask_player();
void show_insturction(); 
void initial();
void game();
void win();
void lose();
void detail();
void end();
void ask_try_again();
void player_calculate_vision1(int d);
void vision_init(int k,vector<PII > v,vector<position_3D> &ret,position_3D pos);
void calculate_vision2(position_3D pos,int pl_ot,vector<position_3D> &ret,int mx_dis,bool vague);
void player_calculate_vision2();
//函数声明 
int main(){//麒轩出品，必属精品 
	srand(time(0));
	//屏幕输出句柄（用来更改字体颜色）
	io_init();
	API_init(); 
	hideCursor();//隐藏输出光标 
	RGB_init();//RGB颜色初始化 
	init_timer();//初始化计时器 
	start_timer();//开启计时器 
	screen_partition();
	welcome_player();CLEAR();
	while(1){
		ask_player();CLEAR();
		show_insturction();//CLEAR();
		initial();
		//输出初始画面和进行游戏是连贯的，不能清屏 
		game();CLEAR();
		if(game_success) win();
		else lose();
		detail();
		ask_try_again();
		CLEAR();
		if(!start_again){
			end();
			break;
		}
	}
	return 0;
}
//主函数
void screen_partition(){//屏幕分区 
	//注意屏幕左上角为(0,0)，右下角为(MAX_SCREEN_LENGTH-1,MAX_SCREEN_WIDTH-1)
	whole_screen.init(-1,-1,MAX_SCREEN_LENGTH,MAX_SCREEN_WIDTH);//边框在屏幕外 
	vital_signs_area.init(-1,-1,MAX_SCREEN_LENGTH,1);//屏幕顶端一行 
	item_area.init(41,MAX_SCREEN_WIDTH-4,MAX_SCREEN_LENGTH-43,MAX_SCREEN_WIDTH);
	weapon_area.init(MAX_SCREEN_LENGTH-44,MAX_SCREEN_WIDTH-4,MAX_SCREEN_LENGTH,MAX_SCREEN_WIDTH);
	/* 
	int midx=MAX_SCREEN_LENGTH/2,midy=MAX_SCREEN_WIDTH/2;//屏幕上显示的游戏地图中心点（玩家的位置）
	game_map_area.init(max(0,midx-midy*2),0,min(MAX_SCREEN_LENGTH-1,midx+midy*2),MAX_SCREEN_WIDTH-1);
	//以玩家的位置为中心的一个（看起来像）正方形作为游戏地图范围（97*48），上下靠屏幕边界
	vital_signs_area.init(0,0,game_map_area.upper_left.x,MAX_SCREEN_WIDTH-1);
	//玩家信息栏放左边
	item_area.init(game_map_area.lower_right.x,0,MAX_SCREEN_LENGTH-1,MAX_SCREEN_WIDTH-1);
	//玩家物品栏放右边*/
}
void welcome_player(){
	//此前要清屏 
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,360),"欢迎来到秘野迷踪！",1,150);
	formatted_output(2,whole_screen,40,21,MMPP(-100,360,0,360),"作者：wqx",1,150);
	formatted_output(2,whole_screen,40,22,MMPP(-100,360,0,60),"按下回车以开始",1,150);
	wait_until(PRESS_KEY_ENTER);
	formatted_output(2,whole_screen,40,22,MMPP(-100,360,0,180),"游戏加载中......",1,100);
}
	void choose_game_map_from(){
		while(1){
			if(_kbhit()){
				int c=_getch();
				if(c==PRESS_KEY_A){
					game_map_from=RANDOM; 
					//cout<<'a';
					return;
				}
				else if(c==PRESS_KEY_B){
					game_map_from=FILE_MODEL;
					//cout<<'b';
					return;
				}
			}
		} 
	}
void ask_player(){
	//此前要清屏
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,360),"请问您叫什么名字？（",1,100);
	formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,60),"不得包含空格和标点符号",1,100);
	formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,360),"）",1,100);
	cin>>player1.name; 
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,360),"你想要  a.随机生成的地图  or  b.预设地图 ？ ",1,100);
	choose_game_map_from();
	if(game_map_from==RANDOM){//随机生成的地图
		formatted_output(2,whole_screen,40,21,MMPP(-100,360,0,360),"请输入地图长宽高，",1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,60),
		"4<=长<="+int_to_str(MAX_LENGTH)+"，4<=宽<="+int_to_str(MAX_WIDTH)+"，1<=高<="+int_to_str(MAX_HEIGHT),
		1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,360),"（请以",1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,60),"空格",1,100);
		formatted_output(2,whole_screen,INF,0,MMPP(-100,360,0,360),"分隔）：",1,100);
		cin>>length>>width>>height;
	}
}
string game_instruction[26]={
	"一、显示",
	"    屏幕左侧为信息栏，包括生命、体力、模式设置、击杀信息等",
	"    屏幕右侧为物品栏和武器栏",
	"    屏幕中间为游戏区",
	"二、操纵",
	"    1、移动",
	"        WASD键对应前左后右的移动方向，按C键上下楼/进出巢穴口",
	"        移动【鼠标】控制视野方向",
	"    2、使用物品",
	"        按F键打开物品栏，",
	"        【鼠标左键】点击屏幕下侧打开物品栏，点击选中物品可使用",
	"        按TAB键开关手电筒",
	"    3、使用武器",
	"        1）切换（按数字键）",
	"           ①矛 ②激光 ③回旋镖",
	"        2）使用",
	"           矛自动攻击，激光、回旋镖按下【鼠标左键】向【鼠标】方向发射",
	"           补充矛耐久、激光能量的道具显示为+n，回旋镖显示为 十 ×",
	"    4、移动物品",
	"        1）【鼠标】点击物体可选中并拉在身后，移动时自动推动物体",
	"        2）按下空格键可将选中物体或面前物体向【鼠标】方向扔出并对生物造成伤害",
	"           注意：对箱子和石化鬼无效", 
	"三、敌人：虫子、鬼、蜘蛛",
	"    鬼会跟着你，看见它就快跑！", 
	"四、游戏目标：活下来并走到出口E]", 
	"警告：电脑任务繁忙时会有少许卡顿，后果自负" 
};
string player_advice[6]={
	"这是来自作者的忠告：",
	"一、暗处逢生",
	"二、随手关门",
	"三、小心背后",
	"四、注意弹药",
	"勇士，祝你好运"
}; 
void show_insturction(){//展示游戏说明 
	formatted_output(1,whole_screen,35,1,MMPP(-100,360,0,360),"游戏说明");
	for(int i=0;i<26;i++) formatted_output(2,whole_screen,1,i+2,MMPP(-100,360,0,360),game_instruction[i]);
	for(int i=0;i<6;i++) formatted_output(2,whole_screen,90,i+2,MMPP(-100,360,0,180),player_advice[i]);
	formatted_output(2,whole_screen,1,47,MMPP(-100,360,0,0),"按2次空格键继续",1,100);
	wait_until(PRESS_KEY_SPACE);wait_until(PRESS_KEY_SPACE);
	formatted_output(1,whole_screen,1,47,MMPP(-100,360,0,180),"好戏即将开始......");
}
	void all_assigned(){//你确定这些就是全部要初始化的东西了吗 
		logMessage("all_assigned"); 
		API_init();
		pos00.init();pos000.init();
		
		game_end=game_success=game_pause=start_again=false;
		hideCursor();
		for(int z=1;z<=height*2;z++){
			for(int y=1;y<=width;y++){
				for(int x=1;x<=length;x++){
					MAP &POS=game_map[x][y][z];
					POS.init();
				}
			}
		}
		
		objects.clear();
		
		cnt_notWALL=cnt_SPACE=cnt_STAIRS=0;
		memset(stair_exist,0,sizeof(stair_exist));
		memset(pos_in_room,0,sizeof(pos_in_room));
		
		mx_dis_to_player=0;
		for(int i=0;i<(MAX_LENGTH-1)*(MAX_WIDTH-1)*(MAX_HEIGHT*2);i++) pos_dis_to_player_door[i].clear();
		for(int i=0;i<(MAX_LENGTH-1)*(MAX_WIDTH-1)*(MAX_HEIGHT*2);i++) pos_dis_to_player_key[i].clear();
		
		player1.up_down=0;
		while(!pos_in_sight.empty()) pos_in_sight.pop();
		while(!pos_lst_sight.empty()) pos_lst_sight.pop();
		pos_backup.clear();pos_change.clear();
		screen_pos.clear();screen_z.clear();
		
		while(!pos_dead.empty()) pos_dead.pop();
		
		for(int i=0;i<4;i++) cnt_visible[i]=360;
		memset(occlusion,0,sizeof(occlusion));
		memset(vague,0,sizeof(vague));
		while(!pos_vague.empty()) pos_vague.pop();
		
		game_time=lst_see_time=start_time=0;
		game_timer.clear(); 
		game_flag.clear();
		
		bugs.clear();ghosts.clear();spiders.clear();
		pos_in_nest.clear();
		while(!Qbug.empty()) Qbug.pop();
		while(!Qbug_hurt.empty()) Qbug_hurt.pop();
		while(!Qspider.empty()) Qspider.pop();
		while(!Qspider_hurt.empty()) Qspider_hurt.pop();
		while(!ssks.empty()) ssks.pop();
		while(!Qghost.empty()) Qghost.pop();
		while(!Qghost_hurt.empty()) Qghost_hurt.pop();
		
		while(!spears.empty()) spears.pop();
		while(!swords.empty()) swords.pop();
		while(!blades.empty()) blades.pop();
		while(!laser_beams.empty()) laser_beams.pop();
		while(!laser_beam_light.empty()) laser_beam_light.pop();
		while(!darts.empty()) darts.pop();
		while(!mvbs.empty()) mvbs.pop();
		while(!pos_fog.empty()) pos_fog.pop(); 
		
		while(!message_box.empty()) message_box.pop(); 
		while(!pos_affect_light.empty()) pos_affect_light.pop(); 
		while(!lights_update.empty()) lights_update.pop(); 
		memset(light_area,0,sizeof(light_area));
		
		forw_now=back_now=MP(-100,360);
	}
					void pos_being_information(position_3D pos,bool &bgh,bool &srh,bool &gth,bool &plh,bool &bnh
					,bug &bg,spider &sr,ghost &gt,bug_nest &bns,life_injury &lfin){
						MAP &POS=game_map[pos.x][pos.y][pos.z];
						thing &THING=POS.things;
						if(bug_here(pos)&&POS.emy.id>=0&&POS.emy.id<bugs.size()){//有虫子 
							bg=bugs[POS.emy.id];
							lfin=bg.lfin;
							bgh=1;
						}
						else if(spider_body_here(pos)&&POS.emy.id>=0&&POS.emy.id<spiders.size()){//有蜘蛛
							sr=spiders[POS.emy.id];
							lfin=sr.lfin;
							srh=1;
						}
						else if(ghost_here(pos)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){//有鬼 
							gt=ghosts[POS.emy.id];
							lfin=gt.lfin;
							gth=1;
						}
						else if(player_here(pos))//玩家 
							plh=1;
						else if(bug_nest_here(pos)&&THING.nst.id>=0){//巢穴
							bns=bug_nests[THING.nst.id];
							lfin=bns.lfin;
						}
					}
				PII pos_background_color(position_3D pos){//此位置的背景色 
					PII back=MP(0,0); 
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					bool bgh=0,srh=0,gth=0,plh=0,bnh=0;
					bug bg;bg.init(pos000,0);//虫子 
					spider sr;sr.init(pos000,0);//蜘蛛 
					ghost gt;gt.init(pos000,0,0);//鬼
					bug_nest bns;bns.init(pos000);//巢穴 
					life_injury lfin;lfin.init(0);
					pos_being_information(pos,bgh,srh,gth,plh,bnh,bg,sr,gt,bns,lfin);
					special_attribute spat=gt.spat;//鬼的技能 
					PSB ssl=str_spider_leg(pos);
					string sleg=ssl.first;bool slk=ssl.second;
					int door_d=atd(calc_angle(pos,player1.pos));
					if(POS.emy.dead&&POS.emy.body_disapp>game_time)//尸体
						back=MP(0,0);//红
					else if(plh&&(player1.color==3||player1.color==4||player1.color==5))//玩家光圈（提示信息） 
						back=MP(0,240);//蓝
					else if(bgh&&bg.lfin.change==2||srh&&sr.lfin.change==2||gth&&gt.lfin.change==2
					||bnh&&bns.lfin.change==2||plh&&player1.color==2) back=MP(0,0);//红
					else if(bgh&&bg.lfin.change==1||srh&&sr.lfin.change==1||gth&&gt.lfin.change==1
					||bnh&&bns.lfin.change==1||plh&&player1.color==1) back=MP(0,120);//绿 
					//生物/巢穴口（历史遗留BUG）加减血 
					else if(THING.lsr.exist)//激光束光圈 
					//&&(!light_through(dtp3(pos,THING.lsr.laser_beam,4),1)||THING.mirrors.exist||THING.windows.exist||THING.mvb.exist)
						back=MP(0,180);//青 
					else if(mvb_here(pos)&&THING.mvb.kind==BOX){//箱子
						if((!(food_above(pos)==food00)||!(ppt_above(pos)==ppt00))&&!closed_box_here(pos,door_d)) back=MP(-75,60);//防止背景太亮看不清东西 
						else back=MP(-25,60);//棕
					}
					else if(srh&&sr.kind)//B型蜘蛛 
						back=MP(-100,360);//黑 
					else if(sleg!=""&&slk)//B型蜘蛛附肢 
						back=MP(-100,360);//黑 
					else if(THING.hdr.exist)//隐藏门
						back=MP(-15,360);//灰 
					else if(window_here(pos)){//窗户 
						if(THING.windows.state) back=MP(0,180);//青 开 
						else back=MP(-10,360);//浅灰 关 
					}
					else if(curtain_here(pos))//帘子
						back=MP(-20,360);//灰
					else if(door_here(pos)){//门
						if(THING.kdr.state==1) back=MP(-20,120);//深绿 开
						else back=MP(-20,60);//深黄 锁/关 
					}
					else if(exit_here(pos))//出口
						back=MP(0,120);//绿 
					else if(gth&&!(spat.can_disappear()&&spat.disa.kind==2)){//鬼（没有隐身消失） 的光圈（技能） 
						switch(spat.defense){
							case 0:back=MP(-100,360);break;
							case EVADE:back=MP(-20,120);break;
							case ROCK:back=MP(-20,360);break;
							case SHIELD:back=MP(-20,180);break;
						}
						if(spat.can_disappear()&&spat.disa.kind==1)//隐身中 
							back=MP(-10,360);//浅灰 墙 
					}
					else if(wall_here(pos))//墙
						back=MP(-10,360);//浅灰
					else back=MP(0,360);//白（不管你是空地还是楼梯有玩家/虫子） 
					return back; 
				}
				PII pos_forward(position_3D pos){//此位置的前景色 
					PII forw=MP(0,0);
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					bool bgh=0,srh=0,gth=0,plh=0,bnh=0;//这里有什么生物 
					bug bg;bg.init(pos000,0);//虫子 
					spider sr;sr.init(pos000,0);//蜘蛛 
					ghost gt;gt.init(pos000,0,0);//鬼
					bug_nest bns;bns.init(pos000);//巢穴 
					life_injury lfin;lfin.init(0);
					pos_being_information(pos,bgh,srh,gth,plh,bnh,bg,sr,gt,bns,lfin);
					special_attribute spat=gt.spat;
					PSB ssl=str_spider_leg(pos);
					string sleg=ssl.first;bool slk=ssl.second;
					int door_d=atd(calc_angle(pos,player1.pos));
					if(POS.emy.dead&&POS.emy.body_disapp>game_time){//尸体
						forw=MP(0,360);//白
					}
					else if(srh){//蜘蛛本体
						if(THING.snt.endurance>50||sr.kind) forw=MP(25,360);//白
						else forw=MP(-200,360);//黑
					}
					/*
					else if(THING.snt.nowk()>=1000){
						forw=MP(25,360);
						out=int_to_str(THING.snt.nowk()/1000,2);
					}*/
					else if(plh){//玩家
						special_effect &spe=player1.spe;
						if(player1.pull_thing){//提示拉中物品
							forw=MP(0,360);
						}
						else if(player1.color==3){//提示信息 
							forw=MP(0,360);//白
						}
						else if(player1.color==4){
							forw=MP(0,360);//白
						}
						else if(player1.color==5){
							forw=MP(0,360);//白 
						}
						else if(spe.mts.exist()&&player1.vts.lfin.change==2){//中毒
							forw=MP(0,120);//绿
						}
						else if(spe.vtg.exist()){//眩晕 
							forw=MP(0,300);//紫
						}
						else if(spe.bds.exist()){//失明 
							forw=MP(-200,360);//黑
						} 
						else if(spe.cfs.exist()){//迷惑 
							forw=MP(0,60);//黄
						}
						else if(spe.wks.exist()){//虚弱
							forw=MP(-20,360);//灰 
						}
						else if(spe.xry.num>1){//透视
							forw=MP(0,240);//蓝
						}
						else{//正常显示 
							forw=MP(0,240);//蓝
						}
					}
					else if(gth&&!(spat.can_disappear()&&spat.disa.kind==2)&&!closed_box_here(pos,door_d)&&!wall_here(pos)){
					//鬼（没有隐身消失，没有藏在箱子里，没有穿墙） 
						switch(spat.attack){
							case 0:forw=MP(0,360);break;
							case VAMPIRE:forw=MP(0,0);break;
							case DISAPP:forw=MP(0,60);break;
							case THROUGH:forw=MP(0,180);break; 
							case INSTANT:forw=MP(0,300);break;
						}
						if(spat.can_disappear()&&spat.disa.kind==1){//隐身中 
							forw=MP(-80,360);//浅灰 墙 
						}
					}
					else if(bgh&&!closed_box_here(pos,door_d)){//虫（没有藏在箱子里）  
						if(bg.lfin.change!=0) forw=MP(0,360);//白
						else if(THING.snt.exist()) forw=MP(25,360);//白
						else forw=MP(0,0);//红
					}
					else if(sleg!=""&&slk){//B型蜘蛛附肢 
						forw=MP(0,360);//白 
					} 
					else if(mvb_here(pos)
					&&!(box_here(pos)&&THING.mvb.door[door_d]&&(!(food_above(pos)==food00)||smb_above(pos)||!(ppt_above(pos)==ppt00)))
					){//如果不是宝箱（看得见里面的东西） 
						bool select=(player1.items.rmv.select==pos);
						if(select) forw=MP(0,180);//青 被选中 
						else if(THING.snt.exist()) forw=MP(25,360);//白
						switch(THING.mvb.kind){
							case BOX:
								if(!select) forw=MP(0,360);//白 
								break;
							case DESK: 
								if(!select) forw=MP(-25,60);//棕 
								break;
							case CHAIR:
								if(!select) forw=MP(-25,60);//棕
								break;
							case BALL:
								if(!select) forw=MP(-30,360);//深灰 
								break; 
						}
					}
					else if(THING.nst.exist){//巢穴口
						if(bns.lfin.change){
							forw=MP(0,360);//白
						}
						else{
							forw=MP(0,0);//红
						}
					}
					else if(THING.spr.exist){//矛
						int d=THING.spr.d;
						if(THING.nst.exist) forw=MP(0,0);//红
						else forw=MP(-20,60);//深黄 
					}
					else if(THING.swd.exist){//剑 
						forw=MP(-60,360);
					}
					else if(THING.bld.exist){//刀 
						forw=MP(-40,360);
					}
					else if(THING.snt.endurance>50){
						if(bgh) forw=MP(25,0);//红 
						else forw=MP(25,360);//白
						//1~25：＊  26~50：ㄨ  51~75：丝  76~100：网
						int edc=THING.snt.endurance;
					}
					else if(sleg!=""){//A型蜘蛛附肢
						if(THING.snt.endurance>0) forw=MP(50,360);//白
						else forw=MP(-200,360);//黑
					}
					else if(THING.drt.exist()){//回旋镖
						if(THING.nst.exist) forw=MP(0,0);//红
						else forw=MP(0,240);//蓝
					}
					else if(THING.ssk.exist()){//飞行的蜘蛛丝 
						forw=MP(-100,360);//黑 
					}
					else if(THING.snt.endurance>0){//厚一点的蜘蛛网 
						forw=MP(25,360);//白
						//1~25：＊  26~50：ㄨ  51~75：丝  76~100：网
						int edc=THING.snt.endurance;
					}
					else if(door_here(pos,0)){//锁的门
						forw=MP(0,360);//白 
					} 
					else if(door_here(pos,2)){//关的门
						if(plh) forw=MP(0,240);//蓝
						else forw=MP(0,360);//白
					}
					else if(weapon_above(pos)){//有武器
						switch(weapon_above(pos)){
							case LAS:
								forw=MP(-40,180);//青 
								break;
							case DAR:
								forw=MP(0,240);//蓝
								break;
							case SPE:
								forw=MP(-20,60);//深黄 
								break; 
							case DAG:
								forw=MP(-40,360);//银
								break;
							case SWO:
								forw=MP(-40,360);//银
								break;  
							case BLA:
								forw=MP(-20,360);//银
								break; 
						}
					}
					else if(!(food_above(pos)==food00)){//有食物
						food foods=food_above(pos);
						switch(foods.effect){
							case 1:forw=MP(-20,60);//深黄 
								break;
							case 2:forw=MP(-20,300);//深紫 
								break;
							case 3:forw=MP(0,240);//蓝 
								break;
						}
					}
					else if(THING.lsr.exist){//激光
						forw=MP(0,360);
					}
					else if(door_here(pos,1)){//貌似有扇门
						if(plh) forw=MP(0,240);//蓝
						else forw=MP(0,360);//白
					}
					else if(THING.hdr.exist){//隐藏门
						forw=MP(-80,360);//灰
					}
					else if(window_here(pos)){//窗户
						int endurance=THING.windows.endurance,state=THING.windows.state;
						if(state) forw=MP(0,360);//白 开
						else forw=MP(0,180);//青 关
					} 
					else if(curtain_here(pos)){//帘子
						int endurance=THING.crt.endurance;
						forw=MP(-80,360);//深深灰
					}
					/*else if(THING.wee.exist){//有武器能量/耐久度回复
						int num=THING.wee.num,kind=THING.wee.kind;
						switch(kind){
							case 0:forw=MP(0,180);//青 激光能量 
								break;
							case 1:forw=MP(-20,60);//深黄 矛耐久度 
								break;
						}
					}*/
					else if(smb_above(pos)){//有烟雾弹
						forw=MP(-100,360);
					}
					else if(!(ppt_above(pos)==ppt00)){//有透视道具
						see_through_prop ppt=ppt_above(pos);
						int kind=ppt.kind,time=ppt.time;
						switch(kind){
							case 1:forw=MP(0,240);//蓝 
								break;
							case 2:forw=MP(-20,300);//深紫 
								break;
							case 3:forw=MP(-20,60);//深黄 
								break;
						}
					}
					else if(key_above(pos)){//有钥匙 
						forw=MP(0,0);//红 
					}
					else if(THING.lgt.exist){//灯 
						forw=MP(-200,360);//超黑 
					}
					else if(THING.exit_signs.exist){//有指向出口的标牌
						forw=MP(0,120);//绿 
					}
					else if(POS.maze==EXIT){//出口 
						forw=MP(0,360);//白 
					}
					else if(stair_here(pos)){//楼梯 
						forw=MP(-100,360);//黑 
					}
					else if(POS.maze==WALL){//这里是堵墙 
						forw=MP(-80,360);//深深灰 
					}
					else{//这里是空地 
						forw=MP(0,360);//白 
						//forw=MP(-100,360);
						//out=double_to_str(POS.things.fogs.absorbance*100,0,2);//测试 
					}
					return forw; 
				}
				string pos_output(position_3D pos){//此位置的输出内容 
					string out=""; 
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					bool bgh=0,srh=0,gth=0,plh=0,bnh=0;//这里有什么生物 
					bug bg;bg.init(pos000,0);//虫子 
					spider sr;sr.init(pos000,0);//蜘蛛 
					ghost gt;gt.init(pos000,0,0);//鬼
					bug_nest bns;bns.init(pos000);//巢穴 
					life_injury lfin;lfin.init(0);
					pos_being_information(pos,bgh,srh,gth,plh,bnh,bg,sr,gt,bns,lfin);
					special_attribute spat=gt.spat;
					PSB ssl=str_spider_leg(pos);
					string sleg=ssl.first;bool slk=ssl.second;
					int door_d=atd(calc_angle(pos,player1.pos));
					if(POS.emy.dead&&POS.emy.body_disapp>game_time){//尸体
						out="KO"; 
					}
					else if(srh){//蜘蛛本体
						if(sr.kind==1) out="蚃";
						else out="蛛";  
					}
					/*
					else if(THING.snt.nowk()>=1000){
						forw=MP(25,360);
						out=int_to_str(THING.snt.nowk()/1000,2);
					}*/
					else if(plh){//玩家
						special_effect &spe=player1.spe;
						if(player1.pull_thing){//提示拉中物品
							out="拉"; 
						}
						else if(player1.color==3){//提示信息 
							switch(player1.d1){//显示方向 
								case 0:out="↑";
									break;
								case 1:out="→";
									break;
								case 2:out="↓";
									break;
								case 3:out="←";
									break;
							}
							out+=" "; 
						}
						else if(player1.color==4){
							out="御";
						}
						else if(player1.color==5){
							out=player1.flash_word;
						}
						else if(spe.mts.exist()&&player1.vts.lfin.change==2){//中毒
							out="毒"; 
						}
						else if(spe.vtg.exist()){//眩晕 
							out="晕";
						}
						else if(spe.bds.exist()){//失明 
							out="盲"; 
						} 
						else if(spe.cfs.exist()){//迷惑 
							out="迷";
						}
						else if(spe.wks.exist()){//虚弱
							out="虚"; 
						}
						else if(spe.xry.num>1){//透视
							out="＠";
						}
						else{//正常显示 
							out=player1.name.substr(0,2);
						}
					}
					else if(gth&&!(spat.can_disappear()&&spat.disa.kind==2)&&!closed_box_here(pos,door_d)&&!wall_here(pos)){
					//鬼（没有隐身消失，没有藏在箱子里，没有穿墙） 
						if(spat.eva.use) out="魅";
						else if(spat.rck.use) out="魑";
						else if(spat.can_through()) out="魆";//穿墙中 
						else if(spat.can_disappear()&&spat.disa.kind==1){//隐身中 
							out="墙";
						}
						else{
							/*
							隐身：魍 
							穿墙：魆
							瞬移：魉 
							石化：魑
							闪避：魅 */
							if(spat.attack==DISAPP) out="魍";
							else if(spat.attack==THROUGH) out="魆";
							else if(spat.attack==INSTANT) out="魉";
							else if(spat.defense==ROCK) out="魑";
							else if(spat.defense==EVADE) out="魅";
							else out="鬼";
							//out=double_to_str(gt.lfin.life,0,2);
						}
						/**/
						special_effect &spe=gt.spe;
						if(spe.mts.exist()&&gt.lfin.change==2)//中毒
							out="毒"; 
						else if(spe.vtg.exist())//眩晕 
							out="晕";
						else if(spe.bds.exist())//失明 
							out="盲"; 
						else if(spe.wks.exist())//虚弱
							out="虚"; 
						//鬼的特殊效果只影响打印的文字 
						if(lfin.change&&lfin.lst_hurt>=1)
							out=int_to_str(lfin.lst_hurt,2);
					}
					else if(bgh&&!closed_box_here(pos,door_d)){//虫（没有藏在箱子里）  
						out="虫";  
					}
					else if(sleg!=""&&slk){//B型蜘蛛附肢 
						out=sleg;
					} 
					else if(mvb_here(pos)
					&&!(box_here(pos)&&THING.mvb.door[door_d]&&(!(food_above(pos)==food00)||smb_above(pos)||!(ppt_above(pos)==ppt00)))
					){//如果不是宝箱（看得见里面的东西） 
						switch(THING.mvb.kind){
							case BOX:
								if(THING.mvb.door[door_d]) out="[]";//atd(...):玩家看得更清楚的是哪一面
								else out="箱";
								break;
							case DESK: 
								out="桌";
								break;
							case CHAIR:
								out="椅";
								break;
							case BALL:
								out="球";
								break; 
						}
					}
					else if(THING.spr.exist){//矛
						int d=THING.spr.d;
						if(THING.spr.head){
							switch(d){
								case 0:out="↑";
									break;
								case 1:out="↗";
									break;
								case 2:out="→";
									break;
								case 3:out="↘";
									break;
								case 4:out="↓";
									break;
								case 5:out="↙";
									break;
								case 6:out="←";
									break;
								case 7:out="↖";
									break;
							}
							out+=" "; 
						}
						else{
							switch(d){
								case 0:case 4:out="｜";
									break;
								case 2:case 6:out="－";
									break;
								case 1:case 5:out="＼";
									break;
								case 3:case 7:out="／";
									break;
							}
						}
					}
					else if(THING.swd.exist){//剑 
						out="剑";
					}
					else if(THING.bld.exist){//刀 
						if(THING.bld.head) out="刀";
						else out="◆ ";
					}
					else if(THING.snt.endurance>50){
						//1~25：＊  26~50：ㄨ  51~75：丝  76~100：网
						int edc=THING.snt.endurance;
						if(edc>75) out="网";
						else out="丝";
					}
					else if(sleg!=""){//A型蜘蛛附肢
						out=sleg;
					}
					else if(THING.drt.exist()){//回旋镖
						if((pos.x%2)^(pos.y%2)) out="× ";
						else out="十"; 
					}
					else if(THING.ssk.exist()){//飞行的蜘蛛丝 
						out="ss"; 
					}
					else if(THING.snt.endurance>0){
						//1~25：＊  26~50：ㄨ  51~75：丝  76~100：网
						int edc=THING.snt.endurance;
						if(edc>25) out="ㄨ";
						else out="＊";
					}
					else if(door_here(pos,0)){//锁的门
						switch(THING.kdr.kind){
							case DOOR1:out="1";
								break;
							case DOOR2:out="2";
								break;
							case DOOR3:out="3";
								break;
							case DOOR4:out="4";
								break;
						}
						out+="]";
					} 
					else if(door_here(pos,2)){//关的门
						if(THING.kdr.light_through) out=" ]";
						else out="门";
					}
					else if(weapon_above(pos)){//有武器
						switch(weapon_above(pos)){
							case LAS:
								out="激";
								break;
							case DAR:
								if((pos.x%2)^(pos.y%2)) out="× ";
								else out="十"; 
								break;
							case SPE:
								out="矛";
								break; 
							case DAG:
								out="匕";
								break;
							case SWO:
								out="剑";
								break;  
							case BLA:
								out="刀";
								break;  
						}
					}
					else if(!(food_above(pos)==food00)){//有食物
						food foods=food_above(pos);
						if(foods.kind==ADDL) out="v+";
						else out="回";
					}
					else if(THING.nst.exist){//巢穴口
						if(bns.lfin.change){
							out=double_to_str(bns.lfin.life,0,2); 
						}
						else{
							out="巢";
						}
					}
					else if(THING.lsr.exist){//激光
						out="※ ";
					}
					else if(THING.hdr.exist){//隐藏门
						out="墙";//与墙尽量保持一致 
					}
					else if(window_here(pos)){//窗户
						int endurance=THING.windows.endurance,state=THING.windows.state;
						if(endurance==100) out="窗"; 
						else out=int_to_str(endurance,2);
					} 
					else if(curtain_here(pos)){//帘子
						int endurance=THING.crt.endurance;
						if(endurance==100) out="帘";
						else out=int_to_str(endurance,2);
					}
					else if(THING.wee.exist){//有武器能量/耐久度回复
						int num=THING.wee.num,kind=THING.wee.kind;
						out="+"+int_to_str(num);
					}
					else if(smb_above(pos)){//有烟雾弹
						out="烟"; 
					}
					else if(!(ppt_above(pos)==ppt00)){//有透视道具
						see_through_prop ppt=ppt_above(pos);
						int kind=ppt.kind,time=ppt.time;
						out=int_to_str(time/1000,2); 
					}
					else if(key_above(pos)){//有钥匙 
						switch(key_above(pos)){
							case KEY1:
								//forw=MP(0,0);//红 
								out="1=";
								break;
							case KEY2:
								//forw=MP(0,0);//红 
								out="2=";
								break;
							case KEY3:
								//forw=MP(-100,360);//黑 
								out="3=";
								break;
							case KEY4:
								//forw=MP(-100,360);//黑 
								out="4=";
								break;
						}
					}
					else if(THING.lgt.exist){//灯 
						if(THING.lgt.state) out="¤ ";
						else out="灯";
					}
					else if(THING.exit_signs.exist){//有指向出口的标牌
						switch(THING.exit_signs.dir){
							case 0:out="↑";
								break;
							case 1:out="→";
								break;
							case 2:out="↓";
								break;
							case 3:out="←";
								break;
						}
						out+=" "; 
					}
					else if(door_here(pos,1)){//貌似有扇门
						if(THING.kdr.light_through) out=" ]";
						else out="门";
					}
					else if(POS.maze==EXIT){//出口 
						if(pos.x==1||pos.y==1) out="E]";
						else out="[E";
					}
					else if(stair_here(pos)){//楼梯 
						switch(POS.maze){
							case UPSTAIR:
								out="上";
								break;
							case DOWNSTAIR:
								out="下";
								break;
						}
					}
					else if(POS.maze==WALL){//这里是堵墙 
						out="墙";
					}
					else{//这里是空地 
						out="  ";
						//forw=MP(-100,360);
						//out=double_to_str(POS.things.fogs.absorbance*100,0,2);//测试 
					}
					return out; 
				}
				int pos_brightness(position_3D u){//一个位置的实际光照亮度 
					MAP &POS=game_map[u.x][u.y][u.z];
					int B=POS.brightness;
					if(exit_here(u)||u.z!=player1.pos.z){//出口/楼上下限制显示亮度 
						limit_int(B,-25,25);
						return B;
					}
					if(light_through(u,2)||player_here(u)) return POS.brightness;//透光位置或玩家位置 
					int ret=-100;
					for(int i=0;i<4;i++){//不透光位置
						position_3D v=dtp3(u,i,4);
						MAP &NPOS=game_map[v.x][v.y][v.z];
						if(light_through(v,2)&&NPOS.ist.player==lst_see_time||player_here(v))//防止进隐藏门变睁眼瞎 
							ret=max(ret,NPOS.brightness);//周围可以看到的透光位置/玩家位置亮度中的最大值 
					}
					return ret;
				}
			string print_game_map_pos(position_3D pos,int kind){//kind=1：函数内设置光标 2：函数外设置光标 3：不输出内容，只返回编码 
				//（输出并）返回输出内容的编码
				position_2D spos=position_3Dtoscr(pos); 
				int x=pos.x,y=pos.y,z=pos.z,px=spos.x,py=spos.y;//输出坐标计算 
				game_flag["测试专用"]=true; 
				MAP &POS=game_map[x][y][z];
				thing &THING=POS.things;
				int brightness=pos_brightness(pos);//光照强度 
				//brightness=0;//全亮 
				PII back=MP(0,0),forw=MP(0,0);
				string out="";
				int dis=MHT_DIST_p3(player1.pos,pos);
				dim_sight &dst=player1.spe.dst;
				int delta_t=game_time-dst.time;
				bool quick_move=delta_t<dst.last;
				double k=player1.vts.stg.physical_strength/100.0;//体力越低看到的范围越小 
				bool flag=true;//是否打印 
				/*动态模糊 
				if(dis>dst.cpt*k&&quick_move){//较远处模糊显示 
					brightness=-90;
					back=MP(-70,360);forw=MP(-70,360);
					out="  ";
					dst.dim=true;
					flag=false;
				}
				/*
				else if(dis>dst.part*k//中距离处只显示重要信息 
				&&nobody_here(pos)&&!THING.foods.exist()&&!THING.kdr.exist&&!THING.lgt.exist //没有生物、食物、门、灯就不显示
				&&quick_move//快速移动中 
				){
					brightness=-70;
					back=MP(-50,360);forw=MP(-50,360);
					out="  ";
					dst.dim=true;
					flag=true;
				}
				else{
				}*/
				back=pos_background_color(pos);//背景色 
				forw=pos_forward(pos);//前景色
				out=pos_output(pos);//输出内容
				back.first+=brightness;forw.first+=brightness;
				limit_int(back.first,-100,100);
				limit_int(forw.first,-100,100);
				//根据光照强度对亮度做处理
				flag=true;
				double vague=POS.ist.pvg();
				//根据模糊系数更改颜色 
				string code=PII_to_str(back)+","+PII_to_str(forw)+" "+out;//计算编码 
				if(kind==1&&!pos_in_game_map(spos)//光标不在游戏地图范围内 
				||kind==3||!flag)//或不输出 
					return code;
				if(kind==1) gotoxy(px,py);//移动光标 
				double vague_RGB[3];
				RGB_brightness(vague_RGB,POS.ist.vague,POS.brightness);//按照亮度修改一下POS.ist.vague返回给vague_color 
				//set_RGBcolor_vague(back.first,back.second,forw.first,forw.second,vague,brightness,0);//设置颜色 
				//set_RGBcolor_vague(back.first,back.second,forw.first,forw.second,vague,POS.things.fogs.col);//设置颜色
				set_RGBcolor_vague(back.first,back.second,forw.first,forw.second,vague_RGB);//设置颜色
				//测试：雾 
				cout<<out<<endl;
				return code;
			}
		void print_game_map_z(int z){//暂不可用 
			for(int y=1;y<=width;y++){
				for(int x=1;x<=length;x++){
					gotoxy((x-1)*2,y-1+(height*2-z)*width);
					print_game_map_pos((position_3D){x,y,z},2);
					//SLEEP(5);
				}
			}
		}
	void print_game_map(){//暂不可用 
		for(int z=1;z<=height*2;z++) print_game_map_z(z);
	}
			void rand_basic(int sx,int sy,int sz,int a,int b,int c,const int l=length,const int w=width,int h1=1,int h2=height){
			//生成基础迷宫（空地+墙+楼梯+巢穴，一条通路），这个尺寸是指一般游戏区的，不包括巢穴区 
			//a、b、c分别指生成楼梯、地面->地下巢穴口、地下->地面巢穴口的概率 
			//h1~h2:生成的高度范围 
				memset(stair_exist,0,sizeof(stair_exist));
				vector<position_3D> vec;//存储只连了一个非墙位置的墙
				map<position_3D,bool> f;//这个墙是否在列表中 
				position_3D st;st.x=sx,st.y=sy;st.z=sz;
				int smaze=2;//0：UPSTAIR 1：DOWNSTAIR 2：SPACE 
				if(sz<h2&&sz>h1) smaze=RAND(1,0);
				else if(sz<h2) smaze=0;
				else if(sz>h1) smaze=1;
				//能装楼梯就装楼梯 
				if(smaze==2){
					game_map[sx][sy][sz].maze=SPACE;cnt_SPACE++;
				}
				else{
					position_3D pos=st;
					if(smaze==0) pos.z=sz+1;
					else pos.z=sz-1;
					game_map[sx][sy][pos.z].maze=UPSTAIR+(smaze^1),stair_exist[pos.z][smaze^1]=true;
					for(int i=0;i<4;i++){
						position_3D v=dtp3(pos,i,4);
						if(pos_in_area2(v.x,v.y,1,1,l,w,2))
							vec.push_back(v),f[v]=true;
					}
					game_map[sx][sy][sz].maze=UPSTAIR+smaze;stair_exist[sz][smaze]=true;cnt_STAIRS++;
				}
				cnt_notWALL++;
				for(int i=0;i<4;i++){
					position_3D u=dtp3(st,i,4);
					if(pos_in_area2(u.x,u.y,1,1,l,w,2)){
						vec.push_back(u);f[u]=true; 
					}
				}
				while(vec.size()){
					int k=RAND(vec.size()-1,0);
					position_3D u=vec[k];//随便选一堵墙
					swap(vec[k],vec[vec.size()-1]);vec.pop_back();f[u]=0;//把墙u删除 
					if(count_around_pos(u,4,wall_here,l,w)==3&&pos_in_area2(u.x,u.y,1,1,l,w,2)){
					//不是边缘墙且和三面都是墙，不会新增通路，可以拓展
						for(int i=0;i<4;i++){//无论如何u这个墙都会消失，提前把它周围的墙处理好 
							position_3D v=dtp3(u,i,4);
							if(!f.count(v)&&game_map[v.x][v.y][v.z].maze==WALL&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								vec.push_back(v),f[v]=true;
						}
						bool add_stair=RAND_BOOL(a),add_up=0,add_down=0;
						//是否加楼梯，向上/下楼梯分别行不行（虫子的巢穴内部暂不允许存在楼梯） 
						int stair_kind;//楼梯的种类（0：UPSTAIR 1：DOWNSTAIR） 
						position_3D u2=u;u2.z++;//计算上/下楼梯通到的位置 
						if(u.z<=h2&&u.z>=h1&&u2.z<=h2&&game_map[u2.x][u2.y][u2.z].maze==WALL&&count_around_pos(u2,4,wall_here,l,w)==4)
							add_up=true; 
						//在一般游戏区内且向上楼梯通到的这个位置不是空地且周围都是墙壁 
						u2=u;u2.z--;//计算下楼梯通到的位置 
						if(u.z<=h2&&u2.z>=h1&&u2.z<=h2&&game_map[u2.x][u2.y][u2.z].maze==WALL&&count_around_pos(u2,4,wall_here,l,w)==4)
							add_down=true; 
						//在一般游戏区内且向下楼梯通到的这个位置不是空地且周围都是墙壁 
						bool add_nest=RAND_BOOL((u.z<=height?b:c)); 
						position_3D u3=u;u3.z+=(u.z>height?-height:height);//计算进/出巢穴口通往的位置
						//（>height:在巢穴里，-=height <=height:在巢穴外，+=height） 
						if(!(game_map[u3.x][u3.y][u3.z].maze==WALL&&count_around_pos(u3,4,wall_here,l,w)==4))
							add_nest=false;
						//进/出巢穴口通到的这个位置不是空地且周围都是墙壁 这个条件不成立就不行 
						if((add_up||add_down)//上下楼梯至少有一个行
						&&((add_up&&!stair_exist[u.z][0])//这层还没有向上楼梯
						||(add_down&&!stair_exist[u.z][1])//或这层还没有向下楼梯 
						||add_stair)//或想放楼梯
						){
							u2=u;
							if(add_up&&add_down) stair_kind=RAND(1,0);
							else if(add_up) stair_kind=0;
							else stair_kind=1;
							if(stair_kind==0) u2.z++;
							else u2.z--;
							for(int i=0;i<4;i++){//楼上/下周围的墙 
								position_3D v=dtp3(u2,i,4);
								if(!f.count(v)&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								//上面保证楼梯周围都是墙，所以不用判断
									vec.push_back(v),f[v]=true;
							}
							game_map[u.x][u.y][u.z].maze=UPSTAIR+stair_kind;
							game_map[u2.x][u2.y][u2.z].maze=UPSTAIR+(stair_kind^1);
							stair_exist[u.z][stair_kind]=true;stair_exist[u2.z][stair_kind^1]=true;
							cnt_STAIRS+=2;cnt_notWALL+=2;
						}
						else if(add_nest){//加个巢穴口没问题
							for(int i=0;i<4;i++){//进/出巢穴口后周围的墙 
								position_3D v=dtp3(u3,i,4);
								if(!f.count(v)&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								//上面保证进/出巢穴口后周围都是墙，所以不用判断
									vec.push_back(v),f[v]=true;
							}
							bug_nest bns;//生成巢穴口
							if(u.z<=height) bns.init(u);
							else bns.init(u3);
							//存储在一般游戏区里的坐标
							bug_nests.push_back(bns);
							int id=int(bug_nests.size())-1;
							game_map[u.x][u.y][u.z].maze=game_map[u3.x][u3.y][u3.z].maze=SPACE;
							nest &NST=game_map[u.x][u.y][u.z].things.nst,&NST2=game_map[u3.x][u3.y][u3.z].things.nst;
							//分别对应u、u3（都得是引用！！！） 
							NST.exist=NST2.exist=true;NST.id=NST2.id=id;//两个对应的巢穴口共用一个编号 
							NST.to=u3;NST2.to=u;//巢穴口的坐标对应起来 
							cnt_SPACE++;cnt_notWALL++;
						}
						else{//楼梯放了会新增一条通路或者不想放楼梯，就只是空地 
							game_map[u.x][u.y][u.z].maze=SPACE;
							cnt_SPACE++;cnt_notWALL++;
						}
					}
				}
			}
			void fill_dead_ends(int kind,int a,int l=length,int w=width,int h1=1,int h2=height){//填充死胡同 
				vector<position_3D> vec;//存储只连了一个空地的空地（死胡同）
				int cnt2=0;//可能填充的地方（现在不一定是死胡同） 
				for(int z=h1;z<=h2;z++)
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(space_here(u)&&empty_here(u)){
								cnt2++;
								if(count_around_pos(u,4,wall_here,l,w)==3&&count_around_pos(u,4,nest_here,l,w)==0) vec.push_back(u);
							}
						}
				int cnt=0;
				if(kind==1) cnt=a;
				else cnt=cnt2*a/100;
				while(vec.size()&&cnt){
					int k=RAND(vec.size()-1,0);
					position_3D u=vec[k];//随便选一个不是墙的位置
					game_map[u.x][u.y][u.z].maze=WALL;cnt--;
					swap(vec[k],vec[vec.size()-1]);
					vec.erase(vec.begin()+vec.size()-1);
					//把这个位置改成墙，删除
					for(int i=0;i<4;i++){//一个新增的墙只会使周围的空地可能变成死胡同 
						position_3D v=dtp3(u,i,4);
						if(space_here(v)&&empty_here(v)&&count_around_pos(v,4,wall_here,l,w)==3&&count_around_pos(v,4,nest_here,l,w)==0
						&&pos_in_area2(v.x,v.y,1,1,l,w,2))//加个判断是否出界 
							vec.push_back(v);
					}
				}
			}
			void make_room(int a,int b,int c,int d,const int l=length,const int w=width,int h=height){
			//a：去除一片墙的概率 
			//b：把聚在一起的墙挖光，形成一个房间的概率 
			//否则画成网格图 k=RAND(c,d),c>=d
				memset(vst,0,sizeof(vst));
				for(int z=1;z<=h;z++){
					//bool flag=0; 
					for(int y=2;y<w;y++){
						for(int x=2;x<l;x++){
							position_3D pos;
							pos.x=x;pos.y=y;pos.z=z;
							if(!vst[x][y][z]&&in_walls(pos)){//依次从每个未扩展到的墙开始扩展 
								//int cnt=1;
								gotoxy();
								//cout<<"start"<<endl;
								//pos.output1(1);cout.flush();
								vector<position_3D> v_wall;//存储连上的墙 
								while(!Q.empty()) Q.pop();
								vst[x][y][z]=1;
								Q.push(pos);
								//cout<<"???"<<endl;
								while(!Q.empty()){
									position_3D u=Q.front();Q.pop();
									//cout<<"???"<<endl;
									v_wall.push_back(u);
									//u.output1(1);cout.flush();
									for(int i=0;i<4;i++){
										position_3D v=dtp3(u,i,4);
										if(pos_in_area2(v.x,v.y,1,1,l,w,2)&&!vst[v.x][v.y][v.z]&&in_walls(v)){//在边缘墙上的不挖掉 
											vst[v.x][v.y][v.z]=1;
											Q.push(v);
											//cnt++;
										}
									}
									//if(cnt>30) break;
								}
								if(RAND_BOOL(a)){//有概率不去除 
									int sz=v_wall.size(),k=RAND(c,d),kind=RAND_BOOL(b);
									while(sz<k*k*5&&k>=d) k--;
									if(k<d) kind=1;
									int tmp=(k-1)/2;//RAND(k-2,(k-1)/2)（%k=）0~tmp为挖掉范围 
									int delta=0;//RAND(k-1,0);//增加随机性 
									for(int i=0;i<sz;i++){
										position_3D u=v_wall[i];
										if(kind||(u.x+delta)%k<=tmp||(u.y+delta)%k<=tmp) game_map[u.x][u.y][u.z].maze=SPACE;
										//kind:0网格型 1全挖掉 
									}
									//SLEEP(5*1000);
									//flag=1;
									//break;//先试一个 
								}
								
							}
						}
						//if(flag) break;
					}
				}
			}
			void enlarge_maze(int l,int w,int h=height){//映射 
				/*随机映射：
					x[3,l-1]->[3,length-1]
					y[3,w-1]->[3,width-1]
				楼梯、巢穴特殊处理
				1、随机选一个位置作为映射点
					valx[][1],valy[][1]
				*/ 
				vector<int> v;//随机取数
				memset(flagx,0,sizeof(flagx));
				for(int x=3;x<length;x++) v.push_back(x);//3~length
				flagx[2]=1;
				for(int i=1;i<=l-3;i++){//[3,length-1]取l-3个 
					int sz=v.size();
					int k=RAND(sz-1,0),nx=v[k];
					swap(v[k],v[sz-1]);
					v.pop_back();
					flagx[nx]=1;
				}
				int px=2;
				memset(val_x,0,sizeof(val_x));
				val_x[1][0]=1;val_x[2][0]=2;val_x[length][0]=l;
				int lstx=2;//lstx<x,flagx[lstx]=true 
				for(int x=3;x<length;x++){
					if(flagx[x]){
						//[lstx,x-1]->px
						val_x[RAND(x-1,lstx)][1]=px;//楼梯或巢穴口 
						px++;
						lstx=x;
					}
					val_x[x][0]=px;
				}
				//随机分x 
				memset(flagy,0,sizeof(flagy));
				v.clear();
				for(int y=3;y<width;y++) v.push_back(y);//3~width
				for(int i=1;i<=w-3;i++){//[3,width-1]取w-3个 
					int sz=v.size();
					int k=RAND(sz-1,0),ny=v[k];
					swap(v[k],v[sz-1]);
					v.pop_back();
					flagy[ny]=1;
				}
				int py=2;
				memset(val_y,0,sizeof(val_y));
				val_y[1][0]=1;val_y[2][0]=2;val_y[width][0]=w;
				int lsty=2;//lsty<y,flagy[lsty]=true 
				for(int y=3;y<width;y++){
					if(flagy[y]){
						//[lsty,y-1]->py
						val_y[RAND(y-1,lsty)][1]=py;
						py++;
						lsty=y;
					}
					val_y[y][0]=py;
				}
				//随机分y 
				/*
				gotoxy(0,0);
				set_RGBcolor(-100,360,0,360);
				for(int x=1;x<=length;x++) cout<<val_x[x][0]<<" ";
				cout<<endl;
				for(int y=1;y<=width;y++) cout<<val_y[y][0]<<" ";
				cout<<endl;
				for(int x=1;x<=length;x++) cout<<val_x[x][1]<<" ";
				cout<<endl;
				for(int y=1;y<=width;y++) cout<<val_y[y][1]<<" ";
				cout<<endl;
				SLEEP(5000);*/
				for(int z=1;z<=h*2;z++)
					for(int y=width;y>=1;y--)
						for(int x=length;x>=1;x--){
							position_3D u;
							u.x=val_x[x][0];u.y=val_y[y][0];u.z=z;
							position_3D pos;
							pos.x=x;pos.y=y;pos.z=z;
							MAP &POS=game_map[u.x][u.y][u.z];//缩小地图的位置 
							MAP &NPOS=game_map[pos.x][pos.y][pos.z];//新位置
							/*
							bool match_ud=(val_x[x][1]==u.x&&val_y[y][1]==u.y);//上下楼/进出巢穴口 
							if(stair_here(u)){
								if(match_ud){
									NPOS.maze=POS.maze;
								}
								else NPOS.maze=SPACE;
							}
							else if(nest_here(u)&&POS.things.nst.id!=-1){
								if(match_ud){
									bug_nest &bnt=bug_nests[POS.things.nst.id];
									if(h<height) bnt.init(pos);//存储在一般游戏区里的坐标
									NPOS.things.nst=POS.things.nst;
									position_3D &to=NPOS.things.nst.to;
									to.x=x;to.y=y;//修改巢穴口的映射点 
									POS.things.nst.init();//删除原巢穴口 ！ 
								}
								else NPOS.maze=SPACE;
							}
							else NPOS.maze=POS.maze;*/
							bool match_ud=(val_x[x][1]&&val_y[y][1]);//上下楼
							NPOS.maze=POS.maze;
							if(stair_here(u)&&!match_ud) NPOS.maze=SPACE;
						}
			}
			void make_hollow(bool spe=true,int l=length,int w=width,int h=height){//把非巢穴区所有聚在一起的墙挖成中空 
				memset(vst,0,sizeof(vst));//标记数组清空 
				for(int z=1;z<=height;z++)
					for(int y=width;y>=1;y--)
						for(int x=length;x>=1;x--){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(wall_here(u)&&count_around_pos(u,4,wall_here)==4) vst[x][y][z]=1; 
						}
			
					for(int z=1;z<=height;z++)
						if(spe){//贴着边缘墙的墙不挖，防止出口生成在那里出不来 
							for(int y=width-2;y>=3;y--)
								for(int x=length-2;x>=3;x--)
									if(vst[x][y][z]) game_map[x][y][z].maze=SPACE;
						}
						else{
							for(int y=width-1;y>=2;y--)
								for(int x=length-1;x>=2;x--)
									if(vst[x][y][z]) game_map[x][y][z].maze=SPACE;
						}
			}
			void nest_maze(int a,int b,int c,int l=length,int w=width,int h=height){//独立生成巢穴
				//a：生成巢穴口 b：堵塞通道 c：拓宽通道 
				for(int z=h+1;z<=h+h;z++){//枚举巢穴区每一层 
					rand_basic(RAND(l-1,2),RAND(w-1,2),z,1,0,0,l,w,z,z);
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u,v;
							u.x=x;u.y=y;u.z=z;
							v.x=x;v.y=y;v.z=z-h;
							MAP &UPOS=game_map[u.x][u.y][u.z];
							MAP &VPOS=game_map[v.x][v.y][v.z];
							int rate=RAND(100,1);//概率 
							if(rate<=a&&space_here(u)&&space_here(v)){
								bug_nest bns;//生成巢穴口
								bns.init(v);
								//存储在一般游戏区里的坐标
								bug_nests.push_back(bns);
								int id=int(bug_nests.size())-1;
								UPOS.maze=VPOS.maze=SPACE;
								nest &NST=UPOS.things.nst,&NST2=VPOS.things.nst;
								NST.exist=NST2.exist=true;NST.id=NST2.id=id;//两个对应的巢穴口共用一个编号 
								NST.to=v;NST2.to=u;//巢穴口的坐标对应起来
							}
							else if(rate<=a+b&&space_here(u)) UPOS.maze=WALL;
						}
				}
				for(int z=h+1;z<=h+h;z++)//枚举巢穴区每一层 
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(RAND_BOOL(c)&&space_here(u)&&pos_in_area2(x,y,3,l-2,3,w-2)){
								for(int ny=y-1;ny<=y+1;ny++)
									for(int nx=x-1;nx<=x+1;nx++)
										game_map[nx][ny][z].maze=SPACE;
								//拓宽成3*3 
							}
						}
				fill_dead_ends(2,85,length,width,height+1,height*2);//删掉一些死胡同 
			}
			void mark_maze(int l=length,int w=width,int h=height){//标记迷宫信息
				for(int z=1;z<=h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){//标记房间 
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							pos_in_room[x][y][z]=in_room(u);
						}
				for(int z=height+1;z<=height+h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &POS=game_map[u.x][u.y][u.z];
							if(!wall_here(u)) pos_in_nest.push_back(u);//巢穴内部生成完毕，记录虫子的复活点 
						}
			}
				bool path_pos_here(position_3D u){
					return space_here(u)&&empty_here(u)&&divided_part(u)==1&&count_around_pos(u,4,space_here)>1;
				}
			void fill_wide_path(int a,int l=length,int w=width,int mnh=1,int mxh=height){//把地上区宽路变狭窄
			//多余空地：变成墙后不会改变迷宫拓扑结构的空地 
				memset(vst,0,sizeof(vst));
				vector<position_3D> path;//暂时可以去除掉的多余空地 
				for(int z=mnh;z<=mxh;z++)
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							//MAP &POS=game_map[u.x][u.y][u.z];
							if(path_pos_here(u)){
								vst[u.x][u.y][u.z]=1;
								path.push_back(u);
							}
						}
				//预筛选↑ 
				int cnt_path=path.size(),cnt_del=cnt_path*a/100;
				int del_space=0;//实际已经删了多少 
				while(del_space<cnt_del&&path.size()>0){
					int k=RAND(path.size()-1,0);
					position_3D u=path[k];
					swap(path[k],path[path.size()-1]);path.pop_back();
					MAP &POS=game_map[u.x][u.y][u.z];
					if(path_pos_here(u)){
						POS.maze=WALL;
						del_space++;
						//改成墙 
						for(int i=0;i<4;i++){
							position_3D v=dtp3(u,i,4);
							if(pos_in_area2(v.x,v.y,1,1,length,width,2)&&path_pos_here(v)&&!vst[v.x][v.y][v.z]){
								vst[v.x][v.y][v.z]=1;
								path.push_back(v);
							} 
						}
						//更新周围的 
					}
					
				}
			}
			void draft_line(int cnt,int mnl,int mxl,int l=length,int w=width,int h=height){
				//生成水平或竖直的墙 
				for(int z=1;z<=h;z++){//逐层生成 
					int num=cnt;//这层楼的量 
					while(num>0){
						int line_length=RAND(mxl,mnl);
						if(RAND_BOOL(50)){//x不变， 
							int x=RAND(l-2,3),y=RAND(w-line_length+1,1);//起始位置 
							//if(x==2||x==length-1) continue;//防止挡住边缘墙 
							for(int i=0;i<line_length;i++)
								game_map[x][i+y][z].maze=WALL;
						}
						else{//y不变 
							int x=RAND(l-line_length+1,1),y=RAND(w-2,3);//起始位置 
							//if(y==2||y==width-1) continue;//防止挡住边缘墙 
							for(int i=0;i<line_length;i++)
								game_map[i+x][y][z].maze=WALL;
						}
						num--; 
					}
				}
			}
				int pos_id(int x,int y,int z){//坐标编号
					return x+(y-1)*length+(z-1)*length*width;
				}
				int pos_id(position_3D pos){//坐标编号
					return pos.x+(pos.y-1)*length+(pos.z-1)*length*width;
				}
			void connect_room(int l=length,int w=width,int h=height){
				//连接draft_line()生成的房间 
				init_dsu(l*w*h);
				for(int z=1;z<=h;z++)
					for(int y=2;y<width;y++)
						for(int x=2;x<length;x++){
							if(game_map[x][y][z].maze==SPACE){
								if(x<length&&game_map[x+1][y][z].maze==SPACE) unit_dsu(pos_id(x,y,z),pos_id(x+1,y,z));
								if(y<width&&game_map[x][y+1][z].maze==SPACE) unit_dsu(pos_id(x,y,z),pos_id(x,y+1,z));
								//连通 
								if(z>1&&game_map[x][y][z-1].maze==SPACE||z<height&&game_map[x][y][z+1].maze==SPACE)
									divided_walls.push_back((position_3D){x,y,z});//上下能连到空地 
							}
							else divided_walls.push_back((position_3D){x,y,z}); 
						}
				while(divided_walls.size()>0){
					int sz=divided_walls.size(),k=RAND(sz-1,0);
					position_3D pos=divided_walls[k];
					swap(divided_walls[k],divided_walls[sz-1]);divided_walls.pop_back();
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					int posid=pos_id(pos);
					if(space_here(pos)){
						position_3D u=pos,v=pos;
						u.z--;v.z++;//下楼、上楼 
						int uid=pos_id(u),vid=pos_id(v);
						bool can_down=u.z>=1&&space_here(u)&&find_dsu(posid)!=find_dsu(uid)
						,can_up=v.z<=height&&space_here(v)&&find_dsu(posid)!=find_dsu(vid);
						bool kind;
						if(can_down&&can_up) kind=RAND_BOOL(50);
						else if(can_down) kind=0;
						else if(can_up) kind=1;
						else continue;
						//连上楼梯 
						if(kind==0){
							POS.maze=DOWNSTAIR;
							game_map[u.x][u.y][u.z].maze=UPSTAIR;
							unit_dsu(posid,uid);//连通 
						}
						else{
							POS.maze=UPSTAIR;
							game_map[v.x][v.y][v.z].maze=DOWNSTAIR;
							unit_dsu(posid,vid);//连通 
						}
					}
					else if(wall_here(pos)){
						int id=-1;bool flag=false;//id记录上一个位置编号 
						for(int d=0;d<4;d++){
							position_3D u=dtp3(pos,d,4);
							if(pos_in_area(u.x,u.y,1,1,length,width)&&space_here(u)){
								int uid=pos_id(u);
								if(id==-1) id=uid;
								else if(find_dsu(id)!=find_dsu(uid)){//能联通不同房间
								//直接连上，后面再挖墙 
									unit_dsu(id,uid);//连通 
									id=uid;
									flag=true;
								}
							}
						}
						if(flag){//先斩后奏 
							POS.maze=SPACE;//挖掉墙 
							unit_dsu(posid,id);//连通
						}
					}
				}
			}
			void print_maze(){
				return;
				gotoxy();
				for(int z=1;z<=height;z++){//不打印巢穴区 
					gotoxy();
					for(int y=1;y<=width;y++){
						for(int x=1;x<=length;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(wall_here(u)){
								set_RGBcolor(-100,360,0,360);
								cout<<"墙";
							}
							else if(nest_here(u)){
								set_RGBcolor(0,360,0,0);
								cout<<"巢";
							}
							else if(upstair_here(u)){
								set_RGBcolor(-20,360,0,360);
								cout<<"上";
							}
							else if(downstair_here(u)){
								set_RGBcolor(-50,360,0,360);
								cout<<"下";
							}
							else{
								set_RGBcolor(0,360,0,360);
								cout<<"  ";
							}
						}
						cout<<endl;
					}
					SLEEP(5*1000);
					system("cls");
				}
			}
		void rand_maze(int l=length,int w=width,int h=height){
			/*奇怪的房间划分法*/
			make_hollow(false);//全部挖空 
			draft_line(l*w/100,min(5,min(l,w)),min(l,w));//地上区随机划线生成房间 
			print_maze();//
			connect_room();//地上区把房间连起来 
			print_maze();//
			fill_wide_path(3);
			nest_maze(2,10,20);
			mark_maze();//
			print_maze();
			/*乱搞法 
			生成类似密室CS的地图 
			int p=80;
			while(p>0){
				fill_dead_ends(2,p,length,width,1,height);
				make_hollow();
				fill_wide_path(p);
				p-=20;
				print_maze();
			}*/ 
			/*
			double x=RAND_DOUBLE(3,2);//缩小系数 
			if(l>10&&w>10){//缩小长宽 
				l/=x;
				w/=x;
			}
			else x=1;
			*/
			/*缩小系数法2 BUG 
			rand_basic(RAND(l-1,2),RAND(w-1,2),RAND(h,1),1,5,10,l,w);//按照缩小比例生成地图，包括巢穴 
			print_maze();
			enlarge_maze(l,w);//放大 
			fill_wide_path(50);//缩小巢穴区的宽路 
			make_hollow();//挖空地上区的墙 
			mark_maze();//做标记 
			print_maze();
			*/
			/*缩小系数法1 
			
			rand_basic(RAND(l-1,2),RAND(w-1,2),RAND(h,1),1,0,0,l,w);//按照缩小比例生成地图，不生成巢穴 
			//gotoxy(100,0);	
			//set_RGBcolor(-100,360,0,360);
			//cout<<"l="<<l<<" w="<<w<<endl;
			//print_maze();
			enlarge_maze(l,w);
			make_hollow();
			fill_wide_path(5);
			nest_maze(2,10,20);
			mark_maze();
			print_maze();
			*/
			/*旧方法 
			rand_basic(RAND(l-1,2),RAND(w-1,2),RAND(h,1),1,5,10);
			//调整下面这些函数的参数，生成不同的迷宫
			fill_dead_ends(1,RAND_ALTO(cnt_SPACE,0,RAND(40,20)),length,width,1,height);
			fill_dead_ends(2,85,length,width,height+1,height*2);
			make_room(100,5,6,2);
			mark_maze();
			//print_maze();*/
		}
			void make_exits(int l=length,int w=width,int h=height){//生成所有的出口
				int exit_nums=RAND_ALTO(max(max(l,w)*height/10,1),1,1)+1;//游戏地图中出口的数量（保证至少有一个） 
				RAND_EXIT_AROUND_GAME_MAP(exit_nums,l,w,h);
			}
				void mark_exit(int x,int y,int z){//标记一个出口 
					Q.push((position_3D){x,y,z});
					vst[x][y][z]=1;
					dis_to_exit[x][y][z]=0;
					//cout<<x<<" "<<y<<" "<<z<<"\n"; 
				}
			void make_exit_sign(int a,int b,int l=length,int w=width,int h=height){//生成出口的标牌->]（箭头用char(24~27)）
				memset(vst,0,sizeof(vst));
				memset(dis_to_exit,-1,sizeof(dis_to_exit));
				//距离全部初始化为-1！ 
				while(!Q.empty()) Q.pop();
				for(int z=1;z<=height*2;z++){
					for(int x=2;x<=length-1;x++)//枚举上下边缘
						if(game_map[x][1][z].maze==EXIT) mark_exit(x,1,z);
						else if(game_map[x][width][z].maze==EXIT) mark_exit(x,width,z);
					for(int y=2;y<=width-1;y++)//枚举左右边缘 
						if(game_map[1][y][z].maze==EXIT) mark_exit(1,y,z);
						else if(game_map[length][y][z].maze==EXIT) mark_exit(length,y,z);
					//角上不会有出口 
				}
				//make_exits和make_exit_sign切割开 
				while(!Q.empty()){//BFS 
					position_3D u=Q.front();Q.pop();
					for(int i=0;i<4;i++){
						position_3D v=dtp3(u,i,4);
						if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
							if(!vst[v.x][v.y][v.z]&&game_map[v.x][v.y][v.z].maze!=WALL){
								vst[v.x][v.y][v.z]=1;
								dis_to_exit[v.x][v.y][v.z]=dis_to_exit[u.x][u.y][u.z]+1;
								Q.push(v);
								if(v.z<=height&&space_here(v)&&empty_here(v) 
								&&count_around_pos(v,4,space_here)>=3
								&&(pos_in_room[v.x][v.y][v.z]?RAND_BOOL(a):RAND_BOOL(b))
								){
									exit_sign &EXIT_SIGN=game_map[v.x][v.y][v.z].things.exit_signs;
									EXIT_SIGN.exist=1;
									EXIT_SIGN.dir=turn(i,TURN_BACK);
								}
								if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
								else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
								else if(game_map[v.x][v.y][v.z].things.nst.exist) v=game_map[v.x][v.y][v.z].things.nst.to;
								if(!vst[v.x][v.y][v.z]&&u.z!=v.z){//这边有楼梯或者巢穴口 
									vst[v.x][v.y][v.z]=1;
									dis_to_exit[v.x][v.y][v.z]=dis_to_exit[u.x][u.y][u.z]+1;
									Q.push(v);
								}
							}
						}
					}
				}
			}
		void make_exit(){
			//必须放在迷宫基本设施生成完毕后！！！ 
			if(game_map_from==RANDOM) make_exits(); 
			//文件读入暂时关闭这些 
			make_exit_sign(4,8);
		}
	void make_map(){
		logMessage("make_map");
		if(game_map_from==RANDOM) rand_maze();
		//文件读入暂时关闭这些 
		make_exit();
	}
		void player::init(){
			pos=RAND_PLAYER_IN_GAME_MAP();
			game_map[pos.x][pos.y][pos.z].player_enemy=PLAYER;
			d1=d2=0;color=0;flash_word="";
			angle=lsta=270;//向前的方向角 
			alc=0;
			w.speed=0;w.vt();
			mpos=pos000;
			vts.init();
			//vlc.wait_time=1;vlc.ts();//wait_time更新speed 
			vlc.speed=100;vlc.vt();//speed更新wait_time 
			scr.init();
			items.init();
			spe.init();
			move=true;
			action_kind=RUN; 
			lst_ud=lst_enter=false;
			grid=-INF;
		}
			void update_pos_mx_dis(position_3D u){//统计到玩家不同距离的位置，计算最远距离
				int x=u.x,y=u.y,z=u.z;
				if(dis_to_player[x][y][z]>0&&!wall_here(u)){
					pos_dis_to_player_door[dis_to_player[x][y][z]].push_back(u);
					pos_dis_to_player_key[dis_to_player[x][y][z]].push_back(u);
				}
				mx_dis_to_player=max(mx_dis_to_player,dis_to_player[x][y][z]); 
			}
		void calculate_dis_to_player(int l=length,int w=width,int h=height){
			while(!Q.empty()) Q.pop();
			memset(vst,0,sizeof(vst));
			memset(dis_to_player,-1,sizeof(dis_to_player));
			//初始化为-1！
			Q.push(player1.pos);
			vst[player1.pos.x][player1.pos.y][player1.pos.z]=1;
			dis_to_player[player1.pos.x][player1.pos.y][player1.pos.z]=0;
			while(!Q.empty()){//BFS 
				position_3D u=Q.front();Q.pop();
				for(int i=0;i<4;i++){
					position_3D v=dtp3(u,i,4);
					MAP &NPOS=game_map[v.x][v.y][v.z];
					if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
						if(!vst[v.x][v.y][v.z]&&NPOS.maze!=WALL){
							vst[v.x][v.y][v.z]=1;
							dis_to_player[v.x][v.y][v.z]=dis_to_player[u.x][u.y][u.z]+1;
							update_pos_mx_dis(v);
							Q.push(v);
							if(NPOS.maze==UPSTAIR) v.z++;
							else if(NPOS.maze==DOWNSTAIR) v.z--;
							else if(NPOS.things.nst.exist) v=NPOS.things.nst.to;
							if(!vst[v.x][v.y][v.z]&&u.z!=v.z){//这边有楼梯可以上下 
								vst[v.x][v.y][v.z]=1;
								dis_to_player[v.x][v.y][v.z]=dis_to_player[u.x][u.y][u.z]+1;
								update_pos_mx_dis(v);
								Q.push(v);
							}
						}
					}
				}
			}
		}
	void make_player(){
		logMessage("make_player"); 
		player1.init();
		calculate_dis_to_player();
	}
			void bug::init(position_3D u,double speed){
				pos=u;d=0;vlc.speed=speed;vlc.vt();
				lfin.init(5);//改了这个bug_move_away也要改
				lst_ud=enter_nest=-INF;change_pos=update=false;
			}
			void bug_nest::init(position_3D u){
				pos=u;
				lfin.init(3);
			}
			void pos_make_bug(position_3D u,double speed,bool upd){//在指定位置生成虫子（要先检验位置合理性） 
				//upd:是否加入队列更新 
				MAP &POS=game_map[u.x][u.y][u.z];
				bug bg;//生成虫子
				bg.init(u,speed);
				bugs.push_back(bg);
				int id=int(bugs.size())-1;
				POS.player_enemy=BUG;POS.emy.id=id;
				/*暂不加入队列，会有BUG */
				if(upd){
					Qbug.push(id);
					bugs[id].update=true;//不能用bg.update！ 
				}
			}
		void make_bug(int a,int b,int c,int l=length,int w=width,int h=height){//生成虫子 
			for(int z=1;z<=height+h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						if(space_here(u)&&nobody_here(u)&&empty_here(u)&&dis_to_player[x][y][z]>=10//至少在玩家10步开外 
						&&dis_to_exit[x][y][z]>0&&RAND_BOOL(a+b/dis_to_exit[x][y][z]*(100-c-a)/b+(z>height?c:0))){ 
							pos_make_bug(u,RAND(4,3),0);
						}
					}
		}
			void spider::init(position_3D u,bool k){
				pos=bir=u;prey=pos000;d=0;vlc.speed=RAND(5,4);vlc.vt();
				lfin.init(20);//改了这个spider_move_away也要改
				kind=k;
				change_pos=update=false;
			}
		void make_spider(int a,int b,int l=length,int w=width,int h=height){//生成蜘蛛 
			for(int z=1;z<=height;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						int k=RAND_BOOL(b);//提前定种类 
						//if(count_around_pos(u,8,space_here)==8&&count_around_pos(u,8,noitem_here)==8) k=1;
						//else k=0;
						//k=1;
						if(space_here(u)&&nobody_here(u)&&noitem_here(u)&&dis_to_player[x][y][z]>=10//至少在玩家10步开外 
						&&(k?count_around_pos(u,8,space_here)==8&&count_around_pos(u,8,noitem_here)==8:1)
						&&RAND_BOOL(a)&&RAND_BOOL(10)){
							spider sr;//生成蜘蛛
							sr.init(u,k);
							spiders.push_back(sr);
							int id=int(spiders.size())-1;
							POS.player_enemy=SPIDER;POS.emy.id=id;
							for(int i=0;i<8;i++){ 
								position_3D v=dtp3(u,i,8);
								MAP &VPOS=game_map[v.x][v.y][v.z];
								spider_leg &slg=VPOS.things.slg;
								slg.num++;slg.id=id;//附肢在地图上标记一下
							}
							if(k==0) POS.things.snt.endurance=100;//A型蜘蛛出生点留下蜘蛛网 
						}
					}
		}
			void ghost::init(position_3D u,int att,int def){
				//def=0;//防御技能清空 
				pos=u;goal=pos000;d=0;vlc.speed=RAND_DOUBLE(3.5,1.5);vlc.vt();
				lfin.init(30);//改了这个ghost_move_away也要改 
				spat.init(att,def);
				switch(spat.attack){
					case THROUGH:
						spat.thr.time=RAND(10000,1);
						break;
					case DISAPP:
						spat.disa.use=true;//一开始隐身 
						spat.disa.time=RAND(20000,10000);
						spat.disa.maxt=RAND(10000,5000);
						spat.disa.kind=RAND(2,1);
						break;
					case INSTANT:
						spat.ins.p=RAND(60,30); 
						spat.ins.dis=RAND(7,3);
						break;
				}
				switch(spat.defense){
					case EVADE:
						spat.eva.k=RAND(100,50);
						break;
					case ROCK:
						spat.rck.k=RAND(50,1)*0.01;
						break;
					case SHIELD://=上面2个加起来 
						spat.rck.k=RAND(50,30)*0.01;
						spat.eva.k=RAND(75,50);
						break;
				}
				change_pos=update=false;
				attack_time=RAND_DOUBLE(0.7,0.5);
				spe.init();//特殊效果清空 
			}
		void make_ghost(int a,int b,int l=length,int w=width,int h=height){//生成鬼 
			for(int z=1;z<=height+h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						if(space_here(u)&&nobody_here(u)&&empty_here(u)&&dis_to_player[x][y][z]>=20//至少在玩家20步开外 
						&&RAND_BOOL(10)&&mx_dis_to_player>0&&RAND_BOOL(a+dis_to_player[x][y][z]*(b-a+1)/mx_dis_to_player)){ 
							ghost gt;//生成鬼
							gt.init(u,RAND(RAND(RAND(INSTANT,0),0),0),RAND(RAND(ROCK,0),0));
							//gt.init(u,VAMPIRE,0);
							special_attribute &spat=gt.spat;
							int id=int(ghosts.size());
							
							if(/*(spat.attack==THROUGH||spat.attack==DISAPP||spat.attack==INSTANT)
							&&*/MHT_DIST_p3(u,player1.pos)<=50){//提前开始更新 
								gt.update=true;
								Qghost.push(id);
							}
							ghosts.push_back(gt);
							POS.player_enemy=GHOST;POS.emy.id=id;
						}
					}
		}
	void make_enemy(){
		logMessage("make_enemy"); 
		make_bug(4,30,40);
		make_spider(5,80);
		make_ghost(20,25);
	}
			void farther_more_doors(int a,int b,int c,int d){//越远越多
			logMessage("farther_more_doors"); 
			//a:某个距离上有门的概率 [b,c]:从近到远门的生成数量占此距离上总数的期望占比 d:开着的门的概率 
				for(int i=10;i<=mx_dis_to_player;i++)//枚举不同的距离 
					if(RAND_BOOL(a)){
						int sz=pos_dis_to_player_door[i].size(),door_num=RAND_ALTO(sz>0?sz:1,1,b+i*(c-b)/mx_dis_to_player);
						//当前这个距离上可以放门的位置数量（用于随机取位置）和需要的门数量 
						logMessage("sz,door_num"); 
						while(sz>0&&door_num>0){
							int k=RAND(sz-1,0);
							position_3D u=pos_dis_to_player_door[i][k];
							swap(pos_dis_to_player_door[i][k],pos_dis_to_player_door[i][sz-1]);
							sz--;
							logMessage("door pos?"); 
							//随机找放门的位置
							MAP &DPOS=game_map[u.x][u.y][u.z]; 
							thing &THING=DPOS.things;
							key_door &DRS=THING.kdr;
							bool kdr_place=space_here(u)&&empty_here(u)&&!count_around_pos(u,4,key_door_here);
							logMessage("kdr_place"); 
							spider_leg_here(u);
							logMessage("kdr_place spider_leg_here?"); 
							player_here(u);
							logMessage("kdr_place player_here?"); 
							//ghost_here(u);
							logMessage("kdr_place ghost_here?"); 
							spider_body_here(u);
							logMessage("kdr_place spider_body_here?"); 
							bug_here(u);
							logMessage("kdr_place bug_here?"); 
							bool kdr_being=0;
							kdr_being=nobody_here(u)&&count_around_pos(u,4,player_here)==0;//周围没有玩家 
							logMessage("kdr_being"); 
							/*
							try{
							}
							catch (const std::exception& e){
								string message = e.what();
								logMessage("捕获到异常: "+message);
								continue;
    						}*/
							if(u.z<=height
							&&kdr_place
							&&kdr_being
							&&useful_door(position_3Dto2D(u),u.z,10)){
							//空地、无物、有用（从门的一边到另一边的路程不会太近） 
								int door_kind=RAND(4,1);//随机选门种类
								DRS.exist=true;
								DRS.kind=door_kind-1+DOOR1;
								DRS.light_through=RAND_BOOL(80);//随机选择门的透明度
								DRS.state=RAND_BOOL(d)*2;//0/2
								door_num--;
								logMessage("door here"); 
							}
							logMessage("next door"); 
						}
						logMessage("next dis"); 
					}
			}
			void doors_around_rooms(int a,int b,int l=length,int w=width,int h=height){//门生成在房间周围 
			//b:开着的门的概率 
				logMessage("doors_around_rooms"); 
				for(int z=1;z<=h;z++)
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &POS=game_map[u.x][u.y][u.z]; 
							thing &THING=POS.things;
							key_door &DRS=THING.kdr;
							if(RAND_BOOL(a)
							&&!pos_in_room[u.x][u.y][u.z]
							&&space_here(u)&&nobody_here(u)&&empty_here(u)
							&&count_around_pos(u,4,wall_here)<=2&&!count_around_pos(u,4,key_door_here)
							&&count_around_pos(u,4,player_here)==0){//周围没有玩家 
							//不在房间里，空地，周围没有门、不多于2堵墙 
								bool flag=0;
								for(int i=0;i<4;i++){
									position_3D v=dtp3(u,i,4);
									if(pos_in_room[v.x][v.y][v.z]){
										flag=1;
										break;
									}
								}
								if(!flag) continue;
								int door_kind=RAND(4,1);//随机选门种类
								DRS.exist=true;
								DRS.kind=door_kind-1+DOOR1;
								DRS.light_through=RAND_BOOL(20);//随机选择门的透明度 
								DRS.state=RAND_BOOL(b)*2;//0/2
							}
						}
			}
		void make_key_door(){
			logMessage("make_key_door"); 
			farther_more_doors(5,10,25,0);
			doors_around_rooms(100,0);
		}
		void make_hiden_door(int a,int l=length,int w=width,int h=height){
			logMessage("make_hiden_door"); 
			return;//先不设置，有点烦 
			for(int z=1;z<=h;z++)
				for(int y=2;y<w;y++)
					for(int x=2;x<l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						if(RAND_BOOL(a)
						&&space_here(u)&&nobody_here(u)&&empty_here(u)
						&&divided_part(u)>=2&&count_around_pos(u,4,nobody_here)==4){
							hiden_door &HDR=POS.things.hdr;
							HDR.exist=true;
							HDR.kind=1;//RAND(2,1);
						}
					}
		}
			void farther_less_keys(int a,int b,int c){//越远越少 
				for(int i=1;i<=mx_dis_to_player;i++)
					if(RAND_BOOL(a)){
						int sz=pos_dis_to_player_key[i].size(),key_num=RAND_ALTO(sz>0?sz:1,1,b-i*(b-c)/mx_dis_to_player);
						//当前这个距离上可以放钥匙的位置数量（用于随机取位置）和需要的钥匙数量（会随着生成不断减小） 
						while(sz&&key_num){
							int k=RAND(sz-1,0);
							position_3D u=pos_dis_to_player_key[i][k];
							swap(pos_dis_to_player_key[i][k],pos_dis_to_player_key[i][sz-1]);
							//sz--;位置可以重复放 
							//随机找放钥匙的位置
							MAP &KPOS=game_map[u.x][u.y][u.z]; 
							thing &KTHING=KPOS.things;
							object obj;obj.type=KEY;
							if(u.z<=height&&space_here(u)&&KPOS.things.noitem()){
								int key_kind=RAND(3,0);//随机选钥匙种类
								KTHING.key=key_kind+KEY1;
								obj.key=key_kind+KEY1;
								new_object(obj,KTHING.fir);
								key_num--;
							} 
						}
					}
			}
			void keys_in_rooms(int a,int l=length,int w=width,int h=height){//钥匙生成在房间里面
				vector<position_3D> v;
				for(int z=1;z<=h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &KPOS=game_map[u.x][u.y][u.z]; 
							if(pos_in_room[x][y][z]&&space_here(u)&&KPOS.things.noitem())
								v.push_back(u);
						}
				for(int i=0;i<int(v.size());i++){
					position_3D u=v[i];
					MAP &KPOS=game_map[u.x][u.y][u.z]; 
					thing &KTHING=KPOS.things;
					object obj;obj.type=KEY;
					if(RAND_BOOL(a)){
						int key_kind=RAND(3,0);//随机选钥匙种类
						obj.key=KTHING.key=key_kind+KEY1;
						new_object(obj,KTHING.fir);
						new_object(obj,KTHING.fir);
						//一次性放2个 
					} 
				}
			}
			void keys_to_doors(int a,int b,int l=length,int w=width){//每个钥匙都对应一扇门 
				vector<position_3D> vspace;//已访问、未放钥匙的空地	
				vector<position_3D> vdoor[4];//已访问、未放对应钥匙的门（四种分别记录）
				while(!Q.empty()) Q.pop();
				memset(vst,0,sizeof(vst));
				Q.push(player1.pos);
				vst[player1.pos.x][player1.pos.y][player1.pos.z]=1;
				while(1){
					while(!Q.empty()){//BFS 
						position_3D u=Q.front();Q.pop();
						for(int i=0;i<4;i++){
							position_3D v=dtp3(u,i,4);
							if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
								if(!vst[v.x][v.y][v.z]
								&&!wall_here(v)&&!door_here(v)){//不穿墙、不走门（当然不包括起点） 
									vst[v.x][v.y][v.z]=1;
									Q.push(v);
									if(space_here(v)&&noitem_here(v)) vspace.push_back(v);//已访问、没有物品的空地
									else if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
									else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
									else if(game_map[v.x][v.y][v.z].things.nst.exist) v=game_map[v.x][v.y][v.z].things.nst.to;
									if(u.z!=v.z&&!vst[v.x][v.y][v.z]){//这边有楼梯可以上下/巢穴可以进出，且不会走到去过的地方 
										vst[v.x][v.y][v.z]=1;
										Q.push(v);
									}
								}
								else if(!vst[v.x][v.y][v.z]&&door_here(v)){
									vst[v.x][v.y][v.z]=1;
									vdoor[game_map[v.x][v.y][v.z].things.kdr.kind-DOOR1].push_back(v);
									//已访问、未放对应钥匙的门
								}
							}
						}
					}
					vector<int> vkind;//可以选择的门的种类 
					for(int i=0;i<4;i++)
						if(vdoor[i].size()&&vspace.size()>=vdoor[i].size()) vkind.push_back(i);
					if(vkind.size()){//有可以选择的门的种类  
						int door_kind=vkind[RAND(vkind.size()-1,0)];//随机选门的种类
						for(int i=0;i<int(vdoor[door_kind].size());i++){
							position_3D dr=vdoor[door_kind][i];//当前放的钥匙对应的门 
							Q.push(dr);
							//把放了对应钥匙的门“打开”，作为下次循环的起点 
							int k=RAND(vspace.size()-1,0);
							position_3D u=vspace[k];
							//取出要放钥匙的空地
							MAP &KPOS=game_map[u.x][u.y][u.z];
							thing &KTHING=KPOS.things;
							object obj;obj.type=KEY;
							if(1){
							//目前所有门都保证有钥匙 
							//dis_to_player[dr.x][dr.y][dr.z]>0?RAND_BOOL(a*max(1,b/dis_to_player[dr.x][dr.y][dr.z])):RAND_BOOL(a)
								int key_kind=door_kind;
								obj.key=KTHING.key=key_kind+KEY1;
								new_object(obj,KTHING.fir);
								//空地不删掉↓可以堆叠 
								//swap(vspace[k],vspace[vspace.size()-1]);vspace.pop_back();//放了钥匙才把这个空地删掉 
							}
							//生成钥匙 
						}
						vdoor[door_kind].clear();//清空这类门 
					}
					else break;//循环到没有未放对应钥匙的门（至少一次，因为最开始没门） 
				}
			}
		void make_key(){
			logMessage("make_key"); 
			//farther_less_keys(20,15,5); 
			//keys_in_rooms(10);//10
			keys_to_doors(100,0); 
		}
		void make_mirror(position_3D u,int a,int l=length,int w=width,int h=height){
			logMessage("make_mirror"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			if(RAND_BOOL(a)
			&&space_here(u)&&no_mirror_around(u)&&nobody_here(u)&&empty_here(u)&&!THING.exit_signs.exist){//不生成在出口标牌上 
				int mirror_dir=RAND_MIRROR_DIRECTION(u);
				if(mirror_dir==-1) return;
				int cw=count_around_pos(u,4,wall_here),mirror_side;
				if(cw==2) mirror_side=1;
				else if(!cw) mirror_side=2;
				else mirror_side=RAND(2,1);
				mirror &MIRROR=game_map[u.x][u.y][u.z].things.mirrors;
				MIRROR.exist=1;MIRROR.side=mirror_side;
				if(mirror_side==1) MIRROR.dir=mirror_dir;
				else MIRROR.dir=mirror_dir%2;
				MIRROR.endurance=100;
			}
		}
		void make_window(position_3D u,int a,int l=length,int w=width,int h=height){
			logMessage("make_window"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			if(RAND_BOOL(a+count_around_pos(u,4,window_here)*15)&&pos_in_area2(u.x,u.y,1,1,length,width,2)
			//+(u.x==length||u.y==width?100:0)边缘墙打窗户 
			&&wall_here(u)&&nobody_here(u)&&empty_here(u)&&divided_part(u)>=2
			//&&!game_map[u.x-1][u.y-1][u.z].things.windows.exist
			&&!count_around_pos(u,4,player_here)){
				window &WDN=POS.things.windows;
				WDN.exist=true;
				WDN.endurance=100;
				WDN.state=RAND(1,0);
			}
		}
		void make_curtain(position_3D u,int a,int b,int l=length,int w=width,int h=height){
			logMessage("make_curtain"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			if(RAND_BOOL(a+count_around_pos(u,4,curtain_here)*b)
			&&space_here(u)&&nobody_here(u)&&empty_here(u)&&count_around_pos(u,4,wall_here)<=2){
				curtain &CRT=POS.things.crt;
				CRT.exist=true;
				CRT.endurance=100;
			}
		}
				int pos_to_brightness(position_3D u,position_3D v,int p){//以u为光源换算v的光照强度增量（发散光） 
					if(u.x==v.x&&u.y==v.y) return p;//防止/0！
					return p/MHT_DIST(u.x,u.y,v.x,v.y);
				}
				int pos_to_brightness2(position_3D u,position_3D v,int p,int dir,int angle){//以u为光源换算v的光照强度增量（聚光灯）
					//dir、d：方向角0~359 
					if(u.x==v.x&&u.y==v.y) return p;
					int d=calc_angle(u,v),tmp=(dir-d+360)%360,d2=min(tmp,360-tmp);//角度差 
					if(d2>angle||angle==0) return 0;
					return p/sqrt(MHT_DIST(u.x,u.y,v.x,v.y))*cos(d2*(90.0/angle)/180.0*PI);
					//  功率   距离因子（开平方减小影响）      余弦衰减因子（d2=0->1,d2=angle->0） 
				}
			void update_light_brightness(position_3D u,bool scr=1){//重新计算以u灯为光源的光照范围并更新（发散光） 
				//scr：是否更新到屏幕 
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things; 
				light &LGT=THING.lgt;
				LGT.update=false;//防止重复更新 
				int id=LGT.id;
				if(id<0) return;
				map<position_3D,bool> mp;
				for(int i=0;i<light_area[id].size();i++){//清空上次的照射区域 
					position_3D v=light_area[id][i];
					MAP &NPOS=game_map[v.x][v.y][v.z];
					NPOS.brightness-=pos_to_brightness(u,v,LGT.p);//减少
					mp[v]=1;
					if(NPOS.ist.player==lst_see_time){//上次照射的全部清除更新 (!LGT.state&&灯关了?)
						game_flag["光照更新"]=true;
						pos_change.insert(v);
					} 
				}
				light_area[id].clear();
				if(!LGT.state) return;//灯关了 
				vector<PII> v;vector<position_3D> ret;
				for(int i=0;i<4;i++) v.push_back(MP(0,359));
				vision_init(1,v,ret,pos000);
				calculate_vision2(u,2,ret,INF,0);//计算新的照射范围
				for(int i=0;i<ret.size();i++){
					position_3D v=ret[i];
					MAP &NPOS=game_map[v.x][v.y][v.z];
					light_area[id].push_back(v);//更新此灯照射范围 
					NPOS.brightness+=pos_to_brightness(u,v,LGT.p);//增加 
					if(scr&&!mp[v]&&NPOS.ist.player==lst_see_time){//更新到屏幕
						game_flag["光照更新"]=true;
						pos_change.insert(v);
					}
				}
			}
		void make_light(position_3D u,int a,int b,int c,int &cnt,int l=length,int w=width,int h=height){//生成灯
			logMessage("make_light"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			light &LGT=THING.lgt;
			int p=RAND(40,20);
			bool st=RAND_BOOL(c);//有概率是暗的 
			if((pos_in_room[u.x][u.y][u.z]?RAND_BOOL(a):RAND_BOOL(b))
			&&space_here(u)&&nobody_here(u)&&empty_here(u)&&!THING.exit_signs.exist&&!THING.nst.exist
			&&POS.brightness+p<=0){//防止太亮 
				LGT.exist=true;
				LGT.p=p;
				LGT.id=cnt++;
				LGT.update=true;
				LGT.state=st;
				update_light_brightness(u,0);//不显示到屏幕 
			}
		}
		void make_fog(position_3D u,int a,int l=length,int w=width,int h=height){//生成雾气
			logMessage("make_fog"); 
			if(RAND_BOOL(a)&&(space_here(u)||stair_here(u))&&nobody_here(u)&&empty_here(u)
			//&&(u.z<=height?count_around_pos(u,4,space_here)+count_around_pos(u,4,stair_here):count_around_pos(u,4,bug_nest_here))==0
			){
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				for(int i=0;i<3;i++) FOGS.absorbance[i]=RAND_BOOL(50)*7000+3000;//初始化，后续慢慢扩散
				//雾的颜色：RGB三原色及其混色共8种；对雾颜色的absorbance较低 
				//absorbance[x]>0表示x颜色被吸收 
				//FOGS.col=code_to_RGB(0,120*RAND(2,0),0);//红/绿/蓝雾 
				FOGS.update=true; 
				pos_fog.push(u);//加入队列 
			}
		}
		void make_mvb(position_3D u,int a,int b,int c,int l=length,int w=width,int h=height){//生成可移动物品
			logMessage("make_mvb"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			movable &mvb=POS.things.mvb;
			int k=RAND(BALL,BOX);//BOX;//
			if(ghost_here(u)||bug_here(u)) k=BOX;
			logMessage("ghost_herebug_here"); 
			bool rAnD=RAND_BOOL(k==BOX&&ghost_here(u)?a:(pos_in_room[u.x][u.y][u.z]?b:c));//在房间/有鬼的位置箱子高概率 
			logMessage("rAnD"); 
			bool plh=player_here(u);
			logMessage("plh"); 
			bool sph=spider_here(u);
			logMessage("sph"); 
			bool noh=nobody_here(u);
			logMessage("noh"); 
			bool emh=empty_here(u);
			logMessage("emh"); 
			bool being=(k==BOX?!plh&&!sph:noh&&emh);//箱子里可以有除玩家、蜘蛛以外的生物 
			logMessage("being"); 
			if(rAnD&&being&&space_here(u)&&dis_to_player[u.x][u.y][u.z]>=15){
				logMessage("mvb.exist=true;"); 
				mvb.exist=true;
				mvb.kind=k;
				POS.fcmv.lock=false;
			}
		}
		void make_dart(position_3D u,int a,int b,int l=length,int w=width,int h=height){//生成地上的回旋镖
			logMessage("make_dart"); 
			dart &DRT=game_map[u.x][u.y][u.z].things.drt;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				DRT.num[0]++;
			}
		}
		void make_smoke_bomb(position_3D u,int a,int b,int l=length,int w=width,int h=height){//生成 
			logMessage("make_smoke_bomb"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			smoke_bomb &SMB=game_map[u.x][u.y][u.z].things.smb;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				object obj;obj.type=SMO; 
				new_object(obj,THING.fir);
			}
		}
		void make_ppt(position_3D u,int a,int b,int l=length,int w=width,int h=height){//生成可使玩家获得透视效果的道具
			logMessage("make_ppt"); 
			MAP &POS=game_map[u.x][u.y][u.z];
			thing &THING=POS.things; 
			perspective &PPT=game_map[u.x][u.y][u.z].things.ppt;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				/*
				PPT.exist=true;
				PPT.kind=RAND(RAND(1,1),1); //2
				PPT.time=RAND(10,5)*1000;//ms */
				object obj;obj.type=PER; 
				obj.stp.kind=RAND(RAND(1,1),1);//2
				obj.stp.time=RAND(10,5)*1000;//ms
				new_object(obj,THING.fir);
			}
		}
			void pos_make_food(position_3D u,int kind,int effect){
				thing &THING=game_map[u.x][u.y][u.z].things;
				food_pile &FOOD=THING.foods;
				//FOOD.make(kind,effect);
				object obj;obj.type=FOO;
				obj.foods={kind,effect};
				new_object(obj,THING.fir);
			}
		void make_food(position_3D u,int a,int b,int l=length,int w=width,int h=height){
			logMessage("make_food"); 
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(b)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)){
				int kind=RAND(ADDL,ADDS),effect=log2(RAND(1<<3,1<<1));//8,7,6,5->3;4,3->2;2->1
				pos_make_food(u,kind,effect);
			}
		}
		void make_wpn_energy_edc(position_3D u,int a,int b,int c,int l=length,int w=width,int h=height){//生成武器的能量/耐久度回复
			logMessage("make_wpn_energy_edc"); 
			weapon_energy_edc &WEE=game_map[u.x][u.y][u.z].things.wee;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(pos_in_room[u.x][u.y][u.z]?b:c)&&!box_here(u)&&empty_here(u))&&space_here(u)&&nobody_here(u)&&empty_here(u)){
				WEE.exist=true;
				WEE.num=RAND(9,1);
				if(RAND_BOOL(c)) WEE.kind=0;
				else WEE.kind=1;
			}
		}
		void make_weapon(position_3D u,int a,int b,int c,int l=length,int w=width,int h=height){//生成武器 
			logMessage("make_weapon"); 
			thing &THING=game_map[u.x][u.y][u.z].things;
			if((RAND_BOOL(a)&&box_here(u)||RAND_BOOL(pos_in_room[u.x][u.y][u.z]?b:c)&&!box_here(u)&&noitem_here(u))
			&&space_here(u)&&nobody_here(u)&&noitem_here(u)){
				object obj;obj.type=RAND(BLA,LAS);//LAS,DAR,SPE,DAG,SWO,BLA
				//obj.type=SPE;
				switch(obj.type){
					case LAS:obj.lsrE=RAND(9,1);break;//激光枪能量 
					case SPE:obj.sprE=RAND(100,50);break;//长矛耐久 
					case DAG:obj.daggerE=RAND(100,50);break;//匕首耐久 
					case SWO:obj.swordE=RAND(100,50);break;//剑耐久 
					case BLA:obj.bladeE=RAND(100,50);break;//长刀耐久 
				}
				new_object(obj,THING.fir);
			}
		}
		void make_TNT(){
		}
		void make_treasure(){
		}
		void make_candle(){
		}
		void make_water(){
		}
		void make_magma(){
		}
	void make_thing(int l=length,int w=width,int h=height){
		logMessage("make_thing"); 
		int cnt_light=0;
		make_key_door();
		if(game_map_from==RANDOM) make_hiden_door(20);
		make_key();
		//print_maze();
		for(int z=1;z<=h;z++)//地上区的东西 
			for(int y=1;y<=w;y++)
				for(int x=1;x<=l;x++){
					position_3D u;
					u.x=x;u.y=y;u.z=z;
					//make_mirror(u,10); 
					if(game_map_from==RANDOM) make_window(u,5);
					if(game_map_from==RANDOM) make_curtain(u,2,12);
					make_light(u,15,50,50,cnt_light);
					//make_fog(u,1);//指定位置全部是雾 
					make_mvb(u,100,15,1);
					//make_dart(u,20,2); 
					make_smoke_bomb(u,20,0);
					make_food(u,80,1);
					//make_wpn_energy_edc(u,20,2,80);
					make_weapon(u,15,2,20);//10,1,15
				}
		//print_maze();
		for(int z=h+1;z<=h*2;z++)//巢穴区的东西 
			for(int y=1;y<=w;y++)
				for(int x=1;x<=l;x++){
					position_3D u;
					u.x=x;u.y=y;u.z=z;
					//make_fog(u,1);//巢穴区全部是雾 
					make_mvb(u,3,3,3);
					//make_dart(u,30,0); 
					make_ppt(u,20,1);
					make_smoke_bomb(u,30,5);
					make_food(u,40,5);
					//make_wpn_energy_edc(u,30,11,50);
					make_weapon(u,30,10,50);
				}
		make_TNT();
		make_treasure();
		make_candle();
		make_water();
		make_magma();
	}
	void print_initial_picture(){ 
	    //此前要清屏 
		logMessage("print_initial_picture"); 
		screen_center=position_3Dto2D(player1.pos);
		game_time=lst_see_time=0;
		player_calculate_vision2();
		player_calculate_vision1(player1.d2);
		while(!pos_in_sight.empty()){
			position_3D u=pos_in_sight.front();pos_in_sight.pop();
			print_game_map_pos(u,1);
			position_2D spos=position_3Dtoscr(u);
			pos_lst_sight.push(spos);
		}
		
		formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0),"生命值："+repeat_str("★",player1.vts.lfin.life/10.0)+"           ");
		formatted_output(1,vital_signs_area,50,0,MMPP(-100,360,0,120),"体力值：100% ");
		formatted_output(1,vital_signs_area,80,0,MMPP(-100,360,0,360),"特殊效果：1.透视0层，持续0秒");
		formatted_output(1,vital_signs_area,160,0,MMPP(-100,360,0,60),"击杀数：0");
		
		player1.items.print1();player1.items.print2();player1.items.print3();
		player1.items.wpn_print1();player1.items.wpn_print2();player1.items.wpn_print3();
	}//改了这里的输出位置下面也要改
void initial(){//游戏初始化
	//此前不要清屏 
	logMessage("initial()",2); 
	ifstream fin;
	if(game_map_from==FILE_MODEL){//文件读取预设地图 
		fin.open("map.in",ios::in);
		if(!fin.is_open()){
			cout<<"文件错误！"<<"\n";
			exit(0);
		}
		fin>>length>>width>>height;
	}
	
	all_assigned();
	
	if(game_map_from==FILE_MODEL){//文件读取预设地图 
		for(int z=1;z<=height*2;z++)
			for(int y=1;y<=width;y++)
				for(int x=1;x<=length;x++)
					fin>>game_map[x][y][z].maze;
		fin.close();
	}
	 
	make_map();
	make_player();
	//print_maze();
	make_enemy();
	//print_maze();
	make_thing();
	//print_maze();
	//print_game_map();
	//SLEEP(10000);
	CLEAR();
	print_initial_picture();
}			
	void assigned(){
		logMessage("assigned()",2);
		player1.scr.time_spent=game_time;
		//更新用时 
		while(!Q.empty()) Q.pop();
		pos_backup.clear();
		for(int i=0;i<4;i++) cnt_visible[i]=360;
		memset(occlusion,0,sizeof(occlusion));
		player1.d1_change=player1.d2_change=player1.move=player1.vts.lfin.change=player1.vts.stg.change
		=player1.ud_change=player1.ak_change=player1.flash=player1.use_weapon=player1.pull_thing
		=player1.enemy_move
		=player1.items.num_change=player1.items.sn_change=player1.items.il_change
		=player1.items.wpn.sw_change=player1.items.wpn.data_change=player1.items.wpn.mode_change
		=player1.items.rmv.dl_change
		=player1.items.flt.change
		=player1.scr.kc.change
		=player1.spe.xry.change
		=player1.spe.wks.change=player1.spe.vtg.change=player1.spe.bds.change=player1.spe.mts.change=player1.spe.cfs.change
		=game_flag["游戏暂停/继续"]=game_flag["光照更新"]
		=game_flag["敌人被玩家攻击"]=game_flag["清除尸体"]=game_flag["鬼隐身"]=game_flag["吸血"]=game_flag["上下楼被挡"] 
		=game_flag["玩家矛改变位置"]=game_flag["回旋镖变化"]=game_flag["蛛丝变化"]=game_flag["物品损坏"]
		=game_flag["推桌椅"]=game_flag["拉"]=game_flag["飞"]=game_flag["推noply"]
		=game_flag["测试专用"]
		=false;
	}
	void pause(){
		logMessage("pause",2);
		if(!game_pause) return;
		position_2D scr_mouse=pos_mouse();//鼠标的屏幕位置 
		char getch=_getch();
		if(getch!=PRESS_KEY_ESC){//游戏暂停->游戏继续
			game_pause=false;
			game_flag["游戏暂停/继续"]=true;
		}
		else if(KEY_DOWN(VK_LBUTTON)&&!game_flag["鼠标单击"]){//鼠标左键
			game_flag["鼠标单击"]=true;
			if(scr_mouse.x<=20){//游戏继续 
				game_pause=false;
				game_flag["游戏暂停/继续"]=true;
			}
		}
		else game_flag["鼠标单击"]=false;
		SLEEP(100);//防止多次点击（暂停后game_time不变，无法使用game_timer） 
	}
			void player_reduce_blood(double sub,PII from){
				vital_signs &vts=player1.vts;
				life_injury &lfin=vts.lfin;
				if(lfin.life<=0) return;//已经死了就不管了 
				score &scr=player1.scr;
				if(sub<=0||sub>0&&lfin.canhurt()) lfin.life-=sub;//改变血量
				player1.flash=true;
				if(sub>=0&&lfin.canhurt()){ 
					lfin.hurt+=sub;//伤害累计 
					lfin.lst_hurt=sub;
					scr.hurt_times++;//受伤次数 
					lfin.change=2;//扣血 
					if(from!=MP(0,-1)) lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
					player1.color=2;
					game_timer["玩家图标闪烁"]=game_time+100;
				}
				else{
					lfin.recovery-=sub;//回血累计 
					lfin.change=1;//回血 
					player1.color=1;
					game_timer["玩家图标闪烁"]=game_time+1000;
				}
				if(lfin.life<=0){//防止出错 
					message_box.push(MP(from,MP(PLAYER,-1)));//击杀信息 
					lfin.life=0;
					game_end=true;game_success=false;
				}
			}
			void player_add_stg(double add){
				player1.vts.stg.physical_strength+=add;
				limit_double(player1.vts.stg.physical_strength,1,100);//不要越界 
				player1.vts.stg.change=true;
			}
			void hurt_enemy(MAP &POS){
				if(POS.player_enemy!=NOBODY&&POS.emy.id>=0){
					int id=POS.emy.id;
					if(POS.player_enemy==BUG) Qbug_hurt.push(id);
					else if(POS.player_enemy==SPIDER) Qspider_hurt.push(id);
					else if(POS.player_enemy==GHOST) Qghost_hurt.push(id);
				}
			}
			bool bug_move_away(int id){//改变位置重生（false：没巢穴了无法复活） 
				if(id<0||id>=bugs.size()) return false;
				bug &bg=bugs[id];
				bg.update=false;
				if(pos_in_nest.size()==0){//没有巢穴了 
					bg.change_pos=false;//无法复活 
					return false;
				}
				int k=RAND(pos_in_nest.size()-1,0);
				position_3D npos=pos_in_nest[k];
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				if(space_here(npos)&&nobody_here(npos)&&!NPOS.fcmv.lock&&NPOS.emy.id==-1){
					bg.pos=npos;
					NPOS.player_enemy=BUG;NPOS.emy.id=id;
					bg.lfin.init(5);
					bg.vlc.speed++;bg.vlc.vt();
					bg.enter_nest=true;
					bg.change_pos=false;
				}
				else bg.change_pos=true;
				return true; 
			}
			void bug_reduce_blood(int id,double hurt,PII from,bool push=1){
				if(id<0||id>=bugs.size()) return;
				bug &bg=bugs[id];
				if(bg.lfin.life<=0) return;//已经死了就不再扣血了 
				MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				thing &THING=POS.things;
				life_injury &lfin=bg.lfin;
				if(hurt<=0||hurt>0&&lfin.canhurt()) lfin.life-=hurt;
				if(hurt>0&&lfin.canhurt()){
					lfin.change=2;
					lfin.hurt+=hurt;
					lfin.lst_hurt=hurt;
					lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
				} 
				else lfin.change=1;
				if(push) 
					Qbug_hurt.push(id);
				if(POS.ist.player==lst_see_time){
					game_flag["敌人被玩家攻击"]=true; 
					pos_change.insert(bg.pos);
				}
			}
				void spider_update_leg(position_3D pos,int k,int id){//位置为pos的蜘蛛附肢屏幕更新（只要蜘蛛位置、方向改变就调用） 
					if(id<0) return;
					for(int i=0;i<8;i++){//之前的附肢在屏幕上更新 
						position_3D v=dtp3(pos,i,8);
						MAP &VPOS=game_map[v.x][v.y][v.z];
						spider_leg &slg=VPOS.things.slg;
						slg.num+=k;//不管这里有没有附肢都加减 
						if(k>=0&&(id<0||id>=spiders.size()?1:spiders[id].kind==2)) slg.id=id;
						else slg.id=-1;//蜘蛛离开要重新判断附肢 
						if(!wall_here(v)&&VPOS.ist.player==lst_see_time){
							player1.enemy_move=true;
							pos_change.insert(v);
							game_flag["遮挡生物移动"]=true; 
						}
					}
				}
			void spider_move_away(int id){//改变位置重生 
				if(id<0||id>=spiders.size()) return;
				spider &sr=spiders[id];
				sr.update=false;
				position_3D npos;
				npos.x=RAND(length-1,1);npos.y=RAND(width-1,1);npos.z=RAND(height,1);
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				if((space_here(npos)||stair_here(npos))&&nobody_here(npos)&&!NPOS.fcmv.lock&&NPOS.emy.id==-1){
					sr.pos=npos;
					NPOS.player_enemy=SPIDER;NPOS.emy.id=id;
					sr.bir=sr.pos;
					sr.lfin.init(20);//与make_spider保持相同 
					sr.vlc.speed+=1.2;sr.vlc.vt();
					sr.change_pos=false;
					sr.update=true;
					spider_update_leg(sr.pos,1,id);//重生后标记附肢 
					NPOS.things.snt.endurance=100;//出生点留下蜘蛛网 
				}
				else sr.change_pos=true;
			}
			void spider_reduce_blood(int id,double hurt,PII from){
				if(id<0||id>=spiders.size()) return;
				spider &sr=spiders[id];
				if(sr.lfin.life<=0) return;//已经死了就不管了 
				MAP &POS=game_map[sr.pos.x][sr.pos.y][sr.pos.z];
				thing &THING=POS.things;
				life_injury &lfin=sr.lfin;
				if(hurt<=0||hurt>0&&lfin.canhurt()) lfin.life-=hurt;
				if(hurt>0&&lfin.canhurt()){
					lfin.change=2;
					lfin.hurt+=hurt;
					lfin.lst_hurt=hurt;
					lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
				} 
				else lfin.change=1;
				if(POS.ist.player==lst_see_time){
					game_flag["敌人被玩家攻击"]=true; 
					pos_change.insert(sr.pos);
				}
			}
			void ghost_move_away(int id){//改变位置重生 
				logMessage("ghost_move_away id="+int_to_str(id)); 
				if(id<0||id>=ghosts.size()) return;
				ghost &gt=ghosts[id];
				if(gt.lfin.life<=0) return;//已经死了就不管了 
				gt.update=false;
				position_3D npos;
				npos.x=RAND(length-1,1);npos.y=RAND(width-1,1);npos.z=RAND(height,1);
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				if(space_here(npos)&&nobody_here(npos)&&!NPOS.fcmv.lock&&NPOS.ist.player!=lst_see_time&&NPOS.emy.id==-1){
					gt.pos=npos;
					NPOS.player_enemy=GHOST;NPOS.emy.id=id;
					gt.lfin.init(30);//与make_ghost保持相同 
					gt.vlc.speed+=0.5;gt.vlc.vt();
					gt.change_pos=false;
					gt.update=true;
					gt.spe.init();//特殊效果全部清空 
					special_attribute &spat=gt.spat;
					switch(gt.spat.attack){
						case INSTANT:
							spat.ins.p=min(100,spat.ins.p+10);
							break;
					}
					switch(gt.spat.defense){
						case EVADE:
							spat.eva.k=min(100,spat.eva.k+10);
							break;
						case ROCK:
							spat.rck.k*=0.5;
							break;
						case SHIELD://=上面2个加起来
							spat.eva.k=min(100,spat.eva.k+10); 
							spat.rck.k*=0.5;
							break;
					}
					//技能鬼实力不断加强
					gt.attack_time=gt.attack_time-RAND_DOUBLE(0.05,0.0);//不断减小 
					limit_double(gt.attack_time,0.0,0.5); 
				}
				else gt.change_pos=true;
			}
			void ghost_reduce_blood(int id,double hurt,PII from){
				if(id<0||id>=ghosts.size()) return;
				ghost &gt=ghosts[id];
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				thing &THING=POS.things;
				life_injury &lfin=gt.lfin;
				if(hurt<=0||hurt>0&&lfin.canhurt()) lfin.life-=hurt;
				if(hurt>0&&lfin.canhurt()){//受到伤害且没有免除 
					lfin.change=2;
					lfin.hurt+=hurt;
					lfin.lst_hurt=hurt;
					lfin.last_injury_from=from;
					lfin.last_injury_time=game_time;
				} 
				else lfin.change=1;
				if(POS.ist.player==lst_see_time){
					game_flag["敌人被玩家攻击"]=true; 
					pos_change.insert(gt.pos);
				}
			}
			void living_things_reduce_blood(position_3D pos,double hurt,int kind,PII from){//所有生物扣血 
				MAP &POS=game_map[pos.x][pos.y][pos.z]; 
				if(POS.player_enemy==PLAYER) player_reduce_blood(hurt,from);
				else if(POS.player_enemy==BUG&&POS.emy.id>=0&&POS.emy.id<bugs.size())
					bug_reduce_blood(POS.emy.id,hurt,from);
				else if(POS.player_enemy==SPIDER&&POS.emy.id>=0&&POS.emy.id<spiders.size())
					spider_reduce_blood(POS.emy.id,hurt,from);
				else if(POS.player_enemy==GHOST&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){
					ghost &gt=ghosts[POS.emy.id];
					if(kind==1&&gt.spat.defense==ROCK||gt.spat.defense==SHIELD) ghost_reduce_blood(POS.emy.id,hurt*gt.spat.rck.k,from);
					//攻击时技能减伤 
					else ghost_reduce_blood(POS.emy.id,hurt,from);
				}
			}
			void player_kill_reward(position_3D u,int kill,special_attribute spat){
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				int kind,effect;
				switch(kill){
					case GHOST:
						//直接生成食物补给 
						if(spat.attack&&spat.defense){//双技能的鬼 
							kind=ADDS;//只有生命回复 
							effect=RAND(spat.attack+spat.defense,spat.defense);//上限为攻击+防御，下限为防御，有概率出稀有道具 
							limit_int(effect,1,3);//限制范围
						}
						else if(!spat.attack&&!spat.defense){//无技能的鬼 
							kind=RAND(ADDL,RAND(ADDL,ADDS));//大部分体力回复 
							effect=RAND(2,1);//等级较低 
						}
						else{//单技能的鬼 
							kind=RAND(ADDL,ADDS);//有生命回复或体力回复
							effect=log2(RAND(RAND(1<<3,1<<1),1<<1));//高等级的较为稀有 
						}
						food_pile &FOOD=THING.foods;
						pos_make_food(u,kind,effect);//FOOD.make(kind,effect);
						break;
				}
			}
			void player_move_update(position_3D npos);
				void move_box_thing(position_3D u,position_3D v){//u->v u[box]
					//把箱子里装的东西移走 
					MAP &POS=game_map[u.x][u.y][u.z];
			   		thing &THING=POS.things;
					MAP &NPOS=game_map[v.x][v.y][v.z];
			   		thing &NTHING=NPOS.things;
			   		/*
					for(int i=0;i<KINDS_OF_FOOD;i++)
						for(int j=0;j<EFFECT_OF_FOOD;j++)
							NTHING.foods.food_cnt[i][j]+=THING.foods.food_cnt[i][j];
					THING.foods.init();
					swap(THING.ppt,NTHING.ppt);
					swap(THING.smb,NTHING.smb);*/
					swap(THING.fir,NTHING.fir);
					//移动食物、道具 
					
					swap(POS.player_enemy,NPOS.player_enemy);
					swap(POS.emy.id,NPOS.emy.id);
					int id=NPOS.emy.id;
					//此时已移动好生物 
					if(NPOS.player_enemy==BUG&&id>=0&&id<bugs.size()){//虫 
						bug &bg=bugs[id];
						bg.pos=v;
					}
					else if(NPOS.player_enemy==GHOST&&id>=0&&id<ghosts.size()){//鬼 
						ghost &gh=ghosts[id];
						gh.pos=v;
					}
					else if(NPOS.player_enemy==SPIDER&&id>=0&&id<spiders.size()){//蜘蛛 
						spider &sr=spiders[id];
						spider_update_leg(sr.pos,-1,id);
						sr.pos=v;
						spider_update_leg(v,1,id);
					}
					else if(NPOS.player_enemy==PLAYER){//玩家
						player1.items.rmv.select=pos000;
						player_move_update(v);//好像有点套娃？ 
					} 
					//移动生物 
				}
				void vibrate_spider_net(position_3D pos,int k){//振动蜘蛛网 
					map<position_3D,bool> mp;//vst 
					while(!Q.empty()) Q.pop();
					game_map[pos.x][pos.y][pos.z].things.snt.mxk(k);
					mp[pos]=1;
					Q.push(pos);
					while(!Q.empty()){
						position_3D u=Q.front();Q.pop();
					   	MAP &POS=game_map[u.x][u.y][u.z];
					   	thing &THING=POS.things;
					   	int uk=THING.snt.nowk();
						if(uk<=1000) continue;//再减就是0了 
						for(int i=0;i<=4;i++){//0~3+4楼梯 
							position_3D v;
							if(i<4) v=dtp3(u,i,4);//正常四方向传导 
							else if(stair_here(u)){//楼梯 
								v=u;
							   	if(upstair_here(u)) v.z++;
						   		else v.z--;
							}
							else break;//没有楼梯就算了 
						   	MAP &NPOS=game_map[v.x][v.y][v.z];
						   	thing &NTHING=NPOS.things;
						   	if(mp[v]) continue;//访问过了 
						   	if(!NTHING.snt.exist()) continue;//没有蜘蛛网就算了 
						   	if(wall_here(v)||exit_here(v)||door_here(v,0)||door_here(v,2)) continue;//传导不了 
						   	int vk=NTHING.snt.nowk(),nxtk=uk-1000;
						   	if(vk>=nxtk) continue;//没有更新就不用在此处拓展了 
						   	NTHING.snt.mxk(nxtk);//随距离衰减后的新振幅
						   	mp[v]=1;
						   	Q.push(v);
						}
					}
				}
			void player_move_update(position_3D npos){//玩家移动的附加事项（处理拉动的物品、振动蛛网） 
				removable &rmv=player1.items.rmv;
				position_3D u=rmv.select,v=player1.pos;
			   	MAP &POS=game_map[v.x][v.y][v.z];
			   	thing &THING=POS.things;
			   	MAP &NPOS=game_map[npos.x][npos.y][npos.z];
			   	thing &NTHING=NPOS.things;
				if(u!=pos000){//rmv.deal_kind==PULL&&
					if((u==npos?0:!NTHING.mvb.exist)&&(u==v?0:!THING.mvb.exist||u==npos)){//可以拉动物品
						MAP &SPOS=game_map[u.x][u.y][u.z];
						thing &STHING=SPOS.things;
						if(STHING.mvb.exist){
							if(THING.mvb.kind==BOX&&POS.update_light()) pos_affect_light.push(v);//箱子动了更新光照 
							if(STHING.mvb.kind==BOX&&SPOS.update_light()) pos_affect_light.push(u);//箱子动了更新光照 
							if(box_here(u)){
								move_box_thing(u,v);
							}
							swap(THING.mvb,STHING.mvb);//拉动
							int k=STHING.mvb.kind;
							if(k==CHAIR||k==DESK||k==BOX)
								MUSIC("推桌椅2.wav",1);//拉动椅子/桌子/箱子的声音 
						}
						player1.items.rmv.select=v;
					}
					else if(u!=npos&&u!=v&&!NTHING.mvb.exist) player1.items.rmv.select=pos000;//没有走到选中的物品上
				}
				if(NTHING.snt.exist()) vibrate_spider_net(npos,15*1000);//最多持续15秒 
				if(MHT_DIST(screen_center.x,screen_center.y,npos.x,npos.y)==1) screen_center=position_3Dto2D(npos);
				//距离为1直接切换，否则交给player_sight_update 
				player1.spe.dst.time=game_time;
				player1.pos=npos;//更新位置 
				player1.move=true;
				game_timer["玩家上次移动"]=game_time;
			}
			bool push_thing(position_3D pos,int dir,int kind){
			//把pos位置的可移动物品向dir方向推（可作用于箱子、生物等），返回是否成功推动 
			//kind=0：只返回值无任何效果 1：造成推动附加效果（比如撞碎东西），返回值为真就推动 
			   	MAP &POS=game_map[pos.x][pos.y][pos.z];
			   	thing &THING=POS.things;
				mirror &MIRRORS=THING.mirrors;
				if(mirror_here(pos)) dir=mirror_relect(MIRRORS.dir,MIRRORS.side,dir);//实际方向 
				if(dir==-1) return false;
				position_3D u=dtp3(pos,dir,4);//pos->u
			   	MAP &NPOS=game_map[u.x][u.y][u.z];
			   	thing &NTHING=NPOS.things;
				bool nothing=normv_here(pos),nobody=nobody_here(pos);
			   	if(nothing&&nobody) return true;//现在的位置是空位可以推动
			   	if(!pos_in_area2(u.x,u.y,1,1,length,width,2)//超出地图范围 
				||!mvb_through(u,dir)){//障碍
					if(kind==1){//检查附加效果
						bool effect=0;
						if(mirror_here(u)){//撞到镜子 
							NTHING.mirrors.damage(30);
							effect=1;
						}
					 	else if(window_here(u)){//撞到玻璃 
							NTHING.windows.damage(5,u);
							effect=1;
						}
						if(effect&&NPOS.ist.player==lst_see_time) player_add_stg(-5);//有附加效果消耗体力 
					}
				 	return false;//推不了了 
				}
			   	if(!push_thing(u,dir,kind)) return false;//后续推不动就不动了 
			   	if(kind==0) return true;//只返回值
			   	if(player1.items.rmv.select==pos) player1.items.rmv.select=pos000;
			   	NTHING.snt.addedc(THING.snt.endurance/2,u);
			   	THING.snt.endurance/=2;//分一半到下一个位置 
				if(!nothing){//推动物品
					swap(NTHING.mvb,THING.mvb);
					if(box_here(u)){//THING->NTHING 已经推过去了 
						move_box_thing(pos,u);
					}
					if(THING.mvb.kind==BOX&&POS.update_light()) pos_affect_light.push(pos);//箱子动了更新光照 
					if(NTHING.mvb.kind==BOX&&NPOS.update_light()) pos_affect_light.push(u);//箱子动了更新光照 
					if((NTHING.mvb.kind==CHAIR||NTHING.mvb.kind==DESK||NTHING.mvb.kind==BOX)
					&&MHT_DIST(u.x,u.y,player1.pos.x,player1.pos.y)<=10&&u.z==player1.pos.z)
						MUSIC("推桌椅2.wav",1);//推动椅子/桌子/箱子的声音 
					if(NPOS.ist.player==lst_see_time){
						game_flag["推桌椅"]=true;
						pos_change.insert(pos); 
					}
				}
				nobody=nobody_here(pos);//防止移动物体顺带着把生物移走了 
				if(!nobody){//推开生物
					int id=POS.emy.id;
					if(POS.player_enemy==BUG&&id>=0&&id<bugs.size()){//虫 
						bug &bg=bugs[id];
						bg.pos=u;
					}
					else if(POS.player_enemy==GHOST&&id>=0&&id<ghosts.size()){//鬼 
						ghost &gh=ghosts[id];
						gh.pos=u;
					}
					else if(POS.player_enemy==SPIDER&&id>=0&&id<spiders.size()){//蜘蛛 
						spider &sr=spiders[id];
						spider_update_leg(sr.pos,-1,id);
						sr.pos=u;
						spider_update_leg(u,1,id);
					}
					else if(POS.player_enemy==PLAYER){//玩家
						player1.items.rmv.select=pos000;
						player_move_update(u);//好像有点套娃？ 
					} 
					swap(NPOS.player_enemy,POS.player_enemy);
					swap(NPOS.emy.id,POS.emy.id);
				}
				game_timer["鬼"]++;
				return true;
			}
			void throw_thing(position_3D pos,double speed,double hurt,int angle,pair<int,int> from){
			//给pos的物体speed的加速度，方向angle，来源from 
			//扔东西的准备工作（更新地图+加入队列+撞击扣血） 
			//hurt：伤害系数 
				MAP &POS=game_map[pos.x][pos.y][pos.z]; 
				force_move &FCMV=POS.fcmv;
				flying_mvb fmb;
				fmb.init(pos);//新的移动物品 
				if(!FCMV.lock) mvbs.push(fmb);//没有在队列里就放入队列
				FCMV.init2(speed,angle,from);
				if(!nobody_here2(pos)&&fabs(hurt)>eps)//踢/撞飞生物 
					living_things_reduce_blood(pos,hurt*speed,0.5,from);
				//formatted_output(1,vital_signs_area,1,17,MMPP(0,360,-100,360),double_to_str(vx.speed,0,3));
				//formatted_output(1,vital_signs_area,1,18,MMPP(0,360,-100,360),double_to_str(vy.speed,0,3));
			}
			void update_being(position_3D pos){//使某处生物开始更新 
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				if(POS.player_enemy==BUG&&POS.emy.id>=0&&POS.emy.id<bugs.size()){//能看到这个虫子
					int id=POS.emy.id;
					bug &bg=bugs[id];
					if(!bg.update){
						Qbug.push(id);
						bg.update=true;
					}
				}
				else if(POS.player_enemy==SPIDER&&POS.emy.id>=0&&POS.emy.id<spiders.size()){//能看到这个蜘蛛
					int id=POS.emy.id;
					spider &sr=spiders[id];
					if(!sr.update){
						Qspider.push(id);
						sr.update=true;
					}
				}
				else if(POS.player_enemy==GHOST&&POS.emy.id>=0&&POS.emy.id<ghosts.size()){//能看到这个鬼
					int id=POS.emy.id;
					ghost &gt=ghosts[id];
					if(!gt.update){
						Qghost.push(id);
						gt.update=true;
					}
				}
				if(spider_leg_here(pos)&&POS.things.slg.id>=0&&POS.things.slg.id<=spiders.size()){//B型蜘蛛附肢体（分开考虑） 
					int id=POS.things.slg.id;
					spider &sr=spiders[id];
					if(!sr.update){
						Qspider.push(id);
						sr.update=true;
					}
				} 
			}
		void deal_bug(){
			logMessage("deal_bug"); 
			int bug_num=Qbug_hurt.size();
			while(bug_num>0){
				bug_num--;
				int id=Qbug_hurt.front();Qbug_hurt.pop();
				if(id<0||id>=bugs.size()) continue;
				bug &bg=bugs[id];
				life_injury &lfin=bg.lfin; 
				MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				string s="虫子"+int_to_str(id);
				if(bg.lfin.life>0&&!bg.update){//受伤更新 
					Qbug.push(id);
					bg.update=true;
				}
				thing &THING=POS.things;
				if(THING.lsr.exist||THING.drt.exist1()
				||(THING.spr.exist&&game_timer[s+"被矛刺中"]<=game_time)//1000毫秒延时已到 
				){
				    if(THING.spr.exist){
						game_timer[s+"被矛刺中"]=game_time+1000;//每秒计算一次伤害 
						object_addE(player1.items.wpn.primary,-bg.vlc.speed);
					}
					else player1.scr.shoot_hit_times++;
					bug_reduce_blood(id,5,MP(PLAYER,-1),0);
				}
				if(POS.fcmv.lock){
					if(POS.fcmv.speed()>5&&game_timer[s+"被砸中"]<=game_time){
						bug_reduce_blood(id,1,POS.fcmv.from,0);
						game_timer[s+"被砸中"]=game_time+500;
					}
				}
				if(lfin.life<=0){//清除痕迹 bug_here(bg.pos)&&POS.emy.id==id&&
					if(POS.ist.player==lst_see_time){
						game_flag["敌人被玩家攻击"]=true; 
						pos_change.insert(bg.pos);
						pos_dead.push(bg.pos);
					}
					if(bg.pos!=pos000){
						message_box.push(MP(lfin.last_injury_from,MP(BUG,id)));//击杀信息 
						bg.pos=pos000;
						if(lfin.last_injury_from.first==PLAYER) player1.scr.kc.update(1,BUG);
					}
					POS.fcmv.lock=false;//game_flag["飞"]=true;pos_change.insert(bg.pos);//解除锁定 
					POS.emy.dead=true;POS.emy.body_disapp=game_time+200;
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					/*别复活了 
					if(bug_move_away(id)){//如果一次复活就成功就不劳烦下面那个循环了 
						Qbug.push(id);
						bg.update=true;
					}*/
					//continue; 
				}
				game_timer["虫"]++;
			}//循环1：生命更新循环 
			bug_num=Qbug.size();
			while(bug_num>0){
				bug_num--;
				int id=Qbug.top();Qbug.pop();
				if(id<0||id>=bugs.size()) continue;
				bug &bg=bugs[id];
				MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				string s="虫子"+int_to_str(id);
				if(bg.lfin.life<=0) continue;//别重生了
				/* 别重生了
				if(bg.change_pos){//重生中 
					game_timer["虫"]++;
					
					if(bug_move_away(id)) Qbug.push(id);//没有巢穴可用就不要再更新了
					continue; 
				}*/
				if(MHT_DIST2(bg.pos.x,bg.pos.y,(bg.pos.z>height?bg.pos.z-height:bg.pos.z),player1.pos.x,player1.pos.y,player1.pos.z)>100
				&&POS.ist.player<lst_see_time)//离玩家距离超过100格（注意巢穴高度）且玩家看不到 
					bg.update=false;//停止更新 
				if(!bg.update) continue;
				Qbug.push(id);
				thing &THING=POS.things;
				if(game_timer[s]>game_time)//时间没到不更新 
					break;
				game_timer[s]=game_time+bg.vlc.wait_time; 
				game_timer["虫"]++;
				if(!(THING.lsr.exist||THING.drt.exist1()||THING.spr.exist)
				&&game_timer[s+"被砸中"]<=game_time){
				//要和上面一一对应 
					if(bg.lfin.change!=0&&POS.ist.player==lst_see_time){
						game_flag["敌人被玩家攻击"]=true; 
						pos_change.insert(bg.pos);
					}
					bg.lfin.change=0;
				}
				THING.snt.addedc(-2,bg.pos);//损坏蜘蛛网 
				if(THING.spr.exist||POS.fcmv.lock||THING.snt.endurance>25){
					continue;//被矛刺中无法移动和攻击 
				}
				position_3D npos=bg.pos;
				int d=bg.d;
				if(POS.emy.phm.disapp>game_time&&POS.emy.phm.id!=id) d=POS.emy.phm.d;//有信息素 
				else if(d==4) d=RAND(3,0);//上下楼/进出巢穴口后随机设置方向 
				//bool special_move=false;
				if(stair_here(npos)&&(bg.lst_ud+5000<=game_time||d==4)){//上下楼 
					if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
					else npos.z--;
					bg.lst_ud=game_time;//special_move=true;
					d=4;
				}
				else if(POS.things.nst.exist&&(bg.enter_nest+5000<=game_time||d==4)){//进巢穴口
					position_3D npos2=POS.things.nst.to;
					MAP &POS2=game_map[npos2.x][npos2.y][npos2.z];
					npos.x=npos2.x;npos.y=npos2.y;npos.z=npos2.z;//移动到对应的巢穴口
					bg.enter_nest=game_time;//special_move=true;
					d=4;
				}
				else{//普通移动 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				if(!(NTHING.spr.exist||NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
				||closed_box_here(bg.pos,d)
				||NTHING.lsr.exist||NPOS.fcmv.lock)
				&&(stair_here(npos)||space_here(npos))&&nobody_here(npos)){
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					if(POS.emy.phm.disapp<=game_time||POS.emy.phm.d!=d){//留下信息素
						POS.emy.phm.disapp=game_time+5000;//持续时间5s 
						POS.emy.phm.id=id;
						POS.emy.phm.d=d; 
					}
					NPOS.player_enemy=BUG;NPOS.emy.id=id;
					if(POS.ist.player==lst_see_time&&bg.pos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(bg.pos);
						if(THING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["帘子摇动"]=true;
							if(POS.update_light()) pos_affect_light.push(bg.pos);//帘子动了光照更新 
						}
					}
					if(NPOS.ist.player==lst_see_time&&npos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(npos);
						if(NTHING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["帘子摇动"]=true;
							if(NPOS.update_light()) pos_affect_light.push(npos);//帘子动了光照更新 
						}
					}
					if(NTHING.snt.exist()) vibrate_spider_net(npos,10*1000);
					
					//繁殖 
					if(bg.pos.z>height//仅在巢穴内繁殖 
					&&space_here(bg.pos)&&nobody_here(bg.pos)&&!dead_here(bg.pos)&&empty_here(bg.pos)&&!POS.fcmv.lock
					//空地，没别的生物，没东西，不会被撞飞 
					//&&!(THING.lsr.exist||THING.spr.exist||THING.drt.exist())
					//&&count_around_pos(bg.pos,4,wall_here)==3//在死胡同里繁殖 
					&&count_around_pos(bg.pos,4,nobody_here)>=2//别太挤了 
					&&bg.lfin.life>=6//&&RAND_BOOL(20)&&RAND_BOOL(5)//设定概率 
					){
						pos_make_bug(bg.pos,bg.vlc.speed+1,1);
						bug_reduce_blood(id,1,MP(BUG,id));//消耗生命繁殖 
					}
					
					bg.pos=npos;//重置位置 
					if(!stair_here(npos)) bg.lst_ud=game_time-5000;
					if(!NPOS.things.nst.exist) bg.enter_nest=game_time-5000;
				}
				else{
					if(d==4&&!box_here(bg.pos)||d<4&&!closed_box_here(bg.pos,d)){
						int door_d=(d==4?0:turn(d,TURN_BACK,4,8));//箱门 
						if(NPOS.player_enemy==PLAYER&&(d==4?!box_here(bg.pos):!door_here(npos,2)&&!closed_box_here(npos,door_d))){
							player_reduce_blood(10.0/bg.vlc.speed,MP(BUG,id));
							bug_reduce_blood(id,-1,MP(BUG,id));//虫子吸血
							if(POS.ist.player==lst_see_time){
								game_flag["敌人被玩家攻击"]=true; 
								pos_change.insert(bg.pos);
							}
						}
						else if(NTHING.mvb.exist&&(NTHING.mvb.kind==BALL||NTHING.mvb.kind==CHAIR)&&!NPOS.fcmv.lock){//推动足球/椅子 
							position_3D v=dtp3(npos,d<4?d:RAND(3,0),4);
							MAP &VPOS=game_map[v.x][v.y][v.z];
							thing &VTHING=VPOS.things;
							if(!(VTHING.spr.exist||VTHING.mvb.exist||door_here(v,0)||door_here(v,2)||VTHING.hdr.exist)
							&&(stair_here(v)||space_here(v))&&nobody_here(v)){//只推一个
								swap(VTHING.mvb,NTHING.mvb); 
								if(NPOS.ist.player==lst_see_time){
									game_flag["推noply"]=true;
									pos_change.insert(npos);
								}
								if(VPOS.ist.player==lst_see_time){
									game_flag["推noply"]=true;
									pos_change.insert(v);
								}
							}
						}
						else if(enemy_here(npos)){
							update_being(npos);
							int id=NPOS.emy.id;
							if(ghost_here(npos)&&!door_here(npos,2)
							&&(id<0||id>=ghosts.size()?1:ghosts[id].spat.defense!=ROCK&&ghosts[id].spat.defense!=SHIELD)){
								ghost_reduce_blood(id,10.0/bg.vlc.speed,MP(BUG,id));//攻击不能石化的鬼
								bug_reduce_blood(id,-1,MP(BUG,id));//虫子吸血 
								if(NPOS.ist.player==lst_see_time){
									game_flag["敌人被玩家攻击"]=true;//借用一下 
									pos_change.insert(bg.pos);
								}
							}
							if(id!=-1&&spider_body_here(npos)&&THING.snt.endurance<50){//网不够时可攻击蜘蛛
								spider_reduce_blood(id,10.0/bg.vlc.speed,MP(BUG,id)); 
								bug_reduce_blood(id,-1,MP(BUG,id));//虫子吸血 
								if(NPOS.ist.player==lst_see_time){
									game_flag["敌人被玩家攻击"]=true;//借用一下 
									pos_change.insert(bg.pos);
								}
							}
						}
						int tmp=count_around_pos(npos,4,space_here);
						if(npos.z>height&&pos_in_area2(npos.x,npos.y,1,1,length,width,2)
						&&wall_here(npos)&&tmp<3
						&&(tmp<=1?RAND_BOOL(15):RAND_BOOL(5))){//虫子挖巢穴 
							NPOS.maze=SPACE;
							pos_in_nest.push_back(npos);//新增巢穴里的重生点 
							position_3D npos2=npos;npos2.z-=height;
							MAP &NPOS2=game_map[npos2.x][npos2.y][npos2.z];
							if(NPOS.ist.player==lst_see_time) game_flag["虫子挖地道"]=true;
							if((wall_here(npos2)||space_here(npos2))&&count_around_pos(npos2,4,space_here)<=2&&RAND_BOOL(80)){//生成巢穴口
								if(!light_through(npos2)&&NPOS2.ist.player==lst_see_time) game_flag["虫子挖地道"]=true;
								NPOS2.maze=SPACE;NPOS2.things.windows.init();//有窗户就打碎 
								bug_nest bns;
								bns.init(npos2);
								bug_nests.push_back(bns);
								int id=int(bug_nests.size())-1;
								nest &NST=NPOS.things.nst,&NST2=NPOS2.things.nst; 
								NST.exist=NST2.exist=true;NST.id=NST2.id=id;
								NST.to=npos2;NST2.to=npos; 
							}
						}
					}
					if(d==4) d=RAND(3,0);
					else if(RAND_BOOL(50)) d=turn(d,TURN_RIGHT,4,9);
					else d=turn(d,TURN_LEFT,4,10);
					bg.d=d;
				}
			}//循环2：主体循环 
		}
				void spider_decision_update(vector<int> &vd,vector<double> &vrate,int &d,int &i,position_3D bir,position_3D u,position_3D v){
					MAP &POS=game_map[u.x][u.y][u.z];
					thing &THING=POS.things;
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					double rate=1;
					int uk=THING.snt.nowk(),vk=NTHING.snt.nowk(),disu=MHT_DIST_p3(bir,u),disv=MHT_DIST_p3(bir,v);
					if(disv<disu) rate=5;//靠近出生点移动概率大 
					//if(dis>0) rate*=2.0/dis;//离出生点越远概率越小（防止/0）
					//else rate*=2; 
					if(NTHING.snt.exist()){
						//rate*=sqrt((50-abs(50-NTHING.snt.endurance))/25+1);//防止*0
						if(vk>uk) rate*=pow((vk-uk)/1000+1,4);//防止*0 
					}
					if(!nobody_here2(v)) rate*=3;//更大概率攻击其他生物
					if(door_here(v,0)||door_here(v,2)) rate*=0.5;//更小概率开门 
					//if(d==i) rate*=1.5;//较大概率维持原先方向 
					vd.push_back(i);
					vrate.push_back(rate); 
				}  
				int spider_see(int id){//返回前进方向
					if(id<0||id>=spiders.size()) return RAND(3,0);
					int mx_dis=SPIDERB_SIGHT;//最远观察距离 
					spider &sr=spiders[id];
					position_3D pos=sr.pos;//原位置 
					int d=sr.d;//原方向 
					vector<PII > v(4);vector<position_3D> ret;
					int tmp=(d+3)%4*90;//蜘蛛方向对应的方向角
					for(int i=0;i<4;i++) v[i]=MP((tmp-90+360)%360,(tmp+90+360)%360);//蜘蛛部分视野（-90°~90°） 
					vision_init(1,v,ret,pos000);
					calculate_vision2(sr.pos,3,ret,mx_dis,0);
					position_3D goal=pos000;
					for(int i=0;i<ret.size();i++){
						position_3D u=ret[i];
						MAP &NPOS=game_map[u.x][u.y][u.z];
						int gtid=NPOS.emy.id;
						if(player_here(u)//找到玩家 
						||ghost_here(u)&&(gtid<0||gtid>=ghosts.size()?1:!ghosts[gtid].spat.can_disappear())){//或非隐身鬼 
							goal=u;//就近原则（ret一定是从近到远排序的） 
							break;
						}
					}
					if(goal==pos000){//看不到目标 
						if(sr.prey==pos000) return -1;//找不到猎物 
						if(sr.pos==sr.prey){
							sr.prey=pos000;
							return -1;//到了猎物最后出现的位置，但还是找不着 
						}
						else goal=sr.prey;//目标设为猎物最后出现的位置
					}
					else sr.prey=goal;//更新猎物最后出现的位置 
					direction direct=ptp(goal,pos);
					int d1=direct.d1,d2=direct.d2;
					vector<int> vd2;
					if(pos.y!=goal.y){
						position_3D u=dtp3(pos,d1,4);//新位置 
						vision_init(1,v,ret,pos000);
						calculate_vision2(u,3,ret,mx_dis,0);//新视野
						if(find(ret.begin(),ret.end(),goal)!=ret.end()&&spider_through(u,d1,1)) vd2.push_back(d1);//d1方向可行 
					}
					if(pos.x!=goal.x){
						position_3D u=dtp3(pos,d2,4);//新位置
						vision_init(1,v,ret,pos000);
						calculate_vision2(u,3,ret,mx_dis,0);//新视野 
						if(find(ret.begin(),ret.end(),goal)!=ret.end()&&spider_through(u,d2,1)) vd2.push_back(d2);//d2方向可行 
					}
					if(vd2.size()) return vd2[RAND(vd2.size()-1,0)];
					return -1;
				}
			void spider_turn(int &d,int id){//蜘蛛选择方向
				//引用d直接进行函数内修改 
				//MAP &PPOS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				if(id<0||id>=spiders.size()) return;
				spider &sr=spiders[id];
				bool srk=sr.kind;
				vector<int> vd;//可选方向
				vector<double> vrate;//权重 
				position_3D u=sr.pos;
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				position_3D v;
				for(int i=0;i<4;i++){
					v=dtp3(u,i,4);
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					int door_d=turn(i,TURN_BACK,4,11);//i的相反方向（箱门） 
					if(door_d==sr.d&&sr.kind==1) continue;//B型蜘蛛太笨拙没法向后转 
					if((player_here(v)||ghost_here(v))&&!closed_box_here(v,door_d)){//旁边有玩家、鬼就走过去 
						d=i;
						return;//最高级别直接退出 
					}
					if(spider_towards(v,i,srk)){
						/*
						if(i==d1) ok1=1;
						else if(i==d2) ok2=1;
						//蜘蛛的视野范围不大，不用考虑太多 */
						spider_decision_update(vd,vrate,d,i,sr.bir,u,v);
					}
				}
				if(srk==0&&stair_here(u)){//上下楼（B型蜘蛛体形太大挤不进去） 
					int i=4;
					v=u;
					position_3D v2=v;
					MAP &POS2=game_map[v2.x][v2.y][v2.z];
					if(POS.maze==UPSTAIR) v.z++;
					else if(POS.maze==DOWNSTAIR) v.z--;
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					if((player_here(v)||ghost_here(v))&&!box_here(v)){//旁边有玩家、蜘蛛就走过去 
						d=i;
						return;//最高级别直接退出 
					}
					if(spider_towards(v,i,srk)) spider_decision_update(vd,vrate,d,i,sr.bir,u,v);
				}
				if(srk){//B型蜘蛛 
					int goal_d=spider_see(id);
					if(goal_d!=-1){
						d=goal_d;
						return;
					}
				}
				int sz=vd.size();
				for(int i=0;i<sz;i++)//在原来基础上增加 
					for(int j=1;j<vrate[i];j++) vd.push_back(vd[i]);
				sz=vd.size();
				if(sz) d=vd[RAND(sz-1,0)]; 
				d=(d+RAND(1,-1)+4)%4;//没有可选方向就随机左转右转或原先方向 
			}
			void spider_shoot_silk(position_3D pos,double speed,int angle){//蜘蛛发射蛛丝
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				thing &THING=POS.things;
				flying_ssk fsk;
				fsk.init(pos,speed,angle);
				ssks.push(fsk);//加入队列
				THING.ssk.num++;//更新地图
			} 
				void poison_spe(special_effect &spe,int k,PII from){//鬼和人的效果一致 
					switch(k){
						case 1://虚弱 
							spe.wks.change=true;
							spe.wks.end=max(spe.wks.end,game_time)+5000;
							spe.wks.t=-INF;spe.wks.T=RAND(10,5)*100;
							spe.wks.x=RAND(10,5);
							spe.wks.from=from;
							break;
						case 2://眩晕
							spe.vtg.change=true;
							spe.vtg.end=max(spe.vtg.end,game_time)+10000;
							spe.vtg.t=-INF;spe.vtg.T=RAND(6,4)*100;
							spe.vtg.from=from;
							break;
						case 3://失明 
							spe.bds.change=true; 
							spe.bds.end=max(spe.bds.end,game_time)+6000;
							spe.bds.vision_dis=RAND(5,1);
							spe.bds.from=from;
							break;
						case 4://中毒
							spe.mts.change=true;
							spe.mts.end=max(spe.mts.end,game_time)+5000;
							spe.mts.t=-INF;spe.mts.T=RAND(10,5)*100;
							spe.mts.x=2;
							spe.mts.from=from;
							break;
						case 5://迷惑 
							spe.cfs.change=true;
							spe.cfs.end=max(spe.cfs.end,game_time)+4000;
							spe.cfs.a=5;
							spe.cfs.from=from;
							break;
					}
				}
			void poison_player(PII from){//注射毒液
				int k=RAND(5,1);
				special_effect &spe=player1.spe;
				/*
				1 weakness wks;
				2 vertigo vtg;
				3 blindness bds;
				4 methysis mts;
				5 confusion cfs;
				改了参数把下面也改一下 
				*/
				poison_spe(spe,k,from);
			}
			void poison_ghost(int id,PII from){
				if(id<0||id>=ghosts.size()) return;
				int k=RAND(4,1);
				ghost &gt=ghosts[id];
				if(gt.lfin.life<=0) return;//已经死了就不再下毒了 
				special_effect &spe=gt.spe;
				/*
				1.虚弱（移动速度下降）
				2.眩晕（无法攻击）
				3.失明（视野范围受限）
				4.中毒（持续扣血） 
				*/
				poison_spe(spe,k,from);
			}
		void deal_spider(){
			logMessage("Qspider_hurt"); 
			int spider_num=Qspider_hurt.size();
			while(spider_num>0){
				spider_num--;
				int id=Qspider_hurt.front();Qspider_hurt.pop();
				if(id<0||id>=spiders.size()) continue;
				spider &sr=spiders[id];
				life_injury &lfin=sr.lfin;
				MAP &POS=game_map[sr.pos.x][sr.pos.y][sr.pos.z];
				string s="蜘蛛"+int_to_str(id);
				if(!sr.update){//更新
					sr.update=true;
					Qspider.push(id);
				}
				thing &THING=POS.things;
				if(THING.lsr.exist||THING.drt.exist1()
				||(THING.spr.exist&&game_timer[s+"被矛刺中"]<=game_time)//1000毫秒延时已到 
				){//要和下面一一对应
				    if(THING.spr.exist){
						game_timer[s+"被矛刺中"]=game_time+1000;//每秒计算一次伤害 
						object_addE(player1.items.wpn.primary,-sr.vlc.speed*2);
					}
					else player1.scr.shoot_hit_times++;
					spider_reduce_blood(id,5*(THING.lsr.exist+THING.drt.exist1()*THING.drt.num[1])+THING.spr.exist,MP(PLAYER,-1));
					//长矛对蜘蛛造成的伤害微乎其微（-1） 
					if(POS.ist.player==lst_see_time){
						game_flag["敌人被玩家攻击"]=true;
						pos_change.insert(sr.pos);
					}
				}
				if(POS.fcmv.lock&&game_timer[s+"被砸中"]<=game_time){
					if(POS.fcmv.speed()>2){
						spider_reduce_blood(id,1,POS.fcmv.from);
						game_timer[s+"被砸中"]=game_time+500;
					}
				}
				if(lfin.life<=0){//清除痕迹 spider_here(sr.pos)&&
					logMessage("Qspider_hurt lfin.life<=0"); 
					if(POS.ist.player==lst_see_time){
						game_flag["敌人被玩家攻击"]=true; 
						pos_change.insert(sr.pos);
						pos_dead.push(sr.pos);
					}
					if(sr.pos!=pos000){
						message_box.push(MP(lfin.last_injury_from,MP(SPIDER,id)));//击杀信息 
						sr.pos=pos000;
						if(lfin.last_injury_from.first==PLAYER) player1.scr.kc.update(1,SPIDER);
					}
					spider_update_leg(sr.pos,-1,id);//死了附肢也要清除掉 
					POS.fcmv.lock=false;//game_flag["飞"]=true;pos_change.insert(sr.pos);//解除锁定 
					POS.emy.dead=true;POS.emy.body_disapp=game_time+300;
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					spider_move_away(id);
					logMessage("Qspider_hurt lfin.life<=0 end"); 
				}
				//game_timer["蜘蛛"]++;
			}//循环1：生命更新循环 
			logMessage("Qspider"); 
			spider_num=Qspider.size();
			while(spider_num>0){
				spider_num--;
				int id=Qspider.top();Qspider.pop();
				if(id<0||id>=spiders.size()) continue;
				spider &sr=spiders[id];
				int srk=sr.kind;//蜘蛛种类 
				MAP &POS=game_map[sr.pos.x][sr.pos.y][sr.pos.z];
				string s="蜘蛛"+int_to_str(id);
				if(sr.change_pos){
					Qspider.push(id);
					spider_move_away(id);
					continue;
				}
				if(MHT_DIST_p3(sr.pos,player1.pos)>100 
				&&POS.ist.player<lst_see_time)//离玩家距离超过100格且玩家看不到 
					sr.update=false;//停止更新 
				if(!sr.update) continue;
				if(sr.lfin.life<=0) Qspider_hurt.push(id);
				Qspider.push(id);
				thing &THING=POS.things;
				if(game_timer[s]>game_time)//时间没到不更新 
					break;
				game_timer[s]=game_time+sr.vlc.wait_time; 
				game_timer["蜘蛛"]++;//
				if(!(THING.lsr.exist||THING.drt.exist1()||THING.spr.exist)
				&&game_timer[s+"被砸中"]<=game_time){
					if(sr.lfin.change!=0&&POS.ist.player==lst_see_time){
						game_flag["敌人被玩家攻击"]=true; 
						pos_change.insert(sr.pos);
					}
					sr.lfin.change=0;
				}
				if(THING.lsr.exist||POS.fcmv.lock&&sr.kind==0) continue;//被激光命中或被击飞（A型）无法移动和攻击 
				position_3D npos=sr.pos;
				int d=sr.d;
				spider_turn(d,id); 
				if(stair_here(npos)&&d==4){//上下楼 
					if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
					else npos.z--;
				}
				else{//普通移动 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				if(spider_through(npos,d,srk)){
					logMessage("Qspider move"); 
					/*
					if(sr.kind&&sr.prey!=pos000){//B型蜘蛛发射蛛丝 
						int angle=calc_angle(sr.pos,sr.prey),angle2=(d+3)%4*90;//angle：目标方向 angle2：移动后的新方向 
						if(sub_angle(angle,angle2)<=45&&MHT_DIST_p3(npos,sr.prey)>=2)
							spider_shoot_silk(npos,7,angle);//方向、距离合适 
					}*/
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					NPOS.player_enemy=SPIDER;NPOS.emy.id=id;
					if(POS.ist.player==lst_see_time){
						player1.enemy_move=true;
						pos_change.insert(sr.pos);
						if(THING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["帘子摇动"]=true;
							if(POS.update_light()) pos_affect_light.push(sr.pos);//帘子动了光照更新 
						}
					}
					if(NPOS.ist.player==lst_see_time){
						player1.enemy_move=true;
						pos_change.insert(npos);
						if(NTHING.crt.exist&&POS.ist.player==lst_see_time){
							game_flag["帘子摇动"]=true;
							if(NPOS.update_light()) pos_affect_light.push(npos);//帘子动了光照更新 
						}
					}
					spider_update_leg(sr.pos,-1,id);
					spider_update_leg(npos,1,id);
					if(sr.kind==0) NTHING.snt.addedc(10,npos);//A型蜘蛛留下蜘蛛丝 每次移动有概率if(RAND_BOOL(100-NTHING.snt.endurance))  
					sr.pos=npos;
					if(MHT_DIST(sr.pos.x,sr.pos.y,player1.pos.x,player1.pos.y)<=7&&sr.pos.z==player1.pos.z)
						MUSIC(sound_spider_move[RAND(4,0)],1);//蜘蛛爬行声 
					sr.d=d;
					logMessage("Qspider move end"); 
				}
				else{
					logMessage("Qspider pump"); 
					int door_d=(d==4?0:turn(d,TURN_BACK,4,12));//箱门 
					bool make_net=false;
					if(player_here(npos)&&(d==4?!box_here(npos):!closed_box_here(npos,door_d))){
						player_reduce_blood(5.0/sr.vlc.speed,MP(SPIDER,id));
						if(RAND_BOOL(25)) poison_player(MP(SPIDER,id));//25%概率给玩家注射毒液 
						make_net=true;
					}
					else if(ghost_here(npos)&&NPOS.emy.id!=-1&&!closed_box_here(npos,door_d)){
						ghost_reduce_blood(NPOS.emy.id,2.5,MP(SPIDER,id));//蜘蛛打鬼 
						if(sr.kind) spider_reduce_blood(id,-2,MP(SPIDER,id));//吃鬼回血（B型）
						if(RAND_BOOL(25)) poison_ghost(id,MP(SPIDER,id));//25%概率给鬼注射毒液  
						hurt_enemy(NPOS);
						make_net=true;
					}
					else if(bug_here(npos)&&NPOS.emy.id!=-1&&!closed_box_here(npos,door_d)){
						bug_reduce_blood(NPOS.emy.id,2.5,MP(SPIDER,id));//蜘蛛吃虫子
						spider_reduce_blood(id,-1,MP(SPIDER,id));//吃虫子回血 
						hurt_enemy(NPOS);
						make_net=true;
					}
					else if(door_here(npos,0)||door_here(npos,2)){
						int &state=NTHING.kdr.state;
						if(state==2){
							state=1;//关->开 
							if(NPOS.update_light()) pos_affect_light.push(npos);//门开了光照更新
							if(NPOS.ist.player==lst_see_time) game_flag["开门"]=true;
						}
						else{//锁住的门也能开 
							state=2;//锁->关 即拆锁 
							if(NPOS.ist.player==lst_see_time){
								game_flag["物品损坏"]=true;
								pos_change.insert(npos);
							}
						}
					}
					else if(closed_box_here(npos,door_d)){
						NTHING.mvb.door[door_d]^=1;
						if(NPOS.ist.player==lst_see_time) game_flag["开门"]=true;
					}
					else if(NTHING.windows.exist){
						window &WDN=NTHING.windows;
						WDN.damage(20,npos); 
					}
					if(make_net&&sr.kind==0){//A型蜘蛛攻击敌人顺便结个网
						NTHING.snt.addedc(40,npos);
					}
					if(d!=sr.d) spider_update_leg(sr.pos,0,id);//改变方向附肢更新（数量不变） 
					if(sr.kind==0||spider_through(sr.pos,d,srk)) sr.d=d;//防止B型蜘蛛转一下把自己卡住 
					logMessage("Qspider pump end"); 
				}
				//sr.d=d;
			}//循环2：主体循环 
		}
				void ghost_decision_update(int id,vector<int> &vd,int &d,int &i,int &fpt,MAP &POS,MAP &NPOS,thing &THING,thing &NTHING){
					if(id<0||id>=ghosts.size()) return;
					ghost &gt=ghosts[id];
					if(d==i) vd.push_back(i),vd.push_back(i);//更大概率保持原先方向 
					if(THING.fpt.d==i)//足迹向前后左右 
						fpt=THING.fpt.d;
					if(NTHING.fpt.d!=-1){//旁边有足迹 
						//fnear=i;
						vd.push_back(i);
						vd.push_back(i);
					}
					if(NPOS.player_enemy==SPIDER) vd.push_back(i),vd.push_back(i),vd.push_back(i);//更大概率揍旁边的蜘蛛 
					if(gt.spat.attack==VAMPIRE&&POS.brightness>NPOS.brightness){
						REP(10) vd.push_back(i);//更更大概率（吸血鬼）远离光亮区域 
					} 
					vd.push_back(i);
				}  
				position_3D ghost_aim_goal(position_3D u,position_3D v){//u->v冲
					/*
					int angle=calc_angle(u,v);
					double dis=NED_p3(u,v)+3;//瞄着玩家后面一点 
					position_3D pos=u;
					pos.x+=round(dis*cos(angle*PI/180.0)); 
					pos.y+=round(dis*sin(angle*PI/180.0));*/
					position_3D pos;
					pos.x=2*v.x-u.x;
					pos.y=2*v.y-u.y;
					pos.z=u.z;
					return pos;
				}
			void ghost_turn(int &d,int id){//随机改变方向/跟踪玩家足迹/跟着玩家声音 
				logMessage("ghost_turn id="+int_to_str(id)); 
				//旁边有玩家>声音>足迹>旁边有足迹>随机 		
				if(id<0||id>=ghosts.size()) return;
				MAP &PPOS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				ghost &gt=ghosts[id];
				special_attribute &spat=gt.spat;
				int &att=spat.attack,&def=spat.defense;
				blindness &bds=gt.spe.bds;
				
				int mx_dis=(bds.exist()?bds.vision_dis:GHOST_SIGHT);//失明效果下限制视野 
				vector<int> vd;vd.clear();//可以走的方向 
				vector<int> d_vpr;d_vpr.clear();//吸血鬼可以走的方向 
				
				position_3D u=gt.pos;
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				position_3D v;
				
				/*
				横冲直撞——调整目标法 
				double dis1=NED_p3(gt.pos,player1.pos),dis2=NED_p3(gt.goal,gt.pos),dis3=NED_p3(player1.pos,gt.goal);
				if(POS.ist.other==lst_see_time){
					if(gt.goal==pos000&&dis1>2&&RAND_BOOL(30))
						gt.goal=ghost_aim_goal(gt.pos,player1.pos);//gt.goal=player1.pos;//保持跟踪 
					//else if(gt.goal!=pos000&&dis3>5)
					//	gt.goal=ghost_aim_goal(gt.pos,player1.pos);//gt.goal=player1.pos;//保持跟踪 
					else if(gt.pos==gt.goal) gt.goal=pos000;//丢失目标 
				}
				else if(gt.goal!=pos000&&gt.pos==gt.goal) gt.goal=pos000;//丢失目标 
				*/
				direction direct;
				if(gt.goal==pos000) direct=ptp(player1.pos,u);
				else direct=ptp(gt.goal,u);
				int snd=-1,fpt=-1,fnear=-1,d1=direct.d1,d2=direct.d2;
				if(u.y==player1.pos.y&&RAND_BOOL(25)&&gt.goal!=pos000) d1=-1;
				if(u.x==player1.pos.x&&RAND_BOOL(25)&&gt.goal!=pos000) d2=-1;
				//正常追逐玩家时，和玩家在水平或竖直线上时有75%概率把垂直于面向玩家的方向加入考虑 
				
				bool ok1=0,ok2=0;
				for(int i=0;i<4;i++){
					v=dtp3(u,i,4);
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					int door_d=turn(i,TURN_BACK,4,13);//箱门
					/*
					if(player_here(v)&&!closed_box_here(v,door_d)&&NPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()){//旁边有玩家就走过去 
						d=i;
						return;//最高级别直接退出 
					}*/
					if(ghost_towards(gt.pos,v,i,spat.can_through())&&(gt.spat.attack==VAMPIRE?!NPOS.burn_vampire():1)){
						if(gt.spat.attack==VAMPIRE&&POS.burn_vampire()&&POS.brightness>NPOS.brightness)//吸血鬼躲避强光 
							d_vpr.push_back(i);
						if((POS.ist.other==lst_see_time&&NPOS.ist.other==lst_see_time//这里和下一步都能看到玩家
						||spat.can_through()&&player1.pos.z==u.z)//穿墙（透视）且位于同一楼层 
						&&PPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()){//太暗或太亮都看不见 
							if(i==d1) ok1=1;
							else if(i==d2) ok2=1;
						}
						ghost_decision_update(id,vd,d,i,fpt,POS,NPOS,THING,NTHING);
					}
				}
				if(stair_here(u)||POS.things.nst.exist){//上下楼、进出巢穴口
					int i=4;
					v=u;
					position_3D v2=v;
					if(POS.things.nst.exist) v2=POS.things.nst.to;
					MAP &POS2=game_map[v2.x][v2.y][v2.z];
					if(POS.maze==UPSTAIR) v.z++;
					else if(POS.maze==DOWNSTAIR) v.z--;
					else{//移动到对应的巢穴口
						v.x=v2.x;
						v.y=v2.y;
						v.z=v2.z;
					}
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					if(player_here(v)&&!box_here(v)&&NPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()){//旁边有玩家就走过去 
						d=i;
						return;//最高级别直接退出 
					}
					if(ghost_towards(gt.pos,v,i,spat.can_through())&&(gt.spat.attack==VAMPIRE?!NPOS.burn_vampire():1)){
						if(gt.spat.attack==VAMPIRE&&POS.burn_vampire()&&POS.brightness>NPOS.brightness)//吸血鬼躲避强光 
							d_vpr.push_back(i);
						ghost_decision_update(id,vd,d,i,fpt,POS,NPOS,THING,NTHING);
					}
				}
				
				int sz3=d_vpr.size();//吸血鬼可以躲避的方向 
				if(gt.spat.attack==VAMPIRE&&POS.burn_vampire()&&sz3){//吸血鬼被光攻击了 
					d=d_vpr[RAND(sz3-1,0)];
					return;
				}
				
				vector<int> vd2;//追逐玩家可以走的方向 
				if(ok1) vd2.push_back(d1);
				if(ok2) vd2.push_back(d2);
				int sz=vd.size(),sz2=vd2.size();
				int B=POS.brightness;
				int a=max(0,100-abs(B)*2);//看清足迹的概率 
				bool chase=0;//是否追逐 
				if(snd!=-1) d=snd;
				else if(NED_p3(u,player1.pos)<=mx_dis&&sz2){
					d=vd2[RAND(sz2-1,0)];//在视野范围内就追 
					chase=1;
				}
				else if(fpt!=-1&&RAND_BOOL(a)) d=fpt;//跟踪足迹 
				//else if(fnear!=-1) d=fnear;
				else if(sz) d=vd[RAND(sz-1,0)]; 
				
				if(!chase) gt.goal=pos000; 
			}
			void ghost_disappear_print(position_3D pos,int kind){//鬼切换隐身状态的显示更新 
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				if(kind==1){
					game_flag["鬼装墙"]=true;
					if(POS.ist.player==lst_see_time&&POS.update_light()) pos_affect_light.push(pos);//鬼伪装成墙更新光照 
				}
				else{
					game_flag["鬼隐身"]=true;
					if(POS.ist.player==lst_see_time) pos_change.insert(pos);
				}
			}
			position_3D ghost_instant_pos(position_3D pos,special_attribute &spat){//围绕pos进行瞬移
				position_3D npos;
				int d=RAND(spat.ins.dis,1),dx=RAND(d,1)*(RAND(1,0)*2-1),dy=RAND(d,1)*(RAND(1,0)*2-1);//偏移量 
				//不同距离的瞬移概率相同 
				if(RAND_BOOL(50)) dx=(d-abs(dy))*(RAND(1,0)*2-1);
				else dy=(d-abs(dx))*(RAND(1,0)*2-1);
				npos.x=pos.x+dx;npos.y=pos.y+dy;npos.z=pos.z;//新的坐标（不能瞬移到楼下） 
				if(npos.x<=1) npos.x=2;
				else if(npos.x>=length) npos.x=length-1;
				if(npos.y<=1) npos.y=2;
				else if(npos.y>=width) npos.y=width-1;//防止超出地图范围 
				return npos;
			}
				bool player_grid(int angle){//玩家面对angle的格挡是否有效 
					return player1.color==4&&game_timer["玩家图标闪烁"]>game_time&&sub_angle(angle,player1.angle)<=20;
				}
			void ghost_attack(int id,string s){//目前只有攻击玩家，专门针对高玩
				if(id<0||id>=ghosts.size()) return; 
				ghost &gt=ghosts[id];
				special_effect &spe=gt.spe;
				vertigo &vtg=spe.vtg;//眩晕 
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				thing &THING=POS.things;
				MAP &PPOS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				int door_d=atd(calc_angle(player1.pos,gt.pos)),door_d2=turn(door_d,TURN_BACK,4,14);//箱门 
				bool hit_around=count_around_pos(gt.pos,4,player_here)
				&& !closed_box_here(player1.pos,door_d) && !closed_box_here(gt.pos,door_d2);
				bool change_z=false;//能否跨楼层攻击 
				if(gt.pos.x==player1.pos.x&&gt.pos.y==player1.pos.y){//有可能跨楼层 
					if(stair_here(gt.pos)){//走楼梯 
						position_3D npos=gt.pos;
						if(upstair_here(gt.pos)) npos.z++;
						else npos.z--;
						if(npos==player1.pos) change_z=true;
					}
					else if(nest_here(gt.pos)){//走巢穴 
						position_3D npos=POS.things.nst.to;
						if(npos==player1.pos) change_z=true;
					}
					//够得着吗？（注意上下楼/进出巢穴口的情况）
				}
				change_z=change_z and !box_here(player1.pos);
				bool atk=(PPOS.ist.other==lst_see_time&&PPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()//看得见才打 
					&&(hit_around||change_z)&&!vtg.exist())//没眩晕
					&&!(THING.lsr.exist||POS.fcmv.lock);//没被激光命中或踢出去 
				//确定攻击的条件
				if(atk){
					if(game_timer[s+"可打玩家"]==0) game_timer[s+"可打玩家"]=game_time;
					//如果可以攻击，维护连续往前最早可攻击的时间点 
				}
				else game_timer[s+"可打玩家"]=0;//否则清零 
				//记录时钟 
				double atk_t=gt.attack_time;
				int angle_ghost_player=calc_angle(gt.pos,player1.pos);//鬼->玩家方向角 
				if(spe.wks.exist()){//虚弱 
					atk_t*=1.5;//放慢鬼的攻击速度 
					limit_double(atk_t,0.0,0.5);//防止越界 
				}
				//if(gt.goal!=pos000&&(gt.d+3)%4*90==angle_ghost_player) atk_t=0;//鬼冲过来对准了就是秒反 
				int react_time=atk_t*gt.vlc.wait_time*((gt.d+3)%4*90==angle_ghost_player?1.0:2.0);//反应时间（ms） 
				//如果打击方向和当前方向不同，反应时间延长 
				if(gt.spat.attack==INSTANT) react_time*=(100-gt.spat.ins.p)/100.0;
				//瞬移鬼的反应时间缩短 
				if(game_timer[s+"可打玩家"]+react_time<=game_time//反应时间还没到 
				&&RAND_BOOL(100)&&atk){//有一定概率 
					int angle=(RAND(45,-45)+angle_ghost_player+360)%360;
					if(change_z) angle=RAND(359,0);
					//上下楼/进出巢穴口 随便乱打 
					double force=0,hurt_rate=0;//作用力、伤害系数 
					if(RAND_BOOL(50)&&!box_here(player1.pos)){//踢飞（箱子不踢） 
						force=15.0;
						hurt_rate=0.3;
						if(player_grid((angle_ghost_player+180)%360)) force*=0.2,hurt_rate*=0.2;//格挡削弱80%
						if(!change_z) throw_thing(gt.pos,2.5*PPOS.mass()/POS.mass(),0,(angle+180)%360,MP(GHOST,id));
						//反弹力（跨楼层攻击时不考虑） 
					}
					else{//拳打 
						force=10.0;
						hurt_rate=0.2;
					}
					throw_thing(player1.pos,force/PPOS.mass(),hurt_rate,angle,MP(GHOST,id));//最终作用在玩家身上的 
					
					game_timer[s+"可打玩家"]=game_time+gt.vlc.wait_time;
					//冷却时间 
				}
				double dis1=NED_p3(gt.pos,player1.pos),dis2=NED_p3(gt.goal,gt.pos),dis3=NED_p3(player1.pos,gt.goal);
				if(game_timer[s]<=game_time&&POS.ist.other==lst_see_time&&dis1<=10&&dis1>=4&&!POS.fcmv.lock
				&&RAND_BOOL(30)){
					double v=15,v2=1;
					int nohurt_time=(v-v2)*1000;//v0,vt=1,a=1->t=(v0-vt)/a 
					gt.rampage=true;//gt.lfin.no_hurt=game_time+nohurt_time;//防止伤害 
					throw_thing(gt.pos,v,0,calc_angle(gt.pos,player1.pos),MP(GHOST,id)); 
				}
			}
			void shut_door(position_3D pos,position_3D who,PII from){//摔门到人家脸上 
				int angle=calc_angle(who,pos);
				direction dir=ptp(pos,who);
				int d1=dir.d1,d2=dir.d2;
				if(d1!=-1){
					position_3D u=dtp3(pos,d1,4);
					MAP &POS=game_map[u.x][u.y][u.z];
					if(!nobody_here2(u)&&!box_here(u)){//门能摔到生物身上 
						throw_thing(u,10.0/POS.mass(),0.3,angle,from);
					}
				}
				if(d2!=-1){
					position_3D u=dtp3(pos,d2,4);
					MAP &POS=game_map[u.x][u.y][u.z];
					if(!nobody_here2(u)&&!box_here(u)){//门能摔到生物身上 
						throw_thing(u,10.0/POS.mass(),0.3,angle,from);
					}
				}
			} 
		void deal_ghost(){
			logMessage("deal_ghost"); 
			int ghost_num=Qghost_hurt.size();
			while(ghost_num>0){
				ghost_num--;
				int id=Qghost_hurt.front();Qghost_hurt.pop();
				logMessage("Qghost_hurt id="+int_to_str(id)); 
				if(id<0||id>=ghosts.size()) continue;
				ghost &gt=ghosts[id];
				life_injury &lfin=gt.lfin;
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				string s="鬼"+int_to_str(id);
				if(!gt.update){//只要被攻击都更新
					gt.update=true;
					Qghost.push(id);
				}
				thing &THING=POS.things;
				special_attribute &spat=gt.spat;
				int &att=spat.attack,&def=spat.defense;
				if((THING.lsr.exist||THING.drt.exist1())&&game_timer[s+"被射中"]<=game_time
				||(THING.spr.exist&&game_timer[s+"被矛刺中"]<=game_time)){ //1000毫秒延时已到 
					if(!spat.can_evade()){//没有闪开 
						player1.scr.shoot_hit_times++;
						ghost_reduce_blood(id,5*THING.lsr.exist+1.5*THING.drt.num[1]+0.5*THING.spr.exist,MP(PLAYER,-1));
						//激光伤害5.0 飞镖伤害1.5 长矛伤害0.5 
						game_timer[s+"被射中"]=game_time+500;//0.5s延时防止出现重复判定
						game_timer[s+"被矛刺中"]=game_time+1000;//1.0s延时 
					}
					else{
						spat.eva.use=true;
						if(POS.ist.player==lst_see_time){//显示“闪” 
							game_flag["敌人被玩家攻击"]=true;
							pos_change.insert(gt.pos);
						}
					}
				}
				if(POS.fcmv.lock&&game_timer[s+"被砸中"]<=game_time&&!gt.rampage){//飞行中且没有带免伤 
					if(POS.fcmv.speed()>5){//速度大于5每秒受到1点伤害 
						ghost_reduce_blood(id,1,POS.fcmv.from);
						game_timer[s+"被砸中"]=game_time+500;
					}
				}
				special_effect &spe=gt.spe;
				methysis &mts=spe.mts;
				if(mts.exist()&&mts.t+mts.T<=game_time){//中毒扣血 
					mts.t=game_time;
					ghost_reduce_blood(id,mts.x,mts.from);
				}
				skill_disappear &disa=spat.disa;
				if(lfin.change!=0&&spat.attack==DISAPP&&lfin.life<10){//被攻击且生命值低停止隐身 
					disa.use=false;
					disa.time=game_time+RAND(20000,10000);
					if(POS.ist.player==lst_see_time) ghost_disappear_print(gt.pos,disa.kind);
				}
				if(lfin.life<=0){//清除痕迹 ghost_here(gt.pos)&&POS.emy.id>=0&&
					logMessage("lfin.life<=0"); 
					if(POS.ist.player==lst_see_time){
						game_flag["敌人被玩家攻击"]=true; 
						pos_change.insert(gt.pos);
						pos_dead.push(gt.pos);
					}
					if(gt.pos!=pos000){
						message_box.push(MP(lfin.last_injury_from,MP(GHOST,id)));//击杀信息 
						gt.pos=pos000;
						if(lfin.last_injury_from.first==PLAYER){
							player1.scr.kc.update(1,GHOST);
							player_kill_reward(gt.pos,GHOST,gt.spat);
						}
					}
					POS.fcmv.lock=false;//game_flag["飞"]=true;pos_change.insert(gt.pos);//解除锁定 
					POS.emy.dead=true;POS.emy.body_disapp=game_time+400;
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					ghost_move_away(id);
				}
				game_timer["鬼"]++;
			}//循环1：生命更新循环 
			ghost_num=Qghost.size();
			while(ghost_num>0){
				ghost_num--;
				int id=Qghost.front();Qghost.pop();
				logMessage("Qghost id="+int_to_str(id)); 
				if(id<0||id>=ghosts.size()) continue;
				ghost &gt=ghosts[id];
				life_injury &lfin=gt.lfin;
				special_effect &spe=gt.spe;
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				string s="鬼"+int_to_str(id);
				if(gt.change_pos){
					Qghost.push(id);
					ghost_move_away(id);
					continue;
				}
				if(MHT_DIST2(gt.pos.x,gt.pos.y,(gt.pos.z>height?gt.pos.z-height:gt.pos.z),player1.pos.x,player1.pos.y,player1.pos.z)>100
				&&POS.ist.player<lst_see_time)//离玩家距离超过100格（注意巢穴高度）且玩家看不到 
					gt.update=false;//停止更新 
				if(lfin.life<=0){//没血了就加入队列 
					Qghost_hurt.push(id);
					gt.update=false;//停止更新 
				}
				if(gt.spe.exist()) Qghost_hurt.push(id);//特殊效果就加入队列 
				if(!gt.update) continue;//不更新了就跳出队列 
				Qghost.push(id);
				thing &THING=POS.things;
				special_attribute &spat=gt.spat;
				skill_vampire &vpr=spat.vpr;
				skill_through &thr=spat.thr;
				skill_disappear &disa=spat.disa;
				spat.eva.use=false;
				switch(spat.attack){//有持续时间的技能更新 
					case VAMPIRE:
						if(POS.burn_vampire()&&thr.time<=game_time){
							ghost_reduce_blood(id,0.1*POS.brightness,MP(GHOST,id));
							thr.time=game_time+1000;//每秒计算一次灼烧伤害 
						}
						break;
					case THROUGH:
						if(thr.time<=game_time){
							thr.time+=10000;//每十秒开启一次穿墙技能，持续十秒 
							thr.use=!thr.use;
						}
						break;
					case DISAPP:
						if(disa.time<=game_time){
							if(!disa.use&&disa.kind==1&&POS.ist.other==lst_see_time
							&&game_map[player1.pos.x][player1.pos.y][player1.pos.z].see(GHOST,gt.spat.attack)&&POS.see_fr())
								disa.time=game_time+RAND(4000,2000);//被看见时不切换为隐身
							else{
								disa.use=!disa.use;
								if(disa.use) disa.time=game_time+RAND(disa.maxt,disa.maxt/2);
								else disa.time=game_time+RAND(3000,1000);
								if(POS.ist.player==lst_see_time) ghost_disappear_print(gt.pos,disa.kind);
							} 
						}
						break;
				}
				force_move &FCMV=POS.fcmv;
				if(gt.rampage&&(FCMV.lock?not(FCMV.from==MP(int(GHOST),id)):1)) gt.rampage=false;//弹射起步结束 
				double atktime=gt.attack_time;
				ghost_attack(id,s);//到了攻击时间
				if(game_timer[s]>game_time)//时间没到不移动 
					continue;
				int wait_time=gt.vlc.wait_time;
				if(spat.attack==INSTANT&&RAND_BOOL(spat.ins.p))//发动瞬移技能
					wait_time=0;
				else if(gt.goal!=pos000) wait_time/=5;//速度*5 
				game_timer[s]=game_time+wait_time; 
				game_timer["鬼"]++;
				if(!(THING.lsr.exist||THING.drt.exist1()||THING.spr.exist)
				&&game_timer[s+"被砸中"]<=game_time&&game_timer[s+"被矛刺中"]<=game_time){//要和上面一一对应 
					if(lfin.change!=0&&POS.ist.player==lst_see_time){
						game_flag["敌人被玩家攻击"]=true; 
						pos_change.insert(gt.pos);
					}
					lfin.change=0;
				}
				if(THING.lsr.exist||POS.fcmv.lock){
					if(FCMV.lock&&(spat.defense==ROCK||spat.defense==SHIELD)){
						int k=spat.rck.k;
						FCMV.init3(FCMV.vx.speed*k,FCMV.vy.speed*k);
						if(FCMV.speed()<=1) FCMV.init();
						spat.rck.use=true;//鬼的技能 
					}
					else spat.rck.use=false;
					continue;//被激光命中或被击飞无法移动和攻击 
				}
				else spat.rck.use=false;
				if(spat.can_disappear()&&disa.kind==1) continue;//隐身状态下伪装成墙不移动 
				spider_net &SNT=THING.snt;
				SNT.addedc(-20,gt.pos);//损坏蜘蛛网 
				if(SNT.endurance>50+25)//先减少再判断 
					continue;//被蜘蛛网粘住 
				weakness &wks=spe.wks;
				vertigo &vtg=spe.vtg;
				if(wks.exist()&&RAND_BOOL(wks.x*8)){
					if(POS.ist.player==lst_see_time) pos_change.insert(gt.pos);
					continue;//虚弱给鬼的行动造成卡顿 
				}
				position_3D npos=gt.pos;
				int d=gt.d;
				ghost_turn(d,id); 
				bool use_instant=false;
				if(spat.attack==INSTANT//能瞬移 
				&&count_around_pos(gt.pos,4,spider_here)+count_around_pos(gt.pos,4,flying_thing_here)>=1){
				//优先考虑躲避蜘蛛、飞过来的东西 
					logMessage("instant1"); 
					npos=ghost_instant_pos(gt.pos,spat);
					int cnt=10;//最多找10次，多了就不找了
					while(cnt>0&&!ghost_through(gt.pos,npos,-1,spat.can_through())){//不能瞬移到npos就换一个 
						npos=ghost_instant_pos(gt.pos,spat);
						cnt--;
					}
					use_instant=true;
					d=4;
				}
				else if(spat.attack==INSTANT&&RAND_BOOL(spat.ins.p)//能瞬移 
				&&POS.ist.player<lst_see_time){
					logMessage("instant2"); 
					npos=ghost_instant_pos(gt.pos,spat);
					use_instant=true;
					d=4;
				}
				else if(spat.attack==INSTANT&&(MHT_DIST_p3(gt.pos,player1.pos)<spat.ins.dis*2)
				&&RAND_BOOL(spat.ins.p)){//瞬移到玩家旁边 
					logMessage("instant3"); 
					npos=ghost_instant_pos(player1.pos,spat);
					use_instant=true;
					d=4;
				}
				else if(d==4){ 
					if(stair_here(npos)){//上下楼
						logMessage("stair"); 
						if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
						else npos.z--;
					}
					else if(POS.things.nst.exist){//进巢穴口
						logMessage("nest"); 
						position_3D npos2=POS.things.nst.to;
						MAP &POS2=game_map[npos2.x][npos2.y][npos2.z];
						npos.x=npos2.x;npos.y=npos2.y;npos.z=npos2.z;//移动到对应的巢穴口
					}
				}
				else{//普通移动 
					logMessage("normal d="+int_to_str(d)); 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				if(npos!=gt.pos//防止瞬移鬼作妖 
				&&ghost_through(gt.pos,npos,d,spat.can_through())){
					logMessage("move"); 
					if(NTHING.mvb.exist&&!NPOS.fcmv.lock&&d<4){//下一步有（可以推的）东西
						push_thing(npos,d,1);//推动物品 
						position_3D u=dtp3(npos,d,4);//此时物品所在的位置
						MAP &MPOS=game_map[u.x][u.y][u.z]; 
						thing &MTHING=MPOS.things; 
						if(MTHING.mvb.kind!=BOX&&!wks.exist()//虚弱时扔不了东西 
						&&RAND_BOOL(POS.ist.other==lst_see_time&&POS.see(GHOST,gt.spat.attack)&&POS.see_fr()?40:20)){//有概率扔出去，看到玩家时概率更大 
							int angle=calc_angle(gt.pos,player1.pos),angle2=(d+3)%4*90;//angle:朝玩家扔 angle2:朝正前方扔 
							if(vtg.exist()) angle=RAND(359,0);//眩晕时会乱扔东西 
							if((angle-angle2+360)%360>90&&(angle2-angle+360)%360>90) angle=angle2;//别砸自己身上 
							throw_thing(u,15.0/MPOS.mass(),0,angle,MP(GHOST,id));
							throw_thing(gt.pos,2.5*MPOS.mass()/POS.mass(),0,(angle+180)%360,MP(GHOST,id));//反弹力 
						}
					}
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					NPOS.player_enemy=GHOST;NPOS.emy.id=id;
					if(POS.ist.player==lst_see_time&&gt.pos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(gt.pos);
						if(THING.crt.exist){
							game_flag["帘子摇动"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(gt.pos);//帘子动了光照更新 
						}
					}
					if(NPOS.ist.player==lst_see_time&&npos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.insert(npos);
						if(NTHING.crt.exist){
							game_flag["帘子摇动"]=true;
							if(NPOS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(npos);//帘子动了光照更新 
						}
					}
					if(NTHING.snt.exist()) vibrate_spider_net(npos,20*1000);//振动蜘蛛网 
					light &NLGT=NTHING.lgt;
					if(NLGT.exist&&NLGT.state==0&&NPOS.brightness+NLGT.p<-10
					&&!(spat.attack==VAMPIRE||spat.can_disappear())){//吸血、隐身鬼不会主动开灯 
						NLGT.state=1;//关着的灯在亮度适中情况下可以打开 
						pos_affect_light.push(npos);//灯开了光照更新
					}
					gt.pos=npos;
				}
				else if(npos!=gt.pos){//防止瞬移鬼作妖 
					logMessage("block"); 
					int rev_d=(d<4?turn(d,TURN_BACK):0);//d的反方向 
					if(d<4&&closed_box_here(gt.pos,d)){
						if(POS.ist.player==lst_see_time&&MHT_DIST_p3(player1.pos,gt.pos)<=2&&gt.pos.z==player1.pos.z
						//看到玩家并且同一楼层、距离较近 
						||lfin.change==2){
						//或者遭到攻击 
							THING.mvb.door[d]=1;//所在箱子打开门 
							if(POS.ist.player==lst_see_time) game_flag["开门"]=true;
							if(POS.update_light()) pos_affect_light.push(gt.pos);//光照更新
						}
					}
					else if(d<4&&closed_box_here(npos,rev_d)){
						NTHING.mvb.door[rev_d]=1;//面前箱子打开门
						if(NPOS.ist.player==lst_see_time) game_flag["开门"]=true;
						if(NPOS.update_light()) pos_affect_light.push(npos);//光照更新
					}
					else if(d==4&&!box_here(gt.pos)&&!box_here(npos)||d<4){
						int angle=(d+3)%4*90;
						int angle2=(d<4?(RAND(90,-90)+angle+360)%360:RAND(359,0));
						if(door_here(npos,2)){
							NTHING.kdr.state=1;
							shut_door(npos,gt.pos,MP(GHOST,id));//开门摔门 
							if(NPOS.update_light()) pos_affect_light.push(npos);//门开了光照更新
							if(NPOS.ist.player==lst_see_time) game_flag["开门"]=true;//开门视野更新 
						}
						else if(NTHING.mvb.exist&&NTHING.mvb.kind!=BOX
						&&RAND_BOOL(50+max(0,20-MHT_DIST_p3(player1.pos,npos)))){//扔东西 
							throw_thing(npos,15.0/NPOS.mass(),0,angle2,MP(GHOST,id));
							throw_thing(gt.pos,2.5*NPOS.mass()/POS.mass(),0,(angle2+180)%360,MP(GHOST,id));//反弹力 
						}
						else if(NTHING.windows.exist){
							window &WDN=NTHING.windows;
							WDN.damage(20,npos); 
						}
						int door_d=(d==4?0:turn(d,TURN_BACK,4,15));//箱门
						if(!vtg.exist()){//眩晕时无法攻击
							//移动受到阻碍的攻击
							/* 对玩家的暂时取消 
							if(NPOS.player_enemy==PLAYER&&!use_instant&&NPOS.see(GHOST,gt.spat.attack)&&POS.see_fr()
							&&!(d==4?box_here(npos):closed_box_here(npos,door_d))){
								//够得着、看得清才攻击 
								player_reduce_blood(5.0/gt.vlc.speed,MP(GHOST,id));
								if(spat.attack==VAMPIRE) ghost_reduce_blood(id,-1);//鬼吸血
							}
							else*/ 
							if(enemy_here(npos)){//打虫子和蜘蛛，更新生物 
								if(!use_instant&&(bug_here(npos)||spider_body_here(npos))){//要排除掉瞬移来的情况 
									throw_thing(npos,15.0/NPOS.mass(),0.3,angle,MP(GHOST,id));
									throw_thing(gt.pos,2.5*NPOS.mass()/POS.mass(),0,(angle+180)%360,MP(GHOST,id));//反弹力 
								}
								update_being(npos);
							} 
						}
					}
				}
				gt.d=d;
			}//循环2：主体循环 
		}
	void deal_enemy(){
		logMessage("deal_enemy()",2);
		deal_bug();
		deal_spider();
		deal_ghost();
	}
				void player_erase_flashlight(){//清理上次手电筒的照射区域并更新手电筒的信息 
					flashlight &flt=player1.items.flt;
					queue<pair<position_3D,int> > &lst=flt.lst;
					while(!lst.empty()){
						pair<position_3D,int> x=lst.front();lst.pop();
						position_3D u=x.first;
						int sub=x.second;
						game_map[u.x][u.y][u.z].brightness-=sub;
					}
				}//每次玩家视野计算前必须调用！ 
				void player_update_flashlight(position_3D pos){//玩家手电筒照到pos位置 
					bool state=player1.items.flt.state;
					if(!state) return;//关了就不更新了 
					int tmp=player1.angle;//玩家方向对应的方向角 (player1.d2+3)%4*90
					flashlight &flt=player1.items.flt;
					queue<pair<position_3D,int> > &lst=flt.lst;
					int add=pos_to_brightness2(player1.pos,pos,flt.p,tmp,flt.angle);//手电筒更新 
					if(add>0){
						game_map[pos.x][pos.y][pos.z].brightness+=add;
						lst.push(make_pair(pos,add));//留给下次更新重置 
					}
				}
				void calculate_vision(position_3D pos,vector<position_3D> &ret,int dir,bool mir,bool pl_ot,int mx_dis){//计算在pos位置向d方向看的视野
					//只返回能看到的地方，不进行任何视野更新的标记 
					//pl_ot：0鬼 1玩家  mx_dis：最远距离（曼哈顿） 
					ret.clear();//清空 
					int cnt=player1.spe.xry.num;//透视 
					position_3D npos=pos;
 					int door_d=turn(dir,TURN_BACK);
 					do{
						npos=dtp3(npos,dir,4);
						if(!pos_in_area2(npos.x,npos.y,1,1,length,width)) return;
						//超出地图范围就可以直接走人了
						if(MHT_DIST_p3(npos,pos)>mx_dis) return;
						//超出距离 
						MAP &POS=game_map[npos.x][npos.y][npos.z];
						/*
						if(POS.ist.player<game_time){
							if(!screen_pos.count(position_3Dtoscr(npos))) pos_in_sight.push(npos);
							//玩家看得见的格子入队
							screen_z[position_3Dtoscr(npos)]=npos.z;//修改屏幕上这个位置所处的楼层（覆盖之前） 
							if(pl_ot) POS.ist.player=game_time;//标记游戏地图
							else if(!mir&&cnt==player1.spe.xry.num) POS.ist.other=game_time;
							update_being(npos);//更新生物 
						}*/
						if(pl_ot||!mir&&cnt==player1.spe.xry.num) ret.push_back(npos);
						if(light_through2(npos,door_d,pl_ot+1)){
							int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT);
							position_3D pos1=dtp3(npos,d1,4),pos2=dtp3(npos,d2,4);
							/*
							if(game_map[pos1.x][pos1.y][pos1.z].ist.player<game_time){
								pos_in_sight.push(pos1);
								screen_z[position_3Dtoscr(pos1)]=pos1.z;
								if(pl_ot) game_map[pos1.x][pos1.y][pos1.z].ist.player=game_time;
								else if(!mir) game_map[pos1.x][pos1.y][pos1.z].ist.other=game_time;
							}*/
 							if(pl_ot||!mir) ret.push_back(pos1);
							/*
							if(game_map[pos2.x][pos2.y][pos2.z].ist.player<game_time){
								pos_in_sight.push(pos2);
								screen_z[position_3Dtoscr(pos2)]=pos2.z;
								if(pl_ot) game_map[pos2.x][pos2.y][pos2.z].ist.player=game_time;
								else if(!mir) game_map[pos2.x][pos2.y][pos2.z].ist.other=game_time;
							}*/
 							if(pl_ot||!mir) ret.push_back(pos2);
							if(POS.things.mirrors.exist){ 
								mirror &MIRROR=POS.things.mirrors;
								int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=MIRROR.dir;
								int mx_dis2=mx_dis-MHT_DIST_p3(pos,npos);//新距离 
								if(MIRROR.side==1){
									if(dir==d3) calculate_vision(npos,ret,d2,1,pl_ot,mx_dis2);
									else if(d2==d3) calculate_vision(npos,ret,d1,1,pl_ot,mx_dis2);
								}
								else{
									if(dir%2==d3) calculate_vision(npos,ret,d2,1,pl_ot,mx_dis2);
									else calculate_vision(npos,ret,d1,1,pl_ot,mx_dis2);
								}
							}
						}
						else{
							int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=turn(dir,TURN_BACK);
							position_3D pos1=dtp3(npos,d1,4),pos2=dtp3(npos,d2,4),pos3=dtp3(pos1,d3,4);
 							if(light_through2(pos3,door_d,pl_ot+1)&&(pl_ot||!mir)) ret.push_back(pos1);
							pos3=dtp3(pos2,d3,4);
 							if(light_through2(pos3,door_d,pl_ot+1)&&(pl_ot||!mir)) ret.push_back(pos2);
						}
						if(!light_through2(npos,door_d,pl_ot+1)) cnt--;
					}while(cnt>0);//视线可以穿过就继续计算（至少会看见一个格子）
				}
			void player_calculate_vision1(int d){//计算玩家的视野
				//if(block_light(pos)) return;//玩家位置的东西挡住全部视野 
				MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				if(POS.ist.player<game_time){//防止重复浪费时间 
					if(!screen_pos.count(position_3Dtoscr(player1.pos)))//屏幕上这个位置没有显示内容
						pos_in_sight.push(player1.pos);//标记玩家所在的位置、入队
					screen_z[position_3Dtoscr(player1.pos)]=player1.pos.z;//修改屏幕上这个位置所处的楼层
					POS.ist.player=game_time;
					if(!block_light(player1.pos)) POS.ist.other=game_time;
					player_update_flashlight(player1.pos);
				}
				vector<position_3D> ret;
				if(d!=-1){
					//玩家视野单方向计算（无视箱门阻挡）但只有面前这个方向 
					int mx_dis=(player1.spe.bds.exist()?player1.spe.bds.vision_dis:INF);//视野最大距离 
					calculate_vision(player1.pos,ret,d,0,1,mx_dis);//玩家 
					for(int i=0;i<ret.size();i++){
						position_3D u=ret[i];
						MAP &UPOS=game_map[u.x][u.y][u.z];
						if(UPOS.ist.player<game_time){//防止重复浪费时间 
							pos_in_sight.push(u);
							screen_z[position_3Dtoscr(u)]=u.z;
							game_map[u.x][u.y][u.z].ist.player=game_time;//玩家 
							player_update_flashlight(u);//手电筒能照到这里 
	 						update_being(u);//更新生物 
	 					}
					}
				}
				for(int i=0;i<4;i++){//枚举4方向 
					if(closed_box_here(player1.pos,i)) continue;//玩家位置的东西挡住敌人此方向视野 
					calculate_vision(player1.pos,ret,i,0,0,INF);//敌人 
					for(int j=0;j<ret.size();j++){
						position_3D u=ret[j];
						//不重复标记pos_in_sight和screen_z 
						MAP &UPOS=game_map[u.x][u.y][u.z];
						if(UPOS.ist.other<game_time){//防止重复浪费时间 
							game_map[u.x][u.y][u.z].ist.other=game_time;//敌人 
							update_being(u);//更新生物 
						}
					}
				}
			}
				void vision_init(int k,vector<PII > v,vector<position_3D> &ret,position_3D pos){//每次计算前重置（k：透视） 
					for(int i=0;i<4;i++) cnt_visible[i]=0;
					memset(occlusion,0,sizeof(occlusion));
					for(int i=0;i<4;i++){
						for(int j=v[i].first;j!=v[i].second;j=(j+1)%360){//a~b 0=>b+1~a-1 1
							occlusion[i][j]=k;
							cnt_visible[i]++;
						}
						occlusion[i][v[i].second]=k;
						cnt_visible[i]++; 
					}
					/*
					if(pos!=pos000&&block_light(pos)){//初始位置有东西遮挡视野 
						movable &MVB=game_map[pos.x][pos.y][pos.z].things.mvb;
						position_3D u[4];
						u[0]=u[1]=u[2]=u[3]=pos;
						for(int i=0;i<4;i++) u[i].x+=(i&1),u[i].y+=(i&2);//初始位置四个格点 
						int tmp[4][4]={{0,1,2,3},{1,3,0,2},{3,2,0,1},{2,0,1,3}};//tmp[i][0,1]为遮挡点，[2,3]为计算点 
						for(int i=0;i<4;i++)//当前箱门方向 
							if(MVB.door[i]==0)
								for(int j=2;j<4;j++){//哪个计算点
									int p=tmp[i][j],q=tmp[i][0],r=tmp[i][1];
									int a=calc_angle(u[p],u[q]);
									int b=calc_angle(u[p],u[r]);
									if(cmpa(b,a)) swap(a,b);
									mark_lose_sight_area(p,a,b);
									//不贴脸的点
									a=calc_angle(u[p],u[q]);b=calc_angle(u[q],u[p]);
									int c,d;
									c=d=(i+3)%4*90;//重叠点的遮挡方向 
									if(cmpa(c,a)) swap(a,c);
									mark_lose_sight_area(q,a,c);
									if(cmpa(d,b)) swap(b,d);
									mark_lose_sight_area(r,b,d);
									//贴脸的点 
								}
					}*/
					memset(vague,0,sizeof(vague));//全部清空 
					ret.clear();//使用前清空 
				}
				void calculate_vision2(position_3D pos,int pl_ot,vector<position_3D> &ret,int mx_dis,bool vague){
					//以pos为光源计算光照/视野范围（同一层） 
					//ret：范围内的位置 pl_ot=0：透视帘子 1：不透视帘子 （本质是激光/普通光） vague：是否计算模糊值 
					//超出mx_dis就不考虑了 
					//格子的四角：(x,y)->0,(x+1,y)->1,(x,y+1)->2,(x+1,y+1)->3 
					//vision_init处理即可（if(block_light(pos)) return;//玩家位置的东西挡住全部视野 ） 
					int x=pos.x,y=pos.y,z=pos.z;
					memset(vst,0,sizeof(vst));
					while(!Q.empty()) Q.pop();
					vst[x][y][z]=1;
					ret.push_back(pos); 
					Q.push(pos);
					if(block_light(pos)){//初始位置有东西遮挡视野 
						movable &MVB=game_map[pos.x][pos.y][pos.z].things.mvb;
						for(int d=0;d<4;d++){
							position_3D u=dtp3(pos,d,4);
							if(MVB.door[d]==0) mark_occlusion(u,pos,0);//把箱门转化为一个方块处理 
						}
					}
					while(!Q.empty()&&(cnt_visible[0]||cnt_visible[1]||cnt_visible[2]||cnt_visible[3])){
						position_3D u=Q.front();Q.pop();
						movable &UMVB=game_map[u.x][u.y][u.z].things.mvb;
						for(int i=0;i<4;i++){
							position_3D v=u;v.x+=dx4[i];v.y+=dy4[i];
							MAP &POS=game_map[v.x][v.y][z];
							movable &MVB=POS.things.mvb;
							if(!pos_in_area2(v.x,v.y,1,1/*,200,200,超出边缘的视野*/,length,width)
							||vst[v.x][v.y][z]
							||NED_p3(pos,v)>mx_dis//超出最远距离也不行（欧几里得距离）
							)//u有箱门阻挡 ||box_here(u)&&UMVB.door[i]==0
								continue;
							//||box_here(v)&&MVB.door[turn(i,TURN_BACK)]==0 v（反方向）有箱门阻挡 
							vst[v.x][v.y][z]=1;
							if(invisible(pos,v)) continue;
							ret.push_back(v);
							if(vague)//先计算模糊效果
								calc_mark_vague(v,pos);//更新v的视野信息（模糊值），如果v造成模糊标记一下 
							if(!light_through(v,pl_ot)) mark_occlusion(v,pos);//鬼（0+1）透视帘子，玩家（1+1）不行  
							if(!invisible(pos,v)) Q.push(v); 
						}
					}
					game_timer["循"]++;
				}
			void player_calculate_vision2(){//计算视野并更新手电筒 
				game_timer["see"]++;
				vector<PII > v(4);vector<position_3D> ret;
				int tmp=player1.angle;//玩家方向对应的方向角 (player1.d2+3)%4*90
				for(int i=0;i<4;i++) v[i]=MP((tmp-120+360)%360,(tmp+120+360)%360);
				while(!pos_vague.empty()){//每次计算玩家视野前清除掉上次模糊的地方 
					position_3D pos=pos_vague.front();pos_vague.pop();
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					memset(POS.ist.vague,0,sizeof(POS.ist.vague));//清零 
				}
				vision_init(player1.spe.xry.num,v,ret,player1.pos);
				position_2D scr_mouse=pos_mouse();//鼠标的屏幕位置 
				position_3D map_mouse=position_scrto3D(scr_mouse,player1.pos.z);//鼠标的地图位置
				int player_sight_dis=(player1.spe.bds.exist()?player1.spe.bds.vision_dis:NED_p3(map_mouse,player1.pos));
				//玩家视野范围受失明效果和鼠标位置的限制 
				calculate_vision2(player1.pos,2,ret,player_sight_dis,1);//玩家部分视野 
				for(int i=0;i<ret.size();i++){//包含了player1.pos 
					position_3D pos=ret[i];
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					light &LGT=THING.lgt;
					if(POS.ist.player<game_time){//防止重复浪费时间 
						POS.ist.player=game_time;
						if(!screen_pos.count(position_3Dtoscr(pos))) pos_in_sight.push(pos);
						screen_z[position_3Dtoscr(pos)]=pos.z;
						update_being(pos); 
						player_update_flashlight(pos);
					}
					if(LGT.exist&&LGT.update) update_light_brightness(pos,0);//视野范围内灯光重算 
					if(POS.ist.vague_exist()) pos_vague.push(pos);//模糊的位置入队，方便清零 
				}
				for(int i=0;i<4;i++) v[i]=MP(0,359);
				vision_init(1,v,ret,player1.pos);
				calculate_vision2(player1.pos,1,ret,INF,0);//（敌人）全部视野 
				for(int i=0;i<ret.size();i++){
					position_3D pos=ret[i];
					MAP &POS=game_map[pos.x][pos.y][pos.z];
					thing &THING=POS.things;
					light &LGT=THING.lgt;
					if(POS.ist.other<game_time){//防止重复浪费时间 
						POS.ist.other=game_time;
						update_being(pos); 
					}
					if(LGT.exist&&LGT.update) update_light_brightness(pos,0);//视野范围内灯光重算
				}
			}
				void add_fog(position_3D pos,double r,double g,double b){//新增雾气 
					fog &FOGS=game_map[pos.x][pos.y][pos.z].things.fogs;
					FOGS.absorbance[0]+=r;
					FOGS.absorbance[1]+=g;
					FOGS.absorbance[2]+=b;
					FOGS.update=true;
					pos_fog.push(pos);
				}
				void player_have_food(int kind,int effect){
					if(kind==ADDS){
						player_reduce_blood(-(1<<(EFFECT_OF_FOOD-effect))*5,MP(PLAYER,-1));//增加生命值 
						player1.items.num_change=true;
					}
					else{
						player_add_stg((1<<(EFFECT_OF_FOOD-effect))*10);//增加体力值 
						player1.items.num_change=true;
					}
				}
				void player_use_ppt(int kind,int time){
					x_ray &xry=player1.spe.xry;
					xry.num+=kind;
					if(xry.time<=game_time) xry.time=game_time+time;
					else xry.time+=time;
					xry.change=true;
					game_flag["玩家视野参数改变"]=true;
				}
			void player_use_item(){//玩家（按E）使用物品 
				MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
				item &items=player1.items;
				weapon_carried wpn=items.wpn;
				vector<int> &v=items.item_lab;
				int x=items.select_number;
				if(x<0||x>=v.size()) return;
				int id=v[x];
				if(id<0) return;
				object &ob=objects[id];
				int k=ob.type;
				life_injury &lfin=player1.vts.lfin;
				strength &stg=player1.vts.stg;
				bool del=false;
				switch(k){
					case FOO:
						player_have_food(ob.foods.kind,ob.foods.effect);
						del=true;//用完了要删掉 
						break;
					case SMO:
						add_fog(player1.pos,10000,10000,10000);
						del=true;//用完了要删掉
						break;
					case PER:
						player_use_ppt(ob.stp.kind,ob.stp.time);
						del=true;
						break;
					case LAS:case DAR:case SPE:case DAG:case SWO:case BLA:
						add_weapon(x);
						//自动轮换武器 
						break; 
				}
				if(del){
					del_object2(x);//记得删掉用了的物品 
				}
				player1.items.il_change=true;
			} 
							void damage_curtain(position_3D u,int hurt=1){
								MAP &POS=game_map[u.x][u.y][u.z];
								thing &THING=POS.things;
								curtain &CRT=THING.crt;
								CRT.endurance-=hurt;
								if(POS.ist.player==lst_see_time){
									game_flag["物品损坏"]=true;
									pos_change.insert(u);
								}
								if(CRT.endurance<=0){
									CRT.init();
									if(POS.update_light()) pos_affect_light.push(u);//帘子没了更新光照 
									game_flag["物品消失"]=true;
								}
							}
							bool laser_beam_through(position_3D pos,position_3D u,int angle){//以pos格子中心为起点，发射角度为angle的射线是否经过u
								pos.x=pos.x*2+1;pos.y=pos.y*2+1;
								int mn=-1,mx=-1;//最小/大角 
								for(int i=0;i<4;i++){
									position_3D v=u;v.x+=bool(i&1);v.y+=bool(i&2);//u格子的某个角 
									v.x*=2;v.y*=2;
									int a=calc_angle(pos,v);//计算起点到这个角的方向角 
									if(mn==-1||cmpa(a,mn)) mn=a;//a<mn
									if(mx==-1||cmpa(mx,a)) mx=a;//mx<a
								}
								return cmpa(mn,angle)&&cmpa(angle,mx);//发射角度在范围内 
							}
							void make_laser_beam_brightness(position_3D pos,int p){
								vector<PII > v;vector<position_3D> ret;
								for(int i=0;i<4;i++) v.push_back(MP(0,359));
								vision_init(1,v,ret,pos);
								calculate_vision2(pos,1,ret,p,0);//mx_dis=p限制计算范围，节约算力 
								for(int i=0;i<ret.size();i++){
									position_3D u=ret[i];
									MAP &POS=game_map[u.x][u.y][u.z];
									thing &THING=POS.things;
									if(light_through(u,1)){
										int tmp=pos_to_brightness(pos,u,p);
										POS.brightness+=tmp;
										laser_beam_light.push(MP(u,tmp));//(照亮的位置,亮度增幅)
										if(POS.ist.player==lst_see_time) pos_change.insert(u);
									}
								}
							}
						int player_shoot_laser_beam2(position_3D pos,int angle){//0~359 返回命中的格子数量 
							vector<PII > v;vector<position_3D> ret;
							int a1=(angle+1)%360,a2=(angle-1+360)%360;
							for(int i=0;i<4;i++) v.push_back(MP(a2,a1));
							vision_init(1,v,ret,pos);
							calculate_vision2(pos,1,ret,INF,0);
							int cnt=0;
							for(int i=0;i<ret.size();i++){
								position_3D u=ret[i];
								MAP &POS=game_map[u.x][u.y][u.z];
								thing &THING=POS.things;
								if(u==pos||!laser_beam_through(pos,u,angle)) continue;
								if(light_through(u,1)&&u!=pos){
									THING.lsr.exist=true;
									cnt++;
								}
								laser_beams.push(u);
								
								//if(!nobody_here(u)) make_laser_beam_brightness(u,7);//命中一些东西发光 
								POS.brightness+=40;//加个发光效果？ 
								
			 					if(POS.ist.player==lst_see_time) pos_change.insert(u);//屏幕更新 
			 					if(nobody_here(u)&&THING.nst.exist&&THING.nst.id!=-1){//命中虫子的巢穴口
			 						position_3D v=THING.nst.to;
			 						MAP &NPOS=game_map[v.x][v.y][v.z];
			 						thing &NTHING=NPOS.things;
								 	nest &NST=THING.nst,&NST2=NTHING.nst;
								 	int id=NST.id;
								 	bug_nest &bns=bug_nests[id];
								 	bns.lfin.life--;bns.lfin.change=2;//造成伤害 
								 	bns.lfin.last_injury_from=MP(PLAYER,-1);
									bns.lfin.last_injury_time=game_time;
								 	if(bns.lfin.life<=0){//打没掉 
								 		NST.exist=false;
										NST.id=-1;
										NST2.exist=false;
										NST2.id=-1;
									}
								}
								hurt_enemy(POS);
								if(THING.crt.exist) damage_curtain(u);
							}
							return cnt;
						}
					void player_use_laser_gun012(int k){
						if(game_timer["激光枪冷却"]>game_time) return;//还没冷却好就不管了 
						item &items=player1.items;
						weapon_carried &wpn=items.wpn;
						laser_gun_info &lsg=wpn.lsg;
						if(object_type(wpn.primary)!=LAS) return;
						int id=items.item_lab[wpn.primary];
						object &ob=objects[id];
						bool use=false;//是否使用了 
						if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,player1.angle)){//至少有1格可以射 
							object_addE(wpn.primary,-1);
							use=true; 
						}
						int ang[5];//注意不要越界 
						ang[0]=player1.angle;
						for(int i=1;i<5;i++) ang[i]=ang[i-1]+pow(-1,i)*i*5;
						if(k>=1){//在上面基础上补
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[1])){
								object_addE(wpn.primary,-1);
								use=true; 
							}
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[2])){
								object_addE(wpn.primary,-1);
								use=true; 
							}
						}
						if(k==2){//在上面基础上补
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[3])){
								object_addE(wpn.primary,-1);
								use=true; 
							}
							if(ob.lsrE>0&&player_shoot_laser_beam2(player1.pos,ang[4])){
								object_addE(wpn.primary,-1); 
								use=true; 
							}
						}
						if(use){//打出去了 
							game_timer["清除激光束"]=game_time+lsg.last_time;game_timer["激光枪冷却"]=game_timer["清除激光束"]+lsg.cool_time;
							player1.use_weapon=true;
							player1.scr.shoot_times++;//玩家信息更新 
							MUSIC("Laser2.wav",1);//提示音 
						}
					}
				void player_use_laser_gun(){
					weapon_carried &wpn=player1.items.wpn;
					laser_gun_info &lsg=wpn.lsg;
					player_use_laser_gun012(0);
					/*
					int k=lsg.kind;
					switch(k){
						case 0:case 1:case 2:
							player_use_laser_gun012(k);//if(lsg.energy>=2*k+1) 提前判断能量是否足够？ 
							break;
						case 3:
							break;
						case 4:
							break;
					}*/
				}
			    void player_use_dart(){//生成扔出的回旋镖并加入回旋镖队列 
					weapon_carried &wpn=player1.items.wpn;
					int x=wpn.primary;//武器在物品栏中的编号 
					if(object_type(x)!=DAR) return;
					int id=player1.items.item_lab[x];//武器id 
					flying_dart fdt;
					dart &DRT=game_map[player1.pos.x][player1.pos.y][player1.pos.z].things.drt; 
					fdt.init(player1.pos,player1.angle,id);//从玩家位置扔出 
					darts.push(fdt);//加入队列 
					DRT.num[1]++;//地图更新
					player1.scr.shoot_times++;//玩家信息更新 
					del_object2(x); 
					//消耗一个飞镖 
					game_timer["扔回旋镖冷却"]=game_time+200;
					MUSIC("丢飞镖2.wav",1);//飞镖嗖得飞过的声音 
				}
			void player_use_weapon(){
				weapon_carried &wpn=player1.items.wpn;
				laser_gun_info &lsg=wpn.lsg;
				vector<int> &v=player1.items.item_lab;
				int type=object_type(wpn.primary);
				if(!type_weapon(type)) return;
				switch(type){
					case LAS:
						if(game_timer["激光枪冷却"]<=game_time) player_use_laser_gun();
						break;//ob.lsrE>=lsg.kd_energy[lsg.kind]&&
					case DAR:
						if(game_timer["扔回旋镖冷却"]<=game_time
						&&!game_map[player1.pos.x][player1.pos.y][player1.pos.z].things.drt.exist1()) player_use_dart();
						break;//object_cnt(id)>=1&&
				}
 			}
			    void player_erase_spear(){//清理上次显示的矛 
		    		while(!spears.empty()){
		    			position_3D u=spears.front();spears.pop();
		    			if(game_map[u.x][u.y][u.z].ist.player==lst_see_time)
							pos_change.insert(u),game_flag["玩家矛改变位置"]=true;
			    		MAP &POS=game_map[u.x][u.y][u.z];
			    		POS.things.spr.exist=false;
			    		hurt_enemy(POS);//取消伤害效果
			    		/*
			    		if(curtain_here(u)){
							game_flag["帘子摇动"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(u);//帘子摆动更新光照  
						}*/
			    	}
			    }
			    void player_use_spear(position_3D pos,int angle,int dir,int le=2){ 
					weapon_carried &wpn=player1.items.wpn;
					int x=wpn.primary;
					if(object_type(x)!=SPE) return;
					if(objects[player1.items.item_lab[x]].sprE<=0)
						del_object2(x);//自动换弹 
					if(object_type(x)!=SPE) return;
					int a2=(dir+3)%4*90;
					bool kind=0;
					int d2=0;
					position_3D npos;
					if(sub_angle(a2,angle)>22){//22.5° 
						if(angle<a2) d2=(dir+3)%4;
						else d2=(dir+1)%4;
						if(dir==3&&d2==0||dir==0&&d2==3) dir=7;
						else dir=dir+d2;
						npos=dtp3(pos,dir,8);
						le/=1.414;
						kind=1;
					}
		    		else{
		    			npos=dtp3(pos,dir,4);
						kind=0;
					}
					position_3D lpos=pos;
					int i=1;
		    		while(1){
		    			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
		    			thing &NTHING=NPOS.things;
		        		if(NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
						||wall_here(npos)||exit_here(npos)||ghost_here_d(npos,ROCK)||i>le){//矛碰到箱子、墙、石化鬼或矛的长度不够 
		    				MAP &LPOS=game_map[lpos.x][lpos.y][lpos.z];
		    				if(i!=1) LPOS.things.spr.head=true;
		        			break;
					    }
					    hurt_enemy(NPOS);
			    		if(curtain_here(npos)){
							game_flag["帘子摇动"]=true;
							if(NPOS.update_light()&&NPOS.ist.player==lst_see_time) pos_affect_light.push(npos);//帘子摆动更新光照  
						}
						NTHING.snt.addedc(-10,npos); 
			    		spear &spr=NTHING.spr;
			    		spr.exist=true;
						if(kind==0) spr.d=dir*2;
						else spr.d=dir;
						spr.head=false;
			    		//if(NPOS.ist.player==lst_see_time) pos_change.insert(npos);
						spears.push(npos);
			    		lpos=npos;
						if(kind==0) npos=dtp3(npos,dir,4);
						else npos=dtp3(pos,dir,8);
						i++;
			    	}
		    	}
			void player_update_spear(){//矛自动更新
				player_erase_spear();
				player_use_spear(player1.pos,player1.angle,atd(player1.angle),2); 
			}
				void player_erase_sword(){
					while(!swords.empty()){
		    			position_3D u=swords.front();swords.pop();
		    			if(game_map[u.x][u.y][u.z].ist.player==lst_see_time)
							pos_change.insert(u),game_flag["玩家剑改变位置"]=true;
			    		MAP &POS=game_map[u.x][u.y][u.z];
			    		POS.things.swd.exist=false;
			    		if(curtain_here(u)){
							game_flag["帘子摇动"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(u);//帘子摆动更新光照  
						}
			    	}
				}
				void player_use_sword(position_3D pos,int angle,int dir,int le){
					int a2=(dir+3)%4*90;
					bool kind=0;
					int d2=0;
					position_3D npos;
					if(sub_angle(a2,angle)>22){//22.5° 
						if(angle<a2) d2=(dir+3)%4;
						else d2=(dir+1)%4;
						if(dir==3&&d2==0||dir==0&&d2==3) dir=7;
						else dir=dir+d2;
						npos=dtp3(pos,dir,8);
						//length/=1.414;去掉防止斜着没有 
						kind=1;
					}
		    		else{
		    			npos=dtp3(pos,dir,4);
						kind=0;
					}
					int i=1;
		    		while(1){
		    			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
		    			thing &NTHING=NPOS.things;
		        		if(NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
						||wall_here(npos)||exit_here(npos)||ghost_here_d(npos,ROCK)||ghost_here_d(npos,SHIELD)
						||NPOS.ist.player<lst_see_time||i>le){
						//剑碰到箱子、墙或在视野范围外或剑的长度不够 
		        			break;
		        		}
		        		if(enemy_here2(npos)&&!NPOS.fcmv.lock){
		        			//living_things_reduce_blood(npos,5.0,1,MP(PLAYER,-1));
		        			if(player1.w.speed>90){
		        				double v=0.2*player1.w.speed*PI/180;//击飞速度 
		        				throw_thing(npos,v,0.5,player1.angle,MP(PLAYER,-1));
		        				object_addE(player1.items.wpn.primary,-0.01*pow(v,2)*NPOS.mass());
							}
		        			player1.color=5;
		        			player1.flash_word="剑";
		        			player1.flash=true;
							game_timer["玩家图标闪烁"]=game_time+500;
		        			pos_change.insert(player1.pos);
						}
			    		if(curtain_here(npos)){
							game_flag["帘子摇动"]=true;
							if(NPOS.update_light()&&NPOS.ist.player==lst_see_time) pos_affect_light.push(npos);//帘子摆动更新光照  
						}
						NTHING.snt.addedc(-5,npos); 
			    		sword &swd=NTHING.swd;
			    		swd.exist=true;
			    		if(NPOS.ist.player==lst_see_time) pos_change.insert(npos);
						swords.push(npos);
						if(kind==0) npos=dtp3(npos,dir,4);
						else npos=dtp3(pos,dir,8);
						i++;
			    	}
				}
			void player_update_sword(){//剑自动更新 
				player_erase_sword();
				weapon_carried &wpn=player1.items.wpn;
				int x=wpn.primary;
				if(object_type(x)!=SWO) return;
				if(objects[player1.items.item_lab[x]].swordE<=0)
					del_object2(x);//自动换弹 
				if(object_type(x)!=SWO) return;
				//检查类型 
				int start_angle,end_angle;
				if(cmpa(player1.angle,player1.lsta))
					start_angle=player1.angle,end_angle=player1.lsta;
				else
					start_angle=player1.lsta,end_angle=player1.angle;
				for(int i=start_angle;cmpa(i,end_angle);i+=30) player_use_sword(player1.pos,i,atd(i),1); 
				player_use_sword(player1.pos,end_angle,atd(end_angle),1); 
			}
				void player_erase_blade(){
					while(!blades.empty()){
		    			position_3D u=blades.front();blades.pop();
		    			if(game_map[u.x][u.y][u.z].ist.player==lst_see_time)
							pos_change.insert(u),game_flag["玩家刀改变位置"]=true;
			    		MAP &POS=game_map[u.x][u.y][u.z];
			    		POS.things.bld.init();
			    		if(curtain_here(u)){
							game_flag["帘子摇动"]=true;
							if(POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(u);//帘子摆动更新光照  
						}
			    	}
				}
				void player_use_blade(position_3D pos,int angle,int le){
					position_3D lpos=pos;//上一个位置 
					/*
	        			player1.color=5;
	        			player1.flash_word="刀";
	        			player1.flash=true;
						game_timer["玩家图标闪烁"]=game_time+500;
	        			pos_change.insert(player1.pos);*/
	        		int i=1;
					for(;i<=le;i++){
				        int dx=round(i*cos(angle*PI/180.0));
				        int dy=round(i*sin(angle*PI/180.0));
				        //计算当前部分相对于起始位置的偏移量 
						position_3D npos=pos;
						npos.x+=dx;npos.y+=dy;
				        //计算当前部分在网格地图中的位置
		        		//	if(player1.flash_word!="da"&&player1.flash_word!="DA") player1.flash_word="刃";
		    			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
		    			thing &NTHING=NPOS.things;
						if(lpos==npos||NTHING.bld.exist) continue;
				        //检查是否不重复 
		        		//	if(player1.flash_word!="da") player1.flash_word="da";
		        		if(!pos_in_area2(npos.x,npos.y,1,1,length,width,2)||
						NTHING.mvb.exist||door_here(npos,0)||door_here(npos,2)||NTHING.hdr.exist
						||wall_here(npos)||exit_here(npos)||ghost_here_d(npos,ROCK)||ghost_here_d(npos,SHIELD)
						||NPOS.ist.player<lst_see_time){
						//刀碰到箱子、墙或在视野范围外 
							if(lpos!=pos) game_map[lpos.x][lpos.y][lpos.z].things.bld.head=1;
		        			break;
		        		}
		        		//	player1.flash_word="DA";
		        		if(enemy_here2(npos)&&!NPOS.fcmv.lock){
		        			//living_things_reduce_blood(npos,5.0,1,MP(PLAYER,-1));
		        			if(player1.w.speed>90){
		        				double v=0.3*NED(player1.pos.x,player1.pos.y,npos.x,npos.y)*player1.w.speed*PI/180;//击飞速度 
								throw_thing(npos,v,0.5,player1.angle,MP(PLAYER,-1));
								object_addE(player1.items.wpn.primary,-0.01*pow(v,2)*NPOS.mass());
							}
		        			player1.color=5;
		        			player1.flash_word="刀";
		        			player1.flash=true;
							game_timer["玩家图标闪烁"]=game_time+500;
		        			pos_change.insert(player1.pos);
						}
						NTHING.snt.addedc(-5,npos); 
						blade &bld=NTHING.bld;
						bld.exist=1;bld.head=0;
			    		if(NPOS.ist.player==lst_see_time) pos_change.insert(npos);
						blades.push(npos);
						lpos=npos;
				    }
				    if(i>le) game_map[lpos.x][lpos.y][lpos.z].things.bld.head=1;
				}
			void player_update_blade(){//刀自动更新
				player_erase_blade(); 
				weapon_carried &wpn=player1.items.wpn;
				int x=wpn.primary;
				if(object_type(x)!=BLA) return;
				if(objects[player1.items.item_lab[x]].bladeE<=0)
					del_object2(x);//自动换弹 
				if(object_type(x)!=BLA) return;
				//检查类型 
				int start_angle,end_angle;
				if(cmpa(player1.angle,player1.lsta))
					start_angle=player1.angle,end_angle=player1.lsta;
				else
					start_angle=player1.lsta,end_angle=player1.angle;
				for(int i=start_angle;cmpa(i,end_angle);i+=30) player_use_blade(player1.pos,i,2);
				player_use_blade(player1.pos,end_angle,2);
			}
			void player_pickup_object(position_3D pos){//捡拾物品
				thing &THING=game_map[pos.x][pos.y][pos.z].things;
				int id=THING.fir;
				if(id<0) return;
				object &ob=objects[id];
				item &items=player1.items;
				int sn=items.select_number;
				vector<int> &v=items.item_lab;
				bool success=0;
				for(int i=0;i<v.size();i++)
					if(v[i]>=0){
						object ob2=objects[v[i]];
						if(ob==ob2){//堆在一样的上面 
							del_object1(pos);
							add_object2(id,i);
							success=1;
							break;
						}
					}
				if(!success){
					for(int i=0;i<v.size();i++)
						if(v[i]<0){//不然就放在空位置 
							del_object1(pos);
							add_object2(id,i);
							success=1;
							break;
						}
					/*
					if(!success){//再不然新开一个位置 
						v.push_back(-1);
						del_object1(pos);
						add_object2(id,v.size()-1);
					}*/
				}
				/*
				switch(obj.type){
					case KEY:
						if(ob.key){
						}
						break;
				}*/
			}
			void player_discard_object(position_3D pos){//丢弃物品 
				if(!(space_here(pos)&&noitem_here(pos))) return;//违规丢弃 
				item &items=player1.items;
				int sn=items.select_number;
				vector<int> &v=items.item_lab;
				if(sn<0||sn>=v.size()) return;
				int id=v[sn];
				if(id<0) return;
				object &obj=objects[id];
				del_object2(sn);
				add_object1(pos,id);
			}
		void player_detect_move(){
			logMessage("player_detect_move");
			int maze=game_map[player1.pos.x][player1.pos.y][player1.pos.z].maze;
			MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
			thing &THING=POS.things;
			vector<int> &item_lab=player1.items.item_lab;
			removable &rmv=player1.items.rmv;
			int d=player1.d1,tmp;//鼠标跑到外面去方向就不变
			position_2D scr_mouse=pos_mouse();//鼠标的屏幕位置 
			position_3D map_mouse=position_scrto3D(scr_mouse,player1.pos.z);//鼠标的地图位置
			bool mouse_in_area=pos_in_game_map(scr_mouse);//鼠标是否在游戏地图区内 
			if(mouse_in_area&&player1.mpos!=map_mouse){//控制方向
				//formatted_output(1,vital_signs_area,1,11,MMPP(0,360,-100,360),int_to_str(scr_mouse.x,3));
				//formatted_output(1,vital_signs_area,1,12,MMPP(0,360,-100,360),int_to_str(scr_mouse.y,3));
				//formatted_output(1,vital_signs_area,1,13,MMPP(0,360,-100,360),int_to_str(screen_zoom,3));
				player1.mpos=map_mouse;//更新鼠标位置 
				game_flag["玩家视野参数改变"]=true;//
				int mouse_angle=calc_angle(player1.pos,map_mouse);
				if(player1.angle!=mouse_angle){
					player1.w.speed=1.0*sub_angle(player1.angle,mouse_angle)/(game_time-player1.alc)*1000;
					player1.w.vt();
					//更新角速度 
					player1.lsta=player1.angle;
					player1.angle=mouse_angle;
					player1.alc=game_time;
					//更新角度 
					int d2=atd(player1.angle);
					player_update_spear();player_update_sword();player_update_blade();//改变方向就更新矛、剑、刀 
					if(player1.d2!=d2){
						player1.d2=d2;
						player1.d2_change=true;
					}
					//if(game_time%200==0) //限制更新频率
					game_flag["玩家视野参数改变"]=true;
				}
			}
			if(game_timer["玩家移动"]>game_time) return;
			game_timer["玩家移动"]=game_time+player1.vlc.wait_time;
			bool want_move=false;//玩家想要移动 
			position_3D npos;//下一步走到的位置 
			npos=player1.pos;
			int mouse_dis=MHT_DIST_p3(map_mouse,player1.pos);//鼠标到玩家的距离 
			if(KEY_DOWN(VK_LBUTTON)&&game_timer["按下鼠标"]<=game_time&&!game_flag["鼠标单击"]){//鼠标左键
				game_timer["按下鼠标"]=game_time+100;//侦测频率 
				game_flag["鼠标单击"]=true;
				if(mouse_in_area){//在游戏地图区域里 
					if(pos_in_area2(map_mouse.x,map_mouse.y,1,1,length,width)){//地图交互 
						MAP &MPOS=game_map[map_mouse.x][map_mouse.y][map_mouse.z];
						thing &MTHING=MPOS.things;
						item &items=player1.items;
						bool mouse_near=(mouse_dis==1);//就在身旁
						int connect=interconnection_distance(player1.pos,map_mouse,3,pos000);//用于检查玩家能否够得到 
						if(mouse_near&&MTHING.mvb.exist){//（取消）选择拉的物品
							game_flag["拉"]=true;
							position_3D &select=items.rmv.select;
							if(select!=pos000&&game_map[select.x][select.y][select.z].ist.player==lst_see_time)
								pos_change.insert(select);//换一个 
							if(select==map_mouse) select=pos000;//取消选中 
							else select=map_mouse;//原来没有，选择新的 
							player1.pull_thing=true;
							player1.color=3;//提示玩家已拉到物品 
							player1.flash=true;
							game_timer["玩家图标闪烁"]=game_time+500;
							if(MPOS.ist.player==lst_see_time) pos_change.insert(map_mouse); 
						}
						else if(mouse_dis<=2&&door_here(map_mouse,1)){//关上门 
							MTHING.kdr.state=2;
							if(MPOS.update_light()) pos_affect_light.push(map_mouse);//门开了光照更新
							shut_door(map_mouse,player1.pos,MP(PLAYER,-1));//把门摔别的东西脸上 
							game_flag["关门"]=true;
							MUSIC("Door_Closing.wav",1);//提示音 
						}
						else if(mouse_near&&door_here(map_mouse,0)){//这门锁了
							bool unlock=false;
							for(int i=0;i<item_lab.size();i++){//遍历寻找钥匙 
								int id=item_lab[i];
								if(id<0) continue;
								object &ob=objects[id];
								if(ob.type==KEY&&ob.key==MTHING.kdr.kind-DOOR1+KEY1){
									del_object2(i);
									unlock=true;
									break;
								}
							}
							if(unlock){
								MTHING.kdr.state=1;//先用钥匙在开门 
								if(MPOS.update_light()) pos_affect_light.push(map_mouse);//门开了光照更新
								game_flag["开门"]=true; 
								MUSIC("开门.wav",1);//提示音
							}
						}
						else if(mouse_near&&MTHING.windows.exist){ 
							MTHING.windows.state^=1;//开/关
							if(MPOS.update_light()) pos_affect_light.push(map_mouse);//门开了光照更新 
							game_flag["玩家开/关窗户"]=true; 
							if(MTHING.windows.state) MUSIC("开灯.wav",1);//提示音 
							else MUSIC("关灯.wav",1);//提示音
						}
						else if(mouse_dis<=2&&MTHING.lgt.exist
						&&connect!=-1&&connect<=mouse_dis){//开关灯 
							//够得到（防止长臂管辖）
							MTHING.lgt.state=!MTHING.lgt.state;
							update_light_brightness(map_mouse);
						}
						else{
							player_use_weapon();
							return;
						} 
					}
					else{
						player_use_weapon();
						return;
					} 
				}
				else if(scr_mouse.x<=20){
					game_pause=!game_pause;
					game_flag["游戏暂停/继续"]=true; 
					return;
				}
				else if(item_area.contain(scr_mouse)){//点击物品栏 
					player1.action_kind=CHOOSE_ITEM;player1.ak_change=true;
					game_timer["按下鼠标"]=game_time;//一键使用物品，不用按两次 
					return;
				}
				else if(weapon_area.contain(scr_mouse)){//点击武器栏 
					player1.action_kind=CHANGE_WPN;
					player1.ak_change=true;
					return;
				}
				//设置？物品？ 
			}
			else if(game_timer["按下鼠标"]<=game_time) game_flag["鼠标单击"]=false; 
			position_3D throw_pos;
			if(_kbhit()){
				position_3D u=dtp3(player1.pos,player1.d2,4),v=player1.items.rmv.select;//玩家面前（angle）、玩家拉着的
				//position_3D u2=dtp3(player1.pos,fatd(player1.angle),4);//副手方位 
				int delta_angle=sub_angle(player1.angle,calc_angle(player1.pos,v));
				MAP &UPOS=game_map[u.x][u.y][u.z];
				thing &UTHING=UPOS.things;
				flashlight &flt=player1.items.flt;
				char getch=_getch();
				if(getch!=PRESS_KEY_SPACE) game_flag["按空格键"]=false;
				int door_d;
				switch(getch){//侦测按键 
					case PRESS_KEY_W:
						d=0;want_move=true;
						break;
					case PRESS_KEY_D:
						d=1;want_move=true;
						break;
					case PRESS_KEY_S:
						d=2;want_move=true;
						break;
					case PRESS_KEY_A:
						d=3;want_move=true;
						break;
					case PRESS_KEY_TAB:
						flt.state=!flt.state;//开关手电筒 
						flt.change=1;
						break;
					case PRESS_KEY_SPACE:
						if(game_flag["按空格键"]) break; 
						game_flag["按空格键"]=true;
						POS.player_enemy=NOBODY;//便于扔物品 
						//u:玩家面前（angle）  v:玩家拉着的
						if(box_here(u)){//面前是箱子
							door_d=turn(player1.d2,TURN_BACK,4,16);//箱门方向和人方向相反 
							movable &UMVB=UTHING.mvb;
							UMVB.door[door_d]^=1;//箱门 开关切换 
							game_flag["开门"]=true;
							if(UPOS.update_light()) pos_affect_light.push(u);//光照更新
						}
						else if(box_here(player1.pos)){//现在在箱子里
							door_d=player1.d2;//箱门方向和人方向相同 
							movable &MVB=POS.things.mvb;
							MVB.door[door_d]^=1;//箱门 开关切换 
							game_flag["开门"]=true;
							if(POS.update_light()) pos_affect_light.push(player1.pos);//光照更新 
						}
						else if(!nobody_here2(u)//把面前的生物踢出去（踢B型蜘蛛附肢是没用的） 
						||mvb_here(u)&&UTHING.mvb.kind!=BOX//把面前的东西扔出去
						||mvb_here(player1.pos,0)&&push_thing(player1.pos,player1.d2,1)){//处于可移动物品位置且可以推动
							throw_pos=u;//正手位 
							player1.items.rmv.throw_ready=true;
						}
						else if(v!=pos000&&game_map[v.x][v.y][v.z].things.mvb.kind!=BOX//把拉着的物品扔出去
						&&(mvb_through(u,player1.d2)&&push_thing(u,player1.d2,1)||
						v!=player1.pos&&delta_angle<=90)){//扔拉的东西不会砸到自己 
						//(u2==v) 
							if(delta_angle>90) swap(UTHING.mvb,game_map[v.x][v.y][v.z].things.mvb);
							//扔拉的东西哪里方便扔哪里 
							player1.items.rmv.select=pos000; 
							game_flag["拉"]=true;
							if(game_map[v.x][v.y][v.z].ist.player==lst_see_time) pos_change.insert(v);
							if(delta_angle<=90) throw_pos=v;//副手位
							else{
								if(game_map[u.x][u.y][u.z].ist.player==lst_see_time) pos_change.insert(u);//正手位
								throw_pos=u;
							}
							player1.items.rmv.throw_ready=true;
							player_add_stg(-UPOS.mass()*0.5);//体力减少（拉的东西额外减少体力） 
							MUSIC("Whiz.wav",1);//提示音 
						}
						else if(v!=pos000&&(mirror_here(u)||window_here(u))){
							if(mirror_here(u)) UTHING.mirrors.damage(30);//砸镜子 
							else UTHING.windows.damage(20,u);//砸窗户 
							player_add_stg(-5);//体力减少 
						}
						POS.player_enemy=PLAYER;
						break;
					case PRESS_KEY_ESC:
						game_pause=true;
						game_flag["游戏暂停/继续"]=true; 
						return;
					case PRESS_KEY_C:
						if(stair_here(player1.pos)||POS.things.nst.exist){//上下楼/进出巢穴口 
							d=THING.fpt.d=4;//记录足迹
							if(maze==UPSTAIR) npos.z++;
							else if(maze==DOWNSTAIR) npos.z--;
							else npos=THING.nst.to;
						}
						break;
					case PRESS_KEY_E:
						player_use_item();
						return;
					case PRESS_KEY_F:
						door_d=turn(player1.d2,TURN_BACK,4,16);//箱门方向和人方向相同 
						if(!closed_box_here(u,door_d)) player_pickup_object(u);
						return;
					case PRESS_KEY_Q:
						player_discard_object(u);
						return;
					case PRESS_KEY_CTRL:
						player1.color=4;
						game_timer["玩家图标闪烁"]=game_time+200;
						pos_change.insert(player1.pos); 
						break; 
				}
			}
			else game_flag["按空格键"]=false;
			if(player1.items.rmv.throw_ready){//已经为投掷做好准备 
				position_3D u=throw_pos;//投掷物所在位置 
				MAP &UPOS=game_map[u.x][u.y][u.z];
				player_add_stg(-UPOS.mass()*0.5);//体力减少 
				throw_thing(u,15.0/UPOS.mass(),0.3,player1.angle,MP(PLAYER,-1));//脚踢 
				throw_thing(player1.pos,2.5*UPOS.mass()/POS.mass(),0,(player1.angle+180)%360,MP(PLAYER,-1));//反弹力 
				player1.items.rmv.throw_ready=false;
			}
			if(npos==player1.pos&&want_move){//没有上下楼就计算新位置
				THING.fpt.d=d;//记录足迹
				npos.x+=dx4[d];
				npos.y+=dy4[d];
			}
			MAP &NPOS=game_map[npos.x][npos.y][npos.z];
			thing &NTHING=NPOS.things;
			if(player1.pos!=npos){//必须是改变了位置 
				int nmaze=NPOS.maze;
				int door_d=(d==4?0:turn(d,TURN_BACK,4,17));//箱门方向 
				int pri_type=object_type(player1.items.wpn.primary);//主武器在物品栏中的编号 
				if(!nobody_here(npos)&&!(d==4?box_here(npos):closed_box_here(npos,door_d))){//这里有别的生物
					if(!spider_leg_here(npos)){//B型蜘蛛附肢：你来打我呀
						weapon_carried &wpn=player1.items.wpn;
						int pri=object_type(wpn.primary);
						if(pri==DAG){//匕首不击退，改为造成5点伤害，暴击率30% 
							living_things_reduce_blood(npos,5*(1+RAND_BOOL(30)),1,MP(PLAYER,-1));
							player1.color=5;
							player1.flash_word="匕";
							player1.flash=true;
							pos_change.insert(player1.pos);
							game_timer["玩家图标闪烁"]=game_time+500;
						}
						else throw_thing(npos,10/NPOS.mass(),0.3,(d<4?(d+3)%4*90:RAND(359,0)),MP(PLAYER,-1));//直接一拳（注意上下楼的情况） 
						player_add_stg(-3);//体力减少
					}
					if(d==4){//上下楼/进出巢穴口但被挡住
						game_flag["上下楼被挡"]=true; 
						pos_change.insert(npos);
					}
				}
				else if(!(door_here(npos,0)||door_here(npos,2)||mvb_here(npos,1))//没有开着的门或飞来的物品 
				&&(nmaze==SPACE||nmaze==EXIT//这里是空地、出口
				||(UPSTAIR<=nmaze&&nmaze<=DOWNSTAIR)//或者楼梯
				)){//较正常的移动 
					bool flag=false;
					movable &NMVB=NTHING.mvb; 
					position_3D select=player1.items.rmv.select;
					if(mvb_here(npos,0)){//有静止的东西挡着
					
						door_d=(d==4?0:turn(d,TURN_BACK,4,18));//判断能否进入，故与移动方向相反（d<4才有效） 
						
						if(NMVB.kind==BALL) flag=true;//（球挡不了） 
						else if(d==4&&NMVB.kind!=BOX) flag=true;//允许走到楼下的球/椅子/桌子上
						//上下楼/进出巢穴口 ↑ 
						else if(d<4&&select==npos&&NTHING.mvb.kind!=BOX) flag=true;//允许走到选中的椅子/桌子上
						else if(d<4&&select!=npos&&NMVB.kind==BOX&&(NMVB.door[door_d]||box_here(player1.pos))) flag=true;
						//面前的箱门是开启的/两个箱子之间移动 
						else if(d<4&&select!=npos&&push_thing(npos,d,1)) flag=true;//推动面前物品
					}
					else if(!mvb_here(npos,1)) flag=true;//运动的物体不行 
					//以下判断不行的情况 
					
					door_d=d;//判断能否出去，故与移动方向相同 
					
					if(closed_box_here(player1.pos,door_d)&&!(d<4&&box_here(npos)&&select!=npos)) flag=false;
					//玩家在关闭的箱子里没法动（同一楼层的相邻未选中箱子除外） 
					if(d==4&&!flag){//上下楼/进出巢穴口但被挡住
						game_flag["上下楼被挡"]=true; 
						pos_change.insert(npos);
					}
					spider_net &SNT=THING.snt;
					if(SNT.endurance>50){
						player_add_stg(-2);//体力值减少
						flag=false;//被蜘蛛网粘住 
						game_flag["物品损坏"]=true;
						pos_change.insert(player1.pos);
					}
					SNT.addedc(-25,player1.pos);
					if(flag){
						if(door_here(npos,2)) NTHING.kdr.state=1;//自动打开关上的门 
						player1.move=1;
						if(nmaze==EXIT){
							swap(NPOS.player_enemy,POS.player_enemy);
							game_end=game_success=true;
							return;
						}
					}
				}
				else if(door_here(npos,2)){//门关上了开门 
					NTHING.kdr.state=1;//直接开门 
					if(NPOS.update_light()) pos_affect_light.push(npos);//门开了光照更新 
					player1.move=1;
					MUSIC("开门",1);//开门声 
				}
				else if(window_here(npos)&&(pri_type==DAG||pri_type==SWO||pri_type==BLA)){
					NPOS.things.windows.damage(25,npos);
				}
			}
			if(d!=-1&&d!=4&&player1.d1!=d){
				if(!player1.move){
					player1.color=3;
					player1.flash=true;
					game_timer["玩家图标闪烁"]=game_time+200;
				}
				player1.d1=d;
				player1.d1_change=true;
			}
			if(player1.move){
				if(THING.crt.exist&&POS.update_light()&&POS.ist.player==lst_see_time) pos_affect_light.push(player1.pos);//帘子动了光照更新 
				if(NTHING.crt.exist&&NPOS.update_light()&&NPOS.ist.player==lst_see_time) pos_affect_light.push(npos);//帘子动了光照更新 
				POS.fcmv.init();//game_flag["飞"]=true;pos_change.insert(player1.pos);//玩家能主动移动就停止被动移动 
				game_map[player1.pos.x][player1.pos.y][player1.pos.z].player_enemy=NOBODY;
				game_map[npos.x][npos.y][npos.z].player_enemy=PLAYER;
				//标记地图 
				player_move_update(npos);
			}
			if(!stair_here(player1.pos)) player1.lst_ud=false;
			if(!THING.nst.exist) player1.lst_enter=false;
		}
			/*
			bool player_check_key(position_3D pos,item &items,vector<int> &v){//捡到钥匙 
			//返回是否捡到了物品 
				bool ret=false;
				thing &THING=game_map[pos.x][pos.y][pos.z].things;
				int id=THING.fir;
				if(id<0) return 0;
				object &obj=objects[id];
				if(obj.key==0) return 0;
				int nkey=obj.key;
				//int &nkey=THING.key;
				int &dk=items.keys.door_keys[nkey-KEY1];
				if(nkey){
					if(!dk){
						v.insert(v.end(),nkey-KEY1+K1);//捡到原来没有的 
						items.il_change=true;
					} 
					dk++;items.num_change=true;
					//nkey=0; 
					del_object1(pos);
					ret=true;
				}
				return ret;
			}
			bool player_check_food(thing &THING,item &items,vector<int> &v){//捡到食物 
			//返回是否捡到了物品 
				bool ret=false;
				food_pile &nfood=THING.foods;
				if(nfood.exist()){//这里至少有一个食物 
					int nkind=nfood.kind(),neffect=nfood.effect();//捡到什么食物 
					int &fc=items.foods.food_cnt[nkind-ADDS][neffect-1];//玩家物品栏 
					if(!fc){
						v.insert(v.begin(),AS1+(nkind-1)*EFFECT_OF_FOOD+(neffect-1));//捡到原来没有的
						items.il_change=true;
						MUSIC("Collect.wav",1);//提示音 
					} 
					fc++;items.num_change=true;
					nfood.food_cnt[nkind-ADDS][neffect-1]--;//修改地图上的数据 
					ret=true;
				}
				return ret;
			}
			bool player_check_wpn_energy_edc(thing &THING,item &items){//获得武器耐久度回复 
			//返回是否捡到了物品 
				bool ret=false;
				weapon_energy_edc &wee=THING.wee;
				int &ly=items.wpn.lsg.energy,&hec=items.wpn.hsr.endurance,&num=wee.num,&kind=wee.kind;
				bool &dc=items.wpn.data_change,&ex=wee.exist;
				if(ex){
					switch(kind){
						case 0:ly+=num;num=ex=0;dc=1;
							MUSIC("Coin.wav",1);//提示音 
							break;
						case 1:hec+=num;num=ex=0;dc=1;
							MUSIC("Coin.wav",1);//提示音 
							break;
					}
					ret=true;
				}
				return ret;
			}
			bool player_check_wpn(thing &THING,item &items){//捡到武器
			//返回是否捡到了武器
				bool ret=false;
				dart &DRT=THING.drt;
				weapon_carried &wpn=items.wpn;
				int &dnum=wpn.drt.num;
				if(DRT.exist0()){//地上的回旋镖 
					dnum+=DRT.num[0];
					DRT.num[0]=0;
					wpn.data_change=true;
					ret=true;
				}
				return ret;
			}
			bool player_check_spe(thing &THING,item &items,vector<int> &v){//捡到道具
			//返回是否捡到了物品 
				bool ret=false;
				special_effect &spe=player1.spe; 
				perspective &ppt=THING.ppt;
				bool &nppt=ppt.exist;
				if(nppt){//透视 
					int& kind=ppt.kind,time=ppt.time;
					x_ray &xry=spe.xry;
					xry.num+=kind;
					if(xry.time<=game_time) xry.time=game_time+time;
					else xry.time+=time;
					xry.change=true;
					game_flag["玩家视野参数改变"]=true;
					nppt=kind=time=0; 
					ret=true;
				}
				if(THING.smb.exist){//烟雾弹 
					THING.smb.exist=false;
					int &num=items.pp.smb;
					if(num==0){
						v.push_back(SM);
						items.il_change=true;
					}
					num++;
					items.num_change=true;
					ret=true;
				}
				return ret;
			}
		void player_check_thing(){//玩家捡拾物品
			return;
			thing &THING=game_map[player1.pos.x][player1.pos.y][player1.pos.z].things;
			if(THING.empty()) return;//这里没东西直接退出 
			item &items=player1.items;
			vector<int> &v=items.item_lab;
			//每次只捡一个东西 
			player_check_key(player1.pos,items,v);
			player_check_food(THING,items,v);
			player_check_wpn_energy_edc(THING,items);
			player_check_wpn(THING,items);
			player_check_spe(THING,items,v);
			//if(player_check_key(THING,items,v)) return;
			//if(player_check_food(THING,items,v)) return;
			//if(player_check_wpn_energy_edc(THING,items)) return;
			//if(player_check_wpn(THING,items)) return;
			//if(player_check_spe(THING,items,v)) return;
		}*/
		void player_choose_item(){
			logMessage("player_choose_item");
			position_2D scr_mouse=pos_mouse();//鼠标的屏幕位置 
			bool press_once=game_timer["按下鼠标"]<=game_time&&!game_flag["鼠标单击"];//单击 
			int mx=scr_mouse.x,my=scr_mouse.y;//鼠标在屏幕上的x、y坐标
			item &items=player1.items;
			int x=item_area.upper_left.x,y=item_area.upper_left.y;//物品栏顶部x、y坐标 
			if(KEY_DOWN(VK_LBUTTON)){//鼠标左键
				game_timer["按下鼠标"]=game_time+100;//限制侦测频率 
				game_flag["鼠标单击"]=true;
				if(scr_mouse.x<=20){//点击信息栏 
					game_pause=!game_pause;
					game_flag["游戏暂停/继续"]=true; 
					return;
				}
				else if(pos_in_game_map(scr_mouse)){//点击游戏地图区域 
					player1.action_kind=RUN;player1.ak_change=true;
					return;
				}
				else if(item_area.contain(scr_mouse)){//点击物品栏 
					if(press_once){//防止多次点击 
						if(my>=y+1){//选择使用物品 
							int x2=mx-x-3;//x坐标差值
							int select=x2/6;//选中的物品编号
							if(select>=0&&select<MAX_SIZE_OF_ITEM_LAB){//在物品栏大小范围内
								if(player1.items.select_number==select) player_use_item();
								items.select_number=select;
								items.sn_change=true;
							}
						}
					}
				}
				else if(weapon_area.contain(scr_mouse)){//点击武器栏 
					if(press_once){//防止多次点击 
						player1.action_kind=CHANGE_WPN;
						player1.ak_change=true;
					}
				}
			}
			else game_flag["鼠标单击"]=false;
			game_flag["按空格键"]=false;
			if(_kbhit()){
				int c=_getch();
				int &sn=items.select_number;
				vector<int> &v=items.item_lab,&num=items.item_num;
				switch(c){
					case PRESS_KEY_A://向左交换 
						if(sn>=1&&sn<v.size()){
							if(sn==items.wpn.primary) items.wpn.primary--;
							if(sn==items.wpn.secondary) items.wpn.secondary--;
							swap(v[sn-1],v[sn]);
							swap(num[sn-1],num[sn]);
							items.il_change=items.num_change=1;
							sn--;
							items.sn_change=1;
						}
						break;
					case PRESS_KEY_D://向右交换 
						if(sn>=0&&sn<v.size()-1){
							if(sn==items.wpn.primary) items.wpn.primary++;
							if(sn==items.wpn.secondary) items.wpn.secondary++;
							swap(v[sn],v[sn+1]);
							swap(num[sn],num[sn+1]);
							items.il_change=items.num_change=1;
							sn++;
							items.sn_change=1;
						}
						break;
					case PRESS_KEY_E:
						player_use_item();
						return;
				}
			}
		}
			/*
			void player_weapon_mode(){//更改武器模式 
				item &items=player1.items;
				weapon_carried &wpn=items.wpn;
				laser_gun &lsg=wpn.lsg;
				switch(wpn.select_wpn){
					case LSG:
						lsg.kind=(lsg.kind+1)%lsg.kd_cnt;
						wpn.mode_change=true;
						break;
				}
			}*/
		void player_update_weapon(){//更新武器 
			logMessage("player_update_weapon");
			item &items=player1.items;
			weapon_carried &wpn=items.wpn;
			position_2D scr_mouse=pos_mouse();//鼠标的屏幕位置 
			bool press_once=game_timer["按下鼠标"]<=game_time&&!game_flag["鼠标单击"];//单击 
			int mx=scr_mouse.x,my=scr_mouse.y;//鼠标在屏幕上的x、y坐标
			int x=weapon_area.upper_left.x,y=weapon_area.upper_left.y;//武器栏顶部x、y坐标 
			if(KEY_DOWN(VK_LBUTTON)){//鼠标左键
				game_timer["按下鼠标"]=game_time+100;//限制侦测频率 
				game_flag["鼠标单击"]=true;
				if(scr_mouse.x<=20){//点击信息栏 
					game_pause=!game_pause;
					game_flag["游戏暂停/继续"]=true; 
					return;
				}
				else if(pos_in_game_map(scr_mouse)){//点击游戏地图区域 
					player1.action_kind=RUN;player1.ak_change=true;
					return;
				}
				else if(weapon_area.contain(scr_mouse)){//点击武器栏
					if(press_once){//防止多次点击 
						swap(wpn.primary,wpn.secondary);//交换主副武器 
						wpn.data_change=wpn.sw_change=1; 
						/*
						if(my==y+1){//切换武器种类 
							if(mx>=x+16){
								wpn.select_wpn=(wpn.select_wpn)%wpn.wcnt+1;//从1开始编号
								wpn.sw_change=true;
							}
							else{
								wpn.select_wpn=(wpn.select_wpn-2+wpn.wcnt)%wpn.wcnt+1;//从1开始编号 
								wpn.sw_change=true;
							}
						}
						else if(my==y+2)//切换武器模式 
							player_weapon_mode();
						*/
					}
				}
				else if(item_area.contain(scr_mouse)){//点击物品栏
					if(press_once){//点击物品区 
						player1.action_kind=CHOOSE_ITEM;
						player1.ak_change=true;
					}
				}
			}
			else game_flag["鼠标单击"]=false;
			game_flag["按空格键"]=false;
		}
		void player_lfin_update(){
			logMessage("player_lfin_update"); 
			MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
			if(POS.fcmv.lock&&POS.fcmv.speed()>5&&game_timer["玩家被砸中"]<=game_time){//被砸中无法移动和攻击
				player_reduce_blood(1,POS.fcmv.from);
				game_timer["玩家被砸中"]=game_time+500;
			}
			special_effect &spe=player1.spe;
			methysis &mts=spe.mts;
			weakness &wks=spe.wks;
			if(mts.exist()&&mts.t+mts.T<=game_time){//中毒扣血 
				mts.t=game_time;
				player_reduce_blood(mts.x,mts.from);
			}
			if(wks.exist()&&wks.t+wks.T<=game_time){//虚弱减体力
				wks.t=game_time;
				player_add_stg(-wks.x); 
			}
			if(game_timer["玩家体力恢复"]<=game_time){
				//game_timer["玩家开始奔跑"]=game_time;
				game_timer["玩家奔跑步数"]=0;
			}//清零
			if(player1.move){
				double x=sqrt(game_timer["玩家奔跑步数"]);
				//->体力变化量 
				player_add_stg(-x);//player_add_stg(-1);//体力值减少 
				//连续奔跑体力下降会越来越快 
				game_timer["玩家体力恢复"]=game_time+player1.vts.stg.recovery_time;
				//移动时不回复体力 
				game_timer["玩家奔跑步数"]++;
			}
			else if(game_timer["玩家体力恢复"]<=game_time&&player1.vts.stg.physical_strength<100){//体力恢复时间已到
				player_add_stg(1);//体力值增加 
				game_timer["玩家体力恢复"]+=player1.vts.stg.recovery_time;
			}
			player1.vlc.speed=max(1.0,pow(player1.vts.stg.physical_strength,2)/double(200));
			//速度最低值为1，防止低体力时延时过长 
			player1.vlc.vt();
		}
		void player_sight_update(){//重新计算视野 
			logMessage("player_sight_update"); 
			if(player1.spe.xry.num!=1&&player1.spe.xry.time<=game_time){
				player1.spe.xry.num=1;player1.spe.xry.change=true;
				game_flag["玩家视野参数改变"]=true;
			}
			special_effect &spe=player1.spe;
			dim_sight &dst=spe.dst;
			vertigo &vtg=spe.vtg;
			if(vtg.exist()&&vtg.t+vtg.T<=game_time){
				vtg.t=game_time;
				position_2D &u=screen_center;
				u.x+=RAND(2,-2);
				u.y+=RAND(2,-2);
				//摆动 
				limit_int(u.x,player1.pos.x-10,player1.pos.x+10);
				limit_int(u.y,player1.pos.y-10,player1.pos.y+10);
				//防止跑太远 
				game_flag["玩家视野参数改变"]=true;
			}
			if(!vtg.exist()&&screen_center!=position_3Dto2D(player1.pos)&&game_timer["移动屏幕中心"]<=game_time){
			//&&game_timer["玩家上次移动"]+1000<=game_time
			//移动屏幕中心screen_pos
				position_2D &u=screen_center;
				if(u.x>player1.pos.x) u.x--;
				else if(u.x<player1.pos.x) u.x++;
				if(u.y>player1.pos.y) u.y--;
				else if(u.y<player1.pos.y) u.y++;
				game_timer["移动屏幕中心"]=game_time+200;
				game_flag["玩家视野参数改变"]=true;
			}
			if(player1.d2_change||player1.move||player1.ud_change||player1.items.flt.change
			||game_flag["玩家视野参数改变"]||game_flag["玩家开/关窗户"]||game_flag["虫子挖地道"]||game_flag["鬼装墙"]||game_flag["蛛网变化"]
			||game_flag["帘子摇动"]||game_flag["物品消失"]||game_flag["关门"]||game_flag["开门"]||game_flag["雾气扩散"]||game_flag["遮挡生物移动"]
			||dst.dim&&game_time-dst.time>dst.last){//模糊视野可以消除了 
				game_flag["玩家视野参数改变"]=game_flag["玩家开/关窗户"]=game_flag["虫子挖地道"]=game_flag["鬼装墙"]=game_flag["蛛网变化"]=false; 
				game_flag["帘子摇动"]=game_flag["物品消失"]=game_flag["关门"]=game_flag["开门"]=game_flag["雾气扩散"]=game_flag["遮挡生物移动"]=false; 
				dst.dim=false;
				game_flag["玩家视野重新计算"]=true;
				while(!pos_in_sight.empty()) pos_in_sight.pop();//清除没输出完的 
				screen_z.clear();//重新标记屏幕和位置的映射 
				player_erase_flashlight();//把手电筒照到的删了 
				player_calculate_vision2();
				//player_calculate_vision1(player1.d2);
				lst_see_time=game_time;//计算视野 
			}
		}
		void player_others(){//其他杂碎
			logMessage("player_others");  
			if(player1.move) player_update_spear(),player_update_sword(),player_update_blade();//移动就更新矛、剑、刀 
			//player_erase_spear();//矛的耐久度用光或不用矛自动删除 
		}
	void deal_player(){
		logMessage("deal_player()",2);
		MAP &POS=game_map[player1.pos.x][player1.pos.y][player1.pos.z];
		switch(player1.action_kind){
			case RUN:case WALK:
				if(!(POS.fcmv.lock&&POS.fcmv.speed()>2)){
					POS.fcmv.init();
					player_detect_move();
				}
				//player_check_thing();//if(player1.move) 
				break;
			case CHOOSE_ITEM:
				player_choose_item();
				break;
			case CHANGE_WPN:
				player_update_weapon();
				break;
		}
		player_lfin_update();
		player_sight_update();
		player_others();
	}
		void clean_dead(){//清除尸体 
			logMessage("clean_dead");
			while(!pos_dead.empty()){
				position_3D u=pos_dead.front();
				MAP &POS=game_map[u.x][u.y][u.z];
				if(POS.emy.body_disapp>game_time) return;//最早的尸体还没到清理时间，接下来的不用看了
				if(POS.ist.player==lst_see_time){
					pos_change.insert(u);
					game_flag["清除尸体"]=true;
				}
				pos_dead.pop(); 
			}
		}
		void shoot_laser_beam(){//清除激光束 
			logMessage("shoot_laser_beam");
			if(laser_beams.size()&&game_timer["清除激光束"]<=game_time){
				player1.use_weapon=true;
				while(!laser_beams.empty()){
					position_3D u=laser_beams.front();laser_beams.pop();
					MAP &POS=game_map[u.x][u.y][u.z];
					POS.things.lsr.exist=false;
					
					POS.brightness-=40;//消除发光效果 
					
					if(POS.ist.player==lst_see_time) pos_change.insert(u);
					hurt_enemy(POS);//取消伤害效果 
					if(!POS.things.nst.exist||POS.things.nst.id<0) continue;
					bug_nest &bgn=bug_nests[POS.things.nst.id];
					if(bgn.lfin.change!=0) bgn.lfin.change=0;//巢穴被击中的闪烁停止 
				}
				/*消除发光效果（大地图容易卡爆，不用这个功能了） 
				while(!laser_beam_light.empty()){
					pair<position_3D,int> p=laser_beam_light.front();laser_beam_light.pop();
					position_3D u=p.first;int x=p.second;
					MAP &POS=game_map[u.x][u.y][u.z];
					POS.brightness-=x;
					if(POS.ist.player==lst_see_time) pos_change.insert(u);
				}*/
			}
		}
		void pierce_spear(){//刺出矛
			logMessage("pierce_spear");
			int num=spears.size();
			if(num==0) return;
			while(num>0){
				num--;
				position_3D u=spears.front();spears.pop();
				spears.push(u);//再放回去 
				MAP &POS=game_map[u.x][u.y][u.z];
				if(POS.player_enemy==BUG&&POS.emy.id!=-1) Qbug_hurt.push(POS.emy.id);//伤害
				else if(POS.player_enemy==SPIDER&&POS.emy.id!=-1) Qspider_hurt.push(POS.emy.id);//伤害
			}
		}
			void dart_fall(flying_dart fdt){//回旋镖落下 
				position_3D pos=fdt.pos;
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				thing &THING=POS.things;
				dart &DRT=THING.drt;
				DRT.num[1]--;
				add_object1(pos,fdt.id);//DRT.num[0]++;
				if(POS.ist.player==lst_see_time){//更新屏幕 
					game_flag["回旋镖变化"]=true;
					pos_change.insert(pos); 
				}
			}
		void throw_dart(){//回旋镖飞行 
			logMessage("throw_dart");
			int num=darts.size();
			while(num>0){
				num--;
				flying_dart fdt=darts.front();darts.pop();
				MAP &POS=game_map[fdt.pos.x][fdt.pos.y][fdt.pos.z];
				dart &DRT=POS.things.drt;
				int d=0;//移动方向 
				velocity *vlc;//现在移动的方向对应速度的指针（vx/vy） 
				double vxy=sqrt(fdt.vx.speed*fdt.vx.speed+fdt.vy.speed*fdt.vy.speed);//合成速度的大小 
				if(fdt.tx<=game_time){//x变 
					d=(fdt.vx.speed>0?1:3);//vx有正负 
					fdt.tx=game_time+fdt.vx.wait_time;
					vlc=&fdt.vx;
				}
				else if(fdt.ty<=game_time){//y变 
					d=(fdt.vy.speed>0?2:0);//vy有正负 
					fdt.ty=game_time+fdt.vy.wait_time;
					vlc=&fdt.vy;
				}
				else{//没到移动时间 
					darts.push(fdt);
					break;
				}
				position_3D npos=dtp3(fdt.pos,d,4);//下一个地方 
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				dart &NDRT=NTHING.drt;
				hurt_enemy(POS);
				hurt_enemy(NPOS);
				if(mirror_here(npos)||window_here(npos)){//撞到镜子/窗户 
					if(mirror_here(npos)) NTHING.mirrors.damage(fabs(vlc->speed)*3);
					else NTHING.windows.damage(fabs(vlc->speed),npos);
					vlc->speed*=0.8;vlc->vt();//减速 
					if(NPOS.ist.player==lst_see_time){
						game_flag["飞"]=true;
						pos_change.insert(npos);
					}
				}
				int eid=NPOS.emy.id;
				if(enemy_here(npos)&&!nobody_here2(npos)//撞到敌人，有敌对生物的本体
				&&(eid<0||eid>=ghosts.size()||!ghost_here(npos)?1:ghosts[eid].spat.defense!=EVADE)//闪避鬼无效 
				&&!box_here(npos)//不能有箱子 
				){
					/*
					position_3D b;
					b.x=fdt.vx.speed;b.y=fdt.vy.speed;b.z=0;//计算角度的辅助坐标 
					throw_thing(npos,vxy*0.5,0,calc_angle(pos000,b),MP(PLAYER,-1));*/
					throw_thing(npos,fdt.vx.speed*0.2,0,0,MP(PLAYER,-1));
					throw_thing(npos,fdt.vy.speed*0.2,0,90,MP(PLAYER,-1));
					//粗略模拟一下 
					fdt.vx.speed*=0.8;fdt.vx.vt();//减速 
					fdt.vy.speed*=0.8;fdt.vy.vt();//减速 
				}
				if(pos_in_area2(npos.x,npos.y,1,1,length,width,2)
				&&!(door_here(npos,0)||door_here(npos,2)||wall_here(npos)||spider_leg_here(npos)
				||NTHING.mvb.exist||NTHING.hdr.exist||NTHING.crt.exist)
				){
					if(game_map[fdt.pos.x][fdt.pos.y][fdt.pos.z].ist.player==lst_see_time){//更新屏幕 
						game_flag["回旋镖变化"]=true;
						pos_change.insert(fdt.pos); 
					}
					if(game_map[npos.x][npos.y][npos.z].ist.player==lst_see_time){//更新屏幕 
						game_flag["回旋镖变化"]=true;
						pos_change.insert(npos); 
					}
					DRT.num[1]--;
					fdt.pos=npos;
					NDRT.num[1]++;
					darts.push(fdt);//重新放回队列 
				}
				else{
					if(NTHING.crt.exist) damage_curtain(npos,50); 
					dart_fall(fdt);//碰到墙、箱子、关上的门、B型蜘蛛附肢、隐藏门、帘子就停止飞行
				}
			}
		}
		void shoot_spider_silk(){//蛛丝飞行 
			logMessage("shoot_spider_silk");
			int num=ssks.size();
			while(num>0){
				num--;
				flying_ssk fsk=ssks.front();ssks.pop();
				MAP &POS=game_map[fsk.pos.x][fsk.pos.y][fsk.pos.z];
				thing &THING=POS.things;
				spider_silk &ssk=THING.ssk;
				int d=0;//移动方向 
				velocity *vlc;//现在移动的方向对应速度的指针（vx/vy） 
				if(fsk.tx<=game_time){//x变 
					d=(fsk.vx.speed>0?1:3);
					fsk.tx=game_time+fsk.vx.wait_time;
					vlc=&fsk.vx;
				}
				else if(fsk.ty<=game_time){//y变 
					d=(fsk.vy.speed>0?2:0);
					fsk.ty=game_time+fsk.vy.wait_time;
					vlc=&fsk.vy;
				}
				else{//没到移动时间 
					ssks.push(fsk);
					break;
				}
				position_3D npos=dtp3(fsk.pos,d,4);//下一个地方 
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				spider_silk &nssk=NTHING.ssk;
				if(pos_in_area2(npos.x,npos.y,1,1,length,width,2)
				&&!(door_here(npos,0)||door_here(npos,2)||wall_here(npos)||NTHING.mvb.exist&&NTHING.mvb.kind==BOX)//无法进入 
				){
					if(game_map[fsk.pos.x][fsk.pos.y][fsk.pos.z].ist.player==lst_see_time){//更新屏幕 
						game_flag["蛛丝变化"]=true;
						pos_change.insert(fsk.pos); 
					}
					if(game_map[npos.x][npos.y][npos.z].ist.player==lst_see_time){//更新屏幕 
						game_flag["蛛丝变化"]=true;
						pos_change.insert(npos); 
					}
					ssk.num--;
					fsk.pos=npos;
					if(NTHING.mvb.exist&&(NTHING.mvb.kind==CHAIR||NTHING.mvb.kind==BOX)
					||NTHING.hdr.exist||NTHING.crt.exist||!nobody_here2(npos)) NTHING.snt.addedc(75,npos);//进入且黏住了 
					else{//飞过 
						nssk.num++;
						ssks.push(fsk);//重新放回队列 
					} 
				}
				else{//被挡住，停在前面（fsk.pos） 
					ssk.num--;
					THING.snt.addedc(75,fsk.pos);//和上面保持一致 
				}
			}
		}
		void fly_removable(){//扔可移动物品（包括生物） 
			logMessage("fly_removable");
			int num=mvbs.size()*2;//多扫几遍使x、y都移动 
			queue<flying_mvb> mvbs_new; 
			while(!mvbs.empty()&&num>0){
				num--;
				flying_mvb fmb=mvbs.front();mvbs.pop();
				MAP &POS=game_map[fmb.pos.x][fmb.pos.y][fmb.pos.z];
				thing &THING=POS.things;
				movable &MVB=THING.mvb;
				force_move &FCMV=POS.fcmv;
				if(!FCMV.lock) continue;//不飞了
				double speed=FCMV.speed();//总速度（正） 
				if(speed<1//太慢了 
				||nobody_here2(fmb.pos)&&!mvb_here(fmb.pos)){//飞的东西没了 
					FCMV.init();//速度清零 
					//game_flag["飞"]=true;pos_change.insert(fmb.pos);
					continue;
				} 
				int d=0;//移动方向 
				velocity *vlc;//现在移动的方向对应速度的指针（vx/vy） 
				velocity &vx=FCMV.vx,&vy=FCMV.vy;
				if(fabs(vx.speed)>0.01&&FCMV.tx<=game_time){//x变 
					d=(vx.speed>0?1:3);
					FCMV.tx=game_time+vx.wait_time;
					vlc=&vx;
				}
				else if(fabs(vy.speed)>0.01&&FCMV.ty<=game_time){//y变 
					d=(vy.speed>0?2:0);
					FCMV.ty=game_time+vy.wait_time;
					vlc=&vy;
				}
				else{//没到移动时间 
					mvbs.push(fmb);
					continue;
				}
				int lst_move_time=fmb.lst_move_time;//备份一下 
				fmb.lst_move_time=game_time;
				THING.snt.addedc(-THING.snt.endurance/2,fmb.pos);//损坏蜘蛛网（*0.5） 
				int angle=calc_angle2(vx.speed,vy.speed);//物品移动方向 
				position_3D npos=dtp3(fmb.pos,d,4);
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &NTHING=NPOS.things;
				movable &NMVB=NTHING.mvb;
				force_move &NFCMV=NPOS.fcmv;
				mirror &NMIRRORS=NTHING.mirrors;
				hurt_enemy(POS);
				hurt_enemy(NPOS);
				if(window_here(npos)){//撞到镜子/窗户 
					NTHING.windows.damage(speed,npos);
					vx.speed*=0.8;vx.vt();//减速 
					vy.speed*=0.8;vy.vt();//减速 
					if(NPOS.ist.player==lst_see_time){
						game_flag["飞"]=true;
						pos_change.insert(npos);
					}
				}
				if(!(wall_here(npos)||door_here(npos,0)||door_here(npos,2)||exit_here(npos))
				&&nobody_here(npos)&&!NMVB.exist
				&&(spider_here(fmb.pos)&&POS.emy.id>=0&&POS.emy.id<=spiders.size()?spider_through(npos,d,spiders[POS.emy.id].kind):1)){//还能继续飞（蜘蛛特判） 
					if(POS.ist.player==lst_see_time){
						game_flag["飞"]=true;
						pos_change.insert(fmb.pos);
					}
					if(NPOS.ist.player==lst_see_time){
						game_flag["飞"]=true;
						pos_change.insert(npos);
					}
					fmb.pos=npos;//更新位置 
					mvbs.push(fmb);//重新放回队列
					swap(NMVB,MVB);
					swap(NPOS.player_enemy,POS.player_enemy);
					swap(NPOS.emy.id,POS.emy.id);
					int id=NPOS.emy.id;
					//此时已移动好生物 
					if(NPOS.player_enemy==BUG&&id>=0&&id<bugs.size()){//虫 
						bug &bg=bugs[id];
						bg.pos=npos;
					}
					else if(NPOS.player_enemy==SPIDER&&id>=0&&id<spiders.size()){//蜘蛛 
						spider &sr=spiders[id];
						spider_update_leg(sr.pos,-1,id);
						sr.pos=npos;
						spider_update_leg(npos,1,id);
					}
					else if(NPOS.player_enemy==GHOST&&id>=0&&id<ghosts.size()){//鬼 
						ghost &gh=ghosts[id];
						gh.pos=npos;
					}
					else if(NPOS.player_enemy==PLAYER){//推开玩家 
						NTHING.fpt.d=d;
						player1.items.rmv.select=pos000;
						player1.pos=npos;
						player_erase_spear();
					} 
					swap(NFCMV,FCMV);//game_flag["飞"]=true;pos_change.insert(fmb.pos);pos_change.insert(npos);//把这里的信息迁移到下一个位置
					double deltav=(game_time-lst_move_time)*0.005;//速度受摩擦阻力改变量 
					int speed2=max(0.0,speed-deltav);//防止降到负数  
					NFCMV.init4(speed2,angle);//减速
					//vx、vy同步减少 
					vibrate_spider_net(npos,speed*1000);//震动蜘蛛网 
				}
				else{
					if(player_here(fmb.pos))//玩家速度<=5不扣血 
						living_things_reduce_blood(fmb.pos,max(0.0,speed-5)*0.2,1,FCMV.from);
					else if(!(ghost_here(fmb.pos)&&POS.emy.id>=0&&POS.emy.id<ghosts.size()&&ghosts[POS.emy.id].rampage))
					//鬼在横冲直撞时撞玩家不扣血 
						living_things_reduce_blood(fmb.pos,speed*0.2,1,FCMV.from);
					int door_d=turn(d,TURN_BACK,4,19);
					if(mvb_here(npos)&&NMVB.kind!=BOX||!nobody_here2(npos)&&!closed_box_here(npos,door_d)){//有东西/生物且不是箱子或B型蜘蛛附肢 
						//game_flag["飞"]=true;pos_change.insert(fmb.pos);pos_change.insert(npos);
						//你这动量守恒有问题啊 
						//好像没问题了
						//2024.8.1 
						force_move &NFCMV=NPOS.fcmv;
						double v1x=vx.speed,v1y=vy.speed;
						double v2x=NFCMV.vx.speed,v2y=NFCMV.vy.speed;
						double v12x=v1x-v2x,v12y=v1y-v2y;
						double m1=POS.mass(),m2=NPOS.mass();
						double deltav1x=-2.0*m2/(m1+m2)*v12x,deltav2x=2.0*m1/(m1+m2)*v12x;
						double deltav1y=-2.0*m2/(m1+m2)*v12y,deltav2y=2.0*m1/(m1+m2)*v12y;
						double newv1x=v1x+deltav1x,newv1y=v1y+deltav1y;
						double newv2x=v2x+deltav2x,newv2y=v2y+deltav2y;
						if(fabs(newv1x)<0.1) newv1x=0;
						if(fabs(newv1y)<0.1) newv1y=0;
						if(fabs(newv2x)<0.1) newv2x=0;
						if(fabs(newv2y)<0.1) newv2y=0;
						//防止精度问题 
						FCMV.init3(newv1x,newv1y);//变速
						NFCMV.init3(newv2x,newv2y);//变速
						
						if(FCMV.speed()>=1){//改变自己速度
							mvbs.push(fmb);
						}
						else FCMV.init();//停止运动 
						
						if(NFCMV.speed()>=1){//动能传递 
							if(!NFCMV.lock){//不在队列里 
								flying_mvb nfmb;nfmb.init(npos);
								mvbs_new.push(nfmb);
								NFCMV.tx=NFCMV.ty=game_time;
								NFCMV.tx+=NFCMV.vx.wait_time;//防止瞬间移动2格 
								NFCMV.ty+=NFCMV.vy.wait_time;//防止瞬间移动2格
								NFCMV.lock=1;
								//可参照throw_thing() 
							}
							NFCMV.from=FCMV.from; 
						}
						else NFCMV.init();//停止运动 
						
						/*写的一坨屎 
						double v2=NPOS.fcmv.speed(),v12=speed-v2;
						double m1=POS.mass(),m2=NPOS.mass();
						double deltav1=-2.0*m2/(m1+m2)*v12,deltav2=2.0*m1/(m1+m2)*v12;
						if(fabs(v2+deltav2)>=1) throw_thing(npos,deltav2,0.5,angle,FCMV.from);//动能传递 
						//else NPOS.fcmv.init();//被撞到的停止运动 
						double speed2=speed+deltav1;//FCMV的新速度（可正可负） 
						if(speed2<0){
							speed2=-speed2;
							angle=(angle+180)%360;//方向变反 
						}
						if(speed2>=1){
							FCMV.init4(speed2,angle);//变速
							mvbs.push(fmb);//重新放回队列 
						}
						else FCMV.init();//停止运动*/
					}
					else if(MVB.exist&&MVB.kind!=DESK&&speed>3&&RAND_BOOL(100)){//动能没有传递掉就改变方向（只有mvb改变方向） 
						double k=(MVB.kind==CHAIR?0.7:0.9);//衰减系数 
						vlc->speed=-(vlc->speed);vlc->vt();//当前移动速度方向取反
						FCMV.init3(vx.speed*k,vy.speed*k);
						mvbs.push(fmb);//重新放回队列 
						if(spider_leg_here(npos)&&NTHING.slg.id!=-1) spider_reduce_blood(NTHING.slg.id,0.5,FCMV.from);//撞到B型蜘蛛附肢扣血 
					}
					else FCMV.init();//停止运动
				}
			}
			while(!mvbs_new.empty()){//把新的加进来 
				flying_mvb u=mvbs_new.front();mvbs_new.pop();
				mvbs.push(u);
			}
		}
		void update_lights(){
			logMessage("update_lights");
			if(game_time%500==0) return;//最快每秒更新2次
			int num=pos_affect_light.size(),cnt=0;
			while(num>0&&cnt<=2){//要更新光照的位置（限制更新频率） 
				num--;
				position_3D u=pos_affect_light.front();pos_affect_light.pop();
				MAP &POS=game_map[u.x][u.y][u.z];
				vector<PII> v;vector<position_3D> ret;
				for(int i=0;i<4;i++) v.push_back(MP(0,359));
				vision_init(1,v,ret,pos000);
				calculate_vision2(u,2,ret,INF,0);//以改变的点为光源计算“照射”范围，找出↓ 
				for(int i=0;i<ret.size();i++){
					position_3D v=ret[i];
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &NTHING=NPOS.things;
					light &NLGT=NTHING.lgt;
					if(NLGT.exist&&!NLGT.update){//防止重复加入
						NLGT.update=true;//如果不在视野范围内留到看到这里时更新，先做个标记 
						if(pos_to_brightness(v,u,NLGT.p)>=5) lights_update.push(v);
						//更新能照到视野范围内物品的灯
					}
				}
				cnt++;
			}
			cnt=0;
			num=lights_update.size();
			while(num>0&&cnt<=1){
				num--;
				position_3D u=lights_update.front();lights_update.pop();
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				light &LGT=THING.lgt;
				update_light_brightness(u);//重置+计算 
				cnt++;
			}
		}
			void spread(int kind,position_3D u,position_3D v,double vel,int t){//u->v扩散（一般从浓度高到浓度低）
				MAP &UPOS=game_map[u.x][u.y][u.z];
				MAP &VPOS=game_map[v.x][v.y][v.z]; 
			    fog &UF=UPOS.things.fogs,&VF=VPOS.things.fogs;
				double (&a)[3]=UF.absorbance,(&b)[3]=VF.absorbance,tmp;
				//RGB_color &c=UF.col,&d=VF.col;
				switch(kind){
					case 0://雾气扩散 
						for(int i=0;i<3;i++){//RGB
							tmp=abs(b[i]-a[i])*vel*t/1000.0;
							if(a[i]>b[i]) a[i]-=tmp,b[i]+=tmp;
							//else a[i]+=tmp,b[i]-=tmp;
							//只计算u->v浓度高->低，节省算力 
						}//R/G/B颜色单独扩散 
						if(tmp>5&&UPOS.ist.player==lst_see_time&&VPOS.ist.player==lst_see_time
						&&game_flag["上次计算雾气"]+500<=game_time){
							game_flag["雾气扩散"]=true;//更新视野 
							game_flag["上次计算雾气"]=game_time;
						}
						break;
				}
			}
			void deal_fog(position_3D u,position_3D v){//从u飘到v（fogu>fogv) 
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				fog &NFOGS=game_map[v.x][v.y][v.z].things.fogs;
				if(!fog_through(v,u)) return;//雾气没法穿过这里 ||FOGS.absorbance<=NFOGS.absorbance
				spread(0,u,v,V_FOG_SPREAD,T_SPREAD_DELAY);
				if(!NFOGS.update){
					NFOGS.update=true;
					pos_fog.push(v);//扩散到新节点
				}
				game_timer["雾"]++;
			}
		void spread_fogs(){//雾气扩散
			logMessage("spread_fogs");
			if(game_timer["雾气扩散"]>game_time) return;//隔一段时间计算一次 
			game_timer["雾气扩散"]=game_time+T_SPREAD_DELAY;
			int num=pos_fog.size();
			if(num==0) return;
			while(num--){
				position_3D u=pos_fog.front();pos_fog.pop();
				fog &FOGS=game_map[u.x][u.y][u.z].things.fogs;
				if(FOGS.exist()) pos_fog.push(u);//还有一丁点雾就放到队尾 
				else FOGS.update=false;//不再更新这里 
				MAP &POS=game_map[u.x][u.y][u.z];
				for(int d=0;d<4;d++){
					position_3D v=dtp3(u,d,4);
					deal_fog(u,v);
				}
				if(upstair_here(u)) deal_fog(u,(position_3D){u.x,u.y,u.z+1});//上楼 
				else if(downstair_here(u)) deal_fog(u,(position_3D){u.x,u.y,u.z-1});//下楼 
				else if(bug_nest_here(u)) deal_fog(u,(position_3D){u.x,u.y,u.z+(u.z<=height?height:-height)});//飘进/出巢穴 
			}
		}
		void open_close_treasure(){
		}
		void on_off_candle(){
		}
		void move_barrel(){
		}
		void on_off_lamp(){
		}
		void delay_boom_TNT(){
		}
		void pour_water(){
		}
		void pour_magma(){
		}
	void deal_item(){
		logMessage("deal_item()",2);
		clean_dead(); 
		shoot_laser_beam();
		pierce_spear();
		throw_dart();
		shoot_spider_silk();
		fly_removable();
		update_lights();
		spread_fogs(); 
		open_close_treasure();
		on_off_candle();
		move_barrel();
		on_off_lamp();
		delay_boom_TNT();
		pour_water();
		pour_magma();
	}
		void player_flash_update(){
			logMessage("player_flash_update");
			if(player1.color!=0&&game_timer["玩家图标闪烁"]<=game_time){
				player1.color=0;
				player1.flash=true;
			}
			if(player1.flash) pos_change.insert(player1.pos);
		}
		void game_map_update(){//更新显示在屏幕上的游戏地图 
			logMessage("game_map_update");
			//formatted_output(1,vital_signs_area,1,11,MMPP(0,360,-100,360),int_to_str(pos_in_sight.size(),3));
			//formatted_output(1,vital_signs_area,1,12,MMPP(0,360,-100,360),int_to_str(pos_change.size(),3));
			if(game_flag["玩家视野重新计算"]
			||game_flag["屏幕更新中断"]&&game_time%100==0
			){
				game_flag["玩家视野重新计算"]=game_flag["屏幕更新中断"]=false;
				int num=pos_lst_sight.size(),cnt=0;//输出计数
				while(num>0){//先处理清空掉的 
					position_2D spos=pos_lst_sight.front();pos_lst_sight.pop();
					num--;
					if(!screen_z.count(spos)){
						if(pos_in_game_map(spos))
							formatted_output(1,whole_screen,spos.x,spos.y,MMPP(-100,360,-100,360),"  ");//清空屏幕上这个位置
						if(screen_pos.count(spos)) screen_pos.erase(spos);//屏幕上这个位置的显示内容编码用不上了，删掉 
						continue;
					}
					position_3D npos=position_scrto3D(spos,screen_z[spos]);
					//屏幕坐标转化为游戏地图坐标，z坐标换成现在屏幕上对应位置要显示的楼层
					string ncode=print_game_map_pos(npos,3);
					if(ncode!=screen_pos[spos])//现在要显示的内容编码和上次不同
						pos_lst_sight.push(spos);//改变的留下来 
					else pos_backup.insert(spos);//把屏幕上这个位置放到备份队列里
				}
				cnt=0; 
				while(!pos_lst_sight.empty()&&cnt<100){//再处理屏幕上改变的
					position_2D spos=pos_lst_sight.front();pos_lst_sight.pop();
					cnt++; 
					if(player1.spe.cfs.exist()&&RAND_BOOL(player1.spe.cfs.a)) continue;//玩家【迷惑】，只清空队列不输出 
					position_3D npos=position_scrto3D(spos,screen_z[spos]);
					//屏幕坐标转化为游戏地图坐标，z坐标换成现在屏幕上对应位置要显示的楼层
					screen_pos[spos]=print_game_map_pos(npos,1);//输出新的内容并将屏幕上这个位置的显示内容编码更新 
					pos_backup.insert(spos);//把屏幕上这个位置放到备份队列里
				}
				if(!pos_lst_sight.empty()) game_flag["屏幕更新中断"]=true;//判断是否输出干净 
				num=pos_in_sight.size(); 
				cnt=0; 
				while(num>0&&cnt<50){//接着处理现在新显示到屏幕的 
					position_3D npos=pos_in_sight.front();pos_in_sight.pop();
					num--;
					position_2D spos=position_3Dtoscr(npos);//npos在屏幕上的对应位置
					screen_pos[spos]=print_game_map_pos(npos,1);//输出并新增这个位置的屏幕信息
					cnt++; 
					pos_backup.insert(spos);
				}
				if(!pos_in_sight.empty()) game_flag["屏幕更新中断"]=true;//判断是否输出干净 
				set<position_2D>::iterator it;
				for(it=pos_backup.begin();it!=pos_backup.end();it++){//最后备份队列的内容全部copy到上次显示到屏幕的（给下次循环用） 
					position_2D spos=*it;
					pos_lst_sight.push(spos);
				}
				pos_backup.clear();
				if(!game_flag["屏幕更新中断"]) screen_z.clear();//不用拖到下次，清空 
				pos_change.clear();//重新计算视野就清空部分更新的队列 
			}
			else if(!pos_change.empty()//int cnt=0; &&cnt<=10部分更新（限流）
			){//玩家没移动，显示的游戏地图可能有别的变化（比如突然冒出一个鬼），特殊处理
				while(pos_change.size()>0){
					position_3D npos=*(pos_change.begin());pos_change.erase(npos);
					position_2D spos=position_3Dtoscr(npos);//npos在屏幕上的对应位置 
					//string ncode=print_game_map_pos(npos,3);
					//if(ncode!=screen_pos[spos])//现在要显示的内容编码和上次不同
					screen_pos[spos]=print_game_map_pos(npos,1);//输出并新增这个位置的屏幕信息
					pos_lst_sight.push(spos);//添加到上次显示到屏幕的（给下回合用）
					//cnt++;
				}
			}
			/*&&game_time%50==0
			||(player1.enemy_move||player1.flash||player1.use_weapon||player1.items.rmv.dl_change
			||game_flag["敌人被玩家攻击"]||game_flag["清除尸体"]||game_flag["鬼隐身"]||game_flag["吸血"]||game_flag["上下楼被挡"] 
			||game_flag["玩家矛改变位置"]||game_flag["玩家剑改变位置"]||game_flag["回旋镖变化"]||game_flag["物品损坏"]||game_flag["蛛丝变化"]
			||game_flag["推桌椅"]||game_flag["拉"]||game_flag["飞"]||game_flag["推noply"]
			||game_flag["光照更新"])*/
		}
			void lives_update(){//玩家生命体征更新 ",double_to_str(player1.vts.lfin.hurt,1),"repeat_str("★",x)repeat_str("☆",y)
				logMessage("lives_update");
				if(player1.vts.lfin.change||player1.d1_change||player1.items.sn_change){
					if(player1.vts.lfin.life<10) formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0),"生命垂危！");
					else{
						int x=player1.vts.lfin.life/10.0,y=(player1.vts.lfin.hurt+10-eps)/10.0;
						formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0),"                                        ");
						formatted_output(1,vital_signs_area,0,0,MMPP(-100,360,0,0)
						,"生命值："+repeat_str("★",x)+repeat_str("☆",y));
					}//"生命值："+repeat_str("★",x)+repeat_str("☆",y)+"       "+int_to_str(x)+"                 "
				}
				if(player1.vts.stg.change||player1.d1_change||player1.items.sn_change){
					string s="";//提示信息 
					if(player1.vts.stg.physical_strength<25) s="体力告急！";
					else s="          ";
					formatted_output(1,vital_signs_area,50,0,MMPP(-100,360,0,120)
					,"体力值："+int_to_str(player1.vts.stg.physical_strength)+"%  "+s);
				}
			}
			void score_update(){//分数更新 
				logMessage("score_update");
				if(player1.scr.kc.change)
					formatted_output(1,vital_signs_area,160,0,MMPP(-100,360,0,60),"击杀数："+int_to_str(player1.scr.kc.sum));
			}
			void state_update(){//玩家状态更新 
				logMessage("state_update");
				/*
				if(player1.ak_change||player1.d1_change||player1.items.sn_change)
					switch(player1.action_kind){
						case RUN:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"奔跑     ");break;
						case WALK:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"行走     ");break;
						case CHOOSE_ITEM:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"选择物品 ");break;
						case CHANGE_WPN:formatted_output(1,vital_signs_area,1,5,MMPP(-100,360,0,180),"切换武器 ");break;
					}*/
				if(game_flag["游戏暂停/继续"]) formatted_output(1,whole_screen,1,47,MMPP(-100,360,0,360),(game_pause?"游戏暂停":"        "));
			}
			void special_effect_update(){//打印特殊效果 
				logMessage("special_effect_update");
				//int cnt_spe=0;//打印的效果个数 
				string spe_sentence;//连成一句话 
				special_effect &spe=player1.spe;
				bool flag_1s=game_time%1000==0;//一秒时间间隔已到 
				if(!flag_1s&&!spe.change()) return;//不用更新屏幕 int_to_str(++cnt_spe)+".
				if(spe.xry.change||spe.xry.num>1){//透视 
					spe_sentence+="【透视"+int_to_str(spe.xry.num-1)+"层，"
					+int_to_str(spe.xry.time>=game_time?(spe.xry.time-game_time)/1000:0)+"秒】";
				}
				if(spe.wks.change||spe.wks.exist()){//虚弱
					spe_sentence+="【虚弱"//+"-"+int_to_str(spe.wks.x)+"体力/秒，"
					+int_to_str(spe.wks.end>=game_time?(spe.wks.end-game_time)/1000:0)+"秒】";
				}
				if(spe.vtg.change||spe.vtg.exist()){//眩晕
					spe_sentence+="【眩晕"//+double_to_str(spe.vtg.T/1000.0,1)+","
					+int_to_str(spe.vtg.end>=game_time?(spe.vtg.end-game_time)/1000:0)+"秒】";
				}
				if(spe.bds.change||spe.bds.exist()){//致盲
					spe_sentence+="【失明"//+int_to_str(spe.bds.vision_dis)+","
					+int_to_str(spe.bds.end>=game_time?(spe.bds.end-game_time)/1000:0)+"秒】";
				}
				if(spe.mts.change||spe.mts.exist()){//中毒
					spe_sentence+="【中毒"//+double_to_str(spe.mts.T/1000.0,1)+","+int_to_str(spe.mts.x)+","
					+int_to_str(spe.mts.end>=game_time?(spe.mts.end-game_time)/1000:0)+"秒】";
				}
				if(spe.cfs.change||spe.cfs.exist()){//迷惑
					spe_sentence+="【迷惑"//+int_to_str(spe.cfs.a)
					+int_to_str(spe.cfs.end>=game_time?(spe.cfs.end-game_time)/1000:0)+"秒】";
				}
				int mx_size=70;
				if(spe_sentence.size()<=mx_size) spe_sentence+=repeat_char(' ',mx_size-spe_sentence.size());
				else spe_sentence.resize(mx_size);
				formatted_output(1,vital_signs_area,90,0,MMPP(-100,360,0,360),spe_sentence);
			}
			void weapon_update(){//武器状态更新 
				logMessage("weapon_update");
				if(player1.ak_change) player1.items.wpn_print1();
				if(player1.items.wpn.mode_change||player1.items.wpn.data_change||player1.items.wpn.sw_change) player1.items.wpn_print2();
				if(player1.items.wpn.sw_change) player1.items.wpn_print3();
			}
		void vital_signs_update(){
			logMessage("vital_signs_update");
			lives_update();
			score_update();
			state_update();
			special_effect_update();
			weapon_update();
		}
		void item_update(){
			logMessage("item_update");
			if(player1.ak_change) player1.items.print1();
			if(player1.items.il_change||player1.items.sn_change) player1.items.print2();
			if(player1.items.num_change||player1.items.sn_change) player1.items.print3();
		}
		void message_update(){
			logMessage("message_update");
			if(game_time%2000==0){
				int cnt=1,num=10;//最多信息条数 
				while(!message_box.empty()&&cnt<=num){
					PPII u=message_box.front();message_box.pop();
					PII a=u.first,b=u.second;
					formatted_output(1,whole_screen,1,35+cnt,MMPP(-100,360,0,360)
					,being_name(a)+"击杀了"+being_name(b)+"                ");
					cnt++;
				}
				while(cnt<=num) formatted_output(1,whole_screen,1,20+cnt,MMPP(-100,360,0,360),"                            "),cnt++;
			}
		}
	void screen_update(){//屏幕更新 
		logMessage("screen_update()",2); 
		player_flash_update();
		game_map_update();
		vital_signs_update();
		item_update();
		message_update();
		if(game_time%100==0){
			formatted_output(1,whole_screen,1,16,MMPP(0,30,-100,360),double_to_str(player1.w.speed,0,6));//+int_to_str(bugs.size(),6)
			formatted_output(1,whole_screen,1,17,MMPP(0,360,-100,360),int_to_str(pos_fog.size(),6));
			formatted_output(1,whole_screen,1,18,MMPP(0,360,-100,360),int_to_str(bugs.size(),6));
			formatted_output(1,whole_screen,1,19,MMPP(0,360,-100,360),int_to_str(Qbug.size(),6));
			formatted_output(1,whole_screen,1,20,MMPP(0,360,-100,360)
			,int_to_str(player1.pos.x,2)+","+int_to_str(player1.pos.y,2)+","+int_to_str(player1.pos.z,2));
			game_timer["雾"]=0;
		}
		/**/
		//	if(game_time%1000==0){
				//formatted_output(1,vital_signs_area,1,16,MMPP(0,360,-100,360),int_to_str(game_timer["虫"],6));
				//formatted_output(1,vital_signs_area,1,7,MMPP(0,360,-100,360),int_to_str(game_timer["循"],6));//现在统计calculate_vision2的调用次数 
				//formatted_output(1,vital_signs_area,1,16,MMPP(0,360,-100,360),int_to_str(game_timer["蜘蛛"],6));
		//		game_timer["循"]=game_timer["虫"]=0;
				
		//	}
			//formatted_output(1,vital_signs_area,1,17,MMPP(0,360,-100,360),int_to_str(Qbug.size(),2));
	}
		void judge_win_lose(){
		}
		void delay_time(){//延时1毫秒 
			do read_timer();
			while(now_timer<start_time+1);
			game_time+=now_timer-start_time;
		}
	void others(){
		logMessage("others()",2); 
		judge_win_lose();
		delay_time();
	}
void game(){//游戏部分 
	//此前不要清屏 
	logMessage("game()",2);
	game_time=1;
	//print_maze();
	while(!game_end){
		read_timer();start_time=now_timer;//本次循环开始时间 
		assigned();
		pause();
		if(game_pause) continue;//游戏暂停 
		deal_item();
		deal_enemy();
		deal_player();
		screen_update();
		others();
	}
} 
void win(){
	score &scr=player1.scr;
	MUSIC("Win.wav",1);
	formatted_output(2,whole_screen,40,19,MMPP(-100,360,0,120),
	"你赢了，"+player1.name+"！！！（耗时"+to_time(0,0,scr.time_spent/1000)+"）",1,150);
} 
void lose(){
	score &scr=player1.scr;
	MUSIC("Lose.wav",1);
	formatted_output(1,whole_screen,40,19,MMPP(-100,360,0,0),
	"你输了，"+player1.name+"……（存活"+to_time(0,0,scr.time_spent/1000)+"）");
}
void detail(){//详细游戏信息整理展示 
	PPII col=MMPP(-100,360,0,360);
	int kind=2;
	if(game_success) col=MMPP(-100,360,0,120),kind=2;
	else col=MMPP(-100,360,0,240),kind=1;
	score &scr=player1.scr;
	formatted_output(kind,whole_screen,40,20,col,"详细信息：",1,150);
	if(scr.shoot_times!=0) scr.hit_rate=scr.shoot_hit_times*1.0/scr.shoot_times;//
	else scr.hit_rate=0;
	formatted_output(kind,whole_screen,40,21,col,
	"地图大小：长"+int_to_str(length)+"米 宽"+int_to_str(width)+"米 高"+int_to_str(height)+"层"
	,1,150);
	formatted_output(kind,whole_screen,40,22,col,
	"击杀数："+int_to_str(scr.kc.sum)+" 射击命中率："+double_to_str(scr.hit_rate*100.0,1)+"%"
	,1,150);//
	formatted_output(kind,whole_screen,40,23,col,scr.kc.detail(),1,150);//打印明细 
	formatted_output(kind,whole_screen,40,24,col,
	"遭受攻击次数："+int_to_str(scr.hurt_times)
	+" 失去生命值："+double_to_str(player1.vts.lfin.hurt)+"% 回复生命值："+double_to_str(player1.vts.lfin.recovery)+"%"
	,1,150);
	if(kind==1) SLEEP(2000);
}
	void detect_start_again(){
		while(1){
			if(kbhit()){
				int c=_getch();
				switch(c){
					case PRESS_KEY_X:start_again=false;return;
					case PRESS_KEY_ENTER:start_again=true;return;
				}
			}
		}
	}
void ask_try_again(){
	formatted_output(1,whole_screen,40,25,MMPP(-100,360,0,360),"按下回车重新开始 按下X键退出游戏");
	detect_start_again();//wait_until(PRESS_KEY_ENTER);start_again=true; 
	formatted_output(2,whole_screen,40,25,MMPP(-100,360,0,180),"游戏加载中......",1,100);
}
void end(){//暂时不用 
	//此前要清屏 
	formatted_output(2,whole_screen,40,20,MMPP(-100,360,0,60),player1.name+"，欢迎下次再来！",1,150);
}
//函数定义 
