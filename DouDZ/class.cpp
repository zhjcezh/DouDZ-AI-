#include "class.h"

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
//class card
//{
//	bool IsDZ = false;//地主？
//	bool IsOut = false;//出牌？
//	//三家剩余牌数
//	int frontN = 17;//前家
//	int behindN = 17;//后家
//	int myN = 17;//我
//	int KingBoom = 0;
//	int deck[20][2];int deckIndex = 0; //最优牌组 牌起点，牌数，标签 （1、2、3为顺子、连对、飞机，4为炸弹，0为散牌）
//	int deckTwo[20][2];int deckTwoIndex = 0;
//	int deckThree[20][2]; int deckThreeIndex =0;
//	int One[20];int OneIndex = 0;//单排
//	int Two[20];int TwoIndex = 0;//双排
//	int Three[20]; int ThreeIndex = 0;//三个头
//	int Four[20]; int FourIndex = 0;//炸弹
//	//从 [3](3) - [15](2) 16(小王) 17(大王）
//	int myCard[20];//我剩余
//	int elseCard[20];//外面剩余的牌
//	int c_list[20];//记牌器
//	int mostLike = 0;//对手喜欢的牌
//public:
//	card(int * Cards);
//	~card();
//	int ScoreOfDZ();//叫地主的分数,炸弹、大王小王和2、飞机葫芦
//	bool CallDZ(int score, int MyScore);//叫地主、抢地主 //如果我先叫，则score=0,如果是抢地主，那么score=1;
//	int SortTheCard();//理牌
//	void SerchTheProgression(int LengthOfPg, int *Cards, int * result, int *Sum);//找长度为N的顺子
//	void ActivePlay();//出牌
//	int PassivePlay(int *UpperCard, int * Out);//接牌
//	void EmergentOfOne();//报单
//	void DZorNot(int * C, int YesOrNo);//地主加牌
//	void UpdateC(int * C, int num, int whoseC);//更新牌
//};
card::~card()
{

}

card::card()
{
	GoodNM = false;
	IsDZ = false;//地主？
	IsOut = false;//主动出牌？
	//三家剩余牌数
	RestRounds = 0;//剩余手牌回合
	frontN = 17;//前家
	behindN = 17;//后家
	myN = 17;//我
	KingBoom = 0;//王炸
	deckIndex = 0; //最优牌组 牌起点，牌数，标签 （1、2、3为顺子、连对、飞机，4为炸弹，0为散牌）
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//单排
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//双排
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//三个头
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//炸弹
	//从 [3](3) - [15](2) 16(小王) 17(大王）
	mostLike = 0;//对手喜欢的牌
}

card::card(int * Cards)//初始化牌组 整副牌
{
	GoodNM = false;
	IsDZ = false;//地主？
	IsOut = false;//主动出牌？
	//三家剩余牌数
	RestRounds = 0;//剩余手牌回合
	frontN = 17;//前家
	behindN = 17;//后家
	myN = 17;//我
	KingBoom = 0;
	deckIndex = 0; //最优牌组 牌起点，牌数，标签 （1、2、3为顺子、连对、飞机，4为炸弹，0为散牌）
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//单排
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//双排
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//三个头
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//炸弹
	//从 [3](3) - [15](2) 16(小王) 17(大王）
	mostLike = 0;//对手喜欢的牌
	//我的牌 和计数器
	for (int i = 3; i < 16; ++i)
	{
		myCard[i] = Cards[i];
		elseCard[i] = 4 - Cards[i];
	}
	myCard[16] = Cards[16];
	myCard[17] = Cards[17];
	elseCard[16] = 1 - Cards[16];
	elseCard[17] = 1 - Cards[17];
	SortTheCard();
	RestRounds = GetRestRound();
}
/*
判断所出牌的种类
*/
void card::InToOut(int * out)
{
	if (deckIndex == 1)
	{
		out[0] = deck[0][0];
		out[1] = deck[0][1];
		out[2] = 1;
	}
	else if (deckIndex == 2)
	{
		out[0] = deck[0][0];
		out[1] = deck[0][1];
		out[2] = 2;
	}
	else if (deckTwoIndex == 1)
	{
		out[0] = deckTwo[0][0];
		out[1] = deckTwo[0][1];
		out[2] = 2;
	}
	else if (deckThreeIndex == 1)
	{
		out[0] = deckThree[0][0];
		out[1] = deckThree[0][1];
		out[2] = 3;
		if (OneIndex > 0)
		{
			out[3] = 3;
			out[4] = 1;
		}
		else if (TwoIndex > 0)
		{
			out[3] = 3;
			out[4] = 2;
		}
	}
	else if (ThreeIndex == 1)
	{
		out[0] = Three[0];
		out[1] = 3;
		out[2] = 0;
		if (OneIndex > 0)
		{
			out[3] = 3;
			out[4] = 1;
		}
		else if (TwoIndex > 0)
		{
			out[3] = 3;
			out[4] = 2;
		}
	}
	else if (FourIndex == 1)
	{
		out[0] = Four[0];
		out[1] = 4;
		out[2] = 4;
		if (OneIndex > 0)
		{
			out[3] = 3;
			out[4] = 1;
		}
		else if (TwoIndex > 0)
		{
			out[3] = 3;
			out[4] = 2;
		}
	}
	else if (KingBoom == 1)
	{
		out[0] = 17;
		out[1] = 2;
		out[2] = 4;
	}
	else if (TwoIndex == 1)
	{
		out[0] = Two[0];
		out[1] = 2;
		out[2] = 0;
	}
	else
	{
		out[0] = One[0];
		out[1] = 1;
		out[2] = 0;
	}
}
/*
不知道什么用
*/
card::card(int * Cards, int * BCards, int *FCards, int DZindex)
{
	GoodNM = false;
	IsDZ = false;//地主？
	IsOut = false;//主动出牌？
	//三家剩余牌数
	RestRounds = 0;//剩余手牌回合
	frontN = 17;//前家
	behindN = 17;//后家
	myN = 17;//我
	KingBoom = 0;
	deckIndex = 0; //最优牌组 牌起点，牌数，标签 （1、2、3为顺子、连对、飞机，4为炸弹，0为散牌）
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//单排
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//双排
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//三个头
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//炸弹
	//从 [3](3) - [15](2) 16(小王) 17(大王）
	mostLike = 0;//对手喜欢的牌

	myN = behindN = frontN = 0;
	for (int i = 3; i < 18; ++i)
	{
		myN += Cards[i];
		behindN += BCards[i];
		frontN += FCards[i];
		myCard[i] = Cards[i];
		elseCard[i] = FCards[i] + BCards[i];
	}
	if (DZindex == 1)
	{
		IsDZ = true;
	}
	else if (DZindex == 2)
	{
		DZIndex = 1;
		IsGoodNM();
	}
	else
	{
		DZIndex = -1;
		IsGoodNM();
	}
	SortTheCard();
	RestRounds = GetRestRound();
}

int card::GetRestRound()//求还可以出几回合的最优解
{
	//可优化
	int numOfRound = deckIndex + deckTwoIndex + ThreeIndex + deckThreeIndex + FourIndex + KingBoom;
	int sum = ThreeIndex;
	if (sum < OneIndex + TwoIndex)
	{
		numOfRound += OneIndex + TwoIndex - sum;
	}
	return numOfRound;
}

void card::UpdateC(int * C, int num, int whoseC)//更新手牌数据
{
	if (whoseC == 0)
	{
		myN -= num;
		for (int i = 0; i < num; ++i)
		{
			myCard[C[i]]--;
		}

	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			elseCard[C[i]]--;
		}
		if (whoseC == 1)
		{
			behindN -= num;
		}
		else
		{
			frontN -= num;
		}
	}
	int maxOneRest = 0, maxTwoRest = 0, maxThreeRest = 0;;
	for (int i = 3; i < 16; ++i)
	{
		if (elseCard[i] > 2)
		{
			if (i > maxThreeRest)
			{
				maxThreeRest = i;
			}
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 1)
		{
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 0)
		{
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
	}
	if (elseCard[16] == 1)
	{
		maxOneRest = 16;
	}
	if (elseCard[17] == 1)
	{
		maxOneRest = 17;
	}
	//手牌最大
	OneElseMax = maxOneRest;
	TwoElseMax = maxTwoRest;
	ThreeElseMax = maxThreeRest;
}

void card::DZorNot(int * C, int YesOrNo)//地主加牌 1（地主是后家） 0为自己
{
	const int DZaddC = 3;
	if (YesOrNo == 0)
	{
		IsDZ = true;
		myN += DZaddC;
		for (int i = 0; i < DZaddC; ++i)
		{
			myCard[C[i]]++;
			elseCard[C[i]]--;
		}
	}
	else if (YesOrNo ==1)
	{
		behindN += DZaddC;
	}
	else
	{
		frontN += DZaddC;
	}
}
/*
主动出牌
*/
void card::ActivePlay(int * Out)//出牌 WhoseOut 友军=1 否则 -1
{
	if (GetRestRound() == 1)
	{
		if (deckIndex == 1)
		{
			Out[0] = deck[0][0];
			Out[1] = deck[0][1];
			Out[2] = 1;
			deckIndex--;
			return;
		}
		else if (deckTwoIndex == 1)
		{
			Out[0] = deckTwo[0][0];
			Out[1] = deckTwo[0][1];
			Out[2] = 2;
			deckTwoIndex--;
			return;
		}
		else if (deckThreeIndex == 1)
		{
			Out[0] = deckThree[0][0];
			Out[1] = deckThree[0][1];
			Out[2] = 3;
			deckThreeIndex--;
		}
		else if (ThreeIndex == 1)
		{
			Out[0] = Three[0];
			Out[1] = 3;
			Out[2] = 0;
			ThreeIndex--;
			if (OneIndex > 0)
			{
				Out[3] = One[0];
				Out[4] = 1;
				OneIndex--;
			}
			else if (TwoIndex > 0)
			{
				Out[3] = Two[0];
				Out[4] = 2;
				TwoIndex--;
			}
			else
			{
				//不带
			}
			return;
		}
		else if (OneIndex == 1)
		{
			Out[0] = One[0];
			Out[1] = 1;
			Out[2] = 0;
			OneIndex--;
		}
		else if (TwoIndex == 1)
		{
			Out[0] = Two[0];
			Out[1] = 2;
			Out[2] = 0;
			TwoIndex--;
		}
		else if (KingBoom == 1)
		{
			Out[0] = 17;
			Out[1] = 2;
			Out[2] = 4;
			KingBoom = 0;
		}
		else if (FourIndex == 1)
		{
			Out[0] = Four[0];
			Out[1] = 4;
			Out[2] = 4;
			FourIndex--;
		}
		else
		{
			//没牌了？
		}
		return;
	}
	if (GetRestRound() == 2)
	{
		if (deckIndex == 1)
		{
			Out[0] = deck[0][0];
			Out[1] = deck[0][1];
			Out[2] = 1;
			deckIndex--;
			return;
		}
		else if (deckTwoIndex == 1)
		{
			Out[0] = deckTwo[0][0];
			Out[1] = deckTwo[0][1];
			Out[2] = 2;
			deckTwoIndex--;
			return;
		}
		else if (deckThreeIndex == 1)
		{
			Out[0] = deckThree[0][0];
			Out[1] = deckThree[0][1];
			Out[2] = 3;
			deckThreeIndex--;
			if (TwoIndex == 1)
			{
				Out[3] = Two[0];
				Out[4] = 1;
				Out[5] = Two[0];
			}
			return;
		}
		else if (ThreeIndex == 1)
		{
			Out[0] = Three[0];
			Out[1] = 3;
			Out[2] = 0;
			ThreeIndex--;
			if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
			{
				if (One[0] < Two[0])
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
			}
			else if (OneIndex > 0)//单排
			{
				Out[3] = One[0];
				Out[4] = 1;
				OneIndex--;
				for (int i = 0; i < OneIndex; ++i)
				{
					One[i] = One[i + 1];
				}
			}
			else if (TwoIndex > 0)//对子
			{
				Out[3] = Two[0];
				Out[4] = 2;
				TwoIndex--;
				for (int i = 0; i < TwoIndex; ++i)
				{
					Two[i] = Two[i + 1];
				}
			}
			else
			{
				//不带
			}
			return;
		}
		else if (OneIndex == 2 && One[1] >= OneElseMax)
		{
			Out[0] = One[1];
			Out[1] = 1;
			Out[2] = 0;
			OneIndex--;
			return;
		}
		else if (OneIndex == 1 && One[0] >= OneElseMax)
		{
			Out[0] = One[0];
			Out[1] = 1;
			Out[2] = 0;
			OneIndex--;
			return;
		}
		else if (TwoIndex == 2 && Two[1] >= TwoElseMax)
		{
			Out[0] = Two[1];
			Out[1] = 2;
			Out[2] = 0;
			TwoIndex--;
			return;
		}
		else if (TwoIndex == 1 && Two[0] >= TwoElseMax)
		{
			Out[0] = Two[0];
			Out[1] = 2;
			Out[2] = 0;
			TwoIndex--;
			return;
		}
		else
		{
			//没牌了？
		}
	}
	if (IsDZ)//地主AI
	{
		//************************报单且报双****************************//
		if ((frontN == 1 || behindN == 1) && (frontN == 2 || behindN == 2))
		{
			if (deckThreeIndex > 0)//把飞机拆了，三带都压不了
			{
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					bool flag = false;
					for (int j = 0; j < ThreeIndex; j++)
					{
						if (Three[j] > deckThree[i][0])
						{
							flag = true;
							for (int k = ThreeIndex; k > j; --k)
							{
								Three[k - 1 + deckThree[i][1]] = Three[k - 1];
							}
							ThreeIndex += deckThree[i][0];
							for (int k = 0; k < deckThree[i][1]; ++k)
							{
								Three[j + k] = deckThree[i][0] + k;
							}
						}
					}
					if (flag == false)
					{
						for (int k = 0; k < deckThree[i][1]; ++k)
						{
							Three[ThreeIndex + k] = deckThree[i][0] + k;
						}
						ThreeIndex += deckThree[i][1];
					}
				}
			}
			//找出那3张牌
			int lastOne = -1, lastTwo = -1;
			int maxOne = -1;
			for (int i = 3; i < 18; ++i)
			{
				if (elseCard[i] > 0)
				{
					lastOne = i;
					maxOne = i;
				}
				if (elseCard[i] > 1)
				{
					lastTwo = i;
					maxOne = i;
				}
			}
			//寻找标签最小的套牌	，压不了的赶紧出
			if (deckIndex > 0)
			{	
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else//没有套牌
			{
				//int lastOne = -1, lastTwo = -1;
				int UnsafeOneNum = 0, UnsafeTwoNum = 0;
				for (int i = 0; i < OneIndex; ++i)
				{
					if (One[i] < lastOne)
					{
						UnsafeOneNum++;
					}
					else
					{
						break;
					}
				}
				for (int i = 0; i < TwoIndex; ++i)
				{
					if (Two[i] < lastTwo)
					{
						UnsafeTwoNum++;
					}
					else
					{
						break;
					}
				}
				//-----------2手牌-------------//
				int Rounds = GetRestRound();
				if (Rounds == 2)
				{
					if (KingBoom == 1)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return;
					}
					if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return;
					}
				}
				//-----------分割线-------------//
				if (ThreeIndex > 0)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;//three类型为单牌
					if (UnsafeOneNum > 0)
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (UnsafeTwoNum > 0)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					else
					{
						//稳赢自信不带。
					}
				}
				else if (TwoIndex > UnsafeTwoNum)
				{
					Out[0] = Two[TwoIndex - 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
				}
				else if (FourIndex > 0)//四带二的情况
				{
					bool IsFour = false;
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						IsFour = true;
						if (UnsafeOneNum > 1)
						{
							Out[3] = One[0];
							Out[4] = 1;
							Out[5] = One[1];
							OneIndex -= 2;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 2];
							}
						}
						else if (UnsafeTwoNum > 1)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							Out[5] = Two[1];
							TwoIndex -= 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 2];
							}
						}
						else if (UnsafeTwoNum > 0 && UnsafeOneNum > 0 && Two[0] > One[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							Out[5] = Two[0];
							TwoIndex--;
							One[0] = Two[0];
							Two[0] = 0;
							
						}
						else if (UnsafeTwoNum > 0)
						{
							Out[3] = Two[0];
							TwoIndex--;
							Out[4] = 1;
							Out[5] = Two[0];
							Two[0] = 0;
						}
						else
						{
							//稳赢自信不带。
						}
					if (IsFour)
					{
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
					}
					return;
				}
				else//只剩单双；
				{
					if (UnsafeTwoNum == 0 && TwoIndex > 0)
					{
						if (TwoIndex > 1)
						{
							Out[0] = Two[0];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + 1];
							}
							return;
						}
						else
						{
							if (Two[0] <= lastOne)
							{
								Out[0] = Two[0];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								Two[0] = 0;
								return;
							}
							else
							{
								Out[0] = Two[0];
								Out[1] = 1;
								Out[2] = 0;
								TwoIndex--;
								bool flag = false;
								for (int i = 0; i < OneIndex; ++i)
								{
									if (One[i] > Two[0])
									{
										for (int j = OneIndex; j > i; --j)
										{
											One[j] = One[j - 1];
										}
										One[i] = Two[0];
										Two[0] = 0;
										flag = true;
										OneIndex++;
										break;
									}
								}
								if (!flag)
								{
									One[OneIndex] = Two[0];
									Two[0] = 0;
									OneIndex++;
								}
								return;
							}
						}
					}
					else if (UnsafeOneNum == OneIndex && UnsafeTwoNum == TwoIndex && UnsafeTwoNum > 0)//只能赌一把对面没对子；
					{
						TwoIndex--; UnsafeTwoNum--;
						Out[0] = Two[TwoIndex];
						Out[1] = 2;
						Out[2] = 0;
						return;
					}
					else if (UnsafeOneNum == OneIndex && UnsafeTwoNum == TwoIndex && UnsafeOneNum > 0)
					{
						OneIndex--; UnsafeTwoNum--;
						Out[0] = One[OneIndex];
						Out[1] = 2;
						Out[2] = 0;
						One[OneIndex] = 0;
						return;
					}
					else if (UnsafeOneNum == 1 && One[UnsafeOneNum - 1] > maxOne)
					{
						OneIndex--;
						Out[0] = One[OneIndex];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
					else if (UnsafeOneNum > 0 && UnsafeTwoNum == 0 && OneIndex > UnsafeOneNum)
					{
						OneIndex--;
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						One[OneIndex - 1] = One[OneIndex];
						One[OneIndex] = 0;
					}
					else if (UnsafeOneNum == 0 && UnsafeTwoNum == 1)
					{
						if (OneIndex - 1 > 0) 
						{
							if (One[OneIndex - 1] > maxOne)
							{
								OneIndex--;
								Out[0] = One[OneIndex - 1];
								Out[1] = 1;
								Out[2] = 0;
							}
							else
							{
								TwoIndex--;
								UnsafeTwoNum--;
								Out[0] = Two[TwoIndex];
								Out[1] = 2;
								Out[2] = 0;
							}

						}
						else
						{
							OneIndex--;
							Out[0] = One[OneIndex];
							Out[1] = 1;
							Out[2] = 0;
						}
					}
					else if (UnsafeOneNum == 0 && UnsafeTwoNum > 1)
					{
						UnsafeTwoNum--;
						TwoIndex--;
						Out[0] = Two[TwoIndex];
						Out[1] = 2;
						Out[2] = 0;
					}
					if (TwoIndex > 0 && Out[2] == -1)
					{
						TwoIndex--;
						Out[0] = Two[TwoIndex];
						Out[1] = 2;
						Out[2] = 0;
					}
					else if (OneIndex > 0 && Out[2] == -1)
					{
						OneIndex--;
						Out[0] = One[OneIndex];
						Out[1] = 1;
						Out[2] = 0;
					}
					return;
				}
				return;
			}
		}
		//********************报单***************************//
		else if ((frontN == 1 || behindN == 1))
		{
			//寻找标签最小的套牌	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//还可以深入考虑
				if (OneIndex >= deckThree[0][1] && One[deckThree[0][1]-1] < 15)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0)
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else if (TwoIndex > 0)
						{
							int sum = TwoIndex;
							if (Two[sum - 1] > 14)
							{
								sum--;
							}
							if (sum > 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = sum;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 2;
								for (int i = 1; i < sum; i++)
								{
									Out[i + 4] = Two[i];
								}
								TwoIndex -= sum;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - sum > 1)
								{
									deckThree[0][0] = deckThree[0][0] + sum;
									deckThree[0][1] = deckThree[0][1] - sum;
								}
								else
								{
									if (deckThree[0][1] - sum == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else if (sum == 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = 2;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - 2 > 1)
								{
									deckThree[0][0] = deckThree[0][0] + 2;
									deckThree[0][1] = deckThree[0][1] - 2;
								}
								else
								{
									if (deckThree[0][1] - 2 == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else
							{
								Out[0] = deckThree[0][0];
								Out[1] = deckThree[0][1];
								Out[2] = 3;
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//防止777888999,3455，结果会是777888999带355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else//没有套牌
			{
				int Rounds = GetRestRound();
				if (Rounds == 2)
				{
					if (KingBoom == 1)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return;
					}
					if (FourIndex > 0)
					{
						if (frontN >= 4 || behindN >= 4)
						{
							int i = Four[0] + 1;
							for (; i < 16; ++i)
							{
								if (elseCard[i] == 4)
								{
									break;
								}
							}
							if (i == 16)
							{
								Out[0] = Four[0];
								Out[1] = 4;
								Out[2] = 4;
								FourIndex--;
								for (int j = 0; j < FourIndex; ++j)
								{
									Four[j] = Four[j + 1];
								}
								return;
							}
						}
						else
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = 0; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
							return;
						}
					}
				}
				//---------分割线-------------//
				if (ThreeIndex > 0)
				{
					if (OneIndex > 0 && One[0] < 15)
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)//对A 对2留着
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					ThreeIndex--;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						Three[i] = Three[i + 1];
					}
					return;
				}
				else if (FourIndex == 0)
				{
					if (TwoIndex > 0)
					{
						Out[0] = Two[0];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
						return;
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
				}
				else if (OneIndex > FourIndex * 2 + 1)
				{
					Out[0] = One[FourIndex * 2 + 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = FourIndex * 2 + 1; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
					return;
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					FourIndex--;
					if (OneIndex > 1 && One[1] < OneElseMax)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						OneIndex -= 2;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 2];
						}
					}
					else if (TwoIndex > 1 && Two[1] < TwoElseMax)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 2];
						}
					}
					else if (TwoIndex == 1 && OneIndex == 1 && One[0] < 16)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						if (Two[0] > One[0])
						{
							Out[5] = One[0];
							One[0] = Two[0];
						}
						else
						{
							Out[5] = Two[0];
						}
					}
					else if (TwoIndex == 1)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
					}
					return;
				}
			}
		}
		//***********************报双**************************//
		else if ((frontN == 2 || behindN == 2))
		{
			//寻找标签最小的套牌	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//还可以深入考虑
				if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 15)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else if (TwoIndex > 0)
						{
							int sum = TwoIndex;
							if (Two[sum - 1] > 14)
							{
								sum--;
							}
							if (sum > 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = sum;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 2;
								for (int i = 1; i < sum; i++)
								{
									Out[i + 4] = Two[i];
								}
								TwoIndex -= sum;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - sum > 1)
								{
									deckThree[0][0] = deckThree[0][0] + sum;
									deckThree[0][1] = deckThree[0][1] - sum;
								}
								else
								{
									if (deckThree[0][1] - sum == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else if (sum == 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = 2;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - 2 > 1)
								{
									deckThree[0][0] = deckThree[0][0] + 2;
									deckThree[0][1] = deckThree[0][1] - 2;
								}
								else
								{
									if (deckThree[0][1] - 2 == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else
							{
								Out[0] = deckThree[0][0];
								Out[1] = deckThree[0][1];
								Out[2] = 3;
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//防止777888999,3455，结果会是777888999带355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			int Rounds = GetRestRound();
			if (Rounds == 2)
			{
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return;
				}
				if (FourIndex > 0 && (elseCard[16] == 0 || elseCard[17] == 0))
				{
					if (frontN >= 4 || behindN >= 4)
					{
						int i = Four[0] + 1;
						for (; i < 16; ++i)
						{
							if (elseCard[i] == 4)
							{
								break;
							}
						}
						if (i == 16)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = 0; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
							return;
						}
					}
					else
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return;
					}
				}
				//单、双最大。
				if (OneIndex > 0)
				{
					for (int i = 17; i > 2; --i)
					{
						if (i <= One[OneIndex - 1])
						{
							OneIndex--;
							Out[0] = One[OneIndex];
							Out[1] = 1;
							Out[2] = 0;
							return;
						}
					}
				}
				if (TwoIndex > 0)
				{
					for (int i = 15; i > 2; --i)
					{
						if (i <= Two[TwoIndex - 1])
						{
							TwoIndex--;
							Out[0] = Two[TwoIndex];
							Out[1] = 2;
							Out[2] = 0;
							return;
						}
					}
				}
			}
			//---------分割线-------------//
			if (ThreeIndex > 0)
			{
				if (TwoIndex > 0 && Two[0] < TwoElseMax)
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (OneIndex > 0 && One[0] < OneElseMax)//2留着
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				ThreeIndex--;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					Three[i] = Three[i + 1];
				}
				return;
			}
			else//没有套牌
			{
				//暂未考虑拆牌
				if (FourIndex == 0)
				{
					if (OneIndex > 1 && ((One[OneIndex - 1] > OneElseMax) || (TwoIndex > 0 && Two[0] > OneElseMax)))
					{
						Out[0] = One[OneIndex - 2];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
					if (TwoIndex > 0)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						return;
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
				}
				else if (TwoIndex > FourIndex * 2 + 1)
				{
					// 7单， 2炸
					Out[0] = Two[FourIndex * 2 + 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = FourIndex * 2 + 1; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					FourIndex--;
					if (OneIndex > 1 && One[1] < OneElseMax)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						OneIndex -= 2;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 2];
						}
					}
					else if (TwoIndex > 1 && Two[1] < TwoElseMax)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 2];
						}
					}
					else if (TwoIndex == 1 && OneIndex == 1 && One[0] < OneElseMax)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						if (Two[0] > One[0])
						{
							Out[5] = One[0];
							One[0] = Two[0];
						}
						else
						{
							Out[5] = Two[0];
						}
					}
					else if (TwoIndex == 1 && Two[0] < TwoElseMax)
					{
						TwoIndex--;
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[0];
						Out[1] = 1;
						Out[2] = 0;
					}
					else if (TwoIndex > 0)
					{
						Out[0] = Two[0];
						Out[1] = 2;
						Out[2] = 0;
					}
					return;
				}
				return;
			}
		}
		//**********************正常出牌****************************//
		else
		{
			int Rounds = GetRestRound();
			if (deckIndex > 0 && (deck[0][0] + deck[0][1] - 1 < 11 || deck[0][1] > 6 || frontN < 9 || behindN < 9 || Rounds < 4 || (One[0] >= deck[0][0] && Two[0] >= deck[0][0])))//顺子
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0 && deckThree[0][0] + deckThree[0][1] - 1 <= OneElseMax && (deckThree[0][0] + deckThree[0][1] - 1 < 11 || frontN < 6 || behindN < 6 || OneIndex - deckThree[0][1] < 3 || Rounds < 5 || (One[0] >= deckThree[0][0] && Two[0] >= deckThree[0][0])))
			{
				//还可以深入考虑
				if (ThreeIndex > 0 && Three[0]<deckThree[0][0])
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					for (int i = 0; i < ThreeIndex; i++)
					{
						Three[i] = Three[i + 1];
					}
					ThreeIndex--;
					if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
					{
						if (One[0] < Two[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							OneIndex--;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
						}
						else
						{
							Out[3] = Two[0];
							Out[4] = 2;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
						}
					}
					else if (OneIndex > 0)//单排
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0)//对子
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					return;
				}
				if (OneIndex > deckThree[0][1] && TwoIndex > deckThree[0][1] && One[deckThree[0][1] - 1] < 13 && Two[deckThree[0][1] - 1] < 13)
				{
					int a = 0;
					int b = 0;
					for (int i = 0; i < deckThree[0][1]; i++)
					{
						a += One[i];
						b += Two[i];
					}
					if (a <= b)
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = One[0];
						Out[4] = 1;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= deckThree[0][1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + deckThree[0][1]];
						}
					}
					else
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= deckThree[0][1];
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + deckThree[0][1]];
						}
					}
				}
				else if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 15)
				{

					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 15)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else if (TwoIndex > 0)
						{
							int sum = TwoIndex;
							if (Two[sum - 1] > 14)
							{
								sum--;
							}
							if (sum > 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = sum;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 2;
								for (int i = 1; i < sum; i++)
								{
									Out[i + 4] = Two[i];
								}
								TwoIndex -= sum;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - sum > 1)
								{
									deckThree[0][0] = deckThree[0][0] + sum;
									deckThree[0][1] = deckThree[0][1] - sum;
								}
								else
								{
									if (deckThree[0][1] - sum == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else if (sum == 1)
							{
								Out[0] = deckThree[0][0];
								Out[1] = 2;
								Out[2] = 3;
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								if (deckThree[0][1] - 2 > 1)
								{
									deckThree[0][0] = deckThree[0][0] + 2;
									deckThree[0][1] = deckThree[0][1] - 2;
								}
								else
								{
									if (deckThree[0][1] - 2 == 1)
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > Out[0])
											{
												fg = true;
												for (int j = ThreeIndex; j > i; j--)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = Out[0] + Out[1];
												ThreeIndex++;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = Out[0] + Out[1];
											ThreeIndex++;
										}
									}
									for (int i = 0; i < deckThreeIndex; ++i)
									{
										deckThree[i][0] = deckThree[i + 1][0];
										deckThree[i][1] = deckThree[i + 1][1];
									}
								}
								return;
							}
							else
							{
								Out[0] = deckThree[0][0];
								Out[1] = deckThree[0][1];
								Out[2] = 3;
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//防止777888999,3455，结果会是777888999带355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else if (ThreeIndex > 0 && Three[0]!=15 && Three[0]!=14 && (Three[0] < 11 || frontN < 4 || behindN < 4 || (OneIndex < 2 && TwoIndex < 2)))//判断三带一还是二还是不带
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0)//单排
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//对子
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else if (deckTwoIndex > 0 && (TwoIndex == 0 || deckTwo[0][0] <= Two[0]) && (deckTwo[0][0] + deckTwo[0][1] - 1 < 11 || frontN < 9 || behindN < 9 || Rounds < 5))//连对
			{
				if (TwoIndex > 1&&Two[0]<deckTwo[0][0])
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					return;
				}
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			//---------分割线-------------//
			if (ThreeIndex > 0 && OneIndex + TwoIndex < 4)
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0)//单排
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//对子
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else if(OneIndex > 0 && TwoIndex > 0)//什么小出哪个
			{
				if(One[0] < Two[0])
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
					return;
				}
				else
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
					return ;
				}
			}
			else if (OneIndex > 0)//单排
			{
				Out[0] = One[0];
				Out[1] = 1;
				Out[2] = 0;
				OneIndex--;
				for (int i = 0; i < OneIndex; ++i)
				{
					One[i] = One[i + 1];
				}
			}
			else if (TwoIndex > 0)//对子
			{
				Out[0] = Two[0];
				Out[1] = 2;
				Out[2] = 0;
				TwoIndex--;
				for (int i = 0; i < TwoIndex; ++i)
				{
					Two[i] = Two[i + 1];
				}
			}
			else if (FourIndex > 0)//four
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
			}
			else if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
			}
			else//没牌了
			{
					
			}
			return;
		}
	}
	//****************农民*********************//
	else
	{
		// behindN == 1 && DZIndex == 1  后家地主报单
		//if (behindN == 1 && DZIndex == -1)//朋友农民报单，切地主不报单
		//----------------------下家农民报单||上家农名报单，下家地主大于一张
		if ((behindN == 1 && DZIndex == -1 && frontN > 1) || (frontN == 1 && DZIndex == 2 && behindN > 1))
		{
			if (GetRestRound() == 1)
			{
				if (deckIndex == 1)
				{
					Out[0] = deck[0][0];
					Out[1] = deck[0][1];
					Out[2] = 1;
					deckIndex--;
					return;
				}
				else if (deckTwoIndex == 1)
				{
					Out[0] = deckTwo[0][0];
					Out[1] = deckTwo[0][1];
					Out[2] = 2;
					deckTwoIndex--;
					return;
				}
				else if (deckThreeIndex == 1)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					deckThreeIndex--;
				}
				else if (ThreeIndex == 1)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					ThreeIndex--;
					if (OneIndex > 0)
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
					}
					else if (TwoIndex > 0)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
					}
					else
					{
						//不带
					}
					return;
				}
				else if (OneIndex == 1)
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
				}
				else if (TwoIndex == 1)
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
				}
				else if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
				}
				else if (FourIndex == 1)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
				}
				else
				{
					//没牌了？
				}
				return;
			}
			else
			{
				for (int i = 3; i < 18; ++i)
				{
					if (myCard[i] < 4 && myCard[i] > 0)
					{
						Out[0] = i;
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
				}
			}
			return;
		}
		//----------------------地主报单
		else if ((DZIndex == 2 && behindN == 1) || (DZIndex == -1 && frontN == 1))
		{
			//寻找标签最小的套牌	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//还可以深入考虑
				if (OneIndex >= deckThree[0][1])
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0)
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//防止777888999,3455，结果会是777888999带355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			//两手牌
			int Rounds = GetRestRound();
			if (Rounds == 2)
			{
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return;
				}
				if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					return;
				}
			}
			//---------分割线-------------//
			if (ThreeIndex > 0)
			{
				if (OneIndex > 0 && One[0] < 16)
				{	
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0 && Two[0] < 14)//对A 对2留着
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				ThreeIndex--;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					Three[i] = Three[i + 1];
				}
				return;
			}
			else//没有套牌
			{
				if (TwoIndex > 0)
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (FourIndex == 0 && OneIndex > 0)
				{
					Out[0] = One[OneIndex - 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
				}
				else if (OneIndex > FourIndex * 2 + 1)
				{
					Out[0] = One[FourIndex * 2 + 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = FourIndex * 2 + 1; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					if (OneIndex > 1)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						OneIndex -= 2;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 2];
						}
					}
				}
				return;
			}
		}
		//----------------------地主报双
		else if ((DZIndex == 2 && behindN == 2) || (DZIndex == -1 && frontN == 2))
		{
			//寻找标签最小的套牌	
			if (deckIndex > 0)
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0)
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0)
			{
				//还可以深入考虑
				if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] <= OneElseMax)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] <= OneElseMax)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//防止777888999,3455，结果会是777888999带355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			//两手牌
			int Rounds = GetRestRound();
			if (Rounds == 2)
			{
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return;
				}
				if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					return;
				}
			}
			//---------分割线-------------//
			if (ThreeIndex > 0)
			{
				if (TwoIndex > 0 && Two[0] < TwoElseMax)
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (OneIndex > 0 && One[0] <= OneElseMax)
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				ThreeIndex--;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					Three[i] = Three[i + 1];
				}
				return;
			}
			else//没有套牌
			{	
				int maxONE = 0;int tempN=0;
				for(int i = 0;i < OneIndex;++i)
				{
					if (One[i] >= OneElseMax)
					{
						tempN++;
					}
				}
				if (FourIndex == 0)
				{
					if (OneIndex > 1 && ((One[OneIndex - 1] > OneElseMax) || (TwoIndex > 0 && Two[0] > OneElseMax)))
					{
						Out[0] = One[OneIndex - 2];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
					if (TwoIndex > 0 && Two[TwoIndex - 1] <= OneElseMax)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						return;
					}
					else if (OneIndex > 1)
					{
						Out[0] = One[OneIndex - 2];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
					else if (OneIndex > 0)
					{
						Out[0] = One[0];
						Out[1] = 1;
						Out[2] = 0;
						return;
					}
					else
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						return;
					}
				}
				else if (TwoIndex > FourIndex * 2 + 1)
				{
					// 7单， 2炸
					Out[0] = Two[FourIndex * 2 + 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = FourIndex * 2 + 1; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (OneIndex > 1)
				{
					Out[0] = One[OneIndex - 2];
					Out[1] = 1;
					Out[2] = 0;
				}
				else if (OneIndex > 0)
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
				}
				else
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					if (TwoIndex > 1)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
					}
					else if (TwoIndex > 0)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
					}
				}
				return;
			}
			
		}
		//------------牌好的农民 ||地主下家
		else if (GoodNM || (DZIndex == -1))
		{
			int Rounds = GetRestRound();
			//寻找标签最小的套牌	
			if (deckIndex > 0 && (deck[0][0] + deck[0][1] - 1 < 12 || deck[0][1] > 6 || Rounds < 5 || (One[0] >= deck[0][0] && Two[0] >= deck[0][0])))
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0 && (TwoIndex == 0 || deckTwo[0][0] <= Two[0]) && (deckTwo[0][0] + deckTwo[0][1] - 1 < 13 || Rounds < 4 ))
			{
				if (TwoIndex > 1 && Two[0]<deckTwo[0][0])
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					return;
				}
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0 && deckThree[0][0] + deckThree[0][1] - 1 <= OneElseMax && (deckThree[0][0] + deckThree[0][1] - 1 < 11 || OneIndex - deckThree[0][1] < 3 || Rounds < 5))
			{
				//还可以深入考虑
				if (ThreeIndex > 0 && Three[0]<deckThree[0][0])
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					for (int i = 0; i < ThreeIndex; i++)
					{
						Three[i] = Three[i + 1];
					}
					ThreeIndex--;
					if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
					{
						if (One[0] < Two[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							OneIndex--;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
						}
						else
						{
							Out[3] = Two[0];
							Out[4] = 2;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
						}
					}
					else if (OneIndex > 0)//单排
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0)//对子
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					return;
				}
				if (OneIndex > deckThree[0][1] && TwoIndex > deckThree[0][1] && One[deckThree[0][1] - 1] < 13 && Two[deckThree[0][1] - 1] < 13)
				{
					int a = 0;
					int b = 0;
					for (int i = 0; i < deckThree[0][1]; i++)
					{
						a += One[i];
						b += Two[i];
					}
					if (a <= b)
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = One[0];
						Out[4] = 1;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= deckThree[0][1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + deckThree[0][1]];
						}
					}
					else
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= deckThree[0][1];
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + deckThree[0][1]];
						}
					}
				}
				else if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 14)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//防止777888999,3455，结果会是777888999带355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else if (ThreeIndex > 0 && Three[0] != 15 && Three[0] != 14 && (Three[0] < 11 || (OneIndex < 2 && TwoIndex < 2)))//判断三带一还是二还是不带
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//单排
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//对子
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}	
			if (ThreeIndex > 0 && OneIndex + TwoIndex < 4)
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//单排
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//对子
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
			{
				if (One[0] < Two[0])
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
					return;
				}
				else
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
					return;
				}
			}
			else if (OneIndex > 0)//单排
			{
				if (OneIndex == 2 && One[OneIndex - 1] >= OneElseMax)
				{
					Out[0] = One[OneIndex - 1];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					return;
				}
				Out[0] = One[0];
				Out[1] = 1;
				Out[2] = 0;
				OneIndex--;
				for (int i = 0; i < OneIndex; ++i)
				{
					One[i] = One[i + 1];
				}
			}
			else if (TwoIndex > 0)//对子
			{
				if (TwoIndex == 2 && Two[TwoIndex - 1] >= TwoElseMax)
				{
					Out[0] = Two[TwoIndex - 1];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					return;
				}
				Out[0] = Two[0];
				Out[1] = 2;
				Out[2] = 0;
				TwoIndex--;
				for (int i = 0; i < TwoIndex; ++i)
				{
					Two[i] = Two[i + 1];
				}
			}
			else if (FourIndex > 0)//four
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
			}
			else if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
			}
			return;
		}
		//------------牌差的农民&自我放逐负责顶牌
		else
		{
			int Rounds = GetRestRound();
			//寻找标签最小的套牌	
			if (deckIndex > 0 && (deck[0][0] + deck[0][1] - 1 < 12 || deck[0][1] > 6 || Rounds < 5 || One[0] >= deck[0][0] || behindN < 6))
			{
				Out[0] = deck[0][0];
				Out[1] = deck[0][1];
				Out[2] = 1;
				deckIndex--;
				for (int i = 0; i < deckIndex; ++i)
				{
					deck[i][0] = deck[i + 1][0];
					deck[i][1] = deck[i + 1][1];
				}
				return;
			}
			else if (deckTwoIndex > 0 && (TwoIndex == 0 || deckTwo[0][0] <= Two[0]) && (deckTwo[0][0] + deckTwo[0][1] - 1 < 13 || Rounds < 4 || behindN < 6))
			{
				Out[0] = deckTwo[0][0];
				Out[1] = deckTwo[0][1];
				Out[2] = 2;
				deckTwoIndex--;
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					deckTwo[i][0] = deckTwo[i + 1][0];
					deckTwo[i][1] = deckTwo[i + 1][1];
				}
				return;
			}
			else if (deckThreeIndex > 0 && deckThree[0][0] + deckThree[0][1] - 1 <= OneElseMax && (deckThree[0][0] + deckThree[0][1] - 1 < 11 || OneIndex - deckThree[0][1] < 3 || Rounds < 5 || behindN < 6))
			{
				//还可以深入考虑
				if (ThreeIndex > 0 && Three[0]<deckThree[0][0])
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					for (int i = 0; i < ThreeIndex; i++)
					{
						Three[i] = Three[i + 1];
					}
					ThreeIndex--;
					if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
					{
						if (One[0] < Two[0])
						{
							Out[3] = One[0];
							Out[4] = 1;
							OneIndex--;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
						}
						else
						{
							Out[3] = Two[0];
							Out[4] = 2;
							TwoIndex--;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
						}
					}
					else if (OneIndex > 0)//单排
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else if (TwoIndex > 0)//对子
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
					return;
				}
				if (OneIndex > deckThree[0][1] && TwoIndex > deckThree[0][1] && One[deckThree[0][1] - 1] < 13 && Two[deckThree[0][1] - 1] < 13)
				{
					int a = 0;
					int b = 0;
					for (int i = 0; i < deckThree[0][1]; i++)
					{
						a += One[i];
						b += Two[i];
					}
					if (a <= b)
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = One[0];
						Out[4] = 1;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= deckThree[0][1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + deckThree[0][1]];
						}
					}
					else
					{
						Out[0] = deckThree[0][0];
						Out[1] = deckThree[0][1];
						Out[2] = 3;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < deckThree[0][1]; i++)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= deckThree[0][1];
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + deckThree[0][1]];
						}
					}
				}
				else if (OneIndex >= deckThree[0][1] && One[deckThree[0][1] - 1] < 14)
				{
					Out[0] = deckThree[0][0];
					Out[1] = deckThree[0][1];
					Out[2] = 3;
					Out[3] = One[0];
					Out[4] = 1;
					for (int i = 1; i < deckThree[0][1]; ++i)
					{
						Out[i + 4] = One[i];
					}
					OneIndex -= deckThree[0][1];
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + deckThree[0][1]];
					}
				}
				else
				{
					int temp = 0;
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] < 15)
						{
							temp++;
						}
					}
					if (temp == 0 || (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 13))
					{
						if (TwoIndex >= deckThree[0][1] && Two[deckThree[0][1] - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < deckThree[0][1]; ++i)
							{
								Out[i + 4] = Two[i];
							}
							TwoIndex -= deckThree[0][1];
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1]];
							}
						}
						else if (deckThree[0][1] % 2 == 0 && TwoIndex >= deckThree[0][1] / 2 && Two[deckThree[0][1] / 2 - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < deckThree[0][1] / 2; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= deckThree[0][1] / 2;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + deckThree[0][1] / 2];
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
					else
					{
						int det = (deckThree[0][1] - temp + 1) / 2;
						if (TwoIndex >= det && Two[det - 1] < 14)
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							for (int i = 1; i < det; ++i)
							{
								Out[i + 5] = Two[i];
								Out[i + 6] = Two[i];
							}
							TwoIndex -= det;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + det];
							}
							int OneTemp = deckThree[0][1] - det * 2;
							for (int i = 0; i < OneTemp; ++i)
							{
								Out[i + det * 2 + 4] = One[i];
							}
							if (OneTemp > 0)
							{
								OneIndex -= OneTemp;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
							}
							//防止777888999,3455，结果会是777888999带355
							for (int i = 3; i < 4 + Out[1]; ++i)
							{
								if (i == 4)
								{
									continue;
								}
								if (Out[i] > One[0])
								{
									int t1 = Out[i];
									Out[i] = One[0];
									One[0] = t1;
								}
							}
						}
						else
						{
							Out[0] = deckThree[0][0];
							Out[1] = deckThree[0][1];
							Out[2] = 3;
						}
					}
				}
				deckThreeIndex--;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					deckThree[i][0] = deckThree[i + 1][0];
					deckThree[i][1] = deckThree[i + 1][1];
				}
				return;
			}
			else if (ThreeIndex > 0 && Three[0] != 15 && Three[0] != 14 && (Three[0] < 11 || (OneIndex < 2 && TwoIndex < 2 || behindN < 5)))
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//单排
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//对子
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			if (ThreeIndex > 0 && OneIndex + TwoIndex < 4)
			{
				Out[0] = Three[0];
				Out[1] = 3;
				Out[2] = 0;
				for (int i = 0; i < ThreeIndex; i++)
				{
					Three[i] = Three[i + 1];
				}
				ThreeIndex--;
				if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
				{
					if (One[0] < Two[0])
					{
						Out[3] = One[0];
						Out[4] = 1;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
					}
					else
					{
						Out[3] = Two[0];
						Out[4] = 2;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
					}
				}
				else if (OneIndex > 0 && One[0] < 15)//单排
				{
					Out[3] = One[0];
					Out[4] = 1;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//对子
				{
					Out[3] = Two[0];
					Out[4] = 2;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				return;
			}
			else//没有套牌
			{
				int sum = 0;
				for (int i = 0; i < OneIndex; ++i)
				{
					if (One[i] > 7 && One[i] < 13 && sum < 3)
					{
						Out[0] = One[i];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						for (int j = i; j < OneIndex; ++j)
						{
							One[j] = One[j + 1];
						}
						return;
					}
					sum++;
				}
				sum = 0;
				for (int i = 0; i < TwoIndex; ++i)
				{
					if (Two[i] > 7 && Two[i] < 13 && sum < 2)
					{
						Out[0] = Two[i];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						for (int j = i; j < TwoIndex; ++j)
						{
							Two[j] = Two[j + 1];
						}
						return;
					}
				}
				if (OneIndex > 0 && TwoIndex > 0)//什么小出哪个
				{
					if (One[0] < Two[0])
					{
						Out[0] = One[0];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + 1];
						}
						return;
					}
					else
					{
						Out[0] = Two[0];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + 1];
						}
						return;
					}
				}
				else if (OneIndex > 0)//单排
				{
					if (OneIndex == 2 && One[OneIndex - 1] >= OneElseMax)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return;
					}
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					OneIndex--;
					for (int i = 0; i < OneIndex; ++i)
					{
						One[i] = One[i + 1];
					}
				}
				else if (TwoIndex > 0)//对子
				{
					if (TwoIndex == 2 && Two[TwoIndex - 1] >= TwoElseMax)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						TwoIndex--;
						return;
					}
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					TwoIndex--;
					for (int i = 0; i < TwoIndex; ++i)
					{
						Two[i] = Two[i + 1];
					}
				}
				else if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
				}
				else if (FourIndex > 0)//four
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
				}
				else
				{
					//没牌了？
				}
				return;
			}
		}
	}
}
/*
压牌
*/
int card::PassivePlay(int *UpperCard, int * Out, int WhoseOut)//接牌
{
	//牌的种类
	//单张，对子，三张=0；
	//顺子=1;
	//连对=2;
	//飞机=3;
	if (GetRestRound() == 1)
	{
		if (KingBoom != 0)
		{
			Out[0] = 17;
			Out[1] = 2;
			Out[2] = 4;
			KingBoom = 0;
			return 1;
		}
		else if (FourIndex > 0)
		{
			Out[0] = Four[0];
			Out[1] = 4;
			Out[2] = 4;
			return 1;
		}
		if (UpperCard[2] == 0)
		{
			if (UpperCard[1] == 1)
			{
				if (OneIndex > 0 && One[0] > UpperCard[0])
				{
					Out[0] = One[0];
					Out[1] = 1;
					Out[2] = 0;
					return 1;
				}
				else if (TwoIndex > 0 && Two[0] > UpperCard[0] && Two[0] >= OneElseMax)
				{
					Out[0] = Two[0];
					Out[1] = 1;
					Out[2] = 0;
					return 1;
				}
				else if (ThreeIndex > 0 && Three[0] > UpperCard[0] && Three[0] >= OneElseMax&&Three[0] >= TwoElseMax)
				{
					Out[0] = Three[0];
					Out[1] = 1;
					Out[2] = 0;
					return 1;
				}
			}
			else if (UpperCard[1] == 2)
			{
				if (TwoIndex > 0 && Two[0] > UpperCard[0])
				{
					Out[0] = Two[0];
					Out[1] = 2;
					Out[2] = 0;
					return 1;
				}
				else if (ThreeIndex > 0 && Three[0] > UpperCard[0] && Three[0] >= OneElseMax)
				{
					Out[0] = Three[0];
					Out[1] = 2;
					Out[2] = 0;
					return 1;
				}
			}
			else if (UpperCard[1] == 3 && ThreeIndex > 0 && Three[0] > UpperCard[0])
			{
				if (UpperCard[4] == 1 && OneIndex > 0)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					Out[3] = One[0];
					Out[4] = 1;
					return 1;
				}
				else if (UpperCard[4] == 2 && TwoIndex > 0)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					Out[3] = Two[0];
					Out[4] = 2;
					return 1;
				}
				else if (UpperCard[4] == -1)
				{
					Out[0] = Three[0];
					Out[1] = 3;
					Out[2] = 0;
					return 1;
				}
			}
		}
		else if (UpperCard[2] == 1 && deckIndex > 0 && deck[0][0] > UpperCard[0] && deck[0][1] == UpperCard[1])
		{
			Out[0] = deck[0][0];
			Out[1] = deck[0][1];
			Out[2] = 1;
			return 1;
		}
	}
	if (UpperCard[0] == 17 && UpperCard[1] == 2 && UpperCard[2] == 4)
	{
		return -1;
	}
	//****************地主*********************//
	if (IsDZ)
	{
		int MyRoundNum = GetRestRound();
		if (MyRoundNum == 2)
		{
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			if (UpperCard[1] == 4 && UpperCard[2] == 4 && UpperCard[4] == 0 && FourIndex > 0)
			{
				if (Four[FourIndex - 1] > UpperCard[0])
				{
					Out[0] = Four[FourIndex - 1];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			else if (FourIndex > 0)
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
		}
		if (UpperCard[2] == 0)
		{
			if (UpperCard[1] == 1)//出单张
			{
				if (OneIndex > 0)
				{
					if (MyRoundNum < 3 && OneIndex + TwoIndex < 3 && One[OneIndex - 1] >= OneElseMax)
					{
						if (One[OneIndex - 1] > UpperCard[0])
						{
							Out[0] = One[OneIndex - 1];
							Out[1] = 1;
							Out[2] = 0;
							OneIndex--;
							return 1;
						}				
					}
					int TempOneNM = 0;
					if(behindN < 3 || frontN < 3)
					{
						for(int i=17;i>2;i--)
						{
							if(elseCard[i] >0)
							{
								TempOneNM = i;
								break;
							}
						}
					}
					for (int i = 0; i < OneIndex; ++i)
					{
						if (One[i] > UpperCard[0] && One[i] >= TempOneNM)
						{
							Out[0] = One[i];
							Out[1] = 1;
							Out[2] = 0;
							OneIndex--;
							for (int j = i; j < OneIndex; ++j)
							{
								One[j] = One[j + 1];
							}
							return 1;
						}
					}
					for (int i = OneIndex-1; i >= 0; --i)
					{
						if (One[i] > UpperCard[0])
						{
							Out[0] = One[i];
							Out[1] = 1;
							Out[2] = 0;
							OneIndex--;
							for (int j = i; j < OneIndex; ++j)
							{
								One[j] = One[j + 1];
							}
							return 1;
						}
					}
				}
				//else 不是else关系  one中可能没有最大的牌 //拆牌
				{
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 0)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 0)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
					{
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deck[i][0] + deck[i][1] - 1;
								Out[1] = 1;
								Out[2] = 0;
								deck[i][1]--;
								return 1;
							}
						}
					}
					if (TwoIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
					{
						for (int i = 0; i < TwoIndex; ++i)
						{
							if (Two[i] >= MaxRestC)
							{
								Out[0] = Two[i];
								Out[1] = 1;
								Out[2] = 0;
								TwoIndex--;
								while(i < TwoIndex)
								{
									Two[i] = Two[i + 1];
									++i;
								}
								int IsADD = 0;
								for (int j = 0; j < OneIndex; j++)
								{
									if (One[j] > Out[0])
									{
										for (int k = OneIndex; k > j; --k)
										{
											One[k] = One[k - 1];
										}
										++OneIndex;
										One[j] = Out[0];
										IsADD = 1;
										break;
									}
								}
								if(IsADD == 0)
								{
									One[OneIndex] = Out[0];
									OneIndex++;
								}
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 1;
								Out[2] = 0;
								ThreeIndex--;
								for (int j = 0; j < TwoIndex; j++)
								{
									if (Two[j] > Out[0])
									{
										for (int k = TwoIndex; k > j; --k)
										{
											Two[k] = Two[k - 1];
										}
										++TwoIndex;
										Two[j] = Out[0];
									}
								}
								return 1;
							}
						}
					}
					if (frontN < 4 || behindN < 4)
					{
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0)
						{
							Out[0] = 16;
							Out[1] = 1;
							Out[2] = 0;
							KingBoom = 0;
							One[OneIndex] = 17;
							OneIndex++;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
				}

				return -1;
			}
			else if (UpperCard[1] == 2)
			{
				if (TwoIndex > 0)
				{
					if (MyRoundNum < 3 && OneIndex + TwoIndex < 3&& Two[TwoIndex - 1] >= TwoElseMax)
					{
						if (Two[TwoIndex - 1] > UpperCard[0])
						{
							Out[0] = Two[TwoIndex - 1];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							return 1;
						}		
					}
					int TempTwoNM = 0;
					if (behindN < 5 || frontN < 5)
					{
						for(int i=15;i>2;i--)
						{
							if(elseCard[i] >1)
							{
								TempTwoNM = i;
								break;
							}
						}
					}
					for (int i = 0; i < TwoIndex; ++i)
					{
						if (Two[i] > UpperCard[0] && Two[i] >= TempTwoNM)
						{
							Out[0] = Two[i];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							for (int j = i; j < TwoIndex; ++j)
							{
								Two[j] = Two[j + 1];
							}
							return 1;
						}
					}
					for (int i = TwoIndex - 1; i >= 0; --i)
					{
						if (Two[i] > UpperCard[0])
						{
							Out[0] = Two[i];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							for (int j = i; j < TwoIndex; ++j)
							{
								Two[j] = Two[j + 1];
							}
							return 1;
						}
					}
				}
				//还需要优化
				int MaxRestC = 0, IsHave = 0;
				for (int i = 15; i >= 3; --i)
				{
					if (myCard[i] > 1)
					{
						MaxRestC = i;
						IsHave = 1;
					}
					if (elseCard[i] > 1)
					{
						MaxRestC = i;
						break;
					}
				}
				if (UpperCard[0] >= MaxRestC)
				{
					MaxRestC = UpperCard[0] + 1;
				}
				if (deckTwoIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4))
				{
					for (int i = 0; i < deckTwoIndex; ++i)
					{
						if (deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
						{
							if (frontN < 4 || behindN < 4)
							{
								if (deckTwo[i][1] > 3)
								{
									Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
									Out[1] = 2;
									Out[2] = 0;
									deckTwo[i][1]--;
								}
								else
								{
									int temp = -1;
									for (int j = 0; j < 3; j++)
									{
										if (deckTwo[j][0] + j >= MaxRestC)
										{
											temp = i;
											break;
										}
									}
									Out[0] = deckTwo[i][0] + temp;
									Out[1] = 2;
									Out[2] = 0;
									bool flag = false;
									for (int j = 0; j < TwoIndex; ++j)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; k--)
											{
												Two[k+1] = Two[k - 1];
											}
											flag = true;
											TwoIndex += 2;
											for (int k = 0; k < 3; k++)
											{
												if (k == temp)
												{
													continue;
												}
												Two[j + k] = deckTwo[j][0] + k;
											}
											break;
										}
									}
									deckTwoIndex--;
									for (int j = i; j < deckTwoIndex; ++j)
									{
										deckTwo[j][0] = deckTwo[j + 1][0];
										deckTwo[j][1] = deckTwo[j + 1][1];
									}
								}
								return 1;
							}
							else if (deckTwo[i][1] > 3)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
							else
							{

							}
						}
					}
				}
				if (ThreeIndex > 0 && (IsHave == 1 || frontN < 4 || behindN < 4) && One[0] > 8 && OneIndex < 3)
				{
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] >= MaxRestC)
						{
							Out[0] = Three[i];
							Out[1] = 2;
							Out[2] = 0;
							ThreeIndex--;
							return 1;
						}
					}
				}
				if (frontN < 4 || behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
			}
			else//UpperCard[3] ==3
			{
				bool IsRes = false;
				bool flag = false;
				int temp = 0;
				for (int i = 0; i < ThreeIndex; ++i)
				{
					if (Three[i] > UpperCard[0])
					{
						Out[0] = Three[i];
						Out[1] = 3;
						Out[2] = 0;
						temp = i;
						IsRes = true;
						break;
					}
				}
				//飞机拆分
				if (IsRes == false)
				{
					for (int i = 0; i < deckThreeIndex; ++i)
					{
						if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
						{
							Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
							Out[1] = 3;
							Out[2] = 0;
							temp = 10 + i;
							IsRes = true;
							break;
						}
					}
				}
				//************三带 0,1,2
				if (IsRes == true)
				{
					if (UpperCard[4] == 1)
					{
						if (OneIndex > 0 && One[0] < 15)
						{
							Out[4] = 1;
							Out[3] = One[0];
							OneIndex++;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + 1];
							}
							flag = true;
						}
						else//重点优化//思考是否一定要压，拆对子还是拆顺子还是拆三，待定复杂情况//决定拆顺子，和最大的三
						{
							if (frontN < 5 || behindN < 5)
							{
								int boomtemp = -1;
								for (int i = 15; i > 2; i--)
								{
									if (elseCard[i] > 3)
									{
										boomtemp = i;
										break;
									}
								}
								if (boomtemp > 0 && FourIndex > 0)
								{
									Out[0] = Four[0];
									Out[1] = 4;
									Out[2] = 4;
									Out[4] = 0;
									Out[3] = 0;
									FourIndex--;
									for (int i = 0; i < FourIndex; ++i)
									{
										Four[i] = Four[i + 1];
									}
									return 1;
								}
								else if (KingBoom > 0 && OneIndex < 3)
								{
									Out[0] = 17;
									Out[1] = 2;
									Out[2] = 4;
									KingBoom = 0;
									return 1;
								}
								else if (FourIndex > 0)
								{
									Out[0] = Four[0];
									Out[1] = 4;
									Out[2] = 4;
									Out[4] = 0;
									Out[3] = 0;
									FourIndex--;
									for (int i = 0; i < FourIndex; ++i)
									{
										Four[i] = Four[i + 1];
									}
									return 1;
								}
								else
								{
									if (deckIndex > 0)
									{
										for (int i = 0; i < deckIndex; ++i)
										{
											if (deck[i][1] > 5)
											{
												Out[3] = deck[i][0];
												Out[4] = 1;
												deck[i][0]++;
												deck[i][1]--;
												flag = true;
												break;
											}
										}
									}
									else if (TwoIndex > 1)
									{
										Out[3] = Two[TwoIndex - 2];
										Out[4] = 1;
										Two[TwoIndex - 2] = Two[TwoIndex - 1];
										bool fg = false;
										flag = true;
										for (int i = 0; i < OneIndex; ++i)
										{
											if (One[i] > Out[3])
											{
												for (int j = OneIndex; j > i; j--)
												{
													One[j] = One[j - 1];
												}
												OneIndex++;
												One[i] = Out[3];
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											One[OneIndex] = Out[3];
											OneIndex++;
										}
									}
									else if (TwoIndex == 1)
									{
										Out[3] = Two[TwoIndex - 1];
										Out[4] = 1;
										TwoIndex--;
										bool fg = false;
										flag = true;
										for (int i = 0; i < OneIndex; ++i)
										{
											if (One[i] > Out[3])
											{
												for (int j = OneIndex; j > i; j--)
												{
													One[j] = One[j - 1];
												}
												OneIndex++;
												One[i] = Out[3];
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											One[OneIndex] = Out[3];
											OneIndex++;
										}
									}
									else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
									{
										Out[3] = Three[ThreeIndex - 2];
										Out[4] = 1;
										Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
										ThreeIndex--;
										flag = true;
										bool fg = false;
										for (int i = 0; i < TwoIndex; ++i)
										{
											if (Two[i] > Out[3])
											{
												for (int j = TwoIndex; j > i; j--)
												{
													Two[j] = Two[j - 1];
												}
												Two[i] = Out[3];
												TwoIndex++;
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											Two[TwoIndex] = Out[3];
											TwoIndex++;
										}
									}
									else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp)||(ThreeIndex > 1 && ThreeIndex - 2 != temp))
									{
										Out[3] = Three[ThreeIndex - 1];
										Out[4] = 1;
										ThreeIndex--;
										flag = true;
										bool fg = false;
										for (int i = 0; i < TwoIndex; ++i)
										{
											if (Two[i] > Out[3])
											{
												for (int j = TwoIndex; j > i; j--)
												{
													Two[j] = Two[j - 1];
												}
												Two[i] = Out[3];
												TwoIndex++;
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											Two[TwoIndex] = Out[3];
											TwoIndex++;
										}
									}
									else
									{

									}
								}
							}
							else if (deckIndex > 0)
							{
								for (int i = 0; i < deckIndex; ++i)
								{
									if (deck[i][1] > 5)
									{
										Out[3] = deck[i][0];
										Out[4] = 1;
										deck[i][0]++;
										deck[i][1]--;
										flag = true;
										break;
									}
								}
							}
							else if (TwoIndex > 1)
							{
								Out[3] = Two[TwoIndex - 2];
								Out[4] = 1;
								Two[TwoIndex - 2] = Two[TwoIndex - 1];
								bool fg = false;
								flag = true;
								for (int i = 0; i < OneIndex; ++i)
								{
									if (One[i] > Out[3])
									{
										for (int j = OneIndex; j > i; j--)
										{
											One[j] = One[j - 1];
										}
										OneIndex++;
										One[i] = Out[3];
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									One[OneIndex] = Out[3];
									OneIndex++;
								}
							}
							else if (TwoIndex == 1)
							{
								Out[3] = Two[TwoIndex - 1];
								Out[4] = 1;
								TwoIndex--;
								bool fg = false;
								flag = true;
								for (int i = 0; i < OneIndex; ++i)
								{
									if (One[i] > Out[3])
									{
										for (int j = OneIndex; j > i; j--)
										{
											One[j] = One[j - 1];
										}
										OneIndex++;
										One[i] = Out[3];
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									One[OneIndex] = Out[3];
									OneIndex++;
								}
							}
							else
							{

							}
						}
					}
					else if (UpperCard[4] == 2)
					{
						if (TwoIndex > 0 && Two[0] < 13)
						{
							Out[4] = 2;
							Out[3] = Two[0];
							TwoIndex++;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + 1];
							}
							flag = true;
						}
						else
						{
							if (deckTwoIndex > 0)
							{
								for (int i = 0; i < deckTwoIndex; ++i)
								{
									if (deckTwo[i][1] > 3)
									{
										Out[3] = deckTwo[i][0];
										Out[4] = 2;
										flag = true;
										deckTwo[i][0]++;
										deckTwo[i][1]--;
										break;
									}
									else if (deckTwo[i][0]+deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
									{
										Out[3] = deckTwo[i][0];
										Out[4] = 2;
										flag = true;
										bool fg = false;
										for (int j = 0; j < TwoIndex; ++j)
										{
											if (Two[j] > Out[3])
											{
												for (int k = TwoIndex; k > j; --k)
												{
													Two[k + 1] = Two[k - 1];
												}
												fg = true;
												Two[j] = deckTwo[i][0] + 1;
												Two[j + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
												break;
											}
										}
										if (!fg)
										{
											Two[TwoIndex] = deckTwo[i][0] + 1;
											Two[TwoIndex + 1] = deckTwo[i][0] + 2;
											TwoIndex += 2;
										}
									}
									else
									{

									}
								}
							}
						}
					}
					else
					{
						flag = true;
					}
				}		
				if (IsRes && flag)
				{
					if (temp < 10)
					{
						for (int i = temp; i < ThreeIndex; i++)
						{
							Three[i] = Three[i + 1];
						}
						ThreeIndex--;
					}
					else
					{
						temp -= 10;
						if (deckThree[temp][1] > 2)
						{
							deckThree[temp][1]--;
						}
						else
						{
							bool fg = false;
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] > deckThree[temp][0])
								{
									for (int j = ThreeIndex; j > i; --j)
									{
										Three[j] = Three[j - 1];
									}
									Three[i] = deckThree[temp][0];
									ThreeIndex++;
									fg = true;
									break;
								}
							}
							if (!fg)
							{
								Three[ThreeIndex] = deckThree[temp][0];
								ThreeIndex++;
							}
							for (int i = temp; i < deckThreeIndex; ++i)
							{
								deckThree[i][1] = deckThree[i + 1][1];
								deckThree[i][0] = deckThree[i + 1][0];
							}
						}
					}
					return 1;
				}
				if (frontN < 4 || behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			return -1;
		}
		else if (UpperCard[2] == 1)
		{
			for (int i = 0; i < deckIndex; ++i)
			{
				if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
				{
					Out[0] = deck[i][0];
					Out[1] = deck[i][1];
					Out[2] = 1;
					deckIndex--;
					for (int j = i; j < deckIndex; ++j)
					{
						deck[j][0] = deck[j + 1][0];
						deck[j][1] = deck[j + 1][1];
					}
					return 1;
				}
			}
			for (int i = 0; i < deckIndex; ++i)
			{
				if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
				{
					int restOne = deck[i][0] + deck[i][1] - 1;
					for (int k = OneIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (One[k - 1] > restOne)
						{
							One[k] = One[k - 1];
						}
						else
						{
							One[k] = restOne;
							break;
						}
					}
					OneIndex++;
					Out[0] = deck[i][0];
					Out[1] = deck[i][1] - 1;
					Out[2] = 1;
					deckIndex--;
					for (int j = i; j < deckIndex; ++j)
					{
						deck[j][0] = deck[j + 1][0];
						deck[j][1] = deck[j + 1][1];
					}
					return 1;
				}
				else if(deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
				{
					int restOne = deck[i][0];
					for (int k = OneIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (One[k - 1] > restOne)
						{
							One[k] = One[k - 1];
						}
						else
						{
							One[k] = restOne;
							break;
						}
					}
					OneIndex++;
					Out[0] = deck[i][0] + 1;
					Out[1] = deck[i][1] - 1;
					Out[2] = 1;
					deckIndex--;
					for (int j = i; j < deckIndex; ++j)
					{
						deck[j][0] = deck[j + 1][0];
						deck[j][1] = deck[j + 1][1];
					}
					return 1;
				}
			}
			if (frontN < 4 || behindN < 4)
			{
				int boomtemp = -1;
				for (int i = 15; i > 2; i--)
				{
					if (elseCard[i] > 3)
					{
						boomtemp = i;
						break;
					}
				}
				if (boomtemp > 0 && FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
				else if (KingBoom > 0 && OneIndex < 3)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return 1;
				}
				else if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
		}
		else if (UpperCard[2] == 2)
		{
			for (int i = 0; i < deckTwoIndex; ++i)
			{
				if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
				{
					Out[0] = deckTwo[i][0];
					Out[1] = deckTwo[i][1];
					Out[2] = 2;
					deckTwoIndex--;
					for (int j = i; j < deckTwoIndex; ++j)
					{
						deckTwo[j][0] = deckTwo[j + 1][0];
						deckTwo[j][1] = deckTwo[j + 1][1];
					}
					return 1;
				}
			}
			for (int i = 0; i < deckTwoIndex; ++i)
			{
				if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
				{
					int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
					for (int k = TwoIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (Two[k - 1] > restTwo)
						{
							Two[k] = Two[k - 1];
						}
						else
						{
							Two[k] = restTwo;
							break;
						}
					}
					TwoIndex++;
					Out[0] = deckTwo[i][0];
					Out[1] = deckTwo[i][1] - 1;
					Out[2] = 2;
					deckTwoIndex--;
					for (int j = i; j < deckTwoIndex; ++j)
					{
						deckTwo[j][0] = deckTwo[j + 1][0];
						deckTwo[j][1] = deckTwo[j + 1][1];
					}
					return 1;
				}
				else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
				{
					int restTwo = deckTwo[i][0];
					for (int k = TwoIndex; k > 0; --k)
					{
						//One[k-1] == restOne
						if (Two[k - 1] > restTwo)
						{
							Two[k] = Two[k - 1];
						}
						else
						{
							Two[k] = restTwo;
							break;
						}
					}
					TwoIndex++;
					Out[0] = deckTwo[i][0] + 1;
					Out[1] = deckTwo[i][1] - 1;
					Out[2] = 2;
					deckTwoIndex--;
					for (int j = i; j < deckTwoIndex; ++j)
					{
						deckTwo[j][0] = deckTwo[j + 1][0];
						deckTwo[j][1] = deckTwo[j + 1][1];
					}
					return 1;
				}
			}		
			if (frontN < 4 || behindN < 4)
			{
				int boomtemp = -1;
				for (int i = 15; i > 2; i--)
				{
					if (elseCard[i] > 3)
					{
						boomtemp = i;
						break;
					}
				}
				if (boomtemp > 0 && FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
				else if (KingBoom > 0 && OneIndex < 3)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return 1;
				}
				else if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		else if (UpperCard[2] == 3)
		{
			bool IsRes = false;
			int chai = 0;
			int chaiThree;
			for (int i = 0; i < deckThreeIndex; ++i)
			{
				//未考虑 我的长度 长于目标的情况//因为是地主，飞机一局出现两次已经很多了，暂时不考虑三次，所以能压直接拆；
				if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
				{
					Out[0] = deckThree[i][0];
					Out[1] = deckThree[i][1];
					Out[2] = 3;
					deckThreeIndex--;
					if (deckThree[i][1] - UpperCard[1] >= 2)
					{
						chai = 1;
						deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
						deckThree[i][1] = deckThree[i][1] - UpperCard[1];
					}
					else
					{
						if (deckThree[i][1] - UpperCard[1] > 0)
						{
							chai = 2;
							for (int j = 0; j < ThreeIndex; j++)
							{
								if (Three[j] > Out[0])
								{
									for (int k = ThreeIndex; k > j; --k)
									{
										Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
									}
									ThreeIndex += deckThree[i][1] - UpperCard[1];
									for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
									{
										Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
									}
									chaiThree = j;
									break;
								}
							}
						}
						for (int j = i; j < deckThreeIndex; ++j)
						{
							deckThree[j][0] = deckThree[j + 1][0];
							deckThree[j][1] = deckThree[j + 1][1];
						}
					}
					IsRes = true;
					break;
				}
			}
			if (IsRes == true)
			{
				if (UpperCard[4] == 2)//带对子
				{
					int temp = UpperCard[1];
					//多张，所以长度是UpperCard[1]
					if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < temp; ++i)
						{
							Out[4 + i] = Two[i];
						}
						TwoIndex -= temp;
						for (int i = 0; i < TwoIndex; ++i)
						{
							Two[i] = Two[i + temp];
						}
						return 1;
					}
					else if (deckTwoIndex > 0)
					{
						for (int k = TwoIndex; k > 0; --k)
						{
							if (Two[k - 1] > deckTwo[0][0])
							{
								Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
							}
							else
							{
								for (int j = 0; j < deckTwo[0][1]; j++)
								{
									Two[k + j] = deckTwo[0][0] + j;
								}
								break;
							}
						}
						TwoIndex += deckTwo[0][1];
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							deckTwo[i][1] = deckTwo[i + 1][1];
							deckTwo[i][0] = deckTwo[i + 1][0];
						}
						deckTwoIndex--;
						Out[3] = Two[0];
						Out[4] = 2;
						for (int i = 1; i < Out[1]; i++)
						{
							Out[4 + i] = Two[i + 1];
						}
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + Out[1]];
						}
						TwoIndex -= Out[1];
						return 1;
					}
					else
					{
						return -1;
					}
				}
				else if (UpperCard[4] == 1)
				{
					int temp = UpperCard[1];
					//
					if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
					{
						Out[3] = One[0];
						Out[4] = 2;
						for (int i = 1; i < temp; ++i)
						{
							Out[4 + i] = One[i];
						}
						OneIndex -= temp;
						for (int i = 0; i < OneIndex; ++i)
						{
							One[i] = One[i + temp];
						}
						return 1;
					}
					else
					{

					}
				}
			}	
			if (frontN < 4 || behindN < 4)
			{
				int boomtemp = -1;
				for (int i = 15; i > 2; i--)
				{
					if (elseCard[i] > 3)
					{
						boomtemp = i;
						break;
					}
				}
				if (boomtemp > 0 && FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
				else if (KingBoom > 0 )
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					KingBoom = 0;
					return 1;
				}
				else if (FourIndex > 0)
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		else if (UpperCard[2] == 4)//  四代2 //可优化，目前直接炸//都四带二了，说明农名在蛢命，或者必赢了，所以直接炸；
		{
			if (UpperCard[0] == 17)
			{
				return -1;
			}
			bool boom = false;
			bool ok = false;
			bool BB = false;
			if (FourIndex > 0)
			{
				boom = true;
			}
			if (UpperCard[4] == 1 && boom == true)
			{
				if (OneIndex > 1 && One[1] < 14)
				{
					Out[3] = One[0];
					Out[4] = 1;
					Out[5] = One[1];
					for (int i = 0; i < OneIndex; i++)
					{
						One[i] = One[i + 2];
					}
					OneIndex -= 2;
					ok = true;
				}
				else if (OneIndex == 1 && One[0] < 14)
				{
					if (TwoIndex > 0 && Two[0] < 14)
					{
						if (One[0] > Two[0])
						{
							Out[3] = Two[0];
							Out[4] = 1;
							Out[5] = Two[0];
							TwoIndex--;
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + 1];
							}
							ok = true;
						}
						else
						{
							Out[3] = One[0];
							Out[4] = 1;
							Out[5] = Two[0];
							One[0] = Two[0];
							TwoIndex--;
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + 1];
							}
							ok = true;
						}
					}
				}
				else if (TwoIndex > 0 && Two[0] < 14)
				{
					Out[3] = Two[0];
					Out[4] = 1;
					Out[5] = Two[0];
					TwoIndex--;
					for (int i = 0; i < TwoIndex; i++)
					{
						Two[i] = Two[i + 1];
					}
					ok = true;
				}
				else
				{

				}
			}
			else if (UpperCard[4] == 2 && boom == true)
			{
				if (TwoIndex > 1 && Two[1] < 14)
				{
					Out[3] = Two[0];
					Out[4] = 2;
					Out[5] = Two[1];
					TwoIndex -= 2;
					for (int i = 0; i < TwoIndex; i++)
					{
						Two[i] = Two[i + 2];
					}
					ok = true;
				}
			}
			else
			{
				BB = true;
			}
			if (ok == true || (BB == true && KingBoom == 0))
			{
				for (int i = 0; i < FourIndex; i++)
				{
					if (Four[i] > UpperCard[0])
					{
						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int j = i; j < FourIndex; ++j)
						{
							Four[j] = Four[j + 1];
						}
					}
				}
				return 1;
			}
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				Out[3] = 0;
				Out[4] = 0;
				Out[5] = 0;
				KingBoom = 0;
				return 1;
			}
			if (FourIndex > 0 && UpperCard[4] > 0)
			{
				for (int i = 0; i < FourIndex; i++)
				{

					Out[0] = Four[i];
					Out[1] = 4;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					FourIndex--;
					for (int j = i; j < FourIndex; j++)
					{
						Four[j] = Four[j + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		else
		{
			return -1;
		}
	}
	//*******************农民*******************//
	else
	{
		// behindN == 1 && DZIndex == 1  后家地主报单
		//if (behindN == 1 && DZIndex == -1)//朋友农民报单，切地主不报单
	//	cout << 1 << endl;
	//	cout << UpperCard[0] << " " << UpperCard[1] << " " << UpperCard[2] << endl;
		int MyRoundNum = GetRestRound();
		if (MyRoundNum == 1 && (FourIndex > 0 || KingBoom != 0))
		{
			if (KingBoom != 0)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			else if (FourIndex > 0)
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				return 1;
			}
		}
		if (MyRoundNum == 2)
		{
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			if (UpperCard[1] == 4 && UpperCard[2] == 4 && UpperCard[4] == 0 && FourIndex > 0)
			{
				if (Four[FourIndex - 1] > UpperCard[0])
				{
					Out[0] = Four[FourIndex - 1];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			else if (FourIndex > 0)
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
		}
		if ((behindN == 1 && DZIndex == -1) || (frontN == 1 && DZIndex == 2 && behindN > 1))
		{
			if (WhoseOut == 1)
			{
				return -1;
			}
			//地主打的
			if (UpperCard[2] == 0)
			{
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0 && One[OneIndex - 1] > UpperCard[0])
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					else if (FourIndex > 0)
					{
						bool IsMaxBoom = true;
						int temp = Four[FourIndex - 1];
						for (int i = temp + 1; i < 16; ++i)
						{
							if (elseCard[i] == 4)
							{
								IsMaxBoom = false;
								break;
							}
						}
						if (IsMaxBoom)
						{
							if (UpperCard[2] == 4 && UpperCard[0] > temp)
							{
								return -1;
							}
							Out[0] = temp;
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							return 1;
						}
						else
						{
							//不炸
						}
					}
					else if (TwoIndex > 0 && Two[TwoIndex - 1] > UpperCard[0])
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						TwoIndex--;
						return 1;
					}
					else if (ThreeIndex > 0 && Three[ThreeIndex - 1] > UpperCard[0])
					{
						Out[0] = Three[ThreeIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						ThreeIndex--;
						return 1;
					}
					else if (deck[0][0] + deck[0][1] - 1 > UpperCard[0] && deck[0][1] > 5)
					{
						Out[0] = deck[0][0] + deck[0][1] - 1;
						Out[1] = 1;
						Out[2] = 0;
						deck[0][1]--;
						return 1;
					}

				}
				else if (UpperCard[1] == 2)
				{
					for (int i = 15; i > 3; i--)
					{
						if (i > UpperCard[0] &&  myCard[i] > 1 && myCard[i] < 4)
						{
							Out[0] = i;
							Out[1] = 2;
							Out[2] = 0;
							return 1;
						}
					}
				}
				else//UpperCard[3] ==3
				{
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = ThreeIndex - 1; i >= 0; --i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//飞机拆分
					if (IsRes == false)
					{
						for (int i = deckThreeIndex - 1; i >= 0; --i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************三带 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0 && One[0] < 13)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//重点优化//思考是否一定要压，拆对子还是拆顺子还是拆三，待定复杂情况//决定拆顺子，和最大的三
							{
								if (WhoseOut == -1 && frontN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (OneIndex > 0 && One[0] < 15)
								{
									Out[4] = 1;
									Out[3] = One[0];
									OneIndex++;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + 1];
									}
									flag = true;
								}
								else if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (WhoseOut == -1 && behindN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 1)
			{
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
					else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0];
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0] + 1;
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 3)
			{
				if (WhoseOut == 1 && ((DZIndex == -1) || (DZIndex == 2 && (behindN > 8 || UpperCard[0] > 9 || UpperCard[1] > 2))))
				{
					return -1;
				}
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//带对子
					{
						int temp = UpperCard[1];
						//多张，所以长度是UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{
							return -1;
						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
				if (DZIndex == 2 && behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}

			}
			else if (UpperCard[2] == 4)//  四代2 //可优化，目前直接炸//都四带二了，说明农名在蛢命，或者必赢了，所以直接炸；
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				if (ok == true)
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else
			{
				return -1;
			}
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			if (FourIndex > 0)
			{
				bool IsMaxBoom = true;
				int temp = Four[FourIndex - 1];
				for (int i = temp + 1; i < 16; ++i)
				{
					if (elseCard[i] == 4)
					{
						IsMaxBoom = false;
						break;
					}
				}
				if (IsMaxBoom)
				{
					if (UpperCard[2] == 4 && UpperCard[0] > temp)
					{
						return -1;
					}
					Out[0] = temp;
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					return 1;
				}
				else
				{
					//不炸
				}
			}
			return -1;
		}
		//----------------------地主报单
		else if ((frontN == 1 && DZIndex == -1) || (DZIndex == 2 && behindN == 1))//地主上家
		{
			int dzMaxOne = OneElseMax;
			if (WhoseOut == 1 && (UpperCard[2] > 0 || UpperCard[1] > 1 || (UpperCard[0] >= dzMaxOne) || DZIndex == -1))
			{
				return -1;
			}
			//能跑
			int UnSafeNum = 0;
			for (int i = 0; i < OneIndex; ++i)
			{
				if (One[i] < dzMaxOne)
				{
					UnSafeNum++;
				}
			}
			UnSafeNum -= ThreeIndex;
			int BigThanDZ = 0;
			for (int i = 0; i < deckThreeIndex; ++i)
			{
				UnSafeNum -= deckThree[i][1];
			}
			if (KingBoom == 1)
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			else if (FourIndex > 0 && (UnSafeNum < 2))//优化
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
			//if (WhoseOut == -1)
			{
				//必接  地主出的单牌
				if (UpperCard[2] == 0 && UpperCard[1] == 1)
				{
					if (UpperCard[0] >= dzMaxOne)
					{
						dzMaxOne = UpperCard[0] + 1;
					}
					if (OneIndex > 0 && One[OneIndex - 1] >= dzMaxOne)
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					if (TwoIndex > 0 && Two[TwoIndex - 1] >= dzMaxOne)
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						One[OneIndex] = Two[TwoIndex - 1];
						OneIndex++;
						TwoIndex--;
						return 1;
					}
					if (deckIndex > 0)
					{
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= dzMaxOne)
							{
								Out[0] = deck[i][0] + deck[i][1] - 1;
								Out[1] = 1;
								Out[2] = 0;
								deck[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && Two[TwoIndex - 1] >= dzMaxOne)
					{
						Out[0] = Three[ThreeIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						Two[TwoIndex] = Three[ThreeIndex - 1];
						TwoIndex++;
						ThreeIndex--;
						return 1;
					}
					//else 不是else关系  one中可能没有最大的牌 //拆牌
					if (OneIndex > 0 && One[OneIndex - 1] > UpperCard[0])
					{
						OneIndex--;
						Out[0] = One[OneIndex];
						Out[1] = 1;
						Out[2] = 0;
						return 1;
					}	
				}
				else//套牌
				{
					if (UpperCard[2] == 0)
					{
						
						if (deckThreeIndex > 0)//把飞机拆了，三带都压不了
						{
							for (int i = 0; i < deckThreeIndex; ++i)
							{
								bool flag = false;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > deckThree[i][0])
									{
										flag = true;
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][0];
										for (int k = 0; k < deckThree[i][1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + k;
										}
									}
								}
								if (flag == false)
								{
									for (int k = 0; k < deckThree[i][1]; ++k)
									{
										Three[ThreeIndex + k] = deckThree[i][0] + k;
									}
									ThreeIndex += deckThree[i][1];
								}
							}
						}
						if (UpperCard[1] == 2)
						{
							if (TwoIndex > 0)
							{
								if (Two[TwoIndex - 1] > UpperCard[0])
								{
									Out[0] = Two[TwoIndex - 1];
									Out[1] = 2;
									Out[2] = 0;
									TwoIndex--;
									return 1;
								}
							}
							//gai
							if (deckTwoIndex > 0)
							{
								for (int i = 0; i < deckTwoIndex; ++i)
								{
									if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0])
									{
										Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
										Out[1] = 2;
										Out[2] = 0;
										deckTwo[i][1]--;
										return 1;
									}
									else if (deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0])
									{
										Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
										Out[1] = 2;
										Out[2] = 0;
										Two[TwoIndex] = Out[0] - 2;
										TwoIndex++;
										Two[TwoIndex] = Out[0] - 1;
										TwoIndex++;
										for (int j = i; j < deckTwoIndex; ++i)
										{
											deckTwo[j][0] = deckTwo[j + 1][0];
											deckTwo[j][1] = deckTwo[j + 1][1];
										}
										return 1;
									}
								}
							}
							if (ThreeIndex > 0)
							{
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > UpperCard[0] && (UnSafeNum <= ThreeIndex || Three[i] > dzMaxOne))
									{
										Out[0] = Three[i];
										Out[1] = 2;
										Out[2] = 0;
										ThreeIndex--;
										return 1;
									}
								}
							}
						}
						else//UpperCard[3] ==3
						{
							bool IsRes = false;
							bool flag = false;
							int temp = 0;
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] > UpperCard[0])
								{
									Out[0] = Three[i];
									Out[1] = 3;
									Out[2] = 0;
									temp = i;
									IsRes = true;
									break;
								}
							}
							//飞机拆分
							if (IsRes == false)
							{
								for (int i = 0; i < deckThreeIndex; ++i)
								{
									if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
									{
										Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
										Out[1] = 3;
										Out[2] = 0;
										temp = 10 + i;
										IsRes = true;
										break;
									}
								}
							}
							//************三带 0,1,2
							if (IsRes == true)
							{
								if (UpperCard[4] == 1)
								{
									if (OneIndex > 0 && One[0] < 13)
									{
										Out[4] = 1;
										Out[3] = One[0];
										OneIndex++;
										for (int i = 0; i < OneIndex; ++i)
										{
											One[i] = One[i + 1];
										}
										flag = true;
									}
									else//重点优化//思考是否一定要压，拆对子还是拆顺子还是拆三，待定复杂情况//决定拆顺子，和最大的三
									{
										if (WhoseOut == -1 && frontN < 5)
										{
											int boomtemp = -1;
											for (int i = 15; i > 2; i--)
											{
												if (elseCard[i] > 3)
												{
													boomtemp = i;
													break;
												}
											}
											if (boomtemp > 0 && FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else if (KingBoom > 0 && OneIndex < 3)
											{
												Out[0] = 17;
												Out[1] = 2;
												Out[2] = 4;
												KingBoom = 0;
												return 1;
											}
											else if (FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else
											{
												if (deckIndex > 0)
												{
													for (int i = 0; i < deckIndex; ++i)
													{
														if (deck[i][1] > 5)
														{
															Out[3] = deck[i][0];
															Out[4] = 1;
															deck[i][0]++;
															deck[i][1]--;
															flag = true;
															break;
														}
													}
												}
												else if (TwoIndex > 1)
												{
													Out[3] = Two[TwoIndex - 2];
													Out[4] = 1;
													Two[TwoIndex - 2] = Two[TwoIndex - 1];
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (TwoIndex == 1)
												{
													Out[3] = Two[TwoIndex - 1];
													Out[4] = 1;
													TwoIndex--;
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
												{
													Out[3] = Three[ThreeIndex - 2];
													Out[4] = 1;
													Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
												{
													Out[3] = Three[ThreeIndex - 1];
													Out[4] = 1;
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else
												{

												}
											}
										}
										else if (OneIndex > 0 && One[0] < 15)
										{
											Out[4] = 1;
											Out[3] = One[0];
											OneIndex++;
											for (int i = 0; i < OneIndex; ++i)
											{
												One[i] = One[i + 1];
											}
											flag = true;
										}
										else if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (UpperCard[4] == 2)
								{
									if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
									{
										Out[4] = 2;
										Out[3] = Two[0];
										TwoIndex++;
										for (int i = 0; i < TwoIndex; ++i)
										{
											Two[i] = Two[i + 1];
										}
										flag = true;
									}
									else
									{
										if (WhoseOut == -1 && behindN < 5)
										{
											int boomtemp = -1;
											for (int i = 15; i > 2; i--)
											{
												if (elseCard[i] > 3)
												{
													boomtemp = i;
													break;
												}
											}
											if (boomtemp > 0 && FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else if (KingBoom > 0 && OneIndex < 3)
											{
												Out[0] = 17;
												Out[1] = 2;
												Out[2] = 4;
												KingBoom = 0;
												return 1;
											}
											else if (FourIndex > 0)
											{
												Out[0] = Four[0];
												Out[1] = 4;
												Out[2] = 4;
												Out[4] = 0;
												Out[3] = 0;
												FourIndex--;
												for (int i = 0; i < FourIndex; ++i)
												{
													Four[i] = Four[i + 1];
												}
												return 1;
											}
											else
											{
												if (deckIndex > 0)
												{
													for (int i = 0; i < deckIndex; ++i)
													{
														if (deck[i][1] > 5)
														{
															Out[3] = deck[i][0];
															Out[4] = 1;
															deck[i][0]++;
															deck[i][1]--;
															flag = true;
															break;
														}
													}
												}
												else if (TwoIndex > 1)
												{
													Out[3] = Two[TwoIndex - 2];
													Out[4] = 1;
													Two[TwoIndex - 2] = Two[TwoIndex - 1];
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (TwoIndex == 1)
												{
													Out[3] = Two[TwoIndex - 1];
													Out[4] = 1;
													TwoIndex--;
													bool fg = false;
													flag = true;
													for (int i = 0; i < OneIndex; ++i)
													{
														if (One[i] > Out[3])
														{
															for (int j = OneIndex; j > i; j--)
															{
																One[j] = One[j - 1];
															}
															OneIndex++;
															One[i] = Out[3];
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														One[OneIndex] = Out[3];
														OneIndex++;
													}
												}
												else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
												{
													Out[3] = Three[ThreeIndex - 2];
													Out[4] = 1;
													Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
												{
													Out[3] = Three[ThreeIndex - 1];
													Out[4] = 1;
													ThreeIndex--;
													flag = true;
													bool fg = false;
													for (int i = 0; i < TwoIndex; ++i)
													{
														if (Two[i] > Out[3])
														{
															for (int j = TwoIndex; j > i; j--)
															{
																Two[j] = Two[j - 1];
															}
															Two[i] = Out[3];
															TwoIndex++;
															fg = true;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = Out[3];
														TwoIndex++;
													}
												}
												else
												{

												}
											}
										}
										else if (WhoseOut == 1)
										{
											return -1;
										}
										else if (deckTwoIndex > 0)
										{
											for (int i = 0; i < deckTwoIndex; ++i)
											{
												if (deckTwo[i][1] > 3)
												{
													Out[3] = deckTwo[i][0];
													Out[4] = 2;
													flag = true;
													deckTwo[i][0]++;
													deckTwo[i][1]--;
													break;
												}
												else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
												{
													Out[3] = deckTwo[i][0];
													Out[4] = 2;
													flag = true;
													bool fg = false;
													for (int j = 0; j < TwoIndex; ++j)
													{
														if (Two[j] > Out[3])
														{
															for (int k = TwoIndex; k > j; --k)
															{
																Two[k + 1] = Two[k - 1];
															}
															fg = true;
															Two[j] = deckTwo[i][0] + 1;
															Two[j + 1] = deckTwo[i][0] + 2;
															TwoIndex += 2;
															break;
														}
													}
													if (!fg)
													{
														Two[TwoIndex] = deckTwo[i][0] + 1;
														Two[TwoIndex + 1] = deckTwo[i][0] + 2;
														TwoIndex += 2;
													}
												}
												else
												{

												}
											}
										}
									}
								}
								else
								{
									flag = true;
								}
							}
							if (IsRes && flag)
							{
								if (temp < 10)
								{
									for (int i = temp; i < ThreeIndex; i++)
									{
										Three[i] = Three[i + 1];
									}
									ThreeIndex--;
								}
								else
								{
									temp -= 10;
									if (deckThree[temp][1] > 2)
									{
										deckThree[temp][1]--;
									}
									else
									{
										bool fg = false;
										for (int i = 0; i < ThreeIndex; ++i)
										{
											if (Three[i] > deckThree[temp][0])
											{
												for (int j = ThreeIndex; j > i; --j)
												{
													Three[j] = Three[j - 1];
												}
												Three[i] = deckThree[temp][0];
												ThreeIndex++;
												fg = true;
												break;
											}
										}
										if (!fg)
										{
											Three[ThreeIndex] = deckThree[temp][0];
											ThreeIndex++;
										}
										for (int i = temp; i < deckThreeIndex; ++i)
										{
											deckThree[i][1] = deckThree[i + 1][1];
											deckThree[i][0] = deckThree[i + 1][0];
										}
									}
								}
								return 1;
							}
						}
					}
					else if (UpperCard[2] == 1)
					{
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
							{
								Out[0] = deck[i][0];
								Out[1] = deck[i][1];
								Out[2] = 1;
								deckIndex--;
								for (int j = i; j < deckIndex; ++j)
								{
									deck[j][0] = deck[j + 1][0];
									deck[j][1] = deck[j + 1][1];
								}
								return 1;
							}
						}
						for (int i = 0; i < deckIndex; ++i)
						{
							if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
							{
								int restOne = deck[i][0] + deck[i][1] - 1;
								for (int k = OneIndex; k > 0; --k)
								{
									//One[k-1] == restOne
									if (One[k - 1] > restOne)
									{
										One[k] = One[k - 1];
									}
									else
									{
										One[k] = restOne;
										break;
									}
								}
								OneIndex++;
								Out[0] = deck[i][0];
								Out[1] = deck[i][1] - 1;
								Out[2] = 1;
								deckIndex--;
								for (int j = i; j < deckIndex; ++j)
								{
									deck[j][0] = deck[j + 1][0];
									deck[j][1] = deck[j + 1][1];
								}
								return 1;
							}
							else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
							{
								int restOne = deck[i][0];
								for (int k = OneIndex; k > 0; --k)
								{
									//One[k-1] == restOne
									if (One[k - 1] > restOne)
									{
										One[k] = One[k - 1];
									}
									else
									{
										One[k] = restOne;
										break;
									}
								}
								OneIndex++;
								Out[0] = deck[i][0] + 1;
								Out[1] = deck[i][1] - 1;
								Out[2] = 1;
								deckIndex--;
								for (int j = i; j < deckIndex; ++j)
								{
									deck[j][0] = deck[j + 1][0];
									deck[j][1] = deck[j + 1][1];
								}
								return 1;
							}
						}
					}
					else if (UpperCard[2] == 2)
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
							{
								Out[0] = deckTwo[i][0];
								Out[1] = deckTwo[i][1];
								Out[2] = 2;
								deckTwoIndex--;
								for (int j = i; j < deckTwoIndex; ++j)
								{
									deckTwo[j][0] = deckTwo[j + 1][0];
									deckTwo[j][1] = deckTwo[j + 1][1];
								}
								return 1;
							}
						}
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0] + UpperCard[1] - 1 && deckTwo[i][1] > UpperCard[1])
							{
								int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
								for (int j = 0; j < deckTwo[i][1] - UpperCard[1]; ++j)
								{
									Two[TwoIndex] = deckTwo[i][0] + j;
									TwoIndex++;
								}
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - UpperCard[1];
								Out[1] = UpperCard[1];
								Out[2] = 2;
								deckTwoIndex--;
								for (int j = i; j < deckTwoIndex; ++j)
								{
									deckTwo[j][0] = deckTwo[j + 1][0];
									deckTwo[j][1] = deckTwo[j + 1][1];
								}
								return 1;
							}
						}
					}
					else if (UpperCard[2] == 3)
					{
						bool IsRes = false;
						int chai = 0;
						int chaiThree;
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
							{
								Out[0] = deckThree[i][0];
								Out[1] = UpperCard[1];
								Out[2] = 3;
								deckThreeIndex--;
								if (deckThree[i][1] - UpperCard[1] >= 2)
								{
									chai = 1;
									deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
									deckThree[i][1] = deckThree[i][1] - UpperCard[1];
								}
								else
								{
									if (deckThree[i][1] - UpperCard[1] > 0)
									{
										chai = 2;
										for (int j = 0; j < ThreeIndex; j++)
										{
											if (Three[j] > Out[0])
											{
												for (int k = ThreeIndex; k > j; --k)
												{
													Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
												}
												ThreeIndex += deckThree[i][1] - UpperCard[1];
												for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
												{
													Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
												}
												chaiThree = j;
												break;
											}
										}
									}
									for (int j = i; j < deckThreeIndex; ++j)
									{
										deckThree[j][0] = deckThree[j + 1][0];
										deckThree[j][1] = deckThree[j + 1][1];
									}
								}
								IsRes = true;
								break;
							}
						}
						if (IsRes == true)
						{
							if (UpperCard[4] == 2)//带对子
							{
								int temp = UpperCard[1];
								//多张，所以长度是UpperCard[1]
								if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
								{
									Out[3] = Two[0];
									Out[4] = 2;
									for (int i = 1; i < temp; ++i)
									{
										Out[4 + i] = Two[i];
									}
									TwoIndex -= temp;
									for (int i = 0; i < TwoIndex; ++i)
									{
										Two[i] = Two[i + temp];
									}
									return 1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int k = TwoIndex; k > 0; --k)
									{
										if (Two[k - 1] > deckTwo[0][0])
										{
											Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
										}
										else
										{
											for (int j = 0; j < deckTwo[0][1]; j++)
											{
												Two[k + j] = deckTwo[0][0] + j;
											}
											break;
										}
									}
									TwoIndex += deckTwo[0][1];
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										deckTwo[i][1] = deckTwo[i + 1][1];
										deckTwo[i][0] = deckTwo[i + 1][0];
									}
									deckTwoIndex--;
									Out[3] = Two[0];
									Out[4] = 2;
									for (int i = 1; i < Out[1]; i++)
									{
										Out[4 + i] = Two[i + 1];
									}
									for (int i = 0; i < TwoIndex; i++)
									{
										Two[i] = Two[i + Out[1]];
									}
									TwoIndex -= Out[1];
									return 1;
								}
								else
								{
										
								}
							}
							else if (UpperCard[4] == 1)
							{
								int temp = UpperCard[1];
								//
								if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
								{
									Out[3] = One[0];
									Out[4] = 1;
									for (int i = 1; i < temp; ++i)
									{
										Out[4 + i] = One[i];
									}
									OneIndex -= temp;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + temp];
									}
									return 1;
								}
								else
								{

								}
							}
						}
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0 && OneIndex < 3)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							KingBoom = 0;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
					else if (UpperCard[2] == 4)//  四代2 //可优化，目前直接炸//都四带二了，说明农名在蛢命，或者必赢了，所以直接炸；
					{
						if (UpperCard[0] == 17 || WhoseOut == 1)
						{
							return -1;
						}
						bool boom = false;
						bool ok = false;
						bool BB = false;
						if (FourIndex > 0)
						{
							boom = true;
						}
						if (UpperCard[4] == 1 && boom == true)
						{
							if (OneIndex > 1 && One[1] < 14)
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = One[1];
								for (int i = 0; i < OneIndex; i++)
								{
									One[i] = One[i + 2];
								}
								OneIndex -= 2;
								ok = true;
							}
							else if (OneIndex == 1 && One[0] < 14)
							{
								if (TwoIndex > 0 && Two[0] < 14)
								{
									if (One[0] > Two[0])
									{
										Out[3] = Two[0];
										Out[4] = 1;
										Out[5] = Two[0];
										TwoIndex--;
										for (int i = 0; i < TwoIndex; i++)
										{
											Two[i] = Two[i + 1];
										}
										ok = true;
									}
									else
									{
										Out[3] = One[0];
										Out[4] = 1;
										Out[5] = Two[0];
										One[0] = Two[0];
										TwoIndex--;
										for (int i = 0; i < TwoIndex; i++)
										{
											Two[i] = Two[i + 1];
										}
										ok = true;
									}
								}
							}
							else if (TwoIndex > 0 && Two[0] < 14)
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{

							}
						}
						else if (UpperCard[4] == 2 && boom == true)
						{
							if (TwoIndex > 1 && Two[1] < 14)
							{
								Out[3] = Two[0];
								Out[4] = 2;
								Out[5] = Two[1];
								TwoIndex -= 2;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 2];
								}
								ok = true;
							}
						}
						else
						{
							BB = true;
						}
						if (ok == true || (BB == true && KingBoom == 0))
						{
							for (int i = 0; i < FourIndex; i++)
							{
								if (Four[i] > UpperCard[0])
								{
									Out[0] = Four[i];
									Out[1] = 4;
									Out[2] = 4;
									FourIndex--;
									for (int j = i; j < FourIndex; ++j)
									{
										Four[j] = Four[j + 1];
									}
								}
							}
							return 1;
						}
						if (KingBoom == 1)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							Out[3] = 0;
							Out[4] = 0;
							Out[5] = 0;
							KingBoom = 0;
							return 1;
						}
						if (FourIndex > 0 && UpperCard[4] > 0)
						{
							for (int i = 0; i < FourIndex; i++)
							{

								Out[0] = Four[i];
								Out[1] = 4;
								Out[2] = 4;
								Out[3] = 0;
								Out[4] = 0;
								Out[5] = 0;
								FourIndex--;
								for (int j = i; j < FourIndex; j++)
								{
									Four[j] = Four[j + 1];
								}
								return 1;
							}
						}
						return -1;
					}
				}
				if (FourIndex > 0)//优化
				{
					Out[0] = Four[0];
					Out[1] = 4;
					Out[2] = 4;
					FourIndex--;
					for (int i = 0; i < FourIndex; ++i)
					{
						Four[i] = Four[i + 1];
					}
					return 1;
				}
			}
			return -1;
		}
		//----------------------地主报双
		else if ((DZIndex == 2 && behindN == 2) || (DZIndex == -1 && frontN == 2))
		{
			int dzMaxOne = OneElseMax;
			bool Boom = false;
			if (WhoseOut == 1 && MyRoundNum > 2 && (UpperCard[2] > 0 || UpperCard[1] > 2 || (UpperCard[0] >= TwoElseMax) || DZIndex == -1))
			{
				return -1;
			}
			if (UpperCard[2] == 0)
			{
				if (deckThreeIndex > 0)//把飞机拆了，三带都压不了
				{
					for (int i = 0; i < deckThreeIndex; ++i)
					{
						bool flag = false;
						for (int j = 0; j < ThreeIndex; j++)
						{
							if (Three[j] > deckThree[i][0])
							{
								flag = true;
								for (int k = ThreeIndex; k > j; --k)
								{
									Three[k - 1 + deckThree[i][1]] = Three[k - 1];
								}
								ThreeIndex += deckThree[i][0];
								for (int k = 0; k < deckThree[i][1]; ++k)
								{
									Three[j + k] = deckThree[i][0] + k;
								}
							}
						}
						if (flag == false)
						{
							for (int k = 0; k < deckThree[i][1]; ++k)
							{
								Three[ThreeIndex + k] = deckThree[i][0] + k;
							}
							ThreeIndex += deckThree[i][1];
						}
					}
				}
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0)
					{
						for (int i = OneIndex - 1; i >= 0; --i)
						{
							if (One[i] > UpperCard[0])
							{
								Out[0] = One[i];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								for (int j = i; j < OneIndex; ++j)
								{
									One[j] = One[j + 1];
								}
								return 1;
							}
						}
					}
					else
					{
						int MaxRestC = 0, IsHave = 0;
						for (int i = 15; i >= 3; --i)
						{
							if (myCard[i] > 0)
							{
								MaxRestC = i;
								IsHave = 1;
							}
							if (elseCard[i] > 0)
							{
								MaxRestC = i;
								break;
							}
						}
						if (UpperCard[0] >= MaxRestC)
						{
							MaxRestC = UpperCard[0] + 1;
						}
						if (deckIndex > 0 && IsHave > 0 )
						{
							for (int i = 0; i < deckIndex; ++i)
							{
								if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
								{
									Out[0] = deck[i][0] + deck[i][1] - 1;
									Out[1] = 1;
									Out[2] = 0;
									deck[i][1]--;
									return 1;
								}
							}
						}
						if (TwoIndex > 0 && IsHave > 0)
						{
							for (int i = 0; i < TwoIndex; ++i)
							{
								if (Two[i] >= MaxRestC)
								{
									Out[0] = Two[i];
									Out[1] = 1;
									Out[2] = 0;
									TwoIndex--;
									int IsADD = 0;
									for (int j = 0; j < OneIndex; j++)
									{
										if (One[j] > Out[0])
										{
											for (int k = OneIndex; k > j; --k)
											{
												One[k] = One[k - 1];
											}
											++OneIndex;
											One[j] = Out[0];
											IsADD = 1;
										}
									}
									if (IsADD == 0)
									{
										One[OneIndex] = Out[0];
										OneIndex++;
									}
									return 1;
								}
							}
						}
						if (ThreeIndex > 0 && IsHave > 0)
						{
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] >= MaxRestC)
								{
									Out[0] = Three[i];
									Out[1] = 1;
									Out[2] = 0;
									ThreeIndex--;
									for (int j = 0; j < TwoIndex; j++)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; --k)
											{
												Two[k] = Two[k - 1];
											}
											++TwoIndex;
											Two[j] = Out[0];
										}
									}
									return 1;
								}
							}
						}
					}
				}
				else if (UpperCard[1] == 2)
				{
					if (TwoIndex > 0)
					{
						for (int i = 0; i < TwoIndex; ++i)
						{
							
							if (Two[i] > UpperCard[0] && Two[i] >= TwoElseMax)
							{
								
								Out[0] = Two[i];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								for (int j = i; j < TwoIndex; ++j)
								{
									Two[j] = Two[j + 1];
								}
								return 1;
							}
						}
					}
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 1)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 1)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckTwoIndex > 0 && IsHave > 0)
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && IsHave > 0)
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 2;
								Out[2] = 0;
								ThreeIndex--;
								return 1;
							}
						}
					}
					if (TwoIndex > 0 && Two[TwoIndex - 1] > UpperCard[0])
					{
						Out[0] = Two[TwoIndex - 1];
						Out[1] = 2;
						Out[2] = 0;
						return 1;
					}
				}
				else//UpperCard[3] ==3
				{
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//飞机拆分
					if (IsRes == false)
					{
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************三带 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//重点优化//思考是否一定要压，拆对子还是拆顺子还是拆三，待定复杂情况//决定拆顺子，和最大的三
							{
									
								if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
								{
									Out[3] = Three[ThreeIndex - 2];
									Out[4] = 1;
									Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
									ThreeIndex--;
									flag = true;
									bool fg = false;
									for (int i = 0; i < TwoIndex; ++i)
									{
										if (Two[i] > Out[3])
										{
											for (int j = TwoIndex; j > i; j--)
											{
												Two[j] = Two[j - 1];
											}
											Two[i] = Out[3];
											TwoIndex++;
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										Two[TwoIndex] = Out[3];
										TwoIndex++;
									}
								}
								else if ((ThreeIndex == 1 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
								{
									Out[3] = Three[ThreeIndex - 1];
									Out[4] = 1;
									ThreeIndex--;
									flag = true;
									bool fg = false;
									for (int i = 0; i < TwoIndex; ++i)
									{
										if (Two[i] > Out[3])
										{
											for (int j = TwoIndex; j > i; j--)
											{
												Two[j] = Two[j - 1];
											}
											Two[i] = Out[3];
											TwoIndex++;
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										Two[TwoIndex] = Out[3];
										TwoIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && Two[0] < OneElseMax)
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
					cout << IsRes << " " << flag << endl;
				}
			}
			else if (UpperCard[2] == 1)
			{
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] + deckTwo[i][1] - 1 > UpperCard[0] + UpperCard[1] - 1 && deckTwo[i][1] > UpperCard[1])
					{
						for (int j = 0; j < deckTwo[i][1]; j++)
						{
							if (deckTwo[i][0] + j > UpperCard[0])
							{
								Out[0] = deckTwo[i][0] + j;
								Out[1] = UpperCard[1];
								Out[2] = 2;
								return 1;
							}
						}
					}
				}
			}
			else if (UpperCard[2] == 3)
			{
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//带对子
					{
						int temp = UpperCard[1];
						//多张，所以长度是UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{

						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
			}
			else if (UpperCard[2] == 4)//  四代2 //可优化，目前直接炸//都四带二了，说明农名在蛢命，或者必赢了，所以直接炸；
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				bool BB = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				else
				{
					BB = true;
				}
				if (ok == true || (BB == true && KingBoom == 0))
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0 && UpperCard[4] > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			if (KingBoom == 1 && (WhoseOut != 1 || MyRoundNum == 1))
			{
				Out[0] = 17;
				Out[1] = 2;
				Out[2] = 4;
				KingBoom = 0;
				return 1;
			}
			else if (FourIndex > 0)//优化
			{
				Out[0] = Four[0];
				Out[1] = 4;
				Out[2] = 4;
				FourIndex--;
				for (int i = 0; i < FourIndex; ++i)
				{
					Four[i] = Four[i + 1];
				}
				return 1;
			}
			return -1;
		}
		//------------牌好的农民 ||地主下家
		else if (GoodNM || (DZIndex == -1))
		{
			if (UpperCard[2] == 0)
			{
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0 && (myN == 1 || (MyRoundNum == 2 && One[OneIndex - 1] >= OneElseMax)) && One[OneIndex - 1] > UpperCard[0])
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					if (OneIndex > 0)
					{
						if (MyRoundNum < 3 && OneIndex + TwoIndex < 3 && One[OneIndex - 1] >= OneElseMax)
						{
							if (One[OneIndex - 1] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = One[OneIndex - 1];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								return 1;
							}
						}
						for (int i = 0; i < OneIndex; ++i)
						{
							if (One[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = One[i];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								for (int j = i; j < OneIndex; ++j)
								{
									One[j] = One[j + 1];
								}
								return 1;
							}
						}
					}
					//else 不是else关系  one中可能没有最大的牌 //拆牌
					if (WhoseOut == 1 && ((DZIndex == 2 && behindN > 9)) || (DZIndex == -1))
					{
						return -1;
					}
					else
					{
						int MaxRestC = 0, IsHave = 0;
						for (int i = 15; i >= 3; --i)
						{
							if (myCard[i] > 0)
							{
								MaxRestC = i;
								IsHave = 1;
							}
							if (elseCard[i] > 0)
							{
								MaxRestC = i;
								break;
							}
						}
						if (UpperCard[0] >= MaxRestC)
						{
							MaxRestC = UpperCard[0] + 1;
						}
						if (deckIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 9) || (DZIndex == 2 && behindN < 9)))
						{
							for (int i = 0; i < deckIndex; ++i)
							{
								if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
								{
									Out[0] = deck[i][0] + deck[i][1] - 1;
									Out[1] = 1;
									Out[2] = 0;
									deck[i][1]--;
									return 1;
								}
							}
						}
						if (TwoIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 5) || (DZIndex == 2 && behindN < 5)))
						{
							for (int i = 0; i < TwoIndex; ++i)
							{
								if (Two[i] >= MaxRestC)
								{
									Out[0] = Two[i];
									Out[1] = 1;
									Out[2] = 0;
									TwoIndex--;
									int IsADD = 0;
									for (int j = 0; j < OneIndex; j++)
									{
										if (One[j] > Out[0])
										{
											for (int k = OneIndex; k > j; --k)
											{
												One[k] = One[k - 1];
											}
											++OneIndex;
											One[j] = Out[0];
											IsADD = 1;
										}
									}
									if(IsADD == 0)
									{
										One[OneIndex] = Out[0];
										OneIndex++;
									}
									return 1;
								}
							}
						}
						if (ThreeIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 6) || (DZIndex == 2 && behindN < 6)))
						{
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] >= MaxRestC)
								{
									Out[0] = Three[i];
									Out[1] = 1;
									Out[2] = 0;
									ThreeIndex--;
									for (int j = 0; j < TwoIndex; j++)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; --k)
											{
												Two[k] = Two[k - 1];
											}
											++TwoIndex;
											Two[j] = Out[0];
										}
									}
									return 1;
								}
							}
						}
					}
				}
				else if (UpperCard[1] == 2)
				{
					if (TwoIndex > 0)
					{
						if (TwoIndex > 0 && (myN == 2 || (MyRoundNum == 2 && Two[TwoIndex - 1] > TwoElseMax)) && Two[TwoIndex - 1] > UpperCard[0])
						{
							Out[0] = Two[TwoIndex - 1];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							return 1;
						}
						if (TwoIndex > 0 && MyRoundNum < 3 && OneIndex + TwoIndex < 3 && Two[TwoIndex - 1] >= TwoElseMax)
						{
							if (Two[TwoIndex - 1] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = Two[TwoIndex - 1];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								return 1;
							}
						}
						for (int i = 0; i < TwoIndex; ++i)
						{
							if (Two[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || Two[TwoIndex - 1] > 11))
								{
									return -1;
								}
								Out[0] = Two[i];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								for (int j = i; j < TwoIndex; ++j)
								{
									Two[j] = Two[j + 1];
								}
								return 1;
							}
						}
					}
					//gai
					if (WhoseOut == 1 && DZIndex == 2 && behindN > 9)
					{
						return -1;
					}
					// 地主再拆
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 1)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 1)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckTwoIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 9) || (DZIndex == 2 && behindN < 9)))
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && (IsHave > 0 || (DZIndex == -1 && frontN < 9) || (DZIndex == 2 && behindN < 9)))
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 2;
								Out[2] = 0;
								ThreeIndex--;
								return 1;
							}
						}
					}
				}
				else//UpperCard[3] ==3
				{
					if (WhoseOut == 1 && ((DZIndex == -1) || (DZIndex == 2 && (behindN > 8 || UpperCard[0] > 11))))
					{
						return -1;
					}
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//飞机拆分
					if (IsRes == false)
					{
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************三带 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0 && One[0] < 13)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//重点优化//思考是否一定要压，拆对子还是拆顺子还是拆三，待定复杂情况//决定拆顺子，和最大的三
							{
								if (WhoseOut == -1 && frontN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (OneIndex > 0 && One[0] < 15)
								{
									Out[4] = 1;
									Out[3] = One[0];
									OneIndex++;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + 1];
									}
									flag = true;
								}
								else if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (WhoseOut == -1 && behindN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[0][1] - 1 > 12 && i == deckTwoIndex - 1 )
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
					if (DZIndex == 2 && behindN < 4)
					{
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							KingBoom = 0;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
					return -1;
				}
			}
			else if (UpperCard[2] == 1)
			{
				
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && (DZIndex == -1 || deck[i][0] > 7 || deck[i][0] > 6))
						{
							return -1;
						}
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && ((DZIndex == -1) || (behindN > 9 && DZIndex == 2)))
				{
					return -1;
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (DZIndex == 2 && behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && (DZIndex == -1 || deckTwo[i][0] > 8 || deckTwo[i][1] > 3))
						{
							return -1;
						}
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && ((DZIndex == -1) || (behindN > 9 && DZIndex == 2)))
				{
					return -1;
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
					else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0];
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0] + 1;
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (DZIndex == 2 && behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 3)
			{
				if (WhoseOut == 1 && ((DZIndex == -1) || (DZIndex == 2 && (behindN > 8 || UpperCard[0] > 9 || UpperCard[1] > 2))))
				{
					return -1;
				}
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//带对子
					{
						int temp = UpperCard[1];
						//多张，所以长度是UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{
							return -1;
						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
				if (DZIndex == 2 && behindN < 4)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 4)//  四代2 //可优化，目前直接炸//都四带二了，说明农名在蛢命，或者必赢了，所以直接炸；
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				bool BB = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				else
				{
					BB = true;
				}
				if (ok == true || (BB == true && KingBoom == 0))
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0 && UpperCard[4] > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else
			{
				return -1;
			}
		}
		//------------地主上家垃圾农民
		else
		{
			if (UpperCard[2] == 0)
			{
				if (UpperCard[1] == 1)
				{
					if (OneIndex > 0 && (myN == 1 || (MyRoundNum == 2 && One[OneIndex - 1] > OneElseMax)) && One[OneIndex - 1] > UpperCard[0])
					{
						Out[0] = One[OneIndex - 1];
						Out[1] = 1;
						Out[2] = 0;
						OneIndex--;
						return 1;
					}
					if (OneIndex > 0)
					{
						if (MyRoundNum < 3 && OneIndex + TwoIndex < 3 && One[OneIndex - 1] >= OneElseMax)
						{
							bool ISOK = false;
							for(int i = 0;i < OneIndex;++i)
							{
								if(One[i] > 7 && One[i] > UpperCard[0])
								{
									Out[0] = One[i];
									Out[1] = 1;
									Out[2] = 0;
									OneIndex--;
									for(;i < OneIndex;++i)
									{
										One[i]=One[i+1];
									}
									return 1;
								}
							}
							for(int i = 0;i < OneIndex;++i)
							{
								if(One[i] > UpperCard[0])
								{
									Out[0] = One[i];
									Out[1] = 1;
									Out[2] = 0;
									OneIndex--;
									for(;i < OneIndex;++i)
									{
										One[i]=One[i+1];
									}
									return 1;
								}
							}
						}
						for (int i = 0; i < OneIndex; ++i)
						{
							if (One[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || UpperCard[0] > 13))
								{
									return -1;
								}
								Out[0] = One[i];
								Out[1] = 1;
								Out[2] = 0;
								OneIndex--;
								for (int j = i; j < OneIndex; ++j)
								{
									One[j] = One[j + 1];
								}
								return 1;
							}
						}
					}
					if (WhoseOut == 1 && (UpperCard[0] > 13 || behindN > 8))
					{
						return -1;
					}
					else
					{
						int MaxRestC = 0, IsHave = 0;
						for (int i = 15; i >= 3; --i)
						{
							if (myCard[i] > 0)
							{
								MaxRestC = i;
								IsHave = 1;
							}
							if (elseCard[i] > 0)
							{
								MaxRestC = i;
								break;
							}
						}
						if (UpperCard[0] >= MaxRestC)
						{
							MaxRestC = UpperCard[0] + 1;
						}
						if (deckIndex > 0 && (IsHave > 0 || behindN < 9))
						{
							for (int i = 0; i < deckIndex; ++i)
							{
								if (deck[i][1] > 5 && deck[i][0] + deck[i][1] - 1 >= MaxRestC)
								{
									Out[0] = deck[i][0] + deck[i][1] - 1;
									Out[1] = 1;
									Out[2] = 0;
									deck[i][1]--;
									return 1;
								}
							}
						}
						if (TwoIndex > 0 && (IsHave > 0 || behindN < 5))
						{
							for (int i = 0; i < TwoIndex; ++i)
							{
								if (Two[i] >= MaxRestC)
								{
									Out[0] = Two[i];
									Out[1] = 1;
									Out[2] = 0;
									TwoIndex--;
									int IsADD = 0;
									for (int j = 0; j < OneIndex; j++)
									{
										if (One[j] > Out[0])
										{
											for (int k = OneIndex; k > j; --k)
											{
												One[k] = One[k - 1];
											}
											++OneIndex;
											One[j] = Out[0];
											IsADD = 1;
										}
									}
									if(IsADD == 0)
									{
										One[OneIndex] = Out[0];
										OneIndex++;
									}
									return 1;
								}
							}
						}
						if (ThreeIndex > 0 && (IsHave > 0 || behindN < 6))
						{
							for (int i = 0; i < ThreeIndex; ++i)
							{
								if (Three[i] >= MaxRestC)
								{
									Out[0] = Three[i];
									Out[1] = 1;
									Out[2] = 0;
									ThreeIndex--;
									for (int j = 0; j < TwoIndex; j++)
									{
										if (Two[j] > Out[0])
										{
											for (int k = TwoIndex; k > j; --k)
											{
												Two[k] = Two[k - 1];
											}
											++TwoIndex;
											Two[j] = Out[0];
										}
									}
									return 1;
								}
							}
						}
					}
				}
				else if (UpperCard[1] == 2)
				{
					if (TwoIndex > 0)
					{
						if (TwoIndex > 0 && (myN == 2 || (MyRoundNum == 2 && Two[TwoIndex - 1] >= TwoElseMax)) && Two[TwoIndex - 1] > UpperCard[0])
						{
							Out[0] = Two[TwoIndex - 1];
							Out[1] = 2;
							Out[2] = 0;
							TwoIndex--;
							return 1;
						}
						if (TwoIndex > 0 && MyRoundNum < 3 && OneIndex + TwoIndex < 3 && Two[TwoIndex - 1] >= TwoElseMax)
						{
							if (Two[TwoIndex - 1] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || Two[TwoIndex - 1] > 12))
								{
									return -1;
								}
								Out[0] = Two[TwoIndex - 1];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								return 1;
							}
						}
						for (int i = 0; i < TwoIndex; ++i)
						{
							if (Two[i] > UpperCard[0])
							{
								if (WhoseOut == 1 && (DZIndex == -1 || Two[TwoIndex - 1] > 13))
								{
									return -1;
								}
								Out[0] = Two[i];
								Out[1] = 2;
								Out[2] = 0;
								TwoIndex--;
								for (int j = i; j < TwoIndex; ++j)
								{
									Two[j] = Two[j + 1];
								}
								return 1;
							}
						}
					}
					//gai
					if (WhoseOut == 1 && (UpperCard[0] > 12 || behindN > 8))
					{
						return -1;
					}
					// 地主再拆
					int MaxRestC = 0, IsHave = 0;
					for (int i = 15; i >= 3; --i)
					{
						if (myCard[i] > 1)
						{
							MaxRestC = i;
							IsHave = 1;
						}
						if (elseCard[i] > 1)
						{
							MaxRestC = i;
							break;
						}
					}
					if (UpperCard[0] >= MaxRestC)
					{
						MaxRestC = UpperCard[0] + 1;
					}
					if (deckTwoIndex > 0 && (IsHave > 0 || behindN < 9))
					{
						for (int i = 0; i < deckTwoIndex; ++i)
						{
							if (deckTwo[i][1] > 3 && deckTwo[i][0] + deckTwo[i][1] - 1 >= MaxRestC)
							{
								Out[0] = deckTwo[i][0] + deckTwo[i][1] - 1;
								Out[1] = 2;
								Out[2] = 0;
								deckTwo[i][1]--;
								return 1;
							}
						}
					}
					if (ThreeIndex > 0 && (IsHave > 0 || behindN < 9))
					{
						for (int i = 0; i < ThreeIndex; ++i)
						{
							if (Three[i] >= MaxRestC)
							{
								Out[0] = Three[i];
								Out[1] = 2;
								Out[2] = 0;
								ThreeIndex--;
								return 1;
							}
						}
					}
				}
				else//UpperCard[3] ==3
				{
					if (WhoseOut == 1 && (UpperCard[0] > 10 || behindN > 8))
					{
						return -1;
					}
					bool IsRes = false;
					bool flag = false;
					int temp = 0;
					for (int i = 0; i < ThreeIndex; ++i)
					{
						if (Three[i] > UpperCard[0])
						{
							Out[0] = Three[i];
							Out[1] = 3;
							Out[2] = 0;
							temp = i;
							IsRes = true;
							break;
						}
					}
					//飞机拆分
					if (IsRes == false)
					{
						for (int i = 0; i < deckThreeIndex; ++i)
						{
							if (deckThree[i][0] + deckThree[i][1] - 1 > UpperCard[0])
							{
								Out[0] = deckThree[i][0] + deckThree[i][1] - 1;
								Out[1] = 3;
								Out[2] = 0;
								temp = 10 + i;
								IsRes = true;
								break;
							}
						}
					}
					//************三带 0,1,2
					if (IsRes == true)
					{
						if (UpperCard[4] == 1)
						{
							if (OneIndex > 0 && One[0] < 13)
							{
								Out[4] = 1;
								Out[3] = One[0];
								OneIndex++;
								for (int i = 0; i < OneIndex; ++i)
								{
									One[i] = One[i + 1];
								}
								flag = true;
							}
							else//重点优化//思考是否一定要压，拆对子还是拆顺子还是拆三，待定复杂情况//决定拆顺子，和最大的三
							{
								if (WhoseOut == -1 && frontN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (OneIndex > 0 && One[0] < 15)
								{
									Out[4] = 1;
									Out[3] = One[0];
									OneIndex++;
									for (int i = 0; i < OneIndex; ++i)
									{
										One[i] = One[i + 1];
									}
									flag = true;
								}
								else if (deckIndex > 0)
								{
									for (int i = 0; i < deckIndex; ++i)
									{
										if (deck[i][1] > 5)
										{
											Out[3] = deck[i][0];
											Out[4] = 1;
											deck[i][0]++;
											deck[i][1]--;
											flag = true;
											break;
										}
									}
								}
								else if (TwoIndex > 1)
								{
									Out[3] = Two[TwoIndex - 2];
									Out[4] = 1;
									Two[TwoIndex - 2] = Two[TwoIndex - 1];
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else if (TwoIndex == 1)
								{
									Out[3] = Two[TwoIndex - 1];
									Out[4] = 1;
									TwoIndex--;
									bool fg = false;
									flag = true;
									for (int i = 0; i < OneIndex; ++i)
									{
										if (One[i] > Out[3])
										{
											for (int j = OneIndex; j > i; j--)
											{
												One[j] = One[j - 1];
											}
											OneIndex++;
											One[i] = Out[3];
											fg = true;
											break;
										}
									}
									if (!fg)
									{
										One[OneIndex] = Out[3];
										OneIndex++;
									}
								}
								else
								{

								}
							}
						}
						else if (UpperCard[4] == 2)
						{
							if (TwoIndex > 0 && (Two[0] < 13 || behindN < 6))
							{
								Out[4] = 2;
								Out[3] = Two[0];
								TwoIndex++;
								for (int i = 0; i < TwoIndex; ++i)
								{
									Two[i] = Two[i + 1];
								}
								flag = true;
							}
							else
							{
								if (WhoseOut == -1 && behindN < 5)
								{
									int boomtemp = -1;
									for (int i = 15; i > 2; i--)
									{
										if (elseCard[i] > 3)
										{
											boomtemp = i;
											break;
										}
									}
									if (boomtemp > 0 && FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else if (KingBoom > 0 && OneIndex < 3)
									{
										Out[0] = 17;
										Out[1] = 2;
										Out[2] = 4;
										KingBoom = 0;
										return 1;
									}
									else if (FourIndex > 0)
									{
										Out[0] = Four[0];
										Out[1] = 4;
										Out[2] = 4;
										Out[4] = 0;
										Out[3] = 0;
										FourIndex--;
										for (int i = 0; i < FourIndex; ++i)
										{
											Four[i] = Four[i + 1];
										}
										return 1;
									}
									else
									{
										if (deckIndex > 0)
										{
											for (int i = 0; i < deckIndex; ++i)
											{
												if (deck[i][1] > 5)
												{
													Out[3] = deck[i][0];
													Out[4] = 1;
													deck[i][0]++;
													deck[i][1]--;
													flag = true;
													break;
												}
											}
										}
										else if (TwoIndex > 1)
										{
											Out[3] = Two[TwoIndex - 2];
											Out[4] = 1;
											Two[TwoIndex - 2] = Two[TwoIndex - 1];
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (TwoIndex == 1)
										{
											Out[3] = Two[TwoIndex - 1];
											Out[4] = 1;
											TwoIndex--;
											bool fg = false;
											flag = true;
											for (int i = 0; i < OneIndex; ++i)
											{
												if (One[i] > Out[3])
												{
													for (int j = OneIndex; j > i; j--)
													{
														One[j] = One[j - 1];
													}
													OneIndex++;
													One[i] = Out[3];
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												One[OneIndex] = Out[3];
												OneIndex++;
											}
										}
										else if (ThreeIndex > 1 && ThreeIndex - 2 != temp)
										{
											Out[3] = Three[ThreeIndex - 2];
											Out[4] = 1;
											Three[ThreeIndex - 2] = Three[ThreeIndex - 1];
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else if ((ThreeIndex == 1 && Three[0] < 15 && ThreeIndex != temp) || (ThreeIndex > 1 && ThreeIndex - 2 != temp))
										{
											Out[3] = Three[ThreeIndex - 1];
											Out[4] = 1;
											ThreeIndex--;
											flag = true;
											bool fg = false;
											for (int i = 0; i < TwoIndex; ++i)
											{
												if (Two[i] > Out[3])
												{
													for (int j = TwoIndex; j > i; j--)
													{
														Two[j] = Two[j - 1];
													}
													Two[i] = Out[3];
													TwoIndex++;
													fg = true;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = Out[3];
												TwoIndex++;
											}
										}
										else
										{

										}
									}
								}
								else if (WhoseOut == 1)
								{
									return -1;
								}
								else if (deckTwoIndex > 0)
								{
									for (int i = 0; i < deckTwoIndex; ++i)
									{
										if (deckTwo[i][1] > 3)
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											deckTwo[i][0]++;
											deckTwo[i][1]--;
											break;
										}
										else if (deckTwo[i][0]+ deckTwo[i][1] - 1 > 12 && i == deckTwoIndex - 1 && (frontN < 5 || behindN < 5))
										{
											Out[3] = deckTwo[i][0];
											Out[4] = 2;
											flag = true;
											bool fg = false;
											for (int j = 0; j < TwoIndex; ++j)
											{
												if (Two[j] > Out[3])
												{
													for (int k = TwoIndex; k > j; --k)
													{
														Two[k + 1] = Two[k - 1];
													}
													fg = true;
													Two[j] = deckTwo[i][0] + 1;
													Two[j + 1] = deckTwo[i][0] + 2;
													TwoIndex += 2;
													break;
												}
											}
											if (!fg)
											{
												Two[TwoIndex] = deckTwo[i][0] + 1;
												Two[TwoIndex + 1] = deckTwo[i][0] + 2;
												TwoIndex += 2;
											}
										}
										else
										{

										}
									}
								}
							}
						}
						else
						{
							flag = true;
						}
					}
					if (IsRes && flag)
					{
						if (temp < 10)
						{
							for (int i = temp; i < ThreeIndex; i++)
							{
								Three[i] = Three[i + 1];
							}
							ThreeIndex--;
						}
						else
						{
							temp -= 10;
							if (deckThree[temp][1] > 2)
							{
								deckThree[temp][1]--;
							}
							else
							{
								bool fg = false;
								for (int i = 0; i < ThreeIndex; ++i)
								{
									if (Three[i] > deckThree[temp][0])
									{
										for (int j = ThreeIndex; j > i; --j)
										{
											Three[j] = Three[j - 1];
										}
										Three[i] = deckThree[temp][0];
										ThreeIndex++;
										fg = true;
										break;
									}
								}
								if (!fg)
								{
									Three[ThreeIndex] = deckThree[temp][0];
									ThreeIndex++;
								}
								for (int i = temp; i < deckThreeIndex; ++i)
								{
									deckThree[i][1] = deckThree[i + 1][1];
									deckThree[i][0] = deckThree[i + 1][0];
								}
							}
						}
						return 1;
					}
					if (behindN < 4)
					{
						int boomtemp = -1;
						for (int i = 15; i > 2; i--)
						{
							if (elseCard[i] > 3)
							{
								boomtemp = i;
								break;
							}
						}
						if (boomtemp > 0 && FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
						else if (KingBoom > 0 && OneIndex < 3)
						{
							Out[0] = 17;
							Out[1] = 2;
							Out[2] = 4;
							KingBoom = 0;
							return 1;
						}
						else if (FourIndex > 0)
						{
							Out[0] = Four[0];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int i = 0; i < FourIndex; ++i)
							{
								Four[i] = Four[i + 1];
							}
							return 1;
						}
					}
					return -1;
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 1)
			{
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && deck[i][0] > 6)
						{
							return -1;
						}
						Out[0] = deck[i][0];
						Out[1] = deck[i][1];
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && (UpperCard[0] > 8 || behindN > 10 || UpperCard[1] > 6))
				{
					return -1;
				}
				for (int i = 0; i < deckIndex; ++i)
				{
					if (deck[i][0] > UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0] + deck[i][1] - 1;
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0];
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
					else if (deck[i][0] == UpperCard[0] && deck[i][1] == UpperCard[1] + 1)
					{
						int restOne = deck[i][0];
						for (int k = OneIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (One[k - 1] > restOne)
							{
								One[k] = One[k - 1];
							}
							else
							{
								One[k] = restOne;
								break;
							}
						}
						OneIndex++;
						Out[0] = deck[i][0] + 1;
						Out[1] = deck[i][1] - 1;
						Out[2] = 1;
						deckIndex--;
						for (int j = i; j < deckIndex; ++j)
						{
							deck[j][0] = deck[j + 1][0];
							deck[j][1] = deck[j + 1][1];
						}
						return 1;
					}
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 2)
			{
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1])
					{
						if (WhoseOut == 1 && (DZIndex == -1 || deckTwo[i][0] > 9))
						{
							return -1;
						}
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1];
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (WhoseOut == 1 && (UpperCard[0] > 8 || behindN > 10 || UpperCard[1] > 3))
				{
					return -1;
				}
				for (int i = 0; i < deckTwoIndex; ++i)
				{
					if (deckTwo[i][0] > UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0] + deckTwo[i][1] - 1;
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0];
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
					else if (deckTwo[i][0] == UpperCard[0] && deckTwo[i][1] == UpperCard[1] + 1)
					{
						int restTwo = deckTwo[i][0];
						for (int k = TwoIndex; k > 0; --k)
						{
							//One[k-1] == restOne
							if (Two[k - 1] > restTwo)
							{
								Two[k] = Two[k - 1];
							}
							else
							{
								Two[k] = restTwo;
								break;
							}
						}
						TwoIndex++;
						Out[0] = deckTwo[i][0] + 1;
						Out[1] = deckTwo[i][1] - 1;
						Out[2] = 2;
						deckTwoIndex--;
						for (int j = i; j < deckTwoIndex; ++j)
						{
							deckTwo[j][0] = deckTwo[j + 1][0];
							deckTwo[j][1] = deckTwo[j + 1][1];
						}
						return 1;
					}
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 3)
			{
				if (WhoseOut == 1 && (UpperCard[0] > 8 || behindN > 10 || UpperCard[1] > 2))
				{
					return -1;
				}
				bool IsRes = false;
				int chai = 0;
				int chaiThree;
				for (int i = 0; i < deckThreeIndex; ++i)
				{
					if (UpperCard[0] < deckThree[i][0] && UpperCard[1] <= deckThree[i][1])
					{
						Out[0] = deckThree[i][0];
						Out[1] = UpperCard[1];
						Out[2] = 3;
						deckThreeIndex--;
						if (deckThree[i][1] - UpperCard[1] >= 2)
						{
							chai = 1;
							deckThree[i][0] = deckThree[i][0] + UpperCard[1] - 1;
							deckThree[i][1] = deckThree[i][1] - UpperCard[1];
						}
						else
						{
							if (deckThree[i][1] - UpperCard[1] > 0)
							{
								chai = 2;
								for (int j = 0; j < ThreeIndex; j++)
								{
									if (Three[j] > Out[0])
									{
										for (int k = ThreeIndex; k > j; --k)
										{
											Three[k - 1 + deckThree[i][1] - UpperCard[1]] = Three[k - 1];
										}
										ThreeIndex += deckThree[i][1] - UpperCard[1];
										for (int k = 0; k < deckThree[i][1] - UpperCard[1]; ++k)
										{
											Three[j + k] = deckThree[i][0] + UpperCard[1] + k;
										}
										chaiThree = j;
										break;
									}
								}
							}
							for (int j = i; j < deckThreeIndex; ++j)
							{
								deckThree[j][0] = deckThree[j + 1][0];
								deckThree[j][1] = deckThree[j + 1][1];
							}
						}
						IsRes = true;
						break;
					}
				}
				if (IsRes == true)
				{
					if (UpperCard[4] == 2)//带对子
					{
						int temp = UpperCard[1];
						//多张，所以长度是UpperCard[1]
						if (TwoIndex >= UpperCard[1] && Two[UpperCard[1]] < 14)
						{
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = Two[i];
							}
							TwoIndex -= temp;
							for (int i = 0; i < TwoIndex; ++i)
							{
								Two[i] = Two[i + temp];
							}
							return 1;
						}
						else if (deckTwoIndex > 0)
						{
							for (int k = TwoIndex; k > 0; --k)
							{
								if (Two[k - 1] > deckTwo[0][0])
								{
									Two[k - 1 + deckTwo[0][1]] = Two[k - 1];
								}
								else
								{
									for (int j = 0; j < deckTwo[0][1]; j++)
									{
										Two[k + j] = deckTwo[0][0] + j;
									}
									break;
								}
							}
							TwoIndex += deckTwo[0][1];
							for (int i = 0; i < deckTwoIndex; ++i)
							{
								deckTwo[i][1] = deckTwo[i + 1][1];
								deckTwo[i][0] = deckTwo[i + 1][0];
							}
							deckTwoIndex--;
							Out[3] = Two[0];
							Out[4] = 2;
							for (int i = 1; i < Out[1]; i++)
							{
								Out[4 + i] = Two[i + 1];
							}
							for (int i = 0; i < TwoIndex; i++)
							{
								Two[i] = Two[i + Out[1]];
							}
							TwoIndex -= Out[1];
							return 1;
						}
						else
						{
							return -1;
						}
					}
					else if (UpperCard[4] == 1)
					{
						int temp = UpperCard[1];
						//
						if (OneIndex >= UpperCard[1] && One[UpperCard[1] - 1] < 16)
						{
							Out[3] = One[0];
							Out[4] = 1;
							for (int i = 1; i < temp; ++i)
							{
								Out[4 + i] = One[i];
							}
							OneIndex -= temp;
							for (int i = 0; i < OneIndex; ++i)
							{
								One[i] = One[i + temp];
							}
							return 1;
						}
						else
						{

						}
					}
				}
				if (behindN < 5)
				{
					int boomtemp = -1;
					for (int i = 15; i > 2; i--)
					{
						if (elseCard[i] > 3)
						{
							boomtemp = i;
							break;
						}
					}
					if (boomtemp > 0 && FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
					else if (KingBoom > 0 && OneIndex < 3)
					{
						Out[0] = 17;
						Out[1] = 2;
						Out[2] = 4;
						KingBoom = 0;
						return 1;
					}
					else if (FourIndex > 0)
					{
						Out[0] = Four[0];
						Out[1] = 4;
						Out[2] = 4;
						FourIndex--;
						for (int i = 0; i < FourIndex; ++i)
						{
							Four[i] = Four[i + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else if (UpperCard[2] == 4)//  四代2 //可优化，目前直接炸//都四带二了，说明农名在蛢命，或者必赢了，所以直接炸；
			{
				if (UpperCard[0] == 17 || WhoseOut == 1)
				{
					return -1;
				}
				bool boom = false;
				bool ok = false;
				bool BB = false;
				if (FourIndex > 0)
				{
					boom = true;
				}
				if (UpperCard[4] == 1 && boom == true)
				{
					if (OneIndex > 1 && One[1] < 14)
					{
						Out[3] = One[0];
						Out[4] = 1;
						Out[5] = One[1];
						for (int i = 0; i < OneIndex; i++)
						{
							One[i] = One[i + 2];
						}
						OneIndex -= 2;
						ok = true;
					}
					else if (OneIndex == 1 && One[0] < 14)
					{
						if (TwoIndex > 0 && Two[0] < 14)
						{
							if (One[0] > Two[0])
							{
								Out[3] = Two[0];
								Out[4] = 1;
								Out[5] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
							else
							{
								Out[3] = One[0];
								Out[4] = 1;
								Out[5] = Two[0];
								One[0] = Two[0];
								TwoIndex--;
								for (int i = 0; i < TwoIndex; i++)
								{
									Two[i] = Two[i + 1];
								}
								ok = true;
							}
						}
					}
					else if (TwoIndex > 0 && Two[0] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 1;
						Out[5] = Two[0];
						TwoIndex--;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 1];
						}
						ok = true;
					}
					else
					{

					}
				}
				else if (UpperCard[4] == 2 && boom == true)
				{
					if (TwoIndex > 1 && Two[1] < 14)
					{
						Out[3] = Two[0];
						Out[4] = 2;
						Out[5] = Two[1];
						TwoIndex -= 2;
						for (int i = 0; i < TwoIndex; i++)
						{
							Two[i] = Two[i + 2];
						}
						ok = true;
					}
				}
				else
				{
					BB = true;
				}
				if (ok == true || (BB == true && KingBoom == 0))
				{
					for (int i = 0; i < FourIndex; i++)
					{
						if (Four[i] > UpperCard[0])
						{
							Out[0] = Four[i];
							Out[1] = 4;
							Out[2] = 4;
							FourIndex--;
							for (int j = i; j < FourIndex; ++j)
							{
								Four[j] = Four[j + 1];
							}
						}
					}
					return 1;
				}
				if (KingBoom == 1)
				{
					Out[0] = 17;
					Out[1] = 2;
					Out[2] = 4;
					Out[3] = 0;
					Out[4] = 0;
					Out[5] = 0;
					KingBoom = 0;
					return 1;
				}
				if (FourIndex > 0 && UpperCard[4] > 0)
				{
					for (int i = 0; i < FourIndex; i++)
					{

						Out[0] = Four[i];
						Out[1] = 4;
						Out[2] = 4;
						Out[3] = 0;
						Out[4] = 0;
						Out[5] = 0;
						FourIndex--;
						for (int j = i; j < FourIndex; j++)
						{
							Four[j] = Four[j + 1];
						}
						return 1;
					}
				}
				return -1;
			}
			else
			{
				return -1;
			}
		}
	}
	return -1;
}

int card::ScoreOfDZ()//分三档：必抢、可抢、不抢 2 1 -1
{
	//加分： 炸弹 别人接不上的牌 > 2
	//减分： 小于10的 单、对    小于5
	int ScoreDZ = 0;
	int J_A = 0;
	for (int i = 0; i < OneIndex; ++i)
	{
		if (One[i] < 11)
		{
			ScoreDZ--;
		}
		else if (One[i]<15)
		{
			J_A++;
		}
	}
	for (int i = 0; i < TwoIndex; ++i)
	{
		if (Two[i] < 11)
		{
			ScoreDZ--;
		}
		else if (Two[i]<15)
		{
			J_A++;
		}
	}
	//飞机、三个可以带
	for (int i = 0; i < deckThreeIndex; ++i)
	{
		ScoreDZ += deckThree[i][1];
	}
	ScoreDZ += ThreeIndex;
	//去单牌的权值非正，所以<=0
	if (ScoreDZ > 0)
	{
		ScoreDZ = 0;
	}
	// 2和小王1分，大王2，炸弹2分，王炸3分
	int BigScore = myCard[15] + myCard[16] + myCard[17] * 2 + FourIndex * 2;
	if ((BigScore > 4 && ScoreDZ > -4) || (BigScore > 1 && ScoreDZ == 0))
	{
		return 2;
	}
	else if (ScoreDZ > -4 || BigScore >2)
	{
		return 1;
	}
	return -1;
}

bool card::CallDZ(int score, int MyScore)//如果我先叫，则score=0,如果是抢地主，那么score=1;
{
	if (MyScore > score)
	{
		return true;
	}
	return false;
}

void card::CaLL(int I)
{
	if(I == 1)
	{
		IsDZ = true;
		myN = 20;
	}
	else if(I == -1)
	{
		IsDZ = false;
		frontN = 20;
		DZIndex = -1;
		IsGoodNM();
	}
	else
	{
		IsDZ = false;
		behindN = 20;
		DZIndex = 2;
		IsGoodNM();
	}
}
/*
整理手牌
*/
int card::GetBestSort(int x)
{
	int BestS = 0;
	bool flag = false;
	if (DZIndex == 1 && (frontN == 1 || behindN == 1))
	{
		flag = true;
	}
	else if ((DZIndex == 2 && behindN == 1) || (DZIndex == -1 && frontN == 1))
	{
		flag = true;
	}
	//i.	搜索炸弹，搜索飞机，搜索三带，搜索双顺，搜索顺子, 顺子调优,
	if(x==1)
	{
		int indexDeck = 0;
		int Cards[60];//不破坏原有牌组，最后确定后改变
		memcpy(Cards, myCard, sizeof(myCard));
		//最佳牌型：散牌+1，王炸、炸弹-2,大小王-1，飞机-1、葫芦-2
		int result[60]; int Sum;//结果记录
		//王炸
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//$大小王
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		SerchTheProgression(3, Cards, result, &Sum);//查找飞机的数量sum
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i*3+1];
		}
		//
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有葫芦哦
			{
				Cards[i] = 0;
				BestS -=1;
			}
		}
		//连对
		SerchTheProgression(2, Cards, result, &Sum);
		//顺子
		SerchTheProgression(1, Cards, result, &Sum);
		//其他
		for (int i = 3; i < 15; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//ii.	搜索顺子，顺子调优, 搜索炸弹，搜索飞机，搜索双顺, 搜索三带
	else if(x==2)
	{
		int indexDeck = 0;
		int Cards[60];//不破坏原有牌组，最后确定后改变
		memcpy(Cards, myCard, sizeof(myCard));
		//最佳牌型：散牌+1，王炸、炸弹-2,大小王-1，飞机-1、葫芦-2
		int result[60]; int Sum;//结果记录
		//王炸
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//大小王
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i*3+1];
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
			else if(Cards[i] == 3)
			{
				BestS -=1;
			}
		}
	}
	//iii.	搜索炸弹，搜索飞机，搜索三带，搜索顺子, 顺子调优, 搜索双顺
	else if(x==3)
	{
		int indexDeck = 0;
		int Cards[60];//不破坏原有牌组，最后确定后改变
		memcpy(Cards, myCard, sizeof(myCard));
		//最佳牌型：散牌+1，王炸、炸弹-2,大小王-1，飞机-1、葫芦-2
		int result[60]; int Sum;//结果记录
		//王炸
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//$大小王
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i*3+1];
		}
		//
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Cards[i] = 0;
				BestS -=1;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//iv.	搜索炸弹，搜索顺子, 顺子调优, 搜索双顺, 搜索飞机，搜索三带，
	else if (x == 4)
	{
		int indexDeck = 0;
		int Cards[60];//不破坏原有牌组，最后确定后改变
		memcpy(Cards, myCard, sizeof(myCard));
		//最佳牌型：散牌+1，王炸、炸弹-2,大小王-1，飞机-1、葫芦-2
		int result[60]; int Sum;//结果记录
								//王炸
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//$大小王
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		//boom
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//feiji
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//其他
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i * 3 + 1];
		}
		//
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Cards[i] = 0;
				BestS -= 1;
			}
			
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//炸弹，顺子，飞机，三带，双顺
	else if (x == 5)
	{
		int indexDeck = 0;
		int Cards[60];//不破坏原有牌组，最后确定后改变
		memcpy(Cards, myCard, sizeof(myCard));
		//最佳牌型：散牌+1，王炸、炸弹-2,大小王-1，飞机-1、葫芦-2
		int result[60]; int Sum;//结果记录
								//王炸
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//大小王
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i * 3 + 1];
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Cards[i] = 0;
				BestS -= 1;
			}
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}
	//炸弹，飞机，双顺，顺子,三带，
	else if (x == 6)
	{
		int indexDeck = 0;
		int Cards[60];//不破坏原有牌组，最后确定后改变
		memcpy(Cards, myCard, sizeof(myCard));
		//最佳牌型：散牌+1，王炸、炸弹-2,大小王-1，飞机-1、葫芦-2
		int result[60]; int Sum;//结果记录
								//王炸
		if (Cards[16] && Cards[17])
		{
			BestS -= 2;
			Cards[16] = Cards[17] = 0;
		}
		//大小王
		else if (Cards[16] || Cards[17])
		{
			BestS -= 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				BestS -= 2;
				Cards[i] = 0;
			}
		}
		//1
		//feiji
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			BestS -= result[i * 3 + 1];
		}
		SerchTheProgression(2, Cards, result, &Sum);
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Cards[i] = 0;
				BestS -= 1;
			}
		}
		//2
		
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1 && i < 14)
			{
				BestS += 1;
			}
			else if (Cards[i] == 2 && flag == false && i < 13)
			{
				BestS += 1;
			}
		}
	}

	return BestS;
}

int card::SortTheCard()//理牌 目前：王炸 炸弹 三顺 单顺 连对
{
	KingBoom = 0;//王炸
	deckIndex = 0; //最优牌组 牌起点，牌数，标签 （1、2、3为顺子、连对、飞机，4为炸弹，0为散牌）
	deckTwoIndex = 0;
	deckThreeIndex = 0;
	OneIndex = 0;//单排
	OneMaxIndex = 0;
	OneElseMax = 0;
	TwoIndex = 0;//双排
	TwoMaxIndex = 0;
	TwoElseMax = 0;
	ThreeIndex = 0;//三个头
	ThreeMaxIndex = 0;
	ThreeElseMax = 0;
	FourIndex = 0;//炸弹
	int indexDeck = 0;
	int Cards[60];//不破坏原有牌组，最后确定后改变
	memcpy(Cards, myCard, sizeof(myCard));
	//最佳牌型：散牌+1，王炸、炸弹-2,大小王-1，飞机-1、葫芦-2
	int result[60]; int Sum;//结果记录
	//*********************************//
	int s1 = GetBestSort(1); //cout << "s1:" << s1 << endl;
	int s2 = GetBestSort(2); //cout << "s2:" << s2 << endl;
	int s3 = GetBestSort(3); //cout << "s3:" << s3 << endl;
	int s4 = GetBestSort(4); //cout << "s4:" << s4 << endl;
	int s5 = GetBestSort(5); //cout << "s5:" << s5 << endl;
	int s6 = GetBestSort(6); //cout << "s6:" << s6 << endl;
	int s; 
	if (s4 <= s2 && s4 <= s1 && s4 <= s3 && s4 <= s5 && s4 <= s6)
	{
		s = 4;
	}
	else if (s3 <= s2 && s3 <= s1 && s3 <= s4 && s3 <= s5 && s3 <= s6)
	{
		s = 3;
	}
	else if (s1 <= s3 && s1 <= s2 && s1 <= s4 && s1 <= s5 && s1 <= s6)
	{
		s = 1;
	}
	else if (s5 <= s3 && s5 <= s1 && s5 <= s4 && s5 <= s2 && s5 <= s6)
	{
		s = 5;
	}
	else if (s6 <= s3 && s6 <= s1 && s6 <= s4 && s6 <= s5 && s6 <= s2)
	{
		s = 6;
	}
	else
	{
		s = 2;
	}
	//cout << s << endl;
	//**********************************//
	if (s == 1)//搜索炸弹，搜索飞机，搜索三带，搜索双顺，搜索顺子, 顺子调优,
	{
		//王炸
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		// 炸弹、飞机、顺子、连对
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//当前只有一种情况，直接赋值
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		//333
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 2)
	{
		//王炸
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		// 炸弹、飞机、顺子、连对
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//当前只有一种情况，直接赋值
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
			else if (Cards[i] == 3)//还有0哦
			{
				Three[ThreeIndex++] = i;
			}
		}
	}
	else if (s == 3)
	{
		//王炸
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		// 炸弹、飞机、顺子、连对
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//当前只有一种情况，直接赋值
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Three[ThreeIndex++] = i;
				Cards[i]=0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 4)
	{
		//ix.	搜索炸弹，搜索顺子, 顺子调优, 搜索双顺,搜索飞机，搜索三带，
		//王炸
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		// 炸弹、飞机、顺子、连对
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//当前只有一种情况，直接赋值
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 5)
	{
		//ix.	搜索炸弹，搜索顺子, 顺子调优, 搜索双顺,搜索飞机，搜索三带，
		//王炸
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		// 炸弹、飞机、顺子、连对
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//当前只有一种情况，直接赋值
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//1
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	else if (s == 6)
	{
		//ix.	搜索炸弹，搜索顺子, 顺子调优, 搜索双顺,搜索飞机，搜索三带，
		//王炸
		if (Cards[16] && Cards[17])
		{
			KingBoom = 1;
			Cards[16] = Cards[17] = 0;
		}
		//*********************开始理牌***********************//
		// 炸弹、飞机、顺子、连对
		for (int i = 3; i < 16; ++i)
		{
			if (Cards[i] == 4)
			{
				Four[FourIndex] = i;//当前只有一种情况，直接赋值
				FourIndex++;
				Cards[i] = 0;
			}
		}
		//3
		SerchTheProgression(3, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckThree[deckThreeIndex][0] = result[i * 3];
			deckThree[deckThreeIndex][1] = result[i * 3 + 1];
			deckThreeIndex++;
		}
		//2
		SerchTheProgression(2, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deckTwo[deckTwoIndex][0] = result[i * 3];
			deckTwo[deckTwoIndex][1] = result[i * 3 + 1];
			deckTwoIndex++;
		}
		SerchTheProgression(1, Cards, result, &Sum);
		for (int i = 0; i < Sum; ++i)
		{
			deck[deckIndex][0] = result[i * 3];
			deck[deckIndex][1] = result[i * 3 + 1];
			deckIndex++;
		}
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 3)//还有0哦
			{
				Three[ThreeIndex++] = i;
				Cards[i] = 0;
			}
		}
		//1
		
		//其他
		for (int i = 3; i < 18; ++i)
		{
			if (Cards[i] == 1)
			{
				One[OneIndex++] = i;
			}
			else if (Cards[i] == 2)
			{
				Two[TwoIndex++] = i;
			}
		}
	}
	//**************************理牌结束*********************//
	//找出冲锋组
	//外面最大
	int maxOneRest = 0, maxTwoRest = 0, maxThreeRest = 0;
	for (int i = 3; i < 18; ++i)
	{
		if (elseCard[i] > 2)
		{
			if (i > maxThreeRest)
			{
				maxThreeRest = i;
			}
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 1)
		{
			if (i > maxTwoRest)
			{
				maxTwoRest = i;
			}
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
		else if (elseCard[i] > 0)
		{
			if (i > maxOneRest)
			{
				maxOneRest = i;
			}
		}
	}
	//手牌最大
	OneElseMax = maxOneRest;
	TwoElseMax = maxTwoRest;
	ThreeElseMax = maxThreeRest;
	for (int i = 0; i < OneIndex; ++i)
	{
		if (One[i] >= maxOneRest)
		{
			OneMax[OneMaxIndex++] = One[i];
		}
	}
	for (int i = 0; i < TwoIndex; ++i)
	{
		if (Two[i] >= maxTwoRest)
		{
			TwoMax[TwoMaxIndex++] = Two[i];
		}
	}
	for (int i = 0; i < ThreeIndex; ++i)
	{
		if (Three[i] >= maxThreeRest)
		{
			ThreeMax[ThreeMaxIndex++] = One[i];
		}
	}
	/*for (int i = 3; i < 18; i++)
	{
		if (myCard[i] > 0)
		{
			cout << i << " :" << myCard[i] << endl;
		}
	}*/
	return 0;
}

void card::IsGoodNM()
{
	int temp = FourIndex + KingBoom + ThreeIndex;
	for (int i = 0; i < OneIndex; ++i)
	{
		if (One[i] < OneElseMax)
		{
			temp--;
		}
		else
		{
			temp++;
		}
	}
	for (int i = 0; i < TwoIndex; ++i)
	{
		if (Two[i] < TwoElseMax)
		{
			temp--;
		}
		else
		{
			temp++;
		}
	}
	for (int i = 0; i < deckThreeIndex; ++i)
	{
		temp += deckThree[i][1];
	}
	if (temp > -3)
	{
		GoodNM = true;
	}
	else
	{
		GoodNM = false;
	}
}

void card::SerchTheProgression(int LengthOfPg, int *Cards, int * result, int * Sum)//找长度为LengthOfPg的顺子，飞机长度为3，长度2为连对
{
	//结果
	int res[30][2];
	//规定顺子的规则
	int LofPg = 5, NofC = 1;
	if (LengthOfPg == 2)
	{
		LofPg = 3, NofC = 2;
	}
	else if (LengthOfPg == 3)
	{
		LofPg = 2, NofC =3;
	}
	//开始
	int startP = 3, resCount = 0;
	//  最短的顺子
	for (int i = 3; i < 16 - LofPg; ++i)//最后一顺从10开始
	{
		if (Cards[i] >= NofC)//顺子起点
		{
			int endP = i;
			for (int j = 1; j < LofPg; ++j)
			{
				if (Cards[i + j] < NofC)
				{
					endP = i + j;
					break;
				}
			}
			if (endP != i)//中间隔断，从隔断之后的数字重新开始搜索
			{
				i = endP;
				//cout << i << endl;
			}
			else
			{
				for (int k = 0; k < LofPg; k++)//提取牌组，牌数都减1
				{
					Cards[i + k] -= NofC;
				}
				//记录顺子结果
				res[resCount][0] = i;
				res[resCount][1] = LofPg;
				//cout << res[resCount][0] << ' ' << res[resCount][1] << endl;
				resCount++;
				i--;//i打头的牌可能不止一顺
			}
		}
	}
	//将剩下的牌归进顺子里
	for (int i = 0; i < resCount; ++i)
	{
		int temp = res[i][0] + LofPg;
		for (int k = temp; k < 15; ++k)//最多到A
		{
			if (Cards[k] == NofC)
			{
				Cards[k] -= NofC;
				res[i][1]++;
			}
			else
			{
				break;
			}
		}
	}
	//检查是否能把顺子合并
	int resNumber = resCount;
	for (int i = 0; i < resCount; ++i)
	{
		if (res[i][0] != -1)//已经被合并
		{
			for (int j = i + 1; j < resCount; ++j)
			{
				if (res[j][0] != -1 && res[j][0] == res[i][0] + res[i][1])
				{
					res[j][0] = -1;
					res[i][1] += res[j][1];
					resNumber--;
				}
			}
		}	
	}
	//返回结果
	for (int i = 0; i < resCount; ++i)
	{
		if (res[i][0] != -1)
		{
			result[3 * i] = res[i][0];//第一张
			result[3 * i + 1] = res[i][1];//长度
			result[3 * i + 2] = LengthOfPg;//类型 2顺
		}
	}
	*Sum = resNumber;
}
/*
出牌显示
Out[0] 代表第一张牌
Out[1] 代表第一张牌的数量
Out[2] 代表出牌的种类，0，不是套牌：单张，对子，三张；1：顺子，2：双顺，3：飞机，4：炸弹王炸
Out[4] 代表能带几张牌，例如三带二等
Out[3][5][6][... ] 为带的牌的大小
*/
void card::Sort(int * Out, vector<int> &vc)
{
	if (Out[2] == 0)
	{		
		cout << "出：";
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0]);
		}
		if (Out[1] == 3 && Out[4] > 0)
		{
			for (int i = 0; i < Out[4]; i++)
			{
				vc.push_back(Out[3]);
			}
		}
	}
			//顺子
	else if (Out[2] == 1)
	{
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0] + i);
		}
	}
			//2顺
	else if (Out[2] == 2)
	{
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0] + i);
			vc.push_back(Out[0] + i);
		}
	}
		//飞机
	else if (Out[2] == 3)
	{
		for (int i = 0; i < Out[1]; ++i)
		{
			vc.push_back(Out[0] + i);
			vc.push_back(Out[0] + i);
			vc.push_back(Out[0] + i);
		}
		if (Out[4] > 0)
		{
			if (Out[4] > 1)
			{
				vc.push_back(Out[3]);
			}
			vc.push_back(Out[3]);
			for (int i = 1; i < Out[1]; ++i)
			{
				for (int j = 0; j < Out[4]; ++j)
				{
					vc.push_back(Out[4 + i]);
				}
			}
		}
	}
		//炸弹
	else
	{
		if (Out[0] == 17 && Out[2] == 4)
		{
			vc.push_back(16);
			vc.push_back(17);
		}
		else
		{
			for (int i = 0; i < 4; ++i)
			{
				vc.push_back(Out[0]);
			}
			if (Out[4] > 0)
			{
				for (int i = 0; i < Out[4]; ++i)
				{
					vc.push_back(Out[3]);
				}
				for (int i = 0; i < Out[4]; ++i)
				{
					vc.push_back(Out[5]);
				}
			}
		}
	}
	return;
}
#endif
//over//终于搞完了