#include <string>
#include <iostream>
#include <vector>
using namespace std;

#if 0
class card
{
	int  time = 0;//默认时间为0,暂时不启用
	int index = 1;//表示第几副牌
	int type;//牌类型,三位数：abc：a = 花色（方块、梅花、红桃、黑桃）; bc = 牌数, 3-10,J,Q,K,A,2 = 3-15,大王小王116,117
	string userid;//用户ID,默认为空
};
#elif 0
class card_dz
{
	//用例中的牌型不分花色，3 - 10分别用3 - 10代表，11代表J，12代表Q，13代表K，14代表A，15代表2, 99代表小王，100代表大王
	//dz代表地主，n1代表地主的上家农民，n2代表地主的下家农民
	int n1;
	int n2;
	int dz[20];
	int nn[54 - 20];//剩余的牌
};

class card_n
{
	int dz;
	int n;
	int nm[17];
	int nn[54 - 17];//剩余的牌
};
#else
class card
{
	int DZIndex;
	bool GoodNM;
	bool IsDZ;//地主？
	bool IsOut;//主动出牌？
	//三家剩余牌数
	int RestRounds;//剩余手牌回合
	int frontN;//前家
	int behindN;//后家
	int myN;//我
	int KingBoom;
	int deck[20][2]; int deckIndex; //最优牌组 牌起点，牌数，标签 （1、2、3为顺子、连对、飞机，4为炸弹，0为散牌）
	int deckTwo[20][2]; int deckTwoIndex;
	int deckThree[20][2]; int deckThreeIndex;
	int One[20]; int OneIndex;//单排
	int OneMax[20]; int OneMaxIndex;
	int OneElseMax;
	int Two[20]; int TwoIndex;//双排
	int TwoMax[20]; int TwoMaxIndex;
	int TwoElseMax;
	int Three[20]; int ThreeIndex;//三个头
	int ThreeMax[20]; int ThreeMaxIndex;
	int ThreeElseMax;
	int Four[20]; int FourIndex;//炸弹
	//从 [3](3) - [15](2) 16(小王) 17(大王）
	int myCard[20];//我的手牌
	int elseCard[20];//对手的剩余的牌
	int c_list[20];//记牌器
	int mostLike;//对手喜欢的牌
public:
	card();
	card(int * Cards);
	card(int * Cards, int * BCards, int * FCards, int DZIndex);
	~card();
	int GetBestSort(int x);
	int ScoreOfDZ();//叫地主的分数,炸弹、大王小王和2、飞机葫芦
	bool CallDZ(int score, int MyScore);//叫地主、抢地主 //如果我先叫，则score=0,如果是抢地主，那么score=1;
	int SortTheCard();//理牌
	void SerchTheProgression(int LengthOfPg, int *Cards, int * result, int *Sum);//找长度为N的顺子
	void ActivePlay(int * Out);//出牌
	int PassivePlay(int *UpperCard, int * Out, int WhoseOut = -1);//接牌
	void EmergentOfOne();//报单
	void DZorNot(int * C, int YesOrNo);//地主加牌
	void UpdateC(int * C, int num, int whoseC);//更新牌
	int GetRestRound();
	void IsGoodNM();
	void InToOut(int * out);
	void CaLL(int I);
	void Sort(int * Out,vector<int> &vc);
};
#endif

